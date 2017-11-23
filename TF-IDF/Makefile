#Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

main: main.o tfidf.o porter.o
		$(CXX) $(CXXFLAGS) -o main out/main.o out/tfidf.o out/porter.o

main.o: main.cpp tfidf.h porter.h
		$(CXX) $(CXXFLAGS) -c main.cpp

tfidf.o: tfidf.h

porter.o: porter.h
