################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/cluster/dht/src/dht-common.c \
../xlators/cluster/dht/src/dht-diskusage.c \
../xlators/cluster/dht/src/dht-hashfn.c \
../xlators/cluster/dht/src/dht-helper.c \
../xlators/cluster/dht/src/dht-inode-read.c \
../xlators/cluster/dht/src/dht-inode-write.c \
../xlators/cluster/dht/src/dht-layout.c \
../xlators/cluster/dht/src/dht-linkfile.c \
../xlators/cluster/dht/src/dht-rebalance.c \
../xlators/cluster/dht/src/dht-rename.c \
../xlators/cluster/dht/src/dht-selfheal.c \
../xlators/cluster/dht/src/dht.c \
../xlators/cluster/dht/src/nufa.c \
../xlators/cluster/dht/src/switch.c 

OBJS += \
./xlators/cluster/dht/src/dht-common.o \
./xlators/cluster/dht/src/dht-diskusage.o \
./xlators/cluster/dht/src/dht-hashfn.o \
./xlators/cluster/dht/src/dht-helper.o \
./xlators/cluster/dht/src/dht-inode-read.o \
./xlators/cluster/dht/src/dht-inode-write.o \
./xlators/cluster/dht/src/dht-layout.o \
./xlators/cluster/dht/src/dht-linkfile.o \
./xlators/cluster/dht/src/dht-rebalance.o \
./xlators/cluster/dht/src/dht-rename.o \
./xlators/cluster/dht/src/dht-selfheal.o \
./xlators/cluster/dht/src/dht.o \
./xlators/cluster/dht/src/nufa.o \
./xlators/cluster/dht/src/switch.o 

C_DEPS += \
./xlators/cluster/dht/src/dht-common.d \
./xlators/cluster/dht/src/dht-diskusage.d \
./xlators/cluster/dht/src/dht-hashfn.d \
./xlators/cluster/dht/src/dht-helper.d \
./xlators/cluster/dht/src/dht-inode-read.d \
./xlators/cluster/dht/src/dht-inode-write.d \
./xlators/cluster/dht/src/dht-layout.d \
./xlators/cluster/dht/src/dht-linkfile.d \
./xlators/cluster/dht/src/dht-rebalance.d \
./xlators/cluster/dht/src/dht-rename.d \
./xlators/cluster/dht/src/dht-selfheal.d \
./xlators/cluster/dht/src/dht.d \
./xlators/cluster/dht/src/nufa.d \
./xlators/cluster/dht/src/switch.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/cluster/dht/src/%.o: ../xlators/cluster/dht/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


