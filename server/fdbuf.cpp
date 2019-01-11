//
// Created by Evyatar on 1/10/2019.
//

#include "fdbuf.h"
#include <unistd.h>
#include <poll.h>

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
        ssize_t written = write(_fd, &c, c == EOF ? 0 : 1); // try writing
        return written < 0 ? traits_type::eof() : traits_type::to_int_type(written);
    }

    bool fdbuf::reload() {
        pollfd fd;
        fd.fd = _fd;
        fd.events = POLLIN;

        poll(&fd, 1, _timeoutmillis);

        if (fd.revents != POLLIN) {
            // no data to be read
            RESET_POINTERS
            return false;
        }

        _chars = read(_fd, &_istream[0], _bufsize);

        if (_chars < 0) {
            // failed reading
            RESET_POINTERS
            return false;
        }

        _offset = 0;
        return true;
    }

    std::streamsize fdbuf::xsgetn(char *s, std::streamsize n) {
        // copy old loaded bytes
        std::streamsize totalRead = _chars - _offset;
        std::memcpy(s, &_istream[_offset], totalRead);

        // read from file descriptor into s
        ssize_t countRead = read(_fd, s, n);

        // reset
        RESET_POINTERS

        // calculate entire amount read
        return countRead < 0 ? totalRead : totalRead + countRead;
    }

    int fdbuf::underflow() {
        TRY_RELOADING
        return traits_type::to_int_type(_istream[_offset]);
    }

    int fdbuf::uflow() {
        TRY_RELOADING
        return traits_type::to_int_type(_istream[_offset++]);
    }

    fdbuf::fdbuf(int fd, bool finishClose, int timeoutmillis, int bufsize) :
            _fd(fd), _finishClose(finishClose),
                _bufsize(bufsize), _timeoutmillis(timeoutmillis),
                _chars(0), _offset(0) {
        _istream.resize(bufsize);
    }

    fdbuf::~fdbuf() {
        if (_finishClose) {
            close(_fd);
        }
    }
}