/*
 * LexPy.h : Provide Python-like grammer support
 * By James Zhang
 */

#ifndef LEXPY
#define LEXPY

#include <string>
#include <vector>

namespace Helium {

using WordsVec = std::vector<std::string>;

// This is the keyword list in Python
WordsVec PyKWList = {
    "False", "None", "True", "and", "as", "assert", "break", "class", "continue", "def", "del", "elif", "else", "except", "finally", "for", "from", "global", "if", "import", "in", "is", "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try", "while", "with", "yield"
    };

WordsVec PySingOpList = {
    "(", ")", "[", "]", ">", "<", "%", "^", "*", "-", "+", "=", "/", ".", ">", "<", ",", ":"
    };

WordsVec PyCompOpList = {
    "+=", "-=", "*=", "/=", ">>", "<<"
    };

};

#endif // LEXPY