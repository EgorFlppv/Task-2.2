/*
 * Описание файла: Парсинг аргументов для hex-дампа.
 * ФИО: Филиппов Егор Ильич
 * Группа: МК-102
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "hexdump_lib.h"

int main(int argc, char *argv[]) {
	DumpOptions opts = {0, 0, 1, 16, NULL};
    	char *filepath = NULL;
    	char *dirpath = NULL;
    	int opt;

    	while ((opt = getopt(argc, argv, "i:o:l:g:n:d:f:")) != -1) {
        	switch (opt) {
            		case 'i': filepath = optarg; break;
            		case 'o': opts.offset = strtoull(optarg, NULL, 10); break;
            		case 'l': opts.size = strtoull(optarg, NULL, 10); break;
			case 'g': opts.chunk_size = strtoull(optarg, NULL, 10); break;
            		case 'n': opts.chunks_per_line = strtoull(optarg, NULL, 10); break;
            		case 'f': opts.format_str = optarg; break; 
            		case 'd': dirpath = optarg; break; // Флаг директории
        	}
    	}

	return 0;
}

