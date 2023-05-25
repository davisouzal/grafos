#include<bits/stdc++.h>
#include <limits.h>
#include <vector>
#include <queue>
#include <stdio.h>
#include <string>
#include <fstream>
using namespace std;

typedef pair<int, int> dupla;

void prim(vector<vector<pair<int,int>>> Grafo, int V, int writeN, std::string arName, int src, int order)
{
    priority_queue <dupla, vector <dupla>, greater<dupla>> pq; //alternativa para inverter a ordem da queue


    vector<int> dist(V, INT_MAX);

    vector<int> parent(V, -1);

    vector<bool> check(V, false);
 
    pq.push(make_pair(0, src));
    dist[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(check[u] == true)
        {
            continue;
        }
       
        check[u] = true;
        for (auto edge:Grafo[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (check[v] == false && dist[v] > weight)
            {
                dist[v] = weight;
                pq.push(make_pair(dist[v], v));
                parent[v] = u;
            }
        }
    }
    int sum = 0;
    

    std::vector<std::string> write(V);

    for (int i = 1; i < V; ++i)
    {
        write[i-1] = "(" + std::to_string(parent[i] + 1) + "," + std::to_string(i+1) + ")";
        sum += dist[i];
        if(order!=0){
            cout << "(" << parent[i] + 1 << "," << i+1 << ")" << " " ;
        }
    }
    if(order!=0)
    {
        cout << endl;
    } 
    else
    {
    cout << sum << endl;
    }


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
cout  << "-s : mostra a solução (em ordem crescente)" << endl;
cout  << "-i : vértice inicial (para o algoritmo de Prim)" << endl;

}

int main(int argc, char const *argv[])
{
int write = 0, file = 0, src = 0, order = 0;
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
        } else if(strcmp(argv[i], "-s")==0){
            order = 1;
        } else if(strcmp(argv[i], "-i")==0){
            src = std::stoi(argv[i+1]);
        }
    }

    if(file!=1)
    {
        int n, m, v, u, w;
        cin >> n >> m;

        vector <vector<pair<int,int>>> Grafo(n);
       
        


        for(int i = 0; i < m; i++)
        {

            cin >> v >> u >> w;
            v--, u--;
            Grafo[v].push_back({u, w});
            Grafo[u].push_back({v, w});
        }
        prim(Grafo, n, write, arName, src, order);
    }
    else
    {
        std::ifstream arquivo(inputFile);
        int n, m, v, u, w;
        arquivo >> n >> m;

        vector <vector<pair<int,int>>> Grafo(n);
        //Aceita Apenas Vértices positivos >0

        


        for(int i = 0; i < m; i++)
        {

            arquivo >> v >> u >> w;
            v--, u--;
            Grafo[v].push_back({u, w});
            Grafo[u].push_back({v, w});
        }
        prim(Grafo, n, write, arName, src, order);
    }
    
    return 0;
}