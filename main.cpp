#include "imports.hpp"

using namespace std;

void getMode(int& mode){
    cout << "Enter 0 for First-Come-First-Serve\nEnter 1 for Round Robin\n"; 
    cin >> mode;
}
int main(){
    int finishTime; 
    float utlization;
    vector<vector<Process> > stats;
    map<int, int> processStats; 
    int mode; 
    vector<Process> processes = readProcesses();

    //let user choose which algorithm to run
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
    //run chosen algorithm
    if(mode){
        //get quantum time 
        int qt=1; 
        cout << "Enter quantum time: ";
        while(qt <= 0){
            cin >> qt; 
        }
        stats = roundRobin(processes, qt, finishTime, utlization, processStats);

        }else{
            cout << "inside else" << endl;
            stats = FCFS(processes, finishTime,utlization, processStats);
        }   
        writeOutput(stats, finishTime, utlization, processStats);
    return 0;
}