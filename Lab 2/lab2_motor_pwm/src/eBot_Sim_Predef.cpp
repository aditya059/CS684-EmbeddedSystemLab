/*
 * eBot_Sim_Predef.cpp
 *
 *  Created on: 11-Jan-2021
 *      Author: TAs of CS 684 Spring 2020
 */


//---------------------------------- INCLUDES ----------------------------------

#include "eBot_Sim_Predef.h"


//------------------------------ GLOBAL VARIABLES -------------------------------

// store the client id for connection with CoppeliaSim
simxInt client_id = -1;

// store the ping time before stopping the connection with CoppeliaSim
simxInt *ping_time = new simxInt[1]();

// store the return code of various Remote API calls
simxInt return_code = -1;

// get the handle of robot with object named as 'eBot' in the CoppeliaSim scene
simxInt *eBot_handle = new simxInt[1]();

// get the handle of robot's left motor with object named as 'LeftJoint' in the CoppeliaSim scene
simxInt *left_joint_handle = new simxInt[1]();

// get the handle of robot's right motor with object named as 'RightJoint' in the CoppeliaSim scene
simxInt *right_joint_handle = new simxInt[1]();

// flags for setting direction of robot's left and right motors
simxInt dir_left_motor = 0, dir_right_motor = 0;

// to provide variable linear velocity to robot's left and right motors
simxFloat linear_velocity_left_motor = 0, linear_velocity_right_motor = 0;


//---------------------------------- FUNCTIONS ----------------------------------

/**
 * @brief      Initializes the connection to CoppeliaSim Remote API Server
 */
void init_remote_api_server(void)
{
	int port_number = 19997;

	// just in case, close all opened connections
	simxFinish(-1);

	// connect to CoppeliaSim
	client_id = simxStart("127.0.0.1", port_number, true, true, 5000, 5);
}


/**
 * @brief      Collect the handles of all objects in the current CoppeliaSim scene
 */
void get_object_handles(void)
{
	return_code = -1;

	return_code = simxGetObjectHandle(client_id, "eBot", eBot_handle, simx_opmode_blocking);

	if (return_code == simx_return_ok)
	{
		simxGetObjectHandle(client_id, "LeftJoint", left_joint_handle, simx_opmode_blocking);
		simxGetObjectHandle(client_id, "RightJoint", right_joint_handle, simx_opmode_blocking);
	}
}


/**
 * @brief      Starts the simulation in CoppeliaSim
 */
void start_simulation(void)
{
	return_code = -1;

	printf("\n\tEnter 'Y' or 'y' to start the simulation: ");

	char input_cmd = getchar();

	if (input_cmd == 'Y' || input_cmd == 'y')
	{
		do
		{
			return_code = simxStartSimulation(client_id, simx_opmode_oneshot_wait);
		} while (return_code != simx_return_ok);
	}
}


/**
 * @brief      Initializes the setup by connecting to CoppeliaSim and starting the simulation
 */
int init_setup(void)
{
	// Initialize the connection to CoppeliaSim Remote API Server
	printf("\n\tCoppeliaSim Remote API Server initiated.");
	printf("\n\tTrying to connect to CoppeliaSim Remote API Server ...");

	init_remote_api_server();

	if (client_id == -1)
	{
		printf("\n\tFailed connecting to remote API server!");
		printf("\n\t[WARNING] Make sure the CoppeliaSim software is running and");
		printf("\n\t[WARNING] Make sure the Port number for Remote API Server is set to 19997.");

		return 0;
	}
	else
	{
		printf("\n\tConnected successfully to Remote API Server in CoppeliaSim!");

		// Get the handles of all objects in the scene if connection to CoppeliaSim was successful
		get_object_handles();

		if (return_code == simx_return_ok)
		{
			printf("\n\tCollected handles of all objects in the current CoppeliaSim scene.");

			// Start the simulation
			start_simulation();

			if (return_code == simx_return_ok)
			{
				printf("\n\tSimulation started correctly.");

				return 1;
			}
		}
	}

	return 0;
}


/**
 * @brief      Updates the speed of robot's left and right motors
 */
void set_motor_velocities(void)
{
	simxSetJointTargetVelocity(client_id, *left_joint_handle, linear_velocity_left_motor, simx_opmode_oneshot);
	simxSetJointTargetVelocity(client_id, *right_joint_handle, linear_velocity_right_motor, simx_opmode_oneshot);
}


