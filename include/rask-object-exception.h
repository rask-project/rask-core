#pragma once

#ifdef __cpp_exceptions
#include <exception>

namespace RaskException {

enum class Error
{
    Error = -1,
    Ok = 0,
    TimerIntervalInvalid
};

class ObjectException : public std::exception
{
public:
    ObjectException(Error error);

    virtual const char *what() const noexcept;

private:
    Error m_error;
};

} // RaskException

#endif