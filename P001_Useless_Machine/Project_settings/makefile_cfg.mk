include makefile_scope.mk

# Project depedants
BUILD_DIR 		:= Build
# INFO: Project name should corespond to Atmel Studio project name to allow debugging
PROJECT_NAME	:= P001_Useless_Machine

# Include flags
INC_FLAGS 		:= $(addprefix -I,$(HEADERS))
# Device information for compiler
DEVICE_FLAG		:= -mmcu=atmega328p
COMPILER_FLAGS	:= $(INC_FLAGS) $(DEVICE_FLAG) -O0 -c -fshort-enums -g2 -Wall -std=gnu99
LD_FLAGS		:= $(DEVICE_FLAG) -Wl,-Map=$(PROJECT_NAME).map -T$(LD_SCRIPT)
HEX_EXTENSION 	:= srec
OBJCOPY_FLAGS	:= -O $(HEX_EXTENSION) -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures

# Build artifacts to be removed using "make clean"
BUILD_ARTIFACTS	:= $(PROJECT_NAME).map $(PROJECT_NAME).$(HEX_EXTENSION)

LD				:= $(AVR_GCC_PATH)/avr-gcc.exe
CC				:= $(AVR_GCC_PATH)/avr-gcc.exe
INFO			:= $(AVR_GCC_PATH)/avr-size.exe
OBJCOPY			:= $(AVR_GCC_PATH)/avr-objcopy.exe