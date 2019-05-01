#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

//Defining encryption vars
#define KEY 5
#define SHAKE 2

void encrypt(char *temp);

int main(void){

  pid_t pid, sid;

  pid = fork();
  if(pid < 0){
    exit(EXIT_FAILURE);
  }

  if(pid > 0){
    exit(EXIT_SUCCESS);
  }

  umask(0);

  //open logs here
  openlog("slog", LOG_PID|LOG_CONS, LOG_USER);

  sid = setsid();
  if(sid < 0){
    exit(EXIT_FAILURE);
  }

  if((chdir("/")) < 0){
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1){
    
    syslog(LOG_INFO, "Log Intrusion Detection: Start");
    system("tcpdump -n -c 10 -x > /etc/log");
    system("python3 /etc/flagData.py");
    encrypt("/var/www/html/ipTable");
    encrypt("/var/www/html/dataTable");
    sleep(15);
  }

  exit(EXIT_SUCCESS);
}

//Simple encryption method
void encrypt(char *IPfile){

  FILE *IP;
  IP = fopen(IPfile, "rw");

  FILE *temp;
  temp = fopen("/var/www/html/temp.txt", "w");

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
  temp = fopen("/var/www/html/temp.txt", "r");

  while(fgets(str, 25, temp)){

    len = strlen(str);

    //Remove New Line
    if(len > 0 && str[len-1] == '\n'){
      str[len-1] = 0;
    }

    fprintf(IP, "%s\n", str);
  }

  fclose(temp);
  remove("/var/www/html/temp.txt");
  fclose(IP);
}





