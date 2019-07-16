#ifndef HEAD_H
#include "head.h"
#endif


void jouable(point tab[TAILLE][TAILLE],int x,int y){
	int i, compte1, compte2;
	int lignes, colones, diagocroi, diagode;
	tab[x][y].possible=0;
	tab[x][y].total=0;
	lignes=0;
	colones=0;
	diagocroi=0;
	diagode=0;
	if(tab[x][y].val!=0){
		return;
	}
	else if(x+1>=TAILLE || y+1>=TAILLE|| x-1<0 || y-1<0 || (tab[x+1][y].val==0 && tab[x-1][y].val==0 && tab[x][y+1].val==0 && tab[x][y-1].val==0 && tab[x+1][y+1].val==0 && tab[x-1][y-1].val==0 && tab[x+1][y-1].val==0 && tab[x-1][y+1].val==0)){
		return;
	}
	else{
		//parcour des lignes
		for (i = 1, compte1=0, compte2=0; i < 5; ++i){ 
		  	if(tab[x+i][y].val==1 && compte1==i-1){
		  		compte1++;
		  	}
		  	if(tab[x-i][y].val==1 && compte2==i-1){
		  		compte2++;	
		  	}
		}
		if(compte1+compte2>3){
			lignes=1;
			tab[x][y].totalligne=compte1+compte2-3;
		}
		//parcour des colones
		for (i = 1, compte1=0, compte2=0; i < 5; ++i){
			if(tab[x][y+i].val==1 && compte1==i-1){
				compte1++;
			}
			if(tab[x][y-i].val==1 && compte2==i-1){
				compte2++;
			}
		}
		if(compte1+compte2>3){
			colones=2;
			tab[x][y].totalcolonne=compte1+compte2-3;
		}
		//parcourir la diagonale croissante
		for (i = 1, compte1=0, compte2=0; i < 5; ++i){
			if(tab[x+i][y+i].val==1 && compte1==i-1){
				compte1++;
			}
			if(tab[x-i][y-i].val==1 && compte2==i-1){
				compte2++;
			}
		}
		if(compte1+compte2>3){
			diagocroi=4;
			tab[x][y].totaldiagocroi=compte1+compte2-3;
		}
		//parcourir la diagonale decroissante
		for (i = 1, compte1=0, compte2=0; i < 5; ++i){
			if(tab[x+i][y-i].val==1 && compte1==i-1){
				compte1++;
			}
			if(tab[x-i][y+i].val==1 && compte2==i-1){
				compte2++;
			}
		}
		if(compte1+compte2>3){
			diagode=8;
			tab[x][y].totaldiagode=compte1+compte2-3;
		}
		tab[x][y].possible=lignes+colones+diagocroi+diagode;
		tab[x][y].total=tab[x][y].totalligne+tab[x][y].totalcolonne+tab[x][y].totaldiagocroi+tab[x][y].totaldiagode;
	}
}

void coupjouable(point tab[TAILLE][TAILLE],coup_jouable listecoup[MAXLISTECOUP],segment *hist){
	int i, j, k, possitest;
	segment new;
	listecoup[0].sens=0;
	for (i = 0; i < TAILLE; ++i){
		for(j=0;j<TAILLE;j++){
			possitest=tab[j][i].possible;
			if(possitest>0 && tab[j][i].val==0){
				if(possitest & 1){
					for(k=0;k<tab[j][i].totalligne;++k){
						new=jouerpoint(tab,j,i,1,k);
						if(!historique(hist,new)){
							++listecoup[0].sens;
							listecoup[listecoup[0].sens].courant=tab[j][i];
							listecoup[listecoup[0].sens].sens=1;
							listecoup[listecoup[0].sens].nbsegment=k;
						}
					}
				}
				if(possitest & 2){
					for(k=0;k<tab[j][i].totalcolonne;++k){
						new=jouerpoint(tab,j,i,2,k);
						if(!historique(hist,new)){
							++listecoup[0].sens;
							listecoup[listecoup[0].sens].courant=tab[j][i];
							listecoup[listecoup[0].sens].sens=2;
							listecoup[listecoup[0].sens].nbsegment=k;
						}
					}
				}
				if(possitest & 4){
					for(k=0;k<tab[j][i].totaldiagocroi;++k){
						new=jouerpoint(tab,j,i,4,k);
						if(!historique(hist,new)){
							++listecoup[0].sens;
							listecoup[listecoup[0].sens].courant=tab[j][i];
							listecoup[listecoup[0].sens].sens=4;
							listecoup[listecoup[0].sens].nbsegment=k;
						}
					}
				}
				if(possitest & 8){
					for(k=0;k<tab[j][i].totaldiagode;++k){
						new=jouerpoint(tab,j,i,8,k);
						if(!historique(hist,new)){
							++listecoup[0].sens;
							listecoup[listecoup[0].sens].courant=tab[j][i];
							listecoup[listecoup[0].sens].sens=8;
							listecoup[listecoup[0].sens].nbsegment=k;
						}
					}
				}
			}
		}
	}
}


//fonction qui lance la fonction jouable sur tout les points du tableau
void actualisepoint(point tab[TAILLE][TAILLE]){
	int i, j;
	for(i=0;i<TAILLE;++i){
		for(j=0;j<TAILLE;++j){
			jouable(tab,j,i);
		}
	}
}