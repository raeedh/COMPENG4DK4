
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
    // Simulation_Run_Data_Ptr data;
    // Channel_Ptr channel;

    this_packet = (Packet_Ptr) ptr;
    // data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    // channel = data->s_aloha_channel;

    /* This packet is starting to transmit. */
    // increment_transmitting_stn_count(channel);
    this_packet->status = TRANSMITTING;

    // if (get_channel_state(channel) != IDLE) {
    //     /* The s_aloha_channel is now colliding. */
    //     set_channel_state(channel, COLLISION);
    // } else {
    //     /* The s_aloha_channel is successful, for now. */
    //     set_channel_state(channel, SUCCESS);
    // }

    /* Schedule the end of packet transmission event. */
    schedule_transmission_end_event(
            simulation_run, simulation_run_get_time(simulation_run) + this_packet->service_time, (void *) this_packet);
}

/*******************************************************************************/

long int schedule_transmission_end_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "End of Packet (Station)";
    event.function = transmission_end_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void transmission_end_event(Simulation_Run_Ptr simulation_run, void *packet) {
    Packet_Ptr this_packet;
    Time now;
    Simulation_Run_Data_Ptr data;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    now = simulation_run_get_time(simulation_run);

    this_packet = (Packet_Ptr) packet;

    TRACE(printf("Success.\n"););

    output_blip_to_screen(simulation_run);

    /* Remove job from station queue and put into server queue */
    fifoqueue_get(data->station_queue);
    fifoqueue_put(data->server_queue, (void *) this_packet);

    if(fifoqueue_size(data->server_queue) == 1) {
    /* Execute job on server. */
        schedule_data_transmission_start_event(simulation_run, now, fifoqueue_get(data->server_queue));
    }

    /* Transmit next job in station queue if queue contains job */
    if(fifoqueue_size(data->station_queue) > 0) {
        schedule_transmission_start_event(simulation_run, now, fifoqueue_see_front(data->station_queue));
    }
}

/*******************************************************************************/

long int schedule_data_transmission_start_event(Simulation_Run_Ptr simulation_run, Time event_time, void *packet) {
    Event event;

    event.description = "Start Of Packet (Server)";
    event.function = data_transmission_start_event;
    event.attachment = packet;

    return simulation_run_schedule_event(simulation_run, event, event_time);
}

/*******************************************************************************/

void data_transmission_start_event(Simulation_Run_Ptr simulation_run, void *ptr) {
    Packet_Ptr this_packet;
    // Simulation_Run_Data_Ptr data;
    // Channel_Ptr channel;

    this_packet = (Packet_Ptr) ptr;
    // data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    // channel = data->data_channel;

    /* This packet is starting to transmit. */
    // increment_transmitting_stn_count(channel);
    // set_channel_state(channel, SUCCESS);

    this_packet->status = TRANSMITTING;

    double data_packet_service_time = MEAN_SERVER_SERVICE_TIME;

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
    Time now;
    Simulation_Run_Data_Ptr data;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    now = simulation_run_get_time(simulation_run);

    this_packet = (Packet_Ptr) packet;

    TRACE(printf("Success.\n"););

    /* Collect statistics. */
    data->number_of_packets_processed++;

    data->accumulated_delay += now - this_packet->arrive_time;
    if (this_packet->device_id) {
        data->b_delay += now - this_packet->arrive_time;
        data->b_processed++;
    } else {
        data->g_delay += now - this_packet->arrive_time;
        data->g_processed++;
    }


    output_blip_to_screen(simulation_run);

    /* This packet is done. */
    free((void *) packet);

    /* See if there is another packet in the server queue. If so, begin execution. */
    if (fifoqueue_size(data->server_queue) > 0) {
        next_packet = fifoqueue_get(data->server_queue);

        schedule_data_transmission_start_event(simulation_run, now, (void *) next_packet);
    }
}
