#include "monitor.h"
#include <queue>

using namespace std;

class bufor {
private:
    int *buf;
    int head, tail, lenght;
    int size;
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
    void pushBuf(int val)
    {
        buf[tail] = val;
        tail = (tail+1)%size;
        lenght++;
    }
    int popBuf(void)
    {
        int ret = buf[head];
        head = (head+1)%size;
        lenght--;
        return ret;
    }
    int sizeBuf(void)
    {
        return lenght;
    }
}
