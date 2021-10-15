/*----------------------------------
Name: Joshua Eastgaard
Assignment: WE #7, Interview Question, Makefile_length
Class: CMPUT 275, Winter 2021
Date: April 8th, 2021
------------------------------------*/

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// tarDepth() explores a given target and it's dependencies. Finds longest path in that target and returns that value.
int tarDepth(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map);
// gototDeps() explores a dependency, and returns the length of that dependency depth (How many other dependencies within).
int gotoDeps(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map);

/*
This main() function will calculate the longest path of dependencies in a given makefile.
This will be done using tarDepth() and gotoDeps(). The file input format must be as follows:
# Of Targets
# Of Dependencies target: Dep1 Dep2 Dep2......Depn
						
						Example:
					5
					3 swift: apple pie cherry
					3 apple: crust bubble oven
					2 bubble: crumb delight
					4 cherry: bubble salad dinner sweet
					1 crumb: baking

						Output:
					4
						Explanation:
The longest path would be from swift, apple, bubble, crumb, baking. Since swift is the starting point,
we can say that swift depends on 4 other targets or files.

This function will take the information in through STDIN and print the number out through STDOUT.
Arguments: None
Returns: 0 upon successful execution. 
*/
int main() {
	// Map for storing dependencies for a given  target.
	unordered_map<string, vector<string>> tar_map;
	// Map for reached dependencies.
	unordered_map<string, int> reached;
	// Declare number of targets and number of dependencies.
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
		// Vector was chosen for it's simple, easy to use methods
		// that allow us to add as many dependencies as we want to it,
		// then go through them in the order they were added one at a time.
		vector<string> tar_deps;
		// Get every dependency for the target
		// and add it to the vector
		string temp;
		for (int x = 0; x < n_dep; x++) {
			cin >> temp;
			tar_deps.push_back(temp);
		}
		// Add vector of dependencies to target map.
		tar_map[target] = tar_deps;

	}
	// Now we have all our targets and dependencies
	// We must loop through all targets and find longest chain
	int cur_len = 0, temp = 0;

	for (auto it : tar_map) {
		// If we have already explored this target, then it can no longer have
		// the longest path.
		if (!reached[it.first]) {
			// Explore the target. This will return the LONGEST trail of dependencies.
			reached[it.first] = tarDepth(it.first, reached, &tar_map);
			temp = reached[it.first];
		}
		// Have we found a new longest trail?
		if (temp > cur_len) cur_len = temp;
	}
	// Print out the longest trail found.
	cout << cur_len << endl;
	return 0;
}

/* Description: This function explores a given dependency and returns the 'depth'.
Depth is defined by how many dependencies that the current dependency requires.
Arguments: 
	-dep (string) -> Dependency that will be explored.
	-reached (unordered_map<string, int> reference) -> Reference to the map that keeps track
	of the reached targets, and their max depth.
	-tar_map (unordered_map<string, vector<string>> pointer) -> Pointer to the map that keeps
	track of the targets and corresponding dependencies. Pointer is used as a faster method
	than passing the whole map through to the function.
Returns: 'Depth' of the dependency (int)
*/
int gotoDeps(string dep, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map) {
	/* There are three possibilities:
	1: We have already reached the desired dependency, in that case
	we can return that dependency length + 1
	2: We have never reached the dependency AND it IS a target. In
	that case we need to explore the target.
	3: We have never reached the dependency AND it is NOT a target,
	then we need to return 1 as it cannot go any 'deeper'.*/
	if (reached.count(dep)) {
		return reached[dep] + 1;
	} else {
		if (tar_map->count(dep)) {
			return tarDepth(dep, reached, tar_map) + 1;
		} else {
			return 1;
		}
	}
}

/* Description: This function explores a target, which in turn explores every dependency by calling the gotoDeps function.
It will search through the target and find the dependency with the longest depth.
Arguments:
	-target (string) -> Target that the function explores
	-reached (unordered_map<string, int> reference) -> Reference to the map that keeps track
	of the reached targets, and their max depth.
	-tar_map (unordered_map<string, vector<string>> pointer) -> Pointer to the map that keeps
	track of the targets and corresponding dependencies. Pointer is used as a faster method than
	passing the whole map through the function.
Returns:
	-length (int) -> 'Depth' of the target.
*/
int tarDepth(string target, unordered_map<string, int> & reached, unordered_map<string, vector<string>> * tar_map) {
	// Our starting depth is 0, we set temp to match.
	int length = 0, temp = 0;
	// Loop through every dependency in target.
	for (auto dep : (*tar_map)[target]) {
		// Get depth of dependency.
		temp = gotoDeps(dep, reached, tar_map);
		// If a new longest path is found, set new length.
		if (temp > length) length = temp;
	}
	// We will store the longest chain of the target in the reached map.
	reached[target] = length;
	// Return longest depth found.
	return length;
}
