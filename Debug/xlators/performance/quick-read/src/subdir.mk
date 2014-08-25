################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/quick-read/src/quick-read.c 

OBJS += \
./xlators/performance/quick-read/src/quick-read.o 

C_DEPS += \
./xlators/performance/quick-read/src/quick-read.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/quick-read/src/%.o: ../xlators/performance/quick-read/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


