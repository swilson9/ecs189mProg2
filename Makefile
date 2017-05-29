 DEFAULT_GOAL := all

overlord.out : overlord.c
	gcc -Wall overlord.c -o overlord.out

necromancer.out: necromancer.c
	gcc -Wall necromancer.c -o necromancer.out

zombie.out: zombie.c
	gcc -Wall zombie.c -o zombie.out

.PHONY: clean all

all: necromancer.out overlord.out zombie.out
	make overlord.out
	make necromancer.out
	make zombie.out

clean:
	rm 0f *.out core
