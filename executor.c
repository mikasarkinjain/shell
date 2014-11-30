#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <errno.h>

#include "s4.h"

int execute(char* r, int in, int out){
	int f = fork();
	if (f == 0){
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		int n = count_tokens(r, ' '), lend = 0;
		char **c = split(r, ' ');
		char *reduced[1000];
		int i=0, fd;
		while(i<n){
                        // "cd" case
                        if (!strcmp("cd", c[i])) {
                                // handle the error
                                if (chdir(c[i+1]) == -1)
                                    printf("%s\n", strerror(errno));
                                return -1;
                        }
			if(!strcmp(">", c[i])){
				fd = open(c[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
				dup2(fd, STDOUT_FILENO);

			}
			else if(!strcmp(">>", c[i])){
				fd = open(c[i+1], O_CREAT | O_WRONLY | O_APPEND, 0777);
				dup2(fd, STDOUT_FILENO);
			}
			else if(!strcmp("2>", c[i])){
				fd = open(c[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
				dup2(fd, STDERR_FILENO);
			}
			else if(!strcmp("2>>", c[i])){
				fd = open(c[i+1], O_CREAT | O_WRONLY | O_APPEND, 0777);
				dup2(fd, STDERR_FILENO);
			}
			else if(!strcmp("&>", c[i])){
				fd = open(c[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
				dup2(fd, STDOUT_FILENO);
				dup2(fd, STDERR_FILENO);
			}
			else if(!strcmp("<", c[i])){
				fd = open(c[i+1], O_RDONLY);
				dup2(fd, STDIN_FILENO);
			}
			else {
				reduced[i] = c[i];
				lend++;
				i--;
			}
			i += 2;
		}
		if(lend){
			execvp(reduced[0], reduced);
			printf("Unknown Command\n");
		}
	}
        return f;
}
