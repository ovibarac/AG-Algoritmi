#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
using std::priority_queue;
using std::ifstream;
using std::vector;


void read(int& n, int& rad, vector<int>& parent, vector<int>& grad, ifstream& fin){
    fin>>n;
    parent.resize(n, 0);
    grad.resize(n, 0);
    for(int i = 0; i<n; i++){
        int x;
        fin>>x;
        parent[i]=x;
        if(x!=-1){
            grad[i]++;
            grad[x]++;
        }else{
            rad = i;
        }
    }
}

vector<int> codare_prufer(int& n, int& rad, vector<int>& parent, vector<int>& grad){
    vector<int> K;
    priority_queue<int, vector<int>, std::greater<int>> T;
    for(int i = 0; i<n; i++){
        if(i != rad && grad[i] == 1){
            T.push(i);
        }
    }

    while(!T.empty()){ //T contine alte vf decat radacina
        int frunza = T.top();
        T.pop();  //T = T \ {frunza}
        K.push_back(parent[frunza]); //K<-predecesor(frunza)
        grad[parent[frunza]]--;
        if(grad[parent[frunza]] == 1 && parent[frunza] != rad){
            T.push(parent[frunza]);
        }
    }
    return K;
}

vector<int> decodare_prufer(int n, int rad, vector<int>& code){
    vector<int> parent(n+1, 0);
    std::queue<int> code_q;
    vector<int> frecv(n+1, 0);
    for(auto& c : code){
        code_q.push(c);
        frecv[c]++;
    }

    for(int i = 0; i<n; i++){ //de n ori
        int x = code_q.front(); //x- primul din cod
        int y = 0;
        for(int j = 0; j<frecv.size(); j++){ //y-cel mai mic care nu apare in cod
            if(frecv[j] == 0){
                y = j;
                break;
            }
        }
        code_q.pop(); //sterge x
        frecv[x]--;

        code_q.push(y); //adauga y

        parent[y] = x; //leaga x,y
        frecv[y]++;
    }
    parent[rad] = -1;
    return parent;
}


int main(){
    ifstream fin("graf.txt");
    vector<int> parent;
    vector<int> grad;
    int n, rad;
    read(n, rad, parent, grad, fin);
    vector<int> code = codare_prufer(n, rad, parent, grad);
    for(int i = 0; i<code.size(); i++){
        std::cout<<code[i] << ' ';
    }
    std::cout<<'\n';

    vector<int> decode = decodare_prufer(n-1,rad, code);
    for(int i = 0; i<decode.size(); i++){
        std::cout<<decode[i] << ' ';
    }
}
