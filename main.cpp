//
//  main.cpp
//  Project1_SSLL
//
//  Created by Alexis Athens on 9/9/17.
//  Copyright © 2017 Alexis Athens. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <string>
#include "SSLL.h"
#include "PSLL.h"
#include "SDAL.h"
#include "CBL.h"
//#define CATCH_CONFIG_MAIN
//#include "catch.hpp"

using namespace cop3530;
using namespace std;

//------equals_function()
bool equals_function(const int& element, const int& data)
{
    if(element == data)
        return true;
    else
        return false;
}

int main()
{
    //------ dummy vars
    int insert1 = 8;
    int insert2 = 17;
    int insert3 = 18;
    int insert4 = 9;
    int posInsert = 3;
    int posRemove = 3;
    int posReplace = 2;
    int replace1 = 99;
    int posPeek = 4;
    int* contentsArray;
    
    
    cout<<"\n\n--------------------------------------------------\n";
    cout<<"-------------------- SSLL ------------------------\n";
    cout<<"-------------------- Test 1 ------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    
    SSLL<int> test1;
    
    //----- errors
    cout << "Pre-initialization error tests:" << endl;
    cout << "Try pop_back: ";
    test1.pop_back();
    cout << "Try print: ";
    test1.print(cout);
    cout << "Try replace: ";
    test1.replace(1, 0);
    cout << "Try clear: ";
    test1.clear();
    
    //------ fill linked list
    test1.push_back(12);
    test1.push_back(13);
    test1.push_front(11);
    test1.push_front(6);
    test1.push_front(9);
    test1.push_back(14);
    test1.push_front(8);
    
    cout<<"\n---------------Pushing front and back---------------" << endl;
    //8 9 6 11 12 13 14
    test1.print(cout);
    
    cout<<"---------------Removing---------------" << endl;
    cout << "--Removing " << test1.pop_front() << " from front, " << test1.remove(posRemove) << " from index " << posRemove << ", and " << test1.pop_back() << " from back" << endl;
    test1.print(cout);
    
    cout<<"---------------Inserting---------------" << endl;
    cout << "--Inserting " << insert1 << " to front, " << insert2 << " to position " << posInsert << ", and inserting " << insert3 << " to back, and inserting " << insert4 << " to back" << endl;
    test1.push_front(insert1);
    test1.insert(insert2, posInsert);
    test1.push_back(insert3);
    test1.push_back(insert4);
    test1.print(cout);
    
    cout<<"---------------Replacing---------------" << endl;
    cout << "--Replacing position " << posReplace << " with " << replace1 << endl;
    test1.replace(replace1, posReplace);
    test1.print(cout);

    cout<<"---------------Peeking---------------" << endl;
    cout << "--Peek front is " << test1.peek_front() << ", peek at index " << posPeek << " is " << test1.item_at(posPeek) << ", and peek back is " << test1.peek_back() << endl;
    test1.print(cout);
    
    cout<<"---------------Length---------------" << endl;
    cout << "Length of list is " << test1.length() << endl;
    test1.print(cout);
    
    cout<<"---------------Contents---------------" << endl;
    int lengthInt = static_cast<int>(test1.length());
    contentsArray = new int(lengthInt);
    contentsArray = test1.contents();
    for(int i = 0; i < lengthInt; ++i)
    {
        cout << contentsArray[i] << " ";
    }
    cout << endl;

    cout<<"---------------Contains---------------" << endl;
    cout << "Contains 99 is " << test1.contains(99, equals_function) << endl;
    cout << "Contains 88 is " << test1.contains(88, equals_function) << endl;
    
    
    cout<<"---------------Clearing---------------" << endl;
    test1.clear();
    test1.print(cout);
    
    cout<<"\n---------------Error handling test---------------" << endl;
    cout << "length is " << test1.length() << endl;
    cout << "remove from empty list: ";
    test1.remove(1);
    cout << "peek at empty list: ";
    test1.peek_front();
    cout << "pop_back from empty list: ";
    test1.pop_back();
    cout << "item_at(head) for empty list: ";
    test1.item_at(0);
    cout << "remove from empty list: ";
    test1.insert(2, 3);
    cout << endl;
    
    
    
    cout<<"\n\n--------------------------------------------------\n";
    cout<<"-------------------- PSLL ------------------------\n";
    cout<<"--------------------Test 2------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    
    PSLL<int> test2;
    
    //----- errors
    cout << "Pre-initialization error tests:" << endl;
    cout << "Try pop_back: ";
    test2.pop_back();
    cout << "Try print: ";
    test2.print(cout);
    cout << "\nTry replace: ";
    test2.replace(1, 0);
    cout << "Try clear: ";
    test2.clear();
    
    //------ fill linked list
    test2.push_back(12);
    test2.push_back(13);
    test2.push_front(11);
    test2.push_front(6);
    test2.push_front(9);
    test2.push_back(14);
    test2.push_front(8);
    
    
    cout<<"\n---------------Pushing front and back---------------" << endl;
    //8 9 6 11 12 13 14
    test2.print(cout);
    
    cout<<"---------------Removing---------------" << endl;
    cout << "--Removing " << test2.pop_front() << " from front, " << test2.remove(posRemove) << " from index " << posRemove << ", and " << test2.pop_back() << " from back" << endl;
    test2.print(cout);
    //test2.printFree(cout);
    
    cout<<"---------------Inserting---------------" << endl;
    cout << "--Inserting " << insert1 << " to front, " << insert2 << " to index " << posInsert << ", inserting " << insert3 << " to back, and inserting " << insert4 << " to back" << endl;
    test2.push_front(insert1);
    test2.insert(insert2, posInsert);
    test2.push_back(insert3);
    test2.push_back(insert4);
    test2.print(cout);
    //test2.printFree(cout);
    
    cout<<"---------------Replacing---------------" << endl;
    cout << "--Replacing position " << posReplace << " with " << replace1 << endl;
    test2.replace(replace1, posReplace);
    test2.print(cout);
    
    cout<<"---------------Peeking---------------" << endl;
    cout << "--Peek front is " << test2.peek_front() << ", peek at position " << posPeek << " is " << test2.item_at(posPeek) << ", and peek back is " << test2.peek_back() << endl;
    
    cout<<"---------------Length---------------" << endl;
    cout << "Length of list is " << test2.length() << endl;
    test2.print(cout);
    
    cout<<"---------------Contents---------------" << endl;
    lengthInt = static_cast<int>(test2.length());
    contentsArray = new int(lengthInt);
    contentsArray = test2.contents();
    for(int i = 0; i < lengthInt; ++i)
    {
        cout << contentsArray[i] << " ";
    }
    cout << endl;
    
    cout<<"---------------Contains---------------" << endl;
    cout << "Contains 99 is " << test2.contains(99, equals_function) << endl;
    cout << "Contains 88 is " << test2.contains(88, equals_function) << endl;
    
    cout<<"---------------Clearing---------------" << endl;
    test2.clear();
    test2.print(cout);
    cout << endl;
    
    cout<<"\n---------------Error handling test---------------" << endl;
    cout << "length is " << test2.length() << endl;
    cout << "remove from empty list: ";
    test2.remove(1);
    cout << "peek at empty list: ";
    test2.peek_front();
    cout << "pop_back from empty list: ";
    test2.pop_back();
    cout << "item_at(head) for empty list: ";
    test2.item_at(0);
    cout << "remove from empty list: ";
    test2.insert(2, 3);
    cout << endl;
    
    
    
    
    cout<<"\n\n--------------------------------------------------\n";
    cout<<"-------------------- SDAL ------------------------\n";
    cout<<"--------------------Test 3------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    
    SDAL<int> test3;
    
    //----- errors
    cout << "Pre-initialization error tests:" << endl;
    cout << "Try pop_back: ";
    test3.pop_back();
    cout << "Try print: ";
    test3.print(cout);
    cout << "Try replace: ";
    test3.replace(1, 0);
    cout << "Try clear: ";
    test3.clear();
    
    //------ fill linked list
    test3.push_back(12);
    test3.push_back(13);
    test3.push_front(11);
    test3.push_front(6);
    test3.push_front(9);
    test3.push_back(14);
    test3.push_front(8);
    
    cout<<"\n---------------Pushing front and back---------------" << endl;
    //8 9 6 11 12 13 14
    test3.print(cout);
    
    cout<<"---------------Removing---------------" << endl;
    cout << "--Removing " << test3.pop_front() << " from front, " << test3.remove(posRemove) << " from position " << posRemove << ", and " << test3.pop_back() << " from back" << endl;
    test3.print(cout);
    
    cout<<"---------------Inserting---------------" << endl;
    cout << "--Inserting " << insert1 << " to front, " << insert2 << " to index " << posInsert << ", inserting " << insert3 << " to back, and inserting " << insert4 << " to back" << endl;
    test3.push_front(insert1);
    test3.insert(insert2, posInsert);
    test3.push_back(insert3);
    test3.push_back(insert4);
    test3.print(cout);
    
    cout<<"---------------Replacing---------------" << endl;
    cout << "--Replacing position " << posReplace << " with " << replace1 << endl;
    test3.replace(replace1, posReplace);
    test3.print(cout);
    
    cout<<"---------------Peeking---------------" << endl;
    cout << "--Peek front is " << test3.peek_front() << ", peek at position " << posPeek << " is " << test3.item_at(posPeek) << ", and peek back is " << test3.peek_back() << endl;
    
    cout<<"---------------Length---------------" << endl;
    cout << "Length of list is " << test3.length() << endl;
    test3.print(cout);
    
    cout<<"---------------Contents---------------" << endl;
    //contentsArray = new int(test3.length()); //lengthInt
    lengthInt = static_cast<int>(test3.length());
    contentsArray = new int(lengthInt);
    contentsArray = test3.contents();
    for(int i = 0; i < lengthInt; ++i)
    {
        cout << contentsArray[i] << " ";
    }
    cout << endl;

    cout<<"---------------Contains---------------" << endl;
    cout << "Contains 99 is " << test3.contains(99, equals_function) << endl;
    cout << "Contains 88 is " << test3.contains(88, equals_function) << endl;
   
    cout<<"---------------Clearing---------------" << endl;
    test3.clear();
    test3.print(cout);
    cout << endl;
    
    cout<<"\n---------------Error handling test---------------" << endl;
    cout << "length is " << test3.length() << endl;
    cout << "remove from empty list: ";
    test3.remove(1);
    cout << "peek at empty list: ";
    test3.peek_front();
    cout << "pop_back from empty list: ";
    test3.pop_back();
    cout << "item_at(head) for empty list: ";
    test3.item_at(0);
    cout << "remove from empty list: ";
    test3.insert(2, 3);
    cout << endl;
    
    
    
    cout<<"\n\n--------------------------------------------------\n";
    cout<<"-------------------- CBL ------------------------\n";
    cout<<"--------------------Test 4------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    
    CBL<int> test4(10);
    
    //----- errors
    cout << "Pre-initialization error tests:" << endl;
    cout << "Try pop_back: ";
    test4.pop_back();
    cout << "Try print: ";
    test4.print(cout);
    cout << "Try replace: ";
    test4.replace(1, 0);
    cout << "Try clear: ";
    test4.clear();
    
    //------ fill linked list
    test4.push_back(12);
    test4.push_back(13);
    test4.push_front(11);
    test4.push_front(6);
    test4.push_front(9);
    test4.push_back(14);
    test4.push_front(8);
    
    cout<<"\n---------------Pushing front and back---------------" << endl;
    //8 9 6 11 12 13 14
    test4.print(cout);
    
    cout<<"---------------Removing---------------" << endl;
    cout << "--Removing " << test4.pop_front() << " from front" << endl;
    test4.print(cout);
    cout << "--Removing " << test4.remove(posRemove) << " from position " << posRemove << endl;
    test4.print(cout);
    cout << "--Removing " << test4.pop_back() << " from back" << endl;
    test4.print(cout);
    /*
    cout << "--Removing " << test4.pop_front() << " from front, " << test4.remove(posRemove) << " from position " << posRemove << ", and " << test4.pop_back() << " from back" << endl;
    test4.print(cout);
     */
    
    cout<<"---------------Inserting---------------" << endl;
    cout << "--Inserting " << insert1 << " to front, " << insert2 << " to index " << posInsert << ", inserting " << insert3 << " to back, and inserting " << insert4 << " to back" << endl;
    test4.push_front(insert1);
    test4.insert(insert2, posInsert);
    test4.push_back(insert3);
    test4.push_back(insert4);
    test4.print(cout);
    
    cout<<"---------------Replacing---------------" << endl;
    cout << "--Replacing position " << posReplace << " with " << replace1 << endl;
    test4.replace(replace1, posReplace);
    test4.print(cout);
    
    cout<<"---------------Peeking---------------" << endl;
    cout << "--Peek front is " << test4.peek_front() << ", peek at position " << posPeek << " is " << test4.item_at(posPeek) << ", and peek back is " << test4.peek_back() << endl;
    
    cout<<"---------------Length---------------" << endl;
    cout << "Length of list is " << test4.length() << endl;
    test4.print(cout);
    
    cout<<"---------------Contents---------------" << endl;
    //contentsArray = new int(test3.length()); //lengthInt
    lengthInt = static_cast<int>(test4.length());
    contentsArray = new int(lengthInt);
    contentsArray = test4.contents();
    for(int i = 0; i < lengthInt; ++i)
    {
        cout << contentsArray[i] << " ";
    }
    cout << endl;
    
    cout<<"---------------Contains---------------" << endl;
    cout << "Contains 99 is " << test4.contains(99, equals_function) << endl;
    cout << "Contains 88 is " << test4.contains(88, equals_function) << endl;
    
    cout<<"---------------Clearing---------------" << endl;
    test4.clear();
    test4.print(cout);
    cout << endl;
    
    cout<<"\n---------------Error handling test---------------" << endl;
    cout << "length is " << test4.length() << endl;
    cout << "remove from empty list: ";
    test4.remove(1);
    cout << "peek at empty list: ";
    test4.peek_front();
    cout << "pop_back from empty list: ";
    test4.pop_back();
    cout << "item_at(head) for empty list: ";
    test4.item_at(0);
    cout << "remove from empty list: ";
    test4.insert(2, 3);
    cout << endl;
    
    
    cout<<"\n--------------------------------------------------\n";
    cout<<"--------------------SSLL Iterator------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    SSLL<int> b;
    b.push_back(20);
    b.push_back(-5);
    
    
    for(auto ptr = b.begin(); ptr != b.end(); ++ptr)
    {
        cout << *ptr << endl;
    }
    
    
    cout<<"\n--------------------------------------------------\n";
    cout<<"--------------------PSLL Iterator------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    PSLL<int> c;
    c.push_back(20);
    c.push_back(-5);
    
    
    for(auto ptr = c.begin(); ptr != c.end(); ++ptr)
    {
        cout << *ptr << endl;
    }
    
    cout<<"\n--------------------------------------------------\n";
    cout<<"--------------------SDAL Iterator------------------------";
    cout<<"\n--------------------------------------------------\n\n";
    SDAL<int> d;
    d.push_back(20);
    d.push_back(-5);
    
    
    for(auto ptr = d.begin(); ptr != d.end(); ++ptr)
    {
        cout << *ptr << endl;
    }


    
    cout << "Working" << endl;
    
    
    return 0;
}
