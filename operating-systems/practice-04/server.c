#include "common.h"

void remove_fifos(void) {
    unlink(REQUEST_FIFO);
    unlink(RESPONSE_FIFO);
}

int process_file(char *file_name) {
    FILE *input = fopen(file_name, "r");
    if (input == NULL) {
        perror("Не удалось открыть исходный файл");
        return 1;
    }

    char text[TEXT_SIZE];
    int len = fread(text, 1, sizeof(text) - 1, input);
    if (ferror(input)) {
        perror("Ошибка чтения файла");
        fclose(input);
        return 1;
    }
    text[len] = '\0';
    fclose(input);

    int start = 0, best = 0, best_end = 0;
    int count = 0, max = -1;
    char a[] = "а";

    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\t' ||
            text[i] == '\r' || text[i] == '\0') {
            if (i > start && count > max) {
                max = count;
                best = start;
                best_end = i;
            }
            start = i + 1;
            count = 0;
        } else if (text[i] == a[0] && text[i + 1] == a[1]) {
            count++;
        }
    }

    FILE *output = fopen(RESULT_FILE, "w");
    if (output == NULL) {
        perror("Не удалось создать результат");
        return 1;
    }

    int written;
    if (max < 0) {
        written = fprintf(output, "Слов нет.\n");
    } else {
        text[best_end] = '\0';
        written = fprintf(output, "Слово: %s\nКоличество букв 'а': %d\n",
                          text + best, max);
    }
    int closed = fclose(output);
    if (written < 0 || closed == EOF) {
        perror("Не удалось записать результат");
        return 1;
    }
    return 0;
}

int main(void) {
    if (mkfifo(REQUEST_FIFO, 0600) == -1) {
        perror("Не удалось создать request.fifo");
        return 1;
    }
    if (mkfifo(RESPONSE_FIFO, 0600) == -1) {
        perror("Не удалось создать response.fifo");
        unlink(REQUEST_FIFO);
        return 1;
    }

    printf("Сервер ждёт имя файла от клиента.\n");
    fflush(stdout);
    FILE *request = fopen(REQUEST_FIFO, "r");
    if (request == NULL) {
        perror("Не удалось открыть канал запроса");
        remove_fifos();
        return 1;
    }

    char message[MESSAGE_SIZE];
    char file_name[MESSAGE_SIZE] = "";
    while (fgets(message, sizeof(message), request) != NULL) {
        char *start = strstr(message, REQUEST_START);
        if (start == NULL)
            continue;
        start += strlen(REQUEST_START);
        char *end = strstr(start, REQUEST_END);
        if (end == NULL)
            continue;
        *end = '\0';
        strcpy(file_name, start);
        break;
    }
    fclose(request);

    int status = 1;
    if (file_name[0] != '\0')
        status = process_file(file_name);
    else
        fprintf(stderr, "Не получено имя файла.\n");

    FILE *response = fopen(RESPONSE_FIFO, "w");
    if (response == NULL) {
        perror("Не удалось открыть канал ответа");
        remove_fifos();
        return 1;
    }
    fprintf(response, "%s\n", status == 0 ? RESULT_FILE : ERROR_REPLY);
    if (fclose(response) == EOF) {
        perror("Ошибка отправки ответа");
        status = 1;
    }
    remove_fifos();
    return status;
}
