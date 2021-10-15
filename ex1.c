#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
   int ret1, ret2;
   ret1 = fork();
   ret2 = fork();
   printf("Programa em execução.\n");
}

