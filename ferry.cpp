/*---------------------
Name: Joshua Eastgaard
Problem: Ferry
Date: March 1st, 2021
-----------------------

*This problem was presented to me by the University of Alberta for the
CMPUT 275 Winter 2021 Class*

There is a cute little single-vehicle ferry that transports vehicles across a river. It begins
each day on the West bank of the river. Vehicles arrive at various times throughout the day
on either side of the river. But it can only hold one vehicle at a time.
The ferry operates as follows. If there are no vehicles waiting, it idles on the side it is
currently resting on.
At any time it is not currently transporting a vehicle, if some vehicle is waiting to be
transported then it serves the vehicle that has been waiting the longest. It does this by first
traveling to the side of the river the vehicle is waiting on (if the ferry is not there already),
loading the vehicle, transporting it to the other side, and then unloading it.
The ferry operator is very single-minded. If he unloads a vehicle and if there are vehicles waiting on both sides of the river but the next vehicle to be served (i.e. the one that
has waited the longest) is on the other side, he will travel to the other side without bringing
over a vehicle from the current side. See examples 2 and 3 for clarification.
Loading and unloading takes 0 time. The ferry takes 100 units of time to cross the river.
Again, recall the ferry starts on the West bank. What time is the last vehicle dropped off?


Sample Input:

	5 1
	1 2 3 4 5
	6

Sample Output:
	
	1001
*/
#include <iostream>
#include <map>
using namespace std;

int main() {
	// We need to take the amount of arrivals on the east and west side.
	int west_arrivals, east_arrivals;
	cin >> west_arrivals >> east_arrivals;
	// Create a map that will contain the order that 
	// cars need to be served in.
	map<int,char> serve_order;
	for(int i = 0; i < west_arrivals; i++) {
		int k;
		// We need to take all the cars on the west side
		cin >> k;
		serve_order[k] = 'W';
	}
	for(int i = 0; i < east_arrivals; i++) {
		int k;
		// We need to take all the cars on the east side.
		cin >> k;
		serve_order[k] = 'E';
	}
	// Ferry Starts on the West side of the river
	int size = serve_order.size();
	char current = 'W';
	int time, waiting = 0;
	map<int, char>::iterator it = serve_order.begin();s
	// Set time that the first veichle gets picked up.
	if(it->second == current) {
		time = it->first;
	// If the first veichle to arrive is not on the West side.
	}else {
		time = it->first + 100;
		current = 'E';
	}
	// We need to now ferry every veichle.
	for(it; it != serve_order.end(); it++) {
		// If we need to wait for the veichle, then
		// the current time is the time it arrives.
		if(it->first > time){
			time = it->first;
		}
		// If we do not need to travel to the opposite side
		// of the river, just add 100 units of time.
		if(it->second == current){
			time = time + 100;
			// Switch locations.
			if(current == 'W'){
				current = 'E';
			}else{
				current = 'W';
			}
		// If we have to travel to the other side of the river just
		// to pick them up, then we need to add 200 units of time.
		}else{
			time = time + 200;
		}
	}
	cout << time << endl;
	return 0;
}