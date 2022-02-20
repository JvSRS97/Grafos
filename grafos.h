#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//Autor: João Victor Silva Reis dos Santos
//Universidade Federal de Sergipe
//Aracaju - SE
//biblioteca de grafos

int menu_opcoes(){
    int opcao = 0;
                printf("\n\n ");
                system("pause");
                system("cls");
                printf("\n\n Atenção! Este programa trabalha apenas com grafos orientados.\n");
                printf("\n Escolha uma das opções abaixo: ");
                printf("\n (1) Imprimir informações dos nós de um dos Grafos lido.");
                printf("\n (2) Imprimir informações dos arcos de um dos Grafo lido.");
                printf("\n (3) Calcular menor caminho entre dois nós do Grafo lido (arcos possuem apenas custos positivo).");
                printf("\n (4) Calcular menor caminho entre dois nós do Grafo lido (arcos também possuem custos negativo).");
                printf("\n (5) Fechar programa.");

                printf("\n\n Digite a opção que deseja: ");
                scanf("%d",&opcao);

    return opcao;
}

typedef struct{//estrutura nó
    int rotulo;
    int id; //o id de um nó é apenas o número que representa este nó (assim como o rótulo)
    int ant_node[10]; //antecessores (salva o id (número que identifica um nó) dos nós antecessores)
    int suc_node[10]; //sucessores (salva o id (número que identifica um nó) dos nós sucessores)
    int n_ant; //número de nós antecessores
    int n_suc; //número de nós sucessores
}node;

typedef struct{//estrutura arco
    int rotulo;
    int id; //o id de um arco é apenas o número que representa este arco (assim como o rótulo)
    node ini_node; //id do nó início
    node fim_node; //id do nó final
    int custo; //custo do arco
    int capacidade; //capacidade de fluxo do arco
    int fluxo; //fluxo do arco
}arco;

