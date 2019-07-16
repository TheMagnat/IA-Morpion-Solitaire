#include "head.h"

//Pour initialiser un vecint
vecint remplirvecint(int reserve){
	int i;
	vecint v;
	v.nb=0;
	v.v=malloc(reserve*sizeof(int));
	for(i=0;i<reserve;++i){
		v.v[i]=0;
	}
	return v;
}

//Fonction qui copie un vecteur de position
void copy_vecint(vecint original, vecint *copie){
	int i, nb;
	nb=original.nb;
	copie->nb=nb;
	for(i=0;i<nb;++i){
		copie->v[i]=original.v[i];
	}
}

//Pour initialiser un vecpos
vecpos remplirvec(int reserve){
	vecpos new;
	new.nb=0;
	new.pointeur=malloc(reserve*sizeof(position*));
	return new;
}

//fonction pour remplir une position
void remplirPosition(int nbenfant, position* p, segment *hist){
	int i;
	p->visits=0;
	p->hist=malloc(MAXSEGMENT*sizeof(segment));
	copy_hist(hist,p->hist);
	p->enfants=malloc(nbenfant*sizeof(position*));
	p->visitchem=malloc(nbenfant*sizeof(int));
	p->scorechem=malloc(nbenfant*sizeof(int));
	for(i=0;i<nbenfant;++i){
		p->enfants[i]=NULL;
		p->visitchem[i]=0;
		p->scorechem[i]=0;
	}
	p->toutvisit=0;
	p->terminal=0;
}

void ajoueterdescente(vecint *descentefinal, vecint *chemin, int jusqua){
	int nb, i;
	nb=descentefinal->nb;
	for(i=0;i<jusqua;++i){
		descentefinal->v[nb+i]=chemin->v[i];
	}
	descentefinal->nb+=jusqua;
}

void ajouterscorechemin(position *depart, vecint chemin, int score){
	//declaration variable
	int i, nb;
	position *actuel;
	actuel=depart;
	nb=chemin.nb;

	for(i=0;i<nb;++i){
		++actuel->visits;
		++actuel->visitchem[chemin.v[i]];
		actuel->scorechem[chemin.v[i]]+=score;
		actuel=actuel->enfants[chemin.v[i]];
	}
	++actuel->visits;
}