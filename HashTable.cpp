#include <iostream>
#include <string>
using namespace std;
constexpr int tabsize = 100000; 

struct info {
    int am = 0;
    string key;
};

int h(string key) {
    int x=0;
    for (size_t i = 0; i < key.length(); i++) {
        srand(key[i]);
        x += rand()%key[i];
    }
    return (x*key[0]) % tabsize;
}

void addOA(info tab[],info n) {
    int index = h(n.key);
    for (int i = 0; i < tabsize; i++) {
        if (tab[index].am == 0) {
            tab[index] = n;
            return;
        } 
        else if (tab[index].key == n.key && tab[index].am!=-1) {
            tab[index].am++;
            return;
        }
        index++;
        if (index == tabsize) {
            index = 0;
        }
   }
}

string rewrote(string comand) {
    string word = "";
    for (size_t i = 1; i < comand.size(); i++) word += comand[i];
    return word;
}

void writedown(info tab[], string const &comand) {

    int index = h(comand);
    for (int i = 0; i < tabsize; i++) {

        if (tab[index].am == 0) {
            cout << "0" << endl;
            return;
        }
        else if (tab[index].key == comand && tab[index].am != -1) {
            cout << tab[index].am<<endl;
            return;
        }
        index++;
        if (index == tabsize) {
            index = 0;
        }
    }
}

void del(info tab[], string const &comand ) {
    int index = h(comand);
    for (int i = 0; i < tabsize; i++) {
        if (tab[index].am == 0) {
            return;
        }
        else if (tab[index].key == comand && tab[index].am != -1) {
            tab[index].am = -1; 
            return;
        }
        index++;
        if (index == tabsize) {
            index = 0;
        }
    }
}


int main()
{
    info *tab=new info [tabsize];
    string comand;
    do {
        cin >> comand;
        if (comand[0] == '?') {
            comand = rewrote(comand);
            writedown(tab,comand);
        }
        else if (comand[0] == '-') {
            comand = rewrote(comand);
            del(tab, comand);
        }
        else if (comand[0] == 'q' && comand.length()==1) {
            break;
        }
        else {
            info n;
            n.key = comand;
            n.am = 1;
            addOA(tab,n);
        }


    } while (true);


    


}
