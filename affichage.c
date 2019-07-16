#ifndef HEAD_H
#include "head.h"
#endif

//fonction qui affiche un tableau de point
void affiche(point tab[TAILLE][TAILLE]){
	int i, j;
	printf("\t");
	for(i=0;i<11;++i){
		printf(" %d",i);
	}
	printf(" ...\n");
	for (i = 0; i < TAILLE; ++i){
		printf("%d\t|",i);
		for (j = 0; j < TAILLE; ++j){
	       	if(tab[j][i].val==0){
           		printf(" |");
	       	}
       		else{
       			printf("O|");
       		}
		}
		printf("\n");
	}
}

void faffiche(point tab[TAILLE][TAILLE], FILE * f){
	int i, j;
	fprintf(f,"\t");
	for(i=0;i<11;++i){
		fprintf(f," %d",i);
	}
	fprintf(f," ...\n");
	for (i = 0; i < TAILLE; ++i){
		fprintf(f,"%d\t|",i);
		for (j = 0; j < TAILLE; ++j){
	       	if(tab[j][i].val==0){
           		fprintf(f," |");
	       	}
       		else{
       			fprintf(f,"O|");
       		}
		}
		fprintf(f,"\n");
	}
}

void sauvegarderdansfichier(int score, point tab[TAILLE][TAILLE],coup_jouable *listecoup,segment *hist, vecint cheminfinal){
	int nb, i;
	FILE * f;
	char nom[50];
	snprintf(nom, sizeof nom, "Morpion_solitaire_score_%d.txt", score);
	f = fopen(nom,"w+");
	nb=cheminfinal.nb;
	for(i=0;i<nb;++i){
		faffiche(tab,f);
		fprintf(f,"\nSCORE : %d\n",hist[0].numero[0].val);
		fprintf(f,"\n\nNous jouons ce coup : \n");
		fprintf(f,"x= %d, \ty= %d,\tsens= %d,\tNumero du segment= %d\n\n",listecoup[cheminfinal.v[i]+1].courant.x,listecoup[cheminfinal.v[i]+1].courant.y,listecoup[cheminfinal.v[i]+1].sens,listecoup[cheminfinal.v[i]+1].nbsegment);
		jouersurlistecoup(tab,listecoup,hist,cheminfinal.v[i]);
	}
	faffiche(tab,f);
	fprintf(f,"SCORE : %d\n",hist[0].numero[0].val);
}