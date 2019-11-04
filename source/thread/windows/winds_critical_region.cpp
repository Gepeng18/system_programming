#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
#include<windows.h>

#define __WINDOWSJQ_

class Comm{
public:

    Comm(){
        #ifdef __WINDOWSJQ_
            InitializeCriticalSection(&winsSec);
        #endif
    }

    void msgGenerator(){
        for (size_t i = 0; i < 100; i++){
            #ifdef __WINDOWSJQ_
                EnterCriticalSection(&winsSec);
                msg.push_back(i);
                LeaveCriticalSection(&winsSec);
            #else
                mtx.lock();
                msg.push_back(i);
                mtx.unlock();
                std::cout<<"generator : "<<i<<std::endl;
            #endif
        }
    }

    void msgReceive(){
        for (size_t i = 0; i < 100; i++){

              #ifdef __WINDOWSJQ_
                EnterCriticalSection(&winsSec);
                if(msg.empty()) std::cout<<"empty.\n";
                else{
                    int content = msg.front();
                    msg.pop_front();
                    std::cout<<"--receive--: "<<content<<std::endl;
                }
                LeaveCriticalSection(&winsSec);
            #else
                mtx.lock();
                if(msg.empty()) std::cout<<"empty.\n";
                else{
                    int content = msg.front();
                    msg.pop_front();
                    std::cout<<"receive1--: "<<content<<std::endl;
                }
                mtx.unlock();
            #endif
        }
    }   
 
private:
    std::list<int> msg;
    std::mutex mtx; 
    #ifdef __WINDOWSJQ_
            CRITICAL_SECTION winsSec;  //定义了就必须初始化
    #endif
};

int main(int argc, char const *argv[]){
    Comm com;

    std::thread sumbit(&Comm::msgGenerator, &com);
    std::thread receive(&Comm::msgReceive, &com);

    sumbit.join();
    receive.join();

    
    std::cout<<"Main thread.";
}

