#include "practice.h"

void print_usage(char *program_name) {
    fprintf(stderr, "Запуск: %s [-1] [-2] [-f файл]\n", program_name);
    fprintf(stderr, "-1: окружение через envp\n");
    fprintf(stderr, "-2: окружение через environ\n");
    fprintf(stderr, "-f: вывести содержимое файла\n");
}

int print_environment(char *environment[]) {
    for (int i = 0; i < 10 && environment[i] != NULL; i++) {
        if (printf("%s\n", environment[i]) < 0) {
            perror("Ошибка вывода окружения");
            return 1;
        }
    }

    if (fflush(stdout) == EOF) {
        perror("Ошибка вывода окружения");
        return 1;
    }
    return 0;
}

int print_file(char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        fprintf(stderr, "Не удалось открыть файл %s\n", file_name);
        perror("Причина");
        return 1;
    }

    int symbol;
    int status = 0;

    while ((symbol = fgetc(file)) != EOF) {
        if (putchar(symbol) == EOF) {
            perror("Ошибка вывода файла");
            status = 1;
            break;
        }
    }

    if (ferror(file)) {
        perror("Ошибка чтения файла");
        status = 1;
    }
    if (fclose(file) == EOF) {
        perror("Ошибка закрытия файла");
        status = 1;
    }
    if (status == 0 && fflush(stdout) == EOF) {
        perror("Ошибка вывода файла");
        status = 1;
    }
    return status;
}

int print_author(void) {
    FILE *output = stdout;
    if (ferror(stdout))
        output = stderr;

    int result = fprintf(output,
                         "\nАвтор: Язиков Денис Александрович\nUID: %lu\n",
                         (unsigned long)getuid());
    if (result < 0 || fflush(output) == EOF) {
        if (output == stdout) {
            fprintf(stderr,
                    "\nАвтор: Язиков Денис Александрович\nUID: %lu\n",
                    (unsigned long)getuid());
        }
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[], char *envp[]) {
    int option;
    int status = 0;

    signal(SIGPIPE, SIG_IGN);

    if (argc == 1) {
        print_usage(argv[0]);
        status = 1;
    }

    while ((option = getopt(argc, argv, ":12f:")) != -1) {
        switch (option) {
            case '1':
                if (print_environment(envp) != 0)
                    status = 1;
                break;

            case '2':
                if (print_environment(environ) != 0)
                    status = 1;
                break;

            case 'f':
                if (print_file(optarg) != 0)
                    status = 1;
                break;

            case ':':
                fprintf(stderr, "После -%c нужно имя файла.\n", optopt);
                print_usage(argv[0]);
                status = 1;
                break;

            case '?':
                fprintf(stderr, "Неизвестная опция: -%c\n", optopt);
                print_usage(argv[0]);
                status = 1;
                break;
        }
    }

    if (optind < argc) {
        fprintf(stderr, "Лишний аргумент: %s\n", argv[optind]);
        print_usage(argv[0]);
        status = 1;
    }

    if (print_author() != 0)
        status = 1;

    return status;
}
