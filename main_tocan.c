#include <stdio.h>
#include <malloc.h>
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

void main()
{
	FILE* fpointer = fopen("primjerbin.stl", "rb");
	//radi za bin citanje i sve ostalo
	D3_Objekt* za_citanje_bin = STL_bin_citanje(fpointer);
	//Provjera_jeli_radi_ono_dohvacanje(za_citanje_bin);
	stvaranje_bin_STL_dadoteke(za_citanje_bin);
	stvranje_txt_STL_dadoteke(za_citanje_bin);
	ciscenje_strukture(za_citanje_bin);
	fclose(fpointer);
}
