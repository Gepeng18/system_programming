#include <iostream>
#include <utility>
#include <thread>
#include <chrono>

class baz
{
public:
    void operator()(int& n)
    {
        std::cout<<"func address in sub: "<<this<<"|var address in sub: "<<&n<<"|var value in sub: "<<n<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    int n = 0;
};


int main(int argc, char const *argv[])
{

    baz b;
    int n=10;
    std::thread t6(b,std::ref(n)); // t6 runs baz::operator() on object b 
    
    std::cout<<"class address in sub: "<<&b<<"|var address in main: "<<&n<<"|var value in main: "<<n<<std::endl;
    t6.join();
    return 0;
}
