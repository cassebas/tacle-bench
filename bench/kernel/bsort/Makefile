CROSS_COMPILE ?= ../../../../vivado-risc-v/workspace/gcc/riscv/bin/riscv32-unknown-elf-

CC=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

CFLAGS = -march=rv32imac -mabi=ilp32
CFLAGS += -O0

ifneq ($(BENCHMARK_CONFIG),)
	CFLAGS += -DRISCV_CORE_CONFIG=\"$(BENCHMARK_CONFIG)\"
endif

# Maybe enable measurements with the mcyle instruction
ifneq ($(EXP_USE_MCYCLE),)
	CFLAGS += -DEXP_USE_MCYCLE
endif

CCFLAGS = $(CFLAGS)
CCFLAGS += -mcmodel=medany -Wall
CCFLAGS += -fno-pic -fno-common

LFLAGS = -static -nostartfiles -T main.lds

BUILD_DIR = buildfiles

BENCH = $(shell basename $(CURDIR))
TARGET_ELF = $(BUILD_DIR)/$(BENCH).elf
TARGET_COE = $(BUILD_DIR)/$(BENCH).coe
DISASSEMBLY = $(BUILD_DIR)/$(BENCH)-disassembly.txt

BIN2COE     = binary2coefficient
BIN2COE_SRC = $(BIN2COE).c
BIN2COE_BIN = $(BUILD_DIR)/$(BIN2COE)

SRC = $(CURDIR)
OBJ = buildfiles/$(BENCH).o buildfiles/kprintf.o

all: $(BUILD_DIR) $(TARGET_ELF) $(TARGET_COE) $(DISASSEMBLY)

$(TARGET_ELF): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) head.S
	$(OBJDUMP) -h -p $@

$(TARGET_COE): $(TARGET_ELF) $(BIN2COE_BIN)
	./$(BIN2COE_BIN) $< $@

$(BIN2COE_BIN):
	gcc -o $@ $(BIN2COE_SRC)

$(DISASSEMBLY): $(TARGET_ELF)
	$(OBJDUMP) -d -h -p $< > $@

$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ:.o=.d)

# Create build dir if not already present
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*
