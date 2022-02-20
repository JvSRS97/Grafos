Este programa encontra o caminho de menor custo entre dois nós de um grafo dado, seja ele com custos apenas positivos ou com custos positivos e negativos.


--> Como montar o arquivo de leitura de antecessores e sucessores
nó 1 ant suc ... nó 2 ant suc ... nó i ant suc
exemplo: nó 1 não possui antecessores e possui sucessores, 
nó 2 possui sucessores e antecessores, nó 15 possui 
antecessores e não possui sucessores.

2 4 1 3 5 8 9 12 14
|_| | |___| |_____|
 v  v   v      v
 1  2   2     15

--> Como montar o arquivo de leitura do grafo - 1o jeito
n_nodes n_arcos rotulo n_ant n_suc ... rotulo capacidade fluxo custo  ini_node fim_node
n-nodes n_arcos nós ... arcos

--> Como montar o arquivo de leitura do grafo - 2o jeito
n_nodes n_arcos rotulo n_ant n_suc ... rotulo custo ini_node fim_node
n-nodes n-arcos nós...arcos