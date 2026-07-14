/*
 * Описание файла: Реализация hex-дампа.
 * ФИО: Филиппов Егор Ильич
 * Группа: МК-102
 */
#include "hexdump_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int dump_file(const char *filepath, const DumpOptions *opts) {
	FILE *f = fopen(filepath, "rb");
    	if (!f) return -1;

    	if (opts->offset > 0) fseek(f, opts->offset, SEEK_SET);

    	size_t buffer_size = opts->chunk_size * opts->chunks_per_line;
    	unsigned char @id4557802 (*buffer) = malloc(buffer_size);
    	if (!buffer) { fclose(f); return -1; }

    	// Переменные для цикла
    	free(buffer);
    	fclose(f);
    	return 0;
	
}
