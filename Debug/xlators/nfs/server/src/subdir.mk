################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../xlators/nfs/server/src/acl3.c \
../xlators/nfs/server/src/mount3.c \
../xlators/nfs/server/src/mount3udp_svc.c \
../xlators/nfs/server/src/nfs-common.c \
../xlators/nfs/server/src/nfs-fops.c \
../xlators/nfs/server/src/nfs-generics.c \
../xlators/nfs/server/src/nfs-inodes.c \
../xlators/nfs/server/src/nfs.c \
../xlators/nfs/server/src/nfs3-fh.c \
../xlators/nfs/server/src/nfs3-helpers.c \
../xlators/nfs/server/src/nfs3.c \
../xlators/nfs/server/src/nlm4.c \
../xlators/nfs/server/src/nlmcbk_svc.c 

OBJS += \
./xlators/nfs/server/src/acl3.o \
./xlators/nfs/server/src/mount3.o \
./xlators/nfs/server/src/mount3udp_svc.o \
./xlators/nfs/server/src/nfs-common.o \
./xlators/nfs/server/src/nfs-fops.o \
./xlators/nfs/server/src/nfs-generics.o \
./xlators/nfs/server/src/nfs-inodes.o \
./xlators/nfs/server/src/nfs.o \
./xlators/nfs/server/src/nfs3-fh.o \
./xlators/nfs/server/src/nfs3-helpers.o \
./xlators/nfs/server/src/nfs3.o \
./xlators/nfs/server/src/nlm4.o \
./xlators/nfs/server/src/nlmcbk_svc.o 

C_DEPS += \
./xlators/nfs/server/src/acl3.d \
./xlators/nfs/server/src/mount3.d \
./xlators/nfs/server/src/mount3udp_svc.d \
./xlators/nfs/server/src/nfs-common.d \
./xlators/nfs/server/src/nfs-fops.d \
./xlators/nfs/server/src/nfs-generics.d \
./xlators/nfs/server/src/nfs-inodes.d \
./xlators/nfs/server/src/nfs.d \
./xlators/nfs/server/src/nfs3-fh.d \
./xlators/nfs/server/src/nfs3-helpers.d \
./xlators/nfs/server/src/nfs3.d \
./xlators/nfs/server/src/nlm4.d \
./xlators/nfs/server/src/nlmcbk_svc.d 


# Each subdirectory must supply rules for building sources it contributes
xlators/nfs/server/src/%.o: ../xlators/nfs/server/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


