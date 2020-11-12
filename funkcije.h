#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#include <stdio.h>
#include <malloc.h>

typedef struct
{
	float kordinate[3];
}vrh;

typedef struct
{
	float normale[3];
	vrh tocke[3];
}trokut;

typedef struct
{
	unsigned int n;
	trokut* niz_trokuta;
}D3_Objekt;


// Citanje STL binarne datoteke i spremanje u strukturu Objekt3D
D3_Objekt* STL_bin_citanje(FILE* fpointer);

// Èitanje ispunjenje strukture Objekt3D
void Provjera_jeli_radi_ono_dohvacanje(D3_Objekt* pointer_za_strukt);

// Zapis strukture Objekt3D u binarnu STL datoteku
void stvaranje_bin_STL_dadoteke(D3_Objekt* pointer_za_strukt);

// Funkcija koja Objekt3D strukturu zapisuje u tekstualnu STL datoteku
void stvranje_txt_STL_dadoteke(D3_Objekt* pointer_na_strukt);

void ciscenje_strukture(D3_Objekt* za_citanje_bin);

#endif#pragma once

