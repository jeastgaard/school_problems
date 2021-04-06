/*----------------------------------
Name: Joshua Eastgaard
Problem: Missing Multipliers
Date: March 16th, 2021
-----------------------------------*/

#include <iostream>
#include <unordered_map>

int main(){
	int n, m;
	std::cin >> n >> m;
	// Create array of integers
	// We want two arrays. First will be product from first to last
	// Second will be last to first.
	// P represents product of numbers, starting at zero because if
	// we don't multiply anything, then we have a zero value.
	long long arr[n], first[n], last[n], p = 0;
	bool changed;
	
	// This is the main array of given integers
	for (int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	// We set the starting values in each array.
	first[0] = arr[0];
	last[n - 1] = arr[n - 1];

	// Multiply the integers starting from the first.
	for (int i = 1; i < n; i++) {
		first[i] = first[i - 1] * arr[i];
	}

	// Multiply the integers starting from the last.
	for (int i = n - 2; i >= 0; i--) {
		last[i] = last[i + 1] * arr[i];
	}


	for (int i = 0; i < n; i++) {
		// We have a 'changed' flag in order to tell if we have
		// changed the product value yet, this accounts for zeros
		// in the list of integers.
		changed = false;
		// We are in the lower bound of the array
		if (i + m < n - 1) {
			changed = true;
			// We just get the product at the specified index.
			p = last[i + m + 1];
		}
		// We are in the upper bound of the array
		if (i - m > 0) {
			if (changed == false) {
				// We don't want to multiply by zero.
				p = 1;
				changed = true;
			}
			// Multiply the first p value by our second value.
			// This second value represents the upperbound multiplied value.
			p = p * first[i - m - 1];
		}
		// Print out our calculated product.
		std::cout << p << " ";
		// Reset product.
		p = 0;
	}
	return 0;
}