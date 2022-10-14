#include "events.h"


/* Andy Fleischer - CS202 - Program #1 - 7/16/2021
 * ---------------------------------------------- 
 * This file is for C_Node, CLL, Node, and LLL_Array
 * classes. CLL manages C_Nodes (which derive from
 * Gyms) in the form of a circular linked list.
 * LLL_Array manages Nodes (which derive from 
 * Restaurants) as an array of linear linked lists.
*/


class C_Node : public Gym
{
    public:
        C_Node(); //constructors
        C_Node(const Gym & gym);

        C_Node *& go_next(); //getter and setter
        void set_next(C_Node* new_next);

    private:
        C_Node* next;
};

class CLL
{
    public:
        CLL(); //constructor, cc, and destructor
        CLL(const CLL& source);
        ~CLL();

        void insert(const Gym& to_add); //insert a new Gym event
        void remove(const std::string& workout); //remove a certain workout
        void display() const; //display all Gym events
        Gym* find(const std::string& workout); //find and return a certain workout

    private:
        //private recursive functions for above
        void copy(C_Node*& current, C_Node* source, C_Node* source_rear);
        void remove_all(C_Node*& current);
        bool remove(C_Node*& current, const std::string& workout);
        void display(C_Node* current) const;
        Gym* find(C_Node* current, const std::string& workout);

        C_Node* rear; //rear pointer
};

class Node : public Restaurant
{
    public:
        Node(); //constructors
        Node(const Restaurant& source);
        
        Node *& go_next(); //getter and setter
        void set_next(Node* new_next);

    private:
        Node* next;
};

class LLL_Array
{
    public:
        LLL_Array(int size=5); //constructors, cc, and destructor
        LLL_Array(const LLL_Array& source);
        ~LLL_Array();

        void insert(const Restaurant& to_add); //insert a new restaurant
        void remove(const char* restaurant_name); //remove a certain restaurant
        void display() const; //display all data
        void remove_all(); //remove all data
        Restaurant* find(const char* restaurant_name); //find and return a certain restaurant

    private:
        //private recursive functions for above
        void display(Node* current) const;
        bool remove(const char* restaurant_name, Node *& current);
        Restaurant* find(Node* current, const char* restaurant_name);
        
        Node ** head; //array of Node*
        int array_size; //size
};
