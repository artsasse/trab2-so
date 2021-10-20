#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    size_t input_size = 4;
    char* word;
    char* input = (char*) malloc(input_size * sizeof(char));
    char** command = (char**) malloc(input_size * sizeof(char*));

    while(1) {
        // Lê um comando da entrada
        getline(&input, &input_size, stdin);

        // Se o comando for um \n, será ignorado
        if (strcmp(input, "\n") == 0)
            continue;

        /* Bloco de código que retira espaços e quebra de linha do input
            e salva as palavras encontradas na array de comandos */
        int i = 0;
        word = strtok(input, "\n ");
        while (word != NULL) {
            command[i++] = word;
            word = strtok(NULL, "\n ");
        }
        command[i] = NULL;

        // Se o valor passado como comando foi um exit, termina o programa
        if (strcmp(command[0], "exit") == 0)
            return 0;

        // Executa um fork para criar um novo processo
        int ret = fork();

        // Se ret == 0 então é o processo filho
        if (ret == 0) {
            // execvp precisa apenas do comando e seus argumentos
            execvp(command[0], command);

            // Se a execução falhar, retorna um erro
            exit(1);

        } else {
            // Variável para armazenar o status do filho
            int status;

            // Processo pai espera pelo filho e guarda o status do filho
            waitpid(ret, &status, 0);
            // Guarda o código de retorno do exit()
            int ret_code = WEXITSTATUS(status);

            if (ret_code == 0)
                printf("Executado com sucesso.\n");
            else
                printf("Código de retorno = %d\n", ret_code);
        }
    }

    free(input);
    free(command);

    return 0;
}
