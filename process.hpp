#include <string>

class Process {
    public: 
        int id, CPU, IO, arrival; 
        int finishCycle;
        int quanta; 
        std::string status = "waiting";
        Process(int id, int CPU, int IO, int arrival): id(id), CPU(CPU), IO(IO), arrival(arrival){ }
        ~Process() { }
        bool operator<(const Process& p){
            return id < p.id; 
        }
        bool operator==(const Process& p){
            return id == p.id;
        }
        void setFinishCycle(int n){
            finishCycle = n;
        }
};