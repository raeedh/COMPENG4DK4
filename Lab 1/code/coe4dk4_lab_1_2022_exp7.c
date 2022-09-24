/*
 *
 * Simulation of Single Server Queueing System
 *
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*******************************************************************************/

#include "simlib.h"
#include <stdio.h>

/*******************************************************************************/

/*
 * Simulation Parameters
 */

//#define RANDOM_SEED 5259140
#define NUMBER_TO_SERVE 100e6

#define SERVICE_TIME 10.0
//#define ARRIVAL_RATE 0.1

#define BLIP_RATE 100000000

/*******************************************************************************/

/*
 * main() uses various simulation parameters and creates a clock variable to
 * simulate real time. A loop repeatedly determines if the next event to occur
 * is a customer arrival or customer departure. In either case the state of the
 * system is updated and statistics are collected before the next
 * iteration. When it finally reaches NUMBER_TO_SERVE customers, the program
 * outputs some statistics such as mean delay.
 */

int main() {
    const int max_queue_sizes[] = {1, 10, 100, 1000};
    const double arrival_rates[] = {0.001, 0.01, 0.1, 1};
    const int random_seeds[] = {400188200, 1882004, 18820040, 188200400, 882004001, 820040018, 200400188, 4001882,   40018820,
                                400190637, 1906374, 19063740, 190637400, 906374001, 63740019,  637400190, 374001906, 740019063};

    const int NUM_QUEUE_SIZES = sizeof(max_queue_sizes) / sizeof(int);
    const int NUM_ARRIVAL_RATES = sizeof(arrival_rates) / sizeof(double);
    const int NUM_RANDOM_SEEDS = sizeof(random_seeds) / sizeof(int);

    for (int i = 0; i < NUM_QUEUE_SIZES; ++i) {
        const int MAX_QUEUE_SIZE = max_queue_sizes[i];

        for (int j = 0; j < NUM_ARRIVAL_RATES; ++j) {
            const double ARRIVAL_RATE = arrival_rates[j];
            const double INTER_ARRIVAL_TIME = 1.0 / ARRIVAL_RATE;

            double util = 0.0, fraction_served = 0.0, mean_number_system = 0.0, mean_delay = 0.0, fraction_rejected = 0.0;

            // Arrival rate,Random seed,Utilization,Fraction served,Mean number in system,Mean delay
            for (int k = 0; k < NUM_RANDOM_SEEDS; ++k) {
                const int RANDOM_SEED = random_seeds[k];

                double clock = 0; /* Clock keeps track of simulation time. */

                /* System state variables. */
                int number_in_system = 0;
                double next_arrival_time = 0;
                double next_departure_time = 0;
                double new_service_time = 0;

                /* Data collection variables. */
                long int total_served = 0;
                long int total_arrived = 0;
                long int total_rejected = 0;

                double total_busy_time = 0;
                double integral_of_n = 0;
                double last_event_time = 0;

                /* Set the seed of the random number generator. */
                random_generator_initialize(RANDOM_SEED);

                /* Process customers until we are finished. */
                while (total_served < NUMBER_TO_SERVE) {
                    /* Test if the next event is a customer arrival or departure. */
                    if (number_in_system == 0 || next_arrival_time < next_departure_time) {
                        /* A new arrival is occurring. */
                        clock = next_arrival_time;
                        next_arrival_time = clock + exponential_generator(INTER_ARRIVAL_TIME);

                        /* Update our statistics. */
                        integral_of_n += number_in_system * (clock - last_event_time);
                        last_event_time = clock;

                        // Number in queue is number in system - 1
                        if (number_in_system - 1 >= MAX_QUEUE_SIZE) {
                            total_rejected++;
                        } else {
                            number_in_system++;
                        }

                        total_arrived++;

                        /* If this customer has arrived to an empty system, start its service right away. */
                        if (number_in_system == 1) {
                            new_service_time = exponential_generator(SERVICE_TIME);
                            next_departure_time = clock + new_service_time;
                        }
                    } else {
                        /* A customer departure is occurring. */
                        clock = next_departure_time;

                        /* Update our statistics. */
                        integral_of_n += number_in_system * (clock - last_event_time);
                        last_event_time = clock;

                        number_in_system--;
                        total_served++;
                        total_busy_time += new_service_time;

                        /* If there are other customers waiting, start one in service right away. */
                        if (number_in_system > 0) {
                            new_service_time = exponential_generator(SERVICE_TIME);
                            next_departure_time = clock + new_service_time;
                        }

                        /* Every so often, print an activity message to show we are active. */
                        if (total_served % BLIP_RATE == 0) {
                            printf("Max Queue Size = %d, Arrival rate = %f, Random seed = %d, Customers served = %ld, Customers rejected = "
                                   "%ld (Total arrived = %ld)\r",
                                   MAX_QUEUE_SIZE, ARRIVAL_RATE, RANDOM_SEED, total_served, total_rejected, total_arrived);
                        }
                    }
                }

                util = util + total_busy_time / clock;
                fraction_served = fraction_served + (double) total_served / total_arrived;
                mean_number_system = mean_number_system + integral_of_n / clock;
                mean_delay = mean_delay + integral_of_n / total_served;
                fraction_rejected = fraction_rejected + (double) total_rejected / total_arrived;
            }

            printf("%d, %f, %f, %f, %f, %f, %f\n", MAX_QUEUE_SIZE, ARRIVAL_RATE, util / NUM_RANDOM_SEEDS,
                   fraction_served / NUM_RANDOM_SEEDS, mean_number_system / NUM_RANDOM_SEEDS, mean_delay / NUM_RANDOM_SEEDS,
                   fraction_rejected / NUM_RANDOM_SEEDS);
        }
    }

    return 0;
}