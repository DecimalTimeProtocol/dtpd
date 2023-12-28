//  Decimal Time Protocol Daemon (dtpd) v0.0.1
//  SPDX-FileCopyrightText: 2023 Julio Jimenez <julio@julioj.com>
//  SPDX-License-Identifier: Apache-2.0

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

int main() {
    puts("Decimal Time Protocol Daemon");
    printf("dtpd %s\n\n", VERSION);

    float decimalSeconds = 0;
    float decimalMinutes = 0;
    float decimalHours = 0;
    float decimalDays = 1;
    float decimalMonths = 1;
    float decimalYears = 1;

    for (;;) {
        if (decimalSeconds >= 99) {
        //     decimalSeconds = 0;
        //     decimalMinutes++;
        // } else {
        //     decimalSeconds++;
        // }
        // if (decimalMinutes >= 99) {
        //     decimalMinutes = 0;
        //     decimalHours++;
        // }
        // if (decimalHours >= 9) {
        //     decimalHours = 0;
        //     decimalDays++;
        // }
        // if (decimalDays >= 100) {
        //     decimalDays = 1;
        //     decimalMonths++;
        // }
        // if (decimalMonths >= 10) {
        //     decimalMonths = 1;
        //     decimalYears++;
        // }
    
        // printf("decimalSeconds:\t%f\n", decimalSeconds);
        // printf("decimalMinutes:\t%f\n", decimalMinutes);
        // printf("decimalHours:\t%f\n", decimalHours);
        // printf("decimalDays:\t%f\n", decimalDays);
        // printf("decimalMonths:\t%f\n", decimalMonths);
        // printf("decimalYears:\t%f\n\n", decimalYears);

        // printf("decimalEpoch:\t%lu\n\n", convertToDecimalSeconds(time(NULL)));

        // fflush(stdout);

        // if (nanosleep(&req, &rem) < 0) {
        //     perror("Nanosleep failed");
        //     return 1;
        // }
    }
    return 0;
}
