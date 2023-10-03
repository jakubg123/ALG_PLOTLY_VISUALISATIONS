#include "head.h"
#include <sys/resource.h>
#include <algorithm>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "experimental/random"
#include <ctime>
#include <chrono>
#include <time.h>
#include <fstream>
namespace ranges
{
    template <typename Range, typename Generator>
    void generate(Range &range, Generator generator)
    {
        return std::generate(begin(range), end(range), generator);
    }
}

class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high)
        : random_engine_{std::random_device{}()}, distribution_{low, high}
    {
    }
    int operator()()
    {
        return distribution_(random_engine_);
    }
    int operator+(int a)
    {
        int random_number = (*this)();
        int result = random_number + a;

        return result;
    }

private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

std::vector<double> foo(int x);
std::vector<double> foo_limited(int x);
std::vector<double> foo_nondesc(int x);
void output_file_nondesc(std::ofstream&file_out);
void output_file_right_cs(std::ofstream &file_out);
void output_file_random_cs(std::ofstream &file_out);
void output_file_nondesc_cs(std::ofstream &file_out);

int main()
{

    // remove("PYTHON_READ_X");
    // std::ofstream csv_stream;
    // csv_stream.open("PYTHON_READ_X");
    // output_file_right_cs(csv_stream);
    // csv_stream.close();

    remove("PYTHON_RANDOM_X");
    std::ofstream second_csv_stream;
    second_csv_stream.open("PYTHON_RANDOM_X");
    output_file_random_cs(second_csv_stream);
    second_csv_stream.close();
    

    // remove("PYTHON_NON_OSTATNI");
    // std::ofstream third_stream;
    // third_stream.open("PYTHON_NON_OSTATNI");
    // output_file_nondesc_cs(third_stream);
    // third_stream.close();


    return 0;
}

std::vector<double> foo(int x)
{
    std::vector<int> numbers;
    std::vector<double> results;

    double arithm;

    for (int i = 1; i < 101; i++)
    {
        arithm = 0;
        std::cout << "\nsortowanie " << i << "\n"
                  << std::endl;
        for (int l = 0; l < 3; l++)
        {
            std::generate_n(std::back_inserter(numbers), i * 10000, RandomNumberBetween(0, 5 * i * 10000));

            // for (int number : numbers)
            // {
            //     std::cout << number << ' ';
            // }

            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            quick_sort_choice(numbers, 0, numbers.size()-1, x);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

            double execution_time = std::chrono::duration<double>(end - begin).count();
            // std::cout << "\nTU JEST POSORTOWANE -->>\n";
            //  for(int number:numbers)
            //  {
            //      std :: cout << number << ' ';
            //  }
            // std::cout << execution_time << " Execution time\n";

            arithm += execution_time;

            numbers.clear();
        }
        arithm /= 3;
        std::cout << arithm << std::endl;
        results.push_back(arithm);
    }

    return results;
}

std::vector<double> foo_limited(int x)
{
    std::vector<int> numbers;
    std::vector<double> results;

    double arithm;

    for (int i = 1; i < 101; i++)
    {
        arithm = 0;
        std::cout << "\nsortowanie " << i << "\n";
        
        std::generate_n(std::back_inserter(numbers), i * 10000, RandomNumberBetween(0, 100));

        // for (int number : numbers)
        // {
        //     std::cout << number << ' ';
        // }

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        quick_sort_choice(numbers, 0, numbers.size()-1, x);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        double execution_time = std::chrono::duration<double>(end - begin).count();
        // std::cout << "\nTU JEST POSORTOWANE -->>\n";
        // for(int number:numbers)
        // {
        //     std :: cout << number << ' ';
        // }
        // std::cout << execution_time << " Execution time\n";

        arithm += execution_time;

        numbers.clear();
        //}
        // arithm/=3;
        // std::cout << arithm << std::endl;
        results.push_back(arithm);
    }

    return results;
}



