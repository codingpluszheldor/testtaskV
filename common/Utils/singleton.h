#ifndef SINGLETON_H_
#define SINGLETON_H_

namespace util
{
    //------------ Singleton pattern --------------
    template <class mySingleton>
    class Singleton
    {
    protected:
        Singleton() {}
        Singleton(const Singleton&) {}
        inline Singleton& operator = (const Singleton &) { return *this; }
        virtual ~Singleton() {}
    public:
        static mySingleton& Instance()
        {
            static mySingleton *_instance = nullptr;
            if (_instance == 0)
            {
                _instance = new mySingleton;
            };
            return *_instance;
        }
    };
    //----------------------------------------------
}

#endif /*SINGLETON_H_*/
