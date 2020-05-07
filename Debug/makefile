################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Body_sythesyser.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Body_sythesyser.list \

OBJCOPY_BIN += \
Body_sythesyser.bin \


# All Target
all: Body_sythesyser.elf secondary-outputs

# Tool invocations
Body_sythesyser.elf: $(OBJS) $(USER_OBJS) E:\UNI\DSP-Labor\Signal_Erzeugung\DSP-Labor\Body_Synth_\Body_sythesyser\STM32F746ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "Body_sythesyser.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"E:\UNI\DSP-Labor\Signal_Erzeugung\DSP-Labor\Body_Synth_\Body_sythesyser\STM32F746ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Body_sythesyser.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Body_sythesyser.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Body_sythesyser.list"
	@echo 'Finished building: $@'
	@echo ' '

Body_sythesyser.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Body_sythesyser.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
