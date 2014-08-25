################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/mgmt/glusterd/src/glusterd-brick-ops.c \
../xlators/mgmt/glusterd/src/glusterd-geo-rep.c \
../xlators/mgmt/glusterd/src/glusterd-handler.c \
../xlators/mgmt/glusterd/src/glusterd-handshake.c \
../xlators/mgmt/glusterd/src/glusterd-hooks.c \
../xlators/mgmt/glusterd/src/glusterd-log-ops.c \
../xlators/mgmt/glusterd/src/glusterd-mountbroker.c \
../xlators/mgmt/glusterd/src/glusterd-op-sm.c \
../xlators/mgmt/glusterd/src/glusterd-pmap.c \
../xlators/mgmt/glusterd/src/glusterd-quota.c \
../xlators/mgmt/glusterd/src/glusterd-rebalance.c \
../xlators/mgmt/glusterd/src/glusterd-replace-brick.c \
../xlators/mgmt/glusterd/src/glusterd-rpc-ops.c \
../xlators/mgmt/glusterd/src/glusterd-sm.c \
../xlators/mgmt/glusterd/src/glusterd-store.c \
../xlators/mgmt/glusterd/src/glusterd-syncop.c \
../xlators/mgmt/glusterd/src/glusterd-utils.c \
../xlators/mgmt/glusterd/src/glusterd-volgen.c \
../xlators/mgmt/glusterd/src/glusterd-volume-ops.c \
../xlators/mgmt/glusterd/src/glusterd-volume-set.c \
../xlators/mgmt/glusterd/src/glusterd.c 

OBJS += \
./xlators/mgmt/glusterd/src/glusterd-brick-ops.o \
./xlators/mgmt/glusterd/src/glusterd-geo-rep.o \
./xlators/mgmt/glusterd/src/glusterd-handler.o \
./xlators/mgmt/glusterd/src/glusterd-handshake.o \
./xlators/mgmt/glusterd/src/glusterd-hooks.o \
./xlators/mgmt/glusterd/src/glusterd-log-ops.o \
./xlators/mgmt/glusterd/src/glusterd-mountbroker.o \
./xlators/mgmt/glusterd/src/glusterd-op-sm.o \
./xlators/mgmt/glusterd/src/glusterd-pmap.o \
./xlators/mgmt/glusterd/src/glusterd-quota.o \
./xlators/mgmt/glusterd/src/glusterd-rebalance.o \
./xlators/mgmt/glusterd/src/glusterd-replace-brick.o \
./xlators/mgmt/glusterd/src/glusterd-rpc-ops.o \
./xlators/mgmt/glusterd/src/glusterd-sm.o \
./xlators/mgmt/glusterd/src/glusterd-store.o \
./xlators/mgmt/glusterd/src/glusterd-syncop.o \
./xlators/mgmt/glusterd/src/glusterd-utils.o \
./xlators/mgmt/glusterd/src/glusterd-volgen.o \
./xlators/mgmt/glusterd/src/glusterd-volume-ops.o \
./xlators/mgmt/glusterd/src/glusterd-volume-set.o \
./xlators/mgmt/glusterd/src/glusterd.o 

C_DEPS += \
./xlators/mgmt/glusterd/src/glusterd-brick-ops.d \
./xlators/mgmt/glusterd/src/glusterd-geo-rep.d \
./xlators/mgmt/glusterd/src/glusterd-handler.d \
./xlators/mgmt/glusterd/src/glusterd-handshake.d \
./xlators/mgmt/glusterd/src/glusterd-hooks.d \
./xlators/mgmt/glusterd/src/glusterd-log-ops.d \
./xlators/mgmt/glusterd/src/glusterd-mountbroker.d \
./xlators/mgmt/glusterd/src/glusterd-op-sm.d \
./xlators/mgmt/glusterd/src/glusterd-pmap.d \
./xlators/mgmt/glusterd/src/glusterd-quota.d \
./xlators/mgmt/glusterd/src/glusterd-rebalance.d \
./xlators/mgmt/glusterd/src/glusterd-replace-brick.d \
./xlators/mgmt/glusterd/src/glusterd-rpc-ops.d \
./xlators/mgmt/glusterd/src/glusterd-sm.d \
./xlators/mgmt/glusterd/src/glusterd-store.d \
./xlators/mgmt/glusterd/src/glusterd-syncop.d \
./xlators/mgmt/glusterd/src/glusterd-utils.d \
./xlators/mgmt/glusterd/src/glusterd-volgen.d \
./xlators/mgmt/glusterd/src/glusterd-volume-ops.d \
./xlators/mgmt/glusterd/src/glusterd-volume-set.d \
./xlators/mgmt/glusterd/src/glusterd.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/mgmt/glusterd/src/%.o: ../xlators/mgmt/glusterd/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


