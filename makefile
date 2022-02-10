paddington : main.o state.o
	g++ -o paddington ./make_files/main.o ./make_files/state.o

main.o : main.cpp state.h
	g++ -c -o ./make_files/main.o main.cpp

state.o : state.cpp state.h
	g++ -c -o ./make_files/state.o state.cpp

clean :
	rm paddington ./make_files/main.o ./make_files/state.o