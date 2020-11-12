#include <stdio.h>
#include <malloc.h>
#ifndef FUNKCIJE_H
#define FUNKCIJE_H

typedef struct
{
	float kordinate[3];
}vrh;

typedef struct
{
	float normala[3];
	vrh tocke[3];
	unsigned short boja;
}trokut;

typedef struct
{
	unsigned int n;
	trokut* niz_trokuta;
}D3_Objekt;

D3_Objekt* STL_bin_citanje(FILE* fpointer);

void Provjera_jeli_radi_ono_dohvacanje(D3_Objekt* pointer_za_strukt);

void stvaranje_bin_STL_dadoteke(D3_Objekt* pointer_za_strukt);

void stvranje_txt_STL_dadoteke(D3_Objekt* pointer_na_strukt);

void ciscenje_strukture(D3_Objekt* za_citanje_bin);

#endif // FUNKCIJE_H
