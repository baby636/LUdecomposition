/***************************************************************************
 *            program_test.cc
 *
 *  Wed Feb 16 20:31:09 2005
 *  Copyright  2005  
 *  Pawel Gorny
 ****************************************************************************/
 
#define _GNU_SOURCE
#include <math.h>
#include <time.h>
#include "./pg_lu.h"
#define delimiter " "
#define size 256

int file_in;
void sys_err(int terminate);

unsigned int DajRozmiar(char filename[size])
{
unsigned int ile_nie_zero;
FILE * plik;
char * bufor = NULL;
size_t dlugosc = 0;
ssize_t stat;	
unsigned int num=0,linia = 0;
	double wart;

plik=fopen(filename, "r");
fprintf(stderr,"Czytanie rozmiaru z pliku: %s \n",filename);	
	
bufor=NULL;
  while ((stat=getline(&bufor, &dlugosc, plik))!= -1)
      {
	bufor=strtok(bufor, delimiter); //fprintf(stderr,"Wiersz %d, niezerowych: %d \n",linia+1,atol(bufor));	
	for (ile_nie_zero=atol(bufor); ile_nie_zero>0; ile_nie_zero--)
		{
		stat=getline(&bufor, &dlugosc, plik);
		num=atol(strtok(bufor, delimiter)); //fprintf(stderr,"num=%d \n",num);			
		wart=DajDouble(strtok(NULL, delimiter));	//fprintf(stderr,"wart=%f \n",wart);
		}
	linia++;
      }//while czytanie z pliku
fclose(plik);
return num;
}//czytanie pliku

void CzytajPlikBB(char filename[size], double ** tablica)
{
unsigned int ile_nie_zero;
FILE * plik;
char * bufor = NULL;
size_t dlugosc = 0;
ssize_t stat;	
unsigned int linia = 0, num;
	double wart;

plik=fopen(filename, "r");
fprintf(stderr,"Czytanie z pliku: %s \n",filename);	
	
bufor=NULL;
  while ((stat=getline(&bufor, &dlugosc, plik))!= -1)
      {
	bufor=strtok(bufor, delimiter); //fprintf(stderr,"Wiersz %d, niezerowych: %d \n",linia+1,atol(bufor));	
	for (ile_nie_zero=atol(bufor); ile_nie_zero>0; ile_nie_zero--)
		{
		stat=getline(&bufor, &dlugosc, plik);
		num=atol(strtok(bufor, delimiter)); //fprintf(stderr,"num=%d \n",num);			
		wart=DajDouble(strtok(NULL, delimiter));	//fprintf(stderr,"wart=%f \n",wart);
		tablica[linia][num]=wart;//fprintf(stderr,"Wstawimy %f w pole %d,%d\n",wart,linia,num);
		}
	linia++;
      }//while czytanie z pliku
fclose(plik);
fprintf(stderr,"Czytanie zakonczone.\n"); 
}//czytanie pliku

void Transponuj (double ** we, unsigned int rozmiar)
{
unsigned int i,j;
double tmp;
fprintf(stderr,"Transponowanie.\n"); 
for (i=0; i<=rozmiar; i++)
	{
	for (j=i+1; j<=rozmiar; j++)
		{ 
		tmp=we[j][i];
		we[j][i]=we[i][j];
		we[i][j]=tmp;
		}
	}
fprintf(stderr,"Transponowanie zakonczone.\n"); 
}//transponuj

