/*
 * todo:
 * wait for child process
 * handle extra spaces for exec ("ls " breaks)
 * extend execute so it doesn't rely on space separation
 * actually get program running
 * print specific errors when they occur
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

/* counts number of tokens */
int count_tokens(char *s, char delim){
	int c = 1;
	char *p = s-1;
	while(p = strchr(p+1, delim))
		c++;
	return c;
}

char **split(char *s, char delim){
	char d[2] = {delim, '\0'};
	char **sep = malloc(sizeof(char*) * 1000);
	int i = 0;
	while((sep[i] = strsep(&s, d)))
		i++;
	return sep;
}

char execute(char* r, int in, int out){
	int f = fork();
	if (f == 0){
                printf("in: %d\nout: %d\n", in, out);
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
                close(out);
                printf("after dup2\n");
		int n = count_tokens(r, ' '), lend = 0;
		char **c = split(r, ' ');
		char *reduced[1000];
		int i=0, j=0, fd;
		while(i<n){
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
                        printf("Above exec\n");
			execvp(reduced[0], reduced);
			printf("Unknown Command\n");
			return 1;
		}
	}
}

main(){
	int i, j, npipes;
	int fdin, fdout;
	char buf[1000], **l, **lpipe;
	while(1){
		printf("> ");
		fgets(buf, sizeof buf, stdin);
		*strchr(buf, '\n') = 0;

		l = split(buf, ';');
		i = 0;
		while (l[i]) {
			// "exit" case
			// "cd" case
			npipes = count_tokens(l[i], '|') - 1;
			lpipe = split(l[i], '|');
			j = 0;
			while (lpipe[j]) {
				if(j%2 == 0){
					fdin = open(".f1", O_RDONLY);
					fdout = open(".f2", O_CREAT | O_TRUNC, 0777);
				}
				else {
					fdin = open(".f2", O_RDONLY);
					fdout = open(".f1", O_CREAT | O_TRUNC, 0777);
				}
				if(j == 0)
					fdin = 0;
				if(j == npipes)
					fdout = 1;
				execute(lpipe[j], fdin, fdout);
                                if (j != 0)
                                    close(fdin);
                                if (j != npipes)
                                    close(fdout);
				j++;
			}
			i++;
		}
	}
}
