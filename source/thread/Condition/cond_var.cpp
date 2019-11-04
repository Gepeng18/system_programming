#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>
#include<condition_variable>

class Comm{
public:
    void msgGenerator(){
        for (size_t i = 0; i < 100; i++){

            std::unique_lock<std::mutex> uniLock(mtx);
            msg.push_back(i);
            std::cout<<"generator : "<<i<<std::endl;

            condVar.notify_one();   //谁wait唤醒谁
            
        }
    }

    void msgReceive(){
        for (size_t i = 0; i < 100; i++){

            std::unique_lock<std::mutex> uniLock(mtx);
            condVar.wait(uniLock, [this]{
                    if(!msg.empty()) return true;
                    else return false;
            });

            //wait返回后，此时对于互斥量依然lock
            int content = msg.front();
            msg.pop_front();
            std::cout<<"receive element: "<<content<<'\n';
            //  uniLock.unlock();   //unique_lock的灵活性质，可以随时unlock
        }
    }   

private:
    std::list<int> msg;
    std::mutex mtx; 
    std::condition_variable condVar;
};

int main(int argc, char const *argv[]){
    Comm com;

    std::thread sumbit(&Comm::msgGenerator, &com);
    std::thread receive(&Comm::msgReceive, &com);

    sumbit.join();
    receive.join();

    std::cout<<"Main thread.";
}