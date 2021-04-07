/*
 * Main.cpp : Entry point of the application
 * By James Zhang
 */

#include <cstdio>
#include <string>
#include <cstring>

#include "LexPy.h"
#include "DFA.h"

using Helium::PyKWList;

constexpr int Max_Line_Length = 500;

char f_in[100], f_out[2][100];

int main(int argc, char *argv[], char *envp[]) {

    // reading files
    if (argc <= 1) {
        printf("Running by default input: \'./tests/test.py\'\n");
        strcpy(f_in, "./tests/test.py");
    }
    else {
        strcpy(f_in, argv[0]);
    }
    if (argc <= 2) {
        printf("Output into default location: \'./tests/out/\'\n");
        strcpy(f_out[0], "./tests/out/preprocessed.txt");
        strcpy(f_out[1], "./tests/out/lexically_analyzed.txt");
    }
    else {
        strcpy(f_out[0], argv[1]);
        strcpy(f_out[0] + strlen(argv[1]), "preprocessed.txt");
        strcpy(f_out[1], argv[1]);
        strcpy(f_out[1] + strlen(argv[1]), "lexically_analyzed.txt");
    }
    FILE * InFile = fopen(f_in, "r"),
        * OutPreFile = fopen(f_out[0], "w+"),
        * OutLexFile = fopen(f_out[1], "w+");

    // preprocessing: identify comments, indents, continuations, word splits
    // which cannot be done by DFA
    char *current_line = new char[Max_Line_Length];
    int continuation_place(0); // to support continuation feature
    bool raw_contiuation_sing = false, raw_contiuation_doub = false; // to support raw string
    while (fgets(current_line + continuation_place,
                Max_Line_Length - continuation_place,
                InFile) != NULL) {

        char *cur = current_line + continuation_place;
        int spcs(0), idnts(0), len(strlen(cur)), stp(0);
        if (!raw_contiuation_sing && !raw_contiuation_doub) {
            // identify tabs or 4 spaces
            while (stp < len) {
                if (cur[stp] == '\t') ++idnts;
                else if (cur[stp] == ' ') ++spcs;
                else break;
                ++stp;
            }
            /*if (continuation_place != 0 && !(raw_contiuation_sing || raw_contiuation_doub)) {
                for (int i(0); i <= len - idnts - spcs; ++i) {
                    cur[i] = cur[i + idnts + spcs];
                }
            }*/
            idnts += spcs / 4;
            spcs %= 4;
        }

        // identify comments '#', raw string '''''' or contiuation '\'
        bool is_cont = (raw_contiuation_sing || raw_contiuation_doub);
        int endp = (continuation_place + len);
        for (int i(stp); i < len; ++i) {
            if (cur[i] == '\'' && i + 1 < len && cur[i+1] == '\'' && i + 2 < len && cur[i+2] == '\'') {
                if (raw_contiuation_sing) {
                    raw_contiuation_sing = false;
                    is_cont = false;
                    i += 3;
                }
                else {
                    is_cont = raw_contiuation_sing = true;
                    break;
                }
            }
            if (cur[i] == '\"' && i + 1 < len && cur[i+1] == '\"' && i + 2 < len && cur[i+2] == '\"') {
                if (raw_contiuation_doub) {
                    raw_contiuation_doub = false;
                    is_cont = false;
                    i += 3;
                }
                else {
                    is_cont = raw_contiuation_doub = true;
                    break;
                }
            }
            if (!raw_contiuation_sing && !raw_contiuation_doub) {
                if (cur[i] == '#') {
                    cur[i] = '\n';
                    cur[i + 1] = '\0';
                    endp = continuation_place + i + 1;
                    break;
                }
                if (cur[i] == '\\' && cur[i + 1] == '\n') {
                    endp = continuation_place + i;
                    is_cont = true;
                    cur[i] = '\0';
                    break;
                }
            }
        }
        if (is_cont) {
            continuation_place = endp;
            continue;
        }
        continuation_place = 0;
        raw_contiuation_sing = raw_contiuation_doub = false;
        if (current_line[0] == '\n') continue;
        for (int i(0); i < idnts; ++i) {
            fputs("<\'\\t\',Indent>\n", OutPreFile);
        }
        // fputs(current_line, OutPreFile);
        // need to resolve word split, thus scan OPs
        for (int i(0); current_line[i]; ++i) {
            if (current_line[i] == '\n' && current_line[i+1]) {
                fputc('\\', OutPreFile);
                fputc('n', OutPreFile);
            }
            else {
                fputc(current_line[i], OutPreFile);
            }
        }
    }
    delete [] current_line;

    fclose(InFile);
    fclose(OutPreFile);
    fclose(OutLexFile);

    return 0;
}
