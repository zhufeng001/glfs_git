################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/debug/trace/src/trace.c 

OBJS += \
./xlators/debug/trace/src/trace.o 

C_DEPS += \
./xlators/debug/trace/src/trace.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/debug/trace/src/%.o: ../xlators/debug/trace/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


