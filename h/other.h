/*
 * Copyright (c) 2026 Sam (sjbeaumont)
 * SPDX-License-Identifier: MIT
 * Distributed under the terms of the MIT License.
 */

#ifndef OTHER_H
#define OTHER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

extern char renameValue[4096]; // in kwic.c

static int mkdir_if_missing(const char *dir) {
    if (mkdir(dir, 0755) == 0) return 0;
    if (errno == EEXIST) return 0;
    return -1;
}

static void usage(void) {
    printf("Usage error.\n");
    exit(1);
}

int scan(const char *alias, const char *kwicdP) {  // -2 = file not found, -1 = alias not found
    FILE *kwicd;
    char line[4096];
    int ln = 1;

    kwicd = fopen(kwicdP, "r");
    if (!kwicd) return -2;

    while (fgets(line, sizeof(line), kwicd)) {
        line[strcspn(line, "\r\n")] = '\0';

        char *colon = strchr(line, ':');
        if (!colon) { ln++; continue; }

        *colon = '\0';
        char *key = line;
        char *val = colon + 1;

        snprintf(renameValue, sizeof(renameValue), val); // save in case of renaming

        if (strcmp(key, alias) != 0) { ln++; continue; }

        fclose(kwicd);
        return ln;
    }

    fclose(kwicd);
    return -1;
}

#endif