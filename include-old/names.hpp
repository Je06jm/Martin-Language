#ifndef MARTIN_NAMES
#define MARTIN_NAMES

#include <parse.hpp>
#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

namespace Martin {

    class PackageNamesBase {
    public:
        PackageNamesBase(Tree tree, const std::string& module_name);

        void AddPackage(std::shared_ptr<PackageNamesBase> other);
        void FinishedAddingPackages();

        std::string GetName(const std::string& name) const;

    private:
        bool is_valid = false;
        
        Tree tree;

        std::string module_name;

        std::vector<std::string> names;
        std::unordered_map<std::string, std::shared_ptr<PackageNamesBase>> other_packages;
    };

    typedef std::shared_ptr<PackageNamesBase> PackageNames;

}

#endif