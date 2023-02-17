#include <iostream>
using namespace std;

//funkcja wykresla kolejne wystapienia liczb pierwszych
//liczby pierwsze maja wartosc true a pozostale false
void stworzTabliceLiczbPierwszych(bool tabPierwszych[])
{
	tabPierwszych[0] = false;
	tabPierwszych[1] = false;
	for (int i = 2; i < 256; i++) tabPierwszych[i] = true;
	for (int i = 2; i*i < 256; i++)
	{
		if (tabPierwszych[i]) for (int j = i * i; j < 256; j += i) tabPierwszych[j] = false;
	}
}

int* stworzTabliceRozkladu(int liczba, int k)
{
	int ileMiejsc = 0;
	ileMiejsc = (liczba - k) / 2;
	return new int[ileMiejsc];
}

void zerowanieTempa(int tab[],int dl)
{
	for (int i = 0; i < dl; i++) tab[i] = 1;
}

int PodajNastepnaLiczbePierwsza(bool pierwsze[], int liczba)
{
	int i = liczba + 1;
	while (!pierwsze[i])i++;
	return i;
}

int rozloz(int liczba, int tab[],int poczatek,int koniec)
{
	int g = liczba / 2;
	for (int i = poczatek; i < koniec; i++) tab[i] = 0;
	for (int i = poczatek; i < poczatek + g; i++) tab[i] = 2;
	if (liczba % 2 != 0) tab[poczatek] = 3;
	if (liczba % 2 != 0) return poczatek+1 ;
	else return poczatek;
}

void Sotruj(int tab[], int dl)
{
	for (int i = 0;i < dl; i++)
	{
		for (int j = dl - 1; j > i; j--)
		{
			if (tab[i] < tab[j])
			{
				int temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
		}
	}
}

void PrzepiszTablice(int temp[],int tab[],int dl)
{
	for (int i = 0; i < dl; i++) if (temp[i] >=0 && temp[i]!=1) tab[i] = temp[i];
	Sotruj(tab, dl);
	zerowanieTempa(temp,dl);
}

int UstawNowyPoczatek(int &liczbaPoczatkowa,int tab[], int dlTablicy, bool pierwsze[],int k)
{
	int i=0;
	while(true)
	{
		liczbaPoczatkowa = PodajNastepnaLiczbePierwsza(pierwsze, liczbaPoczatkowa);
		if (liczbaPoczatkowa > k) return -1;
		if (liczbaPoczatkowa > tab[0]) return 0;
		for (i = 0; i < dlTablicy; i++) if (tab[i] == liczbaPoczatkowa) return i;
	}
	return i;
}

void SprawdzanieWszystkichKombinacji(bool tabPierwszych[], int tabRozkladu[], int tempTab[], int dlTablicy, int k)
{
	int poczatekFora = 0, suma = 0, doRozkladu = 0, liczbaPoczatkowa = 2;
	if (tabRozkladu[0] == 3)poczatekFora = 1;
	if (dlTablicy == 1) return;
	for (int i = poczatekFora; i <= dlTablicy; i++)
	{
		suma += tabRozkladu[i];
		int nastepnaPierwsza = PodajNastepnaLiczbePierwsza(tabPierwszych, tabRozkladu[poczatekFora]);
		if (nastepnaPierwsza > k)return;
		if ((suma>=nastepnaPierwsza)&&(suma-nastepnaPierwsza!=1)&&(tabRozkladu[i] != 0))
		{
			tempTab[poczatekFora] = nastepnaPierwsza;
			doRozkladu = suma - nastepnaPierwsza;
			for (int ii = i+1; ii < dlTablicy; ii++) doRozkladu+=tabRozkladu[ii];
			if (doRozkladu < 0) return;
			poczatekFora=rozloz(doRozkladu,tempTab,poczatekFora+1,dlTablicy);
			PrzepiszTablice(tempTab, tabRozkladu, dlTablicy);
			cout << k;
			for (int ii = 0; ii < dlTablicy; ii++) if(tabRozkladu[ii] != 0)cout << "+" << tabRozkladu[ii];
			cout << endl;
			liczbaPoczatkowa = 2;
			suma = 0;
			i = poczatekFora-1;
		}
		if (i>=dlTablicy-1|| tabRozkladu[i]==0)
		{
			i = UstawNowyPoczatek(liczbaPoczatkowa,tabRozkladu,dlTablicy,tabPierwszych,k);
			if (i == -1) break;
			suma = 0;
			poczatekFora = i;
			i--;
		}
	}

}

int main()
{
	int ileDanych = 0;
	cin >> ileDanych;
	bool tabPierwszych[256];
	stworzTabliceLiczbPierwszych(tabPierwszych);
	for(int j=0;j<ileDanych;j++)
	{
		int liczba = 0, k = 0, dlTablicy = 0;
		cin >> liczba;
		if (liczba > 255) continue;
		cin >> k;
		if (!tabPierwszych[k] || k > liczba || ((k==2)&&(liczba%2==1))|| liczba-k==1) continue;
		if (liczba == k)
		{
			cout << liczba << endl;
			continue;
		}
		dlTablicy = (liczba - k) / 2;
		int* tabRozkladu = stworzTabliceRozkladu(liczba, k);
		int* tempTab = stworzTabliceRozkladu(liczba, k);
		zerowanieTempa(tempTab, dlTablicy);
		rozloz(liczba - k, tabRozkladu, 0, dlTablicy - 1);
		cout << k;
		for (int i = 0; i < dlTablicy; i++) cout << "+" << tabRozkladu[i];
		cout << endl;
		SprawdzanieWszystkichKombinacji(tabPierwszych,tabRozkladu,tempTab,dlTablicy,k);
		delete[] tabRozkladu;
		delete[] tempTab;
	}
	return 0;
}
