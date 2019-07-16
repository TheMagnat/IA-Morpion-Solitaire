#include "head.h"

int choixaleatoire(int a, int b){
	return rand()%(1+b-a) + a;
}

int jeualeatoire(point tab[TAILLE][TAILLE],coup_jouable *listecoup,segment *hist){
	int choix; //i;
	segment new;
	if(listecoup[0].sens==0){
		return hist[0].numero[0].val;
	}
	choix=choixaleatoire(1, listecoup[0].sens);
	new=jouerpoint(tab,listecoup[choix].courant.x,listecoup[choix].courant.y,listecoup[choix].sens,listecoup[choix].nbsegment);
	hist[1+hist[0].numero[0].val]=new;
	hist[0].numero[0].val+=1;
	tab[listecoup[choix].courant.x][listecoup[choix].courant.y].val=1;
	actualisepoint(tab);
	coupjouable(tab,listecoup,hist);
	return jeualeatoire(tab,listecoup,hist);
}