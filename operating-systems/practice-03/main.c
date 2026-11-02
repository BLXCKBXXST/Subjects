#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int process(char *text) {
    char best[5000] = "";
    int max = -1;
    char *word = strtok(text, " \t\r\n.,!?;:()\"-");

    while (word != NULL) {
        int count = 0;
        char *p = word;
        while ((p = strstr(p, "а")) != NULL) {
            count++;
            p += strlen("а");
        }
        if (count > max) {
            max = count;
            strcpy(best, word);
        }
        word = strtok(NULL, " \t\r\n.,!?;:()\"-");
    }

    FILE *out = fopen("output.txt", "w");
    if (out == NULL) {
        perror("output.txt");
        return 0;
    }
    if (max == -1)
        fprintf(out, "В тексте нет слов.\n");
    else
        fprintf(out, "Слово: %s\nКоличество букв 'а': %d\n", best, max);
    fclose(out);
    return 1;
}

int main(void) {
    int fd[2], back[2];
    if (pipe(fd) == -1 || pipe(back) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        close(fd[0]);
        close(back[1]);

        FILE *in = fopen("input.txt", "r");
        if (in == NULL) {
            perror("input.txt");
            close(fd[1]);
            close(back[0]);
            wait(NULL);
            return 1;
        }

        int c;
        while ((c = fgetc(in)) != EOF) {
            char ch = c;
            write(fd[1], &ch, 1);
        }
        char end = 26;
        write(fd[1], &end, 1);
        fclose(in);
        close(fd[1]);

        char name[100];
        ssize_t n = read(back[0], name, sizeof(name) - 1);
        if (n > 0) {
            name[n] = '\0';
            printf("Родитель получил имя файла: %s\n", name);
        } else {
            printf("Дочерний процесс не создал файл.\n");
        }
        close(back[0]);
        wait(NULL);
        return n > 0 ? 0 : 1;
    }

    close(fd[1]);
    close(back[0]);

    char buf[5000];
    int len = 0;
    char c;
    while (read(fd[0], &c, 1) == 1) {
        if (c == 26)
            break;
        if (len >= (int)sizeof(buf) - 1) {
            fprintf(stderr, "Слишком большой текст.\n");
            close(fd[0]);
            close(back[1]);
            return 1;
        }
        buf[len++] = c;
    }
    buf[len] = '\0';
    close(fd[0]);

    if (process(buf)) {
        char name[] = "output.txt";
        write(back[1], name, sizeof(name));
    }
    close(back[1]);
    return 0;
}
