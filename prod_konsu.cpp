#include <iostream>
#include <pthread.h>
#include "monitor.h"
#include <time.h>
#include "bufor.h"
#include <cstdlib>
#include <unistd.h>

using namespace std;

void *producer(void *param);
void *consumer(void *param);
int setId(void);

long int buff_size;
long int num_producer;
long int num_items;
bufor buf;

int main(int argc, char **argv)
{
    if(argc != 4)
    {
        cout << "ERROR: Podaj trzy argumenty wywołania" << endl;
        exit(1);
    }
    num_producer = strtol(argv[1], NULL, 0);
    buff_size = strtol(argv[2], NULL, 0);
    num_items = strtol(argv[3], NULL, 0);

    buf = bufor(buff_size);

    srand(time(NULL));

    pthread_t producers[num_producer];
    pthread_t consumers;

    for(int i = 0; i < num_producer; i++)
        pthread_create(&producers[i], NULL, producer, NULL);
    pthread_create(&consumers, NULL, consumer, NULL);

    for(int i = 0; i < num_producer; i++)
        pthread_join(producers[i], NULL);
    pthread_join(consumers, NULL);

    return 0;

}

int setId(void)
{
    static int id = 0;
    int temp = id;
    id++;
    return temp;
}

void *producer(void *param)
{
    int item;
    int id = setId();
    int i = 0;

    while(i < num_items)
    {
        sleep(rand() % 5 + 1);
        item = rand();
        buf.insert_item(item);
        //cout << "Producent nr " << id << " wyprodukowal produnkt nr " << item << endl;
        i++;
    }
}

void *consumer(void *param)
{
    int item;
    int i = 0;
    while(i < num_items * num_producer)
    {
        sleep(rand()%5 + 1);
        item = buf.remove_item();
        //cout << "Konsumer wyjal produnkt nr: " << item << endl;
        i++;
    }
}
