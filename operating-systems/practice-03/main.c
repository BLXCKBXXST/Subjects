#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pipe(fd);

    if (fork() > 0) {
        int keyboard = isatty(0);
        if (keyboard) {
            printf("Введите текст: ");
            fflush(stdout);
        }

        int c;
        while ((c = getchar()) != EOF) {
            if (keyboard && c == '\n')
                break;
            char ch = c;
            write(fd[1], &ch, 1);
        }
        char end = 26;
        write(fd[1], &end, 1);
        close(fd[1]);

        wait(NULL);
        char name[20];
        read(fd[0], name, sizeof(name));
        printf("Файл результата: %s\n", name);
        close(fd[0]);
    } else {
        char text[5000], c;
        int len = 0;
        while (read(fd[0], &c, 1) == 1 && c != 26)
            text[len++] = c;
        text[len] = '\0';
        close(fd[0]);

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
        FILE *out = fopen("output.txt", "w");
        fprintf(out, "Слово: %s\nКоличество букв 'а': %d\n", text + best, max);
        fclose(out);

        char name[] = "output.txt";
        write(fd[1], name, sizeof(name));
        close(fd[1]);
    }
    return 0;
}
