#include <iostream>
#include <vector>
#include <conio.h>
#include <queue>

using namespace std;

void swap(std::vector<int> & data, int i, int j)
{
	int tmp = data[i];
	data[i] = data[j];
	data[j] = tmp;
}

void print(std::vector<int> const & data)
{
	std::vector<int>::const_iterator iter = data.begin();

	for (; iter != data.end(); ++iter)
	{
		cout << *iter << " ";
	}

	if (data.size() > 0)
	{
		cout << endl;
	}
}

int generateRandom(int low, int high);
void Shuffle(std::vector<int> & data)
{
	int length = data.size();

	for (int i = 0; i < length - 1; ++i)
	{
		swap(data, i, generateRandom(i + 1, length - 1));
	}

	print(data);
}

int generateRandom(int low, int high)
{
	srand(low);
	int gen = 0;
	gen = rand() % (high - low + 1) + low;
	return gen;
}

//useful for small lists, and for large lists where data is
//already sorted
void BubbleSort(std::vector<int> & data)
{
	int length = data.size();

	for (int i = 0; i < length; ++i)
	{
		bool swapped = false;
		for (int j = 0; j < length - (i + 1); ++j)
		{
			if (data[j] > data[j + 1])
			{
				swap(data, j, j + 1);
				swapped = true;
			}
		}

		if (!swapped) break;
	}
}

//useful for small lists and where swapping is expensive
// does at most n swaps
void SelectionSort(std::vector<int> & data)
{
	int length = data.size();

	for (int i = 0; i < length; ++i)
	{
		int min = i;
		for (int j = i + 1; j < length; ++j)
		{
			if (data[j] < data[min])
			{
				min = j;
			}
		}

		if (min != i)
		{
			swap(data, i, min);
		}
	}
}

//useful for small and mostly sorted lists
//expensive to move array elements
void InsertionSort(std::vector<int> & data)
{
	int length = data.size();

	for (int i = 1; i < length; ++i)
	{
		bool inplace = true;
		int j = 0;
		for (; j < i; ++j)
		{
			if (data[i] < data[j])
			{
				inplace = false;
				break;
			}
		}

		if (!inplace)
		{
			int save = data[i];
			for (int k = i; k > j; --k)
			{
				data[k] = data[k - 1];
			}
			data[j] = save;
		}
	}
}

void Merge(std::vector<int> & data, int lowl, int highl, int lowr, int highr);
void MergeSort(std::vector<int> & data, int low, int high)
{
	if (low >= high)
	{
		return;
	}

	int mid = low + (high - low) / 2;

	MergeSort(data, low, mid);

	MergeSort(data, mid + 1, high);

	Merge(data, low, mid, mid + 1, high);
}

void Merge(std::vector<int> & data, int lowl, int highl, int lowr, int highr)
{
	int tmp_low = lowl;
	std::vector<int> tmp;

	while (lowl <= highl && lowr <= highr)
	{
		if (data[lowl] < data[lowr])
		{
			tmp.push_back(data[lowl++]);
		}
		else if (data[lowr] < data[lowl])
		{
			tmp.push_back(data[lowr++]);
		}
		else
		{
			tmp.push_back(data[lowl++]);
			tmp.push_back(data[lowr++]);
		}
	}

	while (lowl <= highl)
	{
		tmp.push_back(data[lowl++]);
	}

	while (lowr <= highr)
	{
		tmp.push_back(data[lowr++]);
	}

	std::vector<int>::const_iterator iter = tmp.begin();

	for (; iter != tmp.end(); ++iter)
	{
		data[tmp_low++] = *iter;
	}
}

int Partition(std::vector<int> & data, int low, int high);
void QuickSort(std::vector<int> & data, int low, int high)
{
	if (low >= high) return;

	int p = Partition(data, low, high);

	QuickSort(data, low, p - 1);
	QuickSort(data, p + 1, high);
}

int Partition(std::vector<int> & data, int low, int high)
{
	int p = low;
	for (int i = p + 1; i <= high; ++i)
	{
		if (data[i] < data[p])
		{
			swap(data, i, p);
			if (i != p + 1)
			{
				swap(data, i, p + 1);
			}
			p = p + 1;
		}
	}

	return p;
}

//O(kN) k is max number of digits
int findMaxDigits(std::vector<int> & data);
void PutInQueues(std::queue<int>  q[], int qcount, std::vector<int> & data, int digit);
void GetPartialSorted(std::queue<int>  q[], int qcount, std::vector<int> & data);

void RadixSort(std::vector<int> & data)
{
	std::queue<int> q[10];
	int maxDigits = findMaxDigits(data);

	for (int i = 0; i < maxDigits; ++i)
	{
		PutInQueues(q, 10, data, i + 1);
		data.clear();
		GetPartialSorted(q, 10, data);
	}
}

int getDigitAt(int n, int digit);
void PutInQueues(std::queue<int>  q[], int qcount, std::vector<int> & data, int digit)
{
	std::vector<int>::const_iterator iter = data.begin();
	for (; iter != data.end(); ++iter)
	{
		int qpos = getDigitAt(*iter, digit);
		q[qpos].push(*iter);
	}
}

int getDigitAt(int n, int digit)
{
	int dig = 0;
	while (digit--)
	{
		dig = n % 10;
		n = n / 10;
	}
	return dig;
}

void GetPartialSorted(std::queue<int>  q[], int qcount, std::vector<int> & data)
{
	for (int i = 0; i < qcount; ++i)
	{
		if (q[i].size() > 0)
		{
			int length = q[i].size();
			while (length--)
			{
				data.push_back(q[i].front());
				q[i].pop();
			}
		}
	}
}

int numDigits(int n);
int findMaxDigits(std::vector<int> & data)
{
	std::vector<int>::const_iterator iter = data.begin();
	int max = 0;
	for (; iter != data.end(); ++iter)
	{
		int numd = numDigits(*iter);
		if (max < numd)
		{
			max = numd;
		}
	}

	return max;
}

int numDigits(int n)
{
	int count = 0;
	while (n != 0)
	{
		n = n / 10;
		++count;
	}

	return count;
}

int main()
{
	int a[] = { 5, 6, 1, 2, 0, 8, -1, -2, 8, 0 };
	std::vector<int> data(a, a + sizeof(a) / sizeof(int));

	//Bubble sort
	cout << "Bubble Sort" << endl;
	BubbleSort(data);
	print(data);

	//Selection sort
	Shuffle(data);
	cout << "Selection Sort" << endl;
	SelectionSort(data);
	print(data);

	//Insertion sort
	Shuffle(data);
	cout << "Insertion Sort" << endl;
	InsertionSort(data);
	print(data);

	//Merge sort
	Shuffle(data);
	cout << "Merge Sort" << endl;
	MergeSort(data, 0, data.size() - 1);
	print(data);

	//Quick sort
	Shuffle(data);
	cout << "Quick Sort" << endl;
	QuickSort(data, 0, data.size() - 1);
	print(data);

	//Radix Sort
	int b[] = { 123, 6, 24, 4567, 45, 989834, 98, 23, 8, 0 };
	std::vector<int> rdata(b, b + sizeof(b) / sizeof(int));
	RadixSort(rdata);
	//print(rdata);

	_getch();
}