#ifndef UI_H
#define UI_H

#include "process.h"
#include <vector>
void displayGanttChart(const std::vector<Process>& processes);
void displayProcesses(const std::vector<Process> &processes, bool show_priority = false);
double calculateCPUUtilization(const std::vector<Process>& processes);
double calculateAverageWaitingTime(const std::vector<Process>& processes);

double calculateAverageTurnaroundTime(const std::vector<Process>& processes);
double calculateThroughput(const std::vector<Process>& processes);
#endif
