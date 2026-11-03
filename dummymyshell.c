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
if(strcmp(token[i],">")==0)
{
if(token[i+1]==NULL)
{
printf("Error, Expecting a command after > ");
exit(1);
}
int desc = open(token[i+1], O_WRONLY | O_CREAT | O_TRUNC , 0644);
if(desc==-1)
{
perror("open");
exit(1);
}
dup2(desc,1);
close(desc);
int j = i; // Start at the > index
while (token[j+2] != NULL) {
    token[j] = token[j+2];
    j++;
}
token[j] = NULL;
}
i++;
}
}
//Main Function
int main()
{
char *token[max];
char input[max];
while(1){
printf("\nmyshell> ");
fflush(stdout);
if(fgets(input,sizeof(input),stdin)==NULL)
break;
trimming_spaces(input);
sepratingArguments(input,token);
if(token[0]==NULL)
continue;
if(strcmp(token[0],"exit")==0)
break;
if(isbuiltin(token)==1)
{
execute_builtin(token);
continue;
}
pid_t pid = fork();
if(pid<0)
{
perror("fork failed");
continue;
}
else if(pid==0)
{
remakingcommand(token);
execvp(token[0],token);
perror("wrong command");
exit(1);
}
else
{
int status;
waitpid(pid,&status,0);
}
}
return 0;
}
