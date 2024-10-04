#ifndef MCP2221A
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include <hidapi.h>

#define HIDCHECK(comm) { int32_t _kms = comm; if (_kms) { fprintf(stdout, "Hid error %s:%u[%ls]\n", __FILE__, __LINE__, hid_error(NULL)); hid_exit(); exit(1); } }

void test();

#endif
#define MCP2221A
