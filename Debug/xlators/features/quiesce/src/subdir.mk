################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/features/quiesce/src/quiesce.c 

OBJS += \
./xlators/features/quiesce/src/quiesce.o 

C_DEPS += \
./xlators/features/quiesce/src/quiesce.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/features/quiesce/src/%.o: ../xlators/features/quiesce/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


