#include "nodes.h"


/* Andy Fleischer - CS202 - Program #1 - 7/16/2021
 * ---------------------------------------------- 
 * This file is for C_Node, CLL, Node, and LLL_Array
 * classes. CLL manages C_Nodes (which derive from
 * Gyms) in the form of a circular linked list.
 * LLL_Array manages Nodes (which derive from 
 * Restaurants) as an array of linear linked lists.
*/


// ======== C_NODE ======== //
// simple constuctor w/ default, getter, and setter


C_Node::C_Node()
{
    next = NULL;
}

C_Node::C_Node(const Gym & gym) : Gym(gym)
{
    next = NULL; 
}

C_Node *& C_Node::go_next()
{
    return next;
}

void C_Node::set_next(C_Node* new_next)
{
    next = new_next;
}


// ======== CLL ======== //


//default constructor, set rear to null
CLL::CLL()
{
    rear = NULL;
}

//copy constructor - call recursive copy
CLL::CLL(const CLL& source)
{
    copy(rear, source.rear, source.rear);
}

//private recursive copy - go through and copy data
void CLL::copy(C_Node*& current, C_Node* source, C_Node* source_rear)
{
    current = new C_Node(*source); //copy node

    if (source->go_next() == source_rear) //if at rear, link up the circle
    {
        current->set_next(rear);
        return;
    }

    copy(current->go_next(), source->go_next(), source_rear); //next step
}

//destructor - call recursive remove_all
CLL::~CLL()
{
    if (rear)
        remove_all(rear->go_next());
}

//private recursive remove_all - delete all data
void CLL::remove_all(C_Node*& current)
{
    if (current == rear) //for final node, delete and reset rear to NULL
    {
        delete current;
        rear = NULL; 
        return;
    }

    C_Node* temp = current->go_next(); //store temp, delete, move on
    delete current;
    current = temp;
    remove_all(current);
}

//insert - always insert at rear->next, no need to traverse or recurse
void CLL::insert(const Gym& to_add)
{
    C_Node* new_node = new C_Node(to_add); //make the node

    if (!rear) //if first node, set it up
    {
        rear = new_node;
        rear->set_next(rear);
        return;
    }

    C_Node* temp = rear->go_next(); //store the next and insert
    rear->set_next(new_node);
    new_node->set_next(temp); 
}

//remove - remove the node with a given workout
void CLL::remove(const std::string& workout)
{
    if (remove(rear->go_next(), workout)) //found
        std::cout << "Removed." << std::endl;
    else //did not find
        std::cout << "Could not find that workout." << std::endl;
}

//private recursive remove - check for a match and if so, hook up connections
bool CLL::remove(C_Node *& current, const std::string& workout)
{
    if (current->is_workout(workout)) //found match
    {
        if (current->go_next() == current) //check if only one data to reset rear to NULL
        {
            delete current;
            rear = NULL;
            return true;
        }

        bool is_rear = (current == rear); //if deleting the rear, special case
        C_Node* temp = current->go_next();
        delete current;
        current = temp;
        if (is_rear)
            rear = current;
        return true;
    }

    if (current == rear) //made it through and no match. return false
        return false;

    return remove(current->go_next(), workout); //recurse
}

//display - display every node's data
void CLL::display() const
{
    if (!rear) //special cout if no data
    {
        std::cout << "No gym events.\n" << std::endl;
        return;
    }
    display(rear->go_next()); 
}

//private recursive display - recurse through, display current node's data
void CLL::display(C_Node* current) const
{
    current->display(); //display and give space
    std::cout << std::endl;
    
    if (current == rear) //we are done
        return;

    display(current->go_next()); //recurse
}

//find - return a pointer to the matching workout HEY ANDY CHECK FOR CONST
Gym* CLL::find(const std::string& workout)
{
    if (!rear)
        return NULL;
    return find(rear->go_next(), workout);
}

//find
Gym* CLL::find(C_Node* current, const std::string& workout)
{
    if (current->is_workout(workout))
        return current;

    if (current == rear)
        return NULL;     

    return find(current->go_next(), workout);
}


// ======== NODE ======== //
// simple constuctor w/ default, getter, and setter


Node::Node()
{
    next = NULL;
}

Node::Node(const Restaurant& source) : Restaurant(source)
{
    next = NULL;
}

Node *& Node::go_next()
{
    return next; 
}

void Node::set_next(Node* new_next)
{
    next = new_next;
}


// ======== LLL_ARRAY ======== //


//Constructor and default constructor - initialize the array
LLL_Array::LLL_Array(int size)
{
    array_size = size;
    head = new Node*[array_size];
    for (int i = 0; i < array_size; ++i)
        head[i] = NULL;    
}

//copy constructor
LLL_Array::LLL_Array(const LLL_Array& source)
{
    array_size = source.array_size;
    head = new Node*[array_size];
    for (int i = 0; i < array_size; ++i)
    {
        Node* current = head[i];
        Node* src = source.head[i];

        while (src)
        {
            current = new Node(*src);
            current = current->go_next();
            src = src->go_next();
        }
    }
}

//destructor
LLL_Array::~LLL_Array()
{
    remove_all();
}

//insert - insert at head of random index
void LLL_Array::insert(const Restaurant& to_add)
{
    srand(time(NULL));
    int index = rand() % array_size; //get random index

    Node* new_node = new Node(to_add); //insert at head
    new_node->set_next(head[index]);
    head[index] = new_node;
}

//search through all the array to remove
void LLL_Array::remove(const char* restaurant_name)
{
    for (int i = 0; i < array_size; ++i)
    {
        if (remove(restaurant_name, head[i]))
        {
            std::cout << "Removed." << std::endl;
            return; 
        }
    }
    std::cout << "Could not find that restaurant." << std::endl;
}

//recursive search
bool LLL_Array::remove(const char* restaurant_name, Node *& current)
{
    if (!current)
        return false;
    
    if (current->is_name(restaurant_name))
    {
        Node *& temp = current->go_next();
        delete current;
        current = temp;
        return true;
    }
    return remove(restaurant_name, current->go_next());
}

//display all data
void LLL_Array::display() const
{
    bool has_restaurant = false;
    for (int i = 0; i < array_size; ++i)
    {
        if (head[i])
        {
            has_restaurant = true;
            display(head[i]);
        }
    }

    if (!has_restaurant)
        std::cout << "No restaurant events.\n" << std::endl; 
}

//recursive private display
void LLL_Array::display(Node* current) const
{
    if (!current)
        return;

    current->display();
    std::cout << std::endl;
    display(current->go_next());
}

//remove all data
void LLL_Array::remove_all()
{
    for (int i = 0; i < array_size; ++i)
    {
        Node* current = head[i];

        while (current)
        {
            Node* temp = current->go_next();
            delete current;
            current = temp;
        }
    }
}

//find specific restaurant
Restaurant* LLL_Array::find(const char* restaurant_name)
{
    for (int i = 0; i < array_size; ++i)
    {
        Restaurant* found = find(head[i], restaurant_name);
        if (found)
            return found;
    }
    return NULL;
}

//recursive find
Restaurant* LLL_Array::find(Node* current, const char* restaurant_name)
{
    if (!current)
        return NULL;

    if (current->is_name(restaurant_name))
        return current;

    return find(current->go_next(), restaurant_name);
}
