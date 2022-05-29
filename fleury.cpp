#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using std::vector;
using std::queue;

struct Muchie{
    int u, v, w;
    int f;
    Muchie(){
        u=v=w=f=0;
    }

    Muchie(int _u, int _v, int _w){
        u = _u;
        v = _v;
        w = _w;
        f = 0;
    }
};

void read(int &n, int & m, vector<vector<Muchie>>& G, std::ifstream& fin){
    fin>>n>>m;
    G.resize(n);
    for(int i = 0; i<n; i++){
        G[i].resize(n);
    }
    int u, v, w;
    while(fin>>u>>v>>w){
        Muchie mu(u,v,w);
        G[u][v] = mu;
    }
}

int main(){
    std::ifstream fin("graf.txt");
}