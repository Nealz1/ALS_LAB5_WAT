//============================================================================
//                  Algorytmy i Struktury Danych
// Zadanie 5.1
// Wieza Hanoi
//
//============================================================================

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

//PODSTAWOWA DEKLARACJA STRUKTURY DO KRAZKOW WIEZ
struct Lista
{
    int krazek;
    struct Lista *wierzcholek;
};

//PODSTAWOWA DEKLARACJA STRUKTURY DO NAZW WIEZ
struct Wieza
{
  char nazwa;
  Lista *nastepny;
};

//CALA STRUKTURA ELEMENTOW LISTY O WARTOSCI KRAZEK
struct Lista *ElementListy(int n)
{
    struct Lista* pobrane = (struct Lista*)malloc(sizeof(struct Lista));
    pobrane->krazek = n;
    pobrane->wierzcholek= NULL;
    return pobrane;
}

//CALA STRUKTURA ELEMENTOW WIEZ O WARTOSCI NAZWA
struct Wieza *ListaWiez(char nazwa)
{
  struct Wieza *tower = (struct Wieza*)malloc(sizeof(struct Wieza));
  tower->nazwa = nazwa;
  tower->nastepny = NULL;
  return tower;
}

//FUNKCJA ABY DODAC NA POCZATEK LISTY DANE
void DodajNaPoczatek(struct Wieza *tower, struct Lista *wartosc) 
{
  wartosc->wierzcholek = tower->nastepny;
  tower->nastepny = wartosc;
}

//WYPISANIE DO KONSOLI CALEJ LISTY
void Wypisz(struct Wieza* Lista)
{
    struct Lista *pobrana;
    pobrana = Lista->nastepny;
    while (pobrana != NULL)
    {
        cout << pobrana->krazek << " ";
        pobrana = pobrana->wierzcholek;
    }
    cout << endl;
}

//POBRANANIE WARTOSCI
struct Lista *Pobierz(struct Wieza *dana)
{
  struct Lista *pobrana = dana->nastepny;
  if (pobrana != NULL)
  {
    dana->nastepny = pobrana->wierzcholek;
  }
  return pobrana;
}

//FUNKCJA W CELU WYPISYWANIA NA KTORY SLUPEK CO PRZENIESIONO
int Przenoszenie(struct Wieza *Wieza1, struct Wieza *Wieza2)
{
    struct Lista *pobrana;
    if(Wieza1->nastepny==NULL)
    {
        return -1;
    }
    if(Wieza2->nastepny==NULL||Wieza1->nastepny->krazek < Wieza2->nastepny->krazek)
    {
        pobrana = Pobierz(Wieza1);
        DodajNaPoczatek(Wieza2, pobrana);
        printf("Ze slupka '%c' przeniosono na slupek '%c' krazek o wartosci - %d \n", Wieza1->nazwa, Wieza2->nazwa, pobrana->krazek);
    }
    return -1;
}

//FUNCKJA NA LICZENIE WIEZ HANOI ROZWIAZANY REKURENCYJNIE
void Hanoi(int n,struct Wieza *WiezaA,struct Wieza *WiezaB, struct Wieza *WiezaC )
{
    if (n == 0)
    {
        return;
    }
    Hanoi(n-1, WiezaA, WiezaC, WiezaB); 
    Przenoszenie(WiezaA, WiezaC);
    Hanoi(n-1, WiezaB, WiezaA, WiezaC);
}

//MAIN
int main()
{
    struct Wieza *WiezaA;
    struct Wieza *WiezaB;
    struct Wieza *WiezaC;
    
    int n;
    cout << "Podaj krazek wiezy Hanoi: " << endl;
    cin >> n;
    
    WiezaA = ListaWiez('A');
    WiezaB = ListaWiez('B');
    WiezaC = ListaWiez('C'); 
    
    	int i;
    	for(i = n; i > 0; i--)
        {
            DodajNaPoczatek(WiezaA, ElementListy(i));
        }
        cout << "WIEZE HANOI - START GRY" << endl;
        cout << "Wieza A: " << endl;
        Wypisz(WiezaA);
        cout << "Wieza B: " << endl;
        Wypisz(WiezaB);
        cout << "Wieza C: " << endl;
        Wypisz(WiezaC);
        
        cout << "Etapy przenoszenia:" << endl;
        Hanoi(n, WiezaA, WiezaB, WiezaC);
		cout << endl;
		
		cout << "WIEZE Hanoi - KONIEC GRY" << endl;
        cout << "Wieza A:" << endl;
        Wypisz(WiezaA);
        cout << "Wieza B:" << endl;
        Wypisz(WiezaB);
        cout << "Wieza C: " << endl;
        Wypisz(WiezaC);
	
	return 0;
}
