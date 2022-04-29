//
// Created by misha on 29.04.2022.
//

#include <iostream>
#include <future>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>

template<typename Iterator, typename lambda>
void Future_for_each_block(Iterator begin, Iterator end, const lambda& operation)
{
    std::for_each(begin, end, operation);
}


template<typename Iterator, typename lambda>
void Future_for_each(Iterator beg, Iterator end, const lambda& action, int num_threads)
{
    int len = end - beg;
    if(len < num_threads * 4){
        std::for_each(beg, end, action);
    }else{
        int len_per_thread = len / num_threads;
        std::vector<std::future<void>> working_threads;
        working_threads.reserve(num_threads - 1);
for(int i = 0; i < num_threads - 1; i++)
        {
            working_threads.push_back(std::async(std::launch::async, Future_for_each_block<Iterator,lambda>,
                                                 std::next(beg, i * len_per_thread),
                                                 std::next(beg, (i + 1) * len_per_thread), action));
        }
        working_threads.push_back(std::async(std::launch::async, Future_for_each_block<Iterator,lambda>,
                                             std::prev(end, len_per_thread+1),
                                             end, action));
        for(auto& thread : working_threads)
        {
            thread.get();
        }
    }
}

int main()
{
    auto seed = std::chrono::steady_clock::now().time_since_epoch().count();
    auto generator = std::mt19937(seed);
    auto distribution = std::uniform_int_distribution(1, 100);
    std::vector<int> test_sequence;
    std::generate_n(std::back_inserter(test_sequence), 39,
                    [&generator, &distribution]()
                    {
                        return distribution(generator);
                    });
    std::cout<<"Initial sequence: ";
    std::for_each(std::begin(test_sequence), std::end(test_sequence),
                  [](auto arg){std::cout << arg << " ";});
    std::cout<<"\n";

    std::cout<<"Sequence squared: ";

    auto lambda_0 = [](int &n){ n = int(pow(n,2)); };
    Future_for_each(std::begin(test_sequence), std::end(test_sequence), lambda_0, 8);
    std::for_each(std::begin(test_sequence), std::end(test_sequence),
                  [](auto arg){std::cout << arg << " ";});
    std::cout<<"\n";
}