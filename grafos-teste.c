#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>
#include "grafos.h"
//Autor: João Victor Silva Reis dos Santos
//Universidade Federal de Sergipe
//Aracaju - SE
int main(void){
   setlocale(LC_ALL, "Portuguese");//habilita a acentuação para o português

    FILE *arq;
    grafo G, H;
    G = ler_grafo_custos(arq,"grafo-g.txt");
    G = ler_grafo_ant_suc(arq,"grafo-g-ant-suc.txt",G);

    H = ler_grafo_custos(arq,"grafo-h.txt");
    H = ler_grafo_ant_suc(arq,"grafo-h-ant-suc.txt",H);

    int opcao, opcao_1;
    int i, j, rotulo_partida, rotulo_chegada, id_partida, id_chegada;
    node partida, chegada;
    caminho caminho;

    printf("\n\n Atenção! Este programa trabalha apenas com grafos orientados.\n");
    printf("\n Escolha uma das opções abaixo: ");
    printf("\n (1) Imprimir informações dos nós de um dos Grafos lido.");
    printf("\n (2) Imprimir informações dos arcos de um dos Grafo lido.");
    printf("\n (3) Calcular menor caminho entre dois nós do Grafo G (arcos possuem apenas custos positivo).");
    printf("\n (4) Calcular menor caminho entre dois nós do Grafo H (arcos também possuem custos negativo).");
    printf("\n (5) Fechar programa.");

    printf("\n\n Digite a opção que deseja: ");
    scanf("%d",&opcao);

    j=1;
    while(j==1){
        switch(opcao){
            case 1:
                printf("\n Escolha uma das opções abaixo: ");
                printf("\n (1) Imprimir informações dos nós do Grafo G (arcos possuem apenas custos positivo).");
                printf("\n (2) Imprimir informações dos nós do Grafo H (arcos também possuem custos negativo).");

                printf("\n\n Digite a opção que deseja: ");
                scanf("%d",&opcao_1);

                if(opcao_1 == 1){ //Informação dos nós do Grafo G
                    for(i=0;i<G.n_nodes;i++){
                        imprimir_node_info_id(G,i);
                    }
                    opcao = menu_opcoes();
                    break;
                    }

                else
                    if(opcao_1 == 2){//Informação dos nós do Grafo H
                        for(i=0;i<H.n_nodes;i++){
                            imprimir_node_info_id(H,i);
                        }
                        opcao = menu_opcoes();
                        break;
                    }

                    else{
                        printf(" \n Digite uma opção válida para prosseguir!");
                        opcao = menu_opcoes();
                        break;
                    }

            case 2:
                printf("\n Escolha uma das opções abaixo: ");
                printf("\n (1) Imprimir informações dos arcos do Grafo G (arcos possuem apenas custos positivo).");
                printf("\n (2) Imprimir informações dos arcos do Grafo H (arcos também possuem custos negativo).");

                printf("\n\n Digite a opção que deseja: ");
                scanf("%d",&opcao_1);

                if(opcao_1 == 1){ //Informação dos arcos do Grafo G
                    for(i=0;i<G.n_arcos;i++){
                        imprimir_arco_info_id(G,i);
                    }
                    opcao = menu_opcoes();
                    break;
                    }

                else
                    if(opcao_1 == 2){//Informação dos arcos do Grafo H
                        for(i=0;i<H.n_arcos;i++){
                            imprimir_arco_info_id(H,i);
                        }
                        opcao = menu_opcoes();
                        break;
                    }

                    else{
                        printf(" \n Digite uma opção válida para prosseguir!");
                        opcao = menu_opcoes();
                        break;
                    }

            case 3: //Encontrar menor caminho entre dois nós (Dijkstra)
                printf("\n\n Digite o rótulo do nó de partida: ");
                scanf("%d",&rotulo_partida);

                printf(" Digite o rótulo do nó de chegada: ");
                scanf("%d",&rotulo_chegada);

                id_partida = buscar_id_node(G,rotulo_partida);
                id_chegada = buscar_id_node(G,rotulo_chegada);

                caminho = dijkstra(G, G.node[id_partida], G.node[id_chegada]);
                imprimir_caminho(G,caminho, G.node[id_partida], G.node[id_chegada]);

                opcao = menu_opcoes();
                break;

            case 4: //Encontrar menor caminho entre dois nós (Bellman-Ford)
                printf("\n\n Digite o rótulo do nó de partida: ");
                scanf("%d",&rotulo_partida);

                printf(" Digite o rótulo do nó de chegada: ");
                scanf("%d",&rotulo_chegada);

                id_partida = buscar_id_node(H,rotulo_partida);
                id_chegada = buscar_id_node(H,rotulo_chegada);

                caminho = bellman_ford(H, H.node[id_partida], H.node[id_chegada]);
                imprimir_caminho(H,caminho, H.node[id_partida], H.node[id_chegada]);

                opcao = menu_opcoes();
                break;

            case 5: //Fechar o programa
                j=0;
                printf(" ");
                system("pause");
                break;

            default: //Opção inválida
                printf(" \n Digite uma opção válida para prosseguir!");
                opcao = menu_opcoes();
        }
    }
}
