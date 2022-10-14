#include "nodes.h"
#include <vector>
#include <iterator>


/* Andy Fleischer - CS202 - Program #1 - 7/16/2021
 * ---------------------------------------------- 
 * This main is a sample app to test out all the
 * functionalities of the event planner. It creates
 * the CLL of gyms, LLL_Array of restaurants, and
 * std::vector of parties, which are passed around 
 * between various menus for the different functions.
*/


//Menu constants
#define MAIN_MENU 1
#define GYM_MENU 2
#define RESTAURANT_MENU 3
#define PARTY_MENU 4

//Find event constants
#define REMOVE 0
#define FACT 1
#define INSPIRE 2
#define LINK 2
#define ADD_ITEM 2
#define REMOVE_ITEM 3

using namespace std;

//universal functions
void help(int menu);
void view_all(CLL&, LLL_Array&, vector<Party>&);
void ask_autofill(Event&);

//gym functions
void gym(CLL& my_gyms);
void add_gym(CLL& my_gyms);
void find_gym(CLL& my_gyms, int);

//restaurant functions
void restaurant(LLL_Array&);
void add_restaurant(LLL_Array&);
void find_restaurant(LLL_Array&, int);

//party functions
void party(vector<Party>&);
void add_party(vector<Party>&);
void find_party(vector<Party>&, int);
void add_item(vector<Party>::iterator&);
void remove_item(vector<Party>::iterator&);
void display_parties(vector<Party>&);


int main()
{
    cout << "-------------------" << endl;
    cout << "   Event Planner   " << endl;
    cout << "-------------------" << endl;

    CLL my_gyms;
    LLL_Array my_restaurants;
    vector<Party> my_parties;

    //main menu loop
    char input;
    do
    {
        help(MAIN_MENU);
        cout << ">> ";
        cin >> input;

        //check which input
        switch (input)
        {
            case '0': break;
            case '1': gym(my_gyms); break;
            case '2': restaurant(my_restaurants); break;
            case '3': party(my_parties); break;
            case '4': view_all(my_gyms, my_restaurants, my_parties); break;
            default:  cout << "Invalid command." << endl;
        }

    }
    while (input != '0');

    return 0;
}


// ======== UNIVERSAL FUNCTIONS ======== //


//help - prints out a certain menu depending on what constant is passed in
void help(int menu)
{
    switch (menu)
    {
        case MAIN_MENU:
            cout << endl;
            cout << "-------MENU--------" << endl;
            cout << "0 - Quit" << endl;
            cout << "1 - Gym" << endl;
            cout << "2 - Restaurant" << endl;
            cout << "3 - Party" << endl;
            cout << "4 - View all events" << endl;
            cout << "-------------------" << endl;
            cout << endl;
            break;
        case GYM_MENU:
            cout << endl;
            cout << "--------GYM--------" << endl;
            cout << "0 - Back" << endl;
            cout << "1 - Create" << endl;
            cout << "2 - Remove" << endl;
            cout << "3 - Cool fact" << endl;
            cout << "4 - Get inspired!" << endl;
            cout << "5 - Display" << endl;
            cout << "-------------------" << endl;
            cout << endl;
            break;
        case RESTAURANT_MENU:
            cout << endl;
            cout << "----RESTAURANT-----" << endl;
            cout << "0 - Back" << endl;
            cout << "1 - Create" << endl;
            cout << "2 - Remove" << endl;
            cout << "3 - Cool fact" << endl;
            cout << "4 - Get online menu" << endl;
            cout << "5 - Display" << endl;
            cout << "-------------------" << endl;
            cout << endl;
            break;
        case PARTY_MENU:
            cout << endl;
            cout << "-------PARTY-------" << endl;
            cout << "0 - Back" << endl;
            cout << "1 - Create" << endl;
            cout << "2 - Remove" << endl;
            cout << "3 - Cool fact" << endl;
            cout << "4 - Add item to bring" << endl;
            cout << "5 - Remove item to bring" << endl;
            cout << "6 - Display" << endl;
            cout << "-------------------" << endl;
            cout << endl;
            break;
        default:
            break;
    }
}

//view_all - call the display functions for all events
void view_all(CLL& my_gyms, LLL_Array& my_restaurants, vector<Party>& my_parties)
{
    cout << "=== GYM EVENTS ===" << endl;
    my_gyms.display();
    cout << "=== RESTAURANT EVENTS ===" << endl;
    my_restaurants.display(); 
    cout << "=== PARTY EVENTS ===" << endl;
    display_parties(my_parties);
}

//ask_autofill - autofill location and time data upon request, or have the user manually input them
void ask_autofill(Event& event)
{
    char ans;
    cout << "Autofill location and time? (y/n) ";
    cin >> ans;
    cin.clear();
    cin.ignore(1000, '\n');

    if (toupper(ans) == 'Y') //if yes, autofill, otherwise read
    {
        event.autofill();
        return;
    }
    event.read();
}


// ======== GYM WRAPPERS ======== //


//gym - menu and input for gym
void gym(CLL& my_gyms)
{
    char input;
    do
    {
        //display gym menu and get input
        help(GYM_MENU);
        cout << ">> ";
        cin >> input;

        //check input
        switch (input)
        {
            case '0': break;
            case '1': add_gym(my_gyms); break;
            case '2': find_gym(my_gyms, REMOVE); break;
            case '3': find_gym(my_gyms, FACT); break;
            case '4': find_gym(my_gyms, INSPIRE); break;
            case '5': my_gyms.display(); break;
            default:  cout << "Invalid command." << endl;
        }

    }
    while (input != '0');
}

