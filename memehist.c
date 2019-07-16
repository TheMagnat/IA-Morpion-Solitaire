#include "head.h"

//fonction lancant memepos() sur tout les tableaux de segments des positions pointé par listepos
int memehist(segment *hist, vecpos *listepos){
	int i, nb;
	nb=listepos->nb;
	for(i=0;i<nb;++i){
		if(listepos->pointeur[i]==NULL){
			continue;
		}
		if(memepos(hist,listepos->pointeur[i]->hist)){
			return i;
		}
	}
	return 0;
}

//Fonction comparant deux tableau de segment et qui retourne 1 si elles contiennent exactement les même segments ou 0 si elles en ont au moins 1 de different
int memepos(segment *hist1, segment *hist2){
	int nb1, nb2, i, j, verif;
	nb1=hist1[0].numero[0].val;
	nb2=hist2[0].numero[0].val;
	if(nb1!=nb2){
		return 0;
	}
	for(i=1, verif=0;i<=nb2;++i){
		for(j=1;j<=nb1;++j){
			if(hist1[j].numero[0].x==hist2[i].numero[0].x && hist1[j].numero[0].y == hist2[i].numero[0].y){
				if(hist1[j].numero[4].x==hist2[i].numero[4].x && hist1[j].numero[4].y == hist2[i].numero[4].y){
					++verif;
					break;
				}
			}
		}
		if(!verif){
			return 0;
		}
	}
	if(verif==nb1){
		return 1;
	}
	return 0;
}