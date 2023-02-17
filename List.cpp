#include <iostream>
using namespace std;

struct element
{
    long long int number=NULL;
    element* prev = nullptr;
    element* next = nullptr;
};

struct lista
{
    element* iterator[10]={nullptr,nullptr, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr, nullptr, nullptr};
    element* first = nullptr;
    element* last = nullptr;
    long long int size = 0, iPos[10];
};

void AddAfter(lista &list, long long int a, element *&current) {
    element *n=new element;
    n->number = a;
    if (list.first == nullptr) {
        list.first = n;
        list.last = n;
    }
    else { 
            n->next = current->next;
            n->prev = current;
            if (current->next)current->next->prev = n;
            if (current) current->next = n;
            if (list.last == list.first)list.last = n;
            if (current == list.last)list.last = n;
    }
    list.size++;
}

void AddBefore(lista &list, long long int a, element*& current) {
    element* n = new element;
    n->number = a;
    if (list.first == nullptr) {
        list.first = n;
        list.last = n;
    }
    else { 
        n->next = current;
        n->prev = current->prev;
        if (current->prev)current->prev->next = n;
        if (current) current->prev = n;
        if (!n->prev) list.first = n;
    }
    list.size++;
}

void Wyswietl(lista& list) {
    element* tmp = list.first;
    while (tmp) {
        cout << tmp->number << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

void Del(lista& list, element* &cur) {

    if (list.last == list.first) {
        delete[] cur;
        list.last = nullptr;
        list.first = nullptr;
    }
    else {
        element* tmp = cur;
        if (cur->prev && cur->next) {
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            cur = cur->next;
        }
        else {
            if (cur->next) {
                cur = cur->next;
                cur->prev = nullptr;
                list.first = cur;
            }
            else {
                if (cur->prev) {
                    cur = cur->prev;
                    cur->next = nullptr;
                    list.last = cur;
                }
            }
        }
        for (int i = 0; i < 10; i++) {
            if (list.iterator[i] == tmp) list.iterator[i] = cur;
        }
        delete[] tmp;
    }
}

void Comands(char task[3],lista &list) {
    long long int y;
    if (strcmp(task, "A.") == 0) {
        cin >> task;
        cin >> y;
        if (strcmp(task, "BEG") == 0) {
            AddAfter(list,y, list.first);
        }
        else {
            if (strcmp(task, "END") == 0) {
                AddAfter(list, y, list.last);
            }
            else {
                int g;
                g = task[0] - '0';
                AddAfter(list, y, list.iterator[g]);
            }
        }
    }
    if (strcmp(task, ".A") == 0) {
        cin >> task;
        cin >> y;
        if (strcmp(task, "BEG") == 0) {
            AddBefore(list, y, list.first);
        }
        else {
            if (strcmp(task, "END") == 0) {
                AddBefore(list, y, list.last);
            }
            else {
                int g;
                g = task[0] - '0';
                AddBefore(list, y, list.iterator[g]);
            }
        }
    }
    if (strcmp(task, "i") == 0) {     
        cin >> y;
        cin >> task;
        delete[] list.iterator[y];
        if (strcmp(task, "BEG") == 0) {
            list.iterator[y] = list.first;
            list.iPos[y] = 0;
        }
        else {
            if (strcmp(task, "END") == 0) {
                list.iterator[y] = list.last;
                list.iPos[y] = list.size - 1;
            }
            else {
                int g;
                g = task[0] - '0';
                list.iterator[y] = list.iterator[g];
            }
        }
    }
    if (strcmp(task, "+") == 0) {
        cin >> y;
        if (list.iterator[y]->next) {
            list.iterator[y] = list.iterator[y]->next;
            list.iPos[y]++;
        }
    }
    if (strcmp(task, "-") == 0) {
        cin >> y;
        if (list.iterator[y]->prev) {
            list.iterator[y] = list.iterator[y]->prev;
            list.iPos[y]--;
        }
    }
    if (strcmp(task, "P") == 0) {
        cin >> task;
        if (strcmp(task, "ALL") == 0) {
            Wyswietl(list);
        }
        else {
            y = task[0] - '0';
            if(list.iterator[y])cout << list.iterator[y]->number << endl;
        }
    }
    if (strcmp(task, "R") == 0) {
        cin >> task;
        if (strcmp(task, "BEG") == 0) {
            Del(list,list.first);
        }
        else {
            if (strcmp(task, "END") == 0) {
                Del(list, list.last);
            }
            else {
                y = task[0] - '0';
                Del(list, list.iterator[y]);
                if (list.first == nullptr) {
                 list.iterator[y] = nullptr;
                }
            }
        }
    }
}

int main(){
    char task[3];
    lista list;
    while (cin >> task) Comands(task, list);
    return 0;
}
