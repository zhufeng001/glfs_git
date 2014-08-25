################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../rpc/rpc-transport/rdma/src/name.c \
../rpc/rpc-transport/rdma/src/rdma.c 

OBJS += \
./rpc/rpc-transport/rdma/src/name.o \
./rpc/rpc-transport/rdma/src/rdma.o 

C_DEPS += \
./rpc/rpc-transport/rdma/src/name.d \
./rpc/rpc-transport/rdma/src/rdma.d 


# Each subdirectory must supply rules for building sources it contributes
rpc/rpc-transport/rdma/src/%.o: ../rpc/rpc-transport/rdma/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


