#include "head.h"
#define MAXPOSITION 300000

//pour quiter ia() proprement
void liberertout(segment* hist, vecint *descente, vecpos *listepos){
	int i, nb;
	free(hist);
	free(descente->v);
	nb=listepos->nb;
	for(i=0;i<nb;++i){
		free(listepos->pointeur[i]->hist);
		free(listepos->pointeur[i]->enfants);
		free(listepos->pointeur[i]->visitchem);
		free(listepos->pointeur[i]->scorechem);
		free(listepos->pointeur[i]);
	}
	free(listepos->pointeur);
}

int ia(point tab[TAILLE][TAILLE],coup_jouable *listecoup,segment *hist, vecint *cheminfinal, int objectif){
	//declaration des variables
	int nb, maxxx, choix, compteur, scorestart;
	best final;
	point copy[TAILLE][TAILLE];
	segment *copyhist;
	position *actuel, *depart;
	vecpos listepos;
	vecint descente;

	//reserve de mémoire
	descente=remplirvecint(MAXSEGMENT);
	listepos=remplirvec(MAXPOSITION);
	copyhist=malloc(MAXSEGMENT*sizeof(segment));
	copy_tab(tab,copy);
	copy_hist(hist,copyhist);

	//preparation
	coupjouable(copy,listecoup,copyhist);
	nb=listecoup[0].sens;

	listepos.pointeur[0]=malloc(sizeof(position));
	remplirPosition(nb,listepos.pointeur[0],hist);
	++listepos.nb;

	depart=listepos.pointeur[0];
	actuel=depart;
	depart->visits=1;

	scorestart=actuel->hist[0].numero[0].val;
	maxxx=0;
	compteur=0;

	for(;;){
		for(final=selection(listecoup,&listepos,actuel,copy);!actuel->terminal;final=selection(listecoup,&listepos,actuel,copy)){
			descente.v[descente.nb]=final.i;
			++descente.nb;
			if(final.retro){
				ajouterscorechemin(depart,descente,final.score);
				final.retro=0;
				break;
			}
			copy_hist(actuel->hist,copyhist);
			jouersurlistecoup(copy,listecoup,copyhist,final.i);
			actuel=actuel->enfants[final.i];
			coupjouable(copy,listecoup,actuel->hist);
		}
		if(maxxx<descente.nb+scorestart){
			compteur=0;
			maxxx=descente.nb+scorestart;
			copy_vecint(descente,cheminfinal);
			if(maxxx>=objectif){
				printf("Score de %d obtenue. Voulez vous continuer ? [1/0] : ",maxxx);
				scanf("%d",&choix);
				if(choix==0){
					liberertout(copyhist,&descente,&listepos);
					return maxxx;
				}
				else if(choix==1){
					++objectif;
				}
			}
		}
		++compteur;
		if(compteur>5000){
			printf("Score maximum de %d ,voulez vous toujours continuer ? [1/0] : ",maxxx);
			scanf("%d",&choix);
			if(choix==0){
				liberertout(copyhist,&descente,&listepos);
				return maxxx;
			}
			else if(choix==1){
				compteur=0;
			}
		}
		//Retour a la base
		copy_tab(tab,copy);
		actuel=depart;
		descente.nb=0;
		coupjouable(copy,listecoup,actuel->hist);
	}
}

best selection(coup_jouable *listecoup, vecpos *listepos, position *actuel, point tab[TAILLE][TAILLE]){
	//declaration des variables
	int i, nb, save;
	best final;

	//position *choixfinal;
	nb=listecoup[0].sens;
	final.score=0;
	final.i=-1;
	if(nb==0){
		actuel->terminal=1;
		return final;
	}
	else{
		if(!actuel->toutvisit){ //on cherche tout les enfants qui n'ont pas encore été visité
			for(i=0;i<nb;++i){
				if(actuel->enfants[i]==NULL){
					if(expansion(tab,listecoup,listepos,actuel,i)){
						continue;
					}
					//expansion(tab,listecoup,listepos,actuel,i);
					final.i=i;
					final.score=actuel->scorechem[i];
					final.retro=1;
					return final;
				}
			}
			actuel->toutvisit=1;
		}
		for(i=0;i<nb;++i){
			if(actuel->enfants[i]->terminal){
				continue;
			}
			save=actuel->scorechem[i]/actuel->visitchem[i]+2.8*sqrt(log(actuel->visits)/actuel->visitchem[i]);
			if(final.score<save){
				final.score=save;
				final.i=i;
			}
		}
		if(final.i==-1){

			actuel->terminal=1;
			return final;
		}
		return final;
	}
}

//Fonction pour la premiere visité d'un etat
int expansion(point tab[TAILLE][TAILLE], coup_jouable *listecoup, vecpos *listepos, position *actuel, int i){
	//declaration variable
	int save, where;
	point copy[TAILLE][TAILLE];
	segment *copyhist;
	copyhist=malloc(MAXSEGMENT*sizeof(segment));

	//Copiage du tableau et de l'historique puis joue le coup i sur cette copie
	copy_tab(tab,copy);
	copy_hist(actuel->hist,copyhist);
	jouersurlistecoup(copy,listecoup,copyhist,i);
	where=memehist(copyhist,listepos);
	if(where){

		actuel->enfants[i]=listepos->pointeur[where];
		save=jeualeatoire(copy,listecoup,copyhist);
		actuel->scorechem[i]=save;
		actuel->visitchem[i]=1;

		//Pour sortir proprement
		coupjouable(tab,listecoup,actuel->hist);
		free(copyhist);
		return 1;
	}

	//Creation de la position enfants de actuel, i.
	listepos->pointeur[listepos->nb]=malloc(sizeof(position));
	remplirPosition(listecoup[0].sens,listepos->pointeur[listepos->nb],copyhist);
	actuel->enfants[i]=listepos->pointeur[listepos->nb];
	++listepos->nb;

	//Premier jeu de test
	save=jeualeatoire(copy,listecoup,copyhist);
	actuel->scorechem[i]=save;
	actuel->enfants[i]->visits=1;
	actuel->visitchem[i]=1;

	//Pour sortir proprement
	coupjouable(tab,listecoup,actuel->hist);
	free(copyhist);
	return 0;
}