#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct node Node;

struct node
{
    int PID;
    char nomeProcesso[50];
    bool prioridade;
    Node *proximo;
};

// Variaveis globais
Node *inicioFila;
Node *finalFila;
int opcao;

// Assinaturas dos metodos
void criarFilaVazia();
bool filaVazia();
bool possuiPrioridade();
Node *alocarNovoNode(int PID, char nomeProcesso[], bool prioridade);
void inserir(int PID, char nomeProcesso[], bool prioridade);
void remover();
void removerPrioridade();
void imprimir(bool prioridade);
void desenhaMenu();

int main()
{
    setlocale(LC_ALL, "");

    // INICIANDO LISTA
    criarFilaVazia();
    // INICIANDO OPCAO
    opcao = -1;

    // VARIAVEIS AUXILIARES
    int pid;
    int temp;
    bool prioridade;
    char nomeProcesso[50];

    while (true)
    {
        desenhaMenu();
        scanf("%d", &opcao);

        system("cls");
        switch (opcao)
        {
        case 1:

            printf("------- OPÇÃO UM | Inserção -------");
            printf("\nDigite o PID do processo: ");
            scanf("%d", &pid);

            printf("\nDigite o nome do processo: ");
            scanf("%s", &nomeProcesso);

            printf("\nO processo tem prioridade? [0] - Não | [1] - Sim: ");
            scanf("%d", &temp);
            prioridade = temp;

            inserir(pid, nomeProcesso, prioridade);

            break;

        case 2:
            printf("------- OPÇÃO DOIS | Remoção -------");
            // VERIFICA SE A LISTA TEM ALGUMA PRIORIDADE PARA SABER QUAL MÉTODO CHAMAR
            if (possuiPrioridade())
            {
                removerPrioridade();
            }
            else
            {
                remover();
            }

            break;

        case 3:
            printf("------- OPÇÃO TRÊS | Impressão -------");
            if (filaVazia())
            {
                printf("\nNão é possível imprimir fila vazia!");
            }
            else
            {
                // Imprime processos sem prioridade
                imprimir(false);
                // Imprime processos com prioridade
                imprimir(true);
            }
            break;
        case 4:
            printf("Até logo!");
            return 0;
            break;
        }

        printf("\n\n");
        system("pause");
        system("cls");
    }
    return 0;
}

bool filaVazia()
{
    return (inicioFila == NULL);
}

bool possuiPrioridade()
{
    bool prioridade = false;

    if (filaVazia())
    {
        printf("\nA fila está vazia.");
    }
    else
    {
        Node *atual = inicioFila;

        while (atual)
        {
            if (atual->prioridade)
            {
                prioridade = true;
                break;
            }
            atual = atual->proximo;
        }

        free(atual);
    }

    return prioridade;
}

void criarFilaVazia()
{
    inicioFila = NULL;
    finalFila = NULL;
}

Node *alocarNovoNode(int PID, char nomeProcesso[], bool prioridade)
{
    Node *novo = (Node *)malloc(sizeof(Node));
    novo->PID = PID;
    strcpy(novo->nomeProcesso, nomeProcesso);
    novo->prioridade = prioridade;
    novo->proximo = NULL;

    return novo;
}

void inserir(int PID, char nomeProcesso[], bool prioridade)
{
    Node *novo = alocarNovoNode(PID, nomeProcesso, prioridade);

    if (filaVazia())
    {
        inicioFila = novo;
        finalFila = novo;
    }
    else
    {
        finalFila->proximo = novo;
        finalFila = novo;
    }
}

void remover()
{
    if (filaVazia())
    {
        printf("\nNão é possível remover de uma fila vazia.");
    }
    else
    {
        Node *atual = inicioFila;

        inicioFila = atual->proximo;
        free(atual);
    }
}

void removerPrioridade()
{

    if (filaVazia())
    {
        printf("\nNão é possível remover de uma fila vazia.");
    }
    else
    {
        Node *aux, *auxProx;
        aux = inicioFila;
        auxProx = inicioFila->proximo;

        while (auxProx != NULL && auxProx->prioridade != true)
        {
            aux = auxProx;
            auxProx = auxProx->proximo;
        }

        if (auxProx != NULL)
        {
            aux->proximo = auxProx->proximo;

            free(auxProx);
        }
    }
}

void imprimir(bool prioridade)
{
    Node *atual = inicioFila;

    if (prioridade)
    {
        printf("\n\nFila de Processos COM prioridade:");
    }
    else
    {
        printf("\n\nFila de Processos SEM prioridade:");
    }

    while (atual)
    {
        if (atual->prioridade == prioridade)
        {
            printf("\nPID: %d | Processo: %s", atual->PID, atual->nomeProcesso);
        }

        atual = atual->proximo;
    }

    free(atual);
}

void desenhaMenu()
{
    printf("\n---- GERENCIADOR DE FILAS (Processos) ----");
    printf("\n1 - Inserir");
    printf("\n2 - Remover");
    printf("\n3 - Imprimir Fila");
    printf("\n4 - Sair");
    printf("\nOpção: ");
}
