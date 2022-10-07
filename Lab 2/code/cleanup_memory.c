
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

#include "cleanup_memory.h"
#include "main.h"
#include "simlib.h"

/******************************************************************************/

/*
 * When a simulation_run run is finished, this function cleans up the memory
 * that has been allocated.
 */

void cleanup_memory(Simulation_Run_Ptr simulation_run) {
    Simulation_Run_Data_Ptr data;
    Fifoqueue_Ptr buffer;
    Server_Ptr link;

    data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

    // Free link 1
    link = data->link1;
    if (link->state == BUSY) /* Clean out the server. */
        xfree(server_get(link));
    xfree(link);

    // Free link 2
    link = data->link2;
    if (link->state == BUSY) /* Clean out the server. */
        xfree(server_get(link));
    xfree(link);

    // Free link 3
    link = data->link3;
    if (link->state == BUSY) /* Clean out the server. */
        xfree(server_get(link));
    xfree(link);

    // Free buffer 1
    buffer = data->buffer1;
    while (fifoqueue_size(buffer) > 0) /* Clean out the queue. */
        xfree(fifoqueue_get(buffer));
    xfree(buffer);

    // Free buffer 2
    buffer = data->buffer2;
    while (fifoqueue_size(buffer) > 0) /* Clean out the queue. */
        xfree(fifoqueue_get(buffer));
    xfree(buffer);

    // Free buffer 3
    buffer = data->buffer3;
    while (fifoqueue_size(buffer) > 0) /* Clean out the queue. */
        xfree(fifoqueue_get(buffer));
    xfree(buffer);

    simulation_run_free_memory(simulation_run); /* Clean up the simulation_run. */
}
