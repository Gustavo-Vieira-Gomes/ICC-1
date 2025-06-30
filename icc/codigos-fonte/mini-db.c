#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_SIZE 200

typedef struct
{
    int id;
    char login[16], password[31], gender;
    double salary;
} Registry;

void read_file(char *filename, Registry ***registries_output, int *registries_count_output)
// recebe um ponteiro do tipo Registry, um ponteiro para o numero de registros e o nome do arquivo. Lê o arquivo, aloca apenas a memória necessária para armazenar os registros lidos, aponta o ponteiro de registros para o array de registros criado e altera a quantidade de registros lidos
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Contar quantos caracteres tem o arquivo (Ir até o final)
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file);
    rewind(file);

    // Ler todo o arquivo em uma string
    char *buffer = malloc(file_size + 1);
    size_t bytes_read = fread(buffer, 1, file_size, file);
    buffer[bytes_read] = '\0'; // Garantir que é uma string adicionando o \0 no final
    fclose(file);

    // Contar quantos objetos já vieram cadastrados no banco de dados
    int counter = 0;
    for (int i = 0; i < bytes_read; i++)
    {
        if (buffer[i] == '{')
        {
            counter++;
        }
    }

    *registries_output = (Registry **)malloc(sizeof(Registry *) * counter);

    for (int i = 0; i < counter; i++)
    {
        (*registries_output)[i] = (Registry *)malloc(sizeof(Registry));
        if (!(*registries_output)[i])
        {
            perror("Erro ao alocar memória");
            exit(1);
        }
    }

    if (!*registries_output)
    {
        perror("Erro ao alocar memória");
        exit(1);
    }

    int i = 0;
    char *pointer = buffer;

    // Inicio da leitura dos registros existentes no arquivo (Passar pelo arquivo salvando os dados no vetor de registros)
    while ((pointer = strstr(pointer, "{")) != NULL)
    {
        if (i >= counter)
            break; // segurança (não ultrapassa a contagem de registros contada inicialmente)

        char *end = strstr(pointer, "}");
        if (!end)
            break; // segurança (Confere se o objeto está completo no arquivo, com abertura e fechamento de chaves)

        // Navega até "login"
        char *login_field = strstr(pointer, "\"login\"");
        if (login_field && login_field < end)
        {
            sscanf(login_field, "\"login\": \"%15[^\"]\"", (*registries_output)[i]->login); // Salva o login no vetor Obs: leitura formatada, para salvar sem as aspas
        }

        // O mesmo se aplica para as demais leituras. Primeiro se navega até o campo desejado, e depois se extrai o valor do campo através de sscanf para salvar no tipo correto e evitar as ""
        char *password_field = strstr(pointer, "\"password\"");
        if (password_field && password_field < end)
        {
            sscanf(password_field, "\"password\": \"%30[^\"]\"", (*registries_output)[i]->password);
        }

        char *gender_field = strstr(pointer, "\"gender\"");
        if (gender_field && gender_field < end)
        {
            sscanf(gender_field, "\"gender\": \"%c\"", &(*registries_output)[i]->gender);
        }

        char *salary_field = strstr(pointer, "\"salary\"");
        if (salary_field && salary_field < end)
        {
            sscanf(salary_field, "\"salary\": %lf", &(*registries_output)[i]->salary);
        }

        char *id_field = strstr(pointer, "\"id\"");
        if (id_field && id_field < end)
        {
            sscanf(id_field, "\"id\": %d", &(*registries_output)[i]->id);
        }

        pointer = end + 1; // avança para o próximo objeto
        i++;
    }
    // Devolve o vetor de registros e a quantidade de registros lidos
    *registries_count_output = i;
    printf("%d registro(s) lido(s).\n", i);
}

void print_registry(Registry registry)
// recebe um registro e printa o mesmo no terminal com a formatacão correta
{
    printf("{\n");
    printf("    \"id\": %d,\n", registry.id);
    printf("    \"login\": \"%s\",\n", registry.login);
    printf("    \"password\": \"%s\",\n", registry.password);
    printf("    \"gender\": \"%c\",\n", registry.gender);
    printf("    \"salary\": %.2f\n", registry.salary);
    printf("}\n");
}

void create_registry(Registry ***registries, int *registries_count, char *line)
// Recebe a linha de comando digitada pelo usuário, faz a leitura destas através de sscanf para extrair sem as "" e no tipo correto, verifica se há algum espaço vazio dentro do vetor alocado, e se houver, adiciona o novo registro, se não houver, aumenta o vetor (Caso não tenha chegado ao limite) e adiciona o novo registro
{
    Registry new_registry;
    int operation, empty_space_found = 0;
    sscanf(line, "%d %d \"%15[^\"]\" \"%30[^\"]\" \"%c\" %lf", &operation, &new_registry.id, new_registry.login, new_registry.password, &new_registry.gender, &new_registry.salary);

    for (int i = 0; i < *registries_count; i++)
    {
        if ((*registries)[i] == NULL)
        {
            (*registries)[i] = malloc(sizeof(Registry));
            if (!(*registries)[i])
            {
                perror("Erro ao alocar memória");
                exit(1);
            }
            *((*registries)[i]) = new_registry;
            empty_space_found = 1;
            break;
        }
    }

    if (!empty_space_found)
    {
        if (*registries_count == 1000)
        {
            printf("Sem espaço para inserção.\n");
        }
        else
        {

            *registries = realloc(*registries, sizeof(Registry *) * (*registries_count + 1));
            (*registries)[*registries_count] = (Registry *)malloc(sizeof(Registry));
            if (!(*registries)[*registries_count])
            {
                perror("Erro ao alocar memória");
                exit(1);
            }
            *(*registries)[*registries_count] = new_registry;
            (*registries_count)++;
            printf("Registro inserido.\n");
        }
    }
    else
    {
        printf("Registro inserido.\n");
    }
}

