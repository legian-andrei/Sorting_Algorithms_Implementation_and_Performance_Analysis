#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <chrono>
#include <cmath>
#include <algorithm>

using namespace std;

const int max_count = 1e7;
#define LL long long


long long get_max(vector <LL>& v) {
    LL maxv = -9e5;
    for (auto x : v) {
        if (x > maxv) {
            maxv = x;
        }
    }
    return maxv;
}

// radix 
void radix_sort(vector <LL>& v, int baza) {
    LL max = get_max(v);
    int cifre_max = 0;
    while (max) {
        cifre_max++;
        max /= 10;
    }
    int exp = 1;
    for (int rep = 0; rep <= cifre_max; rep++) {
        vector <vector <LL>> buckets(baza);
        for (auto x : v) {
            buckets[x / exp % baza].push_back(x);
        }
        LL poz = 0;
        for (LL i = 0; i < baza; i++) {
            for(auto x: buckets[i]) {
                v[poz] = x;
                poz++;
            }
        }
        exp *= baza;
        buckets.erase(buckets.begin());
    }
    
}

// merge 
void merge_sort(vector <LL>& v, LL lo, LL hi) {
    if (lo < hi) {
        vector <LL> temp(v.size());
        LL mid = lo + (hi - lo) / 2;
        merge_sort(v, lo, mid);
        merge_sort(v, mid + 1, hi);
        LL index_arr1 = lo, index_arr2 = mid + 1, index_merged = lo;
        while (index_arr1 <= mid && index_arr2 <= hi) {
            if (v[index_arr1] < v[index_arr2]) {
                temp[index_merged] = v[index_arr1];
                index_arr1++;
            }
            else {
                temp[index_merged] = v[index_arr2];
                index_arr2++;
            }
            index_merged++;
        }
        while (index_arr1 <= mid) {
            temp[index_merged] = v[index_arr1];
            index_arr1++;
            index_merged++;
        }
        while (index_arr2 <= hi) {
            temp[index_merged] = v[index_arr2];
            index_arr2++;
            index_merged++;
        }
        for (int i = lo; i <= hi; i++) {
            v[i] = temp[i];
        }
        temp.erase(temp.begin());
    }
}

// shell
void shell_sort(vector <LL>& v) {
    for (LL gap = v.size() / 2; gap > 0; gap /= 2) {
        for (LL i = gap; i < v.size(); i++) {
            LL temp = v[i];
            LL j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = temp;
        }
    }
}

// count sort
bool count_sort(vector<LL>& v) {
    LL maxv = get_max(v);
    if (maxv > max_count) {
        return false;
    }

    vector <LL> count;
    vector <LL> output;
    count.resize(++maxv);
    output.resize(v.size());
    for (auto x : v) {
        count[x]++;
    }

    for (int i = 1; i < maxv; i++) {
      count[i] += count[i - 1];
    }

    for (int i = 0; i < v.size(); i++) {
        output[--count[v[i]]] = v[i];
    }

    for (int i = 0; i < v.size(); i++) {
        v[i] = output[i];
    }
    count.erase(count.begin());
    output.erase(output.begin());
    return true;
}

// quick
void quick_sort(vector <LL>& v, int lo, int hi) {
    if (lo < hi){
        LL j = lo, i = lo - 1, pivot = v[hi];
        while (j < hi) {
            if (v[j] < pivot) {
                i++;
                swap(v[i], v[j]);
            }
            j++;
        }
        swap(v[i + 1], v[hi]);
        quick_sort(v, lo, i - 1);
        quick_sort(v, i + 1, hi);
    }
}


int main()
{
    ifstream in("teste.in");
    int nr_teste, sortare;
    in >> nr_teste; 
    cout << "1. Radix Sort" << endl << "2. Merge Sort" << endl << "3. Shell Sort" << endl << "4. Count Sort" << endl << "5. Quick Sort" << endl << "6. Algoritmul nativ C++ " << endl;
    cout << "Introduceti numarul aferent sortarii pe care vreti sa o testati: "; cin >> sortare;
    switch (sortare) {
    case 1: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            radix_sort(nr, 10);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    case 2: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            merge_sort(nr, 0, nr.size() - 1);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    case 3: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            shell_sort(nr);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    case 4: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            if(!count_sort(nr))
                cout << "Error: lista sau numere prea mari, nu s-au putut sorta folosind count sort." << endl;
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    case 5: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            quick_sort(nr, 0, nr.size() - 1);
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    case 6: {
        for (int index_test = 0; index_test < nr_teste; index_test++) {
            LL nr_numere, max_numere;
            in >> nr_numere >> max_numere;

            vector <LL> nr;
            srand(time(0));
            for (int i = 0; i < nr_numere; i++) {
                nr.push_back(rand() % max_numere);
            }
            chrono::time_point<std::chrono::system_clock> start, end;
            start = chrono::system_clock::now();
            sort(nr.begin(), nr.end());
            end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end - start;
            cout << nr_numere << " - " << max_numere << " - " << elapsed_seconds.count() << "s" << endl;

            nr.erase(nr.begin());
        }
        break;
    }
    default: {
        cout << "Ati introdus un numar invalid." << endl;
        break;
    }
    }

    return 0;
}

