#include <stdio.h>
#include <stdlib.h>
#define BUFSIZE 16

int buffer[BUFSIZE];
int print_buffer[64];
FILE *f;

int main(int argc, char *argv[])
{
    int ch;
    int pos;


    if (argc == 2) {
        f = open(argv[1]);
    }
    else {
        f = stdin;
    }

    while ch != EOF {
        pos = ftell(f);
        int i;
        for (i = 0; (ch = getchar()) != EOF && i < BUFSIZE - 1; i++) {
            buffer[i] = ch;
        }
        buffer[i] = NULL;


