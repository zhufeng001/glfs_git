################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/debug/io-stats/src/io-stats.c 

OBJS += \
./xlators/debug/io-stats/src/io-stats.o 

C_DEPS += \
./xlators/debug/io-stats/src/io-stats.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/debug/io-stats/src/%.o: ../xlators/debug/io-stats/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


