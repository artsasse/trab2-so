#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define N 64


int main(void)
{
   int status, id, j, child_id;
   //// Insira um comando para pegar o PID do processo corrente e mostre na
   //// tela da console.
   id = getpid();
   printf("\nPID: %d", id);

   int parent_buff[2];
   int child_buff[2];
   if (pipe(parent_buff) == -1) exit(3);
   if (pipe(child_buff) == -1) exit(3);
   
   child_id = fork();

   if (child_id) {
      // Faça com que o processo pai execute este trecho de código
      
      char *parent_message = "Hello, child!";
      char parent_buffer[N + 1];
      int parent_int_buffer;


      // Mostre na console o PID do processo pai e do processo filho
      printf("\nPID: %d - PID do Filho: %d", id, child_id);
      
      // Monte uma mensagem e a envie para o processo filho
      if(write(parent_buff[1], parent_message, strlen(parent_message)) == -1) exit(3);
   
      // Mostre na tela o texto da mensagem enviada 
      printf("\nMensagem enviada ao filho: %s", parent_message);

      // Aguarde a resposta do processo filho
      if(read(child_buff[0], parent_buffer, N) == -1) exit(3);
      parent_buffer[N] = 0;

      // Mostre na tela o texto recebido do processo filho
      printf("\nMensagem recebida pelo processo pai: %s", parent_buffer);

      // Aguarde mensagem do filho e mostre o texto recebido
      if(read(child_buff[0], &parent_int_buffer, sizeof(parent_int_buffer)) == -1) exit(3);
      printf("\nValor recebido pelo processo pai: %d", parent_int_buffer);

      // Aguarde o término do processo filho
      wait(&status);

      // Informe na tela que o filho terminou e que o processo pai também
      printf("\nProcesso filho terminou e o pai também");


      // vai encerrar
   } else {
      // Faça com que o processo filho execute este trecho de código
      char *child_message = "Hello, parent!";
      char child_buffer[N + 1];

      id = getpid();
      int parent_id = getppid();

      // Mostre na tela o PID do processo corrente e do processo pai
      printf("\nPID: %d - PID do Pai: %d", id, parent_id);

      // Aguarde a mensagem do processo pai e ao receber mostre o texto na tela
      if(read(parent_buff[0], child_buffer, N) == -1) exit(3);
      child_buffer[N] = 0;

      printf("\nMensagem recebida pelo processo filho: %s\n", child_message);

      // Envie uma mensagem resposta ao pai
      if(write(child_buff[1], child_message, strlen(child_message)) == -1) exit(3);

      // Execute o comando "for" abaixo
      for (j = 0; j <= 10000; j++);

      // Envie mensagem ao processo pai com o valor final de "j"
      if(write(child_buff[1], &j, sizeof(j)) == -1) exit(3);

      // Execute o comando abaixo e responda às perguntas
      execl("/Bin/ls", "ls", NULL);
      // O que acontece após este comando?
         /* 
            O programa tenta substituir o programa original do processo filho pelo programa do comando “ls”.
            Como a pasta "/Bin" não existe, essa tentativa gera um erro que faz
            o processo seguir com a execução do programa original.
         */

      // O que pode acontecer se o comando "execl" falhar?
         /*  
            O Processo segue com a execução do programa original. 
         */
   }
   exit(0);
}