//add_gym - add a gym event to the CLL
void add_gym(CLL& my_gyms)
{
    //get the data
    string workout;
    cout << "Workout: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, workout);

    int length;
    cout << "Length: ";
    cin >> length;
    cin.clear();
    cin.ignore(1000, '\n');

    //create the gym, ask for autofill, then insert
    Gym new_gym(workout, length);
    ask_autofill(new_gym);    

    my_gyms.insert(new_gym);
}

//find_gym - wrapper for any function on a specific gym, given the constant int operation to perform
void find_gym(CLL& my_gyms, int operation)
{
    //input the data
    string workout;
    cout << "Workout: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, workout);

    if (operation == REMOVE) //removing
    {
        my_gyms.remove(workout);
        return;
    }

    Gym* found = my_gyms.find(workout);
    if (!found) //did not find a match
    {
        cout << "Could not find that workout" << endl;
        return;
    }

    switch (operation) //call the proper function
    {
        case FACT: found->cool_fact(); break;
        case INSPIRE: found->get_inspired(); break;
    }
}


// ======== RESTAURANT WRAPPERS ======== //


//restaurant - menu and input for restaurants
void restaurant(LLL_Array& my_restaurants)
{

    char input;
    do
    {
        //print menu and get input
        help(RESTAURANT_MENU);
        cout << ">> ";
        cin >> input;

        switch (input) //call the proper function
        {
            case '0': break;
            case '1': add_restaurant(my_restaurants); break;
            case '2': find_restaurant(my_restaurants, REMOVE); break;
            case '3': find_restaurant(my_restaurants, FACT); break;
            case '4': find_restaurant(my_restaurants, LINK); break;
            case '5': my_restaurants.display(); break;
            default:  cout << "Invalid command." << endl;
        }

    }
    while (input != '0');
}

//add_restaurant - add a restaurant to the array of LLL
void add_restaurant(LLL_Array& my_restaurants)
{
    //get input
    char name[30];
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Restaurant name: ";
    clean_input(name, 30);
    
    char attire[20];
    cout << "Attire: ";
    clean_input(attire, 20);

    int party_size;
    cout << "Party Size: ";
    cin >> party_size;
    cin.clear();
    cin.ignore(1000, '\n');

    //create, fill data, insert
    Restaurant new_restaurant(name, attire, party_size);
    ask_autofill(new_restaurant);    

    my_restaurants.insert(new_restaurant);
}

//find_restaurant - wrapper for any functions on a specific restaurant (determined by operation constant)
void find_restaurant(LLL_Array& my_restaurants, int operation)
{
    //get the name
    char name[30];
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Restaurant name: ";
    clean_input(name, 30);
    
    if (operation == REMOVE) //is it removing?
    {
        my_restaurants.remove(name);
        return;
    }

    Restaurant* found = my_restaurants.find(name); //find it
    if (!found)
    {
        cout << "Could not find that restaurant" << endl;
        return;
    }

    switch (operation) //call the proper function
    {
        case FACT: found->cool_fact(); break;
        case LINK: found->find_link(); break;
    }
}


// ======== PARTY WRAPPERS ======== //


//party - menu and input for party
void party(vector<Party>& my_parties)
{
    char input;
    do
    {
        //print menu and get input
        help(PARTY_MENU);
        cout << ">> ";
        cin >> input;

        switch (input) //call the proper function
        {
            case '0': break;
            case '1': add_party(my_parties); break;
            case '2': find_party(my_parties, REMOVE); break;
            case '3': find_party(my_parties, FACT); break;
            case '4': find_party(my_parties, ADD_ITEM); break;
            case '5': find_party(my_parties, REMOVE_ITEM); break;
            case '6': display_parties(my_parties); break;
            default:  cout << "Invalid command." << endl;
        }

    }
    while (input != '0');
}

//add_party - add a party to the vector
void add_party(vector<Party>& my_parties)
{
    //get input
    string occasion;
    cout << "Occasion: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, occasion);

    //create, fill, and insert
    Party new_party(occasion);
    ask_autofill(new_party);

    my_parties.push_back(new_party);   
}

//find_party - wrapper for any functions on a certain party, given the constant int operation
void find_party(vector<Party>& my_parties, int operation)
{
    //get the occasion
    string occasion;
    cout << "Occasion: ";
    cin.clear();
    cin.ignore(1000, '\n');
    getline(cin, occasion);

    //search the vector for the party
    for (vector<Party>::iterator it = my_parties.begin(); it < my_parties.end(); ++it)
    {
        if (it->is_occasion(occasion)) //match found
        {
            switch (operation) //call the right operation
            {
                case REMOVE: my_parties.erase(it); break;
                case FACT: it->cool_fact(); break;
                case ADD_ITEM: add_item(it); break;
                case REMOVE_ITEM: remove_item(it); break;
            }
            return;
        }
    }
    cout << "Could not find that party" << endl; //if we're here, we didn't find it
}

//add_item - add an item to bring to the party
void add_item(vector<Party>::iterator& my_party)
{
    string to_add;
    cout << "Add item: ";
    getline(cin, to_add);
    my_party->add_item(to_add);
}

//remove_item - remove an item to bring to the party
void remove_item(vector<Party>::iterator& my_party)
{
    string to_remove;
    cout << "Remove item: ";
    getline(cin, to_remove);
    my_party->remove_item(to_remove);
}

//display_parties - loop through and display all party events
void display_parties(vector<Party>& my_parties)
{
    if (my_parties.empty()) //empty vector
    {
        cout << "No party events.\n" << endl;
        return;
    }

    //iterate through, displaying all
    for (vector<Party>::iterator it = my_parties.begin(); it < my_parties.end(); ++it)
    {
        it->display();
        cout << endl;
    }
}
