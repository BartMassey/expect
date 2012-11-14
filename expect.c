/*
 * Copyright © 2012 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file COPYING in the source
 * distribution of this software for license terms.
 */

/* C expect/send code */

#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "expect.h"

int cexpect_verbose = 0;

char cexpect_response[2048];

void csend(FILE *fp, char *cmd, ...) {
    va_list ap;
    va_start(ap, cmd);
    if (cexpect_verbose) {
        vfprintf(stderr, cmd, ap);
        va_end(ap);
        fprintf(stderr, "\n");
        va_start(ap, cmd);
    }
    vfprintf(fp, cmd, ap);
    va_end(ap);
    fprintf(fp, "\r\n");
    fflush(fp);
}

int cexpects(FILE *fp, int codes[], int ncodes, char *msg) {
    int rcode;
    int n = fscanf(fp, "%03d ", &rcode);
    if (n != 1) {
        fprintf(stderr, "expected code but got something else\n");
        exit(1);
    }
    if (cexpect_verbose)
        fprintf(stderr, "%d ", rcode);
    int i = 0;
    for (; i < ncodes; i++)
        if (codes[i] == rcode)
            break;
    if (i >= ncodes) {
        if (ncodes == 1)
            fprintf(stderr, "expected code %d but got %d for %s\n",
                    codes[0], rcode, msg);
        else
            fprintf(stderr, "unexpected code %d for %s\n", rcode, msg);
        exit(1);
    }
    char *r = fgets(cexpect_response, sizeof(cexpect_response), fp);
    assert(r);
    int nr = strlen(cexpect_response);
    assert(nr < sizeof(cexpect_response) - 1);
    assert(cexpect_response[nr - 1] == '\n');
    cexpect_response[nr - 1] = '\0';
    if (nr >= 2 && cexpect_response[nr - 2] == '\r')
        cexpect_response[nr - 2] = '\0';
    if (cexpect_verbose)
        fprintf(stderr, "%s\n", cexpect_response);
    return rcode;
}

void cexpect(FILE *fp, int code, char *msg) {
    int codes[1];
    codes[0] = code;
    (void) cexpects(fp, codes, 1, msg);
}
