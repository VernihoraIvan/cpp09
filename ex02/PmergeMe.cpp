#include "PmergeMe.hpp"
#include <climits>

#define BLUE "\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define DEBUG false
const int MAX_PRINT_COUNT = 50;

PmergeMe::PmergeMe() : _vecTime(0.0), _listTime(0.0) {}

PmergeMe::~PmergeMe() {}

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

void printContainer(const std::vector<int> &vec)
{
    if (DEBUG)
        std::cout << BLUE << "Before: " << RESET;
    else
        std::cout << "Before: ";
	for (size_t i = 0; i < vec.size(); ++i)
    {
        if (i >= MAX_PRINT_COUNT)
        {
            std::cout << "[...]";
            break;
        }
		std::cout << vec[i] << " ";
    }
	std::cout << std::endl;
}


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
	printContainer(_vec);
	if (_vec.empty())
		throw std::runtime_error("Error: No input numbers provided.");
}

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

void PmergeMe::printResults()
{
	std::cout << "After:  ";
	for (size_t i = 0; i < _vec.size(); ++i)
	{
        if (i >= MAX_PRINT_COUNT)
        {
            std::cout << "[...]";
            break;
        }
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

void PmergeMe::initialPairing(const std::vector<int> &vec, std::vector<std::pair<int, int> > &pairs)
{
    for (size_t i = 0; i < vec.size(); i += 2)
    {
        if (i + 1 < vec.size())
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        else
            pairs.push_back(std::make_pair(vec[i], 0));
    }
}

void PmergeMe::initialSort(std::vector<std::pair<int, int> > &pairs)
{
    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (pairs[i].first > pairs[i].second)
            std::swap(pairs[i].first, pairs[i].second);
    }
}

void printPairs(const std::vector<std::pair<int, int> > &pairs)
{
	for (size_t i = 0; i < pairs.size(); i++)
	{
		std::cout << BLUE << "pair[" << i << "]: " << pairs[i].first << " " << pairs[i].second << RESET << std::endl;
	}
}

void PmergeMe::mergeInsertSort(std::vector<int> &vec)
{
	if (vec.size() <= 1)
		return;

	// Handle the stray element if the sequence size is odd.
	int stray = -1;
	if (vec.size() % 2 != 0)
	{
		stray = vec.back();
		vec.pop_back();
	}

	// Pair up elements and sort them internally to (larger, smaller).
	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
		else
			pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
	}

	// Create the main chain (larger elements) and pendulum chain (smaller elements).
	std::vector<int> mainChain;
	std::vector<int> pendChain;
	for (size_t i = 0; i < pairs.size(); i++)
	{
		mainChain.push_back(pairs[i].first);
        if (DEBUG)
            std::cout << GREEN << "mainChain.push_back(" << pairs[i].first << ")" << RESET << std::endl;
		pendChain.push_back(pairs[i].second);
        if (DEBUG)
            std::cout << GREEN << "pendChain.push_back(" << pairs[i].second << ")" << RESET << std::endl;
	}

	// Recursively sort the main chain.
	mergeInsertSort(mainChain);

	if (!pendChain.empty())
		mainChain.insert(mainChain.begin(), pendChain[0]);

	// Generate Jacobsthal numbers to determine the optimal insertion order.
	std::vector<int> jacob_indices;
	int j_prev = 1;
	int j_curr = 3;
	while (j_prev < (int)pendChain.size()) {
		jacob_indices.push_back(std::min((int)pendChain.size(), j_curr));
		int temp = j_curr;
		j_curr = j_curr + 2 * j_prev;
		j_prev = temp;
	}

	// Insert elements in groups based on the Jacobsthal sequence, working backwards.
	// The jacob_indices vector now holds the boundaries for our insertion groups
	int last_inserted_idx = 1;
	for (size_t i = 0; i < jacob_indices.size(); ++i)
	{
		int group_end = jacob_indices[i];
		for (int j = group_end; j > last_inserted_idx; --j)
		{
			int val = pendChain[j - 1];
			std::vector<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), val);
			mainChain.insert(insertion_point, val);
		}
		last_inserted_idx = group_end;
	}

	// Insert any remaining elements not covered by the Jacobsthal sequence
	for (size_t i = last_inserted_idx; i < pendChain.size(); ++i)
	{
		int val = pendChain[i];
		std::vector<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), val);
		mainChain.insert(insertion_point, val);
	}

	// Insert the stray element if it exists.
	if (stray != -1)
	{
		std::vector<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), stray);
		mainChain.insert(insertion_point, stray);
	}

	vec = mainChain;
}

void PmergeMe::mergeInsertSort(std::list<int> &list)
{
    if (list.size() <= 1)
        return;

    int stray = -1;
    if (list.size() % 2 != 0)
    {
        stray = list.back();
        list.pop_back();
    }

    std::list<std::pair<int, int> > pairs;
    for (std::list<int>::iterator it = list.begin(); it != list.end(); )
    {
        int first = *it;
        it++;
        int second = *it;
        it++;
        if (first > second)
            pairs.push_back(std::make_pair(first, second));
        else
            pairs.push_back(std::make_pair(second, first));
    }

    std::list<int> mainChain;
    std::list<int> pendChain;
    for (std::list<std::pair<int, int> >::iterator it = pairs.begin(); it != pairs.end(); ++it)
    {
        mainChain.push_back(it->first);
        pendChain.push_back(it->second);
    }

    mergeInsertSort(mainChain);

    if (!pendChain.empty())
        mainChain.push_front(pendChain.front());

    std::vector<int> jacob_indices;
    int j_prev = 1, j_curr = 3;
    while (j_prev < (int)pendChain.size()) {
        jacob_indices.push_back(std::min((int)pendChain.size(), j_curr));
        int temp = j_curr;
        j_curr = j_curr + 2 * j_prev;
        j_prev = temp;
    }

    int last_inserted_idx = 1;
    for (size_t i = 0; i < jacob_indices.size(); ++i)
    {
        int group_end = jacob_indices[i];
        for (int j = group_end; j > last_inserted_idx; --j)
        {
            std::list<int>::iterator pend_it = pendChain.begin();
            std::advance(pend_it, j - 1);
            int val = *pend_it;

            std::list<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), val);
            mainChain.insert(insertion_point, val);
        }
        last_inserted_idx = group_end;
    }

    for (size_t i = last_inserted_idx; i < pendChain.size(); ++i)
    {
        std::list<int>::iterator pend_it = pendChain.begin();
        std::advance(pend_it, i);
        int val = *pend_it;
        std::list<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), val);
        mainChain.insert(insertion_point, val);
    }

    if (stray != -1)
    {
        std::list<int>::iterator insertion_point = std::lower_bound(mainChain.begin(), mainChain.end(), stray);
        mainChain.insert(insertion_point, stray);
    }

    list = mainChain;
}

void PmergeMe::sortVector()
{
    if (_vec.empty())
        throw std::runtime_error("Error: No input numbers provided.");
    if (_vec.size() == 1)
        return;
    mergeInsertSort(_vec);
}

void PmergeMe::sortList()
{
	if (_list.empty())
		throw std::runtime_error("Error: No input numbers provided.");
	if (_list.size() == 1)
		return;
	mergeInsertSort(_list);
}
