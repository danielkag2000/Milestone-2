#ifndef MILESTONE_2_SOCKET_EXCEPTIONS_H
#define MILESTONE_2_SOCKET_EXCEPTIONS_H

#include <system_error>
#include <stdexcept>

namespace exceptions {
    class timeout_exception : public std::runtime_error {
    public:
        timeout_exception(const char* msg) : std::runtime_error(msg){}
        timeout_exception(std::string msg) : std::runtime_error(msg){}
    };

    class illegal_state_exception : public std::logic_error {
    public:
        illegal_state_exception(std::string msg) : std::logic_error(msg){}
    };

    struct system_generic_error : public std::system_error {
        system_generic_error(int errorno, const std::string& msg)
            : std::system_error(
                    std::error_code(errorno, std::generic_category()),
                    msg){
        }
    };
}

#endif
