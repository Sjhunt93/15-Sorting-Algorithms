//
//  main.cpp
//  15Sorting
//
//  Created by Hackerman on 26/12/2022.
//

#include <iostream>
#include <vector>
#include <cstdlib>



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
        std::cout << "accesses: " << accesses << " comparisons: " << comparisons << "\n";
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
            INCREMENT_ACCESS
            j--;
            INCREMENT_COMPARISONS
        }
    }
}




int main(int argc, const char * argv[])
{
    // insert code here...
    
//    std::vector<int> ar = { 64, 25, 12, 22, 11, 100, 125, 1212, 0, 1};
    std::vector<int> ar = generateRandom<int>(500);
    selectionSort(ar);
    
    SortingAnalytics::print();
    
//    for (auto i : ar) {
//        std::cout << i << ", ";
//    }
//    std::cout << "\n";
    
    
    return 0;
}
