/*----------------------------------
Name: Joshua Eastgaard
ID: 1646032
Assignment: WE #7, Interview Question, Makefile_length
Class: CMPUT 275, Wintedr 2021
Date: April 8th, 2021
------------------------------------*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Map for storing dependencies
unordered_map<string, vector<string>> tar_map;
int gotoTar(string target, unordered_map<string, int> & reached);

int gotoDeps(unordered_map<string, int> & reached, string target){
	//cout << "Checking dependency " << target << endl;
	if(reached.count(target)){
		//cout << "Dependency Checked, Adding: " << reached[target] << " + 1" << endl;
		return reached[target] + 1;
	}else{
		if(tar_map.count(target)){
			return gotoTar(target, reached) + 1;
		}else{
			// Target is not in makefile.
			//cout << "Reached the end" << endl;
			return 1;
		}
	}
}

int gotoTar(string target, unordered_map<string, int> & reached){
	int length = 0, temp = 0;
	//cout << "In target: " << target << endl;
	//cout << "It has " << tar_map[target].size() << " dependencies" << endl;
	// Loop through every depency in target.
	for(uint i = 0; i < tar_map[target].size(); i++){
		temp = gotoDeps(reached, tar_map[target][i]);
		if(temp > length){
			length = temp;
			reached[target] = length;
		}

	}
	//cout << "Target " << target << " is " << length << " long" << endl;
	return length;
}

int main(){
	// Map for reached dependenceis
	unordered_map<string, int> reached;
	int n, n_dep;
	// Take the number of targets
	cin >> n;
	// Get dependencies for every target
	for (int i = 0; i < n; i++) {
		// Get the number of dependencies in the target
		cin >> n_dep;
		string target;
		// Target has ":" at the end, need to get rid of it.
		cin >> target;
		target.pop_back();
		vector<string> tar_deps;
		// Get every dependecy for the target
		// and add it to the vector
		for(int x = 0; x < n_dep; x++){
			string temp;
			cin >> temp;
			tar_deps.push_back(temp);
		}
		// Add vector of dependencies to tar_map
		tar_map[target] = tar_deps;

	}
	// Now we have all our targets and dependencies
	// We must loop through all targets and find longest chain
	unordered_map<string, vector<string>>::iterator it = tar_map.begin();
	int cur_len = 0;
	int temp = 0;
	while(it != tar_map.end()){
		// If we have already explored this
		// target, then it can no longer have
		// the longest path.
		//cout << "Target: " << it->first << endl;
		if(!reached[it->first]){
			// Set the reached to 1.
			//cout << "Not reached, going into: " << it->first << endl;
			reached[it->first] = gotoTar(it->first, reached);
			temp = reached[it->first];
		}
		if(temp > cur_len) cur_len = temp;
		it++;
	}
	unordered_map<string, int>::iterator iter = reached.begin();
	while(iter != reached.end()){
		//cout << iter->first << ": " << iter->second << endl;
		iter++;
	}
	it = tar_map.begin();
	while(it!=tar_map.end()){
		//cout << it->first << endl;
		it++;
	}
	cout << cur_len << endl;
	return 0;
}

