SO2_projekt3: SO2_projekt3.o Timer.o Status.o PersonType.o RoomType.o Visualization.o Person.o Room.o Classroom.o Cloakroom.o DeanOffice.o Floor.o Lecturer.o Student.o Checker.o UniversityWorker.o Toilet.o Corridor.o Entrance.o
	g++ -std=c++11 -pthread -lncurses ./object/SO2_projekt3.o ./object/Timer.o ./object/RoomType.o ./object/Visualization.o ./object/Person.o ./object/Room.o ./object/Classroom.o ./object/Cloakroom.o ./object/DeanOffice.o ./object/Floor.o ./object/Lecturer.o ./object/Checker.o ./object/Student.o ./object/UniversityWorker.o ./object/PersonType.o ./object/Status.o ./object/Toilet.o ./object/Corridor.o ./object/Entrance.o -o ./executable/SO2_projekt3
Toilet.o: Toilet.cpp
	g++ -std=c++11 -c Toilet.cpp -o ./object/Toilet.o
Student.o: Student.cpp
	g++ -std=c++11 -c Student.cpp -o ./object/Student.o
Lecturer.o: Lecturer.cpp
	g++ -std=c++11 -c Lecturer.cpp -o ./object/Lecturer.o
Floor.o: Floor.cpp
	g++ -std=c++11 -c Floor.cpp -o ./object/Floor.o
DeanOffice.o: DeanOffice.cpp
	g++ -std=c++11 -c DeanOffice.cpp -o ./object/DeanOffice.o
Cloakroom.o: Cloakroom.cpp
	g++ -std=c++11 -c Cloakroom.cpp -o ./object/Cloakroom.o
Classroom.o: Classroom.cpp
	g++ -std=c++11 -c Classroom.cpp -o ./object/Classroom.o
Room.o: Room.cpp
	g++ -std=c++11 -c Room.cpp -o ./object/Room.o
Person.o: Person.cpp
	g++ -std=c++11 -c Person.cpp -o ./object/Person.o
Visualization.o: Visualization.cpp
	g++ -std=c++11 -c Visualization.cpp -o ./object/Visualization.o
Timer.o: Timer.cpp
	g++ -std=c++11 -c Timer.cpp -o ./object/Timer.o
Checker.o: Checker.cpp
	g++ -std=c++11 -c Checker.cpp -o ./object/Checker.o
UniversityWorker.o: UniversityWorker.cpp
	g++ -std=c++11 -c UniversityWorker.cpp -o ./object/UniversityWorker.o
PersonType.o: PersonType.cpp
	g++ -std=c++11 -c PersonType.cpp -o ./object/PersonType.o
Status.o: Status.cpp
	g++ -std=c++11 -c Status.cpp -o ./object/Status.o
RoomType.o: RoomType.cpp
	g++ -std=c++11 -c RoomType.cpp -o ./object/RoomType.o
Corridor.o: Corridor.cpp
	g++ -std=c++11 -c Corridor.cpp -o ./object/Corridor.o
Entrance.o: Entrance.cpp
	g++ -std=c++11 -c Entrance.cpp -o ./object/Entrance.o
SO2_projekt3.o: SO2_projekt3.cpp
	g++ -std=c++11 -c SO2_projekt3.cpp -o ./object/SO2_projekt3.o