std::vector<double> foo_nondesc(int x)
{
    std::vector<double> results;
    for (int i = 1; i < 101; i++)
    {
        std::cout << "\nSortowanie " << i << '\n';
        double arithm = 0;
        int step = 10000 * i;
        std::vector<int> numbers(step);
        for (int k = 1; k < step; k++)
        {
            numbers[k] = RandomNumberBetween(0, 3) + numbers[k - 1];
        }

        // for (int l = 0; l < numbers.size(); l++)
        // {
        //     std::cout << numbers[l] << " ";
        // }
        //std::cout << "\n size of vector: " << numbers.size() << '\n';

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        quick_sort_choice(numbers, 0, numbers.size() - 1, x);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        double execution_time = std::chrono::duration<double>(end - begin).count();
        //std::cout << "\nTU JEST POSORTOWANE -->>\n";

        // for(int i = 0;i < numbers.size();i++)
        // {
        //     std ::cout << numbers[i] << ' ';
        // }
        std::cout << " -------- " << execution_time << " ------ Execution time\n";

        arithm += execution_time;
        results.push_back(arithm);

        numbers.clear();
        //std::cout << "\n";
    }

    // for (int i = 0; i < results.size(); i++)
    // {
    //     std::cout << results[i] << "\n";
    // }



    return results;

}

std::vector<double> foo_nondesc_var(int x)
{
    std::vector<double> results;
    for (int i = 1; i < 11; i++)
    {
        std::cout << "\nSortowanie " << i << '\n';
        double arithm = 0;
        int step = 10000 * i;
        std::vector<int> numbers(step);
        for (int k = 1; k < step; k++)
        {
            numbers[k] = RandomNumberBetween(0, 3) + numbers[k - 1];
        }

        // for (int l = 0; l < numbers.size(); l++)
        // {
        //     std::cout << numbers[l] << " ";
        // }
        //std::cout << "\n size of vector: " << numbers.size() << '\n';

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        quick_sort_choice(numbers, 0, numbers.size() - 1, x);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        double execution_time = std::chrono::duration<double>(end - begin).count();
        //std::cout << "\nTU JEST POSORTOWANE -->>\n";

        // for(int i = 0;i < numbers.size();i++)
        // {
        //     std ::cout << numbers[i] << ' ';
        // }
        //std::cout << " -------- " << execution_time << " ------ Execution time\n";

        arithm += execution_time;
        results.push_back(arithm);

        numbers.clear();
        //std::cout << "\n";
    }

    // for (int i = 0; i < results.size(); i++)
    // {
    //     std::cout << results[i] << "\n";
    // }



    return results;

}

std::vector<double> foo_nondesc_var1(int x)
{
    std::vector<double> results;
    for (int i = 1; i < 101; i++)
    {
        std::cout << "\nSortowanie " << i << '\n';
        double arithm = 0;
        int step = 10000 * i;
        std::vector<int> numbers(step);
        for (int k = 1; k < step; k++)
        {
            numbers[k] = RandomNumberBetween(0, 3) + numbers[k - 1];
        }

        // for (int l = 0; l < numbers.size(); l++)
        // {
        //     std::cout << numbers[l] << " ";
        // }
        //std::cout << "\n size of vector: " << numbers.size() << '\n';

        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        quick_sort_choice(numbers, 0, numbers.size() - 1, x);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        double execution_time = std::chrono::duration<double>(end - begin).count();
        //std::cout << "\nTU JEST POSORTOWANE -->>\n";

        // for(int i = 0;i < numbers.size();i++)
        // {
        //     std ::cout << numbers[i] << ' ';
        // }
        //std::cout << " -------- " << execution_time << " ------ Execution time\n";

        arithm += execution_time;
        results.push_back(arithm);

        numbers.clear();
        //std::cout << "\n";
    }

    // for (int i = 0; i < results.size(); i++)
    // {
    //     std::cout << results[i] << "\n";
    // }



    return results;

}

void output_file_nondesc(std::ofstream &file_out)
{
    std::cout << "NIEMALEJACY STREAM";
    std::vector<double> part_vect = foo_nondesc(1);
    std::cout << "kolejny vector \n";

    std::vector<double> random_vect = foo_nondesc(2);
    std::cout << "kolejny vector \n";

    std::vector<double> median_vect = foo_nondesc(3);
    std::cout << "kolejny vector \n";

    std::vector<double> median_five_vect = foo_nondesc(4);
    std::cout << "kolejny vector \n";

    std::vector<double> median_seven_vect = foo_nondesc(5);

    file_out << "partition\n";
    for (const auto &e : part_vect)
        file_out << e << ", ";
    file_out << "\nrandom_partition\n";
    for (const auto &e : random_vect)
        file_out << e << ", ";
    file_out << "\nmedian_partition\n";
    for (const auto &e : median_vect)
        file_out << e << ", ";
    file_out << "\nmedian_five_sort\n";
    for (const auto &e : median_five_vect)
        file_out << e << ", ";
    file_out << "\nmedian_seven_sort\n";
    for (const auto &e : median_seven_vect)
        file_out << e << ", ";
}













