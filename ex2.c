#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   int ret;
   ret = fork();
   if (ret == 0)
      execl("/bin/ls","ls",0);
   else
      printf("Processo continua executando.\n");
}

