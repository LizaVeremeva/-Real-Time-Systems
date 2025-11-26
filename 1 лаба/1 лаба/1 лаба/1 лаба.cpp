#include <iostream>
#include <string>

/*
    1.1
    int main() {
    std::string s = "01234";
    for (unsigned int i = s.size() - 1; i >= 0; i--) {
        std::cout << s[i] << std::endl;
    }
    return 0;
}
*/

#include <time.h>  

using namespace std;

// Функция вычисления факториала
long long factorial(int n) {
    long long result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    const int ITERATIONS = 10000000; // 10 миллионов раз
    const int FACTORIAL_NUM = 10;

    cout << "Task: Calculate " << FACTORIAL_NUM << "! = " << factorial(FACTORIAL_NUM)
        << " exactly " << ITERATIONS << " times" << endl;

    // Замер времени с помощью clock()
    clock_t start = clock();

    long long total = 0;
    for (int i = 0; i < ITERATIONS; i++) {
        total += factorial(FACTORIAL_NUM);
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "- Factorial of " << FACTORIAL_NUM << " is: " << factorial(FACTORIAL_NUM) << endl;
    cout << "- Total sum after " << ITERATIONS << " iterations: " << total << endl;
    cout << "- Execution time: " << seconds << " seconds" << endl;

    return 0;
}
