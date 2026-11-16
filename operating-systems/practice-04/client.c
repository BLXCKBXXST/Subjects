#include "common.h"

int main(void) {
    char file_name[NAME_SIZE];
    printf("Введите имя файла: ");
    fflush(stdout);
    if (fgets(file_name, sizeof(file_name), stdin) == NULL)
        return 1;
    file_name[strcspn(file_name, "\r\n")] = '\0';

    int request = open(REQUEST_FIFO, O_WRONLY);
    if (request == -1) {
        perror("Не удалось открыть канал запроса. Сначала запустите сервер");
        return 1;
    }
    char message[MESSAGE_SIZE];
    int length = snprintf(message, sizeof(message), "%s%s%s\n",
                          REQUEST_START, file_name, REQUEST_END);
    if (write(request, message, length) != length) {
        perror("Ошибка отправки имени файла");
        close(request);
        return 1;
    }
    close(request);

    FILE *response = fopen(RESPONSE_FIFO, "r");
    if (response == NULL) {
        perror("Не удалось открыть канал ответа");
        return 1;
    }
    if (fgets(file_name, sizeof(file_name), response) == NULL) {
        fprintf(stderr, "Сервер не прислал ответ.\n");
        fclose(response);
        return 1;
    }
    fclose(response);
    file_name[strcspn(file_name, "\r\n")] = '\0';

    if (strcmp(file_name, ERROR_REPLY) == 0) {
        fprintf(stderr, "Сервер не смог обработать файл.\n");
        return 1;
    }

    FILE *result = fopen(file_name, "r");
    if (result == NULL) {
        perror("Не удалось открыть файл результата");
        return 1;
    }
    printf("Файл результата: %s\n", file_name);
    int symbol;
    while ((symbol = fgetc(result)) != EOF)
        putchar(symbol);
    int status = ferror(result) ? 1 : 0;
    fclose(result);
    return status;
}
