#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define BUFSIZE 16

int buffer[BUFSIZE];
char print_buffer[65];
FILE *f;

int main(int argc, char *argv[])
{
    int ch;
    int pos;
    int offset;


    if (argc == 2) {
        printf("opening %s \n", argv[1]);
        f = fopen(argv[1], "r");
    }
    else {
        f = stdin;
    }

    while (ch != EOF) {
        // initialize input buffer
        for (int i = 0; i < BUFSIZE; i++) {
            buffer[i] = ' ';
        }

        // print buffer offset
        offset = 0;

        pos = ftell(f);
        offset += sprintf(print_buffer, "%06X ", pos);
        
        int i;
        for (i = 0; (ch = fgetc(f)) != EOF && i < BUFSIZE; i++) {
            buffer[i] = ch;
        }
        if (ch != EOF)
            ungetc(ch, f);

        // append formatted chars to print buffer
        for (int i = 0; i < BUFSIZE; i++) {
            if ((i + 1) % 4 == 0) {
                offset += sprintf(print_buffer + offset, "%02X ", buffer[i]);
            }
            else {
                offset += sprintf(print_buffer + offset, "%02X", buffer[i]);
            }
        }

        offset += sprintf(print_buffer + offset, "*");

        for (int i = 0; i < BUFSIZE; i++) {
            if (!isprint(buffer[i])) {
                offset += sprintf(print_buffer + offset, ".");
            }
            else {
                offset += sprintf(print_buffer + offset, "%c", buffer[i]);
            }
        }

        offset += sprintf(print_buffer + offset, "*");

        // print final string
        printf("%s\n", print_buffer);
    }

    return 0;
}
