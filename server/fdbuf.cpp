//
// Created by Evyatar on 1/10/2019.
//

#include "fdbuf.h"
#include <unistd.h>
#include <poll.h>
#include <iostream>

#define TRY_RELOADING \
		if (_offset == _chars && !reload()) { \
			return traits_type::eof(); \
		}

#define RESET_POINTERS \
	_chars = 0; \
	_offset = 0;

namespace server_side {
    std::streamsize fdbuf::xsputn(const char *__s, std::streamsize __n) {
        return write(_fd, __s, __n);
    }

    int fdbuf::overflow(int c) {
        ssize_t written = write(_fd, &c, c == EOF ? 0 : 1); // try writing(if c is not EOF)
        return written < 0 ? traits_type::eof() : traits_type::to_int_type(written);
    }

    bool fdbuf::reload() {
        _chars = read(_fd, &_istream[0], _bufsize);

        if (_chars <= 0) {
            // read nothing
            RESET_POINTERS
            return false;
        }

        _offset = 0;
        return true;
    }

    void fdbuf::copybuf(char *target, std::streamsize len) {
        using std::memcpy;

        memcpy(target, &_istream[_offset], len);
        _offset += len;
    }

    std::streamsize fdbuf::available() {
        return _chars - _offset;
    }

    std::streamsize fdbuf::xsgetn(char *s, std::streamsize n) {
        using std::streamsize;

        // copy old loaded bytes
        streamsize oldBytes = available();

        if (oldBytes >= n) {
            copybuf(s, n);
            return n;
        }

        // copy all available bytes
        copybuf(s, oldBytes);

        // read from file descriptor into s
        ssize_t countRead = read(_fd, s, n - oldBytes);

        // calculate entire amount read
        return countRead < 0 ? oldBytes : oldBytes + countRead;
    }

    int fdbuf::underflow() {
        TRY_RELOADING

        if (_offset >= _chars) {
            std::cout << "hi" << std::endl;
        }

        return traits_type::to_int_type(_istream[_offset]);
    }

    int fdbuf::uflow() {
        TRY_RELOADING
        return traits_type::to_int_type(_istream[_offset++]);
    }

    fdbuf::fdbuf(int fd, bool finishClose, int bufsize) :
            _fd(fd), _finishClose(finishClose),
                _bufsize(bufsize),
                _chars(0), _offset(0) {
        _istream.resize(bufsize);
    }

    fdbuf::~fdbuf() {
        if (_finishClose) {
            close(_fd);
        }
    }
}