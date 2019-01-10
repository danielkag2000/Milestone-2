#ifndef MILESTONE_2_CLIENTHANDLER_H
#define MILESTONE_2_CLIENTHANDLER_H

#include <ios>
#include <vector>

using namespace std;

namespace server_side {

    typedef char byte;

    class Client {
    private:
        int _fd;
    public:
        /**
         * Construct a client from a given file descriptor
         * @param fd the file descriptor
         */
        Client(int fd);


        /**
         * Read data from this client to a given buffer
         * @param buf the buffer
         * @param length the length of the buffer
         * @return the amount of bytes actually read
         */
        ssize_t read(void* buf, size_t length);

        /**
         * Write buffer data this client
         * @param buf the buffer
         * @param length the buffer length
         */
        void write(void* buf, size_t length);

        /**
         * Read client data into a vector
         * @param v the vector
         * @param len the length of data to be read
         * @param offset the offset to start writing to
         * @return the amount of bytes actually read
         */
        ssize_t read(vector<byte>& v, size_t len, size_t offset = 0);

        /**
         * Write a vector to the client
         * @param v the vector
         * @param len the length to write
         * @param offset the offset to start writing from
         */
        void write(const vector<byte>& v, size_t len, size_t offset = 0);

        /**
         * Close this client.
         */
        void close();

        /**
         * Destructor.
         */
        ~Client();
    };

    class ClientHandler {
    public:
        /**
         * Handle a client
         * @param client the client instance
         */
        virtual void handleClient(Client client) = 0;

        virtual void handleClient(istream& is, ostream& os) = 0;

        /**
         * Copy this instance of client handler.
         * @return a copy.
         */
        virtual ClientHandler* copy() = 0;

        /**
         * Destructor.
         */
        virtual ~ClientHandler() = default;
    };
}

#endif
