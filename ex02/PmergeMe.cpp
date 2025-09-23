#include "PmergeMe.hpp"
#include <climits>

// Default constructor
PmergeMe::PmergeMe() : _vecTime(0.0), _listTime(0.0) {}

// Destructor
PmergeMe::~PmergeMe() {}

// Copy constructor and assignment operator (private to prevent copying)
PmergeMe::PmergeMe(const PmergeMe &other)
{
	*this = other;
}

void PmergeMe::setVecTime(double time)
{
	_vecTime = time;
}

void PmergeMe::setListTime(double time)
{
	_listTime = time;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (this != &other)
	{
		_vec = other._vec;
		_list = other._list;
		_vecTime = other._vecTime;
		_listTime = other._listTime;
	}
	return *this;
}

void printVector(const std::vector<int> &vec)
{
	std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); ++i)
		std::cout << vec[i] << " ";
	std::cout << std::endl;
}

void printList(const std::list<int> &list)
{
	std::cout << "Before: ";
	for (std::list<int>::const_iterator it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
// Method to parse and store the input sequence
void PmergeMe::parseAndStore(int argc, char **argv)
{
	for (int i = 1; i < argc; ++i)
	{
		std::string arg = argv[i];
		for (size_t j = 0; j < arg.length(); ++j)
		    if (!isdigit(arg[j]))
			    throw std::runtime_error("Error: Invalid character in input.");
		long num = atol(arg.c_str());
		if (num > INT_MAX)
			throw std::runtime_error("Error: Input number too large.");
		if (num <= 0)
			throw std::runtime_error("Error: Input must be positive integers.");
		_vec.push_back(static_cast<int>(num));
		_list.push_back(static_cast<int>(num));
	}
	printVector(_vec);
	printList(_list);
	if (_vec.empty())
		throw std::runtime_error("Error: No input numbers provided.");
}

// Method to execute the sorting process for both containers
void PmergeMe::executeSort()
{
    clock_t start = clock();
	sortVector();
    clock_t vecEnd = clock();
    setVecTime(static_cast<double>(vecEnd - start) / CLOCKS_PER_SEC * 1000000);

    clock_t startList = clock();
	sortList();
    clock_t listEnd = clock();
    setListTime(static_cast<double>(listEnd - startList) / CLOCKS_PER_SEC * 1000000);
}

// Method to print the results
void PmergeMe::printResults()
{
	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
		std::cout << _vec[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "Time to process a range of " << _vec.size()
			  << " elements with std::vector : " << std::fixed << std::setprecision(5) << _vecTime
			  << " us" << std::endl;
	std::cout << "Time to process a range of " << _list.size()
			  << " elements with std::list  : " << std::fixed << std::setprecision(5) << _listTime
			  << " us" << std::endl;
}

// Stubs for the sorting methods
void PmergeMe::sortVector()
{
    if (_vec.empty())
        throw std::runtime_error("Error: No input numbers provided.");
    if (_vec.size() == 1)
        return;
    // mergeInsertSort(_vec);
	
}

void PmergeMe::sortList()
{
	// Timing and sorting logic for list will go here
}
