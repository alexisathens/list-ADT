//
//  List.h
//  Project1_SSLL
//
//  Created by Alexis Athens on 9/12/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef List_h
#define List_h
#include <cstdlib>
#include <iostream>

using namespace std;

namespace cop3530
{
    template <typename E>
    class List
    {
    public:
        virtual void insert(E element, size_t position) = 0;
        virtual void push_back(E element) = 0;
        virtual void push_front(E element) = 0;
        virtual E replace(E element, size_t position) = 0; //returns original element
        virtual E remove(size_t position) = 0; //returns removed item, shifts subsequent elts left
        virtual E pop_back(void) = 0;
        virtual E pop_front(void) = 0;
        virtual E item_at(size_t position) = 0;
        virtual E peek_back(void) = 0;
        virtual E peek_front(void) = 0;
        virtual bool is_empty(void) = 0;
        virtual bool is_full(void) = 0;
        virtual size_t length(void) = 0;
        virtual void clear(void) = 0;
        virtual bool contains(E element, bool (*equals_function)(const E& element, const E& data)) = 0;
        virtual ostream& print(ostream& output) = 0;
        virtual E* contents(void) = 0;
    };
    
}

#endif /* List_h */
