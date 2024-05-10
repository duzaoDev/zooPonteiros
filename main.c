#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

///////////////////// TRABALHO APRESENTADO PARA DISCIPLINA DE ALGORITMOS E PROGRAMAÇÃO II
/////////////////////NO CURSO DE SISTEMAS DE INFORMAÇÃO, NA UNIVERSIDADE FEDERAL DE UBERLÂNDIA
///////////////////// DISCENTE: EDUARDO ANTONIO DA SILVA
///////////////////// MATRÍCULA: 12311BSI317

//definindo o struct para as informações que serão armazenadas para cada animal do Zoológico
typedef struct{
    char *codigo;
    char *nome;
    float *peso;
    float *altura;
    char *especie;
} info_animal;

//construindo o struct que dará a estrutura tridimensional do Zoológico
typedef struct {
    int num_setores;
    int num_jaulas_por_setor;
    int num_animais_por_jaula;
    char **setores; // utilizando ponteiro de ponteiro para armazenar as strings dos nomes dos setores
    info_animal ***animais; // matriz tridimensional em formato de p* de p* de p* que armazenará as informações por
    // setor e jaula
} Zoo;


//declarando os protótipos das funções que foram utilizadas
void inicializar(Zoo *zoo);
void listaSetores(Zoo *zoo);
void catalogoSetores(Zoo *zoo);
void inserirAnimais(Zoo *zoo);
void animalMaisPesado (Zoo *zoo);
void animalMaisAlto (Zoo *zoo);
void criarNovoSetor (Zoo *zoo);
void excluirSetor (Zoo *zoo);
void imprimirPopulacaoZoologico(Zoo *zoo);


int main() {
    //setlocale para organizar os acentos, entretanto na IDE que utilizei (CLION) continuou esquisito kkkkk;
    ////IMPORTANTE, por conta disso, se atente a usar vírgulas para os números que são float
    //// na CLION funcionou somente com vírgulas, no online gbd funcionou somente com pontos;
    setlocale(LC_ALL, "Portuguese");
    Zoo zoo;
    int opcao;

    //laço para inicializar o menu e imprimir as opções
    do {
        printf("\nMenu:\n");
        printf("1- Inicialização do Sistema\n");
        printf("2- Catálogo dos Setores\n");
        printf("3- Inserir animais em uma jaula de um setor\n");
        printf("4- Animal mais pesado de um setor\n");
        printf("5- Animal mais alto de um setor\n");
        printf("6- Inserir novo setor\n");
        printf("7- Excluir setor existente\n");
        printf("8- Mostrar população do Zoológico\n");
        printf("0- Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);


        //laço switch case para acessar as opões impressas acima;
        switch (opcao) {
            case 1:
                system("cls");
                inicializar(&zoo); // chama função de inicialização;
                printf("Bem-vindo(a) ao Sistema de Catalogação Virtual do Zoológico.\n");
                break;
            case 2:
                system("cls");
                catalogoSetores(&zoo); // chama função que apresenta o catálogo dos setores;
                break;
            case 3:
                system("cls");
                listaSetores(&zoo); // outra função que mostra os setores para ficar mais fácil de visualizar ao escolher
                // o setor que deseja escolher para inserir os animais;
                inserirAnimais(&zoo);
                break;
            case 4:
                system("cls");
                listaSetores(&zoo); // IDEM
                animalMaisPesado(&zoo); // chama função para encontrar animal mais pesado;
                break;
            case 5: /////FUNÇÃO EXTRA
                system("cls");
                listaSetores(&zoo); // IDEM
                animalMaisAlto(&zoo); // função para encontrar o animal mais alto
                break;
            case 6:
                system("cls");
                listaSetores(&zoo);
                criarNovoSetor(&zoo); // função para criar novo setor, seguido parametros ad inicialização
                break;
            case 7:
                system("cls");
                listaSetores(&zoo);
                excluirSetor(&zoo); // função para excluir setores inseridos posteriormente
                break;
            case 8: ////2a função extra, com alguns bugs que não consegui resolver, mas resolvi deixar no programa
                system("cls");
                imprimirPopulacaoZoologico(&zoo); // função que busca todos os animais inseridos e imprime a população
                // do zoologico;
                break;
           case 0:
                system("cls");
                printf("Saindo do programa.\n"); // sai do programa;
                break;
            default:
                system("cls");
                printf("Opção inválida.\n"); // retorna opção inválida se não for digitado nenhum numero de 1-8;

        }
    }while(opcao != 0);
    return 0; // encerra o programa
}

void inicializar(Zoo *zoo) {

    //solicita os parametros do zoologico, quantos setores, jaulas por setor e animais por jaula
    printf("Número de setores: ");
    scanf("%d", &zoo->num_setores);

    printf("Número de jaulas por setor: ");
    scanf("%d", &zoo->num_jaulas_por_setor);

    printf("Número de animais por jaula: ");
    scanf("%d", &zoo->num_animais_por_jaula);

    // alocando memória para receber as strings dos setores e a matriz tridimensional de info_animal
    zoo->setores = (char **)malloc(zoo->num_setores * sizeof(char *));
    zoo->animais = (info_animal ***)malloc(zoo->num_setores * sizeof(info_animal **));

    // nomeia os setores, percorrendo o primeiro indice da matriz [i]
    for (int i = 0; i < zoo->num_setores; i++) {
        zoo->setores[i] = (char *)malloc(50 * sizeof(char));
        printf("Nome do setor %d: ", i + 1);
        scanf(" %[^\n]s", zoo->setores[i]);
        zoo->animais[i] = (info_animal **)malloc(zoo->num_jaulas_por_setor * sizeof(info_animal *));
        for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
            zoo->animais[i][j] = (info_animal *)malloc(zoo->num_animais_por_jaula * sizeof(info_animal));
        }
    }
    system("cls");
    printf("Sistema inicializado com sucesso.\n\n");

}
void listaSetores(Zoo *zoo) {
    system("cls");
    ////função para auxiliar a visualização e a escolha dos setores na funções necessarias
    // imprime os setores com numero total de jaulas e animais por jaula
    // percorrendo o indice i da matriz para garantir que todos os setores serão impressos
    for (int i = 0; i < zoo->num_setores; i++) {
        printf("\t%d. %s\n\tTotal de jaulas: %d, Animais por jaula: %d\n", i + 1, zoo->setores[i], zoo->num_jaulas_por_setor, zoo->num_animais_por_jaula);
    }
}

