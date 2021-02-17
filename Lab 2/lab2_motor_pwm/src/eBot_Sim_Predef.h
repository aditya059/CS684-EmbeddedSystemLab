/*
 * eBot_Sim_Predef.h
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */

#ifndef EBOT_SIM_PREDEF_H_
#define EBOT_SIM_PREDEF_H_


//---------------------------------- INCLUDES ----------------------------------

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

extern "C" {
	#include "extApi.h"
}


//---------------------------------- CONSTANTS ----------------------------------

#define LINEAR_VELOCITY_MAX		10


//---------------------------------- FUNCTIONS ----------------------------------

void init_remote_api_server(void);
void get_object_handles(void);
void start_simulation(void);
int init_setup(void);
void set_motor_velocities(void);
void forward(void);
void back(void);
void left(void);
void right(void);
void soft_left(void);
void soft_right(void);
void stop(void);
void velocity(int, int);
void thread_calls(void);
void _delay_ms(unsigned int);
void stop_simulation(void);
void exit_remote_api_server(void);
void clean_up(void);


#endif /* EBOT_SIM_PREDEF_H_ */
