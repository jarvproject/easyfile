#include <stdio.h>
void print_help() {
    printf("--- EASYFILE ---");
    printf("Usage: easyfile [OPTIONS] [FILE NAME] [OPTIONS 2]\n\n");
    printf("OPTIONS:\n");
    printf("  -w, --write        Write or rewrite file\n");
    printf("  -r, --read         Read and return file\n");
    printf("  -a, --append       Append to file\n\n");
    printf("OPTIONS 2:\n");
    printf("  -c, --close        Close file");
    printf("Other:\n");
    printf("      --help\n");
    printf("         display this help and exit\n");
    printf("      --version\n");
    printf("         output version information and exit\n");
}
#define VERSION "EasyFile 0.10"