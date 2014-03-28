#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <list>
#include <iostream>
#include <string.h>
#include "mem_tracer.h"

#ifdef MEM_TRACE
#define new     TRACE_NEW
#define delete  TRACE_DELETE
#endif

using namespace std;

class A {
public:
    A() {}
    ~A() {}

private:
    char ch[1024];
};

class TestObj {
public:	
	TestObj() { 
        a = new A[1024];
    }

    virtual ~TestObj() {
        delete[] a;
    };

    void show() {}

private:
    A *a; 
};

void* callback(void *) {
   int i = 0; 
    while(i < 100) {
        new char[1024];
        sleep(1);
    }

}

int main() {

    list<TestObj*> lst;
    lst.clear();

    int d = 0;
    while(d < 30) {

    	TestObj* pob = new TestObj;	
        lst.push_back(pob);
        sleep(1);
        d++;
    }

    d = 0;
    list<TestObj*>::iterator iter;
    for(iter = lst.begin(); iter != lst.end(); iter++) {
        delete *iter;
        sleep(1);
        if(d++ == 10) {
            break;
        }
    }

    //pObAry->TestObj();
/*	
    pthread_t pid;
    pthread_create(&pid, NULL, callback, NULL);

    list<unsigned char*> memptrs;

    int i = 0; 
    
    while(i++ < 30) {
        unsigned char* ptr = (unsigned char*) new char[1024];        
        memptrs.push_back(ptr);
        cout << "i = " << i << endl;
        sleep(1);
    }
 
    list<unsigned char*>::iterator iter;
    for(iter = memptrs.begin(); iter != memptrs.end(); iter++) {
        delete  (*iter);
        sleep(1);
    }
    
    pthread_join(pid, NULL); 
*/
	return 0;
}