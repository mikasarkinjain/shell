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
     char currentOutput[1000];
     char firstPipe = 1;
     while(strchr(p, "|")){
      if (firstPipe){
       currentOutput = execute(SUBSTRING(p, strchr(p, "|")-1));
       firstPipe = 1;
      }
      else {
       pipe(currentOutput, _______________)
      }
      p = strchr(p, ">");
    }
  }
}
