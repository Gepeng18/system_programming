#include <iostream>
#include <thread>
#include <mutex>


class Comm
{

private:
    Comm() {}

    class AuxCls
    {
    public:
        ~AuxCls()
        {
            if (Comm::m_instance)
            {
                delete Comm::m_instance;
                Comm::m_instance = nullptr;
            }
        }
    };

public:
    static Comm *getInstance()
    {
        if (m_instance == nullptr)
        { //双重锁定。因为只是需要在第一次new的时候加锁，为了防止每次都要加锁，加上两个判断，即可。效率up up up
            std::unique_lock<std::mutex> uniLock(mtx);
            if (m_instance == nullptr)
            {
                std::cout<<"instance created only once.\n";
                static AuxCls auxCls; //为了辅 助m_instance析构而存在
                m_instance = new Comm();
            }
        }
        //只能创建一次对象，以后都是返回同一个对象
        return m_instance;
    }

    void func() { std::cout << "existence only for test.\n"; }

private:
    static Comm *m_instance;
    static std::mutex mtx;
};

void create(){
     Comm::getInstance(); 
}
//静态成员默认初始化
Comm *Comm::m_instance = nullptr;
std::mutex Comm::mtx;

int main(int argc, char const *argv[])
{

    // 在创建其他线程之前创建实例
    // 使得实例只读
    Comm *ptr_1 = Comm::getInstance();
    std::thread t1(create);
    std::thread t2(create);

    t1.join();
    t2.join();


    std::cout << "main thread.\n";
}
