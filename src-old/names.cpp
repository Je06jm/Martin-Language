#include <names.hpp>

namespace Martin {

    PackageNamesBase::PackageNamesBase(Tree tree, const std::string& module_name) {
        this->tree = tree;
        this->module_name = module_name;

        // Parse tree for top level names
    }

    void PackageNamesBase::AddPackage(std::shared_ptr<PackageNamesBase> other) {
        other_packages[other->module_name] = other;
    }

    void PackageNamesBase::FinishedAddingPackages() {
        is_valid = true;
    }

    std::string PackageNamesBase::GetName(const std::string& name) const {
        if (!is_valid) return std::string("");
    }
}