#ifndef MILESTONE_2_FDBUF_H
#define MILESTONE_2_FDBUF_H

#include <ios>
#include <cstring>
#include <vector>

namespace server_side {
    class fdbuf : public std::streambuf {

    private:
        int _fd;
        bool _finishClose;
    protected:
        /* output section */

        /**
         * Put characters and flush the output stream.
         * @param c the characters
         * @param n the amount of characters
         * @return the amount of characters read or a negative number if failed
         */
        virtual std::streamsize xsputn(const char* c, std::streamsize n);

        /**
         * Put a character into the output stream.
         * @param c the character
         * @return the character as traits_type::to_int_type upon success. eof upon failure.
         */
        virtual int overflow(int c = EOF);

        /* input section */
    private:
        std::streamsize _chars;
        std::streamsize _offset;
        std::vector<char> _istream;
        const int _timeoutmillis;
        const int _bufsize;

    private:
        /**
         * Reload the buffer.
         * @return true if managed to, false otherwise.
         */
        bool reload();

    protected:
        /**
         * Get n characters from the input sequence.
         * @param s a buffer to put the characters in
         * @param n the maximal amount of characters to read
         * @return the amount of characters read
         */
        virtual std::streamsize xsgetn(char* s, std::streamsize n);

        /**
         * Try getting a character from input stream.
         * @return the character if succeeded. otherwise traits_type::eof()
         */
        virtual int underflow();

        /**
         * Try getting a character from input stream and advance position.
         * @return the character if succeeded. otherwise traits_type::eof()
         */
        virtual int uflow();


    public:
        /**
         * Construct a new fdbuf.
         * @param fd a file descriptor for this buffer
         * @param finishClose whether to close the file descriptor upon finishing
         */
        fdbuf(int fd, bool finishClose = false, int timeoutMillis = 200, int bufsize = 128);

        /**
         * Destructor.
         * Closes file descriptor if needed.
         */
        ~fdbuf();
    };
}


#endif
