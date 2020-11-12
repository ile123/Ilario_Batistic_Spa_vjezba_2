#include "funkcije.h"

D3_Objekt* STL_bin_citanje(FILE* fpointer)
{
	unsigned int priv_n;
	//odreduje koji niz vrhova
	//mislim da se ovako radi?
	fseek(fpointer, 80, SEEK_SET);
	D3_Objekt* pointer_za_strukt = (D3_Objekt*)malloc(sizeof(D3_Objekt));
	fread(&priv_n, sizeof(unsigned int), 1, fpointer);
	pointer_za_strukt->n = priv_n;
	pointer_za_strukt->niz_trokuta = (trokut*)malloc(sizeof(trokut)*priv_n);
	//saznaj kako doci do broj trokuta
	//kako onaj kurac od ovce ima 1404 trokuta?
	//ako ista zaboravis pogledaj prijasnju vjezbu kako se radi

	//zbog nekog glupog razloga size_t je potreban za unsigned int brojeve
	for (size_t i = 0; i < priv_n; i++)
	{
		int j = 0;
		float temp[12];
		unsigned short temp2[1];
		fread(temp, sizeof(float), 12, fpointer);
		for (j; j < 3; j++)
		{
			pointer_za_strukt->niz_trokuta[i].normala[j] = temp[j];
		}
		for (int k = 0; k < 3; k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[0].kordinate[k] = temp[j];
			j++;
		}
		for (int k = 0; k < 3; k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[1].kordinate[k] = temp[j];
			j++;
		}
		for (int k = 0; k < 3; k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[2].kordinate[k] = temp[j];
			j++;
		}
		fread(temp2, sizeof(short), 1, fpointer);
		pointer_za_strukt->niz_trokuta[i].boja = temp2[j];
	}
	return pointer_za_strukt;
}

void Provjera_jeli_radi_ono_dohvacanje(D3_Objekt* pointer_za_strukt)
{
	//ako nesto ovdje neradi to zanci da si se zajeba na prosloj funkciji
	for (size_t i = 0; i < pointer_za_strukt->n; i++)
	{
		printf("\n");
		printf("Normale:\n");
		for (int j = 0; j < 3; j++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].normala[j]);
		}
		printf("\n");
		printf("Prva tocka:\n");
		for (int z = 0; z < 3; z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[0].kordinate[z]);
		}
		printf("\n");
		printf("Druga tocka: \n");
		for (int z = 0; z < 3; z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[1].kordinate[z]);
		}
		printf("\n");
		printf("Treca tocka:\n");
		for (int z = 0; z < 3; z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[2].kordinate[z]);
		}
		printf("\n");
		printf("Boja:\n");
		printf("%u", pointer_za_strukt->niz_trokuta[i].boja);
	}
}

void stvaranje_bin_STL_dadoteke(D3_Objekt* pointer_za_strukt) {
	FILE* pointer_za_pisanje = fopen("testbin.stl", "wb");
	char nule[80];
	for (int i = 0; i < 80; i++)
	{
		nule[i] = 0;
	}
	unsigned int broj_trokuta = pointer_za_strukt->n;
	//1 byte 80 puta
	fwrite(nule, 1, 80, pointer_za_pisanje);
	fwrite(&broj_trokuta, sizeof(unsigned int), 1, pointer_za_pisanje);
	for (size_t i = 0; i < broj_trokuta; i++)
	{
		fwrite(&pointer_za_strukt->niz_trokuta[i], 50, 1, pointer_za_pisanje);
	}
	fclose(pointer_za_pisanje);
}

void stvranje_txt_STL_dadoteke(D3_Objekt* pointer_na_strukt)
{
	FILE* fpointer = fopen("STL_txt.stl", "wt");
	fprintf(fpointer, "solid JELI_OVO_RADI?\n");
	unsigned int broj_trokuta = pointer_na_strukt->n;
	for (size_t i = 0; i < broj_trokuta; i++)
	{
		fprintf(fpointer, "facet normal %f %f %f\n", pointer_na_strukt->niz_trokuta[i].normala[0], pointer_na_strukt->niz_trokuta[i].normala[1], pointer_na_strukt->niz_trokuta[i].normala[2]);
		fprintf(fpointer, "outer loop\n");
		fprintf(fpointer, "vertex %f %f %f\n", pointer_na_strukt->niz_trokuta[i].tocke[0].kordinate[0], pointer_na_strukt->niz_trokuta[i].tocke[0].kordinate[1], pointer_na_strukt->niz_trokuta[i].tocke[0].kordinate[2]);
		fprintf(fpointer, "vertex %f %f %f\n", pointer_na_strukt->niz_trokuta[i].tocke[1].kordinate[0], pointer_na_strukt->niz_trokuta[i].tocke[1].kordinate[1], pointer_na_strukt->niz_trokuta[i].tocke[1].kordinate[2]);
		fprintf(fpointer, "vertex %f %f %f\n", pointer_na_strukt->niz_trokuta[i].tocke[2].kordinate[0], pointer_na_strukt->niz_trokuta[i].tocke[2].kordinate[1], pointer_na_strukt->niz_trokuta[i].tocke[2].kordinate[2]);
		fprintf(fpointer, "endloop\n");
		fprintf(fpointer, "endfacet\n");
	}
	fprintf(fpointer, "endsolid JELI_OVO_RADI?\n");
	fclose(fpointer);
}

void ciscenje_strukture(D3_Objekt* za_citanje_bin)
{
    free(za_citanje_bin->niz_trokuta);
	free(za_citanje_bin);
}
