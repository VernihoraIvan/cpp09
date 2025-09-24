#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <utility>

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::list<int> _list;
	double _vecTime;
	double _listTime;

	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

	// Private methods for vector
    void initialPairing(std::vector<std::pair<int, int> > &pairs);
	void sortVector();
	void initialSort(std::vector<std::pair<int, int> > &pairs);
	// ... any other helper functions for vector ...

	// Private methods for list
	void sortList();
	void mergeInsertSort(std::list<int> &list);
	// ... any other helper functions for list ...
    void setVecTime(double time);
    void setListTime(double time);

public:
	PmergeMe();
	~PmergeMe();

	void parseAndStore(int argc, char **argv);
	void executeSort();
	void printResults();
};

#endif
