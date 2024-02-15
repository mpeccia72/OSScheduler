
#include "process.h"

Process::Process() {
    readyTime = 0; 
    state = -1; // unassigned state
    recycled = false;
}

// clears process
void Process::clear() {
    readyTime = 0; 
    state = -1;
    disk = 0;
    cpu = 0;
    tty = 0;
}