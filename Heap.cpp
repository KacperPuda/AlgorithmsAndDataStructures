#include <iostream>
#include <string>
using namespace std;


struct info{
	int dzien;
	int miesiac;
	int rok;
	string imie;
};

bool porownanie(info A, info B, int poCzym) {
	if (poCzym == 0) {
		if (A.imie < B.imie) return true;
		else return false;
	}
	else {
		if (A.rok < B.rok) return true;
		if (A.rok > B.rok) return false;
		if (A.miesiac < B.miesiac) return true;
		if (A.miesiac > B.miesiac) return false;
		if (A.dzien < B.dzien) return true;
		if (A.dzien > B.dzien) return false;
	}
	return false;
}

void heapify(info* &tab, int i, int size,int poCzym) {
	int R = 2 * i + 1, L = 2 * i, maks = i;
	if (L <= size && porownanie(tab[L - 1], tab[maks - 1],poCzym)) maks = L;
	if (R <= size && porownanie(tab[R - 1], tab[maks - 1], poCzym)) maks = R;
	if (maks != i) {
		swap(tab[i - 1], tab[maks - 1]);
		heapify(tab, maks, size, poCzym);
	}
}

info wpisz() {
	info informacje;
	int dd, mm, yy;
	string im;
	cin >> dd;
	cin.ignore();
	cin >> mm;
	cin.ignore();
	cin >> yy;
	informacje.dzien = dd;
	informacje.miesiac = mm;
	informacje.rok = yy;
	cin >> im;
	informacje.imie = im;
	return informacje;
}

void wypisz(info *tab, int size) {
	for (int i = 0; i < size; i++) {
		if (tab[i].dzien / 10 == 0)cout << "0";
		cout << tab[i].dzien<< "-";
		if (tab[i].miesiac / 10 == 0)cout << "0";
		cout << tab[i].miesiac << "-";
		if (tab[i].rok / 1000 == 0)cout << "0";
		if (tab[i].rok / 100 == 0)cout << "0";
		if (tab[i].rok / 10 == 0)cout << "0";
		cout<< tab[i].rok << " " << tab[i].imie;
		cout << endl;
	}
}

void vector(info* &tab,int size,int start) {
	info* ntab = new info[size];
	for (int i = 0; i < start; i++) {
		ntab[i] = tab[i];
	}
	delete[] tab;
	tab = ntab;
}

void usun(info* &tab, int& size,int jak) {
	wypisz(tab, 1);
	tab[0] = tab[size - 1];
	size--;
	heapify(tab, 1, size, jak);
	vector(tab, size,size);
}

void dodaj(info *tab,int jak,int z) {
	while (z > 1 && porownanie(tab[z - 1], tab[z / 2 - 1],jak)) {
		swap(tab[z - 1], tab[z / 2 - 1]);
		z = z / 2;
	}
}

int main()
{
	char zad;
	int size=0,ile,jak=0;
	info *tab=new info[0];
	while (true) {
		cin >> zad;
		if (zad == '+') {
			cin >> ile;
			vector(tab, size+ile,size);
			for (int i = size; i < size+ile; i++) {
				tab[i] = wpisz();
				dodaj(tab,jak,i+1);
			}
			size += ile;
		}
		if (zad == 'p') {
			if(size!=0)wypisz(tab, size);
		}
		if (zad == '-') {
			cin >> ile;
			for (int i = 0; i < ile; i++) {
				usun(tab, size,jak);
			}
		}
		if (zad == 'r') {
			if (jak == 0) jak = 1;
			else jak = 0;
			for (int i = size; i >= 1; i--) heapify(tab, i, size,jak);
		}
		if (zad == 'q') {
			break;
		}
	}
}
