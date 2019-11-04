#include<iostream>
#include<thread>
#include<future>


int myThread(){
    std::cout<<"\nsubThread id: "<<std::this_thread::get_id()<<"...subThread start.\n";

    std::chrono::milliseconds time(5000);
    std::this_thread::sleep_for(time);

    std::cout<<"\nsubThread id: "<<std::this_thread::get_id()<<"...subThread end.\n";
    return 5;
}

int main(int argc, char const *argv[])
{
    std::cout<<"main Thread id: "<<std::this_thread::get_id()<<"...run...\n";

    std::future<int> retVal = std::async(myThread);//线程开始执行，虽然线程函数会延迟5s,但是不会卡在这儿
    for (size_t i = 0; i < 1000; i++) std::cout<<"test_1..."<<i<<std::endl;
    std::cout<<"\nsubThread return value: "<<retVal.get()<<std::endl;  //如果线程函数没有执行结束，而是会卡在这里，因为这里需要这个线程函数的返回结果

    for (size_t i = 0; i < 1000; i++) std::cout<<"test_2..."<<i<<std::endl;

    // std::thread t1(myThread);

    // for (size_t i = 0; i < 10; i++)  std::cout<<"test..."<<i<<std::endl;
    // t1.join();

    std::cout<<"main Thread.\n";
    return 0;
}
