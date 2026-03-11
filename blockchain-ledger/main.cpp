#include <iostream>
#include <fstream>
#include "BlockChain.h"
#include "Utilities.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << getErrorMessage() << endl;
        return 0;
    }

    string op = argv[1];
    string sourceFile = argv[2];
    string targetFile = argv[3];

    ifstream source(sourceFile);
    if (!source) {
        cout << getErrorMessage() << endl;
        return 0;
    }

    if (op == "format") {
        ofstream target(targetFile);
        if (!target) {
            cout << getErrorMessage() << endl;
            return 0;
        }
        BlockChain chain = BlockChainLoad(source);
        BlockChainDump(chain, target);

    } else if (op == "hash") {
        ofstream target(targetFile);
        if (!target) {
            cout << getErrorMessage() << endl;
            return 0;
        }
        BlockChain chain = BlockChainLoad(source);
        BlockChainDumpHashed(chain, target);

    } else if (op == "compress") {
        ofstream target(targetFile);
        if (!target) {
            cout << getErrorMessage() << endl;
            return 0;
        }
        BlockChain chain = BlockChainLoad(source);
        BlockChainCompress(chain);
        BlockChainDump(chain, target);

    } else if (op == "verify") {
        ifstream target(targetFile);
        if (!target) {
            cout << getErrorMessage() << endl;
            return 0;
        }
        BlockChain chain = BlockChainLoad(source);
        bool ok = BlockChainVerifyFile(chain, target);
        cout << "Verification " << (ok ? "passed" : "failed") << endl;

    } else {
        cout << getErrorMessage() << endl;
        return 0;
    }

    return 0;
}
