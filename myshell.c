#include<sys/wait.h>
#include<sys/types.h> 
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define max 100
//Removing Spaces after Words
void trimming_spaces(char *input_str)
{
int i=0,j=0;
for(i=0;i<strlen(input_str);i++)
{
if(input_str[i]=='\n')
{
j=i;
while(j>=1 && input_str[j-1]==' ')
{
j--;
}
input_str[j]='\0';
}
}
}
//Seprating the Arguments
int sepratingArguments(char *input_str, char **token_str)
{
int i=0,j=0;
while(input_str[i]==' '){
i++;
}
token_str[j] = &input_str[i];
while(input_str[i]!='\0')
{
if(input_str[i]==' ')
{
input_str[i]='\0';
j++;
i++;//So won't have to check again from the index that  has been already visited
int k=i;
while(input_str[k]==' ')
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
return j;
}

//Display the Arguments
void Display(int j,char **token_str)
{
int count = j;
for(j=0;j<=count;j++)
{
printf("%s \n",token_str[j]);
}
}
int main()
{
int i=0,j=0,k=0;
char *token[max];
char input[max];
while(max>0){
printf("myshell>");
if(fgets(input,sizeof(input),stdin)==NULL)
break;
trimming_spaces(input);
k = sepratingArguments(input,token);
if(*token[0]=='\0')
continue;
Display(k,token);
if(strcmp(token[0],"exit")==0)
break;
pid_t pid = fork();
if(pid<0)
{
perror("fork failed");
break;
}
else if(pid==0)
{
execvp(token[0],token);
perror("wrong command");
break;
}
else
{
int status;
waitpid(pid,&status,0);
}
}
return 0;
}