void catalogoSetores(Zoo *zoo) {
    system("cls");
    // imprime os setores com numero total de jaulas e animais por jaula
    // percorrendo o indice i da matriz para garantir que todos os setores serão impressos
    printf("Catálogo de Setores:\n");
    for (int i = 0; i < zoo->num_setores; i++) {
        printf("\t%d. %s\n\tTotal de jaulas: %d, Animais por jaula: %d\n", i + 1, zoo->setores[i], zoo->num_jaulas_por_setor, zoo->num_animais_por_jaula);
    }
}

void inserirAnimais(Zoo *zoo) {
    // função que insere os animais nos setores e jaulas
    char nomeSetor[50];
    int numJaula;

    //usuario insere o nome do setor;
    system("cls");
    printf("Nome do setor: ");
    scanf(" %[^\n]", nomeSetor);

    //percorre o indice e encontra o setor utilizando a função de comparar strings (strcmp)
    for (int i = 0; i < zoo->num_setores; i++) {
        if (strcmp(nomeSetor, zoo->setores[i]) == 0) {
            printf("Número da jaula: ");
            scanf("%d", &numJaula);
            numJaula--;
            // subtrai 1 no numero da jaula por conta da matriz
            // testa se o numero da matriz é valido, a partir do parametro inserido na inicializaçao
            if (numJaula >= 0 && numJaula < zoo->num_jaulas_por_setor) {
                for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                    //alocando memoria para nome, peso, especie, codigo e altura
                    zoo->animais[i][numJaula][k].nome = (char *)malloc(50 * sizeof(char));
                    zoo->animais[i][numJaula][k].peso = (float *)malloc(sizeof(float));
                    zoo->animais[i][numJaula][k].especie = (char *)malloc(50* sizeof(char));
                    zoo->animais[i][numJaula][k].codigo = (char *)malloc(50* sizeof(char));
                    zoo->animais[i][numJaula][k].altura = (float *)malloc(sizeof(float));

                    system("cls");

                    printf("\tInserir Animal em %s\n\n", nomeSetor);
                    printf("Setor - %s\n", nomeSetor);
                    printf("\tJaula %d de %d\n", numJaula + 1, zoo->num_jaulas_por_setor);

                    printf("Código do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].codigo);

                    printf("Nome do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].nome);

                    printf("Espécie do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].especie);

                    //usar vírgula por conta do setlocale, senão dá erro. entretanto fiz um teste no onlinegdb
                    // e lá só funcionou com ponto (.);

                    printf("Peso do animal %d (em kilos, usar vírgula): ", k + 1);
                    scanf("%f", zoo->animais[i][numJaula][k].peso);

                    printf("Altura do animal %d (em metros, usar vírgula): ", k + 1);
                    scanf("%f", zoo->animais[i][numJaula][k].altura);
                    printf("\n");
                }
                system("cls");
                printf("Animais inseridos com sucesso na jaula %d do setor %s.\n", numJaula + 1, nomeSetor);
                return;
            } else {
                printf("Número de jaula inválido.\n");
                return;
            }
        }
    }
    printf("Setor não encontrado.\n");
}

///// versão mais elaborada da função acima, entretanto acarretou problemas na função criarNovoSetor que não consegui
///// resolver :(
///// deixei aqui para não perder e no futuro tentar corrigir.
/*void inserirAnimais(Zoo *zoo) {

    char nomeSetor[50];
    int numJaula;

    printf("Nome do setor: ");
    scanf(" %[^\n]", nomeSetor);

        for (int i = 0; i < zoo->num_setores; i++) {
            if (strcmp(nomeSetor, zoo->setores[i]) == 0) {
                while (1) { // Adiciona um loop para continuar pedindo um número de jaula
                    printf("Número da jaula: ");
                    scanf("%d", &numJaula);
                    numJaula--;

                    if (numJaula >= 0 && numJaula < zoo->num_jaulas_por_setor) {
                        while (zoo->animais[i][numJaula][0].nome != NULL &&
                               zoo->animais[i][numJaula][0].codigo != NULL &&
                               zoo->animais[i][numJaula][0].peso != NULL &&
                               zoo->animais[i][numJaula][0].altura != NULL &&
                               zoo->animais[i][numJaula][0].especie != NULL) {
                            printf("Jaula já está preenchida. Por favor, insira um número de jaula válido.\n");
                            printf("Número da jaula: ");
                            scanf("%d", &numJaula);
                            numJaula--;
                        }
                        break; // Sai do loop quando um número de jaula válido é inserido
                    } else {
                        printf("Número de jaula inválido. Por favor, insira um número de jaula válido.\n");
                    }
                }
                for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                    zoo->animais[i][numJaula][k].nome = (char *) malloc(50 * sizeof(char));
                    zoo->animais[i][numJaula][k].peso = (float *) malloc(sizeof(float));
                    zoo->animais[i][numJaula][k].especie = (char *) malloc(50 * sizeof(char));
                    zoo->animais[i][numJaula][k].codigo = (char *) malloc(50 * sizeof(char));
                    zoo->animais[i][numJaula][k].altura = (float *) malloc(sizeof(float));

                    system("cls");

                    printf("Setor - %s\n", nomeSetor);
                    printf("\tJaula %d de %d\n", numJaula + 1, zoo->num_jaulas_por_setor);

                    printf("Código do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].codigo);

                    printf("Nome do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].nome);

                    printf("Espécie do animal %d: ", k + 1);
                    scanf(" %[^\n]s", zoo->animais[i][numJaula][k].especie);

                    //usar vírgula por conta do setlocale, senão dá erro. entretanto fiz um teste no onlinegdb
                    // e lá só funcionou com ponto (.);

                    printf("Peso do animal %d (em kilos, usar vírgula): ", k + 1);
                    scanf("%f", zoo->animais[i][numJaula][k].peso);

                    printf("Altura do animal %d (em metros, usar vírgula): ", k + 1);
                    scanf("%f", zoo->animais[i][numJaula][k].altura);
                    printf("\n");
                }
                system("cls");
                printf("Animais inseridos com sucesso na jaula %d do setor %s.\n", numJaula + 1, nomeSetor);
                return;
            } else {
                printf("Número de jaula inválido.\n");
                return;
            }
        }
        printf("Setor não encontrado.\n");
    }
*/



void animalMaisPesado(Zoo *zoo) {
    char nomeSetor[50];
    char *nome = NULL;
    float maiorPeso = 0.0; // precisei inicializar o peso do animal em 0, pq estava dando pau pra imprimir o nome
    nome = (char *)malloc(50 * sizeof(char)); // alocação de memória para o ponteiro 'nome'


    printf("\tAnimal mais pesado do setor.\n");
    printf("Escolha o setor: ");
    scanf(" %[^\n]", nomeSetor);

    int setorEscolhido = -1; // inicializa o índice do setor escolhido como -1
    // procura pelo setor inserido pelo usuário no array de setores do zoológico e compara a string (strcmp)
    for (int i = 0; i < zoo->num_setores; i++) {
        if (strcmp(nomeSetor, zoo->setores[i]) == 0) {
            setorEscolhido = i; // se encontrado, atribui o índice do setor à variável 'setorEscolhido'
            break;
        }
    }

    if (setorEscolhido != -1) {
        // percorrendo o indice das janelas na matriz
        for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
            for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                // verifica se o peso do animal atual é maior que o maior peso encontrado até agora
                if (zoo->animais[setorEscolhido][j][k].peso != NULL &&
                    *(zoo->animais[setorEscolhido][j][k].peso) > maiorPeso) {
                    //atualiza o maior peso e armazena o nome do animal
                    maiorPeso = *(zoo->animais[setorEscolhido][j][k].peso);
                    // alocando memória para o nome e copia o nome do animal (strcpy)
                    if (zoo->animais[setorEscolhido][j][k].nome != NULL && strlen(zoo->animais[setorEscolhido][j][k].nome) > 0) {
                        nome = (char *)realloc(nome, (strlen(zoo->animais[setorEscolhido][j][k].nome) + 1) * sizeof(char));
                        strcpy(nome, zoo->animais[setorEscolhido][j][k].nome);
                    }
                }
            }
        }

        system("cls");
        if (nome != NULL && strlen(nome) > 0) {
            // exibe o nome do animal mais pesado, seu peso e o nome do setor
            printf("O animal mais pesado do setor %s é: %s, com %.2f kilos\n", nomeSetor, nome, maiorPeso);
        } else {
            printf("Nenhum animal encontrado no setor escolhido.\n");
        }
    } else {
        printf("Setor não encontrado.\n");
    }
    free(nome); // libera a memória alocada para o nome do animal
}

