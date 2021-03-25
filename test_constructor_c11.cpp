#include <iostream>
#include <string.h>

// 测试验证构造函数调用
class CMyStringC11 {
public:
    CMyStringC11()
    {
        std::cout << "Default constructor function" << std::endl;
        m_pBuf = nullptr;
        m_nBufLen = 0;
    }

    CMyStringC11(const char* str)
    {
        std::cout << "Have param constructor function" << std::endl;
        if (nullptr != str) {
            m_nBufLen = strlen(str);
            copy(str);
        } else {
            m_pBuf = nullptr;
            m_nBufLen = 0;
        }
    }

    CMyStringC11(const CMyStringC11& str) 
    {
        std::cout << "Copy constructor function" << std::endl;
        m_nBufLen = str.m_nBufLen;
        copy(str.m_pBuf);
    }

    CMyStringC11(CMyStringC11&& str) 
    {
        std::cout << "Move constructor function" << std::endl;
        m_nBufLen = str.m_nBufLen;
        m_pBuf = str.m_pBuf;
        
        str.m_nBufLen = 0;
        str.m_pBuf = nullptr;
    }

    ~CMyStringC11()
    {
        std::cout << "Deconstructor function" << std::endl;
        if (nullptr != m_pBuf) {
            std::cout << m_pBuf << std::endl;
            delete[] m_pBuf;
            m_pBuf = nullptr;
        }
        m_nBufLen = 0;
    }

public:
    CMyStringC11& operator= (const CMyStringC11& str)
    {
        std::cout << "Assign function" << std::endl;
        if (&str != this) {
            if (nullptr != m_pBuf) {
                delete[] m_pBuf;
                m_pBuf = nullptr;
            }

            m_nBufLen = str.m_nBufLen;
            copy(str.m_pBuf);
        }

        return *this;
    }

    CMyStringC11& operator= (CMyStringC11&& str)
    {
        std::cout << "Move assign function" << std::endl;
        if (&str != this) {
            if (nullptr != m_pBuf) {
                delete[] m_pBuf;
                m_pBuf = nullptr;
            }

            m_nBufLen = str.m_nBufLen;
            m_pBuf = str.m_pBuf;

            str.m_nBufLen = 0;
            str.m_pBuf = nullptr;
        }

        return *this;
    }

private:
    void copy(const char* s) {
        m_pBuf = new char[m_nBufLen + 1];
        memcpy(m_pBuf, s, m_nBufLen);
        m_pBuf[m_nBufLen] = '\0';
    }

private:
    char*   m_pBuf;
    int     m_nBufLen;
};

void funcUseParamaValue(CMyStringC11 a)
{
    std::cout << "use param value" << std::endl;
}

void funcUseParamReference(CMyStringC11& a)
{
    std::cout << "use param reference" << std::endl;
}

CMyStringC11 funcReturnValue()
{
    std::cout << "func return value" << std::endl;
    CMyStringC11 a("returnValue");
    return a;
}

CMyStringC11 funcReturnValue1()
{
    std::cout << "func return value1" << std::endl;
    return CMyStringC11();
}

//// consider Why not?
// CMyStringC11& funcReturnReference()
// {
    // 局部变量返回引用无效，因为生命周期已随函数结束而结束
//     CMyStringC11 a;
//     return a;
// }

int main()
{   
    CMyStringC11 a;
    CMyStringC11 b("I am is b");
    CMyStringC11 c(b);
    CMyStringC11 d = b;
    CMyStringC11 e;
    e = b;
    CMyStringC11 e1(std::move(e));

    funcUseParamaValue(e);
    funcUseParamaValue(CMyStringC11("I am no name"));
    funcUseParamReference(e);
    // funcUseParamReference(CMyStringC11("I am no name"));


    // have some problem?
    CMyStringC11 f = funcReturnValue();
    std::cout << "func return value test end" << std::endl;
    CMyStringC11 g = funcReturnValue1();
    std::cout << "func return value test end" << std::endl;

    return 0;
}


//// ========
//// Result:
// Default constructor function
// Have param constructor function
// Copy constructor function
// Copy constructor function
// Default constructor function
// Assign function
// Move constructor function
// Copy constructor function
// use param value
// Deconstructor function

// Have param constructor function
// use param value
// Deconstructor function
// I am no name
// use param reference
// func return value
// Have param constructor function
// func return value test end
// func return value1
// Default constructor function
// func return value test end
// Deconstructor function
// Deconstructor function
// returnValue
// Deconstructor function
// I am is b
// Deconstructor function
// Deconstructor function
// I am is b
// Deconstructor function
// I am is b
// Deconstructor function
// I am is b
// Deconstructor function