/*
    Link Class Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of Link Class member functions.
*/
#include "link.h"

// Member function adding new link by setting its successor as successor of the caller and changing "next" of
// the caller to new link; returns new link
Link* Link::add(Link* new_link)
{
    // Checks for null pointers
    if (new_link == nullptr) return this;
    if (this == nullptr) return new_link;

    new_link->next = next;
    next = new_link;
    return new_link;
}

// Member function removing next link by changing "next" of the caller to "next" of its successor while setting "next"
// of successor to nullptr; returns new successor of the caller if present, otherwise returns caller
Link* Link::remove()
{
    // Checks for null pointers
    if (this == nullptr) return nullptr;
    if (!next) return this;

    Link* successor {next};
    next = successor->next;
    successor->next = nullptr;

    if (next) return next;
    return this;
}

// Member function searching for link of passed value and returning pointer to its predecessor, in order to proceed
// accordingly
Link* Link::search(int searched_value) const
{
    if (this == nullptr) return nullptr;

    Link* p {const_cast<Link*>(this)};
    while (p->next && p->next->value < searched_value)
        p = p->next;
    return p;
}
