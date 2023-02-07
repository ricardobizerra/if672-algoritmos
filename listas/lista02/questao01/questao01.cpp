#include <iostream>
using namespace std;

int main(){
    string cmd;
    cin >> cmd;

    bool programa_encerrado = false;

    while (programa_encerrado == false) {

        if (cmd == "END") {
            programa_encerrado = true;
        }

    }

    return 0;
}