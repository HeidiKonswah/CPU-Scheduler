#include <list>
#include <bits/stdc++.h>

using namespace std;

bool compareArrival(Process p1, Process p2){
    return p1.arrival<p2.arrival; 
}

vector<vector<Process> > FCFS(vector<Process>& processes, int& finishTime, float& cpuUtl, map<int, int>& pStats){
    vector<vector<Process> > state;
    list<Process> blockedQ; 
    list<Process> readyQ; 
    Process* running = nullptr;
    int cycle = 0; 
    float busyCyclesNum = 0;

    //run process with smallest arrival time 
    sort(processes.begin(), processes.end(), compareArrival); 
    // running = &processes.front();
    //loop as long as there's still processes running or in Q 
    while(running || !readyQ.empty() || !blockedQ.empty() || processes[0].arrival >= cycle){
        vector<Process> tempState;
        bool busyCycle = false;
        
        //check if current process is finished 
        if(running && !running->IO && !running->CPU){
            running->setFinishCycle(cycle - 1);
            pStats[running->id] = running->finishCycle - running->arrival + 1;
            running->status = "Terminated"; 
            running = NULL;
           
        } // check if current process needs IO 
        else if(running && !running->CPU &&running->IO){             
            blockedQ.push_back(*running);
            running->status = "blocked";
            running = NULL;
            
        }
        //check for newly arrived processes
        for(auto i=processes.begin(); i!=processes.end(); i++){ 
            if(i->arrival == cycle) {
                readyQ.push_back(*i);
                i->status = "ready";
            }
        }
        //handle blocked
        if(!blockedQ.empty()){  
            auto i = blockedQ.begin();
            while(i != blockedQ.end()){
                //decrease IO of blocked process by 1
                //when it's 0, remove from blocked and add to ready
                if(i->IO == 0){     
                    i->status = "ready";
                    readyQ.push_back(*i);
                    blockedQ.erase(i++); 
                }else{
                    i->IO--; 
                    i++;
                }
            }
        }
 
        //if nothing is running, run next in ready Q and remove it from Q
        if(!running && !readyQ.empty()){
            readyQ.sort();
            running = &readyQ.front();
            running->status = "running";
            readyQ.pop_front();
        }

        //dec CPU time of current process
        if(running && running->CPU){
            running->CPU--; 
        }

        //keep track of current state
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

        //update state
        state.push_back(tempState);

        busyCyclesNum = busyCycle? busyCyclesNum+1 : busyCyclesNum;
        cycle++;
    }
    finishTime = cycle-1;
    cpuUtl = (float)busyCyclesNum / ((float)state.size()-1);
    return state;
}

