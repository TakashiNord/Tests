// Test_Task-Messages_queue-v.02.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#include <iostream>
#include <string>
#include <atomic>
#include <condition_variable>
#include <queue>
#include <list>
#include <thread>
#include <chrono>
#include <mutex>
#include <ctime>

using namespace std ;
 
class BookhouseEmpty
{
};

class Bookhouse
{
    enum { MAX = 30  };
	std::queue<string> m_message;
  public:
    void AcceptItem(string item)
    {
      if(m_message.size()== MAX) HandLastItem() ;
	  m_message.push(item);
    }
    string HandLastItem()
    {
        string item = get();
        if(!m_message.empty())
		   m_message.pop();
        return item;
    }
    string get()
    {
       string item = "";
	   item.clear();
	   if(!m_message.empty())
         string item = m_message.front();
       return item;
    }

};
 
Bookhouse g_Writer; 
std::timed_mutex gt_Mutex;
std::mutex g_Mutex;
bool stop = false ;

// Функция генерирования случайного целочисленного числа в указанных пределах.
// Диапазон чисел: [min, max]
int GetRandomNumber(int min, int max)
{
  // Установить генератор случайных чисел
  srand(time(NULL));

  // Получить случайное число - формула
  int num = min + rand() % (max - min + 1);

  return num;
}

int _tmain(int argc, _TCHAR* argv[])
{
 
	auto Producer = []()
    {
        time_t rawtime;
		int i = 0;

        while (!stop) //for (;;)
        {
           i++;

           time( &rawtime );  // получить текущую дату, выраженную в секундах

	       string st = asctime(localtime(&rawtime)) ;
           std::cout << i << " Write = " << st; // << std::endl;

           //gt_Mutex.try_lock();
           g_Writer.AcceptItem(st);
           //gt_Mutex.unlock();
	
           std::this_thread::sleep_for (std::chrono::seconds(1));

		   std::this_thread::yield();
        }		
		
    };
    auto Consumer = []()
    {
        while (!stop) //while(true)
        {
            gt_Mutex.lock();
            string item = "";
            try
            {
                item = g_Writer.HandLastItem();
            }
            catch(Bookhouse)
            {
                std::cout << "Bookhouse empty!\n"; 
            }
            gt_Mutex.unlock(); 

			std::cout << "\t\t Read = " << item; // << std::endl;
			
			int number;
            number = GetRandomNumber(1, 10); // Диапазон чисел: [1, 10]

            std::this_thread::sleep_for(std::chrono::seconds(number));
        }
    };

 
    std::thread producerThread(Producer);
    std::thread consumerThread(Consumer);
 
    producerThread.join();
    consumerThread.join();

    return 0;
}

