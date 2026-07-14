/*
 * Описание файла: Библиотека для вывода содержимого файлов в шестнадцатеричном виде.
 * ФИО: Филиппов Егор Ильич
 * Группа: МК-102
 */
#ifndef HEXDUMP_LIB_H
#define HEXDUMP_LIB_H

#include <stddef.h>

	// Структура параметров вывода
	typedef struct {
	size_t offset;          // -o
	size_t size;            // -l (если 0, то до конца)
	size_t chunk_size;      // -g
	size_t chunks_per_line; // -n
    	const char *format_str; // -f 
} DumpOptions;

int dump_file(const char *filepath, const DumpOptions *opts);

#endif
