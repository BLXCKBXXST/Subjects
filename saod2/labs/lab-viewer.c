#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lab-viewer.h"
#ifdef _WIN32
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#define chdir _chdir
#define getcwd _getcwd
#else
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif
#endif

int initLabPaths(const char *program)
{
    char path[4096];
#ifdef _WIN32
    (void)program;
    DWORD size = GetModuleFileNameA(NULL, path, sizeof(path));
    if (size == 0 || size >= sizeof(path)) return 0;
    for (char *p = path; *p; p++) if (*p == '\\') *p = '/';
#elif defined(__linux__)
    ssize_t size = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (size < 0 || (size_t)size >= sizeof(path) - 1) return 0;
    path[size] = '\0';
    (void)program;
#elif defined(__APPLE__)
    char raw[4096];
    uint32_t size = sizeof(raw);
    if (_NSGetExecutablePath(raw, &size) != 0 || realpath(raw, path) == NULL)
        return 0;
    (void)program;
#else
    if (realpath(program, path) == NULL) return 0;
#endif
    char *last = strrchr(path, '/');
    if (last == NULL) return 0;
    *last = '\0';
    last = strrchr(path, '/');
    if (last == NULL) return 0;
    *last = '\0';
    char check[4200];
    snprintf(check, sizeof(check), "%s/labs/lab-viewer.js", path);
    FILE *file = fopen(check, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Не найден каталог saod2 рядом с build: %s\n", path);
        return 0;
    }
    fclose(file);
    if (chdir(path) != 0)
    {
        perror(path);
        return 0;
    }
    return 1;
}

int openLabPage(const char *page)
{
    char root[4096], full[4600];
    if (getcwd(root, sizeof(root)) == NULL)
    {
        perror("getcwd");
        return 0;
    }
    snprintf(full, sizeof(full), "%s/%s", root, page);
    FILE *file = fopen(full, "r");
    if (file == NULL)
    {
        perror(full);
        return 0;
    }
    fclose(file);
    printf("Страница дерева: %s\n", full);
    fflush(stdout);
    if (getenv("SAOD_NO_BROWSER") != NULL) return 1;
#ifdef _WIN32
    INT_PTR result = (INT_PTR)ShellExecuteA(NULL, "open", full, NULL, NULL, SW_SHOWNORMAL);
    if (result > 32) return 1;
    fprintf(stderr, "Не удалось открыть браузер (код %ld). Откройте %s\n",
            (long)result, full);
    return 0;
#else
    char logPath[4600];
    snprintf(logPath, sizeof(logPath), "%s/build/browser.log", root);
    FILE *log = fopen(logPath, "a");
    if (log == NULL)
    {
        perror(logPath);
        fprintf(stderr, "Откройте вручную: %s\n", full);
        return 0;
    }
    fprintf(log, "\nОткрытие страницы: %s\n", full);
    if (fclose(log) != 0)
    {
        perror(logPath);
        return 0;
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("fork");
        return 0;
    }
    if (pid == 0)
    {
        if (freopen(logPath, "a", stderr) == NULL) _exit(126);
        if (freopen(logPath, "a", stdout) == NULL ||
            freopen("/dev/null", "r", stdin) == NULL)
        {
            perror("Подготовка запуска браузера");
            _exit(126);
        }
#ifdef __APPLE__
        execlp("open", "open", full, (char *)NULL);
#else
        execlp("xdg-open", "xdg-open", full, (char *)NULL);
#endif
        perror("Открытие браузера");
        _exit(127);
    }
    int status;
    while (waitpid(pid, &status, 0) < 0)
    {
        if (errno == EINTR) continue;
        perror("waitpid");
        return 0;
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) return 1;
    fprintf(stderr, "Не удалось открыть браузер. Откройте вручную: %s\n"
                    "Сообщения браузера: %s\n", full, logPath);
    return 0;
#endif
}
