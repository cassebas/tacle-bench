#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void read_elf(const char *filename)
{
  FILE *fp;
  char buffer[8];
  size_t nread;

  if ((fp = fopen(filename, "rb")) == NULL) {
    printf("Error opening input file!\n");
    exit(EXIT_FAILURE);
  }

  uint16_t addr = 0;
  uint16_t addr64;
  while ((nread = fread(&buffer, sizeof(buffer), 1, fp)) > 0) {
    addr64 = addr - (addr % 64);
    printf("0x%08x ", addr64);
    printf("0x");
    for (int i=7; i>=0; i--) {
      printf("%02x", (uint8_t) buffer[i]);
    }
    printf("\n");
    addr += 8;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 2) {
    // Incorrect number of arguments
    printf("Usage: %s <elf filename>\n", argv[0]);
    printf("  where <elf filename> is the file you want to convert.\n");
  } else {
    read_elf(argv[1]);
  }
}
