#ifndef MARTIN_HELPERS_TOKENNODE
#define MARTIN_HELPERS_TOKENNODE

#include <parse.hpp>

namespace Martin {

    TokenNode GetTokenNodeFromTokenList(TokenList list, size_t index) {
        if (!list)
            Fatal("Trying to get an item on a nullptr token list\n");
        
        if (index >= list->size())
            Fatal("Could not get an item at index $ from a token list\n", index);

        TokenNode node = TokenNode(new TokenNodeBase);
        node->is_token = true;
        node->token = (*list)[index];

        return node;
    }

    TokenNode GetTokenNodeFromParseList(Tree list, size_t index) {
        if (!list)
            Fatal("Trying to get an item on a nullptr parse list\n");
        
        if (index >= list->size())
            Fatal("Could not get an item at index $ from a parse list\n", index);
        
        return (*list)[index];
    }

}

#endif