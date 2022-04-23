include makefile_cfg.mk

OBJECTS_PATH 	= $(BUILD_DIR)/objects

OBJECTS 			= $(subst .c,.o,$(notdir $(SRC_C)))
VPATH				= $(dir $(SRC_C)) $(OBJECTS_PATH)
BUILD_OBJ 		= $(addprefix $(OBJECTS_PATH)/,$(OBJECTS))
EXE_FILE			= $(PROJECT_NAME).elf

# Create build directories
$(shell mkdir -p $(OBJECTS_PATH))

.PHONY: all clean

# all involve creating directory for object files then build program
all: $(EXE_FILE)

# .elf file must be crated in location of the makefile for Atmel studio debugging
$(EXE_FILE): $(BUILD_OBJ)
	@echo "	Linking $(PROJECT_NAME).elf"
	$(LD) $(LD_FLAGS) -o $(PROJECT_NAME).elf $(BUILD_OBJ)
	@echo ""
	@echo "	Create binary file $(PROJECT_NAME).$(HEX_EXTENSION)"
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(PROJECT_NAME).elf $(PROJECT_NAME).$(HEX_EXTENSION)
	@echo ""
	@echo "	Build information"
	@$(INFO) $(PROJECT_NAME).elf

# Compile source files
$(OBJECTS_PATH)/%.o: %.c
	@echo "	Compiling $(notdir $<)"
	    $(CC) $(COMPILER_FLAGS) $< -o $@
	@echo ""

# Remove directory with object files, elf file and other build artifacts
clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r $(PROJECT_NAME).elf $(BUILD_ARTIFACTS)
