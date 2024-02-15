
#include "process.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

// This class is an os scheduler that can have a proccesses added to it 
// and simulate run time
class OSScheduler {

    std::queue<Process> interactiveQueue; // interactive queue of ready processes
    std::queue<Process> realTimeQueue; // real-time queue of ready processes
    std::vector<Process> mergedQueue; // merged queue (FCFS disk)

    Process* cpuProcess; // process allocated to the cpu

    // private functions for sorting lists by arrival time
    bool compareByStartTime(const Process&, const Process&);
    void sortProcessesByReadyTime();

    // important vars
    int totalDiskAccesses, realTimeProcesses, realTimeCompleted, 
        interactiveCompleted, numberOfProcesses;

    public:
        OSScheduler();
        void addProcess(Process); // adds process to scheduler
        void simulate(); // simulation
        void printSummary();

};

