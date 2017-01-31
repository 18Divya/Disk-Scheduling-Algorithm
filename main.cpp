#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

double variance(int a[], size_t size, int average);
double FCFS(int a[], int size);
double SSTF(int a[], int size);
double SCAN(int a[], int size);

int main()
{
	const size_t arrSize = 9;
	int a[] = {63,33,72,47,8,99,74,52,75};

	cout << "FCFS average: " << FCFS(a, arrSize) << endl;
	cout << "SSTF average: " << SSTF(a, arrSize) << endl;
	return 0;
}

double variance(int a[], size_t size, int average) 
{
	double sum = 0;
	
	for(int i = 0; i < size; i++)
		sum += pow((a[i] - average), 2);
 
	return sum;
}	

double FCFS(int a[], int size)
{
	double sum = 0.0;

	for(int i = 0; i < size - 1; i++)
		sum += abs(a[i] - a[i+1]);

	return sum / (size - 1);
}

double SSTF(int a[], int size)
{
	double sum = 0.0;
	vector<int> vec(a, a + size);
	sort(vec.begin(), vec.end());		//Sort array

	//currTrack point the serving track
	vector<int>::iterator currTrack = find(vec.begin(), vec.end(), a[0]);
	vector<int>::iterator rTrack = currTrack + 1, lTrack = currTrack - 1;
	//Look for the next nearest track
	vector<int>::iterator nextTrack;
	int Llen, Rlen;

	while(true)
	{
		//Calc the distance from left and right element
		Llen = (lTrack >= vec.begin()) ? abs(*lTrack - *currTrack) : -1;
		Rlen = (rTrack != vec.end())  ? abs(*rTrack - *currTrack) : -1;

		//Make sure lTrack & rTrack are not pointing anywhere
		if(Llen != -1 && Rlen != -1)
			nextTrack = ((Rlen - Llen) > 0) ? lTrack : rTrack;
		else if(Llen == -1 && Rlen == -1)
			break;
		else
			nextTrack = (Llen == -1) ? rTrack : lTrack;

		sum += abs(*currTrack - *nextTrack);

		//Update the value of the pointer
		currTrack = nextTrack;
		if(rTrack == nextTrack) rTrack++; else lTrack--;
	}

	return sum / (size - 1);
}

