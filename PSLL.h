//
//  PSLL.h
//  Project1_SSLL
//
//  Created by Alexis Athens on 11/12/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef PSLL_h
#define PSLL_h
#include "List.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace cop3530
{
    template <typename E>
    class PSLL : public List<E>
    {
    private:
        struct Node
        {
            E data;
            Node* next;
        };
        Node* head;
        Node* tail;
        Node* temp;
        Node* prev;
        Node* free;
        E holder;
        E* listContents;
        
    public:
        class self_reference;
        PSLL(); //size_t num
        PSLL(const PSLL &src); //copy constructor
        PSLL(PSLL &&src); //move constructor
        PSLL<E>& operator=(PSLL& src); //copy assignment
        PSLL<E>& operator=(PSLL&& src); //move assignment
        ~PSLL();
        void insert(E element, size_t position) override;
        void push_back(E element) override;
        void push_front(E element) override;
        E replace(E element, size_t position) override;
        E remove(size_t position) override;
        E pop_back(void) override;
        E pop_front(void) override;
        E item_at(size_t position) override;
        E peek_back(void) override;
        E peek_front(void) override;
        bool is_empty(void) override;
        bool is_full(void) override;
        size_t length(void) override;
        void clear(void) override;
        bool contains(E element, bool (*equals_function)(const E& element, const E& data)) override;
        ostream& print(ostream& output) override;
        E* contents(void) override;
        ostream& printFree(ostream& output);
        
        //----- iterator nested classes
        template <typename DataT>
        class PSLL_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = PSLL_Iter;
            using self_reference = PSLL_Iter&;
            
        private:
            Node* here;
            
        public:
            explicit PSLL_Iter(Node* start = nullptr) : here(start) {}
            PSLL_Iter (const PSLL_Iter& src) : here(src.here) {}
            
            reference operator*() const //dereference
            {
                if(!here) //here == nullptr
                    throw runtime_error("Error, can't dereference a null node");
                
                return here -> data;
            }
            pointer operator ->() const
            {
                if(!here)
                {
                    throw runtime_error("Error, can't use operator on a null node");
                }
                return &(here -> data);
            }
            
            self_reference operator=(PSLL_Iter<DataT> const& src)
            {
                if(*this == src)
                {
                    return *this;
                }
                
                here = src.here;
                return *this;
            }
            self_reference operator++() //preincrement
            {
                if(!here)
                {
                    throw runtime_error("Error, can't increment a null node");
                }
                here = here -> next;
                return *this;
            }
            self_type operator++(int) //postincrement
            {
                if(!here)
                {
                    throw runtime_error("Error, can't increment a null node");
                }
                self_type holder(*this);
                here = here -> next;
                return holder;
            }
            bool operator==(PSLL_Iter<DataT> const& rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(PSLL_Iter<DataT> const& rhs) const
            {
                return here != rhs.here;
            }
        }; //end PSLL_Iter
        
        template <typename DataT>
        class PSLL_Const_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = PSLL_Const_Iter;
            using self_reference = PSLL_Const_Iter&;
            
        private:
            const Node* here;
            
        public:
            explicit PSLL_Const_Iter(Node* start = nullptr) : here(start) {}
            PSLL_Const_Iter (const PSLL_Const_Iter& src) : here(src.here) {}
            
            reference operator*() const //dereference
            {
                if(!here) //here == nullptr
                    throw runtime_error("Error, can't dereference a null node");
                
                return here -> data;
            }
            pointer operator ->() const
            {
                if(!here)
                {
                    throw runtime_error("Error, can't use operator on a null node");
                }
                return &(here -> data);
            }
            
            self_reference operator=(const PSLL_Const_Iter<DataT> src)
            {
                if(*this == src)
                {
                    return *this;
                }
                
                here = src.here;
                return *this;
            }
            self_reference operator++() //preincrement
            {
                if(!here)
                {
                    throw runtime_error("Error, can't increment a null node");
                }
                here = here -> next;
                return *this;
            }
            self_type operator++(int) //postincrement
            {
                if(!here)
                {
                    throw runtime_error("Error, can't increment a null node");
                }
                self_type holder(*this);
                here = here -> next;
                return holder;
            }
            bool operator==(const PSLL_Const_Iter<DataT> &rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const PSLL_Const_Iter<DataT> &rhs) const
            {
                return here != rhs.here;
            }
        }; //end PSLL_Const_Iter
        
        
        using iterator = PSLL_Iter<E>;
        using const_iterator = PSLL_Iter<E const>;
        
        //begin and end functions here
        
        iterator begin()
        {
            return iterator(head);
        }
        
        const_iterator begin() const
        {
            return const_iterator(head);
        }
        
        iterator end()
        {
            return iterator(nullptr);
        }
        
        const_iterator end() const
        {
            return const_iterator(nullptr);
        }

    };
    
    
    
    //==========================================================================
    //constructor, deconstructor
    
    template <typename E>
    PSLL<E> :: PSLL() //size_t num
    {
        head = nullptr;
        tail = nullptr;
        temp = nullptr;
        prev = nullptr;
        free = nullptr;
    }
    
    template <typename E>
    PSLL<E> :: PSLL(const PSLL &src) //copy constructor
    {
        head = nullptr;
        tail = nullptr;
        free = src.free;
        temp = src.head;
        
        while(temp)
        {
            push_back(temp -> data);
            temp = temp -> next;
        }
    }
    
    template <typename E>
    PSLL<E> :: PSLL(PSLL &&src) //move constructor
    {
        head = src.head;
        tail = src.tail;
    }
    
    template <typename E>
    PSLL<E>& PSLL<E> :: operator=(PSLL& src) //copy assignment
    {
        if(this == &src)
        {
            return *this;
        }
        clear(head);
        head = nullptr;
        
        temp = src;
        head = src;
        while(temp)
        {
            tail = src;
            temp = temp -> next;
        }
    }
    
    template <typename E>
    PSLL<E>& PSLL<E> :: operator=(PSLL&& src) //move assignment
    {
        if(this == &src)
        {
            return *this;
        }
        clear(head);
        head = src.head;
        src.head = nullptr;
    }

    
    template <typename E>
    PSLL<E> :: ~PSLL()
    {
        temp = head;
        while(temp)
        {
            prev = temp -> next;
            delete temp;
            temp = prev;
        }
        
        temp = free;
        while(temp) //delete free list
        {
            prev = temp -> next;
            delete temp;
            temp = free;
        }
        
        head = nullptr;
        free = nullptr;
        temp = nullptr;
        tail = nullptr;
        prev = nullptr;
        
        delete [] listContents;
    }
    
    
    //==========================================================================
    //operations
    
    //------push_back()
    template <typename E>
    void PSLL<E> :: push_back(E element)
    {
        insert(element, length());
    }
    
    //------push_front()
    template <typename E>
    void PSLL<E> :: push_front(E element)
    {
        insert(element, 0);
    }
    
    //------insert()
    template <typename E>
    void PSLL<E> :: insert(E element, size_t position)
    {
        bool error = false;
        
        //errors
        if(is_full()) //error
        {
            cout << "Error, list is full" << endl;
            error = true;
        }
        else if(position < 0 || position > length()) //error
        {
            cout << "Error, position invalid" << endl;
            error = true;
        }
        
        if(error == false)
        {
            //find new node
            if(free) //use free node
            {
                temp = free;
                free = free -> next;
            }
            else //create new node
            {
                temp = new Node;
            }
            
            //insert node
            if(is_empty() && position == 0) //create list
            {
                temp -> data = element;
                temp -> next = nullptr;
                head = temp;
                tail = temp;
            }
            else if(position == 0) //push_front
            {
                temp -> data = element;
                temp -> next = head;
                head = temp;
            }
            else if(position == length()) //push_back
            {
                temp -> data = element;
                temp -> next = nullptr;
                tail -> next = temp;
                tail = temp;
            }
            else
            {
                prev = head;
                for(int i = 0; i < (position - 1); ++i) //stop one short of desired pos
                {
                    prev = prev -> next;
                }
                temp -> data = element;
                temp -> next = prev -> next;
                prev -> next = temp;
            }
        }
    }
    
    //------replace()
    template <typename E>
    E PSLL<E> :: replace(E element, size_t position)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        if(position < 0 || position > (length() - 1)) //error
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        
        temp = head;
        for(int i = 0; i < position; ++i)
        {
            temp = temp -> next;
        }
        
        holder = temp -> data;
        temp -> data = element;
        
        return holder;
    }
    
    //------pop_front()
    template <typename E>
    E PSLL<E> :: pop_front(void)
    {
        holder = remove(0);
        return holder;
    }
    
    //------pop_back()
    template <typename E>
    E PSLL<E> :: pop_back(void)
    {
        holder = remove(length() - 1);
        return holder;
    }
    
    //------remove()
    template <typename E>
    E PSLL<E> :: remove(size_t position)
    {
        Node* temp1;
        temp1 = head;
        
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if(position < 0 || position > (length() - 1))
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        
        if(position == 0) //pop_front
        {
            holder = temp1 -> data;
            head = head -> next;
        }
        else
        {
            for(int i = 0; i < position; ++i)
            {
                prev = temp1;
                temp1 = temp1 -> next;
            }
            holder = temp1 -> data;
            if(!(temp1 -> next)) //==nullptr //if temp1 is the tail
            {
                tail = prev;
            }
            prev -> next = temp1 -> next;
        }
        
        if(is_full()) //free list full
        {
            delete temp1;
        }
        //else add node to free list (LIFO order)
        else if(!free) //free list empty
        {
            temp1 -> data = 0;
            free = temp1;
            free -> next = nullptr;
        }
        else //free list already contains nodes
        {
            temp1 -> data = 0;
            temp1 -> next = free;
            free = temp1;
        }
        
        return holder;
    }
    
    //------peek_front()
    template <typename E>
    E PSLL<E> :: peek_front(void)
    {
        holder = item_at(0);
        return holder;
    }
    
    //------peek_back()
    template <typename E>
    E PSLL<E> :: peek_back(void)
    {
        holder = item_at(length() - 1);
        return holder;
    }
    
    //------item_at()
    template <typename E>
    E PSLL<E> :: item_at(size_t position)
    {
        temp = head;
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if(position < 0 || position > (length() - 1))
        {
            cout << "Error, position not valid" << endl;
            return 0;
        }
        else
        {
            for(int i = 0; i < position; ++i)
            {
                temp = temp -> next;
            }
            
            holder = temp -> data;
        }
        
        return holder;
    }
    
    //------is_empty()
    template <typename E>
    bool PSLL<E> :: is_empty(void)
    {
        if(head == nullptr)
            return true;
        else
            return false;
    }
    
    //------is_full()
    template <typename E>
    bool PSLL<E> :: is_full(void) //checks if free list is full (more than 50 nodes)
    {
        size_t freeLen = 0;
        Node* tempFree;
        tempFree = free;
        while(tempFree)
        {
            tempFree = tempFree -> next;
            ++freeLen;
        }
        
        if(freeLen > 50)
            return true;
        
        return false;
    }
    
    //------length()
    template <typename E>
    size_t PSLL<E> :: length(void)
    {
        size_t len = 0;
        Node* tempList;
        tempList = head;
        
        while(tempList)
        {
            tempList = tempList -> next;
            ++len;
        }
        
        return len;
    }
    
    //------clear()
    template <typename E>
    void PSLL<E> :: clear(void)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
        }
        else
        {
            Node *delPtr;
            delPtr = head;
            while(head) //clear list
            {
                head = head -> next;
                delete delPtr; //free memory
                delPtr = head;
            }
            
            delPtr = free;
            while(free) //clear free
            {
                free = free -> next;
                delete delPtr; //free memory
                delPtr = free;
            }
            
            head = nullptr;
            tail = nullptr;
            free = nullptr;
            
            cout << "Memory freed" << endl;
        }
    }
    
    //------contents()
    template <typename E>
    E* PSLL<E> :: contents(void)
    {
        int len = static_cast<int>(length());
        listContents = new E(len);
        temp = head;
        
        for(int i = 0; i < len; ++i)
        {
            listContents[i] = temp -> data;
            temp = temp -> next;
        }
        
        return listContents;
    }
    
    //------contains()
    template <typename E>
    bool PSLL<E> :: contains(E element, bool (*equals_function)(const E& element, const E& data))
    {
        temp = head;
        while(temp)
        {
            if(equals_function(element, temp -> data))
                return true;
            temp = temp -> next;
        }
        
        return false;
    }
    
    //------print(ostream)
    template <typename E>
    ostream& PSLL<E> :: print(ostream& output)
    {
        if(is_empty())
        {
            output << "<empty list>";
        }
        else
        {
            output << "[";
            temp = head;
            while(temp)
            {
                output << temp -> data;
                if(temp -> next)
                    output << ", ";
                temp = temp -> next;
            }
            output << "]" << endl;
        }
        
        return output;
    }
    
    
    //===============================================================
    
    /*
    //------printFree(ostream)
    template <typename E>
    ostream& PSLL<E> :: printFree(ostream& output)
    {
        if(!free)
        {
            output << "<empty freelist>" << endl;
        }
        else
        {
            output << "Free list: [";
            temp = free;
            while(temp)
            {
                output << temp -> data;
                if(temp -> next)
                    output << ", ";
                temp = temp -> next;
            }
            output << "]" << endl;
        }
        
        return output;
    }
     */
    
    
} //end namespace bracket


#endif /* PSLL_h */
