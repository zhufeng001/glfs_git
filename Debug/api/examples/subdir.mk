################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../api/examples/glfsxmp.c 

OBJS += \
./api/examples/glfsxmp.o 

C_DEPS += \
./api/examples/glfsxmp.d 


# Each subdirectory must supply rules for building sources it contributes
api/examples/%.o: ../api/examples/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


