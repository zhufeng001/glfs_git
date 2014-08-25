################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/protocol/client/src/client-callback.c \
../xlators/protocol/client/src/client-handshake.c \
../xlators/protocol/client/src/client-helpers.c \
../xlators/protocol/client/src/client-lk.c \
../xlators/protocol/client/src/client-rpc-fops.c \
../xlators/protocol/client/src/client.c 

OBJS += \
./xlators/protocol/client/src/client-callback.o \
./xlators/protocol/client/src/client-handshake.o \
./xlators/protocol/client/src/client-helpers.o \
./xlators/protocol/client/src/client-lk.o \
./xlators/protocol/client/src/client-rpc-fops.o \
./xlators/protocol/client/src/client.o 

C_DEPS += \
./xlators/protocol/client/src/client-callback.d \
./xlators/protocol/client/src/client-handshake.d \
./xlators/protocol/client/src/client-helpers.d \
./xlators/protocol/client/src/client-lk.d \
./xlators/protocol/client/src/client-rpc-fops.d \
./xlators/protocol/client/src/client.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/protocol/client/src/%.o: ../xlators/protocol/client/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


