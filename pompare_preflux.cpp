#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <queue>

using std::vector;
using std::queue;

struct Nod{
    int nod;
    int e, h;
    Nod(){
        e = 0;
        h = 0;
        nod = -1;
    }

    explicit Nod(int _n){
        nod = _n;
        e = 0;
        h = 0;
    }
};

struct Muchie{
    Nod u, v;
    int w, f;
    Muchie(){
        w=f=0;
    }

    Muchie(Nod _u, Nod _v, int _w){
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
        Nod x(u);
        Nod y(v);
        Muchie mu(x,y,w);
        G[u][v] = mu;
    }
}

void pompare(vector<vector<Muchie>>& Gf, Nod u, Nod v){
    int deltaf = std::min(u.e, Gf[u.nod][v.nod].w - Gf[u.nod][v.nod].f);
    Gf[u.nod][v.nod].f += deltaf;
    Gf[v.nod][u.nod].f -= deltaf;
    u.e -= deltaf;
    v.e += deltaf;

}

void intaltare(vector<vector<Muchie>>& Gf, Nod u){
    int min = INT_MAX;
    for(int i = 0; i < Gf.size(); i++){
        if(Gf[u.nod][i].v.h < min){
            min = Gf[u.nod][i].v.h;
        }
    }
    u.h = 1 + min;
}

void initializare_preflux(vector<vector<Muchie>>& Gf, Nod s, Nod t){
    //toate initializate din constructor:
    //v.h = 0
    //v.e = 0
    //(u,v).f = 0
    s.h = Gf.size();
    for(int i = 0; i< Gf.size(); i++){
        Gf[s.nod][i].f = Gf[s.nod][i].w; //flux = c(s,v)
        Gf[s.nod][i].v.e = Gf[s.nod][i].w; //v.e = c(s,v)
        s.e -= Gf[s.nod][i].w; //s.e -= c(s,v)
    }
}

int pompare_preflux(vector<vector<Muchie>>& Gf, int s, int t){
    initializare_preflux(Gf)
    while(true){

        continue;
        break;
    }
}

int main(){
    std::ifstream fin("graf.txt");
    vector<vector<Muchie>> G;
    int n,m;
    read(n, m, G, fin);


}

/*
Input:
5 6
0 1 17
0 4 19
1 2 15
2 3 19
2 4 4
3 4 1
Output:
24
 */
