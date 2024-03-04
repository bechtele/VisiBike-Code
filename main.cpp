#include "mbed.h"
#include "smart_bike_system.h"

// main() runs in its own thread in the OS
int main()
{
    smartbikesystemInit();
    while (true) {
        smartbikesystemUpdate();
    }
}

