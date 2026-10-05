#ifndef PRACTICE_H
#define PRACTICE_H

#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <signal.h>

extern char **environ;

void print_usage(char *program_name);
int print_environment(char *environment[]);
int print_file(char *file_name);
int print_author(void);

#endif
