#include<bits/stdc++.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <fstream>

using namespace std;

void dijkstra (int n,  vector<vector<pair<int,int>>> Grafo, int writeN, std::string arName, int src){

    priority_queue<pair<int,int>> pq; // queue ordem do maior para o menor
    vector<int> dist(n, INT_MAX);

    src--;
    dist[src] = 0;
    pq.push({0,src});
    int V = n;

    while (pq.size() > 0) 
    {
        int v = pq.top().second;
        int w = -pq.top().first;
        pq.pop();
        if(w != dist[v]) continue;
        for(auto edge:Grafo[v])
        {
            int u = edge.first;
            int w = edge.second;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w; 
                pq.push({-dist[u], u});
            }
        }
    }

    int i = 0;

    std::vector<std::string> write(V);

    for(int d: dist){
        i++;
        if (d == INT_MAX)
        {
            d = -1;
        }
        write[i-1] = std::to_string(i) + ":" + std::to_string(d);
        cout << i << ":" << d << " ";
    }
    cout << endl;
    if(writeN!=0){
        std::ofstream arquivo(arName);
        if (arquivo.is_open()) {
            for (int i = 0; i < V-1; i++) {
                arquivo << write[i] << "\n";
            }
            arquivo.close();
            std::cout << "Array escrita no arquivo com sucesso.\n";
        } else {
            std::cout << "Não foi possível criar o arquivo.\n";
        }
    }
}

void help()
{

cout  << "-h : mostra o help" << endl;
cout  << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
cout  << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
cout  << "-i : vértice inicial (para o algoritmo de Prim)" << endl;



}

int main(int argc, char const *argv[]){

    int write = 0, file = 0, src = 0;
    std::string arName;
    std::string inputFile;
 
    for(int i = 1; i < argc; i++)
    {
        if(strcmp(argv[i], "-h")==0){
            help();
        } 
        else if(strcmp(argv[i], "-o")==0){
            write = 1;
            arName = argv[i+1];
        } else if(strcmp(argv[i], "-f")==0){
            inputFile = argv[i+1];
            file = 1;
        } else if(strcmp(argv[i], "-i")==0){
            src = std::stoi(argv[i+1]);
        }
    }

   if(file!=1)
    {
        int n, m, v, u, w;

    cin >> n >> m;

    vector<vector<pair<int,int>>> Grafo(n);

    for(int i = 0; i < m; i++)
    {
        cin >> v >> u >> w;
        v--, u--;
        Grafo[v].push_back({u, w});
        Grafo[u].push_back({v, w});
    }

    if(src==0){
        src = 1;
    }

    dijkstra(n, Grafo, write, arName, src);
    }
    else
    {
        
        std::ifstream arquivo(inputFile);
        int n, m, v, u, w;

        arquivo >> n >> m;

        vector<vector<pair<int,int>>> Grafo(n);

        for(int i = 0; i < m; i++)
        {
            arquivo >> v >> u >> w;
            v--, u--;
            Grafo[v].push_back({u, w});
            Grafo[u].push_back({v, w});
        }

        if (src==0){
            src = 1;
        }

        dijkstra(n, Grafo, write, arName, src);
    }
    
    return 0;
}