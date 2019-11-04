#include<iostream>
#include<thread>
#include<future>

void mythread(std::promise<int>& prom, int val){
    val++;

    //假设这个线程花了2s, 得到了运算结果
    prom.set_value(val);
    return;
}
void myTrd(std::future<int>& future){
    int ret = future.get();
    std::cout<<"myTrd get: "<<ret<<std::endl;
    return;
}
int main(int argc, char const *argv[]){
    
    std::promise<int> prom; //int 为保存的数据类型
    std::thread trd(mythread, std::ref(prom), 10);
    trd.join();

    // 获取结果值
    std::future<int> future = prom.get_future();
    // std::cout<<"main get: "<<future.get()<<std::endl;

    std::thread trd2(myTrd, std::ref(future));
    trd2.join();
    std::cout<<"main thread.\n";

    return 0;
}
