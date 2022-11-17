#include <iostream>
#include <string>

#include <exception>

using namespace std;

class Exception
{
    string message;
    int code;
public:
    Exception(int code, string message)
        : code { code }, message{ message } {}
    virtual string Message()
    {
        return "Exception [" + to_string(code) + "]: " + message;
    }
};

class NegativeNumberException : public Exception
{
public:
    NegativeNumberException() : Exception(1, "Non positive number") {}
};

class ZeroNumberException : public Exception
{
public:
    ZeroNumberException() : Exception(2, "Zero number") {}
};

class Parent
{
    int value;
public:
    Parent(int value)
    {
        if (value > 0)
            this->value = value;
        else
            if (value == 0)
                throw new ZeroNumberException();
            else
                throw new NegativeNumberException();
    }
};

class Child : public Parent
{
public:
    Child(int value) try : Parent(value) {}
    catch(Exception* e)
    {
        cout << e->Message() << "\n";
        throw new Exception(-100, "My exception");
    }
};

class my_exception : public exception
{
public:
    my_exception() : exception("my error") {};
};

int main()
{
    /*try
    {
        Child child(0);
    }
    catch (Exception* e)
    {
        cout << e->Message() << "\n";
    }*/

    try
    {
        throw new my_exception();
    }
    catch (exception* e)
    {
        cout << e->what();
    }
}
