#include <stdio.h>
#include <string.h>
#define LIMITE 500
#define MAX 50

struct tipoConta {

    //Dados do cliente
    int numConta;
    float saldo;
    char nomeCompleto[MAX];

};

int leEntrada(); //Lê a entrada do usuário e trata o problema da limitação do vetor, devolvendo n

void cadastraClientes(tipoConta c[], int n); //Alimenta o vetor de registros com os atributos de entrada

void imprimeDados(tipoConta c[], int i); //Imprime os dados da posição do vetor de índice i  

int acessoMenu(); //Imprime as opções do Menu, e lê o valor da instrução a seguir, devolvendo o valor lido

void consultaDados(tipoConta c[], int n); /*Recebe um número de conta e busca no vetor de registros. 
                                           Se o mesmo existir, imprime os dados*/

void transfereValor(tipoConta c[], int n); /*Recebe a conta origem, destino e valor da transferência, 
                                             chama um verificador pra saber se as contas existem e caso 
                                             conta origem tenha saldo suficiente, transfere o valor*/

int verificaExistencia(tipoConta c[], int n, int cVerificar); /*Varre o vetor de contas procurando o número 
                                                                da conta idêntico ao lido e devolve índice 
                                                                encontrado ou -1*/

void listaOrdemSaldo(tipoConta c[], int n); /*Ordena de maneira crescente o saldo, comparando o atributo entre 
                                              as posições do vetor de registros. Ordenação por inserção*/

void listaOrdemNome(tipoConta c[], int n); /*Ordena alfabeticamente de maneira decrescente, comparando o nomeCompleto  
                                             de duas posições no vetor de registros. Ordenação por seleção*/

void imprimeNomeSaldo(tipoConta[], int n); //Imprime apenas nome e saldo dos clientes

int repeteMenu(); //Lê instrução de saída ou repetição do Menu do programa e devolve valor lido

int main()
{
    int n = leEntrada();

    tipoConta contas[LIMITE];

    cadastraClientes(contas, n); 

    do {

        switch (acessoMenu()) {
            case 1:
                consultaDados(contas, n);
                break;
            case 2: 
                transfereValor(contas, n);
                break;
            case 3:
                listaOrdemSaldo(contas, n);
                break;
            case 4:
                listaOrdemNome(contas, n);
                break;
            default:
                printf("Opção inválida\n");
                break;
        }

    } while(repeteMenu());

    return 0;
}

int leEntrada() {
    int n;
    scanf("%d", &n);

    while(n > LIMITE) {
        printf("Limite de cadastros excedido. Máximo de 500 cadastros!\n");
        scanf("%d", &n);
    }       
    
    return n;
}

void cadastraClientes(tipoConta c[], int n) {

    for (int i = 0; i < n; i++) {        
        scanf(" %[^\n]", c[i].nomeCompleto);
        scanf("%d", &c[i].numConta);
        scanf("%f", &c[i].saldo);
    }
}

void imprimeDados(tipoConta c[], int i) {

        printf("Nome completo: %s\n", c[i].nomeCompleto);
        printf("Número da conta: %05d\n", c[i].numConta);
        printf("Saldo disponível: R$%.2f\n\n", c[i].saldo);
    
}

int acessoMenu() {
    
    int x;

    printf("---------------------------------\n");
    printf("          Menu de opções         \n");
    printf("---------------------------------\n\n");
    printf("Digite o número da opção desejada\n\n");
    printf("1 Consulta dados de um cliente\n");
    printf("2 Transferência de valor entre contas\n");
    printf("3 Listagem de contas em ordem crescente de saldo\n");
    printf("4 Listagem dos clientes em ordem alfabética decrescente\n");

    scanf("%d", &x);

    return x;
}

void consultaDados(tipoConta c[], int n) {

    int nConta;
    int encontrado = 0;

    printf("Opção 1\n\n");
    printf("Informe o número da conta: \n");

    scanf("%d", &nConta);    

    for (int i = 0; i < n; i++) {
        
        if (nConta == c[i].numConta) {
            imprimeDados(c, i); 
            encontrado = 1; 
        }             
    }

    if (!encontrado)
        printf("Cliente não encontrado!\n");
}

