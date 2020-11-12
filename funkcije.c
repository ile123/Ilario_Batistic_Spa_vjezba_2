#include <stdio.h>
#include <malloc.h>
#include "funkcije.h"

D3_Objekt* STL_bin_citanje(FILE* fpointer)
{
	unsigned int priv_n;
	//odreduje koji niz vrhova
	//mislim da se ovako radi?
	fseek(fpointer, 80, SEEK_SET);
	D3_Objekt* pointer_za_strukt = (D3_Objekt*)malloc(sizeof(D3_Objekt));
	//saznaj kako doci do broj trokuta
	fread(&priv_n, sizeof(unsigned int), 1, fpointer);
	//kako onaj kurac od ovce ima 1404 trokuta?
	//ako ista zaboravis pogledaj prijasnju vjezbu kako se radi
	pointer_za_strukt->n = priv_n;
	trokut* trokut_priv = (trokut*)malloc(sizeof(trokut) * priv_n);
	pointer_za_strukt->niz_trokuta = trokut_priv;
	//zbog nekog glupog razloga size_t je potreban za unsigned int brojeve
	for (size_t i = 0;i < priv_n;i++)
	{
		int j = 0;
		float temp[12];
		fread(&temp, sizeof(float), 12, fpointer);
		for (j;j < 3;j++)
		{
			pointer_za_strukt->niz_trokuta[i].normale[j] = temp[j];
		}
		for (int k = 0;k < 3;k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[0].kordinate[k] = temp[j];
			j++;
		}
		for (int k = 0;k < 3;k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[1].kordinate[k] = temp[j];
			j++;
		}
		for (int k = 0;k < 3;k++)
		{
			pointer_za_strukt->niz_trokuta[i].tocke[2].kordinate[k] = temp[j];
			j++;
		}
		fseek(fpointer, 2, SEEK_CUR);
	}
	return pointer_za_strukt;
}

void Provjera_jeli_radi_ono_dohvacanje(D3_Objekt* pointer_za_strukt)
{
	//ako nesto ovdje neradi to zanci da si se zajeba na prosloj funkciji
	for (size_t i = 0;i < pointer_za_strukt->n;i++)
	{
		printf("\n");
		printf("Normale:\n");
		for (int j = 0;j < 3;j++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].normale[j]);
		}
		printf("\n");
		printf("Prva tocka:\n");
		for (int z = 0;z < 3;z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[0].kordinate[z]);
		}
		printf("\n");
		printf("Druga tocka: \n");
		for (int z = 0;z < 3;z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[1].kordinate[z]);
		}
		printf("\n");
		printf("Treca tocka:\n");
		for (int z = 0;z < 3;z++)
		{
			printf("%f\t", pointer_za_strukt->niz_trokuta[i].tocke[2].kordinate[z]);
		}
	}
}

void stvaranje_bin_STL_dadoteke(D3_Objekt* pointer_za_strukt) {
	FILE* pointer_za_pisanje = fopen("testbin.stl", "wb");
	float nule[80];
	for (int i = 0;i < 80;i++)
	{
		nule[i] = 0;
	}
	unsigned short zadnja_nula = 0;
	unsigned int broj_trokuta = pointer_za_strukt->n;
	fwrite(&nule, sizeof(float), 20, pointer_za_pisanje);
	fwrite(&broj_trokuta, sizeof(unsigned int), 1, pointer_za_pisanje);
	for (size_t i = 0;i < broj_trokuta;i++)
	{
		fwrite(pointer_za_strukt->niz_trokuta[i].normale, sizeof(float), 3, pointer_za_pisanje);
		fwrite(pointer_za_strukt->niz_trokuta[i].tocke, sizeof(float), 9, pointer_za_pisanje);
		fwrite(&zadnja_nula, sizeof(unsigned short), 1, pointer_za_pisanje);
	}
	fclose(pointer_za_pisanje);
}

void stvranje_txt_STL_dadoteke(D3_Objekt* pointer_na_strukt)
{
	FILE* fpointer = fopen("STL_txt.stl", "w");
	fprintf(fpointer, "solid JELI_OVO_RADI?\n");
	unsigned int broj_trokuta = pointer_na_strukt->n;
	for (size_t i = 0;i < broj_trokuta;i++)
	{
		fprintf(fpointer, "facet normal %f %f %f\n", pointer_na_strukt->niz_trokuta[i].normale[0], pointer_na_strukt->niz_trokuta[i].normale[1], pointer_na_strukt->niz_trokuta[i].normale[2]);
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
	free(za_citanje_bin);
}
