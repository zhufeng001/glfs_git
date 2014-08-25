################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/index/src/index.c 

OBJS += \
./xlators/features/index/src/index.o 

C_DEPS += \
./xlators/features/index/src/index.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/index/src/%.o: ../xlators/features/index/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


