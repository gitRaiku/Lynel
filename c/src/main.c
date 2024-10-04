#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#include "mcp2221a.h"

int main(void) {
  setlocale(LC_ALL, "");
  test();
  
  return 0;
}
