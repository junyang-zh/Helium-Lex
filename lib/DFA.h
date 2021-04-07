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
    node *now;
    int N, TKN; // node count, token count
    void dfs_destruct(bool vis[], node *n) {
        vis[n->nID] = true;
        for (auto ch : n->edge) {
            if (!vis[n->nID]) dfs_destruct(vis, ch.second);
        }
        delete n;
        return;
    }
    void trie_build(std::string str, std::string tnm) {
        node *work(S);
        for (auto ch : str) {
            if (!(work->edge.count(ch))) {
                work->edge[ch] = new node(N++);
            }
            work = work->edge[ch];
        }
        work->TokenID = TKN++;
        work->TokenType = tnm;
    }
public:
    DFA() {
        N = 0;
        TKN = 0;
        now = S = new node(N++);
    }
    ~DFA() {
        bool *vis = new bool [N];
        dfs_destruct(vis, S);
        delete [] vis;
    }
    void add_LEX_rule() {
        
    }
    void add_new_Words_Trie(WordsVec src, std::string name) {
        for (auto str : src) {
            trie_build(str, name);
        }
    }
    void next(char a) {
        if (!(now->edge.count(a))) {
            now = now->edge[a];
        }
        else {
            now = S;
        }
    }
};

}

#endif // LEXPY