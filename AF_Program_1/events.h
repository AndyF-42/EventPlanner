#include <iostream>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <time.h>


/* Andy Fleischer - CS202 - Program #1 - 7/16/2021
 * ---------------------------------------------- 
 * This file is for Address, Event, Gym, Restaurant,
 * and Party classes. Gym, Restaurant, and Party 
 * derive from Event, which derives from Address.
 * Each type of Event has unique data, and common
 * data between all events is pushed up. Address
 * is further pushed up to the Address class.
*/


void clean_input(char* buffer, int size); //global function for getting char* input and clearing the buffer


class Address
{
    public:
        Address(); //constructor
        Address(const Address& source); //copy constructor
        ~Address(); //destructor

        void read(); //prompt and read input
        void display() const; //display data
        void cool_fact() const; //display cool fact about address
        void autofill(); //autofill random address data

    private:
        char* street;
        char* city;
        char* state;
        char* zip;
};


class Event : public Address
{
    public:
        Event(); //constructor
        
        void read(); //prompt and read input
        void display() const; //display data
        void autofill(); //autofill random date/time data

    private:
        int date[3]; //stored MM/DD/YYYY
        int start_time[2]; //stored in military time
};


class Gym : public Event
{
    public:
        Gym(); //default constructor with random workout and length
        Gym(const std::string& a_workout, int a_length); //constructor

        void display() const; //display all data
        bool is_workout(const std::string& to_match) const; //check if given workout matches this one
        void get_inspired() const; //display inspirational quote

    private:
        std::string workout;
        int length;
};


class Restaurant : public Event
{
    public:
        Restaurant(char* the_name = NULL, char* the_attire = NULL, int the_party_size = 0); //constructor
        Restaurant(const Restaurant& source); //copy constructor
        ~Restaurant(); //destructor

        void display() const; //display all data
        bool is_name(const char* to_match) const; //check if given name matches this restaurant
        void find_link() const; //display link to restaurant's menu

    private:
        char* name;
        char* attire;
        int party_size;
};


class Party : public Event
{
    public:
        Party(const std::string& the_occasion = "For fun"); //constructor

        bool is_occasion(const std::string& to_match) const; //check if given occasion matches this party
        void add_item(const std::string& to_bring); //add an item to bring
        void remove_item(const std::string& to_remove); //remove an item to bring
        void display() const; //display all data
    
    private:
        std::string occasion;
        std::vector<std::string> bringing;
};
