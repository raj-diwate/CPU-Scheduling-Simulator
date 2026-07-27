#include "ui.h"
#include <iostream>
#include <iomanip>



void displayGanttChart(const std::vector<Process>& processes)
{
    if (processes.empty())
        return;

    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "              GANTT CHART\n";
    std::cout << "=========================================\n\n";

    // Top Border
    std::cout << "+";
    for (size_t i = 0; i < processes.size(); i++)
        std::cout << "-------+";
    std::cout << "\n";

    // Process Blocks
    std::cout << "|";
for (const auto &p : processes)
{
    std::cout << " ";
    std::cout << std::setw(5) << ("P" + std::to_string(p.pid));
    std::cout << " |";
}
    std::cout << "\n";

    // Bottom Border
    std::cout << "+";
    for (size_t i = 0; i < processes.size(); i++)
        std::cout << "-------+";
    std::cout << "\n";

    // Timeline
    std::cout << processes[0].arrival_time;

    for (const auto &p : processes)
        std::cout << "\t" << p.completion_time;

    std::cout << "\n\n";
}


void displayProcesses(const std::vector<Process> &processes, bool show_priority)
{
    if (show_priority)
    {
        std::cout << "PID\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n";
        for (const auto &p : processes)
        {
            std::cout << p.pid << "\t" << p.arrival_time << "\t"
                      << p.burst_time << "\t" << p.priority << "\t\t"
                      << p.waiting_time << "\t" << p.turnaround_time << "\t \t" << p.completion_time << "\n";
        }
        return;
    }
    std::cout << "PID\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n";
    for (const auto &p : processes)
    {
        std::cout << p.pid << "\t" << p.arrival_time << "\t"
                  << p.burst_time << "\t" << p.waiting_time << "\t"
                  << p.turnaround_time << "\t \t" << p.completion_time << "\n";
    }
}



double calculateCPUUtilization(const std::vector<Process>& processes)
{
    if (processes.empty())
        return 0.0;

    int totalBurst = 0;
    int firstArrival = processes[0].arrival_time;
    int lastCompletion = processes[0].completion_time;

    for (const auto &p : processes)
    {
        totalBurst += p.burst_time;

        if (p.arrival_time < firstArrival)
            firstArrival = p.arrival_time;

        if (p.completion_time > lastCompletion)
            lastCompletion = p.completion_time;
    }

    int totalTime = lastCompletion - firstArrival;

    if (totalTime == 0)
        return 100.0;

    return (double)totalBurst * 100.0 / totalTime;
}

double calculateAverageWaitingTime(const std::vector<Process>& processes)
{
    if (processes.empty())
    {
        return 0.0;
    }

    int totalWaitingTime = 0;

    for (const auto& process : processes)
    {
        totalWaitingTime += process.waiting_time;
    }

    return static_cast<double>(totalWaitingTime) / processes.size();
}


double calculateAverageTurnaroundTime(const std::vector<Process>& processes)
{
    if (processes.empty())
    {
        return 0.0;
    }

    int totalTurnaroundTime = 0;

    for (const auto& process : processes)
    {
        totalTurnaroundTime += process.turnaround_time;
    }

    return static_cast<double>(totalTurnaroundTime) / processes.size();
}