BIBLIO=-lm -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

etape3 : etape3.o chargementFichier.o ChargementTexture.o Affichage.o MouvementCollision.o
	gcc etape3.o chargementFichier.o ChargementTexture.o Affichage.o MouvementCollision.o -o etape3 $(BIBLIO)
	#
	# La commande pour lancer le programme est : ./etape3
etape3.o: etape3.c chargementFichier.h ChargementTexture.h Affichage.h MouvementCollision.h
	gcc etape3.c -c

MouvementCollision.o: MouvementCollision.c MouvementCollision.h
	gcc MouvementCollision.c -c

Affichage.o: Affichage.c Affichage.h
	gcc Affichage.c -c

ChargementTexture.o: ChargementTexture.c ChargementTexture.h
	gcc ChargementTexture.c -c

chargementFichier.o: chargementFichier.c chargementFichier.h
	gcc chargementFichier.c -c

clean:
	rm -f *.o