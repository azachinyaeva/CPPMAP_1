#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>
#include <execution>
#include <random>


void fill_vec(std::vector<int>& vec) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 9);
    std::generate(std::execution::par, vec.begin(), vec.end(), [&]() {
        return dis(gen);
        }
    );

}

void sum_vec(std::vector<int>& vec1, std::vector<int>& vec2, int size, int threads) {
    std::vector<int> res (size);
    auto sum( [&] () {
        for (int i = 0; i < size; ++i) 
        {
            res[i] = vec1[i] + vec2[i];
        }
        });

    std::vector<std::thread> th;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < threads; ++i) 
    {
        th.push_back(std::thread(sum));
    }
    for (auto& t : th) 
    {
        t.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    std::cout << time.count() << "s" "\t";

}


int main()
{
    setlocale(LC_ALL, "Russian");
    int min_thread = 1;
    int max_thread = 16;
    int min_num = 1000;
    int max_num = 1000000;
    std::vector<int> vec1 (max_num);
    std::vector<int> vec2 (max_num);
    fill_vec(vec1);
    fill_vec(vec2);
    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << '\n' << '\n';
    std::cout << "\t\t" << "1000\t\t" << "10000\t\t" << "100000\t\t" << "1000000\t\t" << '\n';
    for (int t = min_thread; t <= max_thread; t *= 2) {

        std::cout << '\n' << t << " потоков:\t";
        for (int n = min_num; n <= max_num; n *= 10)
        {
            sum_vec(vec1, vec2, n, t);
        }

    }
}

