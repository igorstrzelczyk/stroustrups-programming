/*
    Link Class Header file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definition of Link Class.
*/
#ifndef LINK_H
#define LINK_H

#include <cstddef>   // size_t
#include <stdexcept> // STL exceptions

class Link {
public:
    Link(int link_value, size_t link_height = 1, Link* successor = nullptr)
        : value{link_value}, height{link_height}, next{successor}
        {
            if (!link_height) height = 1;
        }

    // Modifying functions
    Link* add(Link*);            // Adds new list element after the caller
    Link* remove();              // Removes next element and returns its successor; otherwise returns caller
    void  set_height(long long); // Modifies height of link

    // Non-modifying functions
    Link*  search(int)  const;   // Traverses list, stopping at the predecessor to the link of specified value
                                 // or at the last link of the level
    int    get_value()  const { return value; }
    size_t get_height() const { return height; }
    Link*  get_next()   const { return next; }
private:
    int    value;                // Link value
    size_t height;               // Number of "levels" of link; size of allocated array
    Link*  next;                 // Next link
};

// Member function setting new value as height of the link
inline // Inline member functions are to be defined in header files
void Link::set_height(long long new_value)
{
    if (new_value < 1) throw std::invalid_argument("Passed value must be positive.");

    for (size_t i = 0; i < new_value; ++i)
        this[i].height = new_value;
}

#endif // LINK_H
