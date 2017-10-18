#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

#les noms des fichiers executable
OUTFILES= translate

#les fichiers objet
OBJS= translate.o

#les dépendances
all: $(OUTFILES)

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@

translate: translate.o
	$(CC) $^ -o $@

translate.o: translate.c all.h

clean:
	rm -f $(OUTFILES) $(OBJS) *~
