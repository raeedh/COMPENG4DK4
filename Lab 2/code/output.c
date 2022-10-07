
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

    int num_packets_processed = data->number_of_link2_packets_processed + data->number_of_link3_packets_processed;

    if ((data->blip_counter >= BLIPRATE) || (num_packets_processed >= RUNLENGTH)) {

        data->blip_counter = 0;

        percentage_done = 100 * (double) (data->number_of_link2_packets_processed + data->number_of_link3_packets_processed) / RUNLENGTH;

        printf("%3.0f%% ", percentage_done);

        printf("Success Xmtted Pkts: link 1 = %ld (Arr Pkts = %ld), link 2 = %ld (Arr Pkts = %ld), link 3 = %ld (Arr Pkts = %ld) \r",
               data->number_of_link1_packets_processed, data->arrival_count_link1, data->number_of_link2_packets_processed,
               data->arrival_count_link2, data->number_of_link3_packets_processed, data->arrival_count_link3);

        fflush(stdout);
    }
}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void output_results(Simulation_Run_Ptr simulation_run) {
    double xmtted_fraction_link1, xmtted_fraction_link2, xmtted_fraction_link3;
    Simulation_Run_Data_Ptr data;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    //    printf("\n");
    //    printf("Random Seed = %d\n", data->random_seed);
    //    printf("Packet arrival count: switch 1 = %ld, switch 2 = %ld, switch 3 = %ld\n", data->arrival_count_link1, data->arrival_count_link2,
    //           data->arrival_count_link3);
    //    printf("Probability of 1->2: %.5f\n", P12);
    //
    //    xmtted_fraction_link1 = (double) data->number_of_link1_packets_processed / data->arrival_count_link1;
    //    xmtted_fraction_link2 = (double) data->number_of_link2_packets_processed / data->arrival_count_link2;
    //    xmtted_fraction_link3 = (double) data->number_of_link3_packets_processed / data->arrival_count_link3;
    //
    //    printf("Transmitted packet count: switch 1 = %ld (Service Fraction = %.5f), switch 2 = %ld (Service Fraction = %.5f), switch 3 = %ld "
    //           "(Service Fraction = %.5f)\n",
    //           data->number_of_link1_packets_processed, xmtted_fraction_link1, data->number_of_link2_packets_processed, xmtted_fraction_link2,
    //           data->number_of_link3_packets_processed, xmtted_fraction_link3);

    //    printf("Arrival rate: switch 1 = %.3f packets/second, switch 2 & 3 = %.3f packets/second\n", (double) LINK1_PACKET_ARRIVAL_RATE,
    //           (double) LINK2_3_PACKET_ARRIVAL_RATE);

    double switch1_mean_delay = 1e3 * data->accumulated_delay_link1 / data->number_of_link1_packets_processed;
    double switch2_mean_delay = 1e3 * data->accumulated_delay_link2 / data->number_of_link2_packets_processed;
    double switch3_mean_delay = 1e3 * data->accumulated_delay_link3 / data->number_of_link3_packets_processed;
    printf("Switch 1 Mean Delay (msec) = %.2f, Switch 2 Mean Delay (msec) = %.2f, Switch 3 Mean Delay (msec) = %.2f\n", switch1_mean_delay,
           switch2_mean_delay, switch3_mean_delay);

    //    printf("\n");
}
