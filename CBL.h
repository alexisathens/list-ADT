//
//  CBL.h
//  Project1_SSLL
//
//  Created by Alexis Athens on 11/12/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef CBL_h
#define CBL_h
#include "List.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace cop3530
{
    template <typename E>
    class CBL : public List<E>
    {
    private:
        E* data;
        E* tempData;
        E holder;
        int head;
        int tail;
        int temp;
        int arraySize;
        
    public:
        class self_reference;
        CBL();
        CBL(int arrSize);
        CBL(const CBL &src); //copy constructor
        ~CBL();
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
        class CBL_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = CBL_Iter;
            using self_reference = CBL_Iter&;
            
        private:
            E* here;
            CBL* CBL;
            
        public: //delete "class"
            explicit CBL_Iter(E* start = nullptr, class CBL* array = nullptr) : here(start), CBL(array) {}
            CBL_Iter (const CBL_Iter& src) : here(src.here), CBL(src.CBL) {}
            
            reference operator*() const //dereference
            {
                if(!here) //here == nullptr
                    throw runtime_error("Error, can't dereference a null array");
                
                return *here;
            }
            
            pointer operator ->() const
            {
                if(!here)
                {
                    throw runtime_error("Error, can't use operator on a null array");
                }
                return here;
            }
            
            self_reference operator=(CBL_Iter<DataT> const& src)
            {
                if(*this == src)
                {
                    return *this;
                }
                CBL = src.CBL;
                here = src.here;
                return *this;
            }
            
            self_reference operator++() //preincrement
            {
                if(!(here < CBL -> data + CBL -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                ++here;
                return *this;
            }
            
            self_type operator++(int) //postincrement
            {
                if(!(here < CBL -> data + CBL -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                self_type holder(*this);
                ++here;
                return holder;
            }
            
            bool operator==(CBL_Iter<DataT> const& rhs) const
            {
                return here == rhs.here;
            }
            
            bool operator!=(CBL_Iter<DataT> const& rhs) const
            {
                return here != rhs.here;
            }
        }; //end CBL_Iter
        
        template <typename DataT>
        class CBL_Const_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = CBL_Const_Iter;
            using self_reference = CBL_Const_Iter&;
            
        private:
            const E* here;
            const CBL* CBL;
            
        public:
            explicit CBL_Const_Iter(E* start = nullptr, const class CBL* list = nullptr) : here(start), CBL(list) {}
            CBL_Const_Iter (const CBL_Const_Iter& src) : here(src.here), CBL(src.CBL) {}
            
            reference operator*() const //dereference
            {
                if(!here) //here == nullptr
                    throw runtime_error("Error, can't dereference a null array");
                
                return *here;
            }
            pointer operator ->() const
            {
                if(!here)
                {
                    throw runtime_error("Error, can't use operator on a null array");
                }
                return here;
            }
            
            self_reference operator=(CBL_Iter<DataT> const& src)
            {
                if(*this == src)
                {
                    return *this;
                }
                CBL = src.CBL;
                here = src.here;
                return *this;
            }
            self_reference operator++() //preincrement
            {
                if(!(here < CBL -> data + CBL -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                ++here;
                return *this;
            }
            self_type operator++(int) //postincrement
            {
                if(!(here < CBL -> data + CBL -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                self_type holder(*this);
                ++here;
                return holder;
            }
            bool operator==(const CBL_Const_Iter<DataT> &rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const CBL_Const_Iter<DataT> &rhs) const
            {
                return here != rhs.here;
            }
        }; //end CBL_Const_Iter
        
        
        using iterator = CBL_Iter<E>;
        using const_iterator = CBL_Iter<E const>;
        
        //begin and end functions here
        
        iterator begin()
        {
            return iterator(data, this);
        }
        
        const_iterator begin() const
        {
            return const_iterator(data, this);
        }
        
        iterator end()
        {
            return iterator(data + tail, this);
        }
        
        const_iterator end() const
        {
            return const_iterator(data + tail, this);
        }

    };
    
    
    
    //==========================================================================
    //constructor, deconstructor
    
    template <typename E>
    CBL<E> :: CBL(int arrSize)
    {
        arraySize = arrSize;
        data = new E(arraySize);
        head = -1;
        tail = 0;
    }
    
    template <typename E>
    CBL<E> :: CBL()
    {
        arraySize = 50;
        data = new E(arraySize);
        head = -1;
        tail = 0;
    }
    
    template <typename E>
    CBL<E> :: CBL(const CBL &src)
    {
        head = src.head;
        tail = src.tail;
        data = new E(src.arraySize);
        arraySize = src.arraySize;
        for(int i = head, j = 0; i != ((tail + arraySize) % arraySize); ++i, ++j) //copy data
        {
            data[j] = src.data[i];
            if(i == (arraySize - 1))
            {
                i = -1;
            }
        }
    }

    template <typename E>
    CBL<E> :: ~CBL()
    {
        for(int i = 0; i < arraySize; ++i)
        {
            data[i] = 0;
        }
        delete [] data;
        delete [] tempData;
    }
    
    
    //==========================================================================
    //operations
    
    //------push_back()
    template <typename E>
    void CBL<E> :: push_back(E element)
    {
        //increment tail post-insertion
        insert(element, length());
    }
    
    //------push_front()
    template <typename E>
    void CBL<E> :: push_front(E element)
    {
        if(is_empty())
        {
            head = 0;
            tail = 1;
            data[head] = element;
        }
        else
        {
            if(is_full()) //resize and continue
            {
                cout << "List resized" << endl;
            }
            
            //decrease head
            if(head == 0)
                head = arraySize - 1; //wrap to end of array
            else
                --head;
            
            data[head] = element;
        }
    }
    
    //------insert()
    template <typename E>
    void CBL<E> :: insert(E element, size_t position)
    {
        if(position == -1 && !is_empty()) //push front & list not empty
        {
            push_front(element);
        }
        else if(position >= 0 && position <= length()) //valid position
        {
            if(is_empty()) //position == 0
            {
                head = 0;
                tail = 1;
            }
            else
            {
                if(is_full())
                {
                    cout << "List resized" << endl;
                }
                
                position = (head + position) % arraySize;
                for(int i = tail; i != position; --i) //move elements
                {
                    if(i == 0)
                    {
                        data[i] = data[arraySize - 1];
                        i = arraySize;
                    }
                    else
                    {
                        data[i] = data[i - 1];
                    }
                }
                
                //increase tail
                if(tail == arraySize - 1) //check if tail at end of array
                {
                    tail = 0;
                }
                else
                {
                    ++tail;
                }
            }
            
            data[position] = element; //insert new elt
        }
        else
        {
            if(is_empty())
                cout << "Error, list empty" << endl;
            else
                cout << "Error, position invalid" << endl;
        }
    }
    
    //------replace()
    template <typename E>
    E CBL<E> :: replace(E element, size_t position)
    {
        if(is_empty()) //error
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if(position < 0 || position > (length() - 1)) //error
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        
        holder = data[(head + position) % arraySize];
        data[(head + position) % arraySize] = element;
        return holder;
    }
    
    //------pop_front()
    template <typename E>
    E CBL<E> :: pop_front(void)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }

        holder = data[head];
        data[head] = 0;
        
        //increment head
        if(length() == 1) //last element left in list, reset
        {
            head = -1;
            tail = 0;
        }
        else //shift head
        {
            head = (head + 1) % arraySize;
        }
        
        return holder;
    }
    
    //------pop_back()
    template <typename E>
    E CBL<E> :: pop_back(void)
    {
        holder = remove(length() - 1);
        return holder;
    }
    
    //------remove()
    template <typename E>
    E CBL<E> :: remove(size_t position)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if(position == 0)
        {
            holder = pop_front();
        }
        else if(position < 0 || position > (length() - 1))
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        else //valid position
        {
            holder = data[(head + position) % arraySize];
            
            int i = 0;
            
            for(i = (int)(head + position); ((i + 1) % arraySize) != tail; ++i)
            {
                data[i % arraySize] = data[(i + 1) % arraySize];
            }
            
            data[i] = 0; //set empty space to 0
            tail = (tail - 1 + arraySize) % arraySize; //shift tail left
        }
        
        if(head == tail) //list now empty after removal, reset
        {
            head = -1;
            tail = 0;
        }
        
        return holder;
    }
    
    //------peek_front()
    template <typename E>
    E CBL<E> :: peek_front(void)
    {
        return item_at(0);
    }
    
    //------peek_back()
    template <typename E>
    E CBL<E> :: peek_back(void)
    {
        return item_at(length() - 1); //(tail - 1 + arraySize) % arraySize
    }
    
    //------item_at()
    template <typename E>
    E CBL<E> :: item_at(size_t position)
    {
        if(is_empty())
        {
            cout << "Error, list is empty" << endl;
            return 0;
        }
        else if(position > (length() - 1) || position < 0)
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        
        return data[(head + position) % arraySize];
    }
    
    //------is_empty()
    template <typename E>
    bool CBL<E> :: is_empty(void)
    {
        if(length() == 0) //head = -1, tail = 0
            return true;
        else
            return false;
    }
    
    //------is_full()
    template <typename E>
    bool CBL<E> :: is_full(void)
    {
        if(head == tail) //array full
        {
            //allocate new array 150% of the size
            arraySize = (int)(1.5 * arraySize);
            tempData = new E(arraySize);
            
            //insert first value into new array
            tempData[0] = data[head];
            head = (head + 1) % arraySize; //increment head so head != tail
            
            int i = 0, j = 0;
            for(i = head, j = 1; i != ((tail -1 + arraySize) % arraySize); ++i, ++j) //copy data
            {
                tempData[j] = data[i];
                if(i == (arraySize - 1))
                {
                    i = -1;
                }
            }
            delete [] data; //free memory
            data = tempData; //point to larger memory
            head = 0;
            tail = j;
        }
        else if((arraySize >= 100) && (length() < (arraySize / 2))) //array too empty
        {
            //allocate new array 75% of original size
            arraySize = (int)(.75 * arraySize);
            tempData = new E(arraySize);
            
            //insert first value into new array
            tempData[0] = data[head];
            head = (head + 1) % arraySize; //increment head so head != tail
            
            int i = 0, j = 0;
            for(i = head, j = 1; i != ((tail + arraySize) % arraySize); ++i, ++j) //copy data
            {
                tempData[j] = data[i];
                if(i == (arraySize - 1))
                {
                    i = -1;
                }
            }
            
            delete [] data;
            data = tempData;
            head = 0;
            tail = j;
        }
        
        return false;
    }
    
    //------length()
    template <typename E>
    size_t CBL<E> :: length(void)
    {
        size_t len = 0;
        
        if(head == -1 && tail == 0) //array empty
            len = 0;
        else if(tail > head)
            len = tail - head;
        else //head >= tail
            len = arraySize - (head - tail);
        
        return len;
    }
    
    //------clear()
    template <typename E>
    void CBL<E> :: clear(void)
    {
        if(is_empty())
        {
            cout << "Error, list is empty";
        }
        else
        {
            for(int i = 0; i < arraySize; ++i)
            {
                data[i] = 0;
            }
            head = -1;
            tail = 0;
            cout << "Memory freed" << endl;
        }
    }
    
    //------contents()
    template <typename E>
    E* CBL<E> :: contents(void)
    {
        tempData = new E(arraySize);
        
        //insert first value into new array
        tempData[0] = data[head];
        head = (head + 1) % arraySize; //increment head so head != tail
        
        int i = 0, j = 0;
        for(i = head, j = 0; i != ((tail + arraySize) % arraySize); ++i, ++j) //copy data
        {
            tempData[j] = data[i];
            if(i == (arraySize - 1))
            {
                i = -1;
            }
        }
        return tempData;
    }
    
    //------contains()
    template <typename E>
    bool CBL<E> :: contains(E element, bool (*equals_function)(const E& element, const E& data))
    {
        for(int i = head; (i % arraySize) != tail; ++i)
        {
            if(equals_function(element, data[i]))
                return true;
            if(i == (arraySize - 1))
            {
                i = -1;
            }
        }
        
        /*
        for(int i = head; i != tail; ++i)
        {
            if(equals_function(element, data[i]))
                return true;
            
            if(i == arraySize - 1)
            {
                i = -1;
            }
        }
         */
        
        return false;
    }
    
    //------print(ostream)
    template <typename E>
    ostream& CBL<E> :: print(ostream& output)
    {
        if(is_empty())
        {
            output << "<empty list>" << endl;
        }
        else
        {
            output << "[";
            for(int i = head; i != tail; ++i)
            {
                output << data[i];
                if((i + 1) % arraySize != tail)
                    output << ", ";
                
                if(i == arraySize - 1)
                {
                    i = -1;
                }
            }
            output << "]" << endl;
        }
        return output;
    }
    
} //end namespace bracket




#endif /* CBL_h */
