#ifndef NBC_H_
#define NBC_H_ /*include guard*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Word
{
  string value;
  int good;
  int bad;
  float tot;
  float gp;
  float bp;
  float p;
  bool changed;

Word(): value(""), good(0), bad(0), tot(0.0), gp(0.0), bp(0.0), p(0.0), changed(true) {};
  
Word( const string & v ): value(v), good(0), bad(0), tot(0.0), gp(0.0), bp(0.0), p(0.0), changed(true) {};
};

class NBClassifier
{
 public:
  //Constructor(s)
 NBClassifier() : goodNum(0.0), badNum(0.0), totNum(0.0), goodProb(0.0), badProb(0.0) {};
  //Training function;
  void train(string review, int ans);
  //Testing function;
  int test(string review);
  //output vector
  void output();
  
 private:
  //Data
  float goodNum;
  float badNum;
  float totNum;
  float goodProb;
  float badProb;
  vector<Word> words;
  //helper functions
  float getProb(); //updates local probabilities - Done
  void prime(); //sets all Words in vector to unchanged - Done
};

#endif /*end of include guard*/
