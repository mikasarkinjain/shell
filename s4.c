/*
 * todo:
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
#include <wait.h>

#include "executor.h"

/* counts number of tokens */
int count_tokens(char *s, char delim){
	int c = 1;
	char *p = s-1;
	while ((p = strchr(p+1, delim)))
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


/*
 * int argument_number - the argument that the parser is on, each argument is separated by a '|'
 * char **lpipe - array of all of the arguments
 * int npipes - total number of pipes
 *
 * handles which file descriptor to write to and executes the argument
 */
static void handle_argument(int argument_number, char **lpipe, int npipes) {
        int fdin, fdout;
        /*
         * alternate between in and out files so that the next function reads
         * from the previous function's out file and writes output to the in file
         */
        if(argument_number%2 == 0){
                fdin = open(".f1", O_RDONLY);
                fdout = open(".f2", O_CREAT | O_WRONLY | O_TRUNC, 0777);
        }
        else {
                fdin = open(".f2", O_RDONLY);
                fdout = open(".f1", O_CREAT | O_WRONLY | O_TRUNC, 0777);
        }

        // if it's the first argument, read from stdin
        if(argument_number == 0)
                fdin = 0;

        // if it's the last argument, print the output to the shell
        if(argument_number == npipes)
                fdout = 1;

        // execute the command
        int childpid = execute(lpipe[argument_number], fdin, fdout);

        // don't close stdin or stdout
        if (argument_number != 0)
            close(fdin);
        if (argument_number != npipes) {
            close(fdout);
        }

        // wait for child process before continuing if it's the last command
        if (argument_number == npipes && childpid != -1) {
                int returnStatus;
                waitpid(childpid, &returnStatus, 0);
        }
}

/*
 * char *command_chain - string in between semicolons to be parsed
 *
 * splits on pipes, passes each argument in the pipe to handle_argument for interpretation
 */
static int handle_pipes(char **command_chain) {
        int i, arg_number, npipes;
        char **lpipe;
        while (command_chain[i]) {
                // "exit" case
                if (!strcmp("exit", command_chain[i])) {
                    return -1;
                }
                // "cd" case is handled in executor because we must split on spaces first
                npipes = count_tokens(command_chain[i], '|') - 1;
                lpipe = split(command_chain[i], '|');
                arg_number = 0;
                while (lpipe[arg_number]) {
                        handle_argument(arg_number, lpipe, npipes);
                        arg_number++;
                }
                i++;
        }
        return 1;
}

/*
 * infinite while loop that constantly reads in commands from the user
 * and splits on semicolons ';'
 */
static void run() {
	char buf[1000], **l;
	while(1){
		printf("> ");
		fgets(buf, sizeof buf, stdin);
		*strchr(buf, '\n') = 0;

		l = split(buf, ';');
                int sig = handle_pipes(l);
                if (sig == -1) {
                    break;
                }
	}
}

int main(){
        run();
        return 0;
}
