
#include <iostream>
#include "os_scheduler.h"

// constructor
OSScheduler::OSScheduler()
{
    totalDiskAccesses = 0;
    numberOfProcesses = 0;
    realTimeCompleted = 0;
}

/* helper function to sortProcessesByReadyTime()
bool compareByStartTime(const Process &a, const Process &b)
{
    return a.readyTime < b.readyTime;
}

// sorts processes by ready time
void OSScheduler::sortProcessesByReadyTime()
{
    std::sort(mergedQueue.begin(), mergedQueue.end(), compareByStartTime);
}*/

// adds process to scheduler
void OSScheduler::addProcess(Process process)
{
    mergedQueue.push_back(process);
}

// returns the simulation time
void OSScheduler::simulate()
{

    int currentFinishTime = 0; // time frame that the current running process finishes
    int preemptTime = 0; // total amount of time all interactive process ran on cpu before being pre-empted
    int currentDeadline = 0; // tracks the time to terminate a current real-time process
    int i = 0; // i represents 1 ms
    int index = 0; 
    bool restart = false; // used to see if multiple events happen at the same time frame

    while (i < 200000) // program simulates for 200 seconds
    {

        // if real-time process fails to complete by deadline, it's kicked off of cpu
        if(i == currentDeadline && i != 0) {
            cout << "Process #" << cpuProcess->number << " [REAL-TIME] has been terminated at " 
                 << i << "ms on the CPU" << endl;
            cpuProcess = NULL;
            realTimeCompleted--;
        }

        // current process on cpu finishes
        if(currentFinishTime == i && i != 0) {
            if(cpuProcess->state == 0) {
                cout << "Process #" << cpuProcess->number << " [INTERACTIVE] has finished at " 
                 << i << "ms on the CPU" << endl;
            }
            else {
                cout << "Process #" << cpuProcess->number << " [REAL-TIME] has finished at " 
                 << i << "ms on the CPU" << endl;
                currentDeadline = 0;
            } 
            cpuProcess == NULL;
            currentFinishTime = 0;
        }

        // checks to see if any real-time or interactive processes are ready to queue in this time frame
        if (i == mergedQueue[index].readyTime)
        {
            // status set to ready
            mergedQueue[index].status = 1;

            // added to respective queue
            if (mergedQueue[index].state == 0)
                interactiveQueue.push(mergedQueue[index]);
            else
                realTimeQueue.push(mergedQueue[index]);

            index++;
            restart = true;
        }

        // executes if real-time queue contains processes
        if (!realTimeQueue.empty())
        {

            // checks if cpu is free or occupied by interactive
            if (cpuProcess == NULL || cpuProcess->state == 0)
            {

                // interactive process is occupied in cpu and it's pre-empted
                if (cpuProcess->state == 0)
                {
                    Process savedProcess = *cpuProcess;

                    // will substract from total time at end
                    preemptTime += i - savedProcess.executionTime;

                    // queues back to interactive queue
                    interactiveQueue.push(savedProcess);

                    cout << "Process #" << savedProcess.number << " [INTERACTIVE] has been pre-empted at " 
                         << i << "ms on the CPU" << endl;
                }

                // copying process from real time queue
                Process newProcess = realTimeQueue.front();
                currentDeadline = newProcess.deadline + i;

                // current CPU process is set
                cpuProcess = &newProcess;

                // remove from queue
                realTimeQueue.pop();

                cout << "Process #" << newProcess.number << " [REAL-TIME] has been executed at " 
                         << i << "ms on the CPU" << endl;
                
                currentFinishTime = i + cpuProcess->cpu; // time cpu process will finish

                realTimeCompleted++; // will be decremented if terminated

            }
        }

        // interactive processes are ready and no real time processes are ready and cpu isn't occupied
        else if (!interactiveQueue.empty() && cpuProcess == NULL) {

            // copying process
            Process newProcess = interactiveQueue.front();

            // tracks what time process executes
            newProcess.executionTime = i;

            // current CPU process is set
            cpuProcess = &newProcess;

            currentFinishTime = i + cpuProcess->cpu; // time cpu process will finish

            // remove from queue
            interactiveQueue.pop();

            cout << "Process #" << cpuProcess->number << " [INTERACTIVE] has been executed at " 
                 << i << "ms on the CPU" << endl;
        }

        // FCFS Disk
        for(int i = 0; i < mergedQueue.size(); i++) {

            /*
                I ran out of time but the code here will be similar above except
                real-time and interactive share the same properties            
            */
        }

        if(restart == true)
            restart = false;
        else
            i++;
            

    }
}

void OSScheduler::printSummary() {
    cout << "Real-time processes completed: " << realTimeCompleted << endl;
    cout << "Percentage of real-time that missed deadline: " 
         << static_cast<float>(realTimeCompleted)/static_cast<float>(realTimeProcesses)*100 << "%.";
    cout << "Interactive processes completed: " << interactiveCompleted << endl;
}