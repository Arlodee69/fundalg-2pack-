#include "header.h"

void my_free(char **dynamic, size_t count) {

    if (!dynamic) return;

    for (size_t i = 0; i < count; i++){
        free(dynamic[i]);
    }

    free(dynamic);
}

status_code parse_file(const char *file_in, const char *file_out){

    if (!file_in || !file_out) return ARG_ERROR;

    FILE *input = fopen(file_in, "r");
    FILE *output = fopen(file_out, "w");

    if (!input || !output){
        if (input) fclose(input);
        if (output) fclose(output);
        return FILE_ERROR;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    status_code status = VALID;

    while((read = getline(&line, &len, input)) != -1) {
        if (read > 0 && line[read - 1] == '\n'){
            line[read - 1] = '\0';
        }

        if (strlen(line) < 80){
            if(fprintf(output, "%s\n", line) < 0){
                free(line);
                return FILE_ERROR;
            }
            continue;
        }
        status = some_line(output, line);
        if (status != VALID){
            break;
        }
    }
    free(line);
    fclose(input);
    fclose(output);

    return status;
}

status_code some_line(FILE *file_out, const char *line) {
    char **words = NULL;
    size_t words_count = 0;
    
    status_code status = parse_line(line, &words, &words_count);
    if (status != VALID) return status; 

    if (words_count == 0) {
        if (fputs("\n", file_out) < 0) {
            my_free(words, words_count);
            return FILE_ERROR;
        }
        my_free(words, words_count);
        return VALID;
    }

    size_t i = 0;
    while (i < words_count) { 
        size_t j = i;
        size_t curr = 0;

        while (j < words_count) {
            size_t word_len = strlen(words[j]);
            if (word_len > 80) {
                 if (j > i) {
                     break;
                 } else {
                     j++;
                     break;
                 }
            }
            size_t new_len = curr + word_len + (j > i ? 1 : 0);

            if (new_len > 80) {
                break;
            }

            curr = new_len;
            j++;
        }

        //[i, j) - группа слов, помещающихся в 80 символов
        char *formatted_line = build_line(words, i, j);
        if (!formatted_line) {
            my_free(words, words_count);
            return ALLOCATION_ERROR;
        }

        if (fputs(formatted_line, file_out) < 0 || fputc('\n', file_out) == EOF){
            free(formatted_line);
            my_free(words, words_count);
            return FILE_ERROR;
        }

        free(formatted_line);
        i = j;
    }

    my_free(words, words_count);
    return VALID;
}

status_code parse_line(const char *line, char*** words, size_t* count) {

    if (!line || !words || !count) return ARG_ERROR;

    size_t start_size = 10;
    char **result = (char **)malloc(sizeof(char *) * start_size);
    if (!result) return ALLOCATION_ERROR;

    *count = 0;
    size_t start_index = 0;
    size_t line_len = strlen(line);

    for (size_t i = 0; i <= line_len; i++){
        if (line[i] == '\0' || line[i] == ' '){
            if (i > start_index){
                if(*count >= start_size){
                    start_size *= 2;
                    char **temp = (char **)realloc(result, start_size * sizeof(char *));
                    if (!temp){
                        my_free(result, *count);
                        return ALLOCATION_ERROR;
                    }
                    result = temp;
                }

                size_t word_len = i - start_index;
                result[*count] = malloc(sizeof(char) * (word_len + 1));
                if (!result[*count]) {
                    my_free(result, *count);
                    return ALLOCATION_ERROR;
                }
                memcpy(result[*count], line + start_index, word_len);
                result[*count][word_len] = '\0';
                (*count)++;
            }
            start_index = i + 1;
        }
    }
    *words = result; 
    return VALID;
}

char *build_line(char **words, size_t start, size_t end){
    if (!words || start >= end) return NULL;

    size_t words_count = end - start;

    size_t full_len = 0;
    for (size_t i = start; i < end; i++) {
        full_len += strlen(words[i]);
    }

    size_t needed = words_count - 1;
    if (needed == 0) {
        size_t word_len = strlen(words[start]);
        char *line = malloc((word_len + 1) * sizeof(char));
        if (!line) return NULL;
        strcpy(line, words[start]);
        return line;
    }

    size_t line_len = full_len + needed;

    size_t ext_spaces = 80 - line_len;
    size_t gap = 1 + ext_spaces / needed;
    size_t ext_gaps = ext_spaces % needed;

    size_t total_len = full_len + (gap * needed);
    if (ext_gaps > 0) {
        total_len += ext_gaps;
    }

    char *line = malloc((total_len + 1) * sizeof(char));
    if (!line) return NULL;

    char *p = line;
    for (size_t i = start; i < end; i++) {
        strcpy(p, words[i]);
        p += strlen(words[i]);

        if (i + 1 < end) {
            size_t spaces = gap + (ext_gaps > i - start ? 1 : 0);
            memset(p, ' ', spaces);
            p += spaces;
        }
    }

    *p = '\0';
    return line;
}