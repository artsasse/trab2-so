#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

// Constante para armazenar o tamanho do comando
#define TAM 20

int main(void) {
    // Váriável para armazenar o comando passado
    char command[TAM];

    // Enquanto não é passado "exit"
    while (1) {

        // Lê um comando da entrada
        scanf("%s", command);

        // Se for lido um exit, termina o programa
        if (strcmp(command, "exit") == 0)
            return 0;

        // Executa um fork para criar um novo processo
        int ret = fork();

        // Se ret == 0 então é o processo filho
        if (ret == 0) {
            // Cria uma nova cadeia de caracteres com o "/bin/"
            char path[TAM + 5] = "/bin/";
            // Concatena o comando no path criado
            strcat(path, command);

            // Realiza a execução do comando
            execl(path, command, 0);

            // Se a execução falhar, retorna um erro
            exit(1);

        } else {
            // Variável para armazenar o status do filho
            int status;

            // Processo pai espera pelo filho e guarda o status do filho
            waitpid(ret, &status, 0);
            // Guarda o código de retorno do exit()
            int ret_code = WEXITSTATUS(status);

            // Caso o código de retorno seja 0 ou o comando passado é o exit 
            if (ret_code == 0 || strcmp(command, "exit") == 0) 
                printf("Executado com sucesso.\n");
            else
                printf("Código de retorno = %d\n", ret_code);
        }
    }
    return 0;
}