CC=gcc
CFLAGS=-Wall
SRC=main.c jouable.c jouersens.c remplissage.c affichage.c aleatoire.c iastruct.c deconmcts.c memehist.c
OBJ=main.o jouable.o jouersens.o remplissage.o affichage.o aleatoire.o iastruct.o deconmcts.o memehist.o
HEAD=head.h 

morpion:    $(OBJ) $(HEAD)
	$(CC) $(OBJ) -o $@ -lm

%.o:	%.c
	$(CC) -s -O3 $< $(CFLAGS)

clean:
	rm *.o

cleanall:
	rm *.o morpion

bourdin:
	echo 3,5/20