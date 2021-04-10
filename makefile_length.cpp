/*----------------------------------
Name: Joshua Eastgaard
Assignment: WE #7, Interview Question, Makefile_length
Class: CMPUT 275, Wintedr 2021
Date: April 8th, 2021
------------------------------------*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// gotoTar() explores a given target and it's dependcies. Finds longest path in that target and returns value.
int gotoTar(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map);
// gototDeps() explores a dependcies, and returns the length of that dependency.
int gotoDeps(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map);


int main(){
	// Map for storing dependencies
	unordered_map<string, vector<string>> tar_map;
	// Map for reached dependenceis
	unordered_map<string, int> reached;
	// Delcare number of targets and number of dependcies.
	int n, n_dep;
	// Get number of targets.
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
		string temp;
		for(int x = 0; x < n_dep; x++){
			cin >> temp;
			tar_deps.push_back(temp);
		}
		// Add vector of dependencies to target map.
		tar_map[target] = tar_deps;

	}
	// Now we have all our targets and dependencies
	// We must loop through all targets and find longest chain
	//auto it = tar_map.begin();
	int cur_len = 0, temp = 0;

	for(auto it : tar_map){
		// If we have already explored this target, then it can no longer have
		// the longest path.
		if(!reached[it.first]){
			// Explore the target. This will return the LONGEST trail of dependencies.
			reached[it.first] = gotoTar(it.first, reached, &tar_map);
			temp = reached[it.first];
		}
		// Have we found a new longest trail?
		if(temp > cur_len) cur_len = temp;
	}
	// Print out the longest trail found.
	cout << cur_len << endl;
	return 0;
}

/*Description: This function explores a given dependency and returns the 'depth'.
Depth is defined by how many dependencies that the current dependency needs.
Arguments: 
	-dep (string) -> Dependency that will be explored.
	-reached (unordered_map<string, int> refrence) -> Refrence to the map that keeps track
	of the reached targets, and their max depth.
	-tar_map (unordered_map<string, vector<string>> pointer) -> Pointer to the map that keeps
	track of the targets and corrisponding dependencies. Pointer is used as a faster method
	than passing the whole map through to the function.
Returns: 'Depth' of the dependency (int)
*/
int gotoDeps(string dep, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map){
	/*There are three posiblities:
	1: We have already reached the desired dependency, in that case
	we can return that dependency length + 1
	2: We have never reached the dependency AND it IS a target. In
	that case we need to explore the target.
	3: We have never reached the dependency AND it is NOT a target,
	then we need to return 1 as it cannot go any 'deeper'.*/
	if(reached.count(dep)){
		return reached[dep] + 1;
	}else{
		if(tar_map->count(dep)){
			return gotoTar(dep, reached, tar_map) + 1;
		}else{
			return 1;
		}
	}
}

/*Description: This function explores a target, which in turn explores every dependency by calling the gotoDeps function.
It will search through the target and find the depency with the longest depth.
Arguments:
	-target (string) -> Target that the function explores
	-reached (unordered_map<string, int> refrence) -> Refrence to the map that keeps track
	of the reached targets, and their max depth.
	-tar_map (unordered_map<string, vector<string>> pointer) -> Pointer to the map tjat keeps
	track of the targets and corrisponding dependencies. Pointer is used as a faster method than
	passing the whole map through the function.
Returns:
	-length (int) -> 'Depth' of the target.
*/
int gotoTar(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map){
	int length = 0, temp = 0;
	// Loop through every depency in target.
	for(auto dep : (*tar_map)[target]){
		// Get depth of dependency.
		temp = gotoDeps(dep, reached, tar_map);
		// If a new longest path is found, set new length.
		if(temp > length){
			length = temp;
			reached[target] = length;
		}
	}
	// Return longest depth found.
	return length;
}
