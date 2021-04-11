#include <iostream>
#include <string>
#include <atomic>
#include <condition_variable>
#include <queue>

#include <thread>
#include <chrono>
#include <mutex>
#include <list>
#include <limits>


std::queue<char> q;
std::mutex m;
 
void producer() {
   while(true) {
      char a = std::cin.get();
      std::lock_guard<std::mutex> lock(m);
      q.push(a);
   }
}
 
 
void concumer() {
   while(true) {
      std::lock_guard<std::mutex> lock(m);
      while ( !q.empty()) {
         char a = q.front();
         q.pop();
         std::cout << a << "\n";
      }
   }
}


