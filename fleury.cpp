/*
    Se dă un graf neorientat. Să se găsească un ciclu eulerian în graful dat. Implementarea trebuie să fie eficientă din punctul 
    de vedere al memoriei folosite și al timpului de execuție.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <string>

using std::vector;
using std::stack;
using std::pair;
using std::cout;
using std::ifstream;
using std::ofstream;

vector<vector<int>> G; // G[x] -> numerele de ordine ale muchiilor incidente nodului x
vector<pair<int, int>> edges; // lista de muchii
vector<bool> used; // used[i] -> muchia cu indicele i a fost folosita
vector<int> cycle; // ciclul eulerian
stack<int> st;

void read(ifstream& fin) {
    int n; // numarul de noduri
    int m; // numarul de muchii
    fin >> n >> m;

    used.resize(m, false);
    G.resize(n, vector<int>());
    edges.reserve(m);

    int u, v;
    while (fin >> u >> v) {
        edges.emplace_back(u, v);
        int index = edges.size() - 1;
        G[u].push_back(index);
        G[v].push_back(index);
    }
}

void euler(int start) {
    st.push(start);

    while (!st.empty()) { // simulez recursivitatea cu o stiva
        int node = st.top();

        if (!G[node].empty()) { // daca node mai are vecini
            int edge_index = G[node].back(); // extrag o muchie incidenta lui node
            G[node].pop_back(); // elimin muchia 

            if (!used[edge_index]) { // daca nu am sters muchia (graful e neorientat deci o pot gasi iar in lista de incidenta a altui nod)
                used[edge_index] = true;
                int neighbour = edges[edge_index].second; // extrag vecinul lui node

                // prima data cand descopar un vecin il iau din muchie node->neighbour
                // dar cum graful este neorientat si nodurile nu se parcurg o singura data
                // se poate sa ajung in situatia in care din neighbour incerc sa merg iar in neighbour 
                // (pt ca din muchie extrag mereu extremitatea din dreapta)
                if (node == neighbour) {
                    neighbour = edges[edge_index].first;
                }

                st.push(neighbour); // apel recursiv
            }
        }
        else { // intoarcere din recursivitate
            cycle.push_back(node);
            st.pop();
        }
    }
    cycle.pop_back();
}

void show(ofstream& fout) {
    for (int node : cycle)
        fout << node << ' ';
}

int main(int argc, char* argv[])
{
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    read(fin);
    euler(0);
    show(fout);

    fin.close();
    fout.close();
    return 0;
}
