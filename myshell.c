#include<stdio.h>
#include<string.h>
int main(){
char input[100];
int i=0,j=0;
//Shell continous running loop
do{
printf("myshell>");
fgets(input,sizeof(input),stdin);
for(i=0;i<strlen(input);i++){
// trimming out the spaces after words
if(input[i]=='\n'){
j = i;
while(input[j-1]==' '){
j--;
}
input[j]='\0';
}
}
//Seprating the arguments
char *token[10];
i=0;
j=0;
token[j]=&input[i];
while(input[i]!='\0'){
if(input[i]==' '){
input[i]='\0';
j++;
i++;//so that k won't have to check from exact index where we ended
int k = i;
while(input[k]==' '){
k++;
}
token[j]=&input[k];
i=k;
continue;
}
i++;
}
//Displaying the arguments
int count = j;
for(j=0;j<=count;j++){
printf("%s\n",token[j]);}
}while(strcmp(input,"exit"));
return 0;
}
