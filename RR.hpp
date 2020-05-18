using namespace std;

vector<vector<Process> > roundRobin(vector<Process>& processes, int& finishTime, float& cpuUtl, map<int, int>& pStats, int quantumTime){
    vector<vector<Process> > state;
    list<Process> blockedQ; 
    list<Process> readyQ; 
    Process* running = nullptr;
    int cycle = 0;
    float busyCyclesNum = 0;
   
    sort(processes.begin(), processes.end(), compareArrival); 

    while(running || !readyQ.empty() || !blockedQ.empty() || processes[0].arrival >= cycle){
        bool busyCycle = false;
        vector<Process> tempState;
        //check if current process is finished
        if(running && !running->IO && !running->CPU ){
            running->setFinishCycle(cycle - 1);
            pStats[running->id] = running->finishCycle - running->arrival + 1;
            running->status = "Terminated"; 
            running = NULL;
        }//if current process exceeds the quantum time and still needs CPU, move to ready Q
        else if(running && !running->quanta && running->CPU){
            readyQ.push_back(*running);
            running->status = "ready";
            running = NULL;
        }//if current process exceeds the quantum time and needs IO, move to blocked Q
        else if(running && !running->quanta && running->IO){
            blockedQ.push_back(*running);
            running->status = "blocked";
            running = NULL;
        }//if current process is still within the quantum time but needs IO, move to blocked
        else if(running && !running->CPU &&  running->IO){
            blockedQ.push_back(*running);
            running->status = "blocked";
            running = NULL;
        }

        // check for newly arrived processes, add them to ready Q
        sort(processes.begin(), processes.end(), [](Process a, Process b) {
            return a.id < b.id;
        });
        for(auto i=processes.begin(); i!=processes.end(); i++){ 
            if(i->arrival == cycle) {
                readyQ.push_back(*i);
                i->status = "ready";
            }
        }
    
        // handle blocked processes
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

        //if nothing is running, run next process in ready Q
        if(!running && !readyQ.empty()){
            running = &readyQ.front();
            //set its initial quanta to the allowed quantum time
            running->quanta = quantumTime;
            running->status = "running";
            readyQ.pop_front();
        }

        //if running process needs CPU, update its value and decrement its quanta
        if(running && running->CPU){
            running->CPU--; 
            running->quanta--;
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