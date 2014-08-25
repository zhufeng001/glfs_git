################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../contrib/uuid/clear.c \
../contrib/uuid/compare.c \
../contrib/uuid/copy.c \
../contrib/uuid/gen_uuid.c \
../contrib/uuid/isnull.c \
../contrib/uuid/pack.c \
../contrib/uuid/parse.c \
../contrib/uuid/unpack.c \
../contrib/uuid/unparse.c \
../contrib/uuid/uuid_time.c 

OBJS += \
./contrib/uuid/clear.o \
./contrib/uuid/compare.o \
./contrib/uuid/copy.o \
./contrib/uuid/gen_uuid.o \
./contrib/uuid/isnull.o \
./contrib/uuid/pack.o \
./contrib/uuid/parse.o \
./contrib/uuid/unpack.o \
./contrib/uuid/unparse.o \
./contrib/uuid/uuid_time.o 

C_DEPS += \
./contrib/uuid/clear.d \
./contrib/uuid/compare.d \
./contrib/uuid/copy.d \
./contrib/uuid/gen_uuid.d \
./contrib/uuid/isnull.d \
./contrib/uuid/pack.d \
./contrib/uuid/parse.d \
./contrib/uuid/unpack.d \
./contrib/uuid/unparse.d \
./contrib/uuid/uuid_time.d 


# Each subdirectory must supply rules for building sources it contributes
contrib/uuid/%.o: ../contrib/uuid/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


