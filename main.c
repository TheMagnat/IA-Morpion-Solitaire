//Projet morpion solitaire par Magniadas Guillaume et Mehdi Tayebi

#ifndef HEAD_H
#include "head.h"
#endif


int main(int argc, char const *argv[]){
	//declaration des variables
	int objectif, etat, nbdescente, fin, choix;
	point new[TAILLE][TAILLE], copy[TAILLE][TAILLE], fintab[TAILLE][TAILLE];
	segment *hist, *copyhist, *finalhist;
	coup_jouable* listecoup;
	vecint descente, descentefinal;

	srand(time(NULL));

	//reserve de mémoire
	listecoup=malloc(sizeof(coup_jouable)*MAXLISTECOUP);
	finalhist=malloc(MAXSEGMENT*sizeof(segment));
	copyhist=malloc(MAXSEGMENT*sizeof(segment));
	hist=malloc(MAXSEGMENT*sizeof(segment));
	descente=remplirvecint(MAXSEGMENT);
	descentefinal=remplirvecint(MAXSEGMENT);

	hist[0].numero[0].val=0;

	//creation de la position de depart
	fill(new,0);
	croix_greque(new,6,6);
	actualisepoint(new);
	copy_tab(new,copy);
	copy_tab(new,fintab);
	copy_hist(hist,copyhist);
	copy_hist(hist,finalhist);

	coupjouable(copy,listecoup,copyhist);

	printf("Veuillez choisir un premiere objectif (Commencez bas, on le montera au fur et a mesure) (90 est une bonne valeur) : ");
	scanf("%d",&objectif);
	fin=1;
	for(;fin;){
		etat=ia(copy,listecoup,copyhist,&descente,objectif);
		while(1){
			printf("Score de %d atteint, voulez vous relancer l'ia à une autre profondeur [1/0] ? : ",etat);
			scanf("%d",&choix);
			if(choix==0){
				ajoueterdescente(&descentefinal,&descente,descente.nb);
				coupjouable(fintab,listecoup,finalhist);
				sauvegarderdansfichier(etat,fintab,listecoup,finalhist,descentefinal);
				fin=0;
				break;
			}
			else if(choix==1){
				printf("Bien, a quel profondeur souhaitez vous reprendre (Par rapport a la derniere descente) (max :  %d) : ", descente.nb-1);
				while(1){
					scanf("%d",&nbdescente);
					if(nbdescente>=descente.nb || nbdescente<0){
						printf("Veuillez choisir un nombre entre 0 et %d : ", descente.nb);
					}
					break;
				}
				ajoueterdescente(&descentefinal,&descente,nbdescente);
				coupjouable(new,listecoup,hist);
				jouerdescoups(new,listecoup,hist,descente,nbdescente);
				copy_tab(new,copy);
				copy_hist(hist,copyhist);
				printf("Veuillez choisir un nouvel objectif (Nous conseillons d'augmenter un peu l'ancien (de 1 ou 2 )) : ");
				scanf("%d",&objectif);
				break;
			}
			else{
				printf("Erreur de saisie\n");
				continue;
			}
		}
	}
	return 0;
}