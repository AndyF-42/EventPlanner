#include "events.h"


/* Andy Fleischer - CS202 - Program #1 - 7/16/2021
 * ---------------------------------------------- 
 * This file is for Address, Event, Gym, Restaurant,
 * and Party classes. Gym, Restaurant, and Party 
 * derive from Event, which derives from Address.
 * Each type of Event has unique data, and common
 * data between all events is pushed up. Address
 * is further pushed up to the Address class.
*/


//clean_input - gets input and clears the buffer
void clean_input(char* buffer, int size)
{
    std::cin.get(buffer, size);
    std::cin.clear();
    std::cin.ignore(1000, '\n');
}


// ======== ADDRESS ======== //


//default constructor - set all to nullptr
Address::Address() : street(nullptr), city(nullptr), state(nullptr), zip(nullptr) 
{}

//destructor - release all memory
Address::~Address()
{
    delete [] street;
    delete [] city;
    delete [] state;
    delete [] zip;
    
    street = NULL;
    city = NULL;
    state = NULL;
    zip = NULL;
}

//copy constructor - copy all char* over
Address::Address(const Address& source)
{
    street = new char[strlen(source.street) + 1];
    city = new char[strlen(source.city) + 1];
    state = new char[strlen(source.state) + 1];
    zip = new char[strlen(source.zip) + 1];

    strcpy(street, source.street);
    strcpy(city, source.city);
    strcpy(state, source.state);
    strcpy(zip, source.zip); 
}

//read - prompt user and read in input 
void Address::read()
{
    //street
    char buff[40];
    std::cout << "Street: ";
    clean_input(buff, 40);
    street = new char[strlen(buff) + 1];
    strcpy(street, buff);

    //city
    std::cout << "City: ";
    clean_input(buff, 40);
    city = new char[strlen(buff) + 1];
    strcpy(city, buff);
    
    //state
    std::cout << "State: ";
    clean_input(buff, 40);
    state = new char[strlen(buff) + 1];
    strcpy(state, buff);

    //zip
    std::cout << "Zip: ";
    clean_input(buff, 40);
    zip = new char[strlen(buff) + 1];
    strcpy(zip, buff);
}

//display - display the address as on an envelope
void Address::display() const
{
    std::cout << street << std::endl;
    std::cout << city << ", " << state << " " << zip << std::endl;
}

//cool_fact - give the user a cool fact about the location!
void Address::cool_fact() const
{
    if (strcmp(city, "Portland") == 0 && strcmp(state, "Oregon") == 0)
        std::cout << "Cool fact: the writer of this code grew up where this event is, in Portland, Oregon!" << std::endl;
    else
        std::cout << "Cool fact: the writer of the code did NOT grow up in the city this event is!" << std::endl;
}

//autofill - choose some random data for the address
void Address::autofill()
{
    switch (rand() % 4) //random street
    {
        case 0: street = new char[16];
                strcpy(street, (char*)("1234 SW Fake St"));
                break;
        case 1: street = new char[19];
                strcpy(street, (char*)("34875 NE Smiths Dr"));
                break;
        case 2: street = new char[19];
                strcpy(street, (char*)("8001 NW Hawkins Dr"));
                break;
        case 3: street = new char[18];
                strcpy(street, (char*)("4321 SE 150th Ave"));
                break;
        default: break;
    }
    
    zip = new char[6]; //zip is always 5 long (plus null terminating character)
    switch (rand() % 4) //random city with its state and a specific zip in that city
    {
        case 0: city = new char[9];
                strcpy(city, (char*)("Portland"));
                state = new char[7];
                strcpy(state, (char*)("Oregon"));
                strcpy(zip, (char*)("97229"));
                break;
        case 1: city = new char[8];
                strcpy(city, (char*)("Chicago"));
                state = new char[9];
                strcpy(state, (char*)("Illinois"));
                strcpy(zip, (char*)("60290"));
                break;
        case 2: city = new char[8];
                strcpy(city, (char*)("Seattle"));
                state = new char[11];
                strcpy(state, (char*)("Washington"));
                strcpy(zip, (char*)("98103"));
                break;
        case 3: city = new char[6];
                strcpy(city, (char*)("Salem"));
                state = new char[7];
                strcpy(state, (char*)("Oregon"));
                strcpy(zip, (char*)("97304"));
                break;
        default: break;
    }
}


// ======== EVENT ======== //


//default constructor - sets to "0" values
Event::Event() : Address()
{
    date[0] = 1;
    date[1] = 1;
    date[2] = 2022;
    start_time[0] = 0;
    start_time[1] = 0;
}

//read - prompt user and read in input
void Event::read()
{
    std::string str; //buffer

    std::cout << "Date (mm/dd/yyyy): "; //get the date
    std::getline(std::cin, str);
    //split up the date into int array
    date[0] = std::stoi(str.substr(0, 2)); 
    date[1] = std::stoi(str.substr(3, 2));
    date[2] = std::stoi(str.substr(6, 4));

    std::cout << "Time (hh:mm): "; //get the time
    std::getline(std::cin, str);
    //split up the time into int array
    start_time[0] = std::stoi(str.substr(0, 2));
    start_time[1] = std::stoi(str.substr(3, 2));
    
    //check am, pm, or military time (we store in military time)
    std::cout << "Was that (p)m, (a)m, or (m)ilitary time: ";
    char ans;
    std::cin >> ans; std::cin.clear(); std::cin.ignore(100, '\n');
    ans = tolower(ans);
    
    if (ans == 'p') //add 12 hours if it was pm
        start_time[0] += 12;
    else if (ans != 'a' && ans != 'm')
        std::cout << "Assuming military time." << std::endl;

    Address::read(); //call parent's read
}

