################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/storage/bd_map/src/bd_map.c \
../xlators/storage/bd_map/src/bd_map_help.c 

OBJS += \
./xlators/storage/bd_map/src/bd_map.o \
./xlators/storage/bd_map/src/bd_map_help.o 

C_DEPS += \
./xlators/storage/bd_map/src/bd_map.d \
./xlators/storage/bd_map/src/bd_map_help.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/storage/bd_map/src/%.o: ../xlators/storage/bd_map/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


