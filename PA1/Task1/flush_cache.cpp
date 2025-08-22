#include<stdio.h>

int main() {
    int size = 24 * 1024 * 1024; // size of L3 cache
    char* arr = new char[size]; 

    for (int i = 0; i < size; i++)
        arr[i]++;
}