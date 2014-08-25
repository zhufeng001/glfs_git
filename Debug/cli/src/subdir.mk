################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cli/src/cli-cmd-misc.c \
../cli/src/cli-cmd-parser.c \
../cli/src/cli-cmd-peer.c \
../cli/src/cli-cmd-system.c \
../cli/src/cli-cmd-volume-bdevice.c \
../cli/src/cli-cmd-volume.c \
../cli/src/cli-cmd.c \
../cli/src/cli-rl.c \
../cli/src/cli-rpc-ops.c \
../cli/src/cli-xml-output.c \
../cli/src/cli.c \
../cli/src/input.c \
../cli/src/registry.c 

OBJS += \
./cli/src/cli-cmd-misc.o \
./cli/src/cli-cmd-parser.o \
./cli/src/cli-cmd-peer.o \
./cli/src/cli-cmd-system.o \
./cli/src/cli-cmd-volume-bdevice.o \
./cli/src/cli-cmd-volume.o \
./cli/src/cli-cmd.o \
./cli/src/cli-rl.o \
./cli/src/cli-rpc-ops.o \
./cli/src/cli-xml-output.o \
./cli/src/cli.o \
./cli/src/input.o \
./cli/src/registry.o 

C_DEPS += \
./cli/src/cli-cmd-misc.d \
./cli/src/cli-cmd-parser.d \
./cli/src/cli-cmd-peer.d \
./cli/src/cli-cmd-system.d \
./cli/src/cli-cmd-volume-bdevice.d \
./cli/src/cli-cmd-volume.d \
./cli/src/cli-cmd.d \
./cli/src/cli-rl.d \
./cli/src/cli-rpc-ops.d \
./cli/src/cli-xml-output.d \
./cli/src/cli.d \
./cli/src/input.d \
./cli/src/registry.d 


# Each subdirectory must supply rules for building sources it contributes
cli/src/%.o: ../cli/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


