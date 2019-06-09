#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>

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

using namespace std;

std::vector<Person*> students;
std::vector<Person*> profesors;
//std::vector<DeanCrew*> dziekanatworkers;
//std::vector<thread*> thread_tab;
DeanCrew **dziekanatworkers = new DeanCrew*[STAMPS_CNT];
thread **thread_tab = new thread*[STAMPS_CNT];
int numberStudents;
int numberProfesors;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // Room *strg = new Room("skladzik", 2, E_Storage);
    // Room *wc = new Toilet("kibelek", 2);
    // Room *classroom = new Classroom("salka",30);
    Visualization *display = new Visualization(ROWS,COLUMNS,ROWS_STEP,COLUMNS_STEP);
    Floor *f = new Floor();
    Room *entr = new Entrance("Wejscie", 50);
	Room *corr = new Corridor("korytarz", 100);
    Room *dziekanat = new DeanOffice("dziekanat",STAMPS_CNT*2);
    display->DrawDeanOffice();

    for(int i = 0;i<STAMPS_CNT;i++)
    {
        dziekanatworkers[i] = new DeanCrew(i,STAMPS_CNT,i%STAMPS_CNT,"PaniZDziekanatu"+i,f,E_Entering,dziekanat,dziekanat,display);
 //       cout<<"stworzono pania z dziekanatu "<<i<<endl;
        //dziekanatworkers.push_back(pzd);
//        thread_tab[i] = new thread(*dziekanatworkers[i]);
        //thread_tab.push_back(thd);
    }
    
    for(int i = 0; i < STAMPS_CNT; i++)
    {
        Student *s = new Student(1,"Student",f,E_Entering,E_Student,dziekanat, display);
        students.push_back(s);
    }

    //int a;
    //cin>>a;
    
    while(1){};

    // if(argc == 3)
    // {
    //     numberStudents = atoi(argv[1]);
    //     numberProfesors = atoi(argv[2]);

    //     if(numberStudents <= 0 || numberProfesors <= 0)
    //     {
    //         std::cout << "Wprowadzane liczby muszą być większe od zera!\n";
    //         return -1;
    //     }
    //     if(5 > numberStudents || numberStudents > 30 || 5 > numberProfesors || numberProfesors > 10)
    //     {
    //         std::cout << "Wprowadzane liczby muszą być większe niż 5 i nie większe niż 10.\n";
    //         return -2;
    //     }
    // }
    // else
    // {
    //     std::cout << "Podałeś złą liczbę dnaych. Wprowadź: ilość_studentów ilość_profesorów.\n";
    //     return 0;
    // }



    // f->floorRooms.insert(strg);    
    // f->floorRooms.insert(wc);    
    //f->floorRooms.insert(corr);    
    //f->floorRooms.insert(entr);    
    // f->floorRooms.insert(classroom);    
    //f->floorRooms.insert(dziekanat);    


	// for(int i = 0; i < numberStudents; i++)
    // {
    //     Student *s = new Student("Student" + std::to_string(i),f,E_Entering,E_Student,entr);
    //     students.push_back(s);
    // }
    // for(int i = 0; i < numberProfesors; i++)
    // {
    //     Person *p = new Person("Profesor" + std::to_string(i),f,E_Entering,E_Professor,entr);
    //     profesors.push_back(p);
	// }

    // entr->Print();
    // Room *room = corr;
    // for(int i=0; i<students.size(); i++)    // go to corridor
    // {
    //     students[i]->travel(room);
    // }
    // for(int i=0; i<profesors.size(); i++)
    // {
    //     profesors[i]->travel(room);
    // }

    // entr->Print();
    // corr->Print();
    // for(int i=0; i<students.size(); i++)
    // {
    //     if(i<4)
    //         room = wc;
    //     else if(i > 10)
    //         room = classroom;
    //     else
    //         room = dziekanat;
        
    //     students[i]->travel(room);
    // }
    // corr->Print();
    // wc->Print();
    // classroom->Print();
    // dziekanat->Print();
    // room = classroom;
    // for(int i=0; i<profesors.size(); i++)
    // {
    //     profesors[i]->travel(room);
    // }
    // corr->Print();
    // classroom->Print();

    // std::cout<< "start koniec";
    // for(auto s : students)
    // {
    //     s->t.join();
    // }

    // for(auto p : profesors)
    // {
    //     p->t.join();
    // }

    // std::cout<< "koniec koniec";
    // endwin();
    // for(int i=0; i<students.size(); i++) 
    // {
    //     delete students[i];
    // }
    // for(int i=0; i<profesors.size(); i++)
    // {
    //     delete profesors[i];
    // }   
}


// int main(int argc, char *argv[])// liczba filozofów, liczba powtórzeń sekwencji jedzenie-filozofowanie, minimalny czas, maksymalny czas [ms]
// {
// 	int Philosophers_cnt = 5,
// 		Philosopher_it = 5,
// 		Time_min = 2500,
// 		Time_max = 3500;

// 	if(argc>1)
// 	{
// 		if(atoi(argv[1])>2)
// 			Philosophers_cnt = atoi(argv[1]);
// 		if(argc>2)
// 		{
// 			if(atoi(argv[2])>=0)
// 				Philosopher_it = atoi(argv[2]);
// 			if(argc>3)
// 			{
// 				if(atoi(argv[3])>0)
// 					Time_min = atoi(argv[3]);
// 				if(argc>4)
// 				{
// 					if(argv[4]>0)
// 						Time_max = atoi(argv[4]);
// 					if(atoi(argv[4])<Time_min)
// 						swap(Time_max,Time_min);
// 				}
// 			}
// 		}
// 	}

// 	cout<<Philosophers_cnt<<endl
// 		<<Philosopher_it<<endl
// 		<<Time_min<<endl
// 		<<Time_max<<endl;

// 	Application *app = new Application(Philosophers_cnt, Philosopher_it, Time_min,Time_max);
	
// 	app->ScanForExit();

// 	app->joinAll();
// 	delete app;
// 	return 0;
// }
