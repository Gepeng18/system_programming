
#include<iostream>
#include<thread>
#include<string>

void print(int n){
    std::cout<<"var address in sub: "<<&n
            <<"|var value in sub: "<<n
            <<std::endl;
}

 


int main(int argc, char const *argv[]){
    //1 
    int n = 10;

    std::thread t(print, n);
    std::cout<<"var address in main: "<<&n
            <<"|var value in main: "<<n
            <<std::endl;




    t.join();
    std::cout<<"\nMain thread."<<std::endl;
}
