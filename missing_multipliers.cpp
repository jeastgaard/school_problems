#include <iostream>
#include <unordered_map>
using namespace std;


int main(){
	int n, m;
	cin >> n >> m;
	long long arr[n];
	long long first[n];
	long long last[n];
	long long p = 0;
	bool changed;
	// Create array of integers
	// We want two arrays. First will be product from first to last
	// Second will be last to first.
	for(int i = 0; i < n; i++){
		cin >> arr[i];
	}
	first[0] = arr[0];
	last[n-1] = arr[n-1];
	for (int i = 1; i < n; i++){
		first[i] = first[i-1] * arr[i];
	}
	
	for (int i = n-2; i >= 0; i--){
		last[i] = last[i+1]*arr[i];
	}

	for (int i = 0; i < n; i++){
		changed = false;
		if (i + m < n - 1){
			changed = true;
			p = last[i+m+1];
		}
		if (i - m > 0){
			if (changed == false){
				p = 1;
				changed = true;
			}
			p = p * first[i - m - 1];
		}
		cout << p << " ";
		p = 0;
	}
	return 0;
}