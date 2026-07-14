/*
 * Описание файла: Реализация hex-дампа.
 * ФИО: Филиппов Егор Ильич
 * Группа: МК-102
 */
#include "hexdump_lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static void print_custom_format(size_t line_idx, size_t current_offset, unsigned char *data, size_t data_len, const DumpOptions *opts) {
	if (!opts->format_str) {
        	// Стандартный вывод
        	printf("%08zX  ", current_offset);
        	for(size_t i = 0; i < data_len; i += opts->chunk_size) {
            		printf("%02X ", data[i]);
        	}
        	printf("\n");
        	return;
    	}
}

const char *p = opts->format_str;
    	while (*p) {
        	if (*p == '\\') {
            		p++;
            		switch(*p) {
                	case 'n': putchar('\n'); break;
                	case 't': putchar('\t'); break;
                	default: putchar('\\'); putchar(*p); break;
            		}
        	}
		else if (*p == '%') {
            		p++;
            		if (*p == 'i') printf("%zu", line_idx);
            		else if (*p == 'n') printf("%zu", current_offset);
            		else {
                		int chunk_idx = 0;
                		while (isdigit(*p)) {
					chunk_idx = chunk_idx * 10 + (*p - '0');
					p++;
				}
                		if ((*p == 'x' || *p == 'X') && (size_t)chunk_idx < data_len) {
                    			printf("%02X", data[chunk_idx]);
                		}
				else if (*p == 'c' && (size_t)chunk_idx < data_len) {
                    			char c = data[chunk_idx];
                    			putchar((c >= 32 && c <= 126) ? c : '.');
                		}
            		}
        	} 
		else {
            		putchar(*p);
        		}
    	}

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

        	print_custom_format(line_idx, current_offset, buffer, bytes, opts);
        
        	current_offset += bytes;
        	total_read += bytes;
        	line_idx++;
        	if (bytes < buffer_size) break; // Конец файла
    	}

    	free(buffer);
    	fclose(f);
    	return 0;
	
}
