#le compilateur
CC= gcc

#les flags de compilation
CFLAGS= -std=c99 -Wall -g

#les noms des fichiers executable
OUTFILES= 10K2 C10 G36 kneser62 kneser72 kneser73 kneser83 m47 m95 petersen sierp3

#les fichiers objet
OBJS= translate.o 10K2.o C10.o G36.o kneser62.o kneser72.o kneser73.o kneser83.o m47.o m95.o petersen.o sierp3.o

#les dépendances
all: $(OUTFILES)

10K2: 10K2.o translate.o
	$(CC) $^ -o $@
C10: C10.o translate.o
	$(CC) $^ -o $@
G36: G36.o translate.o
	$(CC) $^ -o $@
kneser62: kneser62.o translate.o
	$(CC) $^ -o $@
kneser72: kneser72.o translate.o
	$(CC) $^ -o $@
kneser73: kneser73.o translate.o
	$(CC) $^ -o $@
kneser83: kneser83.o translate.o
	$(CC) $^ -o $@
m47: m47.o translate.o
	$(CC) $^ -o $@
m95: m95.o translate.o
	$(CC) $^ -o $@
petersen: petersen.o translate.o
	$(CC) $^ -o $@
sierp3: sierp3.o translate.o
	$(CC) $^ -o $@

%o: %c
	$(CC) -c $(CFLAGS) $< -o $@

translate.o: translate.c all.h
10K2.o: 10K2.c all.h
C10.o: C10.c all.h
G36.o: G36.c all.h
kneser62.o: kneser62.c all.h
kneser72.o: kneser72.c all.h
kneser73.o: kneser73.c all.h
kneser83.o: kneser83.c all.h
m47.o: m47.c all.h
m95.o: m95.c all.h
petersen.o: petersen.c all.h
sierp3.o: sierp3.c all.h

clean:
	rm -f $(OUTFILES) $(OBJS) *~

install:
	make all
	rm -f $(OBJS) *~