void output_file_right_cs(std::ofstream &file_out)
{
    std::vector<double> part_vect = foo(1);
    std::cout << "kolejny vector \n";

    std::vector<double> random_vect = foo(2);
    std::cout << "kolejny vector \n";

    std::vector<double> median_vect = foo(3);
    std::cout << "kolejny vector \n";

    std::vector<double> median_five_vect = foo(4);
    std::cout << "kolejny vector \n";

    std::vector<double> median_seven_vect = foo(5);

    for (int i = 0; i < part_vect.size();i++)
    {
        if(i == part_vect.size() - 1)
            file_out << part_vect[i]; 
        else
            file_out << part_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < random_vect.size();i++)
    {
        if(i == random_vect.size() - 1)
            file_out << random_vect[i];  
        else
            file_out << random_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_vect.size();i++)
    {
        if(i == median_vect.size() - 1)
            file_out << median_vect[i]; 
        else
            file_out << median_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_five_vect.size();i++)
    {
        if(i == median_five_vect.size() - 1)
            file_out << median_five_vect[i];
        else
            file_out << median_five_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_seven_vect.size();i++)
    {
        if(i == median_seven_vect.size() - 1)
            file_out << median_seven_vect[i];
        else
            file_out << median_seven_vect[i] << ",";
    }
}



void output_file_random_cs(std::ofstream &file_out)
{
    std::vector<double> part_vect = foo_limited(1);
    std::cout << "kolejny vector \n";

    std::vector<double> random_vect = foo_limited(2);
    std::cout << "kolejny vector \n";

    std::vector<double> median_vect = foo_limited(3);
    std::cout << "kolejny vector \n";

    std::vector<double> median_five_vect = foo_limited(4);
    std::cout << "kolejny vector \n";

    std::vector<double> median_seven_vect = foo_limited(5);

    for (int i = 0; i < part_vect.size();i++)
    {
        if(i == part_vect.size() - 1)
            file_out << part_vect[i]; 
        else
            file_out << part_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < random_vect.size();i++)
    {
        if(i == random_vect.size() - 1)
            file_out << random_vect[i];  
        else
            file_out << random_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_vect.size();i++)
    {
        if(i == median_vect.size() - 1)
            file_out << median_vect[i]; 
        else
            file_out << median_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_five_vect.size();i++)
    {
        if(i == median_five_vect.size() - 1)
            file_out << median_five_vect[i];
        else
            file_out << median_five_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_seven_vect.size();i++)
    {
        if(i == median_seven_vect.size() - 1)
            file_out << median_seven_vect[i];
        else
            file_out << median_seven_vect[i] << ",";
    }
}



void output_file_nondesc_cs(std::ofstream &file_out)
{
    std::vector<double> part_vect = foo_nondesc_var(1);
    std::cout << "kolejny vector \n";

    std::vector<double> random_vect = foo_nondesc_var1(2);
    std::cout << "kolejny vector \n";

    std::vector<double> median_vect = foo_nondesc(3);
    std::cout << "kolejny vector \n";

    std::vector<double> median_five_vect = foo_nondesc(4);
    std::cout << "kolejny vector \n";

    std::vector<double> median_seven_vect = foo_nondesc(5);

    for (int i = 0; i < part_vect.size();i++)
    {
        if(i == part_vect.size() - 1)
            file_out << part_vect[i]; 
        else
            file_out << part_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < random_vect.size();i++)
    {
        if(i == random_vect.size() - 1)
            file_out << random_vect[i];  
        else
            file_out << random_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_vect.size();i++)
    {
        if(i == median_vect.size() - 1)
            file_out << median_vect[i]; 
        else
            file_out << median_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_five_vect.size();i++)
    {
        if(i == median_five_vect.size() - 1)
            file_out << median_five_vect[i];
        else
            file_out << median_five_vect[i] << ",";
    }
    file_out << '\n';
    for (int i = 0; i < median_seven_vect.size();i++)
    {
        if(i == median_seven_vect.size() - 1)
            file_out << median_seven_vect[i];
        else
            file_out << median_seven_vect[i] << ",";
    }
}
