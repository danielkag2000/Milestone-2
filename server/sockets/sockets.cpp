#include "sockets.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


namespace exceptions {
#define SYSERR(msg) (system_generic_error(errno, (msg)))

    TCPSocket::TCPSocket() : _sockfd(socket(AF_INET, SOCK_STREAM, 0)) {
        if (_sockfd < 0) {
            throw system_generic_error(errno, "failure opening socket");
        }
    }

    TCPSocket::TCPSocket(int sockfd) : _sockfd(sockfd) { }

    void TCPSocket::close() {
        if (::close(_sockfd) < 0) {
            throw SYSERR("failure closing socket");
        }
    }

    void TCPSocket::setTimeout(int sec, int usec) {
        timeval timeout;
        timeout.tv_sec = sec;
        timeout.tv_usec = usec;

        if (setsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO,
                &timeout, sizeof(timeout)) < 0) {
            throw SYSERR("failure setting timeout");
        }
    }

    int TCPSocket::fd() {
        return _sockfd;
    }

    timeval TCPSocket::getTimeout() {
        timeval tv;
        socklen_t skln;

        getsockopt(_sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, &skln);

        return tv;
    }

    TCPServer::TCPServer(int port) : _sock() {
        int sockfd = _sock.fd();

        sockaddr_in addr_in;
        addr_in.sin_family = AF_INET;
        addr_in.sin_port = htons(port);
        addr_in.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (sockaddr*) &addr_in, sizeof(addr_in)) < 0) {
            _sock.close();
            throw SYSERR("failure binding socket");
        }
    }

    void TCPServer::listen(int max_lis) {
        if (::listen(_sock.fd(), max_lis) < 0) {
            throw SYSERR("failure listening");
        }
    }

    void TCPServer::setTimeout(int sec, int usec) {
        _sock.setTimeout(sec, usec);
    }

    timeval TCPServer::getTimeout() {
        return _sock.getTimeout();
    }

    TCPSocket TCPServer::accept() {
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int clientfd = ::accept(_sock.fd(), (sockaddr*)&addr, &len);

        if (clientfd < 0)	{
            // eagain and ewouldblock happen regularly on timeouts
            if (errno == EAGAIN || errno == EWOULDBLOCK)	{
                throw timeout_exception("timeout on accept");
            } else {
                throw SYSERR("failure accepting");
            }
        }

        return TCPSocket(clientfd);
    }

    void TCPServer::close() {
        _sock.close();
    }
}