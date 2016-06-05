#include <time.h>
#include "graph.hpp"

using namespace std;

void print_time() {
    time_t nowtime = time(NULL);
    struct tm *local = localtime(&nowtime);
    cout << '[' << local->tm_hour << ":" << local->tm_min << ":" << local->tm_sec << "] ";
}

void log(string l) {
    print_time();
    cout << l << endl;
}

void display_nbrhood_map(map<int, int> nbrhood) {
    for (map<int,int>::iterator it = nbrhood.begin(); it != nbrhood.end(); it++) {
        cout << "[" << it->first << "] " << it->second << endl;
    }
}

bool equal_map(map<int, int> m1, map<int, int> m2) {
    for (map<int,int>::iterator it = m1.begin(); it != m1.end(); it++) {
        int key = it->first;
        if (it->second != m2[key]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {
    log("constructing graph...");
    Graph g = Graph("testg.txt");
    log("ok!");

    log("entering HyperANF...");
    map<int, int> anf_nbrhood = g.anf_nbrhood_func_map();
    log("ok!");
    display_nbrhood_map(anf_nbrhood);

    if (argc > 1) {
        log("entering bfs...");
        map<int, int> bfs_nbrhood = g.bfs_nbrhood_func_map();
        log("ok!");
        display_nbrhood_map(bfs_nbrhood);
    }
    // cout << equal_map(anf_nbrhood, bfs_nbrhood) << endl;
}
