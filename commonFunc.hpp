#include <vector> 
#include <map>
#include <list>
#include <queue>
#include <iostream>
#include <bits/stdc++.h>
#include <fstream> 
using namespace std;
bool compareArrival(Process p1, Process p2){
    return p1.arrival<p2.arrival; 
}

void terminate(Process* p, int crrntCycle){
    p->setFinishCycle(crrntCycle - 1);
    p->status = "Terminated"; 
    p = NULL;
}


void checkNewArrivals(vector<Process>& processes, list<Process>& readyQ, int crrntCycle){
    for(auto i=processes.begin(); i!=processes.end(); i++){ 
        if(i->arrival == crrntCycle) {
            readyQ.push_back(*i);
            i->status = "ready";
        }
    }
}

void handleBlocked(list<Process>& blockedQ, list<Process>& readyQ){
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
}