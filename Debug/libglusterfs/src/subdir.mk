################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libglusterfs/src/call-stub.c \
../libglusterfs/src/checksum.c \
../libglusterfs/src/circ-buff.c \
../libglusterfs/src/common-utils.c \
../libglusterfs/src/compat-errno.c \
../libglusterfs/src/compat.c \
../libglusterfs/src/ctx.c \
../libglusterfs/src/daemon.c \
../libglusterfs/src/defaults.c \
../libglusterfs/src/dict.c \
../libglusterfs/src/event-epoll.c \
../libglusterfs/src/event-history.c \
../libglusterfs/src/event-poll.c \
../libglusterfs/src/event.c \
../libglusterfs/src/fd-lk.c \
../libglusterfs/src/fd.c \
../libglusterfs/src/gf-dirent.c \
../libglusterfs/src/gidcache.c \
../libglusterfs/src/globals.c \
../libglusterfs/src/graph-print.c \
../libglusterfs/src/graph.c \
../libglusterfs/src/hashfn.c \
../libglusterfs/src/inode.c \
../libglusterfs/src/iobuf.c \
../libglusterfs/src/latency.c \
../libglusterfs/src/logging.c \
../libglusterfs/src/mem-pool.c \
../libglusterfs/src/options.c \
../libglusterfs/src/rbthash.c \
../libglusterfs/src/run.c \
../libglusterfs/src/stack.c \
../libglusterfs/src/statedump.c \
../libglusterfs/src/store.c \
../libglusterfs/src/syncop.c \
../libglusterfs/src/syscall.c \
../libglusterfs/src/timer.c \
../libglusterfs/src/trie.c \
../libglusterfs/src/xlator.c 

OBJS += \
./libglusterfs/src/call-stub.o \
./libglusterfs/src/checksum.o \
./libglusterfs/src/circ-buff.o \
./libglusterfs/src/common-utils.o \
./libglusterfs/src/compat-errno.o \
./libglusterfs/src/compat.o \
./libglusterfs/src/ctx.o \
./libglusterfs/src/daemon.o \
./libglusterfs/src/defaults.o \
./libglusterfs/src/dict.o \
./libglusterfs/src/event-epoll.o \
./libglusterfs/src/event-history.o \
./libglusterfs/src/event-poll.o \
./libglusterfs/src/event.o \
./libglusterfs/src/fd-lk.o \
./libglusterfs/src/fd.o \
./libglusterfs/src/gf-dirent.o \
./libglusterfs/src/gidcache.o \
./libglusterfs/src/globals.o \
./libglusterfs/src/graph-print.o \
./libglusterfs/src/graph.o \
./libglusterfs/src/hashfn.o \
./libglusterfs/src/inode.o \
./libglusterfs/src/iobuf.o \
./libglusterfs/src/latency.o \
./libglusterfs/src/logging.o \
./libglusterfs/src/mem-pool.o \
./libglusterfs/src/options.o \
./libglusterfs/src/rbthash.o \
./libglusterfs/src/run.o \
./libglusterfs/src/stack.o \
./libglusterfs/src/statedump.o \
./libglusterfs/src/store.o \
./libglusterfs/src/syncop.o \
./libglusterfs/src/syscall.o \
./libglusterfs/src/timer.o \
./libglusterfs/src/trie.o \
./libglusterfs/src/xlator.o 

C_DEPS += \
./libglusterfs/src/call-stub.d \
./libglusterfs/src/checksum.d \
./libglusterfs/src/circ-buff.d \
./libglusterfs/src/common-utils.d \
./libglusterfs/src/compat-errno.d \
./libglusterfs/src/compat.d \
./libglusterfs/src/ctx.d \
./libglusterfs/src/daemon.d \
./libglusterfs/src/defaults.d \
./libglusterfs/src/dict.d \
./libglusterfs/src/event-epoll.d \
./libglusterfs/src/event-history.d \
./libglusterfs/src/event-poll.d \
./libglusterfs/src/event.d \
./libglusterfs/src/fd-lk.d \
./libglusterfs/src/fd.d \
./libglusterfs/src/gf-dirent.d \
./libglusterfs/src/gidcache.d \
./libglusterfs/src/globals.d \
./libglusterfs/src/graph-print.d \
./libglusterfs/src/graph.d \
./libglusterfs/src/hashfn.d \
./libglusterfs/src/inode.d \
./libglusterfs/src/iobuf.d \
./libglusterfs/src/latency.d \
./libglusterfs/src/logging.d \
./libglusterfs/src/mem-pool.d \
./libglusterfs/src/options.d \
./libglusterfs/src/rbthash.d \
./libglusterfs/src/run.d \
./libglusterfs/src/stack.d \
./libglusterfs/src/statedump.d \
./libglusterfs/src/store.d \
./libglusterfs/src/syncop.d \
./libglusterfs/src/syscall.d \
./libglusterfs/src/timer.d \
./libglusterfs/src/trie.d \
./libglusterfs/src/xlator.d 


# Each subdirectory must supply rules for building sources it contributes
libglusterfs/src/%.o: ../libglusterfs/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


