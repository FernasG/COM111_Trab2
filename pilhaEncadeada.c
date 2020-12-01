#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pilhaEncadeada.h"

typedef struct elemento{
    int topo;
    unsigned capacidade;
    int *vetor;
}Elemento;

Pilha * criarPilha(unsigned capacidade){
    Pilha *pi = (Pilha *) malloc(sizeof(Pilha));

    if(!pi)
        return 0;

    pi->topo = -1;
    pi->capacidade = capacidade;
    pi->vetor = (int *)malloc(pi->capacidade * sizeof(int));

    return pi;
}

int estaVazio(Pilha *pi){
    return pi->topo == -1;
}

char consultarTopo(Pilha *pi){
    return pi->vetor[pi->topo];
}

char removerElemento(Pilha *pi){
    if(!estaVazio(pi))
        return pi->vetor[pi->topo--];
    return '$';
}

void inserirElemento(Pilha *pi, char op){
    pi->vetor[++pi->topo] = op;
}

int eOperando(char valor){
    return ((valor >= 'a' && valor <= 'z') || (valor >= '0' && valor <= '9'));
}

int verificaPrecedencia(char valor){
    switch (valor)
    {
        case '+':
        case '-':
            return 1;     

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;
    }
    return -1;
}

int converteInfixoParaPosfixo(char *exp){
    int i, k;

    Pilha *pilha = criarPilha(strlen(exp));
    if(!pilha)
        return 0;
    
    for(i = 0, k = -1; exp[i]; ++i){
        if(eOperando(exp[i])){
            exp[++k] = exp[i];
        }else if(exp[i] == '('){
            inserirElemento(pilha, exp[i]);
        }else if(exp[i] == ')'){
            while (!estaVazio(pilha) && consultarTopo(pilha) != '('){
                exp[++k] = removerElemento(pilha);
            }
            if(!estaVazio(pilha) && consultarTopo(pilha) != '('){
                return -1;
            }else{
                removerElemento(pilha);
            }
        }else {
            while (!estaVazio(pilha) && verificaPrecedencia(exp[i]) <= verificaPrecedencia(consultarTopo(pilha))){
                exp[++k] = removerElemento(pilha);
            }
            inserirElemento(pilha, exp[i]);
        }
    }

    while (!estaVazio(pilha)){
        exp[++k] = removerElemento(pilha);
    }

    exp[++k] = '\0';
    printf("%s", exp);
    
}