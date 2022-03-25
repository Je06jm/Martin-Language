#ifndef MARTIN_HELPERS_VALIDATETREE
#define MARTIN_HELPERS_VALIDATETREE

#include <string>
#include <parse.hpp>

namespace Martin {

    enum class ValidateSizeType {
        Equals,
        NotEquals,
        LessThan,
        GreaterThan,
        LessThanEquals,
        GreaterThanEquals
    };

    bool ValidateTokenList(TokenList list, std::string& error, int size = -1, ValidateSizeType size_type = ValidateSizeType::Equals) {
        if (!list) {
            error = "Tokenizer return a nullptr";
            return false;
        }

        if (size >= 0) {
            if ((!(size == list->size()) && (size_type == ValidateSizeType::Equals))) {
                error = Format("Tokenizer returned a list of size $ when expecting $", list->size(), size);
                return false;
            } else if ((!(size != list->size()) && (size_type == ValidateSizeType::NotEquals))) {
                error = Format("Tokenizer returned a list of size $ when expecting any other value", size);
                return false;
            } else if ((!(size < list->size()) && (size_type == ValidateSizeType::LessThan))) {
                error = Format("Tokenizer returned a list of size $ when expecting less than $", list->size(), size);
                return false;
            } else if ((!(size > list->size()) && (size_type == ValidateSizeType::GreaterThan))) {
                error = Format("Tokenizer returned a list of size $ when expecting greater than $", list->size(), size);
                return false;
            } else if ((!(size <= list->size()) && (size_type == ValidateSizeType::LessThanEquals))) {
                error = Format("Tokenizer returned a list of size $ when expecting at most $", list->size(), size);
                return false;
            } else if ((!(size >= list->size()) && (size_type == ValidateSizeType::GreaterThanEquals))) {
                error = Format("Tokenizer returned a list of size $ when expecting at least $", list->size(), size);
                return false;
            }
        }

        return true;
    }

    bool ValidateParserTree(Tree tree, std::string& error, int size = -1, ValidateSizeType size_type = ValidateSizeType::Equals) {
        if (!tree) {
            error = "Parser return a nullptr";
            return false;
        }

        if (size >= 0) {
            if (!((size == tree->size()) && (size_type == ValidateSizeType::Equals))) {
                error = Format("Parser returned a tree of size $ when expecting $", tree->size(), size);
                return false;
            } else if ((!(size != tree->size()) && (size_type == ValidateSizeType::NotEquals))) {
                error = Format("Parser returned a tree of size $ when expecting any other value", size);
                return false;
            } else if ((!(size < tree->size()) && (size_type == ValidateSizeType::LessThan))) {
                error = Format("Parser returned a tree of size $ when expecting less than $", tree->size(), size);
                return false;
            } else if ((!(size > tree->size()) && (size_type == ValidateSizeType::GreaterThan))) {
                error = Format("Parser returned a tree of size $ when expecting greater than $", tree->size(), size);
                return false;
            } else if ((!(size <= tree->size()) && (size_type == ValidateSizeType::LessThanEquals))) {
                error = Format("Parser returned a tree of size $ when expecting at most $", tree->size(), size);
                return false;
            } else if ((!(size >= tree->size()) && (size_type == ValidateSizeType::GreaterThanEquals))) {
                error = Format("Parser returned a tree of size $ when expecting at least $", tree->size(), size);
                return false;
            }
        }

        for (size_t i = 0; i < tree->size(); i++) {
            if ((*tree)[i] == nullptr) {
                error = Format("Parser returned a tree with a nullptr at $", i);
                return false;
            }
        }

        return true;
    }

}

#endif