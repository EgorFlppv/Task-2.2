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

    	size_t current_offset = opts->offset;
    	size_t line_idx = 0;
    	size_t total_read = 0;

    	while (1) {
        	size_t to_read = buffer_size;
        	if (opts->size > 0 && (opts->size - total_read) < buffer_size) {
            		to_read = opts->size - total_read;
        	}
        	if (to_read == 0) break;

        	size_t bytes = fread(buffer, 1, to_read, f);
        	if (bytes == 0) break;

        	// Здесь будет вывод
        
        	current_offset += bytes;
        	total_read += bytes;
        	line_idx++;
        	if (bytes < buffer_size) break; // Конец файла
    	}

    	free(buffer);
    	fclose(f);
    	return 0;
	
}