/**
 * @brief      Makes the robot move forward
 */
void forward(void)
{
	dir_left_motor = dir_right_motor = 1;
	linear_velocity_left_motor = linear_velocity_right_motor = LINEAR_VELOCITY_MAX;
}


/**
 * @brief      Makes the robot move backward
 */
void back(void)
{
	dir_left_motor = dir_right_motor = -1;
	linear_velocity_left_motor = linear_velocity_right_motor = LINEAR_VELOCITY_MAX;
}


/**
 * @brief      Makes the robot take hard left turn
 */
void left(void)
{
	dir_left_motor = -1;
	dir_right_motor = 1;
	linear_velocity_left_motor = -LINEAR_VELOCITY_MAX;
	linear_velocity_right_motor = LINEAR_VELOCITY_MAX;
}


/**
 * @brief      Makes the robot take hard right turn
 */
void right(void)
{
	dir_left_motor = 1;
	dir_right_motor = -1;
	linear_velocity_left_motor = LINEAR_VELOCITY_MAX;
	linear_velocity_right_motor = -LINEAR_VELOCITY_MAX;
}


/**
 * @brief      Makes the robot take soft left turn
 */
void soft_left(void)
{
	dir_left_motor = 0;
	dir_right_motor = 1;
	linear_velocity_left_motor = 0;
	linear_velocity_right_motor = LINEAR_VELOCITY_MAX;
}


/**
 * @brief      Makes the robot take soft right turn
 */
void soft_right(void)
{
	dir_left_motor = 1;
	dir_right_motor = 0;
	linear_velocity_left_motor = LINEAR_VELOCITY_MAX;
	linear_velocity_right_motor = 0;
}


/**
 * @brief      Stops the robot's left and right motors
 */
void stop(void)
{
	dir_left_motor = 0;
	dir_right_motor = 0;
	linear_velocity_left_motor = 0;
	linear_velocity_right_motor = 0;
}


/**
 * @brief      Configures the speed of robot's left and right motors
 */
void velocity(int left_motor_speed, int right_motor_speed)
{
	if (left_motor_speed > 255)
		left_motor_speed = 255;

	else if (left_motor_speed < 0)
		left_motor_speed = 0;

	if (right_motor_speed > 255)
		right_motor_speed = 255;

	else if (right_motor_speed < 0)
		right_motor_speed = 0;

	linear_velocity_left_motor = ( dir_left_motor * LINEAR_VELOCITY_MAX * left_motor_speed ) / float(255.0);
	linear_velocity_right_motor = ( dir_right_motor * LINEAR_VELOCITY_MAX * right_motor_speed ) / float(255.0);
}


/**
 * @brief      Starts the thread to set the motor velocities
 */
void thread_calls(void)
{
	while (client_id != -1)
	{
		set_motor_velocities();
	}
}


/**
 * @brief      Generates the delay for the provided number of milliseconds
 */
void _delay_ms(unsigned int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}


/**
 * @brief      Stops the simulation in CoppeliaSim
 */
void stop_simulation(void)
{
	return_code = -1;

	do
	{
		return_code = simxStopSimulation(client_id, simx_opmode_oneshot);
	} while (return_code != simx_return_novalue_flag);
}


/**
 * @brief      Stops the connection to CoppeliaSim Remote API Server
 */
void exit_remote_api_server(void)
{
	// before closing the connection to CoppeliaSim, make sure that the last command sent out had time to arrive
	simxGetPingTime(client_id, ping_time);

	// close the connection to CoppeliaSim
	simxFinish(-1);
}


/**
 * @brief      Stops the robot's left and right motor, stops the simulation and
 * 			   closes the connection with CoppeliaSim Remote API Server
 */
void clean_up(void)
{
	velocity(0, 0);
	set_motor_velocities();

	// Stopping the simulation
	stop_simulation();

	if (return_code == simx_return_novalue_flag)
	{
		printf("\n\tSimulation stopped correctly.");

		// Stop the connection with CoppeliaSim Remote API server
		exit_remote_api_server();

		printf("\n\tDisconnected successfully to Remote API Server in CoppeliaSim!");

		// Reset the client_id
		client_id = -1;
	}
}

