# CSC322Project1
OS Scheduling Algorithms 

|Process-Id	| Active	| Arrival time |	Total CPU time |	Remaining CPU time	| Turnaround time |
|---|---|---|---|---|---|				
|Pi	| 0 / 1	| Ai	| Ti	| Ri | TTi|

* Process-Id: Pi where i is an integer number between [0,n]
* Active: indicates whether the corresponding process is currently competing for the CPU. The value is set to 1 one the process arrives and set to 0 when process has finished. 
* Arrival time: Ai is an integer selected randomly from a uniform distribution between 0 and some value k, where k is a simulation input parameter. 
* Total CPU time: Ti is an integer selected randomly from a normal distribution with an average d and a standard deviation v, where d and v are simulation input parameters.
* Remaining CPU time: Ri is initialized to Ti. 
* Turnaround time: TTi is equal to t – Ai where t is the “current” time.

## Each simulation step consists of the following actions ##
* Run until Ri = 0 for all processes
* If no process is ready to run then just advance t
* Select active process Pi to run next according to the scheduling algorithm
* Decrement Ri
* If Ri == 0 then process i has terminated so set active flag to 0 and calculate its turnaround time TTi. 
* Compute the average turnaround time for all processes by averaging all TTi values

### Scheduling algorithms to include in your simulation program ###

* First-Come First-Severed 
* Shortest Job First
* Shortest Remaining Time
