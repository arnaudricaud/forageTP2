#Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

main: main.o tfidf.o porter.o porterWord.o
		$(CXX) $(CXXFLAGS) -o main main.o tfidf.o porter.o porterWord.o

main.o: main.cpp tfidf.h porter.h
		$(CXX) $(CXXFLAGS) -c main.cpp

tfidf.o: tfidf.h porterWord.h

porter.o: porter.h

porterWord.o: porterWord.h
