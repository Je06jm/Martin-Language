#ifndef MARTIN_GRAMMAR_HPP
#define MARTIN_GRAMMAR_HPP

auto MartinGrammar = R"(
    ScripExp <- DotExp ('[' ScripExp ']')? / NAME
    DotExp <- CallExp ('.' CallExp)*
    CallExp <- NAME / ScripExp '(' (ScripExp (',' ScripExp)*)? ')' / ScripExp

    #NUMBER  <- < [0-9]+('.'[0-9]+)? >
    NAME <- < [a-zA-Z_][a-zA-Z_0-9]* >
    %whitespace <- [ \t\n]*
    %word <- NAME
)";

#endif