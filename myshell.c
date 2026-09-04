#include<stdio.h>
#include<string.h>
int main(){
char input[100];
int i;
do{
printf("myshell>");
fgets(input,sizeof(input),stdin);
for(i=0;i<strlen(input);i++){
if(input[i]=='\n'){
int j = i;
while(input[j-1]==' '){
j--;
}
input[j]='\0';
}
}
printf("%s\n",input);
}while(strcmp(input,"exit"));
return 0;
}
