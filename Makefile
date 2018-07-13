CC = g++ -g

all:	NaiveBayesClassifier

NaiveBayesClassifier:
	$(CC) nbc.cc main.cc  -o $@

.PHONY: clean

clean:
	rm -rf NaiveBayesClassifier
