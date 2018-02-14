#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <stdio.h>
#include <iomanip>
#include <stack>

using namespace std;

// A binary search based function to find the position
// where item should be inserted
int binarySearch(int a[], int item, int low, int high) {
	if (high <= low)
		return (item > a[low])? (low + 1): low;

	int mid = (low + high)/2;

	if(item == a[mid])
		return mid+1;

	if(item > a[mid])
		return binarySearch(a, item, mid+1, high);
	return binarySearch(a, item, low, mid-1);
}

// Function to sort an array a[] of size 'n'
void binary_insertionSort(int a[], int n) {
	int i, loc, j, k, selected;

	for (i = 1; i < n; ++i)
	{
		j = i - 1;
		selected = a[i];

		// find location where selected sould be inseretd
		loc = binarySearch(a, selected, 0, j);

		// Move all elements after location to create space
		while (j >= loc)
		{
			a[j+1] = a[j];
			j--;
		}
		a[j+1] = selected;
	}
}

void insertion_sort (int arr[], int length){
	 	int j, temp;

	for (int i = 0; i < length; i++){
		j = i;

		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}
}

// A function implementing Shell sort.
void ShellSort(int a[], int n)
{
	int i, j, k, temp;
	// Gap 'i' between index of the element to be compared, initially n/2.
	for(i = n/2; i > 0; i = i/2)
	{
		for(j = i; j < n; j++)
		{
			for(k = j-i; k >= 0; k = k-i)
			{
				// If value at higher index is greater, then break the loop.
				if(a[k+i] >= a[k])
				break;
				// Switch the values otherwise.
				else
				{
					temp = a[k];
					a[k] = a[k+i];
					a[k+i] = temp;
				}
			}
		}
	}
}


void quickSort(int *numbers, int left, int right)
{
  int pivot; // разрешающий элемент
  int l_hold = left; //левая граница
  int r_hold = right; // правая граница
  pivot = numbers[left];
  while (left < right) // пока границы не сомкнутся
  {
    while ((numbers[right] >= pivot) && (left < right))
      right--; // сдвигаем правую границу пока элемент [right] больше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      numbers[left] = numbers[right]; // перемещаем элемент [right] на место разрешающего
      left++; // сдвигаем левую границу вправо
    }
    while ((numbers[left] <= pivot) && (left < right))
      left++; // сдвигаем левую границу пока элемент [left] меньше [pivot]
    if (left != right) // если границы не сомкнулись
    {
      numbers[right] = numbers[left]; // перемещаем элемент [left] на место [right]
      right--; // сдвигаем правую границу вправо
    }
  }
  numbers[left] = pivot; // ставим разрешающий элемент на место
  pivot = left;
  left = l_hold;
  right = r_hold;
  if (left < pivot) // Рекурсивно вызываем сортировку для левой и правой части массива
    quickSort(numbers, left, pivot - 1);
  if (right > pivot)
    quickSort(numbers, pivot + 1, right);
}

/*
void swap_in_array(int* array, int i, int j)
 {
     int tmp;
     tmp=array[i];
     array[i]=array[j];
     array[j]=tmp;
 }

int partition(int* array, int l, int r)
 {
     int pivot,i,j;


    pivot=array[l];
     i=l+1;
     j=r;

     for(;;)
     {
         while((array[i] <= pivot) && (i <= r))i++;
         while((array[j] > pivot) && (j > l))j--;

         if(i < j)
             swap_in_array(array,i,j);
         else
             break;
     }
     swap_in_array(array,j,l);

     return j;
 }

void quicksort_it(int *dataset,int l,int r)
{
    stack<int> st;
    int j;
    st.push(r);
    st.push(l);
    while(!st.empty())
    {
        l=st.top();
        st.pop();
        r=st.top();
        st.pop();

        j=partition(dataset,l,r);

        if(l < (j-1))
        {
            st.push(j-1);
            st.push(l);
        }
        if((j+1) < r)
        {
            st.push(r);
            st.push(j+1);
        }
    }

}
*/

void sortComparisonChrono(int array_size) {
    int *linear_array = new int[array_size];
    int *linear_binary_array = new int[array_size];
    int *shell_array = new int[array_size];
    int *quick_array = new int[array_size];

    srand(time(NULL));

    for(int i = 0; i < array_size; i++) {
        linear_array[i] = rand()%15000 + 1;
        linear_binary_array[i] = linear_array[i];
        shell_array[i] = linear_array[i];
        quick_array[i] = linear_array[i];
    }

    //cout <<

    auto start_time = std::chrono::system_clock::now();
    insertion_sort(linear_array, array_size);
    auto end_time = std::chrono::system_clock::now();
    auto elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << "Time for array[" << array_size << "] with linear insertion sort: " << elapsed_ns.count() << " ns.\n";

    start_time = std::chrono::system_clock::now();
    binary_insertionSort(linear_binary_array, array_size);
    end_time = std::chrono::system_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << "Time for array[" << array_size << "] with binary insertion sort: " << elapsed_ns.count() << " ns.\n\n";

    start_time = std::chrono::system_clock::now();
    ShellSort(shell_array, array_size);
    end_time = std::chrono::system_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << "Time for array[" << array_size << "] with Shell sort: " << elapsed_ns.count() << " ns.\n";

    start_time = std::chrono::system_clock::now();
    quickSort(quick_array, 0, array_size);
    end_time = std::chrono::system_clock::now();
    elapsed_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
    cout << "Time for array[" << array_size << "] with quick sort: " << elapsed_ns.count() << " ns.\n\n";


    delete linear_array;
    delete linear_binary_array;
    delete shell_array;
    delete quick_array;
}

void sortComparisonClock(int array_size) {

    int *linear_array = new int[array_size];
    int *linear_binary_array = new int[array_size];
    int *shell_array = new int[array_size];
    int *quick_array = new int[array_size];

    srand(time(NULL));

    for(int i = 0; i < array_size; i++) {
        linear_array[i] = rand()%101;
        linear_binary_array[i] = linear_array[i];
        shell_array[i] = linear_array[i];
        quick_array[i] = linear_array[i];
    }

    cout << setw(9) << array_size << "\t";

    clock_t start_time = clock();
    insertion_sort(linear_array, array_size);
    clock_t end_time = clock();
    double seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    //cout << "Time for array[" << array_size << "] with linear insertion sort: " << seconds << " s.\n";
    cout << setw(6) << seconds << "\t";

    start_time = clock();
    binary_insertionSort(linear_binary_array, array_size);
    end_time = clock();
    seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    //cout << "Time for array[" << array_size << "] with binary insertion sort: " << seconds << " s.\n\n";
    cout << setw(6) << seconds << "\t";

    start_time = clock();
    ShellSort(shell_array, array_size);
    end_time = clock();
    seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    //cout << "Time for array[" << array_size << "] with Shell sort: " << seconds << " s.\n";
    cout << setw(6) << seconds << "\t";

    start_time = clock();
    quickSort(quick_array, 0, array_size-1);
    end_time = clock();
    seconds = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    //cout << "Time for array[" << array_size << "] with quick sort: " << seconds << " s.\n\n";
    cout << setw(6) << seconds << "\n";


    delete linear_array;
    delete linear_binary_array;
    delete shell_array;
    delete quick_array;
}


int main() {
    cout << setw(9) << "size\t" << setw(6) << "linear\t" << setw(6) << "binary\t" << setw(6) << "shell\t" << setw(6) << "quick\t" << endl;
    cout << "----------------------------------------------\n";
    for (int elements = 2; elements <= 1000000; elements*=2){
        sortComparisonClock(elements);
    }
    system("pause");
    return 0;
}
