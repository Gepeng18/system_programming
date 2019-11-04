#include <iostream>
#include <thread>
#include <mutex>

class Comm
{

private:
    Comm() {}

    class AuxCls{
    public:
        ~AuxCls(){
            if (Comm::m_instance){
                delete Comm::m_instance;
                Comm::m_instance = nullptr;
            }
        }
    };

    static void createInstance(){ m_instance = new Comm();}

public:
    static Comm* getInstance(){

        std::call_once(oneFlag, createInstance);
        return m_instance;
    }

private:
    static Comm *m_instance;
    static std::once_flag oneFlag;
};

//静态成员默认初始化
Comm *Comm::m_instance = nullptr;
std::once_flag Comm::oneFlag;


void create(){ Comm::getInstance(); }

int main(int argc, char const *argv[])
{
    Comm *ptr_1 = Comm::getInstance();
    std::thread t1(create);
    std::thread t2(create);

    t1.join();
    t2.join();
    std::cout << "main thread.\n";
}