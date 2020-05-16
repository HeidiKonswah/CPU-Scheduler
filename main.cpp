#pragma once
#include <iostream>
#include <fstream> 
#include <vector>
#include <map> 
#include "readProcesses.hpp"
#include "FCFS.hpp"
#include "writeOutput.hpp"
#include "RR.hpp"

using namespace std;

int main(){
    vector<Process> processes = readProcesses();
    int finishTime; 
    float utlization;
    vector<vector<Process> > stats;
    map<int, int> processStats; 
    int mode; 

    cout << "Enter 0 for First-Come-First-Serve\nEnter 1 for Round Robin\n"; 
    if(mode){
        // exec round robin
    }else{
        stats = FCFS(processes, finishTime,utlization, processStats);
        writeOutput(stats, finishTime, utlization, processStats);
    }
    return 0;
}