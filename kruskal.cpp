#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using std::vector;
using std::sort;

struct Muchie{
    int u, v, w;

    Muchie(int _u, int _v, int _w){
        u = _u;
        v = _v;
        w = _w;
    }
};

void read(int &n, int &m, vector<Muchie>& muchii, std::ifstream& fin){
    fin>>n>>m;
    int x, y, w;
    while(fin>>x>>y>>w){
        muchii.emplace_back(x,y, w);
    }
}

int radacina(const int& nod, const vector<int>& parent){
    if(parent[nod] == -1){
        return nod;
    }
    return radacina(parent[nod], parent);
}

vector<Muchie> Kruskal(int&n, int& cost, vector<Muchie>& muchii){
    vector<Muchie> A; //arborele de acoperire
    vector<int> parent(n, -1); //makeset

    sort(muchii.begin(), muchii.end(), [](const Muchie& x, const Muchie& y){
        return x.w < y.w;
    }); //sort

    for(const auto& muchie : muchii){
        int rad1 = radacina(muchie.u, parent);
        int rad2 = radacina(muchie.v, parent);
        if(rad1 != rad2){     //findset
            A.emplace_back(muchie); //adauga in arbore
            cost+= muchie.w;
            parent[rad1] = rad2; //union
        }
    }

    return A;
}

int main() {
    std::ifstream fin("graf.txt");
    int n, m;
    vector<Muchie> muchii;
    read(n, m, muchii, fin);
    int cost = 0;
    vector<Muchie> arboreDeAcoperire = Kruskal(n, cost, muchii);
    std::cout<<cost<<' '<<arboreDeAcoperire.size();

    for(const auto& muchie : arboreDeAcoperire){
        std::cout<<muchie.u<<' '<<muchie.v<<'\n';
    }

}