void RozkladLU(double ** wiersze, double ** gora, int rozmiar)
{
int i;
int j;    
double wart;

double ** dol;
dol=new double * [rozmiar+1];
for(i=rozmiar; i>=0; i--) 
	dol[i] = new double [i+1]; 

fprintf(stderr,"Rozklad LU.\n"); 
for (i=rozmiar; i>=0; i--)
	for (j=i; j>=0; j--)	
		dol[i][j] = 0.0;
for (i=rozmiar; i>=0; i--)
	dol[i][i]=1.0;
int k;
clock_t start;
start=clock();
for (i=0; i<=rozmiar; i++)
	{
	for (j=i; j<=rozmiar; j++)
		{
		wart=wiersze[i][j];// (2.4)
		for (k=0; k<=i; k++)
			wart-=dol[i][k] * gora[k][j];
		gora[i][j]=wart;
		//fprintf(stderr,"gora[%d][%d]=%e\n",i,j,wart); 
		}
		
		for (j=i+1; j<=rozmiar; j++)			// (2.5)
		{
		wart=wiersze[j][i];
		for (k=0; k<=i; k++)
			wart-=dol[j][k] * gora[k][i]; 
		wart=wart/gora[i][i];
		dol[j][i]=wart;
		//fprintf(stderr,"dol[%d][%d]=%e\n",i,j,wart); 
		}
	if (i%100==0)
	{
	fprintf(stderr,"postep %d / %d\n",i,rozmiar); 
	}		
		
	}//przetwarzanie
//fprintf(stderr,"skrajny prawy dolny: %e\n",gora[rozmiar][rozmiar]); 
delete [] dol;
fprintf(stderr,"	%f sek.\n", double (clock()-start)/CLOCKS_PER_SEC);
fprintf(stderr,"Rozklad zakonczony.\n"); 
}//rozklad LU

void ZapiszWektorDoPliku(char filename[size], double * wektor,unsigned int rozmiar)
{
FILE * plik;
unsigned int i;
fprintf(stderr,"Zapis do pliku '%s'.\n",filename);	
if ((plik=fopen(filename,"w"))==NULL)
    {
    fprintf(stderr,"Nieudane tworzenie pliku do zapisu.\n");
    exit(EXIT_FAILURE);
    }
    else
	{
	//fprintf(plik,"%d\n",rozmiar+1);
	for (i=0; i<=rozmiar; i++)
	    fprintf(plik,"%d\t%e\n",i,wektor[i]);
        }
fprintf(stderr,"Zapis zakonczony.\n");		
}//zapis do pliku

double PrzetwarzanieUkladu(int rozmiar, double ** gora, double * wektor)
{
double suma,sumatmp,tmp,wart;
int i,j;
fprintf(stderr,"Liczenie ukladu Uz.\n"); 
for (i=0; i<=rozmiar-1; i++)
    wektor[i]=0.0;

suma=wektor[rozmiar]=1;

for (i=rozmiar-1; i>=0; i--)
    {
    wart=gora[i][i];
	if (wart!=0.0)
	{ 
	sumatmp=0.0;
	for (j=i+1; j<=rozmiar; j++)
		sumatmp+=(gora[i][j] * wektor[j]);
	if (sumatmp!=0.0)
	    {
	    tmp=(sumatmp/wart)*(-1);
	    wektor[i]=tmp;
	    suma+=tmp;
		//fprintf(stderr,"i=%d war=%e suma=%e.\n",i,tmp,suma); 
	    }
	}
    }
suma=1.0/suma;
for (i=rozmiar; i>=0; i--)
		wektor[i]*=suma;
fprintf(stderr,"Uklad zakonczony.\n"); 
return suma;
}//przetwarzanie ukladu

void SprawdzenieWyniku(double ** wiersze, double * wektor, unsigned int rozmiar)
{
double wynik=0;
int i,j;
double tmp=0;

for (i=rozmiar; i>=0; i--)
    {
    tmp=0;
    for (j=rozmiar; j>=0; j--)
			tmp+= wiersze[i][j]*(wektor[j]);
    wynik+=tmp*tmp;
    }
fprintf(stderr,"Norma kontrolna: %e\n",sqrt(wynik));
}

int main(int argc, char * argv[])
{
char filename[size];

if (argc < 2) 
  {
    fprintf(stderr,"Musisz podac nazwe pliku do wczytania! \n");
    exit(EXIT_FAILURE);
  }    
  
strcpy(filename,argv[1]);
const unsigned int rozmiar=DajRozmiar(filename); // !!!!!!!!!!!!!

double * tmp [rozmiar+1];
double ** tablica=mcreate(rozmiar+1,rozmiar+1,tmp);

CzytajPlikBB(filename,tablica);

Transponuj(tablica,rozmiar);	

double ** gora=mcreateG(rozmiar+1,rozmiar+1);

RozkladLU(tablica,gora,rozmiar);	
	
double wektor[rozmiar+1];
PrzetwarzanieUkladu(rozmiar,gora,wektor);

SprawdzenieWyniku(tablica, wektor, rozmiar);
  
strcpy(filename+strlen(filename),"_wektor");
ZapiszWektorDoPliku(filename,wektor,rozmiar);

exit(0);
} //main
