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

void read_file(char *filename, Registry **registries_output, int *registries_count_output)
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

    Registry *registries = malloc(counter * sizeof(Registry)); // Alocar apenas a memória necessária para armazenar todos os registros iniciais (Inserções terão seu espaço alocado através de realloc) 
    if (!registries)
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
            sscanf(login_field, "\"login\": \"%15[^\"]\"", registries[i].login); // Salva o login no vetor Obs: leitura formatada, para salvar sem as aspas
        }

        // O mesmo se aplica para as demais leituras. Primeiro se navega até o campo desejado, e depois se extrai o valor do campo através de sscanf para salvar no tipo correto e evitar as ""
        char *password_field = strstr(pointer, "\"password\"");
        if (password_field && password_field < end)
        {
            sscanf(password_field, "\"password\": \"%30[^\"]\"", registries[i].password);
        }

        char *gender_field = strstr(pointer, "\"gender\"");
        if (gender_field && gender_field < end)
        {
            sscanf(gender_field, "\"gender\": \"%c\"", &registries[i].gender);
        }

        char *salary_field = strstr(pointer, "\"salary\"");
        if (salary_field && salary_field < end)
        {
            sscanf(salary_field, "\"salary\": %lf", &registries[i].salary);
        }

        char *id_field = strstr(pointer, "\"id\"");
        if (id_field && id_field < end)
        {
            sscanf(id_field, "\"id\": %d", &registries[i].id);
        }

        pointer = end + 1; // avança para o próximo objeto
        i++;
    }

    // Devolve o vetor de registros e a quantidade de registros lidos
    *registries_output = registries;
    *registries_count_output = i;
    printf("%d registro(s) lido(s)\n", i);
}

void print_registry(Registry registry)
// recebe um registro e printa o mesmo no terminal com a formatacão correta
{
    printf("{\n");
    printf("  \"id\": %d,\n", registry.id);
    printf("  \"login\": \"%s\",\n", registry.login);
    printf("  \"password\": \"%s\",\n", registry.password);
    printf("  \"gender\": \"%c\",\n", registry.gender);
    printf("  \"salary\": %.2f\n", registry.salary);
    printf("}\n");
}

Registry create_registry(char *line)
// Recebe a linha de comando digitada pelo usuário, percorre os cada palavra atraves de strtok, faz a leitura destas através de sscanf para extrair sem as "" e no tipo correto, salva numa struct e a retorna
{
    Registry new_registry;

    char *line_helper = strtok(line, " ");
    int operation = atoi(line_helper);

    line_helper = strtok(NULL, " ");
    new_registry.id = atoi(line_helper);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "\"%15[^\"]", new_registry.login);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "\"%30[^\"]", new_registry.password);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "\"%c", &new_registry.gender);

    line_helper = strtok(NULL, " ");
    new_registry.salary = atof(line_helper);

    return new_registry;
}

