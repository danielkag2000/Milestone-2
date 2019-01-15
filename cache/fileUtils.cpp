
#include <sys/stat.h>
#include "fileUtils.h"
#include "../exceptions.h"

void mkdirIfNotExist(const char* dir) {
    if (mkdir(dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) {
        // if error
        if (errno != EEXIST) {
            using namespace exceptions;
            throw SYSERR("error making directory");
        }
    }
}