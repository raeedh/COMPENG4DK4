
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

#include "channel.h"
#include "main.h"
#include "simparameters.h"
#include <stdio.h>

/*******************************************************************************/

/*
 *
 * Define some channel state helper functions.
 *
 */

Channel_Ptr channel_new() {
    Channel_Ptr new_channel;

    new_channel = (Channel_Ptr) xmalloc(sizeof(Channel));
    set_channel_state(new_channel, IDLE);
    reset_transmitting_stn_count(new_channel);
    return new_channel;
}

Channel_State get_channel_state(Channel_Ptr channel) {
    return channel->state;
}

void set_channel_state(Channel_Ptr channel, Channel_State state) {
    channel->state = state;
}

int get_transmitting_stn_count(Channel_Ptr channel) {
    return channel->transmitting_stn_count;
}

void increment_transmitting_stn_count(Channel_Ptr channel) {
    channel->transmitting_stn_count++;
}

void decrement_transmitting_stn_count(Channel_Ptr channel) {
    channel->transmitting_stn_count--;
}

void reset_transmitting_stn_count(Channel_Ptr channel) {
    channel->transmitting_stn_count = 0;
}