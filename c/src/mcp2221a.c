#include "mcp2221a.h"

/*
     | 0x00 | 0x01 | 0x02 | 0x03 | 0x04 | 0x05 | 0x06 | 0x07
0x00 |
0x10 |
0x20 |
0x30 |
0x40 |
0x50 |
0x60 |
0x70 |
*/

void print_response(unsigned char *buf) {
  int32_t i, j;
  for(i = 0; i < 9; ++i) {
    for(j = 0; j < 9; ++j) {
      if (i == 0 && j == 0) { fprintf(stdout, "      "); }
      else if (i == 0) { fprintf(stdout, "| 0x0%u ", j - 1); } 
      else if (j == 0) { fprintf(stdout, " 0x%u0 ", i - 1); }
      else { fprintf(stdout, "| 0x%02x ", buf[(i - 1) * 8 + j - 1]); }
    }
    fputc('\n', stdout);
  }
}

hid_device *__restrict handle;

#define COMM(id, checks) \
  memset(buf, 0, 64); \
  buf[0] = id; \
  checks; \
  HIDCHECK(hid_write(handle, buf, 64)); \
  HIDCHECK(hid_read(handle, buf, 64));

void readsetparameters(uint8_t *buf, uint8_t cancelcomm, uint8_t speedcom, uint8_t speed) {
  COMM(0x10,
    if (cancelcomm) { buf[2] = 0x10; }
    if (speedcom) { buf[3] = 0x20; buf[4] = speed; })
}

void readflash(uint8_t *buf, uint8_t subc) { /// SUBC 0x00(Flash settings), 0x01(GP Settings), 0x02(USB Product descriptor), 0x04(String), 0x05(Serial nr)
  COMM(0xB0, 
      buf[1] = subc);
}

void writestring(uint8_t *buf, uint8_t md, wchar_t *str) { // md=0: manufacturer description; md=1: product descriptor string, md=2: Serial number descriptor string
  if (md > 2) { return; }
  COMM(0xB1,
      buf[1] = md + 2;
      uint32_t sl = wcslen(str);
      buf[2] = sl * 2 + 2;
      buf[3] = 0x03;
      int32_t i;
      for(i = 0; i < sl; ++i) {
        buf[4 + i * 2] = LB(str[i]);
        buf[5 + i * 2] = HB(str[i]);
      })
}

void pers(uint8_t *buf){ 
  writestring(buf, 0, L"Raraiku");
  writestring(buf, 1, L"日本語");
}

void writei2c(uint8_t *buf, uint32_t len, uint8_t addr, uint8_t *data) {
  //uint32_t cl = len;
  COMM(0x90,
      buf[1] = LB(len);
      buf[2] = HB(len);
      buf[3] = (addr << 1) + 0;
      memcpy(buf + 4, data, len))
}

void reset(uint8_t *buf) {
  COMM(0x70,
      buf[1] = 0xAB;
      buf[2] = 0xCD;
      buf[3] = 0xEF)
  exit(0);
}

void writechip(uint8_t *buf) {
  COMM(0xB1,
      buf[2] = 0b11111100 & 0xfc;
      buf[6] = 0x72;
      buf[8] = 0x32;
      buf[11] = 0x32)
}

void readchip(uint8_t *buf) { COMM(0xB0,); }

void setsram(uint8_t *buf) {
  COMM(0x60,
      //buf[11] = 0b10000000)
      buf[7] = 0xff;
      buf[8] = 0b00000111;
      buf[9] = 0b00000111;
      buf[10] = 0b00000111;
      buf[11] = 0b00000001)
}

void seti2csdiv(uint8_t *buf, uint8_t clkdiv) {
  COMM(0x10,
      buf[3] = 0x20;
      buf[4] = clkdiv)
}

void readparam(uint8_t *buf) { COMM(0x10,) }

void reseti2c(uint8_t *buf) { COMM(0x10, buf[2] = 0x10) }

void print_param(uint8_t *buf) {
  if (buf[0] != 0x10) { fprintf(stderr, "Incorrect command!\n"); return; }
  if (buf[1] != 0x00) { fprintf(stderr, "Command didn't complete!\n"); }
  fprintf(stdout, "Cancel transfer: %x\n", buf[2]);
  fprintf(stdout, "New speed %x %x\n", buf[3], buf[4]);
  fprintf(stdout, "I2C State machine %x\n", buf[8]);
  fprintf(stdout, "I2C speed %x\n", buf[15]);
  fprintf(stdout, "SCL %x SDA %x\n", buf[22], buf[23]);
}

// void writeflashchip(uint8_t *buf, uint8_t usbenum, 

void test() {
  HIDCHECK(hid_init());

  handle = hid_open(0x0072, 0x0032, NULL);
  if (!handle) { fprintf(stdout, "Could not open device!\n"); hid_exit(); exit(1); }
  /*
  wchar_t wch[255];
  HIDCHECK(hid_get_manufacturer_string(handle, wch, 255));
  fprintf(stdout, "Manufacturer string %ls\n", wch);
  HIDCHECK(hid_get_product_string(handle, wch, 255));
  fprintf(stdout, "Product string %ls\n", wch);
  */

  uint8_t buf[65];
  
  uint8_t cz = 3;
  switch (cz) {
    case 0:
      readparam(buf);
      print_param(buf);
      break;
    case 1:
      reseti2c(buf);
      print_param(buf);
      break;
    case 2:
      seti2csdiv(buf, 255);
      print_param(buf);
      break;
    case 3:
      uint8_t c[22] = {0};
      writei2c(buf, 20, 0xc2, c);
      while (1) {
        readparam(buf);
        print_param(buf);
      }
      break;
    case 4:
      setsram(buf);
      print_response(buf);
      break;
    case 20:
      reset(buf);
      exit(0);
  }

  /*
  struct timespec ts = {.tv_sec = 0, .tv_nsec = 800000000};
  nanosleep(&ts, NULL);
  */

  hid_close(handle);
  HIDCHECK(hid_exit());
}
