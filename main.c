#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carrinho.h"
#include "estoque.h"

int main() {
    Mercadoria estoque[1000], * view;
    char nome[40];
    float preco;
    int i, sel, tam_estoque;

    loadEstoque(estoque, &tam_estoque);
    loadCarrinho(estoque, tam_estoque);

    sel = 4;

    getView(&view);//Veja a maneira correta de usar o getView

    while(sel != 0){
        if(isInit() && !isEmpty()) {
            printf("======================================================\n");
            printf("Digite 1 para ver o proximo item do carrinho\nDigite 2 para ver o item anterior\nDigite 3 para deletar o item do carrinho\n");
            printf("Digite 0 para fazer o checkout\n======================================================\n");
            printf("Nome: %s\nPreco: %.2f\nQuantidade: %i", view->nome, view->preco, view->quantidade);
            scanf("%i", &sel);
            if (sel == 1) {
                nextView();
            } else if (sel == 2) {
                backView();
            } else if (sel == 3) {
                removeItemCarrinho(view, estoque, tam_estoque);
            }
            getView(&view);
        }else{
            printf("Carrinho vazio!!!");
            return 0;
        }
    }

    checkout(&preco);

    writeEstoque(estoque, tam_estoque);

    return 0;
}
