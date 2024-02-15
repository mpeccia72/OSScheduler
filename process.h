
#include <vector>

using namespace std;

// data structure representing a process
struct Process {

    int number; // process number
    int readyTime; // time in miliseconds when process will be ready
    int status; // WAITING = 0, READY = 1, RUNNING = 2
    int state; // INTERACTIVE = 0, REAL-TIME = 1
    int cpu; // total time of cpu requests
    int tty;
    int disk; // total time of disk requests
    int executionTime; // time the process begins in the running state (can change if interactive)
    int terminationTime; // time that process terminates
    int deadline; // only applies to real-time
    bool recycled; // useful for algorithm

    Process();
    void clear(); // clears data (useful for file input)

};