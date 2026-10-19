#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd[2], back[2];
    pipe(fd);
    pipe(back);

    int pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        close(fd[0]);
        close(back[1]);

        FILE *f = fopen("input.txt", "r");
        if (f == NULL) {
            perror("input.txt");
            exit(1);
        }

        int c;
        while ((c = fgetc(f)) != EOF) {
            char ch = c;
            write(fd[1], &ch, 1);
        }

        char end = 26;
        write(fd[1], &end, 1);

        fclose(f);
        close(fd[1]);

        char answer;
        read(back[0], &answer, 1);
        printf("\nРодитель получил: %c\n", answer);

        close(back[0]);
        exit(0);
    }
    else {
        close(fd[1]);
        close(back[0]);

        char c;
        printf("Потомок получил текст:\n");

        while (read(fd[0], &c, 1) == 1) {
            if (c == 26)
                break;

            printf("%c", c);
            fflush(stdout);
            sleep(1);
        }

        close(fd[0]);

        char answer = 'Y';
        write(back[1], &answer, 1);
        close(back[1]);

        exit(0);
    }
}
