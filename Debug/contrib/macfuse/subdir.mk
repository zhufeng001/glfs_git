################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/macfuse/mount_darwin.c 

OBJS += \
./contrib/macfuse/mount_darwin.o 

C_DEPS += \
./contrib/macfuse/mount_darwin.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/macfuse/%.o: ../contrib/macfuse/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


