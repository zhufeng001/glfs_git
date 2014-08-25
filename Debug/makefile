################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include xlators/system/posix-acl/src/subdir.mk
-include xlators/storage/posix/src/subdir.mk
-include xlators/storage/bd_map/src/subdir.mk
-include xlators/protocol/server/src/subdir.mk
-include xlators/protocol/client/src/subdir.mk
-include xlators/protocol/auth/login/src/subdir.mk
-include xlators/protocol/auth/addr/src/subdir.mk
-include xlators/performance/write-behind/src/subdir.mk
-include xlators/performance/symlink-cache/src/subdir.mk
-include xlators/performance/read-ahead/src/subdir.mk
-include xlators/performance/quick-read/src/subdir.mk
-include xlators/performance/open-behind/src/subdir.mk
-include xlators/performance/md-cache/src/subdir.mk
-include xlators/performance/io-threads/src/subdir.mk
-include xlators/performance/io-cache/src/subdir.mk
-include xlators/nfs/server/src/subdir.mk
-include xlators/mount/fuse/src/subdir.mk
-include xlators/mgmt/glusterd/src/subdir.mk
-include xlators/lib/src/subdir.mk
-include xlators/features/read-only/src/subdir.mk
-include xlators/features/quota/src/subdir.mk
-include xlators/features/quiesce/src/subdir.mk
-include xlators/features/marker/utils/src/subdir.mk
-include xlators/features/marker/src/subdir.mk
-include xlators/features/mac-compat/src/subdir.mk
-include xlators/features/locks/src/subdir.mk
-include xlators/features/index/src/subdir.mk
-include xlators/encryption/rot-13/src/subdir.mk
-include xlators/debug/trace/src/subdir.mk
-include xlators/debug/io-stats/src/subdir.mk
-include xlators/debug/error-gen/src/subdir.mk
-include xlators/cluster/stripe/src/subdir.mk
-include xlators/cluster/dht/src/subdir.mk
-include xlators/cluster/afr/src/subdir.mk
-include rpc/xdr/src/subdir.mk
-include rpc/rpc-transport/socket/src/subdir.mk
-include rpc/rpc-transport/rdma/src/subdir.mk
-include rpc/rpc-lib/src/subdir.mk
-include libglusterfs/src/subdir.mk
-include glusterfsd/src/subdir.mk
-include extras/benchmarking/subdir.mk
-include contrib/uuid/subdir.mk
-include contrib/stdlib/subdir.mk
-include contrib/rbtree/subdir.mk
-include contrib/macfuse/subdir.mk
-include contrib/libgen/subdir.mk
-include contrib/fuse-util/subdir.mk
-include contrib/fuse-lib/subdir.mk
-include cli/src/subdir.mk
-include argp-standalone/subdir.mk
-include api/src/subdir.mk
-include api/examples/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: glusterfs

# Tool invocations
glusterfs: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o"glusterfs" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) glusterfs
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
