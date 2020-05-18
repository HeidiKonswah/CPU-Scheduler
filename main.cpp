#include <iostream>
#include <vector>
#include <map> 
#include "readProcesses.hpp"
#include "FCFS.hpp"
#include "writeOutput.hpp"
#include "RR.hpp"

using namespace std;
void getMode(int& m){
    cout << "Enter 0 for FCFS\nEnter 1 for Round Robin";
    cin >> m;
}

int main(){
    vector<Process> processes = readProcesses();
    int finishTime; 
    float utlization;
    vector<vector<Process> > stats;
    map<int, int> processStats; 
    int mode; 

    getMode(mode);
    try{ 
      if (mode != 0 && mode != 1) 
      { 
         throw mode;  
      } 
    } 
   catch (int mode) { 
      cout << "INVALID INPUT\n"; 
      getMode(mode); 
   } 
    
    if(mode){
        // exec round robin
        int qt=1;
        cout << "Enter quantum time: ";
        cin >> qt; 
        stats = roundRobin(processes, finishTime,utlization, processStats, qt);
    }else{
        stats = FCFS(processes, finishTime,utlization, processStats);
        writeOutput(stats, finishTime, utlization, processStats);
    }
    writeOutput(stats, finishTime, utlization, processStats);
    return 0;
}