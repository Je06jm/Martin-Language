#ifndef MARTIN_PACKAGE
#define MARTIN_PACKAGE

#include <string>
#include <vector>
#include <memory>
#include "versions.hpp"

namespace Martin {

    class Package {
    public:
        typedef struct {
            const std::string name;
            const Version version;
        } DependentPackage;

        typedef struct {
            const std::string name;
            const std::string email;
        } Author;

        typedef struct {
            const std::string name;
            const std::vector<std::string> files;
        } PlatformFiles;

        enum class Type {
            Source,
            Bytecode,
            Static,
            Shared
        };
        
        Package(
            const std::string& name,
            const Version& version,
            const std::string& source_directory,
            const Type& type,
            const std::vector<std::string>& additional_files,
            const std::vector<PlatformFiles>& platform_files,
            const Version& language_version,
            const std::vector<std::string>& local_package_paths,
            const std::vector<Package::DependentPackage>& packages,
            const std::vector<Package::Author>& authors,
            const std::string& link,
            const std::string& license
        ) :
            name(name),
            version(version),
            source_directory(source_directory),
            type(type),
            additional_files(additional_files),
            platform_files(platform_files),
            language_version(language_version),
            local_package_paths(local_package_paths),
            packages(packages),
            authors(authors),
            link(link),
            license(license) {}

        const std::string name;
        const Version version;
        const std::string source_directory;
        const Type type;
        const std::vector<std::string> additional_files;
        const std::vector<PlatformFiles> platform_files;
        const Version language_version;
        const std::vector<std::string> local_package_paths;
        const std::vector<DependentPackage> packages;
        const std::vector<Author> authors;
        const std::string link;
        const std::string license;

        void SaveToFile(const std::string& path);

        static std::unique_ptr<Package> LoadFromFile(const std::string& path);
        static std::unique_ptr<Package> CreateEmpty();
    };

}

#endif