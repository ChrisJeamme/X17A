CC=gcc
CFLAGS=-Wall -lglut -lGLU -lGL -lm

boulemagique: src/main.o src/volume.o src/affichage.o src/karbre.o src/point.h src/matrice.h src/karbre.h src/volume.h
	$(CC) -o $@ $^ $(CFLAGS)

src/affichage.o: src/affichage.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/karbre.o: src/karbre.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/volume.o: src/volume.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/main.o: src/main.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f src/*.o boulemagique 