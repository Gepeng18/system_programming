#include<iostream>
#include<thread>
#include<vector>
#include<list>
#include<mutex>

class Comm{
public:
    void msgGenerator(){
        for (size_t i = 0; i < 100; i++){
            //需要保护的数据进行加锁，这里就是容器msg,
            //在对msg进行写操作时候，不允许读操作进行
            // mtx.lock();
            // msg.push_back(i);
            // mtx.unlock();

            // 加锁和解锁方式2
            std::lock_guard<std::mutex> lock_grd(mtx);//在这个作用域里lock,unlock
            msg.push_back(i);
            std::cout<<"generator : "<<i<<std::endl;
        }
    }

    void msgRecieve1(){
        for (size_t i = 0; i < 100; i++){
            //下面的if-else里面，一个分支执行了，另一个分钟就不会执行
            // 如果把unlock放在分支里面，每个分支都需要加
            mtx.lock();
            if(msg.empty()) std::cout<<"empty.\n";
            else{
                int content = msg.front();
                msg.pop_front();
                std::cout<<"receive1--: "<<content<<std::endl;
            }
            mtx.unlock();
        }
    }   
    
    void msgRecieve2(){
        for (size_t i = 0; i < 100; i++){
            mtx.lock();
            if(msg.empty()) std::cout<<"empty.\n";
            else{
                int content = msg.front();
                msg.pop_front();
                std::cout<<"receive2**: "<<content<<std::endl;
            }
            mtx.unlock();
        }
    }

private:
    std::list<int> msg;
    std::mutex mtx; //创建一个互斥量，不同线程访问同一个数据，必须使用同一个互斥量进行加锁和解锁
};

int main(int argc, char const *argv[]){
    Comm com;

    std::thread sumbit(&Comm::msgGenerator, &com);
    std::thread receive2(&Comm::msgRecieve2, &com);
    // std::thread receive1(&Comm::msgRecieve1, &com);

    sumbit.join();
    // receive1.join();
    receive2.join();

    
    std::cout<<"Main thread.";
}

