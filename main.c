#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BUFSIZE 1024
#define LSH_TOK_BUFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

// ==================== Read line ====================
char *ish_read_line(void) {
    int bufsize = BUFSIZE;
    int position = 0;
    int c;
    char *line = malloc(sizeof(char) * bufsize);

    if (!line) {
        printf("Out of memory\n");
        exit(-1);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            line[position] = '\0';
            return line;
        } else {
            line[position] = c;
        }

        position++;

        if (position >= bufsize) {
            bufsize += BUFSIZE;
            line = realloc(line, bufsize);
            if (!line) {
                printf("Out of memory\n");
                exit(-1);
            }
        }
    }
}

// ==================== Split line ====================
char **lsh_split_line(char *line) {
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(sizeof(char *) * bufsize);
    char *token;

    if (!tokens) {
        printf("Out of memory\n");
        exit(-1);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize);
            if (!tokens) {
                printf("Out of memory\n");
                exit(-1);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

// ==================== Built-in commands ====================
char *builtin_func[] = {"cd", "help", "exit"};

int func_cd(char **args) {
    printf("cd command\n");
    return 1;
}

int func_help(char **args) {
    printf("Available commands: cd, help, exit\n");
    return 1;
}

int func_exit(char **args) {
    return 0;
}

int (*builtin_funcs[])(char **) = {&func_cd, &func_help, &func_exit};

int num_builtins() {
    return sizeof(builtin_func) / sizeof(char *);
}

// ==================== Execute command ====================
int lsh_execute(char **args) {
    if (args[0] == NULL) {
        printf("Not enough arguments\n");
        return 1;
    }

    // Built-in commands
    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_func[i]) == 0) {
            return builtin_funcs[i](args);
        }
    }

    // External command
    char command_line[1024] = "";
    for (int i = 0; args[i] != NULL; i++) {
        strcat(command_line, args[i]);
        strcat(command_line, " ");
    }

    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(
            NULL,
            command_line,
            NULL, NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi)) {
        printf("Command not found: %s\n", args[0]);
        return 1;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 1;
}

// ==================== Shell loop ====================
void ish_loop(void) {
    char *line;
    char **args;
    int status = 1;

    do {
        printf("Enter command line: \n");
        line = ish_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);
        free(line);
        free(args);
    } while (status);
}

// ==================== Main ====================
int main(void) {
    ish_loop();
    return 0;
}
