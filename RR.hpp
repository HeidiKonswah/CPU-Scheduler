#include <vector> 
#include <map>
#include <list>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

vector<vector<Process> > roundRobin(vector<Process>& processes, int quantumTime, int& finish, float& utl, map<int, int>& stats){
    vector<vector<Process> > state;
    list<Process> blockedQ; 
    list<Process> readyQ; 
    Process* running = nullptr;
    int cycle = 0;
    int numOfProcesses = processes.size();
   
    //run process with smallest arrival time 
    sort(processes.begin(), processes.end(), compareArrival); 

    while(running || !readyQ.empty() || !blockedQ.empty() || processes[0].arrival >= cycle){
        int tempCycl = quantumTime; 
        float busyCyclesNum = 0;
        vector<Process> tempState;
        bool busyCycle = false;
        while(tempCycl){
            if(running && running->quantumCycles == quantumTime){
                //suspend and add to Q
            }
            //if running is finished during in
            if(running && !running->CPU && running->IO){
                terminate(running, cycle);
                //find next
                continue; 
            }else if(running && !running->CPU && running->IO){
                //block 
                //find next
            }

            //if new process arrives/ready
            checkNewArrivals(processes, readyQ, cycle);
        
            //handle blocked 
            handleBlocked(blockedQ, readyQ);
            //select next 
            //if nothing is running, run next in ready Q and remove it from Q
            if(!running && !readyQ.empty()){
                readyQ.sort();
                running = &readyQ.front();
                running->status = "running";
                readyQ.pop_front();
                tempCycl = quantumTime; 
                continue;
            }
            //update cpu cycle 
            //dec CPU time of current process
            if(running && running->CPU){
                running->CPU--; 
            }

            cycle++; 
            tempCycl--;
        }
        if(running) {
            tempState.push_back(*running); 
            busyCycle = true;
        }
        for(auto i=blockedQ.begin(); i!=blockedQ.end(); i++){
            tempState.push_back(*i); 
            if (i->status == "running") busyCycle = true;
        }
        for(auto i=readyQ.begin(); i!=readyQ.end(); i++){
            tempState.push_back(*i); 
            if (i->status == "running") busyCycle = true;
        }
        state.push_back(tempState);
        busyCyclesNum = busyCycle? busyCyclesNum+1 : busyCyclesNum;

        cycle++;
    }
    return state;
}