void animalMaisAlto (Zoo *zoo) {
    ////FUNÇÃO EXTRA

    ////os caminhos dessa função são identicos a de cima, só altera a informação que é buscada na matriz
    char nomeSetor[50];
    char *nome = NULL;
    float maiorAltura = 0.0;
    nome = (char *)malloc(50 * sizeof(char));

    printf("\tAnimal mais alto do setor.\n");
    printf("Escolha o setor: ");
    scanf(" %[^\n]", nomeSetor);

    int setorEscolhido = -1;
    for (int i = 0; i < zoo->num_setores; i++) {
        if (strcmp(nomeSetor, zoo->setores[i]) == 0) {
            setorEscolhido = i;
            break;
        }
    }

    if (setorEscolhido != -1) {
        for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
            for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                if (zoo->animais[setorEscolhido][j][k].altura != NULL &&
                    *(zoo->animais[setorEscolhido][j][k].altura) > maiorAltura) {
                    maiorAltura = *(zoo->animais[setorEscolhido][j][k].altura);
                    if (zoo->animais[setorEscolhido][j][k].nome != NULL && strlen(zoo->animais[setorEscolhido][j][k].nome) > 0) {
                        nome = (char *)realloc(nome, (strlen(zoo->animais[setorEscolhido][j][k].nome) + 1) * sizeof(char));
                        strcpy(nome, zoo->animais[setorEscolhido][j][k].nome);
                    }
                }
            }
        }
        system("cls");
        if (nome != NULL && strlen(nome) > 0) {
            printf("O animal mais alto do setor %s é: %s, com %.2f metros\n", nomeSetor, nome, maiorAltura);
        }else{
            printf("Nenhum animal encontrado no setor escolhido.\n");
        }
    }else{
        printf("Setor não encontrado.\n");
    }
    free(nome); // Liberar a memória alocada para o nome
}



