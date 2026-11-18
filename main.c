#include <stdio.h>
#include <stdlib.h>

#define MAX_CONTAS 3

typedef struct {
    int tipo;
    float saldo;
} Conta;

typedef struct {
    char nome[80];
    Conta contas[MAX_CONTAS];
    int qtdContas;
} Cliente;

Cliente *clientes = NULL;
int qtdClientes = 0;

// CADASTRAR CLIENTE
void cadastrarCliente() {
    Cliente *temp;

    temp = realloc(clientes, (qtdClientes + 1) * sizeof(Cliente));

    if (temp == NULL) {
        printf("\nErro de memoria!\n");
        return;
    }

    clientes = temp;

    Cliente *c = &clientes[qtdClientes];

    printf("\nNome do cliente: ");
    scanf(" %79[^\n]", c->nome);

    c->qtdContas = 0;

    qtdClientes++;

    printf("\nCliente cadastrado com sucesso!\n");
}

// LISTAR CLIENTES
void listarClientes() {
    if (qtdClientes == 0) {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    for (int i = 0; i < qtdClientes; i++) {
        printf("\nCliente %d: %s\n", i + 1, clientes[i].nome);

        for (int j = 0; j < clientes[i].qtdContas; j++) {

            printf("Tipo da conta: %02d\n",
                   clientes[i].contas[j].tipo);

            printf("Saldo: R$ %.2f\n",
                   clientes[i].contas[j].saldo);
        }
    }
}

// ABRIR CONTA
void abrirConta() {
    int codigo, tipo;
    float saldo;

    if (qtdClientes == 0) {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }

    listarClientes();

    printf("\nDigite o numero do cliente: ");
    scanf("%d", &codigo);

    if (codigo < 1 || codigo > qtdClientes) {
        printf("\nCliente invalido!\n");
        return;
    }

    Cliente *c = &clientes[codigo - 1];

    if (c->qtdContas >= MAX_CONTAS) {
        printf("\nLimite de contas atingido!\n");
        return;
    }

    printf("\n===== TIPOS DE CONTA =====\n");
    printf("01 - Conta corrente\n");
    printf("02 - Conta salario\n");
    printf("03 - Conta poupanca\n");

    printf("\nEscolha o tipo de conta: ");
    scanf("%d", &tipo);

    if (tipo < 1 || tipo > 3) {
        printf("\nTipo de conta invalido!\n");
        return;
    }

    for (int i = 0; i < c->qtdContas; i++) {

        if (c->contas[i].tipo == tipo) {
            printf("\nCliente ja possui essa conta!\n");
            return;
        }

        if ((tipo == 1 && c->contas[i].tipo == 2) ||
            (tipo == 2 && c->contas[i].tipo == 1)) {

            printf("\nConta corrente e salario nao podem coexistir!\n");
            return;
        }
    }

    printf("\nDigite o saldo inicial: R$ ");
    scanf("%f", &saldo);

    if (saldo < 0) {
        printf("\nSaldo invalido!\n");
        return;
    }

    c->contas[c->qtdContas].tipo = tipo;
    c->contas[c->qtdContas].saldo = saldo;

    c->qtdContas++;

    printf("\nConta aberta com sucesso!\n");
}

// MENU PRINCIPAL
void menuPrincipal() {
    int opcao;

    do {
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Abrir conta\n");
        printf("3 - Listar clientes e saldos\n");
        printf("0 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1:
                cadastrarCliente();
                break;

            case 2:
                abrirConta();
                break;

            case 3:
                listarClientes();
                break;

            case 0:
                printf("\nEncerrando o sistema...\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);
}

// FUNCAO PRINCIPAL
int main() {

    menuPrincipal();

    free(clientes);

    return 0;
}
