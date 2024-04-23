#include <iostream>
#include <vector>
#include <thread>
#include <cmath>

using namespace std;

double Function(double x) {
    return 1.0 / log(x);
}

double CalculateIntegral(double start, double end, double step) {
    double sum = 0.0;
    for (double x = start; x < end; x += step) {
        sum += Function(x) * step;
    }
    return sum;
}

void CalculateIntegralInThread(double start, double end, double step, double* result) {
    *result = CalculateIntegral(start, end, step);
}

int main() {
    double start = 10.0;
    double end = 20.0;
    double step = 0.0000001;

    int numThreads = thread::hardware_concurrency();
    vector<thread> threads;
    vector<double> results(numThreads);

    double totalResult = 0.0;

    for (int i = 0; i < numThreads; ++i) {
        double threadStart = start + i * ((end - start) / numThreads);
        double threadEnd = start + (i + 1) * ((end - start) / numThreads);

        threads.emplace_back(CalculateIntegralInThread, threadStart, threadEnd, step, &results[i]);
    }

    for (auto& t : threads) {
        t.join();
    }

    for (const auto& result : results) {
        totalResult += result;
    }

    cout << "Integral result: " << totalResult << endl;

    return 0;
}
