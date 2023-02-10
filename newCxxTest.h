/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   newCxxTest.h
 * Author: hloi
 *
 * Created on January 26, 2018, 3:52 PM
 */

#ifndef NEWCXXTEST_H
#define NEWCXXTEST_H
#include <string>
#include "list.h"
#include <cxxtest/TestSuite.h>
//Include your classes header file(s) below and uncomment.
//#include "myClass.h"
using KW::list;
using std::string;

class newCxxTest : public CxxTest::TestSuite {
public:

    //All tests should start with the word 'test' followed by
    //the name of the function being tested.

    void test_list_begin() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        list<int>::iterator iter = a_list.begin();
        for (int i = 0; i < 10; i++) {
            TS_ASSERT_EQUALS(*iter, i);
            ++iter;  // pre-increment
        }       
    }
    
    void test_list_end() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        list<int>::iterator iBegin = a_list.begin();
        list<int>::iterator iEnd = a_list.end();
        int i = 0;
        for (; iBegin != iEnd; ++iBegin) {
            TS_ASSERT_EQUALS(*iBegin, i++);
        }       
    }
    void test_list_find() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        
        list<int>::iterator pos=a_list.find(5);
        
        if (*pos) {
            TS_ASSERT(true);
        }
        else {
            TS_ASSERT(false);
        }
    }
    void test_list_erase() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        
        list<int>::iterator pos=a_list.find(5);
        list<int>::iterator p = a_list.erase(pos);
        TS_ASSERT_EQUALS(*p, 6);
        --p;
        TS_ASSERT_EQUALS(*p, 4);
    }
    
    void test_list_insert() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        
        list<int>::iterator pos=a_list.find(5);
        list<int>::iterator p = a_list.insert(pos,10);
        TS_ASSERT_EQUALS(*p, 10);
        --p;  // predecrement
        TS_ASSERT_EQUALS(*p, 4);
        TS_ASSERT_EQUALS(*pos, 5);
    }
 
    void test_list_remove() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        
        a_list.remove(5);
        list<int>::iterator iter=a_list.find(5);
        TS_ASSERT_EQUALS(iter, a_list.end());
    }
    
    void test_list_front_end() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<int> a_list;
        for (int i = 0; i < 10; i++)
            a_list.push_back(i);
        int i = 0;
        TS_ASSERT_EQUALS(i, a_list.front());
        i = 9;
        TS_ASSERT_EQUALS(i, a_list.back());
    }
    
    void test_list_string() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<string> a_list;
        const char* names[] = {"Tom", "Dick", "Harry", "Sharon", "Sam"};
        
        for (int i = 0; i < 5; i++)
            a_list.push_front(names[i]);
        
        TS_ASSERT_EQUALS(names[4], a_list.front());
        
    }
    void test_list_pop_front() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<string> a_list;
        const char* names[] = {"Tom", "Dick", "Harry", "Sharon", "Sam"};
        
        for (int i = 0; i < 5; i++)
            a_list.push_front(names[i]);
        
        a_list.pop_front();
        TS_ASSERT_EQUALS(names[3], a_list.front());
        
    }
    
    void test_list_pop_back() {
        //Use TS_ASSERT_EQUALS(Result, ExpResult) to test your functions. 
        list<string> a_list;
        const char* names[] = {"Tom", "Dick", "Harry", "Sharon", "Sam"};
        
        for (int i = 0; i < 5; i++)
            a_list.push_front(names[i]);
        
        a_list.pop_back();
        TS_ASSERT_EQUALS(names[1], a_list.back());
        
    }
    
};
#endif /* NEWCXXTEST_H */

