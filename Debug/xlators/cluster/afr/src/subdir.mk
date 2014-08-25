################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/cluster/afr/src/afr-common.c \
../xlators/cluster/afr/src/afr-dir-read.c \
../xlators/cluster/afr/src/afr-dir-write.c \
../xlators/cluster/afr/src/afr-inode-read.c \
../xlators/cluster/afr/src/afr-inode-write.c \
../xlators/cluster/afr/src/afr-lk-common.c \
../xlators/cluster/afr/src/afr-open.c \
../xlators/cluster/afr/src/afr-self-heal-algorithm.c \
../xlators/cluster/afr/src/afr-self-heal-common.c \
../xlators/cluster/afr/src/afr-self-heal-data.c \
../xlators/cluster/afr/src/afr-self-heal-entry.c \
../xlators/cluster/afr/src/afr-self-heal-metadata.c \
../xlators/cluster/afr/src/afr-self-heald.c \
../xlators/cluster/afr/src/afr-transaction.c \
../xlators/cluster/afr/src/afr.c \
../xlators/cluster/afr/src/pump.c 

OBJS += \
./xlators/cluster/afr/src/afr-common.o \
./xlators/cluster/afr/src/afr-dir-read.o \
./xlators/cluster/afr/src/afr-dir-write.o \
./xlators/cluster/afr/src/afr-inode-read.o \
./xlators/cluster/afr/src/afr-inode-write.o \
./xlators/cluster/afr/src/afr-lk-common.o \
./xlators/cluster/afr/src/afr-open.o \
./xlators/cluster/afr/src/afr-self-heal-algorithm.o \
./xlators/cluster/afr/src/afr-self-heal-common.o \
./xlators/cluster/afr/src/afr-self-heal-data.o \
./xlators/cluster/afr/src/afr-self-heal-entry.o \
./xlators/cluster/afr/src/afr-self-heal-metadata.o \
./xlators/cluster/afr/src/afr-self-heald.o \
./xlators/cluster/afr/src/afr-transaction.o \
./xlators/cluster/afr/src/afr.o \
./xlators/cluster/afr/src/pump.o 

C_DEPS += \
./xlators/cluster/afr/src/afr-common.d \
./xlators/cluster/afr/src/afr-dir-read.d \
./xlators/cluster/afr/src/afr-dir-write.d \
./xlators/cluster/afr/src/afr-inode-read.d \
./xlators/cluster/afr/src/afr-inode-write.d \
./xlators/cluster/afr/src/afr-lk-common.d \
./xlators/cluster/afr/src/afr-open.d \
./xlators/cluster/afr/src/afr-self-heal-algorithm.d \
./xlators/cluster/afr/src/afr-self-heal-common.d \
./xlators/cluster/afr/src/afr-self-heal-data.d \
./xlators/cluster/afr/src/afr-self-heal-entry.d \
./xlators/cluster/afr/src/afr-self-heal-metadata.d \
./xlators/cluster/afr/src/afr-self-heald.d \
./xlators/cluster/afr/src/afr-transaction.d \
./xlators/cluster/afr/src/afr.d \
./xlators/cluster/afr/src/pump.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/cluster/afr/src/%.o: ../xlators/cluster/afr/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


