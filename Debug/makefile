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
Body-Synthesizer_STM32_F746ZG.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Body-Synthesizer_STM32_F746ZG.list \

OBJCOPY_BIN += \
Body-Synthesizer_STM32_F746ZG.bin \


# All Target
all: Body-Synthesizer_STM32_F746ZG.elf secondary-outputs

# Tool invocations
Body-Synthesizer_STM32_F746ZG.elf: $(OBJS) $(USER_OBJS) C:\Users\Marc\ Bielen\Documents\Studium\Master\ TU\ Berlin\6.\ Semester\Body-Synthesizer_STM32_F746ZG\STM32F746ZGTX_FLASH.ld
	arm-none-eabi-gcc -o "Body-Synthesizer_STM32_F746ZG.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\Marc Bielen\Documents\Studium\Master TU Berlin\6. Semester\Body-Synthesizer_STM32_F746ZG\STM32F746ZGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Body-Synthesizer_STM32_F746ZG.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Body-Synthesizer_STM32_F746ZG.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Body-Synthesizer_STM32_F746ZG.list"
	@echo 'Finished building: $@'
	@echo ' '

Body-Synthesizer_STM32_F746ZG.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Body-Synthesizer_STM32_F746ZG.bin"
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
