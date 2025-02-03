.PHONY: all run

NAMEEXE := diff.exe
OBJ := main.o diff.o tree.o simplify.o read.o diff.o ./myLib/myLib.o -Wall -Wextra -I ./myLib -o diff.exe
all: $(NAMEEXE)

run: $(NAMEEXE)
	.\$(NAMEEXE)

%.o : %.cpp
	@g++ $< -c
