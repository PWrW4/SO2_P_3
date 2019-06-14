#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

#include "Lecturer.hpp"
#include "Person.hpp"
#include "Floor.hpp"
#include "Classroom.hpp"
#include "Cloakroom.hpp"
#include "Entrance.hpp"
#include "Toilet.hpp"
#include "Corridor.hpp"
#include "Room.hpp"
#include "Visualization.hpp"
#include "Student.hpp"
#include "DeanCrew.hpp"
#include "Checker.hpp"


using namespace std;

void JoinAll();
void Cleanup();
void ScanForExit();
std::vector<Person*> students;
std::vector<Person*> profesors;
std::vector<Person*> dziekanatworkers;
std::vector<Person*> szatniaworkers;
int numberStudents = 50;
int numberProfesors = 5;
int numberDziekanatworkers = STAMPS_CNT;
int numberszatniaworkers = 2;
bool *isEnd = new bool;
Floor *f = new Floor();
Visualization *display = new Visualization(ROWS,COLUMNS,ROWS_STEP,COLUMNS_STEP);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    *isEnd = false;

    Room *entr = new Entrance("Wejscie", 999, display);
	Room *corr = new Corridor("korytarz", 90, display);
	Room *cloak = new Cloakroom("szatnia", 26,display);
    Room *dziekanat = new DeanOffice("dziekanat",STAMPS_CNT*(STAMPS_CNT+1));
    Room *kibelek = new Toilet("WC",18);

    for (int i = 0; i < numberProfesors; i++)
    {
        Room * l = new Classroom("klasa" + to_string(i), 9,display, i);
        f->floorRooms.insert(f->floorRooms.end(),l);

        Lecturer * Lec = new Lecturer(isEnd,"Profesor" + std::to_string(i),f,E_Working,E_Professor,l, display);
        profesors.push_back(Lec);
    }
    
    f->floorRooms.insert(f->floorRooms.end(),entr);
    f->floorRooms.insert(f->floorRooms.end(),corr);
    f->floorRooms.insert(f->floorRooms.end(),cloak);
    f->floorRooms.insert(f->floorRooms.end(),dziekanat);
    f->floorRooms.insert(f->floorRooms.end(),kibelek);

    display->DrawDeanOffice();
    display->DrawCloakroom();
    display->DrawEnterance();
    display->DrawCorridor();
    display->DrawClassroom();
    display->DrawToilet();

    for(int i = 0;i<numberDziekanatworkers;i++)
    {
        DeanCrew *d = new DeanCrew(isEnd,i,numberDziekanatworkers,i%numberDziekanatworkers,"PaniZDziekanatu"+i,f,E_Entering,dziekanat,dziekanat,display);
        dziekanatworkers.push_back(d);
    }

    for(int i = 0;i<numberszatniaworkers;i++)
    {
        Checker *c = new Checker(isEnd,"Szatniarka" + std::to_string(i+1),f,E_Working,E_CloakroomCrew,cloak, display,i+1);
        szatniaworkers.push_back(c);
    }
    
    for(int i = 0; i < numberStudents; i++)
    {    
        Student *s = new Student(isEnd,i,"Student",f,E_Entering,E_Student,entr, display);
        students.push_back(s);
        usleep(100000);
    }
    
    ScanForExit();
    delete display;
    //Cleanup();
}

void JoinAll()
{

}

void Cleanup()
{
    delete display;
    for (Room * r : f->floorRooms)
        delete r;
    for (Person * c : szatniaworkers)
        delete c;
    for (Person * s : students)
        delete s;
    for (Person * p : profesors)
        delete p;
    for (Person * d : dziekanatworkers)
        delete d;
    delete f;
}   

void ScanForExit()
{
	char q;
	
	while(!(*isEnd))
	{
		q=getch();
		if(q=='q')
			*isEnd=true;
        sleep(0);
	}
    sleep(3);
}

