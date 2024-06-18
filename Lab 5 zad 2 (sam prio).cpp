//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 5.2
// Kolejka priorytetowa
//
//  WCY21IX4S0  Miksiewicz Pawel
//============================================================================

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

//DEKLARACJA PODSTAWOWEJ LISTY
struct Lista
{
  char data;
  int numerK;
  int czas;
  int priorytetZnaku;
  struct Lista *nastepny;
};

//OKRESLENIE PRIORYTETU NADAWANIU ZNAKOM
int Priorytet(char c)
{ 
	if (c == 'P')
	{
        return 2;
	}
	
    if (c == 'G')
    {
        return 1;
    }
    
    if (c == 'S')
    {
    	return 0;
    }
    else 
	{
	return -1;
	}
}

//DODAWANIE DO NOWEJ LISTY ODCZYTANYCH SYMBOLI
struct Lista* nowaLista(char symbol, int klient, int czas)
{
    struct Lista* temp = (struct Lista*)malloc(sizeof(struct Lista));
    temp->data = symbol;
    temp->numerK = klient;
    temp->czas = czas;
    temp->priorytetZnaku = Priorytet(symbol);
    temp->nastepny = NULL;
    return temp;
}

//FUNCKJA KTORA DODAJE DO STRUKTURY Z PRIORYTETEM
void PriorytetDodaj(struct Lista** poczatek, char znak, int klient, int czas)
{
    struct Lista* start = (*poczatek);
    struct Lista* temp = nowaLista(znak, klient, czas);
 
    if ((*poczatek)->priorytetZnaku > Priorytet(znak))
    {
        temp->nastepny = *poczatek;
        (*poczatek) = temp;
    }
    else
    {
        while (start->nastepny != NULL && start->nastepny->priorytetZnaku > Priorytet(znak))
        {
        	start = start->nastepny;
        }
        temp->nastepny = start->nastepny;
        start->nastepny = temp;
    }
}

//FUNCKJA DLA CELU ZAPISANIA LISTY DO PLIKU
void ZapiszDoPliku(struct Lista *poczatek, char nazwapliku[50])
{
    struct Lista *wsk = poczatek;
    ofstream  plik;
    plik.open(nazwapliku);
    
    if(plik.good() == true)
	{
        while (wsk != NULL)
		{
            plik << wsk->data << " " << wsk->numerK << " " << wsk->czas << endl;
            wsk = wsk->nastepny;
        }
    }
    plik.close();
}

//SPRAWDZANIE CZY LISTA JEST PUSTA
int CzyPusta(struct Lista** poczatek)
{
    return (*poczatek) == NULL;
}

//ODCZYTANIE Z WIERZCHOLKA WARTOSCI DATA (SYMBOL) Z LISTY
char TOP1(struct Lista** poczatek)
{
    return (*poczatek)->data;
}

//ODCZYTANIE Z WIERZCHOLKA WARTOSCI NUMERU KLIENTA Z LISTY
int TOP2(struct Lista** poczatek)
{
    return (*poczatek)->numerK;
}

//ODCZYTANIE Z WIERZCHOLKA WARTPSCI CZAS Z LISTY
int TOP3(struct Lista** poczatek)
{
    return (*poczatek)->czas;
}

//FUNKCJA NA USUWANIE "PIERWSZEGO ELEMENTU", CZYLI WIERZCHOLKA, ODPOWIEDNIK FUNKCJI W STOSIE STOS.POP()
void POP(struct Lista** poczatek)
{
    struct Lista *nc;
    if (poczatek == NULL || *poczatek == NULL)
    {
        return;
    }
    nc = *poczatek;
    *poczatek=(*poczatek)->nastepny;
    free(nc);
}

//FUNCKJA W CELU ODCZYTU DANYCH Z PLIKU, WYPISANIE ICH DO KONSOLI ORAZ WYKONANIE KOLEJKI PRIORYTETOWEJ
void OdczytZPliku(char nazwapliku[50], char nazwapliku2[50])
{	
    ifstream  plik;
    plik.open(nazwapliku);
    
    char a;
    int b,c;
    
    cout << "Dane z pliku wejsciowego" << endl;
    struct Lista* dana = nowaLista(a, b, c);
   	while(!plik.eof())
   	{
   	plik >> a >> b >> c;
   	PriorytetDodaj(&dana, a, b, c);
   	cerr << a << " " << b << " " << c << endl;
	}
    plik.close();
    POP(&dana);
    
    cout << endl << "Dane wyjsciowe po dodaniu z priorytetem" << endl;
    ZapiszDoPliku(dana,nazwapliku2);
  	while (!CzyPusta(&dana))
    {
        cout << TOP1(&dana) << " " << TOP2(&dana) << " " << TOP3(&dana) << endl;
        POP(&dana);
    }
    cout << endl << "Zapisano dane do pliku wyjsciowego o nazwie '" << nazwapliku2 << "'."<< endl;
}

//MAIN, WYLOWANIE FUNKCJI
int main()
{
	char nazwapliku[50];
	char nazwapliku2[50];
    
    cout << "Podaj nazwe pliku do ODCZYTU wraz z rozszerzeniem(!)." << endl;
    cin >> nazwapliku;
    cout << "Podaj nazwe pliku do ZAPISU wraz z rozszerzeniem(!)." << endl;
    cin >> nazwapliku2;
    OdczytZPliku(nazwapliku,nazwapliku2);
	
	return 0;
}
