# lecture 7: 设计模式与并发  

## 单例与多线程保护机制  

下面是解决了多线程问题的单例模式模板

```c++
std::mutex my_mutex;

class Singleton
{
public:
    static Singleton* getInstance()
    {
        if (nullptr == m_instance) //双重检查 
        {
            std::unique_lock<std::mutex> uq(my_mutex);

            if (nullptr == m_instance)
            {
                m_instance = new Singleton();
                static Delete_ dl;
                // cout << "create\n"; //这行可以证明只执行了一次
            }
        }
        return m_instance;
    }

    class Delete_ //这个类用来析构单例
    {
    public:
        ~Delete_()
        {
            if (Singleton::m_instance)
            {
                delete Singleton::m_instance;
                Singleton::m_instance = nullptr;
            }
        };
    };

    void func()
    {
        cout << "test" << endl;
    }

private:
    Singleton(){}
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance = nullptr;
```

## std::call_once()  

std::call_once()的第二个参数是一个函数名，它能够保证该函数只被调用一次，可以修改上述模板，达到相同的目的  

```c++
std::once_flag my_flag;

class Singleton
{
public:
    static void createInstance()
    {
        m_instance = new Singleton();
        static Delete_ dl;
        // cout << "create\n"; //这行可以证明只执行了一次
    }

    static Singleton* getInstance()
    {
        std::call_once(my_flag, createInstance);
        //两个线程同时执行到这里，其中一个线程要等另外一个线程执行完毕createInstance()

        return m_instance;
    }

    class Delete_ //这个类用来析构单例
    {......};

    ......
};

Singleton* Singleton::m_instance = nullptr;
```
