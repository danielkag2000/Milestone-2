#include "server/parallelServer.h"
#include "server/my_client_handler.h"
#include <unistd.h>

namespace boot {

    class Main {
    public:
        int main(int argc, char *argv[]) {
            using namespace server_side;
            using namespace cache;

            int port ;

            try {
                port = stoi(argv[1]);
            }
            catch (const exception& e) {
                cerr << "invalid port entered." << endl;
                return 1;
            }


            Server *s = new ParallelServer;
            MyClientHandler ch;

            s->open(port, &ch);

            sleep(1);
            if (s->isOpen()) {
                s->wait();
            }

            ch.closeCache();

            delete s;

            return 0;
        }
    };
}

int main(int argc, char* argv[]) {
    boot::Main run;
    return run.main(argc, argv);
}