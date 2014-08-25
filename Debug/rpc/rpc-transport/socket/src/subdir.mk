################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rpc/rpc-transport/socket/src/name.c \
../rpc/rpc-transport/socket/src/socket.c 

OBJS += \
./rpc/rpc-transport/socket/src/name.o \
./rpc/rpc-transport/socket/src/socket.o 

C_DEPS += \
./rpc/rpc-transport/socket/src/name.d \
./rpc/rpc-transport/socket/src/socket.d 


# Each subdirectory must supply rules for building sources it contributes
rpc/rpc-transport/socket/src/%.o: ../rpc/rpc-transport/socket/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


