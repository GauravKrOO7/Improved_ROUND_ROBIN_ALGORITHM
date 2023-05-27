#include<bits/stdc++.h>

using namespace std;

// Process structure 
struct Process {
  int processID;
  int burstTime;
  int remainingTime;
  int waitingTime;
};

//Function that implement the algorithm on the two queues
void priorityRoundRobinScheduling(queue < Process > & highPriorityQueue, queue < Process > & lowPriorityQueue, int timeQuantum) {
  //two pointers to point at the two queues
  queue < Process > * currentQueue = & highPriorityQueue;
  queue < Process > * nextQueue = & lowPriorityQueue;

  while (!highPriorityQueue.empty() || !lowPriorityQueue.empty()) {
    if (currentQueue -> empty()) {
      // Switch to the next queue if the current queue is empty
      swap(currentQueue, nextQueue);
    }

    Process currentProcess = currentQueue -> front();
    currentQueue -> pop();

    // Execute the process for the time quantum or until it finishes
    int executionTime = min(timeQuantum, currentProcess.remainingTime);
    currentProcess.remainingTime -= executionTime;

    //increasing waiting time of all the processes that are currently present in both the queues

    int n = highPriorityQueue.size();
    int c = 0;
    while (c != n) {
      Process pro = highPriorityQueue.front();
      pro.waitingTime += executionTime;
      highPriorityQueue.pop();
      highPriorityQueue.push(pro);
      c++;
    }

    n = lowPriorityQueue.size();
    c = 0;
    while (c != n) {
      Process pro = lowPriorityQueue.front();
      pro.waitingTime += executionTime;
      lowPriorityQueue.pop();
      lowPriorityQueue.push(pro);
      c++;
    }

    // If the process is not yet completed, push it back to the respective queue
    if (currentProcess.remainingTime > 0) {
      currentQueue -> push(currentProcess);
    } else {
      // Process completed
      cout << "Process " << currentProcess.processID << " completed." << " " << currentProcess.waitingTime << " " << endl;
    }

    //swapping to give chance to the other queue to avoid starvation
    swap(currentQueue, nextQueue);
  }
}

int main() {
  int numProcesses;
  int timeQuantum;

  cout << "Enter the number of processes: ";
  cin >> numProcesses;

  cout << "Enter the time quantum: ";
  cin >> timeQuantum;

  //two seperate queues for high and low priority
  //queue using Process data type
  queue < Process > highPriorityQueue;
  queue < Process > lowPriorityQueue;

  // Input process details
  for (int i = 0; i < numProcesses; ++i) {
    Process process;
    cout << "Enter details for Process " << i + 1 << endl;
    cout << "Process ID: ";
    cin >> process.processID;
    cout << "Burst Time: ";
    cin >> process.burstTime;
    cout << "Priority (1 for high priority, 0 for low priority): ";
    int priority;
    cin >> priority;
    process.remainingTime = process.burstTime;
    process.waitingTime = 0;

    if (priority == 1) {
      highPriorityQueue.push(process);
    } else {
      lowPriorityQueue.push(process);
    }
  }

  // Perform priority-based round-robin scheduling
  priorityRoundRobinScheduling(highPriorityQueue, lowPriorityQueue, timeQuantum);

  return 0;
}
