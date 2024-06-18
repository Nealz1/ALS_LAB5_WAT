//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 5.2
// Kolejka priorytetowa
//
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;

//DEKLARACJA PODSTAWOWEJ LISTY
struct Lista
{
	int	literaPrio;
	int numerK;
	int czas;
};

//DEKLARACJA PODSTAWOWEJ LISTY
struct Dana
{
	struct Lista Lista;
	struct Dana *nastepny;
};

//FUNCKJA KTORA DODAJE DO STRUKTURY WG. PRIORYTETU
void KolejkaPriorytetowa(struct Dana **poczatek, int numerK, int czas, int literaPriorytet)
{
	struct Dana *nowaDana = (struct Dana*)malloc(sizeof(struct Dana));
	struct Dana *obecna = *poczatek;
	
	nowaDana->Lista.numerK = numerK;
	nowaDana->Lista.czas = czas;
	nowaDana->Lista.literaPrio = literaPriorytet;

	if(obecna && obecna->Lista.literaPrio <= nowaDana->Lista.literaPrio)
    {
        if(obecna->Lista.literaPrio == nowaDana->Lista.literaPrio && obecna->Lista.czas > nowaDana->Lista.czas)
		{
            *poczatek = nowaDana;
            nowaDana->nastepny = obecna;
        }
        else
		{
            while(obecna->nastepny && obecna->nastepny->Lista.literaPrio < nowaDana->Lista.literaPrio)
            {
                obecna = obecna->nastepny;
            }
            //DRUGI WARUNEK SORTOWANIA, CZYLI WG KRYTERIUM CZASU
            while(obecna->nastepny && obecna->nastepny->Lista.literaPrio <= nowaDana->Lista.literaPrio && obecna->nastepny->Lista.czas < nowaDana->Lista.czas)
			{
                obecna = obecna->nastepny;
            }
            struct Dana *nastepny = obecna->nastepny;
            obecna->nastepny = nowaDana;
            nowaDana->nastepny = nastepny;
        }
    }
    else
	{
        *poczatek = nowaDana;
        nowaDana->nastepny = obecna;
    }
}


//STRUKTURA DO USUWANIA Z KOLEJKI
struct Lista UsunZKolejki(struct Dana **poczatek)
{
	struct Lista usun;
	
	usun.numerK = 0;
	usun.literaPrio = 0;
	usun.czas = 0;
	
	if(!*poczatek)
	{
		return usun;
	}
	
	usun = (*poczatek)->Lista;
	struct Dana *zmienna = (*poczatek)->nastepny;
	free(*poczatek);
	*poczatek = zmienna;
	
	return usun;
};

//STRUKTURA NA DANY 1 PIERWSZY ELEMENT KOLEJKI
struct Lista Element(struct Dana **poczatek)
{
	struct Lista powrot;
	
	powrot.numerK = 0;
	powrot.literaPrio = 0;
	powrot.czas = 0;
	
	if(*poczatek)
	{
		powrot = (*poczatek)->Lista;
		return powrot;
	}
	else
	{
		return powrot;
	}
};

//FUNKCJA SPRAWDZAJACA CZY STRUKTURA JEST PUSTA, ODPOWIEDNIK FUNKCJI W STOSIE STOS.EMPTY()
int CzyPusta(struct Dana **Lista)
{
	if (*Lista) 
	{
		return 0;
	}
	else 
	{
		return 1;
	}
}

//FUNKCJA NA ODCZYTANIE PLIKU WEJSCIOWE I WYKONANIE KOLEJKI PRIORYTETOWEJ ORAZ UTWORZONIE PLIKU Z DANYMI WYJSCIOWYMI
void Odczyt(char nazwapliku[50], char nazwapliku2[50])
{
	struct Dana *start = NULL;
    struct Dana **kolejka = &start;
    ifstream  plik;
    plik.open(nazwapliku);
    
    char a;
    int b,c;
    
    int symbolP = 1;
	int symbolG = 2;
	int symbolS = 3;
	
    cout << endl << "Dane z pliku wejsciowego: " << endl;
    cout << "Symbol | Numer Klienta | Czas rozmowy" << endl;
   	while(!plik.eof())
   	{
   		plik >> a >> b >> c;
   		cout << a << " " << b << " " << c << endl;
   	
   		int symbol = a;
   		if(symbol == 'P')
		{
   	    	symbol = symbolP;
   		}
   		else if(symbol == 'G')
		{
        	symbol = symbolG;
    	}
    	else if(symbol == 'S')
		{
        	symbol = symbolS;
    	}
    	else
		{
        	symbol = 0;
    	}
		KolejkaPriorytetowa(kolejka, b, c, symbol);
	}
    plik.close();
    
    ofstream plik2;
    plik2.open(nazwapliku2);
    
    cout << endl << "Dane wyjsciowe:" << endl;
    plik2 << "Symbol | Numer Klienta | Czas rozmowy" << endl;
    cout << "Symbol | Numer Klienta | Czas rozmowy" << endl;
    
    while(!CzyPusta(kolejka))
    {
    	struct Lista tymczasowa = UsunZKolejki(kolejka);
    	if(tymczasowa.literaPrio == symbolP)
		{
            tymczasowa.literaPrio = 'P';
        }
        else if(tymczasowa.literaPrio == symbolG)
		{
            tymczasowa.literaPrio = 'G';
        }
        else if(tymczasowa.literaPrio == symbolS)
		{
            tymczasowa.literaPrio = 'S';
        }
        else
		{
            tymczasowa.literaPrio = 'N';
        }
        
        printf("%c %d %d \n", tymczasowa.literaPrio, tymczasowa.numerK, tymczasowa.czas);
        plik2 << char(tymczasowa.literaPrio) << " " << tymczasowa.numerK << " " << tymczasowa.czas << endl;
	}
	plik2.close();
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
    
    Odczyt(nazwapliku, nazwapliku2);
	cout << endl << "Zapisano dane do pliku o nazwie '" << nazwapliku2 << "'." << endl;
	return 0;
}
