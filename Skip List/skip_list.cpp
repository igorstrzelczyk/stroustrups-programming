/*
    Skip_list Class Source file

    Revision history:

        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) July 2021

    Following code contains definitions of Skip_list Class member functions.
*/
#include "skip_list.h"

// Copy constructor
Skip_list::Skip_list(const Skip_list& sl)
    : height{sl.height}, head{(Link*)malloc(sizeof(Link) * (sl.height + 1))}, size{sl.size}
    {
        std::copy(sl.head, sl.head + (sl.height + 1), head);
    }

// Move constructor
Skip_list::Skip_list(Skip_list&& sl)
    : height{sl.height}, head{sl.head}, size{sl.size}
    {
        sl.height = 0;
        sl.head = nullptr;
        sl.size = 0;
    }

// Copy assignment
Skip_list& Skip_list::operator=(const Skip_list& sl)
{
    Link* new_head {(Link*)malloc(sizeof(Link) * (sl.height + 1))}; // Memory allocation
    std::copy(sl.head, sl.head + (sl.height + 1), new_head);        // Height of "head" is always height of list + 1
    free(head);                                                     // Memory deallocation
    head = new_head;

    height = sl.height;
    size = sl.size;

    return *this;
}

// Move assignment
Skip_list& Skip_list::operator=(Skip_list&& sl)
{
    free(head);         // Memory deallocation
    head = sl.head;
    sl.head = nullptr;

    height = sl.height;
    sl.height = 0;

    size = sl.size;
    sl.size = 0;

    return *this;
}

// Member function changing height of list by modification of "height" member, new array of Link* objects allocation
// and deallocation of memory used up until that point
void Skip_list::change_height(int change_by)
{
    if (!change_by) return; // No changes
    if (height + change_by < 0) throw std::invalid_argument("List height must be nonnegative.");

    const size_t head_height {head->get_height()},      // Current head height
                 array_size  {head_height + change_by};

    // Allocates space on heap that can hold required number of Link objects; way of bypassing
    // inability to use "new" operator with array of objects without default constructor
    Link* new_head {(Link*)malloc(sizeof(Link) * array_size)};
    if (change_by > 0) // Bigger array than previously - copies all available objects
    {
        std::copy(head, head + head_height, new_head);
        // Creates and initializes new, topmost Link objects
        for (size_t i = head_height; i < array_size; ++i)
            new_head[i] = Link {std::numeric_limits<int>::min(), array_size};
    }
    else std::copy(head, head + array_size, new_head);  // Smaller array than previously - copies until fits

    new_head->set_height(array_size);                   // Changes height of all elements in new_head

    // De-allocates memory and sets new value of head pointer
    free(head);
    head = new_head;

    height += change_by;
}

// Member function inserting specified value into the list
void Skip_list::insert(int value)
{
    if (find(value)) throw std::invalid_argument("Specified value is already in the list.");

    size_t link_height {generate_height()};                        // Generates height of new list element
    if (link_height > height) change_height(link_height - height); // Creates new "head" and changes height

    // Creates new Link object
    Link* new_link {(Link*)malloc(sizeof(Link) * link_height)};    // Memory allocation
    for (size_t i = 0; i < link_height; ++i)
        new_link[i] = Link {value, link_height};

    int level {height}; // Link level, for list traversal
    for (Link* p = &head[level]; level >=0; --level, --p)
    {
        p = p->search(value);
        if (level < new_link->get_height())
            p->add(&new_link[level]);
    }
    ++size;
}

// Member function removing specified value from the list
void Skip_list::remove(int searched_value)
{
    if (!height) throw std::runtime_error("List is empty.");

    int empty_rows {0};      // Number of rows to become empty after procedure; only top-most should be

    Link* p {&head[height]}; // Top-most element of "head"
    for (size_t level = height; level > 0; --level, --p)
    {
        // Top-most element should be empty at all times; link to be removed can also be at level 0, hence "level - 1"
        if (head[level - 1].get_next()->get_value() == searched_value && !head[level - 1].get_next()->get_next())
            ++empty_rows;    // Row will become empty after link removal if to-be-removed link is the only one on
                             // this level - both height of head and list should be decreased

        p = p->search(searched_value);
        if (p->get_next() && p->get_next()->get_value() == searched_value)
            p->remove();
    }//end for
    p = p->search(searched_value);
    if (!p->get_next() || p->get_next()->get_value() != searched_value) // Searched value could not be located
            throw std::invalid_argument("List does not contain such value.");

    // Memory deallocation
    Link* to_remove {p->get_next()};
    p->remove();
    free(to_remove);

    // Changes size of the list, as well as its height if neccessary
    --size;
    if (empty_rows) change_height(-empty_rows);
}

// Member function searching for link of specified value and returning it; returns nullptr otherwise
Link* Skip_list::find(int searched_value) const
{
    if (!size) return nullptr; // List is empty

    int level {height}; // Link level, for list traversal
    for (Link* p = &head[level]; level >= 0; --level, --p)
    {
        p = p->search(searched_value);
        if (p->get_next() && p->get_next()->get_value() == searched_value)
            return p->get_next() - level; // Link of specified value found - returns main, bottom link
    }
    return nullptr; // Searched value could not be located
}

// Member function printing list contents
void Skip_list::print() const
{
    if (!size) throw std::runtime_error("List is empty.");

    std::ostringstream oss;
    Link* p {nullptr};
    for (size_t i = height; i > 0; --i)
    {
        p = head[i - 1].get_next();                    // At least one successor must be present on penultimate level
        oss << '[' << i - 1 << "]: " << p->get_value();
        while (p = p->get_next()) oss << " > " << p->get_value();
        oss << std::endl;
    }
    std::cout << oss.str();
}
