#include <assert.h>
#include <stdio.h>
#include "utils.h"

int main() {
    puts("dtpd Unit Tests");

    // 001 - convertToDecimalSeconds
    unsigned long result = convertToDecimalSeconds(45);
    assert(result == 75);
    puts("PASS - 001 - convertToDecimalSeconds");
    
    return 0;
}