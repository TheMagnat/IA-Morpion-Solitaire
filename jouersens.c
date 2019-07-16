#ifndef HEAD_H
#include "head.h"
#endif


int historique(segment *hist,segment coup){
   	int cpt, i, j, k;
   	for (i = 1,cpt=0; i < MAXSEGMENT;++i,cpt=0){
   		if(hist[0].numero[0].val<i){
   	      	return 0;
   		}
   	    for(j = 0; j < 5; ++j){
   	    	for (k = 0; k < 5; ++k){
   	        	if(hist[i].numero[j].x==coup.numero[k].x && hist[i].numero[j].y==coup.numero[k].y){
   	           		++cpt;
   	           	}
   	           	if(cpt>1){
   	           		return 1;
   	           	}
   	      	}
   		}
   	}
   	printf("TAILLE HISTORIQUE DEPASSE\n");
   	return 0;
}

segment jouerpoint(point tab[TAILLE][TAILLE], int x, int y, int sens, int nbsegment){
	if(sens & 1){
		return jouerpointcote(tab,x,y,nbsegment);
	}
	else if(sens & 2){
		return jouerpointhaut(tab,x,y,nbsegment);
	}
	else if(sens & 4){
		return jouerpointdiagocroi(tab,x,y,nbsegment);
	}
	else{
		return jouerpointdiagode(tab,x,y,nbsegment);
	}
}



segment jouerpointcote(point tab[TAILLE][TAILLE],int x, int y,int nbsegment){
	int i, compte1, compte2;
	for (i = 1, compte1=0, compte2=0; i < 5; ++i){ 
		if(tab[x+i][y].val==1 && compte1==i-1){
			compte1++;
		}
		if(tab[x-i][y].val==1 && compte2==i-1){
			compte2++;	
		}
	}
	return creersegment(tab, x-compte2+nbsegment, y, x+4-compte2+nbsegment, y);
}

segment jouerpointhaut(point tab[TAILLE][TAILLE],int x, int y,int nbsegment){
	int i, compte1, compte2;
	for (i = 1, compte1=0, compte2=0; i < 5; ++i){
		if(tab[x][y+i].val==1 && compte1==i-1){
			compte1++;
		}
		if(tab[x][y-i].val==1 && compte2==i-1){
			compte2++;
		}
	}
	return creersegment(tab, x, y+compte1-nbsegment, x, y-4+compte1-nbsegment);
}

segment jouerpointdiagocroi(point tab[TAILLE][TAILLE],int x, int y,int nbsegment){
	int i, compte1, compte2;
	for (i = 1, compte1=0, compte2=0; i < 5; ++i){
		if(tab[x+i][y+i].val==1 && compte1==i-1){
			compte1++;
		}
		if(tab[x-i][y-i].val==1 && compte2==i-1){
			compte2++;
		}
	}
	return creersegment(tab, x-compte2+nbsegment, y-compte2+nbsegment, x+4-compte2+nbsegment, y+4-compte2+nbsegment);
}

segment jouerpointdiagode(point tab[TAILLE][TAILLE],int x, int y,int nbsegment){	
	int i, compte1, compte2;
	for (i = 1, compte1=0, compte2=0; i < 5; ++i){
		if(tab[x+i][y-i].val==1 && compte1==i-1){
			compte1++;
		}
		if(tab[x-i][y+i].val==1 && compte2==i-1){
			compte2++;
		}
	}
	return creersegment(tab, x-compte2+nbsegment, y+compte2-nbsegment, x+4-compte2+nbsegment, y-4+compte2-nbsegment);
}