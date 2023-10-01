#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <cassert>

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;

//========================================================================

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff =
            std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
private:
    std::chrono::high_resolution_clock::time_point m_time;
};

//========================================================================

// These are used for random number generation

std::random_device aRandomDevice;
std::default_random_engine generator(aRandomDevice());

// Here's a class that is not cheap to copy because the objects contain a
// large array.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

using IdType = int;

const int NWEEKS = 4 * 52;

struct Store
{
    IdType id;
    double total;
    double weeklySales[NWEEKS];
    Store(IdType i) : id(i)
    {
        std::uniform_int_distribution<> distro(20, 60);

        // create random sales figures (from 20 to 60)
        for (size_t k = 0; k < NWEEKS; k++)
            weeklySales[k] = distro(generator);
        // (accumulate computes 0.0 + weeklySales[0] + weeklySales[1] + ...)
        total = accumulate(weeklySales, weeklySales + NWEEKS, 0.0);
    }
};

inline
bool compareStore(const Store& lhs, const Store& rhs)
{
    // The Store with the higher total should come first.  If they have
    // the same total, then the Store with the smaller id number should
    // come first.  Return true iff lhs should come first.  Notice that
    // this means that a false return means EITHER that rhs should come
    // first, or there's a tie, so we don't care which comes first,

    if (lhs.total > rhs.total)
        return true;
    if (lhs.total < rhs.total)
        return false;
    return lhs.id < rhs.id;
}

inline
bool compareStorePtr(const Store* lhs, const Store* rhs)
{
    return compareStore(*lhs, *rhs);
}

void insertion_sort(vector<Store>& s, bool comp(const Store&, const Store&))
{
    for (int unsorted = 1; unsorted < s.size(); unsorted++)
    {
        Store nextItem = s[unsorted];
        int loc = unsorted; 
        while (loc > 0 && comp(nextItem,s[loc - 1]))
        {
            s[loc] = s[loc - 1];
            loc--; 
        }
        s[loc] = nextItem; 
    }
}

// Report the results of a timing test

void report(string caption, double t, const vector<Store>& s)
{
    cout << t << " milliseconds; " << caption
        << "; first few stores are\n\t";
    size_t n = s.size();
    if (n > 4)
        n = 4;
    for (size_t k = 0; k < n; k++)
        cout << " (" << s[k].id << ", " << s[k].total << ")";
    cout << endl;
}

// Verify that all ids from 0 to number of stores-1 are in vector
bool allPresent(const vector<Store>& stores)
{
    vector<int> present(stores.size(), 0);
    for (const auto& s : stores)
        present[s.id] = 1;
    return find(present.begin(), present.end(), 0) == present.end();
}

void sortUsingPtrs(vector<Store>& stores, bool comp(const Store*, const Store*));

int main()
{
    size_t nstores;
    cout << "Enter number of stores to sort: ";
    cin >> nstores;
    if (!cin || nstores <= 0)
    {
        cout << "You must enter a positive number.  Goodbye." << endl;
        return 1;
    }

    // Create a random ordering of id numbers 0 through nstores-1
    vector<IdType> ids;
    for (size_t j = 0; j < nstores; j++)
        ids.push_back(IdType(j));
    shuffle(ids.begin(), ids.end(), generator);  // from <algorithm>

    // Create a bunch of Stores
    vector<Store> unorderedStores;
    for (size_t k = 0; k < ids.size(); k++)
        unorderedStores.push_back(Store(ids[k]));

    // Create a timer

    Timer timer;

    // Sort the Stores using the STL sort algorithm.  It uses a variant
    // of quicksort called introsort.

    vector<Store> stores(unorderedStores);
    timer.start();
    sort(stores.begin(), stores.end(), compareStore);
    report("STL sort", timer.elapsed(), stores);
    assert(is_sorted(stores.begin(), stores.end(), compareStore));  // from <algorithm>

    // Sort the already sorted array using the STL sort.  This should be
    // fast.

    timer.start();
    sort(stores.begin(), stores.end(), compareStore);
    report("STL sort if already sorted", timer.elapsed(), stores);
    assert(is_sorted(stores.begin(), stores.end(), compareStore));

    if (TEST_INSERTION_SORT)
    {
        // Sort the original unsorted array using insertion sort.  This
        // should be really slow.  If you have to wait more than a minute,
        // try rerunning the program with a smaller number of Stores.

        stores = unorderedStores;
        timer.start();
        insertion_sort(stores, compareStore);
        double elapsed = timer.elapsed();
        if (is_sorted(stores.begin(), stores.end(), compareStore) && allPresent(stores))
        {
            report("insertion sort if not already sorted", elapsed, stores);

            // Sort the already sorted array using insertion sort.  This
            // should be fast.

            timer.start();
            insertion_sort(stores, compareStore);
            report("insertion sort if already sorted", timer.elapsed(), stores);
            assert(is_sorted(stores.begin(), stores.end(), compareStore) && allPresent(stores));
        }
        else
            cout << "[Skipping tests of insertion_sort, since it's not correctly implemented.]" << endl;
    }

    // Since Stores are expensive to copy, and since the STL's sort copies
    // Stores O(N log N) times, let's sort POINTERS to the Stores, then
    // make one final pass to rearrange the Stores according to the
    // reordered pointers.  We'll write some code; you write the rest
    // below in sortUsingPtrs.

    // Set stores to the original unsorted sequence
    stores = unorderedStores;

    // Start the timing
    timer.start();

    // Sort using pointers
    sortUsingPtrs(stores, compareStorePtr);

    // Report the timing and verify that the sort worked
    report("STL sort of pointers", timer.elapsed(), stores);

    // Until you correctly implement sortUsingPointers, this assertion will fail.
    assert(is_sorted(stores.begin(), stores.end(), compareStore) && allPresent(stores));
}

void sortUsingPtrs(vector<Store>& stores, bool comp(const Store*, const Store*))
{
    // Since Stores are expensive to copy, and since the STL's sort copies
    // Stores O(N log N) times, let's sort POINTERS to the Stores, then
    // make one final pass to rearrange the Stores according to the
    // reordered pointers.  We'll write some code; you write the rest.

    // Create an auxiliary copy of stores to facilitate the later reordering.
    vector<Store> auxStores(stores.begin(), stores.end());

    // TODO:  Create a vector of Store pointers, and set each pointer
    //        to point to the corresponding Store in auxStores.
    vector<Store*> storePointers;
    for (vector<Store>::iterator it = auxStores.begin(); it != auxStores.end(); it++)
    {
        Store& store = *it;
        storePointers.push_back(&store); 
    }

    // TODO:  Sort the vector of pointers using the STL sort algorithm
    //        with the comp parameter as the ordering relationship.
    sort(storePointers.begin(), storePointers.end(), comp);
    // TODO:  Using the now-sorted vector of pointers, replace each Store
    //        in stores with the Stores from auxStores in the correct order.
    for (int i = 0; i < stores.size(); i++)
    {
        stores[i] = *(storePointers[i]);
    }

    // auxStores will be destroyed upon return from the function
}