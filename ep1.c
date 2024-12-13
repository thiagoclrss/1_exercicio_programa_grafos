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

int compararPorCusto(const void *a, const void *b) {
    struct aresta *arestaA = (struct aresta *)a;
    struct aresta *arestaB = (struct aresta *)b;
    return arestaA->custo - arestaB->custo;
}

void kruskal(int quantidadeDeVertices, int quantidadeDeArestas, struct aresta *listaDeArestas){
    int custoTotal;

    //printf("quantidade de vertices e quantidade de arestas: %d %d\n", quantidadeDeVertices, quantidadeDeArestas);
    
    qsort(listaDeArestas, quantidadeDeArestas, sizeof(struct aresta), compararPorCusto);
    
    for (int i = 0; i < quantidadeDeArestas; i++) {
        printf("Aresta %d: Origem = %d, Destino = %d, Custo = %d\n",
               i, listaDeArestas[i].origem, listaDeArestas[i].destino, listaDeArestas[i].custo);
    }
}


int main(){

    int quantidadeDeVertices = 0;   	                    
    int quantidadeDeArestas  = 0; 		                    	                			           
    char caminhoDoArquivo[50];
    struct aresta *listaDeArestas = NULL;
    

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
    
    listaDeArestas = malloc(sizeof(struct aresta) * quantidadeDeArestas);

    //Lê o arquivo para capturar as arestas e armazená-las na lista
    for (int i = 0; i < quantidadeDeArestas; i++){
        fscanf(arquivo, "%d %d %d", 
        &listaDeArestas[i].origem, 
        &listaDeArestas[i].destino, 
        &listaDeArestas[i].custo);
    }

    fclose(arquivo);

    kruskal(quantidadeDeVertices, quantidadeDeArestas, listaDeArestas);

    free(listaDeArestas);

    return 0;
}
