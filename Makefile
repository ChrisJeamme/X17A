CC=gcc
CFLAGS=-Wall -lglut -lGLU -lGL -lm

boulemagique: src/main.o src/boule.o src/decor.o src/karbre.o src/karbre.h src/boule.h
	$(CC) -o $@ $^ $(CFLAGS)

src/decor.o: src/decor.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/karbre.o: src/karbre.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/boule.o: src/boule.c
	$(CC) -o $@ -c $^ $(CFLAGS)

src/main.o: src/main.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	rm -f src/*.o boulemagique 