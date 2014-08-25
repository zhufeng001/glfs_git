################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rpc/rpc-lib/src/auth-glusterfs.c \
../rpc/rpc-lib/src/auth-null.c \
../rpc/rpc-lib/src/auth-unix.c \
../rpc/rpc-lib/src/rpc-clnt.c \
../rpc/rpc-lib/src/rpc-transport.c \
../rpc/rpc-lib/src/rpcsvc-auth.c \
../rpc/rpc-lib/src/rpcsvc.c \
../rpc/rpc-lib/src/xdr-rpc.c \
../rpc/rpc-lib/src/xdr-rpcclnt.c 

OBJS += \
./rpc/rpc-lib/src/auth-glusterfs.o \
./rpc/rpc-lib/src/auth-null.o \
./rpc/rpc-lib/src/auth-unix.o \
./rpc/rpc-lib/src/rpc-clnt.o \
./rpc/rpc-lib/src/rpc-transport.o \
./rpc/rpc-lib/src/rpcsvc-auth.o \
./rpc/rpc-lib/src/rpcsvc.o \
./rpc/rpc-lib/src/xdr-rpc.o \
./rpc/rpc-lib/src/xdr-rpcclnt.o 

C_DEPS += \
./rpc/rpc-lib/src/auth-glusterfs.d \
./rpc/rpc-lib/src/auth-null.d \
./rpc/rpc-lib/src/auth-unix.d \
./rpc/rpc-lib/src/rpc-clnt.d \
./rpc/rpc-lib/src/rpc-transport.d \
./rpc/rpc-lib/src/rpcsvc-auth.d \
./rpc/rpc-lib/src/rpcsvc.d \
./rpc/rpc-lib/src/xdr-rpc.d \
./rpc/rpc-lib/src/xdr-rpcclnt.d 


# Each subdirectory must supply rules for building sources it contributes
rpc/rpc-lib/src/%.o: ../rpc/rpc-lib/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


