################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/eBot_Sandbox.cpp \
../src/lab1_sw_led_main.cpp 

C_SRCS += \
../src/eBot_MCU_Predef.c 

OBJS += \
./src/eBot_MCU_Predef.o \
./src/eBot_Sandbox.o \
./src/lab1_sw_led_main.o 

CPP_DEPS += \
./src/eBot_Sandbox.d \
./src/lab1_sw_led_main.d 

C_DEPS += \
./src/eBot_MCU_Predef.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


