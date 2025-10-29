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
#include <climits>


#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define DEBUG false
#define MAX_PRINT_COUNT 50

class PmergeMe
{
private:
	std::vector<int> _vec;
	std::list<int> _list;
	double _vecTime;
	double _listTime;

	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);

	void sortVector();
	void mergeInsertSortVector(std::vector<int> &vec);

	void sortList();
	void mergeInsertSortList(std::list<int> &list);

    void setVecTime(double time);
    void setListTime(double time);
	void printContainer(const std::vector<int> &vec);

public:
	PmergeMe();
	~PmergeMe();

	void parseAndStore(int argc, char **argv);
	void executeSort();
	void printResults();
};

#endif
