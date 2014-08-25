################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../api/src/glfs-fops.c \
../api/src/glfs-handleops.c \
../api/src/glfs-master.c \
../api/src/glfs-mgmt.c \
../api/src/glfs-resolve.c \
../api/src/glfs.c 

OBJS += \
./api/src/glfs-fops.o \
./api/src/glfs-handleops.o \
./api/src/glfs-master.o \
./api/src/glfs-mgmt.o \
./api/src/glfs-resolve.o \
./api/src/glfs.o 

C_DEPS += \
./api/src/glfs-fops.d \
./api/src/glfs-handleops.d \
./api/src/glfs-master.d \
./api/src/glfs-mgmt.d \
./api/src/glfs-resolve.d \
./api/src/glfs.d 


# Each subdirectory must supply rules for building sources it contributes
api/src/%.o: ../api/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


