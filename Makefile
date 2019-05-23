SO2_projekt3: SO2_projekt3.o Application.o Philosopher.o Visualization.o Timer.o
	g++ -std=c++11 -pthread -lncurses ./object/SO2_projekt3.o ./object/Application.o ./object/Philosopher.o ./object/Visualization.o ./object/Timer.o -o ./executable/SO2_projekt3
Timer.o: Timer.cpp
	g++ -std=c++11 -c Timer.cpp -o ./object/Timer.o
Visualization.o: Visualization.cpp
	g++ -std=c++11 -c Visualization.cpp -o ./object/Visualization.o
Philosopher.o: Philosopher.cpp
	g++ -std=c++11 -c Philosopher.cpp -o ./object/Philosopher.o
Application.o: Application.cpp
	g++ -std=c++11 -c Application.cpp -o ./object/Application.o
SO2_projekt3.o: SO2_projekt3.cpp
	g++ -std=c++11 -c SO2_projekt3.cpp -o ./object/SO2_projekt3.o


