//
// Created by root on 10/11/17.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estoque.h"
#include "carrinho.h"

int loadEstoque(Mercadoria vet[], int* tam){
    FILE* arq;
    arq = fopen("estoque.txt", "r");
    Mercadoria nova;
    char *aux, entrada[50];
    int tamanho = 0;
    if(arq == NULL){
        printf("Arquivo Criado!!!");
        arq = fopen("estoque.txt", "a");
        fclose(arq);
        loadEstoque(vet, tam);
    }else{
        while(fgets(entrada, 50, arq) != NULL){
            aux = strtok(entrada, "-");
            strcpy(nova.nome, aux);
            aux = strtok(NULL, "-");
            nova.preco = atof(aux);
            aux = strtok(NULL, "-");
            nova.quantidade = atoi(aux);
            if(nova.quantidade > 0){
                vet[tamanho] = nova;
                tamanho ++;
            }
        }
    }
    *tam = tamanho;
    fclose(arq);
    return 1;
}

int writeEstoque(Mercadoria vet[], int tam){
    char enviar[50], preco[20], quantidade[3];
    int i;
    FILE* arq;
    arq = fopen("estoque.txt", "w");

    for(i = 0; i < tam; i++){
        if(vet[i].quantidade > 0) {
            strcpy(enviar, "");//Certifica que a string está vazia
            strcat(enviar, vet[i].nome);
            strcat(enviar, "-");
            sprintf(preco, "%.2f", vet[i].preco);
            strcat(enviar, preco);
            strcat(enviar, "-");
            sprintf(quantidade, "%i", vet[i].quantidade);
            strcat(enviar, quantidade);
            strcat(enviar, "\n");
            fprintf(arq, "%s", enviar);
        }
    }

    fclose(arq);
    return 1;
}
