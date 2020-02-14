#include <core.hpp>
#include <vessel.hpp>
#include <bullet.hpp>
#include <time.h>

int main()
{
    Core core(sf::VideoMode(1920, 1080), 8);
    sf::Clock clock;
    long int time;
    struct timespec wait_time;
    long int loopy = 0;
    long int last = clock.getElapsedTime().asMicroseconds();

    wait_time.tv_sec = 0;
    while (core.isAlive()) {
        core.Update();
        core.Events();
        time = clock.getElapsedTime().asMicroseconds();
        loopy++;
        if (last > time) {
            wait_time.tv_nsec = (last - time) * 1000;
            nanosleep(&wait_time, NULL);
        }
        last += 1000000 / 60;
    }
    printf("Global framerate : %i fps\n", (int) (1000000 * loopy / time + 0.5));
    return (0);
}
