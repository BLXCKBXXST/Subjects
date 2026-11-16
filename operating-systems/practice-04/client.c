#include "common.h"

int main(void) {
    char file_name[MAXBUFF];
    printf("Введите имя файла: ");
    fflush(stdout);
    fgets(file_name, sizeof(file_name), stdin);
    file_name[strcspn(file_name, "\r\n")] = '\0';

    int channel = open(FIFO, O_WRONLY);
    write(channel, file_name, strlen(file_name));
    write(channel, "\n", 1);
    close(channel);

    FILE *response = fopen(FIFO, "r");
    fgets(file_name, sizeof(file_name), response);
    fclose(response);
    file_name[strcspn(file_name, "\r\n")] = '\0';

    FILE *result = fopen(file_name, "r");
    int symbol;
    while ((symbol = fgetc(result)) != EOF)
        putchar(symbol);
    fclose(result);
    return 0;
}
