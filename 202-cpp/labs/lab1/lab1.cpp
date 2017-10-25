#include <iostream>
using namespace std;

const int NUM_STUDENTS = 25;

int max(int data[], int dataLen);
int min(int data[], int dataLen);
float average(int data[], int dataLen);


int main(){

int scores[NUM_STUDENTS] = {0};
int numScores = 0;
int userInput;

 cout << "Enter a score (-1 when done): ";
 cin >> userInput;

 while(userInput >= 0 && numScores < NUM_STUDENTS)
   {
     scores[numScores] = userInput;
     numScores++;
     
     cout << "Enter a score (-1 when done): ";
     cin >> userInput;

   }

 int maxVal = max(scores, numScores);
 int minVal = min(scores, numScores);
 float avgVal = average(scores, numScores);


 if (userInput == -1)
   {
     cout << "Max Score is " << maxVal << endl
	  << "Min Score is " << minVal << endl
	  << "Average Score is " << avgVal << endl;
   }

  return 0;
}

int max(int data[], int dataLen)
{
  int currentMax = data[0];
  for(int i = 1; i< dataLen; i++)
    {
      if (data[i] > currentMax)
	{
	  currentMax = data[i];
	}
    }
  return currentMax;
}

int min(int data[], int dataLen)
{
  int currentMin = data[0];
  for(int i = 1; i < dataLen; i++)
    {
      if(data[i] < currentMin)
	{
	  currentMin = data[i];
	}
    }
  return currentMin;
}

float average(int data[], int dataLen)
{
  int currentVal = data[0];
  for(int i = 1; i < dataLen; i++)
    {
      currentVal = currentVal + data[i];
    }
  int average = currentVal / dataLen;
  return average;
}
