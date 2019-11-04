#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
#include<windows.h>

// #define __WINDOWSJQ_

class uniLockWins{
private:
    CRITICAL_SECTION *_critical_sec;
public:

    uniLockWins(CRITICAL_SECTION *sec){
        _critical_sec = sec;
        EnterCriticalSection(_critical_sec);
    }

    ~uniLockWins(){LeaveCriticalSection(_critical_sec);}
};


class Comm{
public:

    Comm(){
        #ifdef __WINDOWSJQ_
            InitializeCriticalSection(&winsSec);
        #endif
    }

    void msgGenerator(){
        for (size_t i = 0; i < 1000; i++){
            #ifdef __WINDOWSJQ_
                uniLockWins lock(&winsSec);
                msg.push_back(i);
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
                uniLockWins lock(&winsSec);
                if(msg.empty()) std::cout<<"empty.\n";
                else{
                    int content = msg.front();
                    msg.pop_front();
                    std::cout<<"--receive--: "<<content<<std::endl;
                }
            #else
                std::chrono::microseconds timeout(1000);
                if(timed_mtx.try_lock_for(timeout)){
                    int content = msg.front();
                    msg.pop_front();
                    std::cout<<"receive1--: "<<content<<std::endl;
                }
               else{
                    std::cout<<"Fail to lock().\n";
                    std::chrono::microseconds dura(1000);
                    std::this_thread::sleep_for(dura);
               }
         
            #endif
        }
    }   
 
private:
    std::list<int> msg;
    std::mutex mtx; 
    #ifdef __WINDOWSJQ_
            CRITICAL_SECTION winsSec;  //定义了就必须初始化
    #endif
    std::timed_mutex timed_mtx;
};

int main(int argc, char const *argv[]){
    Comm com;

    std::thread sumbit(&Comm::msgGenerator, &com);
    std::thread receive(&Comm::msgReceive, &com);

    sumbit.join();
    receive.join();

    
    std::cout<<"Main thread.";
}