#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>
#include <string>
using std::priority_queue;
using std::ifstream;
using std::vector;
using std::string;

struct Nod{
    char caracter;
    Nod* st;
    Nod* dr;
    int fr;

    Nod(char _ch, int _fr): caracter{_ch}, fr{_fr}, st{nullptr}, dr{nullptr}{}
};

void read(string& str, vector<int> freq, ifstream& fin){
    fin>>str;
    freq = vector<int>(128, 0);
    for(const auto& ch : str){
        freq[ch]++;
    }
}

struct cmp{
    bool operator()(Nod* l, Nod* r) {
        if(l->fr == r->fr){
            return l->caracter > r->caracter;
        }
        return l->fr > r->fr;
    }
};

void huffman(vector<int>& freq){
    priority_queue<Nod*, vector<Nod*>, cmp> q;
    int n = 0;
    for(int i = 0; i<128; i++){  // Q = C
        if(freq[i]!=0){
            n++;
            q.push(new Nod(char(i), freq[i]));
        }
    }
    Nod* x;
    Nod* y;
    Nod* z;
    for(int i = 0; i < n-1; i++){
        x = q.top();
        q.pop();

        y = q.top();
        q.pop();

        z = new Nod(x->caracter, x->fr + y->fr);
        z->st = x;
        z->dr = y;

        q.push(z);
    }

}

int main(){
    ifstream fin("graf.txt");
    string str;
    vector<int> freq;
    read(str, freq, fin);
    huffman(freq);
}
