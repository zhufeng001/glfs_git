################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/protocol/server/src/authenticate.c \
../xlators/protocol/server/src/server-handshake.c \
../xlators/protocol/server/src/server-helpers.c \
../xlators/protocol/server/src/server-resolve.c \
../xlators/protocol/server/src/server-rpc-fops.c \
../xlators/protocol/server/src/server.c 

OBJS += \
./xlators/protocol/server/src/authenticate.o \
./xlators/protocol/server/src/server-handshake.o \
./xlators/protocol/server/src/server-helpers.o \
./xlators/protocol/server/src/server-resolve.o \
./xlators/protocol/server/src/server-rpc-fops.o \
./xlators/protocol/server/src/server.o 

C_DEPS += \
./xlators/protocol/server/src/authenticate.d \
./xlators/protocol/server/src/server-handshake.d \
./xlators/protocol/server/src/server-helpers.d \
./xlators/protocol/server/src/server-resolve.d \
./xlators/protocol/server/src/server-rpc-fops.d \
./xlators/protocol/server/src/server.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/protocol/server/src/%.o: ../xlators/protocol/server/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


