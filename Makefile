CC=gcc
CFLAGS=-Wall -lglut -lGLU -lGL -lm -lSOIL

boulemagique: src/main.o src/jeu.o src/boule.o src/decor.o src/menu.o src/gui.o src/entree.o src/karbre.o src/niveaux.o src/niveaux.h src/gui.h src/decor.h src/karbre.h src/jeu.h src/boule.h src/menu.h src/entree.h
	$(CC) -o $@ $^ $(CFLAGS)

src/decor.o: src/decor.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/karbre.o: src/karbre.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/boule.o: src/boule.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/menu.o: src/menu.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/entree.o: src/entree.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/gui.o: src/gui.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/niveaux.o: src/niveaux.c 
	$(CC) -o $@ -c $^ $(CFLAGS)

src/jeu.o: src/jeu.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/main.o: src/main.c 
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f src/*.o boulemagique 