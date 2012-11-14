# "expect / send" in C
Copyright © 2012 Bart Massey

This work is licensed under the "MIT License".  Please see
the file COPYING in the source distribution of this work for
license terms.

This is an implementation of "expect / send" in C. There are
many such implementations; this one is neither particularly
nice nor particularly well-debugged nor particularly
well-supported. On the other hand, it is small and simple,
and has a liberal license.

The interface is as follows:

        extern void csend(FILE *fp, char *cmd, ...);

The `csend()` function is essentially a fancy `fprintf()`. It
adds a newline to its output and flushes it automatically.

The `csend()` function will echo its output to `stderr` if
the `cexpect_verbose` variable described below is set to
true.

        extern int cexpects(FILE *fp, int codes[], int ncodes, char *msg);

The `cexpects()` function reads a line from `fp`. It expects
the line to start with a 3-digit ASCII response code
followed by a space character. It parses that response code
and compares it with each code in the `codes` array. If any
code matches, `cexpects()` returns the code. Otherwise, it
prints an error message containing `msg` and exits the
program with status 1. (Yes, this is obnoxious behavior and
should probably be changed. Caveat emptor.)

The `cexpects()` function will echo its input to `stderr` if
the `cexpect_verbose` variable described below is set to
true.

        extern void cexpect(FILE *fp, int code, char *msg);

The `cexpect()` function is just a simplified interface to
`cexpects()` in the case that only one code is expected.

The `cexpect()` function will echo its input to `stderr` if
the `cexpect_verbose` variable described below is set to
true.

        extern char cexpect_response[];

This largeish static buffer (currently 2048 bytes, but check
its size with `sizeof(cexpect_response)`) will contain the
remainder of the last response processed by `cexpect()` or
`csend()` after the response code has been parsed and thrown
away. If the response contains information beyond the code,
this is where to find it.

        extern int cexpect_verbose;

The `cexpect_verbose` variable defaults to false
(zero). When set to true (non-zero) it causes `cexpects()`,
`cexpect()` and `csend()` to echo their work to `stderr`.
