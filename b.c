#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int main ()
{
    struct  timeval m;

    int i =  0;
    while (i < 10)
    {
        gettimeofday(&m, NULL);
        printf("%ld\n", ((m.tv_usec / 1000) + (m.tv_sec * 1000)));
        usleep(1000);
        i++;
    }
}