void criarNovoSetor(Zoo *zoo) {
    //incrementa o indice dos setores
    zoo->num_setores++;
    //realoca memória para o vetor de setores para incluir a string do nome do novo setor;;
    zoo->setores = (char **)realloc(zoo->setores, zoo->num_setores * sizeof(char *));
    // aloca memória para o nome do novo setor;;
    zoo->setores[zoo->num_setores - 1] = (char *)malloc(50 * sizeof(char));

    printf("Nome do novo setor: ");
    scanf(" %[^\n]", zoo->setores[zoo->num_setores - 1]);

    // realoca memória para o vetor de animais para incluir o novo setor;;
    zoo->animais = (info_animal ***)realloc(zoo->animais, zoo->num_setores * sizeof(info_animal **));
    // aloca memorias para a jaula e animais do novo setor
    zoo->animais[zoo->num_setores - 1] = (info_animal **)malloc(zoo->num_jaulas_por_setor * sizeof(info_animal *));
    for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
        zoo->animais[zoo->num_setores - 1][j] = (info_animal *)malloc(zoo->num_animais_por_jaula * sizeof(info_animal));
        for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
            //inicializa os campos de cada animal nas novas jaulas como NULL;
            zoo->animais[zoo->num_setores - 1][j][k].nome = NULL;
            zoo->animais[zoo->num_setores - 1][j][k].peso = NULL;
            zoo->animais[zoo->num_setores - 1][j][k].altura = NULL;
            zoo->animais[zoo->num_setores - 1][j][k].especie = NULL;
            zoo->animais[zoo->num_setores - 1][j][k].codigo = NULL;
        }
    }

    printf("Novo setor inserido com sucesso!\n");

}

