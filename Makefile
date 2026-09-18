CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -O2
LDFLAGS = -lm
TARGET = optimiseur_lineaire
SRC = Méthode_graphique.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LDFLAGS)

# Analyse statique du code (l'équivalent de flake8 pour le C)
check:
	cppcheck --enable=all --suppress=missingIncludeSystem $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all check clean
