#include "common.h"

int main(void) {
    mkfifo(FIFO, 0600);

    FILE *channel = fopen(FIFO, "r");
    char file_name[MAXBUFF];
    while (fgets(file_name, sizeof(file_name), channel) != NULL) {
        file_name[strcspn(file_name, "\r\n")] = '\0';
        if (access(file_name, F_OK) == 0)
            break;
    }
    fclose(channel);

    FILE *input = fopen(file_name, "r");
    char text[MAXBUFF];
    int len = fread(text, 1, sizeof(text) - 1, input);
    text[len] = '\0';
    fclose(input);

    int start = 0, best = 0, best_end = 0;
    int count = 0, max = -1;
    char a[] = "а";
    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '\n' || text[i] == '\0') {
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

    text[best_end] = '\0';
    FILE *output = fopen(RESULT_FILE, "w");
    fprintf(output, "Слово: %s\nКоличество букв 'а': %d\n",
            text + best, max);
    fclose(output);

    channel = fopen(FIFO, "w");
    fprintf(channel, "%s\n", RESULT_FILE);
    fclose(channel);
    unlink(FIFO);
    return 0;
}
