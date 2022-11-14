
/*
 * Simulation_Run of the ALOHA Protocol
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#include "packet_transmission.h"
#include "channel.h"
#include "output.h"
#include "packet_duration.h"
#include "trace.h"
#include <math.h>
#include <stdio.h>

/*******************************************************************************/

long int schedule_transmission_start_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "Start Of Packet";
    event.function = transmission_start_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void transmission_start_event(Simulation_Run_Ptr simulation_run, void *ptr) {
    Packet_Ptr this_packet;
    Simulation_Run_Data_Ptr data;
    Channel_Ptr channel;

    this_packet = (Packet_Ptr) ptr;
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    channel = data->s_aloha_channel;

    /* This packet is starting to transmit. */
    increment_transmitting_stn_count(channel);
    this_packet->status = TRANSMITTING;

    if (get_channel_state(channel) != IDLE) {
        /* The s_aloha_channel is now colliding. */
        set_channel_state(channel, COLLISION);
    } else {
        /* The s_aloha_channel is successful, for now. */
        set_channel_state(channel, SUCCESS);
    }

    /* Schedule the end of packet transmission event. */
    schedule_transmission_end_event(
            simulation_run,
            SLOT_DURATION * ceil((simulation_run_get_time(simulation_run) + this_packet->service_time) / SLOT_DURATION) - EPSILON,
            (void *) this_packet);
}

/*******************************************************************************/

long int schedule_transmission_end_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "End of Packet";
    event.function = transmission_end_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void transmission_end_event(Simulation_Run_Ptr simulation_run, void *packet) {
    Packet_Ptr this_packet, next_packet;
    Buffer_Ptr buffer;
    Time backoff_duration, now;
    Simulation_Run_Data_Ptr data;
    Channel_Ptr channel;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    channel = data->s_aloha_channel;

    now = simulation_run_get_time(simulation_run);

    this_packet = (Packet_Ptr) packet;
    buffer = (data->stations + this_packet->station_id)->buffer;

    /* This station has stopped transmitting. */
    decrement_transmitting_stn_count(channel);

    /* Check if the packet was successful. */
    if (get_channel_state(channel) == SUCCESS) {

        /* Transmission was a success. The s_aloha_channel is now IDLE. */
        set_channel_state(channel, IDLE);

        TRACE(printf("Success.\n"););

        output_blip_to_screen(simulation_run);

        /* See if there is another packet at this station. If so, enable it for transmission. We will transmit immediately. */
        if (fifoqueue_size(buffer) > 0) {
            next_packet = fifoqueue_see_front(buffer);

            schedule_transmission_start_event(simulation_run, now, (void *) next_packet);
        }

        if (get_channel_state(data->data_channel) != IDLE) {
            fifoqueue_put(data->data_channel_queue, (void *) this_packet);
        } else {
            schedule_data_transmission_start_event(simulation_run, now, (void *) this_packet);
        }
    } else {
        /* The transmission was unsuccessful. Clean up the s_aloha_channel state, backoff, and try again. */
        this_packet->collision_count++;
        this_packet->status = WAITING;

        TRACE(printf("Collision. Collision count = %i\n", this_packet->collision_count););

        /* If the collision is over, free up the s_aloha_channel. */
        if (get_transmitting_stn_count(channel) == 0) {
            set_channel_state(channel, IDLE);
        }

        backoff_duration = SLOT_DURATION * ceil(uniform_generator() * pow(2.0, this_packet->collision_count));

        schedule_transmission_start_event(simulation_run, now + backoff_duration, (void *) this_packet);
    }
}

/*******************************************************************************/

long int schedule_data_transmission_start_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "Start Of Packet";
    event.function = data_transmission_start_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void data_transmission_start_event(Simulation_Run_Ptr simulation_run, void *ptr) {
    Packet_Ptr this_packet;
    Simulation_Run_Data_Ptr data;
    Channel_Ptr channel;

    this_packet = (Packet_Ptr) ptr;
    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    channel = data->data_channel;

    /* This packet is starting to transmit. */
    increment_transmitting_stn_count(channel);
    set_channel_state(channel, SUCCESS);

    this_packet->status = TRANSMITTING;

    double data_packet_service_time = get_data_packet_duration();

    this_packet->service_time += data_packet_service_time;

    /* Schedule the end of data packet transmission event. */
    schedule_data_transmission_end_event(simulation_run, simulation_run_get_time(simulation_run) + data_packet_service_time,
                                         (void *) this_packet);
}

/*******************************************************************************/

long int schedule_data_transmission_end_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "End of Packet";
    event.function = data_transmission_end_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void data_transmission_end_event(Simulation_Run_Ptr simulation_run, void *packet) {
    Packet_Ptr this_packet, next_packet;
    Buffer_Ptr data_buffer;
    Time now;
    Simulation_Run_Data_Ptr data;
    Channel_Ptr channel;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);
    channel = data->data_channel;

    now = simulation_run_get_time(simulation_run);

    this_packet = (Packet_Ptr) packet;
    data_buffer = data->data_channel_queue;

    /* This station has stopped transmitting. */
    decrement_transmitting_stn_count(channel);
    set_channel_state(channel, IDLE);

    TRACE(printf("Success.\n"););

    /* Collect statistics. */
    data->number_of_packets_processed++;

    (data->stations + this_packet->station_id)->packet_count++;
    (data->stations + this_packet->station_id)->accumulated_delay += now - this_packet->arrive_time;

    data->number_of_collisions += this_packet->collision_count;
    data->accumulated_delay += now - this_packet->arrive_time;

    output_blip_to_screen(simulation_run);

    /* This packet is done. */
    free((void *) fifoqueue_get(data_buffer));

    /* See if there is another packet in the data channel queue. If so, enable it for transmission. We will transmit immediately. */
    if (fifoqueue_size(data_buffer) > 0) {
        next_packet = fifoqueue_see_front(data_buffer);

        schedule_data_transmission_start_event(simulation_run, now, (void *) next_packet);
    }
}
