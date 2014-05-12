################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/simp/SimpMain.cc \
../src/simp/SimpSolver.cc 

OBJS += \
./src/simp/SimpMain.o \
./src/simp/SimpSolver.o 

CC_DEPS += \
./src/simp/SimpMain.d \
./src/simp/SimpSolver.d 


# Each subdirectory must supply rules for building sources it contributes
src/simp/%.o: ../src/simp/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/opt/n1ge/include -I/usr/local/boost/include -O0 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


