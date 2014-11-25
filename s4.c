/* 
 * todo:
 * stop leakage from redirection (close files)
 * extend execute so it doesn't rely on space separation
 * actually get program running
 * print specific errors when they occur
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	f = fork();
	if (!f){
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		int n = count_tokens(r, ' '), lend = 0;
		char **c = split(r, ' ');
		char *d[1000];
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
				d[i] = c[i];
				lend++;
				i--;
			}
			i += 2;
		}
		if(lend){
			execvp(d[0], d);
			printf("Unknown Command");
			return 1;
		}
	}
}

/*
   char redirect(char* r){ //t: 1 - >, 2 - >>, 3 - 2>
   f = fork;
   if (!f){
   if (&(strchr(r, ">")+1)==">"){
//int fd = open(f, O_WRONLY | O_APPEND, 0777);
//close(fd);
//dup2(fd,STDOUT_FILENO);
//execlp(e, e, NULL);
}

else if ((strchr(r, ">") != r && &(strchr(r, ">")-1)=="2"){
//int fd = open(f, O_WRONLY | O_APPEND, 0777);
//close(fd);
//dup2(fd,STDERR_FILENO);
//execlp(e, e, NULL);
}

//int fd = open(f, O_WRONLY, 0777);
//close(fd);
//dup2(fd,STDOUT_FILENO);
//execlp(e, e, NULL);
}
return 1;
}
*/
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
			npipes = count_tokens(l[i], '|');
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
				j++;
			}
			i++;
		}
	}
}

		/*    char* l[1000] = {0};
		      l[0] = r;
		      char* p = r-1;
		      int i = 1;
		      while(p = strchr(p+1, ';')){
		      l[i] = p+1;
		 *p = 0;
		 i++;
		 }

		 i = 0;
		 while(l[i])
		 char *p = l+i;
		 if (!strcmp(l[i], "exit")) exit(-1);
		 if (!strcmp(l[i], "cd")) //chdir(path);
		 if (strchr(r, ">") && strchr(r, "|")) execute(l[i]);
		 if (!strchr(r, ">") && strchr(r, "|")) redirect(l[i]);
		 i++;
		 }
		 */
