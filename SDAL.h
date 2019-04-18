//
//  SDAL.h
//  Project1_SSLL
//
//  Created by Alexis Athens on 11/12/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#ifndef SDAL_h
#define SDAL_h
#include "List.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>

using namespace std;

namespace cop3530
{
    template <typename E>
    class SDAL : public List<E>
    {
    private:
        E* data;
        E* tempData;
        E holder;
        int tail;
        int temp;
        int arraySize; //size_t
        
    public:
        class self_reference;
        SDAL();
        SDAL(int arrSize);
        SDAL(const SDAL &src); //copy constructor
        SDAL(SDAL &&src); //move constructor
        SDAL<E>& operator=(SDAL& src); //copy assignment
        SDAL<E>& operator=(SDAL&& src); //move assignment
        ~SDAL();
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
        class SDAL_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = SDAL_Iter;
            using self_reference = SDAL_Iter&;
            
        private:
            E* here;
            SDAL* sdal;
            
        public:
            explicit SDAL_Iter(E* start = nullptr, SDAL* array = nullptr) : here(start), sdal(array) {}
            SDAL_Iter (const SDAL_Iter& src) : here(src.here), sdal(src.sdal) {}
            
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
            
            self_reference operator=(SDAL_Iter<DataT> const& src)
            {
                if(*this == src)
                {
                    return *this;
                }
                sdal = src.sdal;
                here = src.here;
                return *this;
            }
            self_reference operator++() //preincrement
            {
                if(!(here < sdal -> data + sdal -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                ++here;
                return *this;
            }
            self_type operator++(int) //postincrement
            {
                if(!(here < sdal -> data + sdal -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                self_type holder(*this);
                ++here;
                return holder;
            }
            bool operator==(SDAL_Iter<DataT> const& rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(SDAL_Iter<DataT> const& rhs) const
            {
                return here != rhs.here;
            }
        }; //end SDAL_Iter
        
        template <typename DataT>
        class SDAL_Const_Iter
        {
        public:
            //type aliases required for C++ iterator compatibility
            using value_type = DataT;
            using reference = DataT&;
            using pointer = DataT*;
            using difference_type = std::ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;
            
            //type aliases for "prettier code"
            using self_type = SDAL_Const_Iter;
            using self_reference = SDAL_Const_Iter&;
            
        private:
            const E* here;
            const SDAL* sdal;
            
        public:
            explicit SDAL_Const_Iter(E* start = nullptr, const SDAL* list = nullptr) : here(start), sdal(list) {}
            SDAL_Const_Iter (const SDAL_Const_Iter& src) : here(src.here), sdal(src.sdal) {}
            
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
            
            self_reference operator=(SDAL_Iter<DataT> const& src)
            {
                if(*this == src)
                {
                    return *this;
                }
                sdal = src.sdal;
                here = src.here;
                return *this;
            }
            self_reference operator++() //preincrement
            {
                if(!(here < sdal -> data + sdal -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                ++here;
                return *this;
            }
            self_type operator++(int) //postincrement
            {
                if(!(here < sdal -> data + sdal -> tail))
                {
                    throw runtime_error("Error, can't increment a null array");
                }
                self_type holder(*this);
                ++here;
                return holder;
            }
            bool operator==(const SDAL_Const_Iter<DataT> &rhs) const
            {
                return here == rhs.here;
            }
            bool operator!=(const SDAL_Const_Iter<DataT> &rhs) const
            {
                return here != rhs.here;
            }
        }; //end SDAL_Const_Iter
        
        
        using iterator = SDAL_Iter<E>;
        using const_iterator = SDAL_Iter<E const>;
        
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
    SDAL<E> :: SDAL() //default size of 50
    {
        arraySize = 50;
        data = new E(arraySize);
        tail = 0;
    }
    
    template <typename E>
    SDAL<E> :: SDAL(int arrSize)
    {
        arraySize = arrSize;
        data = new E(arraySize);
        tail = 0;
    }
    
    template <typename E>
    SDAL<E> :: SDAL(const SDAL &src) //copy constructor
    {
        tail = src.tail;
        data = new E(src.arraySize);
        arraySize = src.arraySize;
        int i = 0;
        while(i < src.tail)
        {
            data[i] = src.data[i];
            ++i;
        }
    }
    
    template <typename E>
    SDAL<E> :: SDAL(SDAL &&src) //move constructor
    {
        data = src;
        tail = src.tail;
        arraySize = src.arraySize;
    }
    
    template <typename E>
    SDAL<E>& SDAL<E> :: operator=(SDAL& src) //copy assignment
    {
        if(this == &src)
        {
            return *this;
        }
        clear(data);
        data = nullptr;
        
        int i;
        while(i < src.tail)
        {
            data[i] = src.data[i];
            ++i;
        }
    }
    
    template <typename E>
    SDAL<E>& SDAL<E> :: operator=(SDAL&& src) //move assignment
    {
        if(this == &src)
        {
            return *this;
        }
        clear(data);
        data = src.data;
        src.data = nullptr;
    }
    
    
    template <typename E>
    SDAL<E> :: ~SDAL() //destructor
    {
        for(int i = 0; i < length(); ++i)
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
    void SDAL<E> :: push_back(E element)
    {
        insert(element, length());
    }
    
    //------push_front()
    template <typename E>
    void SDAL<E> :: push_front(E element)
    {
        insert(element, 0);
    }
    
    //------insert()
    template <typename E>
    void SDAL<E> :: insert(E element, size_t position)
    {
        if(is_full()) //resize list if array is full
            cout << "List resized" << endl;
        
        if(position < 0 || position > length()) //error
        {
            cout << "Error, position invalid" << endl;
        }
        else //insert data
        {
            temp = tail;
            position = (int)(position);
            while(temp > position)
            {
                data[temp] = data[temp - 1]; //data[temp + 1] = data[temp];
                --temp;
            }
            data[temp] = element;
            ++tail;
        }
    }
    
    //------replace()
    template <typename E>
    E SDAL<E> :: replace(E element, size_t position)
    {
        if(is_empty()) //error
        {
            cout << "Error, list empty" << endl;
            return 0;
        }
        else if(position < 0 || position > (length() - 1)) //error
        {
            cout << "Error, position invalid" << endl;
            return 0;
        }
        holder = data[position];
        data[position] = element;
        return holder;
    }
    
    //------pop_front()
    template <typename E>
    E SDAL<E> :: pop_front(void)
    {
        holder = remove(0);
        return holder;
    }
    
    //------pop_back()
    template <typename E>
    E SDAL<E> :: pop_back(void)
    {
        holder = remove(length() - 1);
        return holder;
    }
    
    //------remove()
    template <typename E>
    E SDAL<E> :: remove(size_t position)
    {
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
        
        temp = (int)(position);
        holder = data[temp];
        while(temp < (tail - 1))
        {
            data[temp] = data[temp + 1];
            ++temp;
        }
        data[temp] = 0;
        --tail;
        
        return holder;
    }
    
    //------peek_front()
    template <typename E>
    E SDAL<E> :: peek_front(void)
    {
        return item_at(0);
    }
    
    //------peek_back()
    template <typename E>
    E SDAL<E> :: peek_back(void)
    {
        return item_at(length() - 1);
    }
    
    //------item_at()
    template <typename E>
    E SDAL<E> :: item_at(size_t position)
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
        
        return data[position];
    }
    
    //------is_empty()
    template <typename E>
    bool SDAL<E> :: is_empty(void)
    {
        if(tail == 0)
            return true;
        else
            return false;
    }
    
    //------is_full()
    template <typename E>
    bool SDAL<E> :: is_full(void)
    {
        if(length() == (arraySize - 1)) //array full
        {
            //allocate new array 150% of the size
            arraySize = (int)(1.5 * arraySize);
            tempData = new E(arraySize);
            for(int i = 0; i < arraySize; ++i) //copy data over
            {
                tempData[i] = data[i];
            }
            delete [] data; //free memory
            data = tempData; //point to larger memory
        }
        else if((arraySize >= 100) && (length() < (arraySize / 2))) //array too empty
        {
            //allocate new array 75% of original size
            arraySize = (int)(.75 * arraySize);
            tempData = new E(arraySize);
            for(int i = 0; i < arraySize; ++i)
            {
                tempData[i] = data[i];
            }
            delete [] data;
            data = tempData;
        }
        
        return false;
    }
    
    //------length()
    template <typename E>
    size_t SDAL<E> :: length(void)
    {
        return tail;
    }
    
    //------clear()
    template <typename E>
    void SDAL<E> :: clear(void)
    {
        if(is_empty())
        {
            cout << "Error, list is empty";
        }
        else
        {
            for(int i = 0; i < length(); ++i)
            {
                data[i] = 0;
            }
            tail = 0;
            cout << "Memory freed" << endl;
        }

    }
    
    //------contents()
    template <typename E>
    E* SDAL<E> :: contents(void)
    {
        return data;
    }
    
    //------contains()
    template <typename E>
    bool SDAL<E> :: contains(E element, bool (*equals_function)(const E& element, const E& data))
    {
        for(int i = 0; i < length(); ++i)
        {
            if(equals_function(element, data[i]))
                return true;
        }
        
        return false;
    }
    
    //------print(ostream)
    template <typename E>
    ostream& SDAL<E> :: print(ostream& output)
    {
        if(is_empty())
        {
            output << "<empty list>" << endl;
        }
        else
        {
            output << "[";
            for(int i = 0; i < length(); ++i)
            {
                output << data[i];
                if((i + 1) != length())
                    output << ", ";
            }
            output << "]" << endl;
        }
        return output;
    }
    
} //end namespace bracket




#endif /* SDAL_h */
