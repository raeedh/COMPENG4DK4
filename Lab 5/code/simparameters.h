
/*
 * Simulation of the ALOHA Protocol
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

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/

// #define NUMBER_OF_STATIONS 10
#define MEAN_STATION_SERVICE_TIME 1      /* normalized packet Tx time */
#define MEAN_SERVER_SERVICE_TIME 1
#define PACKET_ARRIVAL_RATE 0.085     /* packets per Tx time */
#define RUNLENGTH 70000000
#define BLIPRATE 10000000
// #define EPSILON 0.01
// #define SLOT_DURATION (0.98 + EPSILON * 2)

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400188200, 1882004, 18820040, 188200400, 400190637, 1906374, 19063740, 190637400

/*******************************************************************************/

#endif /* simparameters.h */






