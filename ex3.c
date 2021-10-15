#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   int ret;
   ret = fork();
   if (ret == 0) {
      execl("/bin/ls","ls",0);
      printf("Quando este comando será executado ? \n"); 
   }
   printf("Por que a função printf anterior não foi executada?\n");
}

