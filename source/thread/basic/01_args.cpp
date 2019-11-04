#include<iostream>
#include<thread>
#include<string>
// 虽然这里的idx是个应用，但是实际上还是pass-by-value
// ****绝对不可以用指针，因为传入指针和原来的实参变量指向的是同一块内存区域，在detach模型下很危险
// void foo(const int& idx, char* pbuf)
void foo(const int& idx, std::string& pbuf) //会隐式的将char* 转换为string
{
    // std::cout<<"value: "
    //         <<idx<<'|'
    //         <<pbuf<<'\n';
    std::cout<<"first args address in sbu: "<<&idx<<" | second args address in sub: "<<&pbuf<<'\n';
    return;
}

int main(int argc, char const *argv[]){ 

    int var = 10;
    int &refVar = var;
    char buf[] = "this is test string.";
    std::cout<<"first args address in main:"<<&var<< " | second args address in main: "<<&buf<<'\n';
    /*
        事实上存在可能性：
            在detach模型下，buf已经被系统回收了，才被作为参数传递给子线程，会产生和不可预料的后果。
     */
    // std::thread st(foo, var, buf);
    /**
     * 提前将buf包装为string类型，string(buf),安全有效
     */
    std::thread st(foo, var,std::string(buf));


    // st.join();
    st.detach();


    std::cout<<"Main thread over.\n";
    return 0;
}
