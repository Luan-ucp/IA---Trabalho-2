all: agent.o env.o
	gcc agent.o env.o main.c -o main

agent.o: agent.h
	gcc -c agent.c

env.o: env.h
	gcc -c env.c

map.o: map.h
	gcc -c map.c

run: compile
	./main

compile: agent.o env.o
	gcc agent.o env.o main.c -o main
	
clean:
	rm -rf *.o