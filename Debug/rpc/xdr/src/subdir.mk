################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rpc/xdr/src/acl3-xdr.c \
../rpc/xdr/src/cli1-xdr.c \
../rpc/xdr/src/glusterd1-xdr.c \
../rpc/xdr/src/glusterfs3-xdr.c \
../rpc/xdr/src/msg-nfs3.c \
../rpc/xdr/src/nlm4-xdr.c \
../rpc/xdr/src/nlmcbk-xdr.c \
../rpc/xdr/src/nsm-xdr.c \
../rpc/xdr/src/portmap-xdr.c \
../rpc/xdr/src/rpc-common-xdr.c \
../rpc/xdr/src/xdr-generic.c \
../rpc/xdr/src/xdr-nfs3.c 

OBJS += \
./rpc/xdr/src/acl3-xdr.o \
./rpc/xdr/src/cli1-xdr.o \
./rpc/xdr/src/glusterd1-xdr.o \
./rpc/xdr/src/glusterfs3-xdr.o \
./rpc/xdr/src/msg-nfs3.o \
./rpc/xdr/src/nlm4-xdr.o \
./rpc/xdr/src/nlmcbk-xdr.o \
./rpc/xdr/src/nsm-xdr.o \
./rpc/xdr/src/portmap-xdr.o \
./rpc/xdr/src/rpc-common-xdr.o \
./rpc/xdr/src/xdr-generic.o \
./rpc/xdr/src/xdr-nfs3.o 

C_DEPS += \
./rpc/xdr/src/acl3-xdr.d \
./rpc/xdr/src/cli1-xdr.d \
./rpc/xdr/src/glusterd1-xdr.d \
./rpc/xdr/src/glusterfs3-xdr.d \
./rpc/xdr/src/msg-nfs3.d \
./rpc/xdr/src/nlm4-xdr.d \
./rpc/xdr/src/nlmcbk-xdr.d \
./rpc/xdr/src/nsm-xdr.d \
./rpc/xdr/src/portmap-xdr.d \
./rpc/xdr/src/rpc-common-xdr.d \
./rpc/xdr/src/xdr-generic.d \
./rpc/xdr/src/xdr-nfs3.d 


# Each subdirectory must supply rules for building sources it contributes
rpc/xdr/src/%.o: ../rpc/xdr/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


