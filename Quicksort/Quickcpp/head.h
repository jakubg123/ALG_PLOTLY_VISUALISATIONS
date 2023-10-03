#pragma once
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <stdexcept>
std::vector<double> foo();

template <class T>
int median_pivot(std::vector<T>&vec,const int left,const int right)
{
    int mid = (left + right) / 2;

    int arr[3] = {vec[left],vec[mid],vec[right]};
    std::sort(arr,arr + 3);

    int x = arr[1];

    for(int i = left;i < right;i++)
    {
        if(vec[i] == x)
        {
            std::swap(vec[right],vec[i]);
            break;
        }
    }

    int pivot = vec[right];
    int i = left - 1;

    for(int j = left;j < right;j++)
    {
        if(vec[j] <= pivot)
        {
            i+=1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[right]);

    return i + 1;

}
template <class T>
int median_five(std::vector<T>&vec,const int left,const int right)
{
    int mid = (left + right) / 2;
    int left_mid = (left + mid) / 2;
    int right_mid = (mid + right) / 2;
    int arr[5] = {vec[left],vec[left_mid],vec[mid],vec[right_mid],vec[right]};
    std::sort(arr,arr + 5);

    int x = arr[2];

    for(int i = left;i < right;i++)
    {
        if(vec[i] == x)
        {
            std::swap(vec[right],vec[i]);
            break;
        }
    }

    int pivot = vec[right];
    int i = left - 1;

    for(int j = left;j < right;j++)
    {
        if(vec[j] <= pivot)
        {
            i+=1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[right]);

    return i + 1;

}

template<class T>
int median_seven(std::vector<T>&vec,const int left,const int right)
{
    int mid = (left + right) / 2;
    int left_mid = (left + mid) / 2;
    int left_left_mid = (left + left_mid) / 2;
    int right_mid = (mid + right) / 2;
    int right_right_mid = (right_mid + right) / 2;
    int arr[7] = {vec[left],vec[left_left_mid],vec[left_mid],vec[mid],vec[right_mid],vec[right_right_mid],vec[right]};
    std::sort(arr,arr + 7);

    int x = arr[3];

    for(int i = left;i < right;i++)
    {
        if(vec[i] == x)
        {
            std::swap(vec[right],vec[i]);
            break;
        }
    }

    int pivot = vec[right];
    int i = left - 1;

    for(int j = left;j < right;j++)
    {
        if(vec[j] <= pivot)
        {
            i+=1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[right]);

    return i + 1;

}

template <class T>
int random_pivot(std::vector<T>&vec,const int left,const int right)
{
    int random = rand() % (right-left+1) + left;
    //std::cout << "RANDOM -->" << random<< '\n';
    std::swap(vec[random],vec[right]);
    
    int pivot = vec[right];
    int i = left - 1;

    for(int j = left;j < right;j++)
    {
        if(vec[j] <= pivot)
        {
            i+=1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[right]);

    return i + 1;
}
 
template <class T>
int partition(std::vector<T> &vec,const int left,const int right)
{
    int pivot = vec[right];
    int i = left - 1;

    for(int j = left;j < right;j++)
    {
        if(vec[j] <= pivot)
        {
            i+=1;
            std::swap(vec[i],vec[j]);
        }
    }
    std::swap(vec[i+1],vec[right]);

    return i + 1;
}
 
template <class T>
void quick_sort_choice(std::vector<T> & vec, const int left, const int right,int choice)
{
    T pos;
    if(left < right)
    {

        switch(choice)
        {
            case 1:
                pos = partition(vec,left, right);
                break;
            case 2:
                pos = random_pivot(vec,left,right);
                break;
            case 3:
                pos = median_pivot(vec,left,right);
                break;
            case 4:
                pos = median_five(vec,left,right);
                break;
            case 5:
                pos = median_seven(vec,left,right);
                break;

            default:
                throw std::invalid_argument("Sprobuj z innym numerem - [1-5]");
                break;
        }

        quick_sort_choice(vec,left,pos-1,choice);
        quick_sort_choice(vec,pos+1,right,choice);

    }
}



