/*-----------------------------------------------------------------------------------------------

*/
#ifndef BENCHMARK
#define BENCHMARK

#include<iostream>
#include<cstdlib>
#include<chrono>
#include<algorithm>
#include<random>
#include<ctime>

int Array[20], size = 20;

class BenchmarkTimer
{
public:
	std::chrono::time_point<std::chrono::high_resolution_clock> startpt;
	float ms;
	long long duration;
	BenchmarkTimer() : ms(0), duration(0)
	{
		startpt = std::chrono::high_resolution_clock::now();
	}
	~BenchmarkTimer()
	{
		FinalizeTiming();
	}
	void FinalizeTiming(void)
	{
		auto endpt = std::chrono::high_resolution_clock::now();
		auto init = std::chrono::time_point_cast<std::chrono::milliseconds>(startpt).time_since_epoch().count();
		auto final = std::chrono::time_point_cast<std::chrono::milliseconds>(endpt).time_since_epoch().count();
		duration = final - init;
	}
};

void DisplayInformation(void);
void SelectionSort(int[]);
void RecursiveBubbleSort(int[], int);
void RecursiveInsertionSort(int[], int);
void SortFnCPP_STL(int[]);
void ShellSort(int[]);
void CycleSort(int[]);
void CocktailShakerSort(int[]);
void GnomeSort(int[]);
void BrickSort(int[]);

void RandomArrayGenerator()
{
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
		Array[i] = rand();

	std::cout << "\nThe original integer array is: " << std::endl;
	for (int i = 0; i < 20; i++)
		std::cout << Array[i] << "  ";
	SelectionSort(Array);
	RecursiveBubbleSort(Array, size);
	RecursiveInsertionSort(Array, size);
	SortFnCPP_STL(Array);
	ShellSort(Array);
	CycleSort(Array);
	CocktailShakerSort(Array);
	GnomeSort(Array);
	BrickSort(Array);
	
}

void DisplayArray(int Array[])
{
	std::cout << "\n\nThe sorted array is: ";
	for (int i = 0; i < size; i++)
		std::cout << Array[i] << "   ";	
}

