################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/performance/symlink-cache/src/symlink-cache.c 

OBJS += \
./xlators/performance/symlink-cache/src/symlink-cache.o 

C_DEPS += \
./xlators/performance/symlink-cache/src/symlink-cache.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/performance/symlink-cache/src/%.o: ../xlators/performance/symlink-cache/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


