/*
    Skip List implementation

    Revision history:

        Revised by Igor Strzelczyk; 19/07/2021 - Minor code cleanup and division among several translation units
        Revised by Igor Strzelczyk; 16/07/2021 - Skip_list modified to always allocate new Link objects with malloc(),
                                                 in order to deallocate memory with free()
        Originally written by Igor Strzelczyk
            (igor.strzelczyk@icloud.com) June 2021

    Following code is a proposed solution to exercise 11 of chapter 18 from
    Bjarne Stroustrup's "Programming -- Principles and Practice Using C++".

    It contains Skip List implementation utilising two user-defined datatypes:
    Link        - node in the skip list; consists of value, height and a pointer to the next Link in the list
    Skip_list   - the data structure itself; consists of height, size and "head" - pointer to Link object allocated
                  on heap, which is the default, first element of the list. It is the smallest possible value of
                  integer type, represents minus infinity and is not being taken into account during size/height
                  calculation or printing of the list

    The list supports insertion, deletion and searching of specified value, as well as printing its contents.

    Skip_list object is created empty by default and might be populated with insert() or initialised immediately
    with initialiser list of integer type values.
*/

#include "skip_list.h"
#include <cstdlib>   // srand()
#include <ctime>     // time()
#include <iostream>
#include <stdexcept> // STL exceptions

int main()
{
    srand(time(nullptr)); // Seeds rand()

    try
    {
        // Sample usage
        std::cout << "Creating Skip_list object sl using default constructor...\n";
        Skip_list sl;

        std::cout << "sl.insert(3)\n";
        sl.insert(3);
        sl.print();

        std::cout << "sl.insert(2)\n";
        sl.insert(2);
        sl.print();

        std::cout << "sl.insert(4)\n";
        sl.insert(4);
        sl.print();

        std::cout << "sl.remove(2)\n";
        sl.remove(2);
        sl.print();

        std::cout << "sl.remove(3)\n";
        sl.remove(3);
        sl.print();

        std::cout << "sl.remove(4)\n";
        sl.remove(4); // Last element removed; printing results in exception being thrown
        if (!sl.get_size()) std::cout << "The list is empty!" << std::endl;
        else sl.print();

        std::cout << "Creating Skip_list object skip2 using initializer list...\n";
        Skip_list skip2 {4, 5, 7, 1, 0, 33, 12};
        skip2.print();

        return 0;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Something went wrong." << std::endl;
        return 2;
    }
}
