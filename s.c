#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char execute(char* r){
  f = fork();
  if (!f){
    char* c[256] = {0};
    c[0] = r;
    char* p = r-1;
    int i = 1;
    while(p = strchr(p+1, ' ')){
        c[i] = p+1;
        *p = 0;
        i++;
    }
    execvp(c[0], c);
    printf("Unknown Command");
    return 1;
  }
}

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

main(){
  while(1){
    char r[1000];
    printf("> ");
    fgets(r, sizeof r, stdin);
    *strchr(r, '\n') = 0;
    
    char* l[1000] = {0};
    l[0] = r;
    char* p = r-1;
    int i = 1;
    while(p = strchr(p+1, ';')){
        c[i] = p+1;
        *p = 0;
        i++;
    }
    
    int i;
    while(l[i])
      if (!strcmp(l[i], "exit")) exit(-1);
      if (!strcmp(l[i], "cd")) //chdir(path);
      if (strchr(r, ">") && strchr(r, "|")) execute(l[i]);
      if (!strchr(r, ">") && strchr(r, "|")) redirect(l[i]);
      i++;
    }
  }
}
