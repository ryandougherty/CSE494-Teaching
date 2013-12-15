//
//  main.cpp
//  ThreadTest
//
//  Created by redoughe on 12/12/13.
//  Copyright (c) 2013 redoughe. All rights reserved.
//

#include <cmath>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

void evaluate_sqrt(int start, int end) {
	for (int i = start; i < end; ++i) {
		double a1 = i;
		a1 = sqrt(a1);
	}
}

int main(int argc, const char * argv[])
{
	typedef std::chrono::high_resolution_clock hrs;
	
	int n = 1e9;
	
	int numThreads = std::thread::hardware_concurrency();
	std::cout << "Running on " << numThreads << " threads\n";
	
	auto start = hrs::now();
	std::thread oneThread(evaluate_sqrt, 0, n);
	oneThread.join();
	auto end = std::chrono::duration_cast<std::chrono::milliseconds>(hrs::now() - start);
	std::cout << end.count() << "ms\n";
	
	start = hrs::now();
	std::vector<std::thread> threads;
	int a = 0;
	int toAdd = n / numThreads;
	for (int i = 0; i<numThreads; ++i) {
		threads.push_back(std::thread(evaluate_sqrt, a, a+toAdd));
		a+=toAdd;
	}
	for (auto& c : threads) {
		c.join();
	}
	end = std::chrono::duration_cast<std::chrono::milliseconds>(hrs::now() - start);
	std::cout << end.count() << "ms\n";
}

