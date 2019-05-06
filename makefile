

run:  main.o rsdl.o menu.o game.o New_game.o ball.o brick.o life_ball.o fire_ball.o button.o edit.o score.o game_over.o
	g++ game_over.o score.o edit.o button.o fire_ball.o life_ball.o brick.o ball.o New_game.o game.o menu.o main.o rsdl.o -l SDL2 -l SDL2_image -l SDL2_ttf -std=c++11 -o run
main.o: main.cpp
	g++ -c main.cpp
rsdl.o: rsdl.cpp rsdl.hpp
	g++ -c rsdl.cpp
menu.o: menu.cpp menu.hpp
	g++ -c menu.cpp
game.o: game.cpp game.hpp 
	g++ -std=c++11 -c game.cpp
New_game.o: New_game.cpp New_game.hpp
	g++ -std=c++11 -c New_game.cpp
ball.o: ball.cpp ball.hpp
	g++ -c ball.cpp
brick.o: brick.cpp brick.hpp
	g++ -std=c++11 -c brick.cpp
life_ball.o: life_ball.hpp life_ball.cpp
	g++ -c life_ball.cpp
fire_ball.o: fire_ball.hpp fire_ball.cpp
	g++ -c fire_ball.cpp
button.o: button.hpp button.cpp
	g++ -c button.cpp
edit.o: edit.hpp edit.cpp
	g++ -c edit.cpp
score.o: score.cpp
	g++ -std=c++11 -c score.cpp
game_over.o: game_over.cpp
	g++ -std=c++11 -c game_over.cpp	

clean:
	rm -f *.o run