#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "hello.h"

int main(int argc, char *argv[]) {
    print_help();
    static struct option long_options[] = {
        {"write",   no_argument,       0, 'w'},
        {"read",    no_argument,       0, 'r'},
        {"append",  no_argument,       0, 'a'},
        {"close",   no_argument,       0, 'c'},
        {"text",    required_argument, 0, 't'},
        {"version", no_argument,       0, 'v'},
        {"help",    no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    char mode = 0; // 'w', 'r', 'a'
    char *text_to_write = NULL;
    bool should_close = false;

    opterr = 0;
    while ((opt = getopt_long(argc, argv, "+wract:vh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'v':
                printf("result version: %s\n", VERSION);
                return 0;
            case 'h':
                print_help();
                return 0;
            case 'w':
            case 'r':
            case 'a':
                mode = opt;
                break;
            case 't':
                text_to_write = optarg;
                break;
            case 'c':
                should_close = true;
                break;
            case '?':
                
                break;
        }
    }

    if (mode == 0) {
        fprintf(stderr, "Error: Operation mode not specified (-w, -r, -a). Use --help for reference.\n");
        return 1;
    }

    // Check for the filename (it must be located AFTER the options processed SO FAR)
    if (optind >= argc) {
        fprintf(stderr, "Error: Filename not specified.\n");
        return 1;
    }

    char *filename = argv[optind];
    optind++; // Shift the index to parse remaining options AFTER the filename

    // Second pass: read options placed AFTER the filename
    while ((opt = getopt_long(argc, argv, "ct:", long_options, NULL)) != -1) {
        switch (opt) {
            case 't':
                text_to_write = optarg;
                break;
            case 'c':
                should_close = true;
                break;
            default:
                break;
        }
    }

    // File operations logic
    FILE *file = NULL;

    if (mode == 'w') {
        file = fopen(filename, "w");
        if (!file) {
            perror("Error creating file");
            return 1;
        }
        printf("[Event] File '%s' successfully created.\n", filename);
        
        if (text_to_write) {
            fprintf(file, "%s\n", text_to_write);
            printf("[Write] Text written to file.\n");
        }
    } 
    else if (mode == 'a') {
        file = fopen(filename, "a");
        if (!file) {
            perror("Error opening file for appending");
            return 1;
        }
        printf("[Event] File '%s' opened for changes.\n", filename);
        
        if (text_to_write) {
            fprintf(file, "%s\n", text_to_write);
            printf("[Append] Text appended to the end of the file.\n");
        }
    } 
    else if (mode == 'r') {
        file = fopen(filename, "r");
        if (!file) {
            perror("Error reading file");
            return 1;
        }
        printf("[Read] File data '%s':\n---\n", filename);
        char ch;
        while ((ch = fgetc(file)) != EOF) {
            putchar(ch);
        }
        printf("\n---\n");
    }
    if (file) {
        fclose(file);
    }

    if (should_close) {
        printf("[Event] File '%s' successfully closed (-c).\n", filename);
    }

    return 0;
}
