#include "mbed.h"
#include "smart_bike_system.h"
#include "arm_book_lib.h" 

// main() runs in its own thread in the OS
int main()
{
    smartbikesystemInit();
    while (true) {
        smartbikesystemUpdate();
        delay(TIME_INCREMENT_MS);
    }
}