typedef struct{ //estrutura grafo
    node node[25]; //nós
    arco arco[35]; //arcos
    int n_nodes; //número de nós
    int n_arcos; //número de arcos
}grafo;
//---------------------------------------------------------------------------------------------------------------------------
grafo def_grafo_nodes (grafo G){//define os nós do grafo
    int i;

    printf("\n Instruções para adicionar nó: O rótulo de cada nó deve conter apenas um número ");
    printf("e deve ser diferente dos demais rótulos.\n");

    for(i=0;i<G.n_nodes;i++){
        G.node[i].id = i; //definindo i como número representante deste nó

        printf("\n Digite o rótulo para este nó (um número): "); //Definindo o rotulo do nó i
        scanf("%d",&G.node[i].rotulo);
        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o número de nós antecessores que este nó possui: "); //número de nós antecessores
        scanf("%d",&G.node[i].n_ant);

        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o número de nós sucessores que este nó possui: "); //número de nós antecessores
        scanf("%d",&G.node[i].n_suc);
        //---------------------------------------------------------------------------------------------------
    }
return G;
}
//---------------------------------------------------------------------------------------------------------------------------
int buscar_id_node(grafo G, int rotulo){//busca o id de um nó pelo rótulo
    int id = -1;
    int i;

    for(i=0;i<G.n_nodes;i++){
        if (rotulo == G.node[i].rotulo){
            id = G.node[i].id;
            i = G.n_nodes;
        }
    }
return id;
}
//---------------------------------------------------------------------------------------------------------------------------
grafo def_grafo_nodes_ant_suc(grafo G){//definindo nós antecessores e sucessores aos nós definidos
    int i,j,k;
    int rotulo_temp;

        //nós antecessores ao nó i
    printf("\n Definindo nós antecessores.");
    for(i=0;i<G.n_nodes;i++){
        j=0;
        if(G.node[i].n_ant > 0){ //se o número de nós antecessores for maior que zero
            while (j<G.node[i].n_ant){
                printf("\n Digite o rótulo deste nó antecessor ao nó %d: ",G.node[i].rotulo);
                scanf("%d",&rotulo_temp);

                G.node[i].ant_node[j] = buscar_id_node(G,rotulo_temp); //salva o id (número que identifica um nó) do nó antecessor
                j += 1;
            }
        }
    }

        //nós sucessores ao nó i
    printf("\n Definindo nós sucessores.");
    for(i=0;i<G.n_nodes;i++){
        j=0;
        if(G.node[i].n_suc > 0){ //se o número de nós antecessores for maior que zero
            while (j<G.node[i].n_suc){
                printf("\n Digite o rótulo deste nó sucessor ao nó %d: ",G.node[i].rotulo);
                scanf("%d",&rotulo_temp);

                G.node[i].suc_node[j] = buscar_id_node(G,rotulo_temp); //salva o id (número que identifica um nó) do nó sucessor
                j += 1;
            }
        }
    }
return G;
}
//---------------------------------------------------------------------------------------------------------------------------
void imprimir_node_info_id(grafo G, int i){ //função para imprimir informações sobre um nó através do id
    int j,k;
    printf("\n\n --> Características do nó %d:",G.node[i].rotulo);
    printf("\n *Id: %d.", G.node[i].id);
    printf("\n *Número de nós antecessores: %d.", G.node[i].n_ant);
    printf("\n *Número de nós sucessores: %d.", G.node[i].n_suc);

    if(G.node[i].n_ant > 0){
        printf("\n *Nós antecessores: [");

        for(j=0;j<G.node[i].n_ant;j++)
            if (j == (G.node[i].n_ant - 1))
                printf("%d]", G.node[G.node[i].ant_node[j]].rotulo);
            else
                printf("%d,", G.node[G.node[i].ant_node[j]].rotulo);
    }

    if(G.node[i].n_suc > 0){
        printf("\n *Nós sucessores: [");
        for(j=0;j<G.node[i].n_suc;j++){
            if (j == (G.node[i].n_suc - 1))
                printf("%d]", G.node[G.node[i].suc_node[j]].rotulo);
            else
                printf("%d,", G.node[G.node[i].suc_node[j]].rotulo);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------------------
void imprimir_node_info_rotulo(grafo G, int rotulo){//função para imprimir informações sobre um nó através do rótulo
    int id;
    id = buscar_id_node(G,rotulo);
    imprimir_node_info_id(G,id);
}

grafo def_grafo_arcos (grafo G){//define os arcos do grafo
    int i,j,k;

    printf("\n Instruções para adicionar arco: O rótulo de cada arco deve conter apenas um número ");
    printf("e deve ser diferente dos demais rótulos.\n");

    for(i=0;i<G.n_nodes;i++){
        G.arco[i].id = i; //definindo i como número representante deste nó

        printf("\n Digite o rótulo para este arco (um número): "); //Definindo o rotulo do arco i
        scanf("%d",&G.arco[i].rotulo);
        //---------------------------------------------------------------------------------------------------
        printf("\n Digite a capacidade de fluxo deste arco: "); //capacidade de fluxo do arco i
        scanf("%d",&G.arco[i].capacidade);

        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o fluxo do arco: "); //fluxo do arco i
        scanf("%d",&G.arco[i].fluxo);
        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o custo do arco: "); //custo do arco i
        scanf("%d",&G.arco[i].custo);
        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o rótulo do nó inicial deste arco: "); //nó inicial
        scanf("%d",&j);
        G.arco[i].ini_node = G.node[buscar_id_node(G,j)];
        //---------------------------------------------------------------------------------------------------
        printf("\n Digite o rótulo do nó final deste arco: "); //nó final
        scanf("%d",&k);
        G.arco[i].fim_node = G.node[buscar_id_node(G,k)];
        //---------------------------------------------------------------------------------------------------
    }
return G;
}
//---------------------------------------------------------------------------------------------------------------------------
int buscar_id_arco(grafo G, int rotulo){//busca o id de um arco pelo rótulo
    int id = -1;
    int i;

    for(i=0;i<G.n_arcos;i++){
        if (rotulo == G.arco[i].rotulo){
            id = G.arco[i].id;
            i = G.n_arcos;
        }
    }
return id;
}
//---------------------------------------------------------------------------------------------------------------------------
void imprimir_arco_info_id(grafo G, int i){
    printf("\n -->Características do arco %d:",G.arco[i].rotulo);
    printf("\n *Id: %d",G.arco[i].id);
    printf("\n *Capacidade de fluxo: %d.",G.arco[i].capacidade);
    printf("\n *Fluxo do arco: %d.",G.arco[i].fluxo);
    printf("\n *Custo do arco: %d.",G.arco[i].custo);
    printf("\n *Nó inicial deste arco: %d.", G.arco[i].ini_node.rotulo);
    printf("\n *Nó final deste arco: %d.\n",G.arco[i].fim_node.rotulo);
}
void imprimir_arco_info_rotulo(grafo G, int rotulo){
    int id;
    id = buscar_id_arco(G,rotulo);
    imprimir_arco_info_id(G,id);
}

arco buscar_arco(grafo G, int no_inicial_id, int no_final_id){//encontra um arco através do id dos nós inicial e final
    arco A;
    int i,j,k;

    for(i=0;i<G.n_arcos;i++){
        j = G.arco[i].ini_node.id;
        k = G.arco[i].fim_node.id;

        if(no_inicial_id == j && no_final_id == k)
            A = G.arco[i];
    }
return A;
}

//Função para ler um grafo
grafo ler_grafo(FILE *arq, char nome_do_arquivo[]){
//n_nodes n_arcos rotulo n_ant n_suc ... rotulo capacidade fluxo custo  rotulo_ini_node rotulo_fim_node
int V[400];
grafo G;
	arq = fopen(nome_do_arquivo, "r");

  if (arq == NULL){// Se houve erro na abertura
     printf("\n Problemas na abertura do arquivo\n");
     exit(0);
  }
	else{
		int k=0;
		while((fscanf(arq,"%d ", &V[k])) != EOF){
				k+=1;
		}
		fclose(arq);

		int i;
		G.n_nodes = V[0]; //número de nós
		G.n_arcos = V[1]; //número de arcos
		k=2;
		for(i=0;i<G.n_nodes;i++){
            G.node[i].id = i;
            G.node[i].rotulo = V[k];
            G.node[i].n_ant = V[k+1];
            G.node[i].n_suc = V[k+2];
            k += 3;
        }
        for(i=0;i<G.n_arcos;i++){
            G.arco[i].id = i;
            G.arco[i].rotulo = V[k];
            G.arco[i].capacidade = V[k+1];
            G.arco[i].fluxo = V[k+2];
            G.arco[i].custo = V[k+3];
            G.arco[i].ini_node = G.node[buscar_id_node(G,V[k+4])];
            G.arco[i].fim_node = G.node[buscar_id_node(G,V[k+5])];
            k += 6;
        }
	}
return G;
}
//----------------------------------------------------------------------------------------------------------------------------
//Função para ler um grafo com arcos com apenas custo
grafo ler_grafo_custos(FILE *arq, char nome_do_arquivo[]){
//n_nodes n_arcos rotulo n_ant n_suc ... rotulo capacidade fluxo custo  rotulo_ini_node rotulo_fim_node
int V[600];
grafo G;
	arq = fopen(nome_do_arquivo, "r");

  if (arq == NULL){// Se houve erro na abertura
     printf("\n Problemas na abertura do arquivo\n");
     exit(0);
  }
	else{
		int k=0;
		while((fscanf(arq,"%d ", &V[k])) != EOF){
				k+=1;
		}
		fclose(arq);

		int i;
		G.n_nodes = V[0]; //número de nós
		G.n_arcos = V[1]; //número de arcos
		k=2;
		for(i=0;i<G.n_nodes;i++){
            G.node[i].id = i;
            G.node[i].rotulo = V[k];
            G.node[i].n_ant = V[k+1];
            G.node[i].n_suc = V[k+2];
            k += 3;
        }
        for(i=0;i<G.n_arcos;i++){
            G.arco[i].id = i;
            G.arco[i].rotulo = V[k];
            G.arco[i].capacidade = 0;
            G.arco[i].fluxo = 0;
            G.arco[i].custo = V[k+1];
            G.arco[i].ini_node = G.node[buscar_id_node(G,V[k+2])];
            G.arco[i].fim_node = G.node[buscar_id_node(G,V[k+3])];
            k += 4;
        }
	}
return G;
}
//----------------------------------------------------------------------------------------------------------------------------
//Função para ler nós antecessores e nós sucessores (rótulos)
grafo ler_grafo_ant_suc(FILE *arq, char nome_do_arquivo[],grafo G){
//n_nodes n_arcos rotulo n_ant n_suc ... rotulo capacidade fluxo custo  rotulo_ini_node rotulo_fim_node
int V[600];
	arq = fopen(nome_do_arquivo, "r");

  if (arq == NULL){// Se houve erro na abertura
     printf("\n Problemas na abertura do arquivo\n");
     exit(0);
  }
	else{
		int k=0;
		while((fscanf(arq,"%d ", &V[k])) != EOF){
				k+=1;
		}
		fclose(arq);

		int i,j;
		k=0;
		for(i=0;i<G.n_nodes;i++){
            if(G.node[i].n_ant > 0){//se o número de antecessores do nó i for maior que zero
              for(j=0;j<G.node[i].n_ant;j++){ //j < número de antecessores do nó i
                G.node[i].ant_node[j] = buscar_id_node(G,V[k]);
                k += 1;
              }
            }
            if(G.node[i].n_suc > 0){//se o número de sucessores do nó i for maior que zero
              for(j=0;j<G.node[i].n_suc;j++){ //j < número de sucessores do nó i
                G.node[i].suc_node[j] = buscar_id_node(G,V[k]);
                k += 1;
              }
            }
        }
	}
return G;
}
//----------------------------------------------------------------------------------------------------------------------------
typedef struct{
    node node[20]; //salva o nó pesquisado na entrada i
    node precedente[20]; //salva o precedente da entrada i
    int tam;
}caminho;
//----------------------------------------------------------------------------------------------------------------------------
int encontrar_min_rotulo_node(grafo G){//retorna o id do nó de menor rótulo > 0
    int id = -2;
    int i;
    int min_rotulo = 32000;//infinito
    for(i=0;i<G.n_nodes;i++)
      if((G.node[i].rotulo > 0) && (G.node[i].rotulo < min_rotulo)){
            min_rotulo = G.node[i].rotulo;
            id = G.node[i].id;
    }
return id;
}
//----------------------------------------------------------------------------------------------------------------------------
int encontrar_min_rotulo_node_1(grafo G){//retorna o id do nó de menor rótulo
    int id = -2;
    int i;
    int min_rotulo = 32000;//infinito
    for(i=0;i<G.n_nodes;i++)
      if((G.node[i].rotulo > -32000) && (G.node[i].rotulo < min_rotulo)){
            min_rotulo = G.node[i].rotulo;
            id = G.node[i].id;
    }
return id;
}
//----------------------------------------------------------------------------------------------------------------------------
int verificar_node_em_caminho(caminho caminho, node A){//retorna 1 se o nó pertence ao caminho e 0 se não pertence
    int resultado = 0;
    int i;
    for(i=0;i<caminho.tam;i++)
        if(A.id == caminho.node[i].id){
         resultado = 1;
         i = caminho.tam;
    }
return resultado;
}
//----------------------------------------------------------------------------------------------------------------------------
int buscar_id_de_node_em_caminho(node A, caminho caminho_AB){
    int i;
    int id = -1;
    for(i=0;i<caminho_AB.tam;i++){
       if(A.id == caminho_AB.node[i].id)
            id = caminho_AB.node[i].id;
    }
return id;
}
//----------------------------------------------------------------------------------------------------------------------------
int buscar_antecessor_de_node_em_caminho(int A, caminho caminho_AB){//busca antecessor de um nó A em um caminho pelo id de A
    int i;
    int id = -1;
    for(i=0;i<=caminho_AB.tam;i++){
        if(caminho_AB.node[i].id == A){
            id = caminho_AB.precedente[i].id;
            i = caminho_AB.tam + 1;
        }
    }
return id;
 }
//----------------------------------------------------------------------------------------------------------------------------
void imprimir_caminho(grafo G,caminho caminho_AB, node A, node B){
    int i;
    int custo = 0;
    int marcador = 0;
    int vet_caminho[20];
    int vet_aux[20];
    vet_caminho[0] = B.id;

    for(i=1;i<=caminho_AB.tam;i++){
        vet_caminho[i] = buscar_antecessor_de_node_em_caminho(vet_caminho[i-1],caminho_AB);
        marcador += 1;
        if(vet_caminho[i] == A.id)
            i = caminho_AB.tam + 1;
    }

    for(i=0;i<=marcador;i++)
            vet_aux[i] = vet_caminho[marcador-i];

    printf("\n Caminho nó %d -> %d: [",G.node[A.id].rotulo,G.node[B.id].rotulo);
    for(i=0;i<=marcador;i++){
        if(i < marcador)
            custo += buscar_arco(G, vet_aux[i],vet_aux[i+1]).custo;
        if(i != (marcador))
            printf("%d,",G.node[vet_aux[i]]);
        else
            printf("%d]",G.node[vet_aux[i]]);
    }
    printf("\n Custo do caminho: %d.\n\n", custo);
}
//----------------------------------------------------------------------------------------------------------------------------
caminho dijkstra(grafo G,node node_A, node node_B){
    grafo A;
    A = G;

    caminho caminho_AB;
    caminho_AB.node[0] = node_A;
    caminho_AB.precedente[0] = node_A;
    caminho_AB.tam = 0;

    int infinito = 32000;
    int i,j;
    //1º passo:
    for(i=0;i<A.n_nodes;i++){//pondo rótulo 0 no nó de partida e infinito nos demais
        if(i == node_A.id)
            A.node[i].rotulo = 0;
        else
            A.node[i].rotulo = infinito;
    }
    //2º passo:
    //a primeira iteração será manual
    node node_atual, aux_node;
    node_atual = caminho_AB.node[0];
    arco aux_arco;
    int aux_id;
    node aux_precedente[20];
    aux_precedente[node_atual.id] = node_atual;

    //iteração manual
    if(node_atual.n_suc > 0)
        for(i=0;i<node_atual.n_suc;i++){
            aux_node = A.node[node_atual.suc_node[i]];//sucessor do nó atual
            aux_arco = buscar_arco(A,node_atual.id,aux_node.id);//arco que liga nó atual com sucessor
            if(aux_arco.custo < aux_node.rotulo){//se custo do arco for menor que o rótulo do sucessor do nó atual
                aux_node.rotulo = aux_arco.custo; //atualiza o rótulo do nó sucessor
                A.node[aux_node.id] = aux_node;//atualiza o nó sucessor no grafo A
                aux_precedente[aux_node.id] = node_atual; //salva o precedente do nó de id j na casa j
            }
        }
        A.node[node_atual.id].rotulo = -2;//pesquisado
        //obs.: note que caminho_AB possui apenas o nó inicial. Esta etapa foi para tirar rótulos infinitos dos sucessores dele
    i=1;
    while(i >0){
        aux_id = encontrar_min_rotulo_node(A);
        if(aux_id != (-2) && aux_id < A.n_nodes){//encontra o rótulo mínimo > 0, se for = -2 é pq todos os nó foram pesquisados
          node_atual = A.node[aux_id];
          if(node_atual.n_suc > 0)
            for(j=0;j<node_atual.n_suc;j++){
                aux_node = A.node[node_atual.suc_node[j]];
                aux_arco = buscar_arco(A,node_atual.id,aux_node.id);
                if((node_atual.rotulo + aux_arco.custo) < aux_node.rotulo){
                    aux_node.rotulo = node_atual.rotulo + aux_arco.custo; //atualiza o rótulo do nó sucessor
                    A.node[aux_node.id].rotulo = aux_node.rotulo;//atualiza o rótulo do nó sucessor no grafo A
                    aux_precedente[aux_node.id] = node_atual;//salva o precedente do nó de id j na casa j
                }
            }
            caminho_AB.tam += 1; //atualiza o número de nós pesquisados
            caminho_AB.node[caminho_AB.tam] = G.node[node_atual.id]; //insere o nó pesquisado
            caminho_AB.precedente[caminho_AB.tam] = aux_precedente[node_atual.id]; //atualiza o nó precedente
            A.node[node_atual.id].rotulo = -2;//pesquisado
        }
        else{
            A.node[node_atual.id].rotulo = -infinito - 1;
            i = -2;
        }
    }
return caminho_AB;
}
//----------------------------------------------------------------------------------------------------------------------------
caminho bellman_ford(grafo G,node node_A, node node_B){
    grafo A;
    A = G;

    caminho caminho_AB;
    caminho_AB.node[0] = node_A;
    caminho_AB.precedente[0] = node_A;
    caminho_AB.tam = 0;

    int infinito = 32000;
    int i,j;
    //1º passo:
    for(i=0;i<A.n_nodes;i++){//pondo rótulo 0 no nó de partida e infinito nos demais
        if(i == node_A.id)
            A.node[i].rotulo = 0;
        else
            A.node[i].rotulo = infinito;
    }
    //2º passo:
    //a primeira iteração será manual
    node node_atual, aux_node;
    node_atual = caminho_AB.node[0];
    arco aux_arco;
    int aux_id;
    node aux_precedente[20];
    aux_precedente[node_atual.id] = node_atual;

    //iteração manual
    if(node_atual.n_suc > 0)
        for(i=0;i<node_atual.n_suc;i++){
            aux_node = A.node[node_atual.suc_node[i]];//sucessor do nó atual
            aux_arco = buscar_arco(A,node_atual.id,aux_node.id);//arco que liga nó atual com sucessor
            if(aux_arco.custo < aux_node.rotulo){//se custo do arco for menor que o rótulo do sucessor do nó atual
                aux_node.rotulo = aux_arco.custo; //atualiza o rótulo do nó sucessor
                A.node[aux_node.id] = aux_node;//atualiza o nó sucessor no grafo A
                aux_precedente[aux_node.id] = node_atual; //salva o precedente do nó de id j na casa j
            }
        }
        A.node[node_atual.id].rotulo = -infinito;//pesquisado
        //obs.: note que caminho_AB possui apenas o nó inicial. Esta etapa foi para tirar rótulos infinitos dos sucessores dele
    i=1;
    while(i >0){
        aux_id = encontrar_min_rotulo_node_1(A);//encontra o id do nó de rótulo mínimo pesquisado
        if(aux_id != (-2) && aux_id < A.n_nodes){//id != -2 para garantir que a função não teve erro
          node_atual = A.node[aux_id];
          if(node_atual.n_suc > 0)
            for(j=0;j<node_atual.n_suc;j++){
                aux_node = A.node[node_atual.suc_node[j]];
                aux_arco = buscar_arco(A,node_atual.id,aux_node.id);
                if((node_atual.rotulo + aux_arco.custo) < aux_node.rotulo){
                    aux_node.rotulo = node_atual.rotulo + aux_arco.custo; //atualiza o rótulo do nó sucessor
                    A.node[aux_node.id].rotulo = aux_node.rotulo;//atualiza o rótulo do nó sucessor no grafo A
                    aux_precedente[aux_node.id] = node_atual;//salva o precedente do nó de id j na casa j
                }
            }
            caminho_AB.tam += 1; //atualiza o número de nós pesquisados
            caminho_AB.node[caminho_AB.tam] = G.node[node_atual.id]; //insere o nó pesquisado
            caminho_AB.precedente[caminho_AB.tam] = aux_precedente[node_atual.id]; //atualiza o nó precedente
            A.node[node_atual.id].rotulo = -infinito;//pesquisado
        }
        else{
            A.node[node_atual.id].rotulo = -infinito;
            i = -2;
        }
    }
return caminho_AB;
}
