#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;
using namespace chrono;

double sequentialAccess(size_t size) {
    vector<int> data(size, 1);
    volatile long long sum = 0;

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < size; ++i)
        sum += data[i];

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double stridedAccess(size_t size, size_t stride) {
    vector<int> data(size, 1);
    volatile long long sum = 0;

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < size; i += stride)
        sum += data[i];

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

double randomAccess(size_t size) {
    vector<int> data(size, 1);
    vector<size_t> indexes(size);

    iota(indexes.begin(), indexes.end(), 0);

    mt19937 generator(42);
    shuffle(indexes.begin(), indexes.end(), generator);

    volatile long long sum = 0;

    auto start = high_resolution_clock::now();

    for (size_t i : indexes)
        sum += data[i];

    auto end = high_resolution_clock::now();

    return duration<double, milli>(end - start).count();
}

void runTest(size_t size) {
    double memoryMB =
        (size * sizeof(int)) / (1024.0 * 1024.0);

    cout << "\n====================================\n";
    cout << "Memory Size: " << fixed << setprecision(2)
         << memoryMB << " MB\n";
    cout << "====================================\n";

    double sequential = sequentialAccess(size);
    double strided = stridedAccess(size, 16);
    double random = randomAccess(size);

    cout << "Sequential Access : " << sequential << " ms\n";
    cout << "Strided Access    : " << strided << " ms\n";
    cout << "Random Access     : " << random << " ms\n";

    ofstream file("results/results.csv", ios::app);

    file << memoryMB << ","
         << sequential << ","
         << strided << ","
         << random << "\n";

    file.close();
}

void showSystemInfo() {
    cout << "\n===== CPU INFORMATION =====\n";

    ifstream cpuinfo("/proc/cpuinfo");

    string line;
    int count = 0;

    while (getline(cpuinfo, line) && count < 20) {
        if (line.find("model name") != string::npos ||
            line.find("cache size") != string::npos) {
            cout << line << "\n";
            count++;
        }
    }

    cpuinfo.close();
}

int main() {

    ofstream file("results/results.csv");

    file << "Memory_MB,Sequential_ms,Strided_ms,Random_ms\n";

    file.close();

    showSystemInfo();

    int choice;

    while (true) {

        cout << "\n========================================\n";
        cout << " CPU CACHE & MEMORY BEHAVIOR ANALYZER\n";
        cout << "========================================\n";
        cout << "1. Small Memory Test\n";
        cout << "2. Medium Memory Test\n";
        cout << "3. Large Memory Test\n";
        cout << "4. Run All Tests\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice == 1) {
            runTest(1024 * 1024);
        }
        else if (choice == 2) {
            runTest(16 * 1024 * 1024);
        }
        else if (choice == 3) {
            runTest(64 * 1024 * 1024);
        }
        else if (choice == 4) {
            runTest(1024 * 1024);
            runTest(16 * 1024 * 1024);
            runTest(64 * 1024 * 1024);
        }
        else if (choice == 5) {
            cout << "\nExiting analyzer...\n";
            break;
        }
        else {
            cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}


