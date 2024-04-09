CROSS_COMPILE = ../../../../vivado-risc-v/workspace/gcc/riscv/bin/riscv32-unknown-elf-

CC=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

CFLAGS = -march=rv32imac -mabi=ilp32
ifneq ($(BENCHMARK_CONFIG),)
	CFLAGS += -DRISCV_CORE_CONFIG=\"$(BENCHMARK_CONFIG)\"
endif

CCFLAGS = $(CFLAGS)
CCFLAGS += -mcmodel=medany -O2 -Wall -g -MD
CCFLAGS += -fno-pic -fno-common

LFLAGS = -static -nostartfiles -T main.lds

BUILD_DIR = buildfiles
TARGET = $(BUILD_DIR)/ndes.elf

SRC = $(CURDIR)
OBJ = $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC)/*.c))
SRC_SYNTHETIC = $(SRC)/../../../synthetic_bench
OBJ_SYNTHETIC = $(patsubst $(SRC_SYNTHETIC)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_SYNTHETIC)/*.c))

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ) $(OBJ_SYNTHETIC)
	$(CC) -o $@ $^ $(LFLAGS) head.S
	$(OBJDUMP) -h -p $@

$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ:.o=.d)

$(BUILD_DIR)/%.o: $(SRC_SYNTHETIC)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ_SYNTHETIC:.o=.d)


# Create build dir if not already present
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*