void find_registry(Registry **registries, int registries_count, char *line)
// Recebe o vetor de registros, a quantidade de registros e a linha de comando digitada pelo usuário. Identifica o filtro de pesquisa desejada, e percorre o vetor de registros procurando o que foi solicitado pelo usuário
{
    char search_field[11], search_value[31];
    int found = 0, operation;

    sscanf(line, "%d \"%10[^\"]\" %30s", &operation, search_field, search_value);

    if (strcmp(search_field, "id") == 0)
    {
        int id = atoi(search_value);
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i] != NULL)
            {
                if (registries[i]->id == id)
                {
                    print_registry(*registries[i]);
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "login") == 0)
    {
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i] != NULL)
            {
                if (strcmp(registries[i]->login, search_value) == 0)
                {
                    print_registry(*registries[i]);
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "password") == 0)
    {
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i] != NULL)
            {
                if (strcmp(registries[i]->password, search_value) == 0)
                {
                    print_registry(*registries[i]);
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "gender") == 0)
    {
        char gender;
        sscanf(search_value, "\"%c", &gender);
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i] != NULL)
            {
                if (registries[i]->gender == gender)
                {
                    print_registry(*registries[i]);
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "salary") == 0)
    {
        double salary = atof(search_value);
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i] != NULL)
            {
                if (registries[i]->salary == salary)
                {
                    print_registry(*registries[i]);
                    found = 1;
                }
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else
    {
        printf("Nada encontrado.\n");
    }
}

void delete_registry(Registry ***registries, int *registries_count_pointer, char *line)
// Recebe o array de registros, um ponteiro para o número de registros e a linha digitada pelo usuário. Identifica o filtro de deleção desejado e desaloca a memoria dos registros que foram deletados, setando seu ponteiro para NULL depois
{
    char search_field[11], search_value[31];
    int found = 0, deleted_count = 0, operation;

    sscanf(line, "%d \"%10[^\"]\" %30s", &operation, search_field, search_value);

    if (strcmp(search_field, "id") == 0)
    {
        int id = atoi(search_value);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if ((*registries)[read_index] != NULL)
            {
                if ((*registries)[read_index]->id == id)
                {
                    free((*registries)[read_index]);
                    (*registries)[read_index] = NULL;
                    found = 1;
                    deleted_count++;
                }
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }

    else if (strcmp(search_field, "login") == 0)
    {
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if ((*registries)[read_index] != NULL)
            {
                if (strcmp((*registries)[read_index]->login, search_value) == 0)
                {
                    free((*registries)[read_index]);
                    (*registries)[read_index] = NULL;
                    found = 1;
                    deleted_count++;
                }
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else if (strcmp(search_field, "password") == 0)
    {
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if ((*registries)[read_index] != NULL)
            {
                if (strcmp((*registries)[read_index]->password, search_value) == 0)
                {
                    free((*registries)[read_index]);
                    (*registries)[read_index] = NULL;
                    found = 1;
                    deleted_count++;
                }
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else if (strcmp(search_field, "gender") == 0)
    {
        char gender;
        sscanf(search_value, "\"%c", &gender);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if ((*registries)[read_index] != NULL)
            {
                if ((*registries)[read_index]->gender == gender)
                {
                    free((*registries)[read_index]);
                    (*registries)[read_index] = NULL;
                    found = 1;
                    deleted_count++;
                }
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else if (strcmp(search_field, "salary") == 0)
    {
        double salary = atof(search_value);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if ((*registries)[read_index] != NULL)
            {
                if ((*registries)[read_index]->salary == salary)
                {
                    free((*registries)[read_index]);
                    (*registries)[read_index] = NULL;
                    found = 1;
                    deleted_count++;
                }
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else
    {
        printf("Remoção inválida.\n");
    }

    if (found)
    {
        printf("%d registro(s) removido(s).\n", deleted_count);
    }
}

int main()
{
    char filename[256], *line, *line_helper, line_copy[LINE_SIZE];
    Registry **registries = NULL;
    int registries_count = 0, operation;

    scanf("%255s", filename); // Lê o nome do arquivo de entrada
    getchar();

    read_file(filename, &registries, &registries_count); // Chama a função de leitura de arquivo, passando os respectivos parâmetros

    line = malloc(sizeof(char) * LINE_SIZE); // Aloca memória necessária para armazenar a linha de comando do usuário

    while (fgets(line, LINE_SIZE, stdin)) // Permanece lendo os comandos do usuário até encontrar um eof (End of file)
    {
        strcpy(line_copy, line); // Cópia da linha de comando para uma string auxiliar para obter a operação sem ter problema com strtok futuros
        line_helper = strtok(line_copy, " ");
        operation = atoi(line_helper);
        switch (operation)
        {
        case 1:
            create_registry(&registries, &registries_count, line); // Passa o array de registros, um ponteiro para a quantidade de registros e a linha de comando do usuário
            break;
        case 2:
            find_registry(registries, registries_count, line); // Passa o array de registros, a quantidade de registros e a linha de comando do usuário
            break;
        case 3:
            delete_registry(&registries, &registries_count, line); // Passa o array de registros, um ponteiro para a quantidade de registros e a linha de comando do usuário
            break;
        default:
            printf("Operação não reconhecida\n");
            break;
        }
    }

    // Libera a memória dinâmicamente alocada
    for (int i = 0; i < registries_count; i++)
    {
        free(registries[i]);
    }
    free(registries);
    free(line);
    return 0;
}
