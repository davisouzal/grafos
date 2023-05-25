    #include<bits/stdc++.h>
    #include <limits.h>
    #include <vector>
    #include <queue>
    #include <stdio.h>
    #include <string>
    #include <fstream>
    using namespace std;

    int var1, var2, var3, var4;
    std::string var5;

    void setN(int value){
        var1 = value;
    }
    int getN(){
        return var1;
    }
    void setWriteN(int value){
        var2 = value;
    }
    int getWriteN(){
        return var2;
    }
    void setSrc(int value){
        var3 = value;
    }
    int getSrc(){
        return var3;
    }
    void setOrder(int value){
        var4 = value;
    }
    int getOrder(){
        return var4;
    }
    void setArName(std::string value){
        var5 = value;
    }
    std::string getArName(){
        return var5;
    }

    
    typedef pair<int, int> iPair;
    
    struct Graph
    {
        int V, E;
        vector< pair<int, iPair> > edges;
    
        Graph(int V, int E)
        {
            this->V = V;
            this->E = E;
        }
    
        void addEdge(int u, int v, int w)
        {
            edges.push_back({w, {u, v}});
        }
    
        int kruskalMST();
    };
    
    struct DisjointSets
    {
        int *parent, *rnk;
        int n;
    
        DisjointSets(int n)
        {
            this->n = n;
            parent = new int[n+1];
            rnk = new int[n+1];
    
            for (int i = 0; i <= n; i++)
            {
                rnk[i] = 0;
    
                parent[i] = i;
            }
        }
    
        int find(int u)
        {
            if (u != parent[u])
                parent[u] = find(parent[u]);
            return parent[u];
        }
    
        void merge(int x, int y)
        {
            x = find(x), y = find(y);
    
            if (rnk[x] > rnk[y])
                parent[y] = x;
            else 
                parent[x] = y;
    
            if (rnk[x] == rnk[y])
                rnk[y]++;
        }
    };
    
    
    int Graph::kruskalMST()
    {
        int mst_wt = 0; 
    
        sort(edges.begin(), edges.end());
    
        DisjointSets ds(V);
    
        vector< pair<int, iPair> >::iterator it;

        int size = getN();
        int writeN = getWriteN();
        std::string arName = getArName();
        int order = getOrder();


        int cnt = 0;

        
        int initialVertex = getSrc();
        
        std::vector<std::string> write(size);

        for (it=edges.begin(); it!=edges.end(); it++)
        {
            int u = (initialVertex == -1) ? it->second.first : initialVertex;
            int v = it->second.second;
    
            int set_u = ds.find(u);
            int set_v = ds.find(v);
    
            if (set_u != set_v)
            {
                write[cnt] = "("+ std::to_string(u)+","+ std::to_string(v)+ ")";
                cnt++;
                if (order!=0)
                {
                    cout << "(" << u << "," << v << ")" <<" ";
                }

                mst_wt += it->first;
    
                ds.merge(set_u, set_v);
            }
        }

        if(writeN!=0)
        {
            std::ofstream arquivo(arName);
            if (arquivo.is_open()) {
                for (int i = 0; i < cnt; i++) {
                    arquivo << write[i] << "\n";
                }
                arquivo.close();
                std::cout << "Array escrita no arquivo com sucesso.\n";
            } else {
                std::cout << "Não foi possível criar o arquivo.\n";
            }
        }

    
        return mst_wt;
    }

    void help()
    {
        cout  << "-h : mostra o help" << endl;
    cout  << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’" << endl;
    cout  << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada" << endl;
    cout  << "-s : mostra a solução (em ordem crescente)" << endl;


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
        }

        if(file!=1){
            int n, m, v, u, w;
            cin >> n >> m;
            Graph g(n, m);

            for(int i = 0; i < m; i++){
                cin >> v >> u >> w;
                g.addEdge(v, u, w);
            }
        
            setN(n);
            setWriteN(write);
            setArName(arName);
            if (src==0){
                setSrc(-1);
            }else{
                setSrc(src);
            }
            setOrder(order);
            int mst_wt = g.kruskalMST();
            
        
            cout << mst_wt << endl;
        }
        else{
            std::ifstream arquivo(inputFile);
            int n, m, v, u, w;
            arquivo >> n >> m;
            Graph g(n, m);

            for(int i = 0; i < m; i++){
                arquivo >> v >> u >> w;
                g.addEdge(v, u, w);
            }
        
            setN(n);
            setWriteN(write);
            setArName(arName);
            if (src==0){
                setSrc(-1);
            }else{
                setSrc(src);
            }
            setOrder(order);
            int mst_wt = g.kruskalMST();
            
        
            if (order == 0){
                cout << mst_wt << endl;
            }
        }
    
        return 0;
    }