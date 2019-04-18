//
//  SSLL.h
//  Project1_SSLL
//
//  Created by Alexis Athens on 11/12/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef SSLL_h
#define SSLL_h
#include "List.h"
#include <cstdlib>
#include <stdexcept>
#include <string>

using namespace std;

namespace cop3530
{
    template <typename E>
    class SSLL : public List<E>
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
        E holder;
        E* listContents;
        
    public:
        class self_reference;
        SSLL();
        SSLL(const SSLL &src); //copy constructor
        SSLL(SSLL &&src); //move constructor
        SSLL<E>& operator=(SSLL& src); //copy assignment
        SSLL<E>& operator=(SSLL&& src); //move assignment
        ~SSLL();
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
        
        
        //----- iterator nested classes
        template <typename DataT>
        class SSLL_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = SSLL_Iter;
            using self_reference = SSLL_Iter&;
            
        private:
            Node* here;
            
        public:
            explicit SSLL_Iter(Node* start = nullptr) : here(start) {}
            SSLL_Iter (const SSLL_Iter& src) : here(src.here) {}
            
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
            
            self_reference operator=(SSLL_Iter<DataT> const& src)
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
            bool operator==(SSLL_Iter<DataT> const& rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(SSLL_Iter<DataT> const& rhs) const
            {
                return here != rhs.here;
            }
        }; //end SSLL_Iter
        
        template <typename DataT>
        class SSLL_Const_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = SSLL_Const_Iter;
            using self_reference = SSLL_Const_Iter&;
            
        private:
            const Node* here;
            
        public:
            explicit SSLL_Const_Iter(Node* start = nullptr) : here(start) {}
            SSLL_Const_Iter (const SSLL_Const_Iter& src) : here(src.here) {}
            
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
            
            self_reference operator=(const SSLL_Const_Iter<DataT> src)
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
            bool operator==(const SSLL_Const_Iter<DataT> &rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const SSLL_Const_Iter<DataT> &rhs) const
            {
                return here != rhs.here;
            }
        }; //end SSLL_Const_Iter

        
        using iterator = SSLL_Iter<E>;
        using const_iterator = SSLL_Iter<E const>;
        
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
    //constructor, copy constructor, deconstructor
    
    template <typename E>
    SSLL<E> :: SSLL()
    {
        head = nullptr;
        tail = nullptr;
        temp = nullptr;
        prev = nullptr;
    }
    
    template <typename E>
    SSLL<E> :: SSLL(const SSLL &src) //copy constructor
    {
        head = nullptr;
        tail = nullptr;
        temp = src.head;
        while(temp)
        {
            push_back(temp -> data);
            temp = temp -> next;
        }
    }
    
    template <typename E>
    SSLL<E> :: SSLL(SSLL &&src) //move constructor
    {
        head = src.head;
        tail = src.tail;
    }
    
    template <typename E>
    SSLL<E>& SSLL<E> :: operator=(SSLL& src) //copy assignment
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
    SSLL<E>& SSLL<E> :: operator=(SSLL&& src) //move assignment
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
    SSLL<E> :: ~SSLL()
    {
        temp = head;
        while(temp)
        {
            prev = temp -> next;
            delete temp;
            temp = prev;
        }
        
        head = nullptr;
        temp = nullptr;
        tail = nullptr;
        prev = nullptr;
        
        //delete [] listContents;
    }
    
    
    //==========================================================================
    //operations
    
    //------push_back()
    template <typename E>
    void SSLL<E> :: push_back(E element)
    {
        insert(element, length());
    }
    
    //------push_front()
    template <typename E>
    void SSLL<E> :: push_front(E element)
    {
        insert(element, 0);
    }
    
    //------insert()
    template <typename E>
    void SSLL<E> :: insert(E element, size_t position)
    {
        bool error = false;
        
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
            temp = new Node;
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
                for(int i = 0; i < (position - 1); ++i) //stop one short of desired insertion pos
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
    E SSLL<E> :: replace(E element, size_t position)
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
    E SSLL<E> :: pop_front(void)
    {
        holder = remove(0);
        return holder;
    }
    
    //------pop_back()
    template <typename E>
    E SSLL<E> :: pop_back(void)
    {
        holder = remove(length() - 1);
        return holder;
    }
    
    //------remove()
    template <typename E>
    E SSLL<E> :: remove(size_t position)
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
            delete temp1; //free memory
        }
        else
        {
            for(int i = 0; i < position; ++i) //pos-1
            {
                prev = temp1;
                temp1 = temp1 -> next;
            }
            holder = temp1 -> data;
            if(!(temp1 -> next)) //==nullptr
            {
                tail = prev;
            }
            prev -> next = temp1 -> next;
            delete temp1; //free memory
        }
        
        return holder;
    }
    
    //------peek_front()
    template <typename E>
    E SSLL<E> :: peek_front(void)
    {
        holder = item_at(0);
        return holder;
    }
    
    //------peek_back()
    template <typename E>
    E SSLL<E> :: peek_back(void)
    {
        holder = item_at(length() - 1);
        return holder;
    }
    
    //------item_at()
    template <typename E>
    E SSLL<E> :: item_at(size_t position)
    {
        temp = head;
        //position = (int)(position);
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if((position < 0) || (position > (length() - 1))) //(int)(length() - 1))
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
    bool SSLL<E> :: is_empty(void)
    {
        if(head == nullptr)
            return true;
        else
            return false;
    }
    
    //------is_full()
    template <typename E>
    bool SSLL<E> :: is_full(void)
    {
        return false;
    }
    
    //------length()
    template <typename E>
    size_t SSLL<E> :: length(void)
    {
        size_t len = 0;
        Node* lenPtr;
        lenPtr = head;
        
        while(lenPtr)
        {
            lenPtr = lenPtr -> next;
            ++len;
        }
        
        return len;
    }
    
    //------clear()
    template <typename E>
    void SSLL<E> :: clear(void)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
        }
        else
        {
            Node *delPtr;
            delPtr = head;
            while(head)
            {
                head = head -> next;
                delete delPtr; //free memory
                delPtr = head;
            }
            
            head = nullptr;
            tail = nullptr;
            
            cout << "Memory freed" << endl;
        }
    }
    
    //------contents()
    template <typename E>
    E* SSLL<E> :: contents(void)
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
    bool SSLL<E> :: contains(E element, bool (*equals_function)(const E& element, const E& data))
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
    ostream& SSLL<E> :: print(ostream& output)
    {
        if(is_empty())
        {
            output << "<empty list>" << endl;
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
    
}



#endif /* SSLL_h */
