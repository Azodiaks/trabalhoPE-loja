//
// Created by root on 10/11/17.
//

#include "carrinho.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct item{//Estrutura de lista duplamente encadeada
    Mercadoria* merc;
    struct item* back;
    struct item* next;
}Item;

Item* primeiro = NULL;
Item* view;//Esse ponteiro vai apontar pro produto que o usuário está vendo no seu carrinho

int loadCarrinho(Mercadoria estoque[], int tam_estoque){//Carregar estoque antes de usar essa função!!!
    FILE* arq;
    arq = fopen("carrinho.txt", "r");
    Mercadoria* nova;
    char *aux, entrada[100];
    int i, tamanho = 0;
    if(arq == NULL){
        printf("Arquivo criado!");
        arq = fopen("carrinho.txt", "a");
        fclose(arq);
        loadCarrinho(estoque, tam_estoque);
    }else{
        while(fgets(entrada, 100, arq) != NULL){
            nova = (Mercadoria*)malloc(sizeof(Mercadoria));
            aux = strtok(entrada, "-");
            strcpy(nova->nome, aux);
            aux = strtok(NULL, "-");
            nova->quantidade = atoi(aux);
            for(i = 0; i<tam_estoque; i++){
                if(strcmp(estoque[i].nome, nova->nome) == 0 && estoque[i].quantidade - nova->quantidade >= 0){
                    nova->preco = estoque[i].preco;
                    estoque[i].quantidade -= nova->quantidade;
                    if (tamanho == 0){
                        initCarrinho(nova);
                    } else {
                        addItemCarrinho(nova);
                    }
                    tamanho++;
                }
            }
        }
    }
    fclose(arq);
    return 1;
}

int initCarrinho(Mercadoria* primeira){//Inicializa o carrinho com o primeiro item
    if(!isInit()){
        primeiro = (Item *) malloc(sizeof(Item));
        primeiro->next = primeiro;
        primeiro->back = primeiro;
        primeiro->merc = primeira;
        view = primeiro;
        return 1;
    }else{
        freeCarrinho();
        initCarrinho(primeira);
        return 1;
    }
}

int isInit(){//Sempre que o carrinho não estiver inicializado primeiro == NULL
    if(primeiro == NULL) return 0;
    else return 1;
}

int addItemCarrinho(Mercadoria* nova){
    if(isInit()) {
        if (primeiro->next == primeiro){//Verifica se só tem um item no carrinho, pois o algoritmo nesse caso muda
            Item* segundo = (Item*)malloc(sizeof(Item));
            segundo->merc = nova;
            primeiro->next = segundo;//Aqui muda, pois temos que mexer no item depois do primeiro
            primeiro->back = segundo;
            segundo->next = primeiro;
            segundo->back = primeiro;
            return 1;
        } else {//Depois de alocar o segundo todas as alocações são iguais
            Item *novo = (Item *) malloc(sizeof(Item));
            primeiro->back->next = novo;
            novo->back = primeiro->back;
            novo->next = primeiro;
            primeiro->back = novo;
            novo->merc = nova;
            return 1;
        }
    }else return 0;
}

int getView(Mercadoria** item) {//No trecho Mercadoria** item, isso acontece pois queremos apontar um ponteiro pra outro
    if(isInit()){               //lugar, e a sintaxe é esta, estava tendo o mesmo erro que esse cara aqui:
        *item = view->merc;//https://stackoverflow.com/questions/30887252/pointer-parameter-was-set-but-never-used-warning
        return 1;
    }else return 0;
}

int nextView(){//Mexe a view para o proximo item
    if(view != NULL){
        view = view->next;
        return 1;
    }else return 0;
}

int backView(){//Mexe a view pro item anterior
    if(view != NULL){
        view = view->back;
        return 1;
    }else return 0;
}

int isEmpty(){
    if(primeiro->next == primeiro && primeiro->merc == NULL) return 1;
    else return 0;
}

int freeCarrinho(){
    if(isInit() && !isEmpty()) {
        Item *aux = primeiro->next;
        while (aux != primeiro) {
            aux = aux->next;
            free(aux->back);
        }
        free(aux);
        return 1;
    }
    return 0;
}

int removeItemCarrinho(Mercadoria* item, Mercadoria estoque[], int tam_estoque){
    Item* aux = primeiro;
    int i;

    while(aux->merc != item){
        aux = aux->next;
        if(aux == primeiro) return 0;
    }

    aux->merc->quantidade -= 1;

    for(i = 0; i<tam_estoque; i++){
        if(&estoque[i] == item){
            estoque[i].quantidade += 1;
        }
    }

    if(aux->merc->quantidade == 0){
        if(aux == primeiro){
            if(view == primeiro){
                nextView();
            }
            primeiro->back->next = primeiro->next;
            primeiro->next->back = primeiro->back;
            primeiro = primeiro->next;
            free(aux);
            if(isEmpty()) primeiro = NULL;
            return 1;
        }else{
            aux->back->next = aux->next;
            aux->next->back = aux->back;
            if(view == aux) nextView();

            free(aux);
        }
    }
    return 1;

}

int checkout(float* total){
    FILE* arq = fopen("saida.txt", "w");
    char mensagem[2000], linha[100];
    strcpy(mensagem, "");
    if(isInit()) {
        Item *aux = primeiro;
        *total = 0;
        do {
            *total += aux->merc->preco * aux->merc->quantidade;
            sprintf(linha, "%s, preco un = %.2f, qtd = %i, total = %.2f\n\n", aux->merc->nome, aux->merc->preco, aux->merc->quantidade, aux->merc->preco*aux->merc->quantidade);
            strcat(mensagem, linha);
            aux = aux->next;
        } while (aux != primeiro);
        sprintf(linha, "========================================\nTOTAL=%.2f\n========================================", *total);
        strcat(mensagem, linha);
        fprintf(arq, "%s", mensagem);
        freeCarrinho();
        return 1;
    }
    return 0;
}
