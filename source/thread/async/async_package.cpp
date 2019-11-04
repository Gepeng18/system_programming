#include<iostream>
#include<thread>
#include<future>


int myThread(int val){

    std::cout<<"enter sub-thread|val: "<<val<<std::endl;
    std::chrono::milliseconds time(1000);
    std::this_thread::sleep_for(time);

    std::cout<<"subThread id: "<<std::this_thread::get_id()<<" |end."<<"\n";
    return 5;
}
int main(int argc, char const *argv[])
{
    std::cout<<"main id: "<<std::this_thread::get_id()<<std::endl;
    std::packaged_task<int(int)> pkg(myThread);
    std::thread trd(std::ref(pkg), 10);
    trd.join();

    std::future<int> ret = pkg.get_future();
    std::cout<<ret.get()<<std::endl;
    std::cout<<"Main thread.\n";
}
