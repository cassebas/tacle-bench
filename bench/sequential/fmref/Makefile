CROSS_COMPILE ?= ../../../../vivado-risc-v/workspace/gcc/riscv/bin/riscv32-unknown-elf-

CC=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

CFLAGS = -march=rv32imac -mabi=ilp32
ifneq ($(BENCHMARK_CONFIG),)
	CFLAGS += -DRISCV_CORE_CONFIG=\"$(BENCHMARK_CONFIG)\"
endif

CCFLAGS = $(CFLAGS)
CCFLAGS += -mcmodel=medany -O0 -Wall -g
CCFLAGS += -fno-pic -fno-common

LFLAGS = -static -nostartfiles -T main.lds

BUILD_DIR = buildfiles
TARGET = $(BUILD_DIR)/fmref.elf
DISASSEMBLY = $(BUILD_DIR)/fmref-disassembly.txt

SRC = $(CURDIR)
OBJ = $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC)/*.c))

all: $(BUILD_DIR) $(TARGET) $(DISASSEMBLY)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS) head.S
	$(OBJDUMP) -h -p $@

$(DISASSEMBLY): $(TARGET)
	$(OBJDUMP) -d -h -p $< > $@

$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ:.o=.d)

# Create build dir if not already present
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*
