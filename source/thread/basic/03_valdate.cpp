#include<iostream>
#include<thread>
#include<string>

class Val{
public:
    int _idx;
    Val(int idx):_idx(idx){
        std::cout<<"constructror"
                <<"|address: "<<this
                <<"|thread id: "<<std::this_thread::get_id()
                <<"\n";}
    Val(const Val& obj):_idx(obj._idx){
        std::cout<<"copy constructror"
        <<"|address: "<<this
        <<"|thread id: "<<std::this_thread::get_id()
        <<"\n";}
    ~Val(){
        std::cout<<"destroyed"
                <<"|address: "<<this
                <<"|thread id: "<<std::this_thread::get_id()
                <<"\n";}

};

//这里用不用引用都是三次
void print(const int idx, const Val v){
    // std::cout<<"the instance of class Val address: "<<&v<<"\n";
}

void print2(const Val& v){
    // std::cout<<"the instance of class Val address: "<<&v<<"\n";
}

int main(int argc, char const *argv[]){

    std::cout<<"Main thread"
            <<"|thread id: "<<std::this_thread::get_id()
            <<"\n";

    int var = 1;
    int val = 2;
    // std::thread thread(print, var, val);
    // std::thread thread(print, var, Val(val));  //在创建线程的同时，创建一个临时变量，就一定会在main结束之前，构造出来传递给子线程
    // detach 模式下：
    // 如果是简单的类型转换，直接用值传递
    // 如果是类，用显示变量转换，类似Val(val)，再转递给子线程，确保子线程安全。
    // 建议不适用detach()

    
     std::thread thread(print2, Val(val));
    // thread.detach();
    thread.join();

    std::cout<<"Main thread over";
    return 0;
}
