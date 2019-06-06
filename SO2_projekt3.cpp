#include <cstdlib>
#include <iostream>
#include <mutex>
#include "Person.hpp"
#include "Room.hpp"


using namespace std;

std::vector<Person*> students;
std::vector<Person*> profesors;
int numberStudents;
int numberProfesors;

int main(int argc, char *argv[])
{
    srand(time(NULL));

    if(argc == 3)
    {
        numberStudents = atoi(argv[1]);
        numberProfesors = atoi(argv[2]);

        if(numberStudents <= 0 || numberProfesors <= 0)
        {
            std::cout << "Wprowadzane liczby muszą być większe od zera!\n";
            return -1;
        }
        if(5 > numberStudents || numberStudents > 30 || 5 > numberProfesors || numberProfesors > 10)
        {
            std::cout << "Wprowadzane liczby muszą być większe niż 5 i nie większe niż 10.\n";
            return -2;
        }
    }
    else
    {
        std::cout << "Podałeś złą liczbę dnaych. Wprowadź: ilość_studentów ilość_profesorów.\n";
        return 0;
    }

    Room *wc = new Room("kibelek", 2, Toilet);
	Room *corr = new Room("korytarz", 10, Corridor);
	Person *st1 = new Person("Student",Waiting,Student,corr);
	Person *st2 = new Person("Profesor",Waiting,Professor,corr);
	Person *st3 = new Person("KierownikDziekanatu",Waiting,DziekanatCrew,corr);

	for(int i = 0; i < numberStudents; i++)
    {
        Person *s = new Person("Student" + std::to_string(i),Enterance,Student,corr);
        students.push_back(s);
    }
    for(int i = 0; i < numberProfesors; i++)
    {
        Person *p = new Person("Profesor" + std::to_string(i),Enterance,Professor,corr);
        profesors.push_back(p);
	}



	wc->Print();
	corr->Print();
	cout<<endl;

	st1->travel(wc);
	wc->Print();
	corr->Print();
	cout<<endl;

	st2->travel(wc);
	wc->Print();
	corr->Print();
	cout<<endl;

	st3->travel(wc);
	wc->Print();
	corr->Print();
	cout<<endl;

	st1->travel(corr);
	wc->Print();
	corr->Print();
	cout<<endl;

	delete st1,st2,st3,wc,corr;
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
