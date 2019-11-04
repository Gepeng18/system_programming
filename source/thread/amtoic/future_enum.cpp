#include<iostream>
#include<thread>
#include<future>

int myThread(){

    std::chrono::milliseconds time(5000);  //等待时间为5s
    std::this_thread::sleep_for(time);

    std::cout<<"subThread id: "<<std::this_thread::get_id()<<" |end."<<"\n";
    std::cout<<"sub|子线程执行结束.\n";
    return 5;
}

int main(int argc, char const *argv[]){

    std::future<int> ret = std::async(myThread);
    std::future_status stus = ret.wait_for(std::chrono::seconds(6)); //等待子线程的时间
    
    if(stus == std::future_status::timeout){
        std::cout<<"timeout|子线程任务timeout.\n";
    }
    else if(stus == std::future_status::ready){
        std::cout<<"main|子线程成功返回|返回值: "<<ret.get()<<std::endl;
    }
    else if(stus == std::future_status::deferred){
         std::cout<<"main|子线程延迟执行|返回值: "<<ret.get()<<std::endl;
    }
    
    std::cout<<"Main thread|id: "<<std::this_thread::get_id()<<std::endl;
    return 0;
}
