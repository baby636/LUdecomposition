#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstring>

double** mcreate(int iw,int ik, double ** tmp)
{
    //double **tab = new double *[iw];
    double **tab=tmp;
    for (int i = iw-1; i >= 0; i--)
    	{
        tab[i] = new double[ik];
    	};
	for (int i=iw-1; i>=0; i--)
		for (int j=ik-1; j>=0; j--)
			{
			tab[i][j] = 0.0;
			}
	return tab;
}

double** mcreateG(int iw,int ik)
{
    double **tab = new double *[iw];
    for (int i = iw-1; i >= 0; i--)
    	{
        tab[i] = new double[ik-i];
    	};
	for (int i=iw-1; i>=0; i--)
		for (int j=i; j<=ik-1; j++)
			{
			tab[i][j] = 0.0;
			}
	return tab;
}

class Element 
{
public:
	unsigned int Enumer;
	double Ewartosc;
	Element *poprzedni, *nastepny;
	//~Element();
};//element

class Lista
{
public:
	Element * poczatek, * koniec, * teraz;

public:
	Lista();
	void NaPoczatek();
	void NaKoniec();
	bool Aktualny(unsigned int &n, double &w);
	bool Nastepny();
	bool Poprzedni();
	void UsunAktualny();
	bool Wstaw(unsigned int numer, double wartosc);
	bool WstawZPamiecia(unsigned int numer, double wartosc);
	double  DajWartoscZPamiecia(unsigned int numer);
	double  DajWartosc(unsigned int numer);
};//lista

bool Lista::Wstaw(unsigned int numer, double wartosc)
{
Element * nowy=new Element;
nowy->Enumer=numer;
nowy->Ewartosc=wartosc;
Element * tmp=poczatek;
Element * tmp_p=NULL;
while ( (tmp)
	&& (tmp->Enumer < numer) )
	{
	tmp_p=tmp;
	tmp=tmp->nastepny;
	}
if (tmp)
if (tmp->Enumer==numer)
	{
	if (wartosc!=0)
	{
	tmp->Ewartosc=wartosc;
	//fprintf(stderr,"wstawi³: %f w miejsce %d\n",wartosc,numer);
	return true;
	}
	else
		{
		UsunAktualny();
		return true;
		}
	}

if (wartosc==0)
	return true;
		
nowy->nastepny=tmp;
if (tmp)
	tmp->poprzedni=nowy;
	else
	koniec=nowy;
nowy->poprzedni=tmp_p;
if (tmp_p)
	tmp_p->nastepny=nowy;
	else
	poczatek=nowy;
//fprintf(stderr,"wstawi³:(%d) %f\n",numer,wartosc);
return true;
}//nowy element 

bool Lista::WstawZPamiecia(unsigned int numer, double wartosc)
{
Element * nowy=new Element;
nowy->Enumer=numer;
nowy->Ewartosc=wartosc;
//Element * tmp=poczatek;
Element * tmp=teraz;
Element * tmp_p=NULL;
while ( (tmp)
	&& (tmp->Enumer < numer) )
	{
	tmp_p=tmp;
	tmp=tmp->nastepny;
	}
if (tmp)
if (tmp->Enumer==numer)
	{
	if (wartosc!=0)
	{
	tmp->Ewartosc=wartosc;
	//fprintf(stderr,"wstawi³: %f w miejsce %d\n",wartosc,numer);
	return true;
	}
	else
		{
		UsunAktualny();
		return true;
		}
	}

if (wartosc==0)
	return true;
		
nowy->nastepny=tmp;
if (tmp)
	tmp->poprzedni=nowy;
	else
	koniec=nowy;
nowy->poprzedni=tmp_p;
if (tmp_p)
	tmp_p->nastepny=nowy;
	else
	poczatek=nowy;
//fprintf(stderr,"wstawi³:(%d) %f\n",numer,wartosc);
return true;
}//nowy element bez przesuniecia na poczatek


double  Lista::DajWartosc(unsigned int numer)
{
teraz=poczatek;
if (teraz)
	{
	while ((teraz)
		&& (teraz->Enumer <= numer))
		{
		if (teraz->Enumer == numer)
			return teraz->Ewartosc;
			else teraz=teraz->nastepny;
		}
		return 0.0;
	}
	else return 0.0;
}//Daj Wartosc

double  Lista::DajWartoscZPamiecia(unsigned int numer)
{
//teraz=poczatek;
if (teraz)
	{
	while ((teraz)
		&& (teraz->Enumer <= numer))
		{
		if (teraz->Enumer == numer)
			return teraz->Ewartosc;
			else teraz=teraz->nastepny;
		}
		return 0.0;
	}
	else return 0.0;
}//Daj Wartosc bez przesuniecia na poczatek

Lista::Lista() 
{
poczatek=koniec=teraz=NULL;
}

void Lista::NaPoczatek()
{
teraz=poczatek;
}

void Lista::NaKoniec()
{
teraz=koniec;
}

bool Lista::Nastepny()
{
if (teraz)
	 {teraz=teraz->nastepny;
	 return true;
	 }
	 else 
	 	return false;
}

bool Lista::Aktualny(unsigned int &n, double &w) 
{

	if (!teraz) 
	{
	return false;
	}
		
	else 
	{
	n=teraz->Enumer;
	w=teraz->Ewartosc;
	}
return true;
}

bool Lista::Poprzedni()
{
if (teraz)
	{teraz=teraz->poprzedni;
	return true;
	}
	else
		return false;
	
}

void Lista::UsunAktualny() 
{
if (teraz) 
  {
	if (teraz->nastepny) 
		{teraz->nastepny->poprzedni=teraz->poprzedni;}
		else {koniec=teraz->poprzedni;}
	if (teraz->poprzedni) 
		{teraz->poprzedni->nastepny=teraz->nastepny;}
		else {poczatek=teraz->nastepny;}
	teraz->poprzedni=teraz->nastepny=NULL;
	delete(teraz);
  }
}


double DajDouble(const std::string& s)
 {
   std::istringstream i(s);
   double x;
   if (i >> x)
     return x;
   // tu powinna siê znajdowaæ jaka¶ obs³uga b³êdów...
   return 0.0;
 }
