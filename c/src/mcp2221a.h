#ifndef MCP2221A
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <hidapi.h>

// #define HIDCHECK(comm) { int32_t _kms = comm; if (_kms) { fprintf(stdout, "Hid error %s:%u[%ls]\n", __FILE__, __LINE__, hid_error(NULL)); hid_exit(); exit(1); } }
#define HIDCHECK(comm) { int32_t _kms = comm; if (_kms == -1) { fprintf(stdout, "Hid error {%m} %s:%u[%ls]\n", __FILE__, __LINE__, hid_error(NULL)); exit(1); } }

#define LB(a) ((a)&0x00FF)
#define HB(a) (((a)&0xFF)>>8)

void test();

#endif
#define MCP2221A
