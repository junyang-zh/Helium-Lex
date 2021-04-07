/*
 * DFA.h : Provide An Universial DFA Implementation
 * By James Zhang
 */

#ifndef DFAH
#define DFAH

#include <string>
#include <map>
#include <vector>

namespace Helium {

using WordsVec = std::vector<std::string>;

class DFA {
private:
    struct node {
        std::map<char, node*> edge;
        std::string TokenType;
        int nID, TokenID; // -1 indicate inacceptable states
        node(int n) : nID(n), edge(), TokenType(), TokenID(-1) {}
        node(int n, std::string type, int id) : nID(n), edge(), TokenType(type), TokenID(id) {}
    } *S;
    int N; // node count
    void dfs_destruct(bool vis[], node *n) {
        vis[n->nID] = true;
        for (auto ch : n->edge) {
            if (!vis[n->nID]) dfs_destruct(vis, ch.second);
        }
        delete n;
        return;
    }
public:
    DFA() {
        N = 0;
        S = new node(N++);
    }
    ~DFA() {
        bool *vis = new bool [N];
        dfs_destruct(vis, S);
        delete [] vis;
    }
    void add_new_Words_Trie(WordsVec) {
        
    }
};

}

#endif // LEXPY