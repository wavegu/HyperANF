#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "lib/hyperloglog.hpp"

using namespace std;
using namespace hll;

enum ncolor {
    WHITE,
    GRAY,
    BLACK
};

class Node{
public:
    ncolor color;
    string id;
    vector<string> successors;
    HyperLogLog old_hll;
    HyperLogLog new_hll;

    Node() {}

    Node(string nodeline) {
        int beg = 0;
        int pos = nodeline.find(' ');
        if (pos < 0) {
            id = nodeline;
        } else {
            id = nodeline.substr(beg, pos-beg);
            beg = pos + 1;
            pos = nodeline.find(' ', beg);
            while (pos > 0) {
                successors.push_back(nodeline.substr(beg, pos-beg));
                beg = pos + 1;
                pos = nodeline.find(' ', beg);
            }
            if (beg < nodeline.size()) {
                successors.push_back(nodeline.substr(beg, nodeline.size()-beg));
            }
        }
        color = WHITE;
        old_hll = HyperLogLog(12);
        old_hll.add(id.c_str(), id.size());
        new_hll = old_hll;
    }

    Node(const Node &other) {
        id = other.id;
        successors = other.successors;
        old_hll = other.old_hll;
        new_hll = other.new_hll;
    }

    // Node & Node::operator = (const Node & other) {
    //     id = other.id;
    //     successors = other.successors;
    //     hll = other.hll;
    //     return *this;
    // }

    void display() {
        cout << "[node" << id << "] ";
        // for (vector<string>::iterator it = successors.begin(); it != successors.end(); it++)
        // {
        //     cout << *it << ' ';
        // }
        for (uint32_t i = 0; i < new_hll.m_; i++) {
            cout << int(new_hll.M_[i]) << ' ';
        }
        cout << '(' << successors.size() << ')' << endl;
    }
};
