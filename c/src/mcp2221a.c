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
      if (i == 0 && j == 0) { fprintf(stdout, "     "); }
      else if (i == 0) { fprintf(stdout, " 0x0%u ", j); } 
      else if (j == 0) { fprintf(stdout, " 0x%u0 ", i); }
      else { fprintf(stdout, "| 0x%x ", buf[i - 1 * 8 + j - 1]); }
    }
    fputc('\n', stdout);
  }
  fprintf(stdout, "0x%X ", buf[i]);
}

void test() {
  HIDCHECK(hid_init());
  hid_device *__restrict handle;

  wchar_t wch[255];

  handle = hid_open(0x4D8, 0x00DD, NULL);
  if (!handle) { fprintf(stdout, "Could not open device!\n"); hid_exit(); exit(1); }

  HIDCHECK(hid_get_manufacturer_string(handle, wch, 255));
  fprintf(stdout, "Manufacturer string %ls\n", wch);
  HIDCHECK(hid_get_product_string(handle, wch, 255));
  fprintf(stdout, "Product string %ls\n", wch);
  HIDCHECK(hid_get_serial_number_string(handle, wch, 255));
  fprintf(stdout, "Serial number %d %ls\n", wch[0], wch);
  HIDCHECK(hid_get_indexed_string(handle, 1, wch, 255));
  fprintf(stdout, "Indexed string 1 %ls\n", wch);

  unsigned char buf[64];
  buf[0] = 0x10;
  HIDCHECK(hid_write(handle, buf, 64));
  HIDCHECK(hid_read(handle, buf, 64));
  print_response(buf);

  hid_close(handle);
  HIDCHECK(hid_exit());
}
