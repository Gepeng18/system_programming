#include<iostream>
#include<thread>
#include<future>


int myThread(int val){

    std::cout<<"enter sub-thread|val: "<<val<<std::endl;
    std::chrono::milliseconds time(1000);
    std::this_thread::sleep_for(time);

    std::cout<<"sub|id: "<<std::this_thread::get_id()<<" |执行结束."<<"\n";
    return 5;
}


int main(int argc, char const *argv[])
{
    std::packaged_task<int(int)> pkg(myThread);
    std::thread trd(std::ref(pkg), 10);
    trd.join();

    std::future<int> ret_1 = pkg.get_future();
    
    // std::shared_future<int> ret(pkg.get_future());
    std::shared_future<int> ret = pkg.get_future();
    std::shared_future<int> ret(std::move(ret_1));


     std::cout<<ret.get()<<std::endl;
     std::cout<<ret.get()<<std::endl;



    std::cout<<"Main thread.\n";
}
