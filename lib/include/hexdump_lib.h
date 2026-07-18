/*
hexdump_lib.h - заголовочный файл библиотеки hexdump.
ФИО: Филиппов Егор Ильич
Группа: МК-102
*/
#ifndef HEXDUMP_LIB_H
#define HEXDUMP_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct {
    char* input_file;
    char* input_dir;
    char* format_str;
    long offset;
    long size;
    int chunk_size;
    int chunks_per_line;
} DumpOptions;

int dump_file(const char* filename, DumpOptions* opts);
void process_directory(const char* dirname, DumpOptions* opts);
int is_printable(unsigned char c);

#endif