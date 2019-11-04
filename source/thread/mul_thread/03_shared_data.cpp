#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>

class Comm{
public:
    void msgGenerator(){
        for (size_t i = 0; i < 100; i++){
            msg.push_back(i);
            std::cout<<"generator : "<<i<<std::endl;
        }
    }

    void msgRecieve1(){
        for (size_t i = 0; i < 100; i++){
            if(msg.empty()) std::cout<<"empty.\n";
            else{
                int content = msg.front();
                msg.pop_front();
                std::cout<<"receive1--: "<<content<<std::endl;
            }
        }
    }
    void msgRecieve2(){
    for (size_t i = 0; i < 100; i++){
        if(msg.empty()) std::cout<<"empty.\n";
        else{
            int content = msg.front();
            msg.pop_front();
            std::cout<<"receive2**: "<<content<<std::endl;
        }
     }
    }

private:
    std::list<int> msg;
    std::mutex m_mutex; //创建一个互斥量
};

int main(int argc, char const *argv[]){
    Comm com;
    
    std::thread receive1(&Comm::msgRecieve1, &com);
    std::thread receive2(&Comm::msgRecieve1, &com);
    std::thread sumbit(&Comm::msgGenerator, &com);

    sumbit.join();
    receive1.join();
    receive2.join();


    std::cout<<"Main thread.";
}

