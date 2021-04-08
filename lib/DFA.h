/*
 * DFA.h : Provide An Universial DFA Implementation
 * By James Zhang
 */

#ifndef DFAH
#define DFAH

#include <string>
#include <cstring>
#include <map>
#include <vector>

namespace Helium {

using WordsVec = std::vector<std::string>;

class DFA {
private:
    struct node {
        std::map<char, node*> edge;
        node * och_default;
        std::string TokenType;
        int nID, TokenID; // -1 indicate inacceptable states
        node(int n) : nID(n), edge(), TokenType(), TokenID(-1) {}
        node(int n, std::string type, int id) : nID(n), edge(), TokenType(type), TokenID(id) {}
    } *S;
    node *now;
    int N, TKN; // node count, token count
    node * tknn, // identifier
        * rstn;
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
        TKN = 0;
        now = S = new node(N++);
        S->och_default = S;
        tknn = new node(N++, "Identifier", TKN++);
        rstn = new node(N++, "Identifier", TKN++);
        S->edge['_'] = tknn;
        tknn->edge['_'] = rstn;
        tknn->och_default = S;
        rstn->edge['_'] = rstn;
        rstn->och_default = S;
    }
    ~DFA() {
        bool *vis = new bool [N];
        memset(vis, 0, sizeof(vis));
        dfs_destruct(vis, S);
        delete [] vis;
    }
    void add_number_rule() { // [0-9]*(.[0-9]*)+
        node * stnn = new node(N++, "Integer", TKN++),
            * flt = stnn->edge['.'] = new node(N++, "Float   ", TKN++);
        stnn->och_default = S;
        flt->och_default = S;
        for (char i('0'); i <= '9'; ++i) {
            S->edge[i] = stnn;
            stnn->edge[i] = stnn;
            flt->edge[i] = flt;
        }
    }
    void add_token_rule() { // [a-zA-Z][a-zA-z0-9_]*
        for (char i('a'); i <= 'z'; ++i) {
            if (S->edge.count(i)) continue;
            S->edge[i] = tknn;
        }
        for (char i('a'); i <= 'z'; ++i) {
            tknn->edge[i] = rstn;
            rstn->edge[i] = rstn;
        }
        for (char i('A'); i <= 'Z'; ++i) {
            if (S->edge.count(i)) continue;
            S->edge[i] = tknn;
        }
        for (char i('A'); i <= 'Z'; ++i) {
            tknn->edge[i] = rstn;
            rstn->edge[i] = rstn;
        }
        for (char i('0'); i <= '9'; ++i) {
            tknn->edge[i] = rstn;
            rstn->edge[i] = rstn;
        }
    }
    void add_str_rule() { // ['"][]*['"]
        node * stn = new node(N++), *fina = new node(N++, "String  ", TKN++);
        S->edge['\"'] = stn;
        stn->och_default = stn;
        stn->edge['\"'] = fina;
        // now for ' do again
        stn = new node(N++);
        S->edge['\''] = stn;
        stn->och_default = stn;
        stn->edge['\''] = fina;

        fina->och_default = S;
    }
    void add_new_OP_Trie(WordsVec src, std::string tnm) {
        for (auto str : src) {
            node *work(S);
            for (auto ch : str) {
                if (!(work->edge.count(ch))) {
                    work->edge[ch] = new node(N++);
                    work->edge[ch]->och_default = S;
                }
                work = work->edge[ch];
            }
            work->TokenID = TKN++;
            work->TokenType = tnm;
        }
    }
    void add_new_KW_Trie(WordsVec src, std::string tnm) {
        for (auto str : src) {
            node *work(S);
            for (auto ch : str) {
                if (!(work->edge.count(ch)) || work->edge[ch] == rstn) {
                    work->edge[ch] = new node(N++);
                    work = work->edge[ch];

                    work->och_default = S;
                    work->TokenID = TKN++;
                    work->TokenType = "Identifier";
                    work->edge['_'] = rstn;
                    for (char i('a'); i <= 'z'; ++i) {
                        work->edge[i] = rstn;
                    }
                    for (char i('A'); i <= 'Z'; ++i) {
                        work->edge[i] = rstn;
                    }
                    for (char i('0'); i <= '9'; ++i) {
                        work->edge[i] = rstn;
                    }
                }
                else {
                    work = work->edge[ch];
                }
            }
            work->TokenType = tnm;
        }
    }
    std::pair<int, std::string> next(char a) { // -1 continue, -2 is tab, -3 ignore
        printf("%c %d %d %d \"%s\"\n", a, (void*)S, (void*)(now->och_default), now->TokenID, now->TokenType.c_str());
        if (now == S && a == '\t') {
            return std::make_pair(-2, "Indent");
        }
        else if (now == S && (a == ' ' || a == '\n' || a == '\r')) {
            return std::make_pair(-3, "");
        }
        else if (now->edge.count(a) && now->edge[a] == S || !(now->edge.count(a)) && now->och_default == S) {
            auto res = std::make_pair(now->TokenID, now->TokenType);
            now = S;
            if (now->edge.count(a)) {
                now = now->edge[a];
            }
            return res;
        }
        else if (now->edge.count(a)) {
            now = now->edge[a];
            return std::make_pair(-1, "");
        }
        else if (now->och_default != S) {
            now = now->och_default;
            return std::make_pair(-1, "");
        }
        else {
            printf("FATAL! next fail!\n");
            exit(0);
        }
    }
};

}

#endif // LEXPY