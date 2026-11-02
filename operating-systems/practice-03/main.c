#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];
    pipe(fd);

    int pid = fork();

    if (pid > 0) {

        int keyboard = isatty(STDIN_FILENO);
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
        char name[100];
        read(fd[0], name, sizeof(name));
        printf("Родитель получил имя файла: %s\n", name);
        close(fd[0]);
    } else {

        char text[5000];
        int len = 0;
        char c;
        while (read(fd[0], &c, 1) == 1 && c != 26)
            text[len++] = c;
        text[len] = '\0';
        close(fd[0]);

        char best[5000] = "";
        int max = -1;
        char *word = strtok(text, " \n");
        while (word != NULL) {
            int count = 0;
            for (char *p = word; *p; p++) {
                if (strncmp(p, "а", 2) == 0)
                    count++;
            }
            if (count > max) {
                max = count;
                strcpy(best, word);
            }
            word = strtok(NULL, " \n");
        }

        FILE *out = fopen("output.txt", "w");
        fprintf(out, "Слово: %s\nКоличество букв 'а': %d\n", best, max);
        fclose(out);

        char name[] = "output.txt";
        write(fd[1], name, sizeof(name));
        close(fd[1]);
    }
    return 0;
}
