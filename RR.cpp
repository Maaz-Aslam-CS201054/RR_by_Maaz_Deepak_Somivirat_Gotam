#include <iostream>
#include <iomanip> // for std::setw
using namespace std;
struct Process
{
    int id; //process id
    int AT; //Arival time
    int BT; //Burst time
    int CT; //Completion time
    int TAT; //Turn Around Time
    int WT; //Wait Time
};


void calc_time(Process processes[], int n, int quantum)
{   // we are gonna initialize variable known as Remaining Time
    int remainingTime[n];
    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].BT;
    }
    // initializing current time
    int currentTime = 0;
    //meaning we set an indicator no process has has been completed
    bool allDone = false; 
    while (!allDone)
    {
        //indicating all processes have been ran
        allDone = true;

        for (int i = 0; i < n; i++)
        {
            //VERY IMPORTANT CONDITION IF NOT LAGAI THEN WHILE LOOP BECOMES INFINITE
            if(remainingTime[i] > 0)
            {
                allDone = false;  
                if (remainingTime[i] > quantum)
                {
                    currentTime = currentTime + quantum;
                    remainingTime[i] = remainingTime[i] - quantum;
                }
                else
                {
                    currentTime = currentTime + remainingTime[i];
                    processes[i].CT = currentTime;
                    remainingTime[i] = 0;
                } 
            }
        }
        
    }
    



}


void calc_TAT(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].TAT = processes[i].CT - processes[i].AT;
    }
    
}

void calc_WT(Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].WT = processes[i].TAT - processes[i].BT;
    }
}


void print_Table(Process processes[], int n) {
    cout << "------------------------------------------------------------------------------------------\n";
    cout << "| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |\n";
    cout << "------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << "| " << setw(7) << processes[i].id << " | "
             << setw(12) << processes[i].AT << " | "
             << setw(10) << processes[i].BT << " | "
             << setw(15) << processes[i].CT << " | "
             << setw(15) << processes[i].TAT << " | "
             << setw(12) << processes[i].WT << " |\n";
    }

    cout << "---------------------------------------------------------------\n";
}

int main(int argc, char **argv)
{
    int n,quantum;

    cout << "Enter the number of Processes: ";
    cin >> n;
    cout << endl;
    cout << "Enter the time Quantum: ";
    cin >> quantum;
    cout << endl;

    Process processes[n];
    cout << "Enter Process Details: \n";
    for (int i = 0; i < n; i++)
    {
        cout << "Process " << i+1 << ": \n";
        processes[i].id = i + 1;
        cout << "   Arrival Time: ";
        cin >> processes[i].AT;
        cout << "   Burst Time: ";
        cin >> processes[i].BT;
    }
    calc_time(processes, n, quantum);
    calc_TAT(processes, n);
    calc_WT(processes, n);

    cout << "\nRound Robin (RR) Scheduling results:\n";

    print_Table(processes, n);

    return 0;
}