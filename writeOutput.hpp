#include <fstream> 
#include <vector>
#include <map>
using namespace std; 

void writeOutput(vector<vector<Process> > stats, int finish, float utl, map<int, int> pStats){
    ofstream outputFile; 
    cout << "writing" << endl;
    outputFile.open("output.txt"); 
    outputFile << "====Scheduling simulation====" << endl; 
    int count = 0;
    for(auto i = stats.begin(); i!=stats.end();i++){
        outputFile << "Cycle #" << count << endl; 
        for(auto j = i->begin(); j!=i->end();j++){
            outputFile << "P#" << j->id;
            outputFile << " " << j->status << endl;
        }
        outputFile << "\n";
        count++; 
    }

    outputFile << "====Statistics====" << endl; 
    outputFile << "Finishing time: " << finish <<endl;
    outputFile << "CPU Utilization: " << utl << endl; 
    outputFile << "\n"; 
    for(auto i = pStats.begin(); i!=pStats.end(); i++){
        outputFile << "Turnaround of P#" << i->first << " = " << i->second << endl;
    }
    outputFile.close();
    cout << "written" << endl;
}