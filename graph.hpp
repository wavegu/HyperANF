#include <map>
#include <queue>
#include "node.hpp"

#define MAXINT 99999999

using namespace std;


class Graph {
public:

    map<string, Node*> node_map;

    Graph(string filename) {
        ifstream fin(filename);
        string nodeline;
        while (getline(fin, nodeline)) {
            Node *node = new Node(nodeline);
            node_map[node->id] = node;
        }
    }

    ~Graph() {
        for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++) {
            delete it->second;
        }
    }

    map<int,int> anf_nbrhood_func_map() {
        map<int,int> nbhood_func_map;
        int t = 0;
        bool has_change = true;
        while (has_change) {
            has_change = false;
            nbhood_func_map[t] = 0;
            // cout << "t = " << t << endl;
            for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++) {
                nbhood_func_map[t] += it->second->new_hll.estimate();
                it->second->old_hll = it->second->new_hll;
                // cout << it->second->id << ' ' << it->second->new_hll.estimate() << endl;
            }
            // cout << "[" << t << "] " << nbhood_func_map[t] << endl;
            for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++) {
                vector<string> succs = it->second->successors;
                for (vector<string>::iterator succ_it = succs.begin(); succ_it != succs.end(); succ_it++) {
                    Node *nb = node_map[*succ_it];
                    // cout << "(" << it->second->id << "," << nb->id << ") ";
                    has_change = it->second->new_hll.merge(nb->old_hll) || has_change;
                }
            }
            t++;
        }
        int pre = 0;
        for (map<int,int>::iterator it = nbhood_func_map.begin(); it != nbhood_func_map.end(); it++) {
            if (it == nbhood_func_map.begin()) {
                pre = it->second;
                continue;
            }
            int num = it->second;
            it->second = num - pre;
            pre = num;
        }
        return nbhood_func_map;
    }

    map<int,int> bfs_nbrhood_func_map() {
        map<int,int> nbrhood_func_map;
        for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++){
            Node *node = it->second;
            map<string,int> distance_map = bfs_distance_map(node);
            for (map<string,int>::iterator it = distance_map.begin(); it != distance_map.end(); it++) {
                int dis = it->second;
                // if (dis == MAXINT)  continue;
                if (nbrhood_func_map.find(dis) == nbrhood_func_map.end())
                    nbrhood_func_map[dis] = 0;
                nbrhood_func_map[dis]++;
            }
        }
        return nbrhood_func_map;
    }

    map<string,int> bfs_distance_map(Node *s) {
        map<string,int> distance_map;
        map<string,Node*> parent_map;
        queue<Node*> q;
        for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++) {
            Node *node = it->second;
            node->color = WHITE;
            distance_map[node->id] = MAXINT;
            parent_map[node->id] = NULL;
        }
        s->color = GRAY;
        distance_map[s->id] = 0;
        parent_map[s->id] = NULL;
        q.push(s);
        while(q.size() != 0) {
            Node *u = q.front();
            vector<string> succs = u->successors;
            for (vector<string>::iterator it = succs.begin(); it != succs.end(); it++) {
                Node *v = node_map[*it];
                if (v->color == WHITE) {
                    v->color = GRAY;
                    distance_map[v->id] = distance_map[u->id] + 1;
                    parent_map[v->id] = u;
                    q.push(v);
                }
            }
            q.pop();
            u->color = BLACK;
        }
        return distance_map;
    }

    void display() {
        for (map<string,Node*>::iterator it = node_map.begin(); it != node_map.end(); it++)
            it->second->display();
    }

};
