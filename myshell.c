#include<stdio.h>
#include<string.h>
#define max 100
int i=0;
int j=0;
char *token[max];
char input[max];
//Removing Spaces after Words
void trimming_spaces(char *input_str)
{
for(i=0;i<strlen(input);i++)
{
if(input[i]=='\n')
{
j=i;
while(j>=1 && input[j-1]==' ')
{
j--;
}
input[j]='\0';
}
}
}
//Seprating the Arguments
void sepratingArguments(char *input_str)
{
i=0;
j=0;
token[j] = &input[i];
while(input[i]!='\0')
{
if(input[i]==' ')
{
input[i]='\0';
j++;
i++;//So won't have to check again from the index that  has been already visited
int k=i;
while(input[k]==' ')
{
k++;
}
token[j]=&input[k];
i=k;
continue;
}
i++;
}
}
//Display the Arguments
void Display()
{
int count = j;
for(j=0;j<=count;j++)
{
printf("%s \n",token[j]);
}
}
int main()
{
do{
printf("myshell>");
fgets(input,sizeof(input),stdin);
trimming_spaces(input);
sepratingArguments(input);
Display();
}while(strcmp(input,"exit"));
return 0;
}

