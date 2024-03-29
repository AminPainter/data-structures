#include <iostream>

using namespace std;

#ifndef ERROR_H
#define ERROR_H

class Error
{
private:
    string message;

public:
    Error(string message)
    {
        this->message = message;
    }

    friend ostream &operator<<(ostream &print, Error &err)
    {
        return print << "ERROR: { message: \"" << err.message << "\" }\n";
    }
};

#endif