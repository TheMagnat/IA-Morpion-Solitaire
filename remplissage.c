#ifndef HEAD_H
#include "head.h"
#endif

//fonction qui remplie un tableau de point
void fill(point tab [TAILLE][TAILLE],int n)
{
	int i, j;
	for (i = 0; i < TAILLE; ++i){
	    for (j= 0; j < TAILLE; ++j){
			tab[j][i].x=j;
			tab[j][i].y=i;
			tab[j][i].val=n;
			tab[j][i].possible=0;
			tab[j][i].totalligne=0;
			tab[j][i].totalcolonne=0;
			tab[j][i].totaldiagocroi=0;
			tab[j][i].totaldiagode=0;
			tab[j][i].total=0;
		}
	}
}

//insere la croix greque
void croix_greque(point tab[TAILLE][TAILLE],int n,int m){
	int i;
	for (i = 5; i < 9; ++i){
		tab[m+2][n+i].val=1;	
		tab[m+5][n+i-3].val=1;
		tab[m+5][n+i+3].val=1;
		tab[m+8][n+i-3].val=1;
		tab[m+8][n+i+3].val=1;
		tab[m+11][n+i].val=1;
	}
	for (i = 3; i < 5; ++i){
		tab[m+i][n+5].val=1;
		tab[m+i][n+8].val=1;
		tab[m+i+3][n+2].val=1;
		tab[m+i+3][n+11].val=1;
		tab[m+i+6][n+5].val=1;
		tab[m+i+6][n+8].val=1;
	}
}

//copie un tableau de point
void copy_tab(point tab[TAILLE][TAILLE],point copie[TAILLE][TAILLE]){
	int i, j;
	for (i = 0; i < TAILLE; ++i){
		for (j = 0; j < TAILLE; ++j){
			copie[i][j]=tab[i][j];

		}
	}
}

//Fonction qui copie un tableau de segment
void copy_hist(segment *tab,segment *copy){
	int i;
	for(i=0;i<MAXSEGMENT;++i){
		copy[i]=tab[i];
	}
}

//fonction qui creer un segment a l'aide des coordoné de deux point
segment creersegment(point tab[TAILLE][TAILLE],int x1,int y1,int x2,int y2)
{
	int i, d, h;
	segment new;
	if(x1<x2){
		d=1;
	}
	else if(x1>x2){
		d=-1;
	}
	else{
		d=0;
	}
	if(y1<y2){
		h=1;
	}
	else if(y1>y2){
		h=-1;
	}
	else{
		h=0;
	}
	for (i = 0; i <5 ; ++i){
		new.numero[i]=tab[x1+d*i][y1+h*i];
	}
	return new;
}

void jouersurlistecoup(point tab[TAILLE][TAILLE], coup_jouable *listecoup, segment *hist, int quelcoup){
	segment new;
	new=jouerpoint(tab,listecoup[quelcoup+1].courant.x,listecoup[quelcoup+1].courant.y,listecoup[quelcoup+1].sens,listecoup[quelcoup+1].nbsegment);
	hist[1+hist[0].numero[0].val]=new;
	hist[0].numero[0].val+=1;
	tab[listecoup[quelcoup+1].courant.x][listecoup[quelcoup+1].courant.y].val=1;
	actualisepoint(tab);
	coupjouable(tab,listecoup,hist);
}

void jouerdescoups(point tab[TAILLE][TAILLE],coup_jouable *listecoup,segment *hist, vecint chemin, int profondeur){
	int i;
	for(i=0;i<profondeur;++i){
		jouersurlistecoup(tab,listecoup,hist,chemin.v[i]);
	}
}