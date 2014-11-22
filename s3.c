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
        l[i] = p+1;
        *p = 0;
        i++;
    }
    
    i = 0;
    while(l[i]){
     char* p = l+i;
     char currentOutput[1000] = {0};
     currentOuput = execute(SUBSTRING(p, strchr(p, "|")));
     while(strchr(p, "|")){
      currentOutput = pipe(currentOutput, SUBSTRING(strchr(p, "|")+1, strchr(strchr(p, "|"), "|")));
      p = strchr(p, "|")+1;
      }
    printf("%s\n", currentOutput);
    }
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
    
    i = 0;
    while(l[i]){
     char p = l[i];
     char currentOutput[1000] = {0};
     
     if (strchr(p, "|") && !strchr(p, ">") || strchr(p, "|") && strchr(p, ">") && strchr(p, "|") < strchr(p, ">")){
      currentOuput = execute(SUBSTRING(p, strchr(p, "|")));
     }
     if (strchr(p, ">") && !strchr(p, "|") || strchr(p, ">") && strchr(p, "|") && strchr(p, ">") < strchr(p, "|")){
      currentOuput = execute(SUBSTRING(p, strchr(p, ">")));
     }
     
     while(strchr(p, "|")){
      if (strchr(p, "|") && !strchr(p, ">") || strchr(p, "|") && strchr(p, ">") && strchr(p, "|") < strchr(p, ">")){
        currentOutput = pipe(currentOutput, SUBSTRING(strchr(p, "|")+1, strchr(strchr(p, "|"), "|")));
        p = strchr(p, "|")+1;
      } 
      if (strchr(p, ">") && !strchr(p, "|") || strchr(p, ">") && strchr(p, "|") && strchr(p, ">") < strchr(p, "|")){
        currentOutput = redirect(currentOutput, SUBSTRING(strchr(p, "|")+1, strchr(strchr(p, "|"), "|")));
        p = strchr(p, ">")+1;
      }
      }
    printf("%s\n", currentOutput);
    }
}


have not tested
