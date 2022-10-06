
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

#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************************/

#include "simlib.h"
#include "simparameters.h"

/******************************************************************************/

typedef struct _simulation_run_data_ {
    Fifoqueue_Ptr buffer;
    Server_Ptr link1;
    Server_Ptr link2;
    long int blip_counter;
    long int arrival_count;
    long int number_of_packets_processed;
    double accumulated_delay;
    unsigned random_seed;
} Simulation_Run_Data, *Simulation_Run_Data_Ptr;

typedef enum { XMTTING, WAITING } Packet_Status;

typedef struct _packet_ {
    double arrive_time;
    double service_time;
    int source_id;
    int destination_id;
    Packet_Status status;
} Packet, *Packet_Ptr;

/*
 * Function prototypes
 */

int main(void);

/******************************************************************************/

#endif /* main.h */
