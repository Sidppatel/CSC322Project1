#pragma warning( disable : 4244)

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <time.h>
#include <queue>
#include <map>
#include <numeric>
#include <random>
#include <string> 

using namespace std;

class Process {
private:
	int id;
	int cpuTime;
	int arrivalTime;
	int completionTime;
	int turnAroundTime;
	int waitingTime;
	bool active;
	int remaningTime;

public:
	int getId() {
		return id;
	}
	int getCPUTime() {
		return cpuTime;
	}
	int getArrivalTime() {
		return arrivalTime;
	}
	int getCompletionTime() {
		return completionTime;
	}
	int getTurnAroundTime() {
		return turnAroundTime;
	}
	int getWaitingTime() {
		return waitingTime;
	}
	bool getActive() {
		return active;
	}
	int getRemaningTime() {
		return remaningTime;
	}
	void setId(int id) {
		this->id = id;
	}
	void setCPUTime(int cpuTime) {
		this->cpuTime= cpuTime;
	}
	void setArrivalTime(int arrivalTime) {
		this->arrivalTime = arrivalTime;
	}
	void setCompletionTime(int completionTime) {
		this->completionTime = completionTime;
	}
	void setTurnAroundTime(int turnAroundTime) {
		this->turnAroundTime = turnAroundTime;
	}
	void setWaitingTime(int waitingTime) {
		this->waitingTime = waitingTime;
	}
	void setActive(bool active) {
		this->active = active;
	}
	void setRemaningTime(int remaningTime) {
		this->remaningTime = remaningTime;
	}
};

bool compareByRemaningTime(Process p, Process q)
{
	return p.getRemaningTime() > q.getRemaningTime();
}

bool compareByArrival(Process p, Process q)
{
	return p.getArrivalTime() < q.getArrivalTime();
}

bool compareByCPU(Process p, Process q)
{
	return p.getCPUTime() < q.getCPUTime();
}

void displayProcess(Process P[], int jobCount) {
	for (int i = 0; i < jobCount; i++) {
		cout << "\t\tProcess ID : " << P[i].getId() << "\tArrival Time : " << P[i].getArrivalTime() << "\tCPU time : " << P[i].getCPUTime() << endl;
	}
}

void display(Process P[], int jobCount, float avgtat = 0)
{
	string remaningTime = " ";
	string waitingTime = "";
	string turnAroundTime = "";
	string completionTime = "";
	sort(P, P + jobCount, compareByRemaningTime);
	cout << "\n\n\t\t The Process Status \n\n";
	cout << "\tID\tActive\tArrival Time\tCPU Time\tCompletion Time\t\tTurn Around\tWaiting Time\tRemaning Time";
	for (int i = 0; i < jobCount; ++i) {
		remaningTime = to_string(P[i].getRemaningTime());
		waitingTime = to_string(P[i].getWaitingTime());
		turnAroundTime = to_string(P[i].getTurnAroundTime());
		completionTime = to_string(P[i].getCompletionTime());
		/*
		remaningTime = (P[i].getRemaningTime() < 0) ? "-" : to_string(P[i].getRemaningTime());
		waitingTime = (! P[i].getActive()) ? "-" : to_string(P[i].getWaitingTime());
		turnAroundTime = (! P[i].getActive()) ? "-" : to_string(P[i].getTurnAroundTime());
		completionTime = (! P[i].getActive()) ? "-" : to_string(P[i].getCompletionTime());
		*/
		cout << "\n\t" << P[i].getId() << "\t" << P[i].getActive() << "\t" << P[i].getArrivalTime() << "\t\t" << P[i].getCPUTime() << "\t\t"
			<< completionTime << "\t\t\t" << turnAroundTime << "\t\t" << waitingTime << "\t\t" << remaningTime;
	}
	cout << "\n\n\t\tAverage Turn Around Time: " << avgtat;
	cout << "\n\n\n";
}

void getData(Process P[], int& jobCount)
{
	int x;
	for (int i = 0; i < jobCount; i++)
	{
		P[i].setId(i + 1);
		cout << "\n\t Process ID: ";
		cout << P[i].getId();
		cout << "\n\t Enter the Process Arrival Time: ";
		cin >> x;
		P[i].setArrivalTime(x);
		cout << "\n\t Enter the Process CPU Time: ";
		cin >> x;
		P[i].setCPUTime(x);
		P[i].setCompletionTime(0);
		P[i].setTurnAroundTime(0);
		P[i].setWaitingTime(0);
	}
}