void transfereValor(tipoConta c[], int n) {

    int cOrigem, cDestino, iOrigem, iDestino;
    float valorTransferencia;

    printf("Digite o número da conta que irá transferir o valor:\n");
    scanf("%d", &cOrigem);
    printf("Digite o número da conta que irá receber o valor:\n");
    scanf("%d", &cDestino);
    printf("Digite o valor a ser transferido:\n");
    scanf("%f", &valorTransferencia);

    //Varre o vetor de contas procurando o número da conta idêntico ao lido e devolve índice encontrado ou -1
    iOrigem = verificaExistencia(c, n, cOrigem);
    
    //Caso conta origem não exista, a conta destino já é anulada, caso contrário é verificada    
    iOrigem < 0 ? iDestino = -1 : iDestino = verificaExistencia(c, n, cDestino);

    if (iOrigem == -1) 
        printf("Conta origem não existe!\n");
    else if (iDestino == -1)
        printf("Conta destino não existe!\n");
    else if (c[iOrigem].saldo < valorTransferencia)
        printf("Saldo insuficiente para completar a transferência\n");
    else { 
        //Executa transferência
        c[iOrigem].saldo -= valorTransferencia;
        c[iDestino].saldo += valorTransferencia;

        //Imprime dados para verificar se a transferência ocorreu corretamente
        imprimeDados(c, iOrigem);
        imprimeDados(c, iDestino);
    }    
}

int verificaExistencia(tipoConta c[], int n, int cVerificar) {
    for (int i = 0; i < n; i++) {
        //Verifica se número da conta informado como origem ou destino está no vetor, devolve índice
        if (cVerificar == c[i].numConta) {
            return i;
        }        
    }
    //Sinaliza com -1 e inexistência da conta
    return -1;
}

void listaOrdemSaldo(tipoConta c[], int n) {
    
    tipoConta x;

    //Contadores
    int numComp = 0;
    int numMov = 0;
    int j;

    for (int i = 1; i < n; i++) {
        x = c[i];

        for (j = i-1; j > -1 && c[j].saldo > x.saldo; j--) {
            c[j+1] = c[j];
            c[j] = x;
            numComp++;
            numMov++;
        }

        //Condição para contar apenas quando a variável j não tiver passado do índice 0 do vetor        
        if (j > -1) 
            numComp++;
    }

    //Impressão dos dados ordenados
    for (int i = 0; i < n; i++) {
        imprimeDados(c, i);
    }

    //Impressão dos contadores
    printf("Número de comparações = %d\n", numComp);
    printf("Número de movimentações = %d\n\n", numMov);

}

void listaOrdemNome(tipoConta c[], int n) {
    
    int menor;
    tipoConta x;

    //Contadores
    int numComp = 0;
    int numMov = 0;

    for (int i = 0; i < n-1; i++) {
        menor = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(c[j].nomeCompleto, c[menor].nomeCompleto) > 0) 
                menor = j;
            numComp++;            
        }

        /*Só faz realmente a movimentação quando define o índice da posição com a letra de menor "valor"  
        após esgotar as iterações do segundo for*/

        if (i!=menor) {
            x = c[i];
            c[i] = c[menor];
            c[menor] = x;
            numMov++;
        }
    }

    //Impressão dos dados ordenados
    imprimeNomeSaldo(c, n);

    //Impressão dos contadores
    printf("Número de comparações = %d\n", numComp);
    printf("Número de movimentações = %d\n\n", numMov);
}

void imprimeNomeSaldo(tipoConta c[], int n) {

    for (int i = 0; i < n; i++) {
        printf("Nome Completo: %s\n", c[i].nomeCompleto);
        printf("Saldo: R$%.2f\n\n", c[i].saldo);
    }
}

int repeteMenu() {

        int continua;
        printf("Deseja continuar ou sair do programa?\n");
        printf("1 - Continuar       0 - Sair\n\n");

        scanf("%d", &continua);

        return continua;
}
