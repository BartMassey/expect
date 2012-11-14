/*
 * Copyright © 2012 Bart Massey
 * [This program is licensed under the "MIT License"]
 * Please see the file COPYING in the source
 * distribution of this software for license terms.
 */

/* C expect/send interface */

extern int cexpect_verbose;
extern char cexpect_response[2048];
extern void csend(FILE *fp, char *cmd, ...);
extern int cexpects(FILE *fp, int codes[], int ncodes, char *msg);
extern void cexpect(FILE *fp, int code, char *msg);
