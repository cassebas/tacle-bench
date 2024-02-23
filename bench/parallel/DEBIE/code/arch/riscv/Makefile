CROSS_COMPILE = /opt/riscv32/bin/riscv32-unknown-elf-

CC=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump

# Set tpd to the Test Program Directory
TPD=../..
# Set hnd to the "harness" directory
HND=$(TPD)/harness

CFLAGS = -misa-spec=2.2 -march=rv32imac -mabi=ilp32

CCFLAGS = $(CFLAGS)
CCFLAGS += -mcmodel=medany -O2 -Wall -g
CCFLAGS += -fno-pic -fno-common -I. -I$(TPD) -I$(HND)
CCFLAGS += -DTRACE_HARNESS -DTRACE_TARGET

LFLAGS = -static -nostartfiles -T main.lds

BUILD_DIR = buildfiles
TARGET = $(BUILD_DIR)/debie1.elf

SRC = $(CURDIR)
OBJ = $(patsubst $(SRC)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC)/*.c))
SRC_TPD = $(TPD)
OBJ_TPD = $(patsubst $(SRC_TPD)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_TPD)/*.c))
SRC_HND = $(HND)
OBJ_HND = $(patsubst $(SRC_HND)/%.c,$(BUILD_DIR)/%.o,$(wildcard $(SRC_HND)/*.c))

all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(OBJ) $(OBJ_TPD) $(OBJ_HND)
	$(CC) -o $@ $^ $(LFLAGS) head.S
	$(OBJDUMP) -h -p $@

$(BUILD_DIR)/%.o: $(SRC)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ:.o=.d)

$(BUILD_DIR)/%.o: $(SRC_TPD)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ_TPD:.o=.d)

$(BUILD_DIR)/%.o: $(SRC_HND)/%.c
	$(CC) -c $(CCFLAGS) -o $@ $<
-include $(OBJ_HND:.o=.d)

# Create build dir if not already present
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*
