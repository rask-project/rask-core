#ifdef __cpp_exceptions
#include "rask-object-exception.h"

namespace RaskException {

ObjectException::ObjectException(Error error) : m_error(error) {}

const char *ObjectException::what() const noexcept {
    switch (m_error) {
    case Error::Ok: return "No Error";
    case Error::TimerIntervalInvalid: return "No valid interval have been set";
    case Error::NoFunctionDefined: return "No function defined";
    default: return "Unknown error";
    }
}

} // RaskException

#endif