//display - display all time data
void Event::display() const
{
    //basically just print everything out, padding single digit numbers with a 0
    if (date[0] < 10) { std::cout << "0"; }
    std::cout << date[0] << "/";
    if (date[1] < 10) { std::cout << "0"; }
    std::cout << date[1] << "/" << date[2] << std::endl;
    if (start_time[0] < 10) { std::cout << "0"; }
    std::cout << start_time[0] << ":";
    if (start_time[1] < 10) { std::cout << "0"; }
    std::cout << start_time[1] << std::endl;

    Address::display(); //call parent's display
}

//autofill - randomly generate time data
void Event::autofill()
{
    srand(time(NULL));

    //random month, date, and year
    date[0] = rand() % 12 + 1;
    date[1] = rand() % 28 + 1;
    if (date[0] <= 7)
        date[2] = 2022;
    else
        date[2] = rand() % 2 + 2021;

    //random hour, minute (multiple of 5)
    start_time[0] = rand() % 24;
    start_time[1] = (rand() % 12) * 5;

    Address::autofill(); //call parent's autofill
}


// ======== GYM ======== //


//default constructor - choose random workout
Gym::Gym() : Event()
{
    srand(time(NULL));
    std::string workouts[] = {"Legs", "Core", "Arms", "Cardio"};
    workout = workouts[rand() % 4];
    length = (rand() % 7) * 5 + 30; //30, 35,..., 55, or 60
}

//constructor - initialize all variables
Gym::Gym(const std::string& a_workout, int a_length) : Event(), workout(a_workout), length(a_length)
{}

//display - display all data
void Gym::display() const
{
    Event::display(); //call parent's display first, then my data
    std::cout << "Workout: " << workout << std::endl;
    std::cout << "Length: " << length << std::endl;
}

//is_workout - check if workout matches (useful for many CLL functions)
bool Gym::is_workout(const std::string& to_match) const
{
    return to_match == workout;
}

//get_inspired - give random inspirational quote
void Gym::get_inspired() const
{
    std::string messages[] = {"YOU GOT THIS!", "GET UP AND MOVE", "LET'S GET MOVING", "COME ON LET'S DO THIS"};
    std::cout << messages[rand() % 4] << std::endl;
}


// ======== RESTAURANT ======== //


//constructor - initialize all variables, deep copying the dynamically allocated memory
Restaurant::Restaurant(char* the_name, char* the_attire, int the_party_size) : Event(), party_size(the_party_size)
{
    name = new char[strlen(the_name) + 1];
    strcpy(name, the_name);

    attire = new char[strlen(the_attire) + 1];
    strcpy(attire, the_attire);
}

//copy constructor - deep copy all dynamically allocated char* and call parent's cc
Restaurant::Restaurant(const Restaurant& source) : Event(source)
{
    name = new char[strlen(source.name) + 1];
    strcpy(name, source.name);

    attire = new char[strlen(source.attire) + 1];
    strcpy(attire, source.attire);

    party_size = source.party_size;  
}

//destructor - release char* memory
Restaurant::~Restaurant()
{
    delete [] name;
    delete [] attire;
    name = NULL;
    attire = NULL;
}

//display - display all data
void Restaurant::display() const
{
    Event::display(); //call parent's display first
    std::cout << "Reservation for " << name << ", party of " << party_size << std::endl;
    std::cout << "Wear " << attire << " attire." << std::endl; //force all lowercase for attire?
}

//is_name - check if given name matches this restaurant (useful for data structures)
bool Restaurant::is_name(const char* to_match) const
{
    return strcmp(to_match, name) == 0;
}

//find_link - generate a (definitely legitimate) link to the restaurant's menu
void Restaurant::find_link() const
{
    std::cout << "https://www."; //simple start
    for (int i = 0; name[i] != '\0'; ++i) //don't print spaces and set to lowercase
        if (name[i] != ' ')
            std::cout << (char)tolower(name[i]);

    std::cout << ".com/menu" << std::endl; //fake ending
}


// ======== PARTY ======== //


//constructor - initialize variables
Party::Party(const std::string& the_occasion) : Event(), occasion(the_occasion)
{}

//is_occasion - check if given occasion matches this party (useful for calling other functions from main)
bool Party::is_occasion(const std::string& to_match) const
{
    return to_match == occasion;
}

//add_item - add an item to bring
void Party::add_item(const std::string& to_bring)
{
    bringing.push_back(to_bring); 
}

//remove_item - remove an item to bring
void Party::remove_item(const std::string& to_remove)
{
    //iterate through vector
    for (std::vector<std::string>::iterator it = bringing.begin(); it != bringing.end(); ++it)
    {
        if (*it == to_remove) //if it is a match, erase it
        {
            bringing.erase(it);
            std::cout << "Removed." << std::endl;
            return;
        }
    }
    std::cout << "Could not find " << to_remove << std::endl; //if we are here, no match found
}

//display - display all data
void Party::display() const
{
    Event::display(); //call parent first

    std::cout << occasion << " party" << std::endl;
    if (!bringing.empty()) //if you are bringing items, iterate through and print them
    {
        std::cout << "Make sure to bring:" << std::endl;
        for (std::vector<std::string>::const_iterator it = bringing.begin(); it != bringing.end(); ++it)
            std::cout << "  " << *it << std::endl;
    }
}