void find_registry(Registry *registries, int registries_count, char *line)
// Recebe o vetor de registros, a quantidade de registros e a linha de comando digitada pelo usuário. Identifica o filtro de pesquisa desejada, e percorre o vetor de registros procurando o que foi solicitado pelo usuário
{
    char search_field[11], search_value[31];
    int found = 0;

    char *line_helper = strtok(line, " ");
    int db_operation = atoi(line_helper);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "\"%10[^\"]", search_field);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "%30s", search_value);

    if (strcmp(search_field, "id") == 0)
    {
        int id = atoi(search_value);
        for (int i = 0; i < registries_count; i++)
        {
            if (registries[i].id == id)
            {
                print_registry(registries[i]);
                found = 1;
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "login") == 0)
    {
        char login[16];
        sscanf(search_value, "\"%15[^\"]", login);
        for (int i = 0; i < registries_count; i++)
        {
            if (strcmp(registries[i].login, login) == 0)
            {
                print_registry(registries[i]);
                found = 1;
            }
        }
        if (!found)
        {
            printf("Nada encontrado.\n");
        }
    }
    else if (strcmp(search_field, "password") == 0)
    {
        char password[31];
        sscanf(search_value, "\"%30[^\"]", password);
        for (int i = 0; i < registries_count; i++)
        {
            if (strcmp(registries[i].password, password) == 0)
            {
                print_registry(registries[i]);
                found = 1;
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
            if (registries[i].gender == gender)
            {
                print_registry(registries[i]);
                found = 1;
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
            if (registries[i].salary == salary)
            {
                print_registry(registries[i]);
                found = 1;
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

void delete_registry(Registry *registries, int *registries_count_pointer, char *line)
// Recebe o array de registros, um ponteiro para o número de registros e a linha digitada pelo usuário. Identifica o filtro de deleção desejado e filtra o vetor com base nisso. Por fim, realoca a memória para utilizar apenas a memória necessária, altera o ponteiro de registros para o novo array e atualiza o número de registros
{
    char search_field[11], search_value[31];
    int found = 0, write_index = 0, deleted_count = 0;

    char *line_helper = strtok(line, " ");
    int db_operation = atoi(line_helper);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "\"%10[^\"]", search_field);

    line_helper = strtok(NULL, " ");
    sscanf(line_helper, "%30s", search_value);

    if (strcmp(search_field, "id") == 0)
    {
        int id = atoi(search_value);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if (registries[read_index].id != id)
            {
                registries[write_index++] = registries[read_index];
            } else {
                found = 1;
                deleted_count++;
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else if (strcmp(search_field, "login") == 0)
    {
        char login[16];
        sscanf(search_value, "\"%15[^\"]", login);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if (strcmp(registries[read_index].login, login) != 0)
            {
                registries[write_index++] = registries[read_index];
            } else {
                found = 1;
                deleted_count++;
            }
        }
        if (!found)
        {
            printf("Remoção inválida.\n");
        }
    }
    else if (strcmp(search_field, "password") == 0)
    {
        char password[31];
        sscanf(search_value, "\"%30[^\"]", password);
        for (int read_index = 0; read_index < *registries_count_pointer; read_index++)
        {
            if (strcmp(registries[read_index].password, password) != 0)
            {
                registries[write_index++] = registries[read_index];
            } else {
                found = 1;
                deleted_count++;
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
            if (registries[read_index].gender != gender)
            {
                registries[write_index++] = registries[read_index];
            } else {
                found = 1;
                deleted_count++;
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
            if (registries[read_index].salary != salary)
            {
                registries[write_index++] = registries[read_index];
            } else {
                found = 1;
                deleted_count++;
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
        *registries_count_pointer = write_index;
        Registry *realloc_helper = realloc(registries, *registries_count_pointer * sizeof(Registry));
        if (realloc_helper == NULL)
        {
            printf("Memória insuficiente\n");
            exit(1);
        }
        registries = realloc_helper;
        printf("%d registro(s) removido(s).\n", deleted_count);
    }
}

int main()
{
    char filename[256], *line, *line_helper, line_copy[LINE_SIZE];
    Registry *registries = NULL;
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

            if (registries_count == 1000)
            {
                printf("Sem espaço para inserção.\n");
            }
            else
            {
                Registry *realloc_helper = realloc(registries, (registries_count + 1) * sizeof(Registry)); // Realoca memória para armazenar mais um registro
                if (realloc_helper == NULL)
                {
                    printf("Memória insuficiente\n");
                    break;
                }
                Registry new_registry = create_registry(line); // Passa a linha de comando do usuário e recebe a struct do novo registro montada
                registries = realloc_helper;
                registries[registries_count] = new_registry; // Insere o novo registro no array
                registries_count++;
                printf("Registro inserido.\n");
            }
            break;
        case 2:
            find_registry(registries, registries_count, line); // Passa o array de registros, a quantidade de registros e a linha de comando do usuário
            break;
        case 3:
            delete_registry(registries, &registries_count, line); // Passa o array de registros, um ponteiro para a quantidade de registros e a linha de comando do usuário
            break;
        default:
            printf("Operação não reconhecida\n");
            break;
        }
    }

    // Libera a memória dinâmicamente alocada
    free(registries);
    free(line);
    return 0;
}
