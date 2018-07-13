#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "nbc.h"
using namespace std;
//Constructor

//Public Methods
//Implement train
void NBClassifier::train(string review, int ans)
{
  prime();
  if(ans == 0)
    {
      badNum = badNum + 1;
    }
  else
    {
      goodNum = goodNum + 1;
    }
  totNum = totNum + 1;
  getProb();
  //Parse in words
  string item;
  istringstream iss(review);
  bool found = false;
  while(iss >> item)
    {
      //search vector for word
      /*if(item.at(item.length()-1) == '.'||item.at(item.length()-1) == ','||
	 item.at(item.length()-1) == '!'||item.at(item.length()-1) == '?')
	{
	  item.pop_back();
        }*/
      if(item == "0" || item == "1")
	{}
      else
	{
	  
	  for(int i = 0; i < words.size(); ++i)
	    {
	      //if word is in vector, add to its total
	      if(item == words.at(i).value && !words.at(i).changed)
		{
		  if(ans == 1)
		    {
		      words.at(i).good++;
		    }
		  else
		    {
		      words.at(i).bad++;
		    }
		  words.at(i).tot = words.at(i).tot + 1;
		  words.at(i).changed = true;
		  found = true;
		}
	    }
	  //Otherwise, make a new Word and put it in the vector
	  if(!found)
	    {
	      Word* input = new Word(item);
	      if(ans == 1)
		{
		  input->good++;
		}
	      else
		{
		  input->bad++;
		}
	      input->tot = input->tot + 1;
	      input->changed = true;
	      words.push_back(*input);
	    }
	}
    }
  //Adjust probability of every word in structure
  for(int i = 0; i < words.size(); i++)
    {
      words.at(i).gp = (words.at(i).good/words.at(i).tot) / goodProb;
      words.at(i).bp = (words.at(i).bad/words.at(i).tot) / badProb;
      words.at(i).p = words.at(i).tot / totNum;
    }
}

//Implement test
int NBClassifier::test(string review)
{
  prime();
  //Parse in each word
  string item;
  float g = goodProb;
  float b = badProb;
  //search vector for word
  istringstream iss(review);
  while(iss >> item)
    {
      /*if(item.at(item.length()-1) == '.'||item.at(item.length()-1) == ','||
	 item.at(item.length()-1) == '!'||item.at(item.length()-1) == '?')
	{
	  item.pop_back();
	}*/
      for(int i = 0; i < words.size(); ++i)
	{
	  if(item == words.at(i).value)
	    {
	      g = g * words.at(i).gp;
	      b = b * words.at(i).bp;
	    }
	}
    }

  //once all words have been parsed, determine if positive or negative
  if(g > b)
    {
      return 1;
    }
  else
    {
      return 0;
    }
}

void NBClassifier::output()
{
  for(int i = 0; i < words.size(); ++i)
    {
      cout << words.at(i).value << " goodProb: " << words.at(i).gp << " badProb: ";
      cout << words.at(i).bp << "totProb: " << words.at(i).p << endl;
    }
}

//Private Methods
float NBClassifier::getProb()
{
  goodProb = goodNum / totNum;
  badProb = badNum / totNum;
}

void NBClassifier::prime()
{
  for(int i = 0; i< words.size(); ++i)
    {
      words.at(i).changed = false;
    }
}
