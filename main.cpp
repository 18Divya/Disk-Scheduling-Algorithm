#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>
#include <ctime>

using namespace std;

double variance(int a[], size_t size, int average);
double FCFS(int a[], int size);
double SSTF(int a[], int size);
double SCAN(int a[], int size);

int main()
{
	srand(time(NULL));
	const size_t arrSize = 9;
	//int a[arrSize];
	int a[] = {63, 33, 72, 47, 8, 99, 74, 52, 75};

	//for(int i = 0; i < arrSize; i++)
	//	a[i] = rand() % 100;

	double average;

	average = FCFS(a, arrSize);
	cout << "FCFS average: " << average << endl;
	cout << "FCFS variance: " << variance(a, arrSize, average) << endl << endl;
	average = SSTF(a, arrSize);
	cout << "SSTF average: " << average << endl;
	cout << "SSTF variance: " << variance(a, arrSize, average) << endl << endl;
	average = SCAN(a, arrSize);
	cout << "SCAN average: " << average << endl;
	cout << "SCAN variance: " << variance(a, arrSize, average) << endl << endl;
	return 0;
}

/***************************************************
This function will calculate the variance of the 
value base on the calculated average depending on the
formula used.
	Pre: a - array
		 size - size of the array
		 average - average value calculated prev
	Post: variance value
****************************************************/
double variance(int a[], size_t size, int average) 
{
	double sum = 0;
	
	for(int i = 0; i < size; i++)
		sum += pow((a[i] - average), 2);
 
	return sum;
}	

/***************************************************
It calculates the average move using FCFS(First 
Come First Serve) technique.
	Pre: a - array
		 size - size of the array
	Post: average move
****************************************************/
double FCFS(int a[], int size)
{
	double sum = 0.0;

	for(int i = 0; i < size - 1; i++)
		sum += abs(a[i] - a[i+1]);

	return sum / (size - 1);
}

/***************************************************
It calculates the average move using SSTF() technique.
	Pre: a - array
		 size - size of the array
	Post: average move
****************************************************/
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

/***************************************************
It calculates the average move using SCAN() technique.
	Pre: a - array
		 size - size of the array
	Post: average move
****************************************************/
double SCAN(int a[], int size)
{
	double sum = 0.0;
	vector<int> vect(a, a + size);

	//Sort the vector
	sort(vect.begin(), vect.end());
	vector<int>::iterator currTrack = find(vect.begin(), vect.end(), a[0]);
	vector<int>::iterator lTrack = currTrack - 1, rTrack = currTrack + 1;

	//Traverse left part of the track
	while(lTrack >= vect.begin()) 
		sum += abs(*(lTrack--) - *(currTrack--));

	//Change direction
	sum += abs(*currTrack - *rTrack);
	currTrack = rTrack;
	rTrack++;

	//Traverse right part of the track
	while(rTrack != vect.end())
		sum += abs((*rTrack++) - (*currTrack++));

	return sum / (size - 1);
}

