
using namespace std ;

class Stack 
{
public :
	enum { MAX = 30  };
	string message[MAX];
	int top ;
	std::mutex m;
public :
   Stack () {
      top = 0;
   }
   void push (string var) {
	   if (top>=MAX) return ;
	   message[top++] = var ;
   }
   string pop ()  {
       if (top<0) return ("");
	   return (message[--top]);
   }

   void producer( Stack &q , std::string &a) {
     while(true) {
       std::lock_guard<std::mutex> lock(m);
       q.push(a);
     }
   }


} ;

// FIFO with circular buffer
#define fifo_size 4

class Fifo {
  uint8_t buff[fifo_size];
  int writePtr = 0;
  int readPtr = 0;
  
public:  
  void put(uint8_t val) {
    buff[writePtr%fifo_size] = val;
    writePtr++;
  }
  uint8_t get() {
    uint8_t val = NULL;
    if(readPtr < writePtr) {
      val = buff[readPtr%fifo_size];
      readPtr++;
      
      // reset pointers to avoid overflow
      if(readPtr > fifo_size) {
        writePtr = writePtr%fifo_size;
        readPtr = readPtr%fifo_size;
      }
    }
    return val;
  }
  int count() { return (writePtr - readPtr);}
};



