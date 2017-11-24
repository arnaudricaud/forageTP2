#Makefile

CXX = g++
CXXFLAGS = -Wall -std=c++11 -g -fpermissive

main: main.o tfidf.o porter.o porterWord.o kmeans.o cah.o cluster.o document.o
		$(CXX) $(CXXFLAGS) -o main main.o tfidf.o porter.o porterWord.o kmeans.o cah.o cluster.o document.o

main.o: main.cpp tfidf.h porter.h kmeans.h
		$(CXX) $(CXXFLAGS) -c main.cpp

tfidf.o: tfidf.h porterWord.h

porter.o: porter.h

porterWord.o: porterWord.h

cah.o: cah.h cluster.h

cluster.o: cluster.h

document.o: document.h cluster.h

kmean.o: kmeans.h document.h cluster.h
