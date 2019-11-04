
#include<iostream>
#include<thread>
#include<string>

class Val{
public:
   mutable int _idx;
    Val(int idx):_idx(idx){
        std::cout<<"constructror"
                <<"|address: "<<this
                <<"|thread id: "<<std::this_thread::get_id()
                <<"\n";}
    Val(const Val& obj):_idx(obj._idx){
        std::cout<<"copy constructror"
        <<"|address: "<<this
        <<"|thread id: "<<std::this_thread::get_id()
        <<"\n";}
    ~Val(){
        std::cout<<"destroyed"
                <<"|address: "<<this
                <<"|thread id: "<<std::this_thread::get_id()
                <<"\n";}

public:
    void foo(int n){
        std::cout<<"foo function."
            <<"|address: "<<this
            <<"|thread id: "<<std::this_thread::get_id()
            <<"\n";
    }
};

void print2(const Val& v){
    v._idx = 100;
    std::cout<<"copy constructror"
    <<"|address: "<<&v
    <<"|thread id: "<<std::this_thread::get_id()
    <<"\n";
}
// 传入一个智能指针
void smartptr(std::unique_ptr<int> ptr){

}

int main(int argc, char const *argv[]){
    //1 
    // Val cls(10);
    // std::thread thread(print2, std::ref(cls));
    // std::thread thread_1(std::move(thread));
    // thread.detach();
    // thread.join();

    // std::cout<<"\nidx: "<<cls._idx
    //     <<"\nMain thread."<<std::endl;

    //2 传入一个智能指针
    // std::unique_ptr<int> smptr(new int(100)); //不能detach
    // std::thread threadPtr(smartptr, std::move(smptr));
    // threadPtr.join();

    // if (smptr == nullptr) std::cout<<"null\n";
    


    // 3 成员函数指针做线程函数
    
    Val cls(10);
    std::thread thread_3(&Val::foo, &cls, 10);
    thread_3.join();
    // thread_3.detach();

    std::cout<<"\nMain thread."<<std::endl;
}
