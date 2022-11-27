#Initialisation de mes variables
CC = gcc
EXEC = prog
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

#Début de ma compilation avec les fichiers nécessaires
all : $(EXEC)

%.o : %.c
	$(CC) -o $@  -c $<

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^


#Nettoyage de mes fichiers en .o
clean : 
	rm -rf *.o

#Nettoyage total de mes fichiers en .o et de l'executable
cleanall : clean
	rm -rf prog