#include<iostream>
#include<thread>
#include<vector>
using namespace std;

//只读数据是安全的、共享的
const vector<int> sharedArgs = {1,2,3};


void myPrint(int num){
    std::cout<<"my sub thread id: "<<this_thread::get_id();
    std::cout<<"|num is "<<sharedArgs[0]<<'|'<<sharedArgs[1]<<'|'<<sharedArgs[2]<<endl;
}

int main(int argc, char const *argv[]){

    vector<thread> threads;
    for (size_t i = 0; i < 3; i++) threads.push_back(std::thread(myPrint, i+1));   // 创建线程
    for(auto iter=threads.begin(); iter != threads.end(); iter++) iter->join();    //等待所有的线程完成

    std::cout<<"Main thread.\n";
}



