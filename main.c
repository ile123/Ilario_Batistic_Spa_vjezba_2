#include <stdio.h>
#include <malloc.h>
#include "funkcije.h"


void main()
{
	FILE* fpointer = fopen("primjertxt.stl", "r");
	//radi za bin citanje i sve ostalo
	D3_Objekt* za_citanje_bin = STL_bin_citanje(fpointer);
	Provjera_jeli_radi_ono_dohvacanje(za_citanje_bin);
	stvaranje_bin_STL_dadoteke(za_citanje_bin);
	stvranje_txt_STL_dadoteke(za_citanje_bin);
	ciscenje_strukture(za_citanje_bin);
	fclose(fpointer);
}
