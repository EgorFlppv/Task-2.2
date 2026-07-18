/*
hexdump_lib.c - реализация библиотеки hexdump.
ФИО: Филиппов Егор Ильич
Группа: МК-102
*/
#include "hexdump_lib.h"

int is_printable(unsigned char c) {
    return (c >= 32 && c <= 126);
}

static void print_chunk_hex(FILE* out, unsigned char* chunk, int size) {
    for (int i = 0; i < size; i++) {
        fprintf(out, "%02X", chunk[i]);
    }
}

static void print_chunk_char(FILE* out, unsigned char* chunk, int size) {
    for (int i = 0; i < size; i++) {
        if (is_printable(chunk[i])) {
            fprintf(out, "%c", chunk[i]);
        }
        else {
            fprintf(out, ".");
        }
    }
}

static void process_line_format(FILE* out, DumpOptions* opts, long current_offset, int line_idx, unsigned char* line_buffer, int bytes_in_line) {
    if (!opts->format_str) {
        fprintf(out, "%08lX ", current_offset);
        int chunks = (bytes_in_line + opts->chunk_size - 1) / opts->chunk_size;
        for (int i = 0; i < chunks; i++) {
            if (i > 0) fprintf(out, " ");
            int start = i * opts->chunk_size;
            int len = (start + opts->chunk_size <= bytes_in_line) ? opts->chunk_size : (bytes_in_line - start);
            print_chunk_hex(out, &line_buffer[start], len);
        }
        if (opts->chunk_size == 1) {
            fprintf(out, " | ");
            for (int i = 0; i < bytes_in_line; i++) {
                fprintf(out, "%c", is_printable(line_buffer[i]) ? line_buffer[i] : '.');
            }
        }
        fprintf(out, "\n");
        return;
    }

    const char* fmt = opts->format_str;
    while (*fmt) {
        if (*fmt == '\\') {
            fmt++;
            switch (*fmt) {
            case 'n': fprintf(out, "\n"); break;
            case 'r': fprintf(out, "\r"); break;
            case 't': fprintf(out, "\t"); break;
            case '\\': fprintf(out, "\\"); break;
            default: fprintf(out, "\\%c", *fmt); break;
            }
            fmt++;
        }
        else if (*fmt == '%') {
            fmt++;
            if (*fmt == 'i') {
                fprintf(out, "%d", line_idx);
                fmt++;
            }
            else if (*fmt == 'n') {
                fprintf(out, "%08lX", current_offset);
                fmt++;
            }
            else if (*fmt == 'x' || *fmt == 'c') {
                int index = 0;
                if (isdigit((unsigned char)*fmt)) {
                    index = *fmt - '0';
                    fmt++;
                }
                char type = *fmt;
                fmt++;

                int start_pos = index * opts->chunk_size;
                if (start_pos < bytes_in_line) {
                    int len = opts->chunk_size;
                    if (start_pos + len > bytes_in_line) {
                        len = bytes_in_line - start_pos;
                    }
                    if (type == 'x') {
                        print_chunk_hex(out, &line_buffer[start_pos], len);
                    }
                    else if (type == 'c') {
                        print_chunk_char(out, &line_buffer[start_pos], len);
                    }
                }
            }
            else {
                fprintf(out, "%%%c", *fmt);
                fmt++;
            }
        }
        else {
            fputc(*fmt, out);
            fmt++;
        }
    }
}

int dump_file(const char* filename, DumpOptions* opts) {
    if (!filename) return -1;

    FILE* f = fopen(filename, "rb");
    if (!f) {
        perror(filename);
        return -1;
    }

    if (opts->offset > 0) {
        fseek(f, opts->offset, SEEK_SET);
    }

    int line_capacity = opts->chunks_per_line * opts->chunk_size;
    unsigned char* line_buffer = malloc(line_capacity);
    if (!line_buffer) {
        fclose(f);
        return -1;
    }

    long total_read = 0;
    int line_idx = 0;

    while (1) {
        memset(line_buffer, 0, line_capacity);
        int bytes_read_in_line = 0;

        for (int i = 0; i < opts->chunks_per_line; i++) {
            for (int j = 0; j < opts->chunk_size; j++) {
                int c = fgetc(f);
                if (c == EOF) break;
                if (opts->size > 0 && total_read >= opts->size) break;

                line_buffer[bytes_read_in_line++] = (unsigned char)c;
                total_read++;
                if (opts->size > 0 && total_read >= opts->size) break;
            }
            if (opts->size > 0 && total_read >= opts->size) break;
            if (feof(f)) break;
        }

        if (bytes_read_in_line == 0) break;

        long current_line_offset = opts->offset + (line_idx * opts->chunks_per_line * opts->chunk_size);
        process_line_format(stdout, opts, current_line_offset, line_idx, line_buffer, bytes_read_in_line);

        line_idx++;
    }

    free(line_buffer);
    fclose(f);
    return 0;
}

void process_directory(const char* dirname, DumpOptions* opts) {
    DIR* dir = opendir(dirname);
    if (!dir) {
        perror(dirname);
        return;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        char path[1024];
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);

        struct stat path_stat;
        stat(path, &path_stat);

        if (S_ISREG(path_stat.st_mode)) {
            printf("=== %s ===\n", path);
            dump_file(path, opts);
            printf("\n");
        }
    }
    closedir(dir);
}