//
//  main.cpp
//  15Sorting
//
//  Created by Hackerman on 26/12/2022.
//

// https://www.youtube.com/watch?v=kPRA0W1kECg

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>

class SortingAnalytics {
public:
    static void incrementAccess()
    {
        accesses++;
    }
    static void incrementComparisons()
    {
        comparisons++;
    }
    static void reset()
    {
        accesses = 0;
        comparisons = 0;
    }
#define INCREMENT_ACCESS SortingAnalytics::incrementAccess();
#define INCREMENT_COMPARISONS SortingAnalytics::incrementComparisons();

    
    static void print()
    {
        std::cout << "accesses: " << accesses << "\ncomparisons: " << comparisons << "\n";
    }
    static void approximateBigO(int items)
    {
        int y = accesses + comparisons;
        if (y < items) {
            std::cout << "O(n)\n";
        }
        else if (y < (items * log(items))) {
            std::cout << "O(n log n)\n";
        }
        else if (y < (items * log(items) * 3)) {
            std::cout << "O(n3 log n)\n";
        }
        else if (y < (items * log(items) * 5)) {
            std::cout << "O(n5 log n)\n";
        }
        else if (y < (items * items)) {
            std::cout << "O(n ^ 2)\n";
        }
        else if (y < pow(2, items)) {
            std::cout << "O(2 ^ n)\n";
        }
        else {
            std::cout << "O Terrible\n";
        }
    }
private:
    static int accesses;
    static int comparisons;
};

int SortingAnalytics::accesses = 0;
int SortingAnalytics::comparisons = 0;



template <typename T>
static std::vector<T> generateRandom(int its) {
    
    srand(time(0));

    std::vector<T> vals;
    vals.reserve(its);
    while (its--) {
        
        vals.push_back((T) rand());
        
    }
    return vals;
}



template <typename T>
void selectionSort(std::vector<T> & array)
{
    for (int i = 0; i < array.size()-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < array.size(); j++) {
            minIndex = (array[j] < array[minIndex]) ? j : minIndex;
            INCREMENT_COMPARISONS
        }
        std::swap(array[i], array[minIndex]);
        INCREMENT_ACCESS INCREMENT_ACCESS
    }
}

template <typename T>
void insertionSort(std::vector<T> & array)
{
    for (int i = 1; i < array.size(); i++) {
        T key = array[i];
        int j = i-1;
        INCREMENT_COMPARISONS
        while (key < array[j] && j >= 0) {
            std::swap(array[j+1], array[j]);
            INCREMENT_ACCESS INCREMENT_ACCESS
            j--;
            INCREMENT_COMPARISONS
        }
    }
}

template <typename T>
void quickSort(std::vector<T> & array)
{
    struct localQSort {
        static void quickSort(std::vector<T> array, int low, int high)
        {
            INCREMENT_COMPARISONS
            if (low < high) {
                int pi = partition(array, low, high);
                quickSort(array, low, pi - 1);
                quickSort(array, pi + 1, high);
            }
        }
        static int partition(std::vector<T> array, int low, int high)
        {
            const int pivot = array[high]; // pivot
            int i = (low-1);
            
            for (int j = low; j <= high - 1; j++) {
                INCREMENT_COMPARISONS
                if (array[j] < pivot) {
                    i++;
                    std::swap(array[i], array[j]);
                    INCREMENT_ACCESS INCREMENT_ACCESS
                }
            }
            std::swap(array[i+1], array[high]);
            INCREMENT_ACCESS INCREMENT_ACCESS

            return i+1;
        }
    };
    localQSort::quickSort(array, 0, (int) array.size()-1);
    
    
}

//TODO quick sort

template <typename T>
void bubbleSort(std::vector<T> & array)
{
    for (int i = 0; i < array.size()-1; i++) {
        bool didswap = false;
        for (int j = 0; j < array.size()-i-1; j++) {
            INCREMENT_COMPARISONS
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                INCREMENT_ACCESS INCREMENT_ACCESS
                didswap = true;
            }
        }
        if (!didswap) {
            break;
        }
    }
}

template <typename T>
void cocktailSort(std::vector<T> & array)
{
    bool swapped = true;
    int start = 0;
    int end = array.size()-1;
    
    while (swapped) {
        swapped = false;
        for (int j = start; j < end; j++) {
            INCREMENT_COMPARISONS
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                swapped = true;
                INCREMENT_ACCESS INCREMENT_ACCESS
            }
        }
        
        if (!swapped) {
            break;
        }
        swapped = false;
        end--;
        
        for (int j = end; j >= start; j--) {
            INCREMENT_COMPARISONS
            if (array[j] > array[j+1]) {
                std::swap(array[j], array[j+1]);
                swapped = true;
                INCREMENT_ACCESS INCREMENT_ACCESS
            }
        }
    }
    
}

// very intresting algorithm good for memory!
template <typename T>
void cycleSort(std::vector<T> & array) {
    
    

    for (int start = 0; start < array.size()-1; start++) {
        T item = array[start];
        int location = start;
        
        for (int i = start+1; i < array.size(); i++) {
            INCREMENT_COMPARISONS
            if (array[i] < item) {
                location++;
            }
        }
        if (location == start) {
            continue;
        }
        while (item == array[location]) { // check for duplicates
            location++;
        }
        
        if (location != start) {
            std::swap(item, array[location]);
            INCREMENT_ACCESS INCREMENT_ACCESS
            
        }
        
        while (location != start) {
            location = start;
            for (int i = start + 1; i < array.size(); i++) {
                INCREMENT_COMPARISONS
                if (array[i] < item) {
                    location++;
                }
            }
            while (item == array[location]) {
                location++;
            }
            INCREMENT_COMPARISONS
            if (item != array[location]) {
                std::swap(item, array[location]);
                INCREMENT_ACCESS INCREMENT_ACCESS
                
            }
        }
    }
    
    /*
     
     Begin
     for
     start:= 0 to n - 2 do
     key := array[start]
     location := start
     for i:= start + 1 to n-1 do
       if array[i] < key then
          location: =location +1
     done
     if location = start then
         ignore lower part, go for next iteration
     while key = array[location] do
        location = location
     done
     if location != start then
         swap array[location] with key
     while location != start do
         location start


     for i:= start + 1 to n-1 do
          if array[i] < key then
               location: =location +1
     done
     while key= array[location]
           location := location +1
      if key != array[location]
           Swap array[location] and key
        done
      done
     End
     */
}


template <typename T>
void testIsSorted(std::vector<T> & array)
{
    for (int i = 1; i < array.size(); i++) {
        if (array[i] < array[i]) {
            assert(false);
        }
    }
}



int main(int argc, const char * argv[])
{
    // insert code here...
    
//    std::vector<int> ar = { 64, 25, 12, 22, 11, 100, 125, 1212, 0, 1};
    std::vector<int> ar = generateRandom<int>(500);
    
//    bubbleSort(ar);
    
//    selectionSort(ar);
//    cocktailSort(ar);
//    insertionSort(ar);
    cycleSort(ar);
//    quickSort(ar);
    SortingAnalytics::print();
    SortingAnalytics::approximateBigO(500);
//    testIsSorted(ar);
//    for (auto i : ar) {
//        std::cout << i << ", ";
//    }
//    std::cout << "\n";
//
    
    return 0;
}
