
/*
 * 
 * Simulation of A Single Server Queueing System
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

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/******************************************************************************/

#define LINK1_PACKET_ARRIVAL_RATE 750   /* packets per second */
#define LINK2_3_PACKET_ARRIVAL_RATE 500 /* packets per second */
#define PACKET_LENGTH 1000              /* bits */
#define LINK1_BIT_RATE 2e6              /* bits per second */
#define LINK2_3_BIT_RATE 1e6            /* bits per second */
#define RUNLENGTH 10e6                  /* packets */

#define P12 0.9

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST                                                                                                                   \
    400188200, 1882004, 18820040, 188200400, 882004001, 820040018, 200400188, 4001882, 40018820, 400190637, 1906374, 19063740, 190637400,  \
            906374001, 63740019, 637400190, 374001906, 740019063

#define LINK1_PACKET_XMT_TIME ((double) PACKET_LENGTH / LINK1_BIT_RATE)
#define LINK2_3_PACKET_XMT_TIME ((double) PACKET_LENGTH / LINK2_3_BIT_RATE)
#define BLIPRATE (RUNLENGTH / 1000)

/******************************************************************************/

#endif /* _SIMPARAMETERS_H_ */