void generateRandomData(Process P[], int jobCount, int k, int d, int v)
{
	/*
	k = Maximum Arrival Time (Uniform Distribution)
	d = Mean Average (Normal Distribution)
	v = Standard deviation (Normal Distribution)
	*/

	random_device rd;	//Will be used to obtain a seed for the random number engine
	mt19937 gen(rd());	//Standard mersenne_twister_engine seeded with rd()
	mt19937 eng;		//Standard mersenne_twister_engine

	uniform_int_distribution<> distrib(0, k);
	normal_distribution<float> normal(d, v);

	for (int i = 0; i < jobCount; i++)
	{
		P[i].setId(i + 1);
		P[i].setArrivalTime(distrib(gen));
		P[i].setCPUTime(abs(int(normal(eng))));
		P[i].setCompletionTime(0);
		P[i].setTurnAroundTime(0);
		P[i].setWaitingTime(0);
	}

}

void FirstComeFirstServed(Process P[], int jobCount, int time)
{
	vector<int> turnAroundTime;
	float avgTurnAroundTime = 0.0f;

	cout << "\n\t*** FCFS ***\n";

	sort(P, P + jobCount, compareByArrival); // Sorting the processes according to Arrival Time

	for (int i = 0, prevEnd = 0; i < jobCount; i++) {
		P[i].setCompletionTime(max(prevEnd, P[i].getArrivalTime()) + P[i].getCPUTime());
		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getCPUTime());
		P[i].setRemaningTime(time - P[i].getCompletionTime());
		if (P[i].getCompletionTime() <= time)
		{
			P[i].setActive(true);
			turnAroundTime.push_back(P[i].getTurnAroundTime());
		}
		else
			P[i].setActive(false);
		prevEnd = P[i].getCompletionTime();
	}

	auto n = turnAroundTime.size();
	
	if (n != 0)
		avgTurnAroundTime = accumulate(turnAroundTime.begin(), turnAroundTime.end(), 0.0) / n;
	display(P, jobCount, avgTurnAroundTime);
}

void ShortestJobFirst(Process P[], int jobCount,int time) // Shortest job first non preemptive
{
	cout << "\n\t*** SJF ***\n";

	int executedCount = 0;
	bool* processActive = new bool[jobCount];
	fill(processActive, processActive + jobCount, false);
	vector <Process> processInQueue;
	map<int, int> id_compl;
	for (int t = 0; executedCount < jobCount;) {
		for (int i = 0; i < jobCount; i++) {
			if (!processActive[P[i].getId() - 1] && P[i].getArrivalTime() <= t) { 		//To check if process is executed before and also whether it has arrived or not
				processInQueue.push_back(P[i]);				// Pushed to Process Arrived Vector
				processActive[P[i].getId() - 1] = true;
			}
		}
		if (processInQueue.size() != 0) {
			vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
				processInQueue.end(), compareByCPU);
			Process processMinCPUTime = *minPosition;
			t += processMinCPUTime.getCPUTime();
			id_compl[processMinCPUTime.getId()] = t;
			executedCount++;
			processInQueue.erase(minPosition);

		}
		else {
			t++;
		}
	}

	vector<int> turnAroundTime;
	float avgTurnAroundTime = 0.0f;

	for (int i = 0; i < jobCount; ++i)
	{
		P[i].setCompletionTime(id_compl[P[i].getId()]);
		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getCPUTime());
		P[i].setRemaningTime(time - P[i].getCompletionTime());
		if (P[i].getCompletionTime() <= time)
		{
			P[i].setActive(true);
			turnAroundTime.push_back(P[i].getTurnAroundTime());
		}
		else
			P[i].setActive(false);

		avgTurnAroundTime += P[i].getTurnAroundTime();
	}
	auto n = turnAroundTime.size();

	if (n != 0)
		avgTurnAroundTime = accumulate(turnAroundTime.begin(), turnAroundTime.end(), 0.0) / n;
	display(P, jobCount, avgTurnAroundTime);
}

