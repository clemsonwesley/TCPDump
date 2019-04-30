#include<string.h>
#include<stdio.h>
#include<stdlib.h>


#define KEY 5
#define SHAKE 2

void encrypt(char *IPfile){

  FILE *IP;
  IP = fopen(IPfile, "rw");

  FILE *temp;
  temp = fopen("temp.txt", "w");

  int len;
  int i;
  int x;
  char str[25];

  while(fgets(str, 25, IP)){
     
    len = strlen(str);

    //Remove New Line
    if(len > 0 && str[len-1] == '\n'){
      str[len-1] = 0;
    }

   //Encrypt
   for(i=0; i<len; i++){
     x = str[i] - '0';
     x += KEY;
     str[i] = x + '0';     
   }
   fprintf(temp, "%s\n", str);
  
  /*
  //Decrypt
  for(i=0; i<len; i++){
     x = str[i] - '0';
     x -= KEY;
     str[i] = x + '0';
   } 
   printf("%s\n", str);
  }
  */

  }
  fclose(IP);
  fclose(temp);
  IP = fopen(IPfile, "w");
  temp = fopen("temp.txt", "r");
  
  while(fgets(str, 25, temp)){

    len = strlen(str);

    //Remove New Line
    if(len > 0 && str[len-1] == '\n'){
      str[len-1] = 0;
    }

    fprintf(IP, "%s\n", str);
  }

  fclose(temp);
  remove("temp.txt");
  fclose(IP);
}




int main(void){

  encrypt("flaggedIPs2.txt");

  return 0;
}