void excluirSetor(Zoo *zoo){
    char nomeSetor[50];
    printf("Nome do setor a ser removido: ");
    scanf(" %[^\n]", nomeSetor);

    int indiceSetor = -1;
    //procura o indice do setor a ser removido no vetor de setores do zoologico
    for (int i = 0; i < zoo->num_setores; i++) {
        //compara a string do nome do setor
        if (strcmp(nomeSetor, zoo->setores[i]) == 0) {
            indiceSetor = i;
            break;
        }
    }

    if (indiceSetor != -1) {
        // libera memoria alocada para o nome do setoer a ser removido
        free(zoo->setores[indiceSetor]);

        //limpa os campos de animal dentro do setor a ser removido
        for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
            for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                zoo->animais[indiceSetor][j][k].nome = NULL;
                zoo->animais[indiceSetor][j][k].peso = NULL;
                zoo->animais[indiceSetor][j][k].altura = NULL;
                zoo->animais[indiceSetor][j][k].especie = NULL;
            }
        }

        // libera a memória alocada para os campos de cada animal dentro do setor a ser removido
        for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
            for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                free(zoo->animais[indiceSetor][j][k].nome);
                free(zoo->animais[indiceSetor][j][k].peso);
                free(zoo->animais[indiceSetor][j][k].altura);
                free(zoo->animais[indiceSetor][j][k].especie);
            }
            // libera a memória alocada para as jaulas dentro do setor a ser removido
            free(zoo->animais[indiceSetor][j]);
        }  // libera a memória alocada para o vetor de animais dentro do setor a ser removido
        free(zoo->animais[indiceSetor]);

        // move os setores e animais restantes para ocupar o espaço do setor removido
        for (int i = indiceSetor; i < zoo->num_setores - 1; i++) {
            zoo->setores[i] = zoo->setores[i + 1];
            zoo->animais[i] = zoo->animais[i + 1];
            zoo->setores[zoo->num_setores - 1] = NULL;
            zoo->animais[zoo->num_setores - 1] = NULL;
        }

        // realoca memória para reduzir o tamanho do array de setores e animais
        zoo->setores = (char **)realloc(zoo->setores, (zoo->num_setores - 1) * sizeof(char *));
        zoo->animais = (info_animal ***)realloc(zoo->animais, (zoo->num_setores - 1) * sizeof(info_animal **));

        //retirar -1 no indice dos setores;
        zoo->num_setores--;

        printf("Setor removido com sucesso!\n");
    } else {
        printf("Setor não encontrado.\n");
    }
}


void imprimirPopulacaoZoologico(Zoo *zoo) {
    ////FUNÇÃO EXTRA
    ////essa função percorre todos os indices da matriz e imprime todas as informações dos animais inseridos
    ////no zoologico.

    system("cls");
    for (int i = 0; i < zoo->num_setores; i++) {
        if (zoo->setores[i] != NULL) {
            printf("População do Zoológico\n");
            printf("Setor: %s\n", zoo->setores[i]);
            for (int j = 0; j < zoo->num_jaulas_por_setor; j++) {
                printf("\t\tJaula %d:\n", j + 1);
                for (int k = 0; k < zoo->num_animais_por_jaula; k++) {
                    if (zoo->animais[i][j][k].nome != NULL &&
                        zoo->animais[i][j][k].codigo != NULL &&
                        zoo->animais[i][j][k].peso != NULL &&
                        zoo->animais[i][j][k].altura != NULL &&
                        zoo->animais[i][j][k].especie != NULL) {
                        printf("  Animal %d:\n", k + 1);
                        printf("    Código: %s\n", zoo->animais[i][j][k].codigo);
                        printf("    Nome: %s\n", zoo->animais[i][j][k].nome);
                        printf("    Peso: %.2f\n", *zoo->animais[i][j][k].peso);
                        printf("    Altura: %.2f\n", *zoo->animais[i][j][k].altura);
                        printf("    Espécie: %s\n", zoo->animais[i][j][k].especie);
                    }
                }
            }
        }
    }
}







