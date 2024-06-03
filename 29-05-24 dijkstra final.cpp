#include <iostream>
#include <string>
#include <locale>
#include <locale.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <vector>

#define QTD 9999
#define MAX 5

using namespace std;

void dijkstra(int G[MAX][MAX], int n, int inicial);

int G[MAX][MAX];

void inicializarGrafo() {
    for (int l = 0; l < MAX; l++) {
        for (int p = 0; p < MAX; p++) {
            G[l][p] = -1;
        }
    }

    G[0][1] = 100;
    G[0][2] = 800;
    G[1][3] = 500;
    G[1][4] = 700;
    G[2][1] = 200;
    G[2][3] = 500;
    G[4][3] = 100;
}

int minDist(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < MAX; v++) {
        if (!sptSet[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[MAX][MAX], int src, int dist[], int parent[]) {
    bool sptSet[MAX];

    for (int i = 0; i < MAX; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < MAX - 1; count++) {
        int u = minDist(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < MAX; v++) {
            if (!sptSet[v] && graph[u][v] != -1 && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

void encontrarCaminhoMaisCurto(int src, int dest) {
    int dist[MAX];
    int parent[MAX];

    dijkstra(G, src, dist, parent);

    std::cout << "Distância do vértice " << src << " ao vértice " << dest << " é " << dist[dest] << std::endl;

    // Imprimir caminho
    if (dist[dest] == INT_MAX) {
        std::cout << "Não há caminho do vértice " << src << " ao vértice " << dest << std::endl;
    } else {
        std::vector<int> path;
        for (int v = dest; v != -1; v = parent[v]) {
            path.push_back(v);
        }
        std::cout << "Caminho: ";
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << path[i] << (i != 0 ? " -> " : "\n");
        }
    }
    sleep(5);
    system("cls");
}

void calcularDistanciaEntreDoisPontos(int src, int dest) {
    int dist[MAX];
    int parent[MAX];

    dijkstra(G, src, dist, parent);

    std::cout << "Distância do vértice " << src << " ao vértice " << dest << " é " << dist[dest] << std::endl;
    
    sleep(5);
    system("cls");
}


int numVertices = 5;
    void adicionarVertice() {
    if (numVertices >= MAX) {
        printf("Número máximo de vértices atingido.\n");
        return;
    }
    
    int numVizinhos;
    printf("Quantos vizinhos o novo vértice terá? ");
    scanf("%d", &numVizinhos);

    int novoVertice = numVertices;
    numVertices++;
    printf("Vértice %d adicionado.\n", novoVertice);

    for (int i = 0; i < numVizinhos; i++) {
        int vizinho, peso;
        printf("Informe o vértice vizinho: ");
        scanf("%d", &vizinho);
        printf("Informe a distância até o vértice %d: ", vizinho);
        scanf("%d", &peso);
        
        if (vizinho >= numVertices) {
            printf("Vértice inválido.\n");
            i--;
        } else {
            G[novoVertice][vizinho] = peso;
            G[vizinho][novoVertice] = peso; // Se o grafo for não-direcionado
            printf("Aresta adicionada entre %d e %d com peso %d.\n", novoVertice, vizinho, peso);
        }
    }
}


void visualizarGrafo() {
    for (int l = 0; l < MAX; l++) {
        for (int p = 0; p < MAX; p++) {
            if (G[l][p] != -1) {
                printf("G[%d][%d] = %d;\n", l, p, G[l][p]);
            }
        }
    }
    sleep(5);
    system("cls"); // Use "cls" no Windows, "clear" no Unix/Linux/Mac
}




void alterarPesosArestas() {
    // Implementação para alterar pesos das arestas
    int u, v, peso;
    printf("Informe o nó inicial: ");
    scanf("%d", &u);
    printf("Informe o nó final: ");
    scanf("%d", &v);
    printf("Informe o peso da aresta: ");
    scanf("%d", &peso);
    G[u][v] = peso;
    printf("Peso alterado.\n");
    sleep(3);
    system("cls");
}

void informacoesSobreSistema() {
    printf("Nosso sistema tem a funcionalidade de encontrar o caminho mais curto entre um ponto de origem de distribuição de fibra até seu destino final, encontrando o menor caminho entre esse trajeto.\n");
    sleep(8);
    system("cls");
}

void teoriaDoAlgoritmo() {
    printf("O sistema é baseado no algoritmo de Dijkstra, que tem por finalidade encontrar o caminho de custo mínimo entre a origem e o destino, ou seja, o caminho menos custoso para realizar a instalação da rede.\n");
    sleep(8);
    system("cls");
}

void adicionarAresta(int origem, int destino, int peso) {
    if (origem >= 0 && origem < MAX && destino >= 0 && destino < MAX) {
        G[origem][destino] = peso;
        std::cout << "Aresta adicionada: G[" << origem << "][" << destino << "] = " << peso << std::endl;
    } else {
        std::cout << "Erro: índice de vértice fora do intervalo." << std::endl;
    }
    sleep(4);
    system("cls");
}

void removerAresta(int origem, int destino) {
    if (origem >= 0 && origem < MAX && destino >= 0 && destino < MAX) {
        G[origem][destino] = -1;
        std::cout << "Aresta removida: G[" << origem << "][" << destino << "]" << std::endl;
    } else {
        std::cout << "Erro: índice de vértice fora do intervalo." << std::endl;
    }
    sleep(4);
    system("cls");
}


void mostrarMenuPrincipal() {
	int opcao, origem, destino, peso;
    system("cls");
    printf("\n");
    printf(" |V| _ __  \n");
    printf(" | |(/_| ||_| \n");
    printf("\n");

    int escolha;

    do {
        printf("1. Encontrar caminho mais curto entre dois pontos\n\n");
        printf("2. Calcular distância mínima a partir de um ponto específico\n\n");
        printf("3. Adicionar Aresta\n\n");
        printf("4. Remover Aresta\n\n");
        printf("5. Visualizar o caminho\n\n");
        printf("6. Alterar distancias entre os pontos\n\n");
        printf("7. Sobre o sistema\n\n");
        printf("8. Teoria dos grafos\n\n");
        printf("0. Sair\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                std::cout << "Digite a origem e destino para encontrar o caminho mais curto: ";
                std::cin >> origem >> destino;
                encontrarCaminhoMaisCurto(origem, destino);
                break;
            case 2:
                std::cout << "Digite a origem e destino para calcular a distância: ";
                std::cin >> origem >> destino;
                calcularDistanciaEntreDoisPontos(origem, destino);
                break;
            case 3:
                std::cout << "Digite a origem, destino e peso da aresta: ";
                std::cin >> origem >> destino >> peso;
                adicionarAresta(origem, destino, peso);
                break;
            case 4:
                std::cout << "Digite a origem e destino da aresta a remover: ";
                std::cin >> origem >> destino;
                removerAresta(origem, destino);
                break;

			case 5:
                visualizarGrafo();
                break;
            case 6:
                alterarPesosArestas();
                break;
            case 7:
                informacoesSobreSistema();
                break;
            case 8:
                teoriaDoAlgoritmo();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Escolha novamente.\n");
                break;
        }

    } while (escolha != 0);
}

void mostrarMenu() {
   printf("\n \n");
    printf("   _                                      __                               _    o \n");
    printf("  |_) _ __       o __  _| _     _  _    (_  o  _ _|_ _ __  _     _| _    | \  o  |  |  _ _|_ __ _ \n");
    printf("  |_)(/_|||  \\_/ | | |(_|(_)   (_|(_)   __) | _>  |_(/_|||(_|   (_|(/_   |_/ | _|  |<_>  |_ | (_| \n");                          
	printf("\n\n");
    printf("=======================================================================================================================\n");
    printf("Este sistema usa como base o algoritmo de Dijkstra para encontrar o ponto minimo entre o ponto de origem e o ponto de destino\n\n\n");
    printf("Desenvolvido por:\n\n");
    printf("Joao Vitor Berger \n");
    printf("Gabriel de Souza Gava \n\n");
    time_t agora = time(NULL);
    struct tm *dataAtual = localtime(&agora);
    printf("=======================================================================================================================\n");
    printf("Data atual: %02d/%02d/%d\n", dataAtual->tm_mday, dataAtual->tm_mon + 1, dataAtual->tm_year + 1900);
    printf("=======================================================================================================================\n\n");
    printf("Aguarde para ser redirecionado para o menu...\n");

    for (int i = 5; i >= 0; --i) {
        printf("\n Redirecionamento em %d\n", i);
        sleep(1);
    };

    mostrarMenuPrincipal();
}

void dijkstra(int G[MAX][MAX], int n, int inicial) {
    int custo[n][n], distancia[n], pred[n];
    int visitado[n], cont, distanciamin, proxno, i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (G[i][j] == -1)
                custo[i][j] = QTD;
            else
                custo[i][j] = G[i][j];

    for (i = 0; i < n; i++) {
        distancia[i] = custo[inicial][i];
        pred[i] = inicial;
        visitado[i] = 0;
    }

    distancia[inicial] = 0;
    visitado[inicial] = 1;
    cont = 1;

    while (cont < n - 1) {
        distanciamin = QTD;

        for (i = 0; i < n; i++)
            if (distancia[i] < distanciamin && !visitado[i]) {
                distanciamin = distancia[i];
                proxno = i;
            }

        visitado[proxno] = 1;

        for (i = 0; i < n; i++) {
            if (!visitado[i])
                if (distanciamin + custo[proxno][i] < distancia[i]) {
                    distancia[i] = distanciamin + custo[proxno][i];
                    pred[i] = proxno;
                }
        }
        cont++;
    }

    for (i = 0; i < n; i++) {
        if (i != inicial) {
            printf("\nDistância do nó %d = %d", i, distancia[i]);
            printf("\nCaminho = %d", i);
            j = i;
            do {
                j = pred[j];
                printf("<-%d", j);
            } while (j != inicial);
        }
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");
    inicializarGrafo();
    mostrarMenu();

    return 0;
}
