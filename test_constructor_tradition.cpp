#include <iostream>
#include <string.h>

// 测试验证构造函数调用
class CMyString {
public:
    CMyString()
    {
        std::cout << "Default constructor function" << std::endl;
        m_pBuf = NULL;
        m_nBufLen = 0;
    }

    CMyString(const char* str)
    {
        std::cout << "Have param constructor function" << std::endl;
        if (NULL != str) {
            m_nBufLen = strlen(str);
            copy(str);
        } else {
            m_pBuf = NULL;
            m_nBufLen = 0;
        }
    }

    CMyString(const CMyString& str) 
    {
        std::cout << "Copy constructor function" << std::endl;
        m_nBufLen = str.m_nBufLen;
        copy(str.m_pBuf);
    }

    ~CMyString()
    {
        std::cout << "Deconstructor function" << std::endl;
        if (NULL != m_pBuf) {
            std::cout << m_pBuf << std::endl;
            delete[] m_pBuf;
            m_pBuf = NULL;
        }
        m_nBufLen = 0;
    }

public:
    CMyString& operator= (const CMyString& str)
    {
        std::cout << "Assign function" << std::endl;
        if (&str != this) {
            if (NULL != m_pBuf) {
                delete[] m_pBuf;
                m_pBuf = NULL;
            }

            m_nBufLen = str.m_nBufLen;
            copy(str.m_pBuf);
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

void funcUseParamaValue(CMyString a)
{
    std::cout << "use param value" << std::endl;
}

void funcUseParamReference(CMyString& a)
{
    std::cout << "use param reference" << std::endl;
}

CMyString funcReturnValue()
{
    std::cout << "func return value" << std::endl;
    CMyString a;
    return a;
}

CMyString funcReturnValue1()
{
    std::cout << "func return value1" << std::endl;
    return CMyString();
}

//// consider Why not?
// CMyString& funcReturnReference()
// {
    // 局部变量返回引用无效，因为生命周期已随函数结束而结束
//     CMyString a;
//     return a;
// }

int main()
{   
    CMyString a;
    CMyString b("I am is b");
    CMyString c(b);
    CMyString d = b;
    CMyString e;
    e = b;

    funcUseParamaValue(e);
    funcUseParamaValue(CMyString("I am no name"));
    funcUseParamReference(e);
    // funcUseParamReference(CMyString("I am no name"));


    // have some problem?
    CMyString f = funcReturnValue();
    std::cout << "func return value test end" << std::endl;
    CMyString g = funcReturnValue1();
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
// Copy constructor function
// use param value
// Deconstructor function
// I am is b
// Have param constructor function
// use param value
// Deconstructor function
// I am no name
// use param reference
// func return value
// Default constructor function
// func return value test end
// func return value1
// Default constructor function
// func return value test end
// Deconstructor function
// Deconstructor function
// Deconstructor function
// I am is b
// Deconstructor function
// I am is b
// Deconstructor function
// I am is b
// Deconstructor function
// I am is b
// Deconstructor function


//// ========
//// Parse:
// CMyString a;                     Default constructor function
// CMyString b("I am is b");        Have param constructor function
// CMyString c(b);                  Copy constructor function
// CMyString d = b;                 Copy constructor function
// CMyString e;                     Default constructor function
// e = b;                           Assign function

// funcUseParamaValue(e);
// Copy constructor function
// use param value
// Deconstructor function

// funcUseParamaValue(CMyString("I am no name"));
// Have param constructor function
// Copy constructor function
// use param value
// Deconstructor function

// funcUseParamReference(e);
// use param reference

// CMyString f = funcReturnValue();
// Default constructor function
// Deconstructor function
// Copy constructor function

// CMyString g = funcReturnValue1();
// Default constructor function
// Deconstructor function
// Copy constructor function

// Deconstructor function
// Deconstructor function

// Deconstructor function
// Deconstructor function
// Deconstructor function
// Deconstructor function
// Deconstructor function
// Deconstructor function
// Deconstructor function