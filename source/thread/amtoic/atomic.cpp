#include<iostream>
#include<thread>
#include<mutex>
#include<atomic>

// std::mutex mtx;
// int commVar = 0;
std::atomic<int> commVar{10};

void Write(){
    for (size_t i = 0; i < 1000000; i++) {
        commVar++;
    }
    return;
}

int main(int argc, char const *argv[]){

    std::thread t1(Write);
    std::thread t2(Write);

    t1.join();
    t2.join();

    std::cout<<commVar<<std::endl;
    std::cout<<"main thread.\n";
}

