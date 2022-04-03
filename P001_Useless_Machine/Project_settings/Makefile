include makefile_cfg.mk

OBJECTS := $(subst .c,.o,$(notdir $(SRC_C)))
VPATH	= $(dir $(SRC_C)) $(BUILD_DIR)/objects
BUILD_OBJ = $(addprefix $(BUILD_DIR)/objects/,$(OBJECTS))

# all involve creating directory for object files then build program
all: build_dir exe

# .elf file must be crated in location of the makefile for Atmel studio debugging
exe: $(OBJECTS)
	@echo "	Linking $(PROJECT_NAME).elf"
	$(LD) $(LD_FLAGS) -o $(PROJECT_NAME).elf $(BUILD_OBJ)
	@echo ""
	@echo "	Create binary file $(PROJECT_NAME).$(HEX_EXTENSION)"
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(PROJECT_NAME).elf $(PROJECT_NAME).$(HEX_EXTENSION)
	@echo ""
	@echo "	Build information"
	$(INFO) $(PROJECT_NAME).elf

build_dir:
	@mkdir -p $(BUILD_DIR)/objects

# Compile all files coresponding to $(OBJECTS)
%.o: %.c
	@echo "	Compiling $<"
	    $(CC) $(COMPILER_FLAGS) $< -o $(BUILD_DIR)/objects/$@
	@echo ""
	@echo ""

# Remove directory with object files, elf file and other build artifacts
clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r $(PROJECT_NAME).elf $(BUILD_ARTIFACTS)
