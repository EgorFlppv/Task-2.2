/*
main.c - точка входа программы hexdump.
ФИО: Филиппов Егор Ильич
Группа: МК-102
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hexdump_lib.h"

int main(int argc, char* argv[]) {
    DumpOptions opts = {
        .input_file = NULL,
        .input_dir = NULL,
        .format_str = NULL,
        .offset = 0,
        .size = 0,
        .chunk_size = 1,
        .chunks_per_line = 16
    };

    int opt;
    while ((opt = getopt(argc, argv, "i:o:l:g:n:d:f:")) != -1) {
        switch (opt) {
        case 'i': opts.input_file = optarg; break;
        case 'o': opts.offset = atol(optarg); break;
        case 'l': opts.size = atol(optarg); break;
        case 'g': opts.chunk_size = atoi(optarg); break;
        case 'n': opts.chunks_per_line = atoi(optarg); break;
        case 'd': opts.input_dir = optarg; break;
        case 'f': opts.format_str = optarg; break;
        default:
            fprintf(stderr, "Usage: %s -i file [-o offset] [-l size] [-g size] [-n count] [-d dir] [-f format]\n", argv[0]);
            return 1;
        }
    }

    if (opts.input_dir) {
        process_directory(opts.input_dir, &opts);
    }
    else if (opts.input_file) {
        dump_file(opts.input_file, &opts);
    }
    else {
        fprintf(stderr, "Error: No input file (-i) or directory (-d) specified.\n");
        return 1;
    }

    return 0;
}