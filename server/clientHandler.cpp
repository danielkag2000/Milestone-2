#include "clientHandler.h"
#include <unistd.h>
#include <vector>

#define VECTOR_PTR(v, offset) ((v.begin() + offset).base())

namespace server_side {

    Client::Client(int fd) : _fd(fd) { }

    void Client::read(void *buf, size_t length) {
        ::read(_fd, buf, length);
    }

    void Client::write(void *buf, size_t length) {
        ::write(_fd, buf, length);
    }

    void Client::read(vector<char *> v, size_t len, size_t offset) {
        ::read(_fd, VECTOR_PTR(v, offset), len);
    }

    void Client::write(vector<char *> v, size_t len, size_t offset) {
        ::write(_fd, VECTOR_PTR(v, offset), len);
    }

    void Client::close() {
        ::close(_fd);
    }

    Client::~Client() {
        close();
    }
}