#ifndef STREAM_WAITER
#define STREAM_WAITER

#include <sstream>
#include <streambuf>

struct StreamWaiter: std::stringstream {
    std::istream& read(char_type* s, std::streamsize count) {
        do
            count -= rdbuf()->sgetn(s, count);
        while(count > 0);
        return *this;
    }
};

#endif // !STREAM_WAITER
