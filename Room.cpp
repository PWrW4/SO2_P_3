#include <vector>
#include <iostream>
#include <algorithm>
#include "Room.hpp"

using namespace std;

    Room::Room(std::string name, int capacity, RoomType type, vector <Person*> people)
    {
        this->name = name;
        this->capacity = capacity;
        this->type = type;
        this->people = people;
    }
	Room::Room(std::string name, int capacity, RoomType type)
    {
        this->name = name;
        this->capacity = capacity;
        this->type = type;
    }
    Room::Room(int capacity, RoomType type)
    {
        this->name = "room";
        this->capacity = capacity;
        this->type = type;
    }
    Room::Room() {}
	Room::~Room() {}

    int Room::addPerson(Person * person)
    {
        if(people.size()==capacity)
        {
            cout<<"brak miejsc w "<<name<<"!\n";
            return -1;
        }
        people.push_back(person);
        return 0;
    }

	int Room::delPerson(Person * person)
    {
        if(people.size()==0)
        {
            cout<<"nikogo nie ma w "<<name<<"!\n";
            return -1;
        }
        vector<Person*>::iterator it = find(people.begin(), people.end(),person);
        if(it == people.end() && people.back() != person)
        {
            cout<<"osoba nieobecna w "<<name<<"!\n";
            return -1;
        }
        people.erase(it);
        return 0;
    }

    void Room::Print()
    {
        cout<<name<<", "<<type<<", "<<capacity<<endl;
        PrintPeople();
    }
    
    void Room::PrintPeople()
    {
        cout<<"list of people in "<<name<<":\n";
        for(int i=0; i<people.size();i++)
        {
            cout<<people[i]->name<<endl;
        }
    }