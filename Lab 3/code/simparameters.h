
/*
 * 
 * Call Blocking in Circuit Switched Networks
 * 
 * Copyright (C) 2014 Terence D. Todd
 * Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 * 
 */

/*******************************************************************************/

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/

#define Call_ARRIVALRATE 3   /* calls/minute */
#define MEAN_CALL_DURATION 3 /* minutes */
#define RUNLENGTH 5e6        /* number of successful calls */
#define BLIPRATE 1e3
#define NUMBER_OF_CHANNELS 11

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST                                                                                                                   \
    400188200, 1882004, 18820040, 188200400, 882004001, 820040018, 200400188, 4001882, 40018820, 400190637, 1906374, 19063740, 190637400,  \
            906374001, 63740019, 637400190, 374001906, 740019063

/*******************************************************************************/

#endif /* simparameters.h */