void ShortestJobRemainingFirst(Process P[], int jobCount, int time)
{
	cout << "\n\t*** SJRF ***\n";
	int t = 0, executedCount = 0;
	vector<int> turnAroundTime;
	float avgTurnAroundTime = 0.0f;
	vector <Process> processInQueue;
	bool* inQueue = new bool[jobCount];
	fill(inQueue, inQueue + jobCount, false);
	map<int, int> pid_compl;
	while (executedCount != jobCount)
	{
		for (int i = 0; i < jobCount; i++)
		{
			if ((P[i].getArrivalTime() <= t) && (inQueue[i] == false))
			{
				processInQueue.push_back(P[i]);
				inQueue[i] = true;
			}
		}

		if (processInQueue.size() != 0)
		{
			vector<Process>::iterator minPosition = min_element(processInQueue.begin(),
				processInQueue.end(), compareByCPU);
			(*minPosition).setCPUTime((*minPosition).getCPUTime() - 1);
			t++;
			if ((*minPosition).getCPUTime() == 0)
			{
				pid_compl[(*minPosition).getId()] = t;
				executedCount++;
				processInQueue.erase(minPosition);
			}
		}
		else
			t++;
	}
	for (int i = 0; i < jobCount; i++) {
		P[i].setCompletionTime(pid_compl[P[i].getId()]);
		P[i].setTurnAroundTime(P[i].getCompletionTime() - P[i].getArrivalTime());
		P[i].setWaitingTime(P[i].getTurnAroundTime() - P[i].getCPUTime());
		P[i].setRemaningTime(time - P[i].getCompletionTime());
		if (P[i].getCompletionTime() <= time)
		{
			P[i].setActive(true);
			turnAroundTime.push_back(P[i].getTurnAroundTime());
		}
		else
			P[i].setActive(false);

	}
	auto n = turnAroundTime.size();

	if (n != 0)
		avgTurnAroundTime = accumulate(turnAroundTime.begin(), turnAroundTime.end(), 0.0) / n;
	display(P, jobCount, avgTurnAroundTime);
}

int main()
{
	int schedulingType, dataInputChoice, jobCount;
	int totalTime = 100;
	int k = 0; //Maximum Arrival Time (Uniform Distribution)
	int d = 0; // Mean Average (Normal Distribution)
	int v = 0; // standard deviation (Normal Distribution)

	while (1) {

		cout << "\n\t*****CPU Scheduling Algorithms*****\n";

		cout << "\t 1. First Come First Served (FCFS)\n\t 2. Shortest Job First (SJF)\n\t 3. Shortest Job Remaining First (SJRF)\n\t 0. Exit\n";
		cout << "\n\t Enter your choice [0-4] : ";

		cin >> schedulingType;

		if (schedulingType == 0) {
			exit(1);
		}

		/*
		cout << "\t No. of processes : ";
		cin >> jobCount;
		cout << "\n\t Enter Maximum Arrival Time : ";
		cin >> k;
		cout << "\t Enter Mean of CPU time & Standard Deviation :";
		cin >> d >> v;
		
		Process* P = new Process[jobCount];
		generateRandomData(P, jobCount, k, d, v);
		*/
		
//		* Options to Control Process by Manually
		cout << "\n\t Manually enter data or Auto generated data? \n\t 1. Manually \t 2. Random Generated \n";
		cout << "\n\t Enter your choice [1/2] : ";

		cin >> dataInputChoice;

		cout << "\t No. of processes : ";
		cin >> jobCount;

		Process* P = new Process[jobCount];

		switch (dataInputChoice) {
			case 1: {
				getData(P, jobCount);
				break;
			}

			case 2: {
				cout << "\n\t Enter Maximum Arrival Time : ";
				cin >> k;
				cout << "\t Enter Mean of CPU time & Standard Deviation :";
				cin >> d >> v;
				generateRandomData(P, jobCount, k, d, v);
			}
		}
		
		displayProcess(P, jobCount);

		switch (schedulingType) {
			case 1: {
				FirstComeFirstServed(P, jobCount, totalTime);
				break;
			}
			case 2: {
				ShortestJobFirst(P, jobCount, totalTime);
				break;
			}
			case 3: {
				ShortestJobRemainingFirst(P, jobCount, totalTime);
				break;
			}
		}
	}
	return 0;
}