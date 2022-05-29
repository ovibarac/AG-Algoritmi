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

bool bfs(vector<vector<Muchie>>& G, int s, int t, vector<Muchie>& p){
    vector<bool> viz(G.size(), false);

    queue<int> q;
    q.push(s);
    viz[s] = true;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(int i = 0; i < G[u].size(); i++){
            if(!viz[i] && G[u][i].w > 0){
                p.emplace_back(G[u][i]);
                if(i == t){
                    return true;
                }
                q.push(i);
                viz[i] = true;
            }
        }
    }
    return false;
}

int ford_fulkerson(vector<vector<Muchie>>& G, int s, int t){
    //(u,v).f = 0 - din constructor

    vector<vector<Muchie>> Gf = G;  //creare graf rezidual

    int f = 0;
    vector<Muchie> p;
    while(bfs(Gf, s, t, p)){ //while bfs gaseste drum p
        int cf = INT_MAX;
        for(auto& m : p){  //cf = min p
            if(m.w < cf){
                cf = m.w;
            }
        }

        for(auto& m : p){ //for fiecare
            if(Gf[m.u][m.v].w >0)
                Gf[m.u][m.v].w -= cf;
            else
                Gf[m.v][m.u].w += cf;
        }
        f+=cf;
    }

    return f;
}

int main(){
    std::ifstream fin("graf.txt");
    vector<vector<Muchie>> G;
    int n,m;
    read(n, m, G, fin);
    std::cout<<ford_fulkerson(G, 0, n-1);

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
