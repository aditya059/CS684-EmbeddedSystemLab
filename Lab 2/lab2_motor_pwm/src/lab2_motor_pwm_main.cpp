//============================================================================
// Name        : lab2_motor_pwm.cpp
// Author      : TAs of CS 684 Spring 2020
// Description : To traverse "S" shape by controlling the speed of motors
//============================================================================


#include "eBot_Sandbox.h"


// Main Function
int main(int argc, char* argv[])
{
	int init_setup_success = 0;

	init_setup_success = init_setup();

	if (init_setup_success)
	{
		#ifdef NON_MATLAB_PARSING
			std::thread t_1(thread_calls);
			_delay_ms(4000);
		#endif

		traverse_s_shape();

		#ifdef NON_MATLAB_PARSING
			clean_up();
			t_1.detach();
		#endif
	}
	else
	{
	}
}
