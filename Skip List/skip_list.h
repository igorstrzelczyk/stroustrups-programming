/*
    Skip_list Class Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Skip_list Class.
*/
#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include "functions.h"
#include "link.h"
#include <iostream> // cout
#include <limits>   // numeric_limits<T>
#include <sstream>  // ostringstream

class Skip_list {
public:
    // Essential operations
    Skip_list() { *head = Link {std::numeric_limits<int>::min()}; } // Default constructor
    Skip_list(std::initializer_list<int> lst) : Skip_list()         // Parameterized constructor
        { for (const int& val : lst) insert(val); }
    Skip_list(const Skip_list&);                                    // Copy constructor
    Skip_list(Skip_list&&);                                         // Move constructor
    ~Skip_list() { free(head); }                                    // Destructor
    Skip_list& operator=(const Skip_list&);                         // Copy assignment
    Skip_list& operator=(Skip_list&&);                              // Move assignment

    // Modifying functions
    void insert(int);           // Adds element of specified value to the list
    void remove(int);           // Removes element of specified value from the list

    // Non-modifying functions
    Link*  find(int)    const;  // Seeks specified value and returns pointer to its link; otherwise returns nullptr
    void   print()      const;  // Prints contents of the list
    size_t get_height() const { return height; }
    Link*  get_head()   const { return head; }
    size_t get_size()   const { return size; }
private:
    void   change_height(int);  // In- or decreases height of the list, deallocates memory pointed by "head" member,
                                // appropriately allocates new and modifies "size" member
    size_t height {0};                           // List height; index of last element in "head"
    Link*  head   {(Link*)malloc(sizeof(Link))}; // Default, first-most link representing -infinity
    size_t size   {0};                           // List size; number of elements
};

#endif // SKIP_LIST_H
