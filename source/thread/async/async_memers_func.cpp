#include<iostream>
#include<thread>
#include<future>


class Async{

public:
    int myThread(int val){

        std::cout<<"enter sub-thread|val: "<<val<<std::endl;
        std::chrono::milliseconds time(1000);
        std::this_thread::sleep_for(time);

        std::cout<<"subThread id: "<<std::this_thread::get_id()<<" |end."<<"\n";
        return 5;
    }


};

int main(int argc, char const *argv[])
{
    std::cout<<"matnThread id: "<<std::this_thread::get_id()<<"\n";
    Async ayc;
    int val = 12;
    std::future<int> retVal = std::async(std::launch::deferred,&Async::myThread, &ayc, val);

    std::cout<<"return value: "<<retVal.get()<<std::endl;
    std::cout<<"main Thread.\n";
    return 0;
}
