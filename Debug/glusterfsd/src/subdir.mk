################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../glusterfsd/src/glusterfsd-mgmt.c \
../glusterfsd/src/glusterfsd.c 

OBJS += \
./glusterfsd/src/glusterfsd-mgmt.o \
./glusterfsd/src/glusterfsd.o 

C_DEPS += \
./glusterfsd/src/glusterfsd-mgmt.d \
./glusterfsd/src/glusterfsd.d 


# Each subdirectory must supply rules for building sources it contributes
glusterfsd/src/%.o: ../glusterfsd/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


