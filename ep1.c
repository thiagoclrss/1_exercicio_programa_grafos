// 1º Exercício-programa de Grafos
//Equipe: Edmilson Bernardino Souza, Davison Lucas Mendes Viana e Thiago Colares de Souza

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct aresta {
    int origem;
    int destino;
    int custo;
};

struct unionFind {
    int *pai;      
    int *rank;     
};

void inicializarUnionFind(struct unionFind *uf, int n) {
    uf->pai = malloc(n * sizeof(int));
    uf->rank = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        uf->pai[i] = i; 
        uf->rank[i] = 0; 
    }
}

int encontrar(struct unionFind *uf, int x) {
    if (uf->pai[x] != x) {
        uf->pai[x] = encontrar(uf, uf->pai[x]); 
    }
    return uf->pai[x];
}

void unir(struct unionFind *uf, int x, int y) {
    int raizX = encontrar(uf, x);
    int raizY = encontrar(uf, y);
    if (raizX != raizY) {
        if (uf->rank[raizX] < uf->rank[raizY]) {
            uf->pai[raizX] = raizY;
        } else if (uf->rank[raizX] > uf->rank[raizY]) {
            uf->pai[raizY] = raizX;
        } else {
            uf->pai[raizY] = raizX;
            uf->rank[raizX]++;
        }
    }
}

void liberarUnionFind(struct unionFind *uf) {
    free(uf->pai);
    free(uf->rank);
}

int compararPorCusto(const void *a, const void *b) {
    struct aresta *arestaA = (struct aresta *)a;
    struct aresta *arestaB = (struct aresta *)b;
    return arestaA->custo - arestaB->custo;
}

void kruskal(int quantidadeDeVertices, int quantidadeDeArestas, struct aresta *grafo){
    int custoTotal = 0;
    int agmIndex = 0;
    struct aresta *arvoreGeradoraMinima = malloc(sizeof(struct aresta) * (quantidadeDeVertices - 1));

    qsort(grafo, quantidadeDeArestas, sizeof(struct aresta), compararPorCusto);
    
    struct unionFind uf;
    inicializarUnionFind(&uf, quantidadeDeVertices);

    //construindo a agm
    for (int i = 0; i < quantidadeDeArestas && agmIndex < quantidadeDeVertices - 1; i++) {
        struct aresta arestaAtual = grafo[i];

        // Verifica se a aresta atual forma um ciclo
        if (encontrar(&uf, arestaAtual.origem - 1) != encontrar(&uf, arestaAtual.destino - 1)) {
            arvoreGeradoraMinima[agmIndex++] = arestaAtual; // Adiciona a aresta à MST
            custoTotal += arestaAtual.custo;
            unir(&uf, arestaAtual.origem - 1, arestaAtual.destino - 1);
        }
    }
    
    
    printf("Árvore geradora de custo mínimo:\n");
    for (int i = 0; i < agmIndex; i++) {
        printf("Origem: %d, Destino: %d, Custo: %d\n", 
        arvoreGeradoraMinima[i].origem, 
        arvoreGeradoraMinima[i].destino, 
        arvoreGeradoraMinima[i].custo);
    }

    printf("Custo total: %d\n", custoTotal);


    free(arvoreGeradoraMinima);
    liberarUnionFind(&uf);
}


int main(){

    int quantidadeDeVertices = 0;   	                    
    int quantidadeDeArestas  = 0; 		                    	                			           
    char caminhoDoArquivo[50];
    struct aresta *grafo = NULL;
    

    FILE *arquivo = NULL;
    

    while(arquivo == NULL){
        printf("Insira o caminho do arquivo e pressione Enter: \n");
        fgets(caminhoDoArquivo, sizeof(caminhoDoArquivo), stdin);
        //Remove o último caractere do caminho, pois o fgets armazena a quebra de linha '\n'
        char *p_chr = strchr(caminhoDoArquivo, '\n'); 
        if(p_chr != NULL) 
            *p_chr = '\0';
        arquivo = fopen(caminhoDoArquivo, "r");
    }

    //Lê o arquivo para capturar a quantidade de vertices e a quantidade de arestas e armazená-las em suas respectivas variáveis
    fscanf(arquivo, "%d %d", &quantidadeDeVertices, &quantidadeDeArestas); 
    
    grafo = malloc(sizeof(struct aresta) * quantidadeDeArestas);

    //Lê o arquivo para capturar as arestas e armazená-las na lista
    for (int i = 0; i < quantidadeDeArestas; i++){
        fscanf(arquivo, "%d %d %d", 
        &grafo[i].origem, 
        &grafo[i].destino, 
        &grafo[i].custo);
    }

    fclose(arquivo);
    
    kruskal(quantidadeDeVertices, quantidadeDeArestas, grafo);

    free(grafo);

    return 0;
}