void SelectionSort(int Array[])
{
	BenchmarkTimer timer;
	int temp, smallest, position, j;
	for (int i = 0; i < size - 1; i++)
	{
		smallest = Array[i];
		position = i;
		for (j = i + 1; j < size; j++)
			if (Array[j] < smallest)
			{
				smallest = Array[j];
				position = j;
			}
		temp = Array[i];
		Array[i] = Array[position];
		Array[position] = temp;
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Selection Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void RecursiveBubbleSort(int Array[], int size)
{
	int temp;
	BenchmarkTimer timer;
	if (size == 1)
	{
		DisplayArray(Array);
		timer.FinalizeTiming();
		std::cout << "\nTime taken to sort the array using Recursive Bubble Sort: " << timer.duration << " ms" << std::endl;
		std::cout << "\n----------------------------------------------------------------------------------------------------------";
		return;
	}

	for (int i = 0; i < size - 1; i++)
		if (Array[i] > Array[i + 1])
		{
			temp = Array[i];
			Array[i] = Array[i + 1];
			Array[i + 1] = temp;
		}
	RecursiveBubbleSort(Array, size - 1);
}

void RecursiveInsertionSort(int Array[], int size)
{
	BenchmarkTimer timer;
	if (size <= 1)
	{
		DisplayArray(Array);
		timer.FinalizeTiming();
		std::cout << "\nTime taken to sort the array using Recursive Insertion Sort: " << timer.duration << " ms" << std::endl;
		std::cout << "\n----------------------------------------------------------------------------------------------------------";
		return;
	}
	RecursiveInsertionSort(Array, size - 1);

	int Final = Array[size - 1];
	int j = size - 2;

	while (j >= 0 && Array[j] > Final)
	{
		Array[j + 1] = Array[j];
		j--;
	}
	Array[j + 1] = Final;
}

void SortFnCPP_STL(int Array[])
{ 
	BenchmarkTimer timer;
	std::sort(Array, Array + size);
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using std::sort function: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void ShellSort(int Array[])
{
	BenchmarkTimer timer;
	for (int space = size / 2; space > 0; space /= 2)
	{
		for (int i = space; i < size; i++)
		{
			int temp = Array[i];
			int j;
			for (j = i; j >= space && Array[j - space] > temp; j -= space)
				Array[j] = Array[j - space];
			Array[j] = temp;
		}
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Shell Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void CycleSort(int Array[])
{
	BenchmarkTimer timer;
	int writeCount = 0;

	for (int cycleStart = 0; cycleStart < size - 1; cycleStart++)
	{
		int temp = Array[cycleStart];
		int pos = cycleStart;
		for (int i = cycleStart + 1; i < size; i++)
		{
			if (Array[i] < temp)
				pos += 1;
		}

		if (pos == cycleStart)
			continue;

		while (temp == Array[pos])
			pos += 1;	
		int t = Array[pos];
		Array[pos] = temp;
		temp = t;
		writeCount++;

		while (pos != cycleStart)
		{
			pos = cycleStart;
			for (int i = cycleStart + 1; cycleStart < size; cycleStart++)
			{
				if (Array[i] < temp)
					pos += 1;
			}

			while (temp == Array[pos])
				pos += 1;
			int t = Array[pos];
			Array[pos] = temp;
			temp = t;
			writeCount++;
		}
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Cycle Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void CocktailShakerSort(int Array[])
{
	BenchmarkTimer timer;
	bool swap = true;
	int initial = 0, final = size - 1, temp;
	
	while (swap)
	{
		swap = false;
		for (int i = initial; i < final; i++)
		{
			if (Array[i] > Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
				swap = true;
			}
		}

		if (!swap)
			break;

		swap = false;
		final--;
		for (int i = final - 1; i >= initial; i--)
		{
			if (Array[i] = Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
				swap = true;
			}
		}
		initial++;
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Cocktail Shaker Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void GnomeSort(int Array[])
{
	BenchmarkTimer timer;
	int key = 0, temp;
	while (key < size)
	{
		if (key == 0)
			key++;
		else if (Array[key] >= Array[key - 1])
			key++;
		else
		{
			temp = Array[key];
			Array[key] = Array[key - 1];
			Array[key - 1] = temp;
			key--;
		}
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Gnome Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void BrickSort(int Array[])
{
	BenchmarkTimer timer;
	int temp;
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 1; i <= size - 2; i += 2)
		{
			if (Array[i] > Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
				sorted = false;
			}
		}

		for (int i = 0; i <= size - 2; i += 2)
		{
			if (Array[i] > Array[i + 1])
			{
				temp = Array[i];
				Array[i] = Array[i + 1];
				Array[i + 1] = temp;
				sorted = false;
			}
		}
	}
	DisplayArray(Array);
	timer.FinalizeTiming();
	std::cout << "\nTime taken to sort the array using Brick Sort: " << timer.duration << " ms" << std::endl;
	std::cout << "\n----------------------------------------------------------------------------------------------------------";
}

void DisplayInformation()
{
	char choice;
	do
	{
		system("cls");
		std::cout << "\n\n\n\t\t\t\t\t\t\tSorting Algorithm Benchmarking Program" << std::endl << std::endl;
		std::cout << "---------------------------------------------------------------------------------------------------------------------------------------";
		std::cout << "\nThis program performs benchmarking operations to check which sorting algorithm is the fastest.\n";
		std::cout << "The following sorting algorithms are benchmarking candidates in this program:\n" << std::endl;
		std::cout << "1. Selection Sort\n2. Bubble Sort (using recursion)\n3. Insertion Sort (using recursion)"
			<< "\n4. std::sort function\n5. Shell Sort\n6. Cycle Sort\n7. Cocktail Shaker Sort\n8. Gnome Sort"
			<< "\n9. Brick Sort" << std::endl << std::endl;

		system("pause");
		system("cls");
		RandomArrayGenerator();
		std::cout << std::endl << "Would you like to perform another round of benchmarking?(Y/N): ";
		std::cin >> choice;
	} while (choice == 'y' || choice == 'Y');
	system("cls");
	std::cout << "\n\n\n\t\t\t\t\t\t\tThank you for using this program.";
}

#endif