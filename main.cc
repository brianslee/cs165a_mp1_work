#include <iostream>
#include <fstream>
#include <time.h>
#include <set>
#include <stdlib.h>
#include <math.h>
#include <string>

#include "nbc.h"

using namespace std;

int main(int argc, char *argv[] )
{
  if(argc != 3)
    {
      cout << "usage: " << argv[0] << " <training_file> <testing_file>" << endl;
      return 0;
    }

  ifstream training (argv[1], ios::in);
  ifstream testing (argv[2], ios::in);
  string review; //review
  int ans; //Correct Answer
  float trainAcc = 0.0; //Accuracy of training set
  float testAcc = 0.0; //Accuracy of testing set
  float trainCor = 0.0; //Number of correct answers in training set
  float testCor = 0.0; //Number of correct answers in testing set
  float trainTot = 0.0; //Number of total answers in training set
  float testTot = 0.0; //Number of total answers in testing set
  float trainTime; //Length of time to train
  float labTime; //Length of time to test

  NBClassifier *ai = new NBClassifier();
  clock_t startTime, endTime;

  //Train the NBC
  startTime = clock();
  while(getline(training, review))
    {
      char cans = review.at(review.length() - 1);
      ans = cans - '0';
      //review.pop_back();
      ai->train(review, ans);
    }
  endTime = clock();
  trainTime = (int)(endTime - startTime)/CLOCKS_PER_SEC;

  training.close();

  ifstream testing1(argv[1], ios::in);
  //Test the NBC on the training set
  startTime = clock();
  while(getline(testing1, review))
    {
      char cans = review.at(review.length() - 1);
      ans = cans - '0';
      //review.pop_back();
      int x = ai->test(review);
      if(x == ans)
	{
	  trainCor = trainCor + 1;
	}
      trainTot = trainTot + 1;
      //cout << x <<  endl;
    }
  trainAcc = trainCor/trainTot;
  trainAcc = floor(trainAcc * 1000 + 0.5)/1000;
  
  //Test the NBC on the testing set
  while(getline(testing, review))
    {
      char cans = review.at(review.length() - 1);
      ans = cans - '0';
      //review.pop_back();
      int y = ai->test(review);
      if(y == ans)
	{
	  testCor = testCor + 1;
	}
      testTot = testTot  + 1;
      cout << y << endl;
    }
  testAcc = testCor/testTot;
  testAcc = floor(testAcc * 1000 + 0.5)/1000;

  endTime = clock();
  labTime = (int)(endTime - startTime)/CLOCKS_PER_SEC;

  //Output results
  cout << trainTime << " seconds (training)" << endl;
  cout << labTime << " seconds (labeling)" << endl;
  cout << trainAcc << " (training)" << endl;
  cout << testAcc << " (testing)" << endl;

  //ai->output();

  //Close streams
  testing1.close();
  testing.close();
  
  return 0;
}
