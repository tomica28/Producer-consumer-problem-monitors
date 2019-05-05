#include "monitor.h"
#include <queue>
#include <iostream>

using namespace std;

class bufor: public Monitor {
private:
    int *buf;
    int head, tail, lenght;
    int size;

    Condition full, empty;

    void pushBuf(int val)
    {
        buf[tail] = val;
        tail = (tail+1)%size;
        lenght++;
        cout << "Wlozono produnt nr " << val << endl;
    }
    int popBuf(void)
    {
        int ret = buf[head];
        head = (head+1)%size;
        lenght--;
        cout << "Wyjeto produntk nr " << ret << endl;
        return ret;
    }

public:
    bufor()
    {
        head = 0;
        tail = 0;
        lenght = 0;
        size = 0;
    }
    bufor(int asize)
    {
        buf = new int [asize];
        size = asize;
        head = 0;
        tail = 0;
        lenght = 0;
    }
    bufor(const bufor& other)
    {
        buf = new int[other.size];
        head = other.head;
        tail = other.tail;
        lenght = other.lenght;
        size = other.size;
        for(int i = 0; i < other.size; i++)
            buf[i] = other.buf[i];
    }
    bufor& operator= (const bufor& other)
    {
        if(this != &other)
        {
            buf = new int[other.size];
            head = other.head;
            tail = other.tail;
            lenght = other.lenght;
            size = other.size;
            for(int i = 0; i < other.size; i++)
            buf[i] = other.buf[i];
        }
        return *this;
    }
    ~bufor()
    {
        delete [] buf;
    }
    void insert_item(int item)
    {
        enter();
        if(lenght == size)
            wait(empty);
        pushBuf(item);
        if(lenght == 1)
            signal(full);
        leave();
    }
    int remove_item(void)
    {
        enter();
        if(lenght == 0)
            wait(full);
        int ret = popBuf();
        if(lenght == size - 1)
            signal(empty);
        leave();
        return ret;

    }
};


