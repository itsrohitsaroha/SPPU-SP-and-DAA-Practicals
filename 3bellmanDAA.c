#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int INF = 1000000000;

//Structure of edge
struct edge{
    int src, dst, weight;
};

//Bellmanford function to calculate shortest distance of all vertices from `source`.
void bellmanford(int V, int E, int source, struct edge * graph, int dis[]){

    dis[source] = 0;
    bool ok = 0;
    for(int i = 0; i < V - 1; i++){
        ok = 0;

        for(int j = 0; j < E; j++){
            int src = graph[j].src;
            int dst = graph[j].dst;
            int weight = graph[j].weight;

            if(dis[src] != INF && dis[dst] > dis[src] + weight){
                dis[dst] = dis[src] + weight;
                ok = 1;
            }
        }
        if(!ok){
            break;
        }
    }

    //Checking if negative cycle exists.
    if(!ok)
    for(int j = 0; j < E; j++){
        int src = graph[j].src;
        int dst = graph[j].dst;
        int weight = graph[j].weight;
        if(dis[src] != INF && dis[dst] > dis[src] + weight){
            printf("\n Graph has a negative cycle.\n");
            return;
        }
    }
    //Print distance of all vertices.
    printf("\n\tVertex\t\tDistance");
    printf("\n\t------\t\t--------");
    for(int i = 1; i <= V; i++){
        printf("\n\t  %d\t\t  %d", i, dis[i]);
    }
}

int main(){

    int E, V, source;
    struct edge * graph;
    bool map[100][100] = {0};
    printf("\n\t\t\tBellmanford Algorithm");
    printf("\n\t\t\t---------------------\n");
    printf("\n Enter the no. of vertices : ");
    do{
        scanf("%d", &V);
        if(V > 1)
            break;
        printf("\n No. of vertices must be greater than 1.");
        printf("\n Enter the no. of vertices : ");
    }
    while(1);

    printf("\n Enter the no. of edges : ");
    do{
        scanf("%d", &E);
        if(((E >= V - 1) && (E <= ((V)*(V - 1))))){
            break;
        }
        printf("\n No of edges must be between (V - 1) and (V * (V - 1)) .");
        printf("\n Enter the no. of edges : ");
    }
    while(1);

    graph = (struct edge *)malloc(sizeof(struct edge) * E);
    int* dis = (int *)malloc(sizeof(int) * V);
    for(int i = 0; i <= V; i++){
        dis[i] = INF;
    }

    for(int i = 0; i < E; i++){
        //bool isvalid = 1;
        printf("\n Edge %d source, destination and weight: ", i + 1);
        do{
            scanf("%d%d%d", &(graph[i].src), &(graph[i].dst), &(graph[i].weight));
            if(map[graph[i].src][graph[i].dst])
                printf("\n Edge from %d to %d already exists.", graph[i].src, graph[i].dst);
            else if(graph[i].src == graph[i].dst)
                printf("\n Self loops are not allowed.");
            else if(graph[i].src <= 0 && graph[i].dst <= 0 && graph[i].src > V && graph[i].dst > V)
                printf("\n Source and destination must be between 1 and %d", V);
            else
                break;
            printf("\n Enter %d source, destination and weight : ", i + 1);
        }while(1);
        map[graph[i].src][graph[i].dst] = 1;
    }
    printf("\n Enter the source vertex : ");
    scanf("%d", &source);
    bellmanford(V, E, source, graph, dis);
    free(graph);
    return 0;
}

