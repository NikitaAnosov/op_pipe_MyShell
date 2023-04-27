#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

#define MAX_ARGS 10
#define MAX_PIPE 10
pid_t shell_pid;
void sigint_handler(int sig)
{
    if (getpid() == shell_pid)
    {
        signal(SIGINT, sigint_handler);
    }
    else
    {
        signal(SIGINT, SIG_DFL);
    }
}

int main()
{
    char input[100];
    char *args[MAX_ARGS][MAX_ARGS];
    int i, j, num_args, num_pipes, status;
    int pipefds[MAX_PIPE][2];
    pid_t pid;
    shell_pid = getpid();
    signal(SIGINT, sigint_handler);

    while (1)
    {
        // Print prompt
        printf("stshell: ");
        // Read input
        fgets(input, sizeof(input), stdin);
        input[strlen(input) - 1] = '\0';

        // Check if 'exit' command
        if (strcmp(input, "exit") == 0)
        {
            break;
        }

        // Split input into separate commands
        char *commands[MAX_PIPE];
        num_pipes = 0;
        commands[num_pipes] = strtok(input, "|");
        while (commands[num_pipes] != NULL)
        {
            num_pipes++;
            commands[num_pipes] = strtok(NULL, "|");
        }

        // Execute commands
        for (i = 0; i < num_pipes; i++)
        {
            // Check if output redirection
            char *redirect_append = strstr(commands[i], ">>");
            char *redirect_output = strstr(commands[i], ">");
            char *redirect_cmd = NULL;

            if (redirect_append != NULL)
            {
                redirect_cmd = redirect_append;
                *redirect_cmd = '\0'; // Terminate command before the append symbol
                redirect_cmd += 2;    // Move pointer to the filename after the append symbol
            }
            else if (redirect_output != NULL)
            {
                redirect_cmd = redirect_output;
                *redirect_cmd = '\0'; // Terminate command before the output symbol
                redirect_cmd += 1;    // Move pointer to the filename after the output symbol
            }

            // Split command into separate arguments
            num_args = 0;
            args[i][num_args] = strtok(commands[i], " ");
            while (args[i][num_args] != NULL)
            {
                num_args++;
                args[i][num_args] = strtok(NULL, " ");
            }
            args[i][num_args] = NULL;

            // Create pipe
            if (pipe(pipefds[i]) == -1)
            {
                perror("pipe");
                return 1;
            }

            // Fork process
            pid = fork();
            if (pid == -1)
            {
                perror("fork");
                return 1;
            }
            else if (pid == 0)
            {
                // Child process
                if (i > 0)
                {
                    // Redirect stdin to previous pipe
                    dup2(pipefds[i - 1][0], STDIN_FILENO);
                }
                if (i < num_pipes - 1)
                {
                    // Redirect stdout to next pipe
                    dup2(pipefds[i][1], STDOUT_FILENO);
                }
                // Close all pipe fds
                for (j = 0; j < num_pipes; j++)
                {
                    if (j != i)
                    {
                        close(pipefds[j][0]);
                        close(pipefds[j][1]);
                    }
                }

                // Check if output redirection
                if (redirect_cmd != NULL)
                {
                    int fd;
                    if (redirect_append != NULL)
                    {
                        // Open file for append
                        fd = open(redirect_cmd, O_WRONLY | O_APPEND | O_CREAT, 0644);
                    }
                    else
                    {
                        // Open file for write
                        fd = open(redirect_cmd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
                    }
                    if (fd == -1)
                    {
                        perror("open");
                        exit(1);
                    }
                    // Redirect stdout to file
                    dup2(fd, STDOUT_FILENO);
                    close(fd);
                }

                // Execute command
                if (execvp(args[i][0], args[i]) == -1)
                {
                    perror("execvp");
                    exit(1);
                }
            }
            else
            {
                // Parent process
                // Close unused pipe fds
                if (i > 0)
                {
                    close(pipefds[i - 1][0]);
                    close(pipefds[i - 1][1]);
                }
            }
        }

        // Wait for all child processes to finish
        for (i = 0; i < num_pipes; i++)
        {
            wait(&status);
        }
    }

    return 0;
}
