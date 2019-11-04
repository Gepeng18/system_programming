#include <thread>
#include <iostream>

void foo() {
    std::cout << "subthread" << std::endl;
}

class Cls{\
private:
    int& _var;
public:
    Cls(int& var):_var(var){ }
    Cls(const Cls& obj):_var(obj._var){
        std::cout<<" copy constructor is runing.\n";
    }
    ~Cls(){
        std::cout<<"Cls destory function is running.\n";
    }

    void operator()(){
        std::cout<<"operator foo is runing.\n";

        std::cout<<"var0 value: "<<_var<<std::endl;
        std::cout<<"var1 value: "<<_var+1<<std::endl;
        std::cout<<"var2 value: "<<_var+2<<std::endl;
        std::cout<<"var3 value: "<<_var+3<<std::endl;

        std::cout<<"operator foo is exited.\n";
    }
};


int main(int argc, char const *argv[])
{
    // std::thread thread(foo);    // 启动线程foo,并且已经开始执行
    // thread.join();              // 让主线程等待子线程执行完成,相当于阻塞,join执行完毕,主线程再继续执行
    
   /*
     int var = 6;
    Cls obj(var);
    std::thread st(obj);
    st.join();
    // st.detach();
    */

/*3
 */
    auto lad = []{
        std::cout<<"lambda expression is running.\n";
        std::cout<<"lambda expression is exited.\n";
    };
  
    std::thread thread(lad);
    thread.join();
    std::cout<<"I am main thread.\n";
    return 0;
}

