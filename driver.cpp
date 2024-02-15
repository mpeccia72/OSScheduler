/*
    Assignment: HW1
    Name: Michael Peccia
    Class: CS 302
    Student #: 388
    Due Date: 02/08/2023
    Short Description: Process Scheduler
*/

#include <iostream>
#include <fstream>
#include "os_scheduler.h"

using namespace std;

// reads input file to scheduler object
void readFile(OSScheduler& scheduler, ifstream& inputFile);

int main() {

    // object instantiation
    OSScheduler scheduler;

    // opens "input.txt"
    ifstream inputFile("input.txt"); 

    // closes program if "input.txt" fails to open
    if(!inputFile.is_open()) {
        cout << "File failed to open." << endl;
        exit(0);
        system("pause");
    }

    // file read to object
    readFile(scheduler, inputFile);

    scheduler.simulate();

    return 0; 

}

void readFile(OSScheduler& scheduler, ifstream& inputFile) {

    Process process;
    string line;
    int processNumber = 1;

    while(!inputFile.eof()) {

        getline(inputFile, line);
        int value;

        // interactive process
        if(line.substr(0, 11) == "INTERACTIVE") {

            // marks end of previous process and beginning of a new process
            if(process.state != -1) {
                scheduler.addProcess(process);
                process.clear();
                cout << "process above added" << endl;
            }
                
            process.state = 0; // interactive
            process.status = 0; // waiting
            process.readyTime = stoi(line.substr(12));
            process.number = processNumber++; // numbers process        

            cout << "Interactive " << endl;

        }

        // real-time process
        else if(line.substr(0, 9) == "REAL-TIME") {

            // marks end of previous process and beginning of a new process
            if(process.state != -1) {
                scheduler.addProcess(process);
                process.clear();
                cout << "process above added" << endl;
            } 

            process.state = 1; // real-time
            process.status = 0; // waiting
            process.readyTime = stoi(line.substr(10));
            process.number = processNumber++; // numbers process  

            cout << "Real-Time " << endl;

        }

        else if(line.substr(0, 3) == "CPU") {
            // cumulatively adds total time of cpu requests to process data strucutre
            process.cpu += stoi(line.substr(4));
            cout << "CPU " << stoi(line.substr(4)) << endl;
        }

        else if(line.substr(0, 3) == "TTY") {
            // cumulatively adds total time of terminal requests to process data strucutre
            process.tty += stoi(line.substr(4));
            cout << "TTY " << stoi(line.substr(4)) << endl;
        }

        else if(line.substr(0, 4) == "DISK") {
            // cumulatively adds total time of disk requests to process data strucutre
            process.disk += stoi(line.substr(5));
            cout << "DISK " << stoi(line.substr(5)) << endl;
        }

        else if(line.substr(0, 8) == "DEADLINE") {
            // sets deadline for real-time
            process.deadline = stoi(line.substr(9));
            cout << "DEADLINE " << stoi(line.substr(9)) << endl;
        }

    }

    scheduler.addProcess(process);
    process.clear();
    cout << "process above added" << endl << endl << endl;

}