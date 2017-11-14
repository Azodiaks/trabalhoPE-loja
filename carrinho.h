//
// Created by root on 10/11/17.
//

#ifndef TRABALHO_PE_CARRINHO_H
#define TRABALHO_PE_CARRINHO_H

typedef struct mercadoria{
    char nome[40];
    float preco;
    int quantidade;
}Mercadoria;

//No main.c existe um exemplo de implementação desse TAD funcionando!

int initCarrinho(Mercadoria* primeira);
int loadCarrinho(Mercadoria estoque[], int tam_estoque);
int isInit();
int isEmpty();//Vazio != Não inicializado!!!
int addItemCarrinho(Mercadoria* item);
int removeItemCarrinho(Mercadoria* item, Mercadoria estoque[], int tam_estoque);
int getView(Mercadoria** item);//enviar argumento do tipo Mercadoria* e na declaração da função enviar getView(&arg);
int nextView();
int backView();
int freeCarrinho();
int checkout(float* total);//a função checkout já da free no carrinho!!!

#endif //TRABALHO_PE_CARRINHO_H
