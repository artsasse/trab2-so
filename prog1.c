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
   printf("PID: %d\n", id);

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
      printf("PID: %d - PID do Filho: %d\n", id, child_id);
      
      // Monte uma mensagem e a envie para o processo filho
      if(write(parent_buff[1], parent_message, strlen(parent_message)) == -1) exit(3);
   
      // Mostre na tela o texto da mensagem enviada 
      printf("Mensagem enviada ao filho: %s\n", parent_message);

      // Aguarde a resposta do processo filho
      if(read(child_buff[0], parent_buffer, N) == -1) exit(3);
      parent_buffer[N] = 0;

      // Mostre na tela o texto recebido do processo filho
      printf("Mensagem recebida pelo processo pai: %s\n", parent_buffer);


      // Envia o aviso de lido
      if(write(parent_buff[1], "ping", strlen("ping")) == -1) exit(3);

      // Aguarde mensagem do filho e mostre o texto recebido
      if(read(child_buff[0], &parent_int_buffer, sizeof(int)) == -1) exit(3);
      printf("Valor recebido pelo processo pai: %d\n", parent_int_buffer);

      // Aguarde o término do processo filho
      wait(&status);

      close(parent_buff[0]);
      close(parent_buff[1]);

      // Informe na tela que o filho terminou e que o processo pai também
      printf("Processo filho terminou e o pai também\n");
      // vai encerrar

   } else {
      // Faça com que o processo filho execute este trecho de código
      char *child_message = "Hello, parent!";
      char child_buffer[N + 1];

      id = getpid();
      int parent_id = getppid();

      // Mostre na tela o PID do processo corrente e do processo pai
      printf("PID: %d - PID do Pai: %d\n", id, parent_id);

      // Aguarde a mensagem do processo pai e ao receber mostre o texto na tela
      if(read(parent_buff[0], child_buffer, N) == -1) exit(3);
      child_buffer[N] = 0;

      printf("Mensagem recebida pelo processo filho: %s\n", child_buffer);

      // Envie uma mensagem resposta ao pai
      if(write(child_buff[1], child_message, strlen(child_message)) == -1) exit(3);

      // Aguardando o aviso de que o pai leu a última mensagem
      if(read(parent_buff[0], child_buffer, N) == -1) exit(3);

      // Execute o comando "for" abaixo
      for (j = 0; j <= 10000; j++);

      // Envie mensagem ao processo pai com o valor final de "j"
      if(write(child_buff[1], &j, sizeof(int)) == -1) exit(3);

      close(child_buff[0]);
      close(child_buff[1]);

      // Execute o comando abaixo e responda às perguntas
      execl("/bin/ls", "ls", NULL);
      // O que acontece após este comando?
         /* 
            Respondido no relatório.
         */

      // O que pode acontecer se o comando "execl" falhar?
         /*  
            Respondido no relatório.
         */
   }
   exit(0);
}