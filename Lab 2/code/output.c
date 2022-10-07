
/*
 * 
 * Simulation_Run of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
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

/******************************************************************************/

#include "output.h"
#include "main.h"
#include "simparameters.h"
#include <stdio.h>

/******************************************************************************/

/*
 * This function outputs a progress message to the screen to indicate this are
 * working.
 */

void output_progress_msg_to_screen(Simulation_Run_Ptr simulation_run) {
    double percentage_done;
    Simulation_Run_Data_Ptr data;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    data->blip_counter++;

    if ((data->blip_counter >= BLIPRATE) || (data->number_of_packets_processed >= RUNLENGTH)) {

        data->blip_counter = 0;

        percentage_done = 100 * (double) data->number_of_packets_processed / RUNLENGTH;

        printf("%3.0f%% ", percentage_done);

        printf("Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \r", data->number_of_packets_processed, data->arrival_count);

        fflush(stdout);
    }
}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void output_results(Simulation_Run_Ptr simulation_run) {
    double xmtted_fraction;
    Simulation_Run_Data_Ptr data;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    printf("\n");
    // printf("Random Seed = %d \n", data->random_seed);
    // printf("Packet arrival count = %ld \n", data->arrival_count);

    // xmtted_fraction = (double) data->number_of_packets_processed / data->arrival_count;

    // printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n", data->number_of_packets_processed, xmtted_fraction);

    // printf("Transmitted data packet count  = %ld\n", data->number_of_data_packets_processed);

    // printf("Transmitted voice packet count  = %ld\n", data->number_of_voice_packets_processed);

    // printf("Arrival rate = %.3f packets/second \n", (double) PACKET_ARRIVAL_RATE);

    // printf("Mean Delay (msec) = %.2f \n", 1e3 * data->accumulated_delay / data->number_of_packets_processed);

    // Mean Delay (msec) for data packets
    printf("%.2f,\n", 1e3 * data->accumulated_data_delay / data->number_of_data_packets_processed);

    // Mean Delay (msec) for voice packets
    printf("%.2f,\n", 1e3 * data->accumulated_voice_delay / data->number_of_voice_packets_processed);

    printf("\n");
}
