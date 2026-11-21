#include<sys/wait.h>
#include<sys/types.h>
#include<stdio.h>
#include<fcntl.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#define max 100
//Removing Spaces after Words
void trimming_spaces(char *input_str)
{
int j=((int)strlen(input_str))-1;
for(int i= j;i>=0;i--)
{
if(isspace((unsigned char)input_str[i]))
{
input_str[i]='\0';
}
else
break;
}
}
//Seprating the Arguments
void sepratingArguments(char *input_str, char **token_str)
{
int i=0,j=0;
while(isspace(input_str[i])){
i++;
}
token_str[j] = &input_str[i];
while(input_str[i]!='\0')
{
if(isspace(input_str[i]))
{
input_str[i]='\0';
j++;
i++;//So won't have to check again from the index that  has been already visited
int k=i;
while(isspace(input_str[k]))
{
k++;
}
token_str[j]=&input_str[k];
i=k;
continue;
}
i++;
}
if(*token_str[0]=='\0')
token_str[0]=NULL;
else
token_str[j+1]=NULL;
}
//Checking for built-in commands
int isbuiltin(char **token_str)
{
if(strcmp(token_str[0],"cd")==0||strcmp(token_str[0],"pwd")==0)
return 1;
else
return 0;
}
//Executing the built-in functions
void execute_builtin(char **token)
{
char cwd[1024], *home_path;
if(strcmp(token[0],"pwd")==0)
{
if(getcwd(cwd,sizeof(cwd))==NULL)
perror("pwd");
else
printf("%s\n",cwd);
}
else if(strcmp(token[0],"cd")==0)
{
if(token[1]!=NULL){
if(chdir(token[1])==-1)
perror("cd");
}
else
{
home_path=getenv("HOME");
if(home_path!=NULL)
{
if(chdir(home_path)==-1)
perror("cd");
}
else
printf("home not set");
}
}
}
//Checking command for redirection
void remakingcommand(char **token)
{
int i=0;
while(token[i]!=NULL)
{
if(strcmp(token[i],">")==0||strcmp(token[i],">>")==0||strcmp(token[i],"<")==0)
{
int desc;
if(token[i+1]==NULL)
{
printf("Error,command not complete ");
exit(1);
}
if(strcmp(token[i],">")==0)
desc = open(token[i+1], O_WRONLY | O_CREAT | O_TRUNC , 0644);
else if(strcmp(token[i],">>")==0)
desc = open(token[i+1], O_WRONLY | O_CREAT | O_APPEND , 0644);
else
desc = open(token[i+1], O_RDONLY);
if(desc==-1)
{
perror("open");
exit(1);
}
if(strcmp(token[i],"<")==0)
dup2(desc,0);
else
dup2(desc,1);
close(desc);
int j = i; // Start at the > index
while (token[j+2] != NULL) {
    token[j] = token[j+2];
    j++;
}
token[j] = NULL;
continue;
}
i++;
}
}
//checking for pipes
int pipecheck(char **token,char ***pipedtoken)
{
int i = 0, j = 0;
pipedtoken[j]=&token[i];
while(token[i]!=NULL)
{
if(token[i+1]!=NULL)
{
if(strcmp(token[i],"|")==0 && strcmp(token[i+1],"|")==0)
{
return 0;
}
}
if(strcmp(token[i],"|")==0)
{
token[i]=NULL;
j++;
pipedtoken[j]=&token[i+1];
i=i+1;
continue;
}
i++;
}
pipedtoken[j+1]=NULL;
return j+1;
}
//Main Function
int main()
{
char *token[max];
char input[max];
char **pipedtoken[max];
while(1){
printf("\nmyshell> ");
fflush(stdout);
if(fgets(input,sizeof(input),stdin)==NULL)
break;
trimming_spaces(input);
sepratingArguments(input,token);
if(token[0]==NULL)
continue;
if(strcmp(token[0],"exit")==0 && token[1] == NULL)
break;
else if(strcmp(token[0],"exit")==0 && token[1] != NULL)
{
perror("wrong command");
continue;
}
if(isbuiltin(token)==1)
{
execute_builtin(token);
continue;
}
int x = pipecheck(token,pipedtoken);
if(x == 0){
printf("Error in the given command");
continue;
}
if(x == 1){
pid_t pid = fork();
if(pid<0)
{
perror("fork failed");
continue;
}
else if(pid==0)
{
remakingcommand(pipedtoken[0]);
execvp(pipedtoken[0][0],pipedtoken[0]);
perror("wrong command");
exit(1);
}
else
{
int status;
waitpid(pid,&status,0);
}
}
else{
int y = 0, pipefd[x-1][2];
pid_t pid[x];
for(y = 0;y < x-1; y++)
{
pipe(pipefd[y]);
}
for(y=0;y<x;y++)
{
pid[y] = fork();
if(pid[y]<0)
{
perror("fork failed");
continue;
}
else if(pid[y]==0)
{
if(y>0){
dup2(pipefd[y-1][0],0);
}
if(y<(x-1))
{
dup2(pipefd[y][1],1);
}
for(int z=0; z < x-1;z++){
close(pipefd[z][0]);
close(pipefd[z][1]);
}
remakingcommand(pipedtoken[y]);
execvp(pipedtoken[y][0],pipedtoken[y]);
perror("wrong command");
exit(1);
}
}
for(y=0;y<x-1;y++){
close(pipefd[y][0]);
close(pipefd[y][1]);
}
int status;
for(y=0;y<x;y++){
waitpid(pid[y],&status,0);
}
}
}
return 0;
}
