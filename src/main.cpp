#include "process.h"
#include "scheduler.h"
#include "ui.h"
#include <iostream>
#include <vector>
#include <limits>
#include <unordered_set>

void inputProcesses(std::vector<Process> &processes)
{
    int n;

    while (true)
    {
        std::cout << "Enter the number of processes: ";

        if (!(std::cin >> n))
        {
            std::cout << "\nInvalid input! Please enter a number.\n\n";

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        if (n <= 0)
        {
            std::cout << "\nNumber of processes must be greater than 0.\n\n";
            continue;
        }

        break;
    }

    std::unordered_set<int> usedPID;

    for (int i = 0; i < n; ++i)
    {
        int pid, arrival, burst, priority;

        std::cout << "\n=========================================\n";
        std::cout << "          PROCESS " << i + 1 << " DETAILS\n";
        std::cout << "=========================================\n";

        // PID
        while (true)
        {
            std::cout << "PID           : ";
            std::cin >> pid;

           
 
            if (std::cin.fail())
            {
                std::cout << "Invalid PID.\n";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
             if (pid <= 0)
           {
                 std::cout << "PID must be greater than 0.\n";
                 continue;
            }

            if (usedPID.count(pid))
            {
                std::cout << "PID already exists. Enter a unique PID.\n";
                continue;
            }

            usedPID.insert(pid);
            break;
        }

        // Arrival Time
        while (true)
        {
            std::cout << "Arrival Time  : ";
            std::cin >> arrival;

            if (std::cin.fail())
            {
                std::cout << "Invalid arrival time.\n";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (arrival < 0)
            {
                std::cout << "Arrival time cannot be negative.\n";
                continue;
            }

            break;
        }

        // Burst Time
        while (true)
        {
            std::cout << "Burst Time    : ";
            std::cin >> burst;

            if (std::cin.fail())
            {
                std::cout << "Invalid burst time.\n";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (burst <= 0)
            {
                std::cout << "Burst time must be greater than 0.\n";
                continue;
            }

            break;
        }

        // Priority
        while (true)
        {
            std::cout << "Priority      : ";
            std::cin >> priority;

            if (std::cin.fail())
            {
                std::cout << "Invalid priority.\n";

                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (priority <= 0)
            {
                std::cout << "Priority must be greater than 0.\n";
                continue;
            }

            break;
        }

        processes.emplace_back(pid, arrival, burst, priority);
    }
}

int main()
{
    std::vector<Process> processes;
    inputProcesses(processes);

    std::cout << "\nSelect Scheduling Algorithm:\n";
    std::cout << "1. First Come First Serve (FCFS)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "3. Round Robin (RR)\n";
    std::cout << "4. Priority Scheduling\n";
    std::cout << "5. Highest Response Ratio Next (HRRN)\n";
    std::cout << "6. Multiple Queue Scheduling\n";
    std::cout << "7. Multilevel Feedback Queue Scheduling\n";
    std::cout << "8. Multilevel Queue Scheduling\n";
    int choice;

while (true)
{
    std::cout << "\nSelect Scheduling Algorithm (1-8): ";

    if (!(std::cin >> choice))
    {
        std::cout << "\nInvalid input! Please enter a number.\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
    }

    if (choice < 1 || choice > 8)
    {
        std::cout << "\nPlease enter a choice between 1 and 8.\n";
        continue;
    }

    break;
}

    switch (choice)
    {
    case 1:
        FCFS_Scheduling(processes);

        std::cout << "\nAfter FCFS Scheduling:\n";

        displayGanttChart(processes);

        displayProcesses(processes);
        break;

    case 2:
        SJF_Scheduling(processes);

        std::cout << "\nAfter SJF Scheduling:\n";

        displayGanttChart(processes);

        displayProcesses(processes);
        break;

    case 3:
    {
        int time_quantum;
        while (true)
{
    std::cout << "Enter Time Quantum: ";

    if (!(std::cin >> time_quantum))
    {
        std::cout << "Invalid input.\n";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
    }

    if (time_quantum <= 0)
    {
        std::cout << "Time Quantum must be greater than 0.\n";
        continue;
    }

    break;
}
        RoundRobin_Scheduling(processes, time_quantum);
        std::cout << "\nAfter Round Robin Scheduling:\n";
        displayProcesses(processes);
        break;
    }

    case 4:
       Priority_Scheduling(processes);

        std::cout << "\nAfter Priority Scheduling:\n";

        displayGanttChart(processes);

        displayProcesses(processes, true);
        break;

    case 5:
        HRRN_Scheduling(processes);

        std::cout << "\nAfter HRRN Scheduling:\n";

        displayGanttChart(processes);

        displayProcesses(processes);
        break;

    case 6:
    {
        std::vector<std::vector<Process>> queues = {{processes.begin(), processes.begin() + processes.size() / 2},
                                                    {processes.begin() + processes.size() / 2, processes.end()}};
        MultipleQueue_Scheduling(queues);
        std::cout << "\nAfter Multiple Queue Scheduling:\n";
        for (const auto &queue : queues)
            displayProcesses(queue);
        break;
    }

    case 7:
    {
        int num_queues, time_quantum;
        std::cout << "Enter number of queues: ";
        std::cin >> num_queues;
        std::cout << "Enter time quantum: ";
        std::cin >> time_quantum;
        MultilevelFeedbackQueue_Scheduling(processes, num_queues, time_quantum);
        std::cout << "\nAfter Multilevel Feedback Queue Scheduling:\n";
        displayProcesses(processes);
        break;
    }

    case 8:
    {
        std::vector<std::vector<Process>> queues = {{}, {}};
        std::vector<int> priorities = {1, 2}; // Higher priority = lower number

        for (const auto &p : processes)
        {
            if (p.priority <= 2)
                queues[0].push_back(p);
            else
                queues[1].push_back(p);
        }

        MultilevelQueue_Scheduling(queues, priorities);
        std::cout << "\nAfter Multilevel Queue Scheduling:\n";

        for (size_t i = 0; i < queues.size(); ++i)
        {
            if (!queues[i].empty()) // Check if the queue is not empty
            {
                std::cout << "Queue " << i + 1 << ":\n";
                displayProcesses(queues[i], true);
            }
            else
            {
                std::cout << "Queue " << i + 1 << " is empty.\n";
            }
        }
        break;
    }

    default:
        std::cout << "Invalid choice!\n";
        break;
    }

    return 0;
}
