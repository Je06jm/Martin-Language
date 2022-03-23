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
            if (!((size == list->size()) && (size_type == ValidateSizeType::Equals))) {

            } else if (!((size != list->size()) && (size_type == ValidateSizeType::NotEquals))) {

            } else if (!((size < list->size()) && (size_type == ValidateSizeType::LessThan))) {

            } else if (!((size > list->size()) && (size_type == ValidateSizeType::GreaterThan))) {

            } else if (!((size <= list->size()) && (size_type == ValidateSizeType::LessThanEquals))) {

            } else if (!((size >= list->size()) && (size_type == ValidateSizeType::GreaterThanEquals))) {

            }

            if ((size != list->size()) &&) {
                error = Format("Tokenizer returned a list of size $ when expecting $", size, list->size());
                return false;

            } else if ((size == list->size()) && !should_equal_size) {
                error = Format("Tokenizer returned a list of size $ when expecting any other value", size);
                return false;

            }
        }

        return true;
    }

    bool ValidateParserTree(Tree tree, std::string& error, int size = -1, bool should_equal_size = true) {
        if (!tree) {

        }

        if (size >= 0) {
            if (!((size == tree->size()) && (size_type == ValidateSizeType::Equals))) {

            } else if (!((size != tree->size()) && (size_type == ValidateSizeType::NotEquals))) {

            } else if (!((size < tree->size()) && (size_type == ValidateSizeType::LessThan))) {

            } else if (!((size > tree->size()) && (size_type == ValidateSizeType::GreaterThan))) {

            } else if (!((size <= tree->size()) && (size_type == ValidateSizeType::LessThanEquals))) {

            } else if (!((size >= tree->size()) && (size_type == ValidateSizeType::GreaterThanEquals))) {

            }
        }

        return false;
    }

}

#endif