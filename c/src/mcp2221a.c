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
      }
      )
}

void writei2c(uint8_t *buf, uint32_t len, uint8_t addr, uint8_t *data) {
  uint32_t cl = len;
  COMM(0x90,
      buf[1] = LB(len);
      buf[2] = HB(len);
      buf[3] = (addr << 1) + 0;
      memcpy(buf + 4, data, len));
}

// void writeflashchip(uint8_t *buf, uint8_t usbenum, 

void test() {
  HIDCHECK(hid_init());
  wchar_t wch[255];

  handle = hid_open(0x4D8, 0x00DD, NULL);
  if (!handle) { fprintf(stdout, "Could not open device!\n"); hid_exit(); exit(1); }

  HIDCHECK(hid_get_manufacturer_string(handle, wch, 255));
  fprintf(stdout, "Manufacturer string %ls\n", wch);
  HIDCHECK(hid_get_product_string(handle, wch, 255));
  fprintf(stdout, "Product string %ls\n", wch);

  uint8_t buf[65];
  //readsetparameters(buf, 0, 0, 0);
  //readflash(buf, 0);
  //print_response(buf);
  //writestring(buf, 0, L"Raraiku");
  //writestring(buf, 1, L"日本語");
  uint8_t c[22] = {0};
  writei2c(buf, 20, 0xc2, c);
  print_response(buf);

  memset(buf, 0, sizeof(buf));


  hid_close(handle);
  HIDCHECK(hid_exit());
}
