#ifndef MARTIN_PROJECT
#define MARTIN_PROJECT

#include <string>
#include <vector>
#include <memory>
#include "versions.hpp"

namespace Martin {

    class Project {
    public:
        typedef struct {
            const std::string name;
            const Version version;
        } Package;

        typedef struct {
            const std::string name;
            const std::string email;
        } Author;

        typedef struct {
            const std::string name;
            const std::vector<std::string> files;
        } PlatformFiles;
        
        Project(
            const std::string& name,
            const Version& version,
            const std::string& source_directory,
            const std::string& main_file,
            const std::string& output,
            const std::vector<std::string>& additional_files,
            const std::vector<PlatformFiles>& platform_files,
            const Version& language_version,
            const std::vector<std::string>& local_package_paths,
            const std::vector<Project::Package>& packages,
            const std::vector<Project::Author>& authors,
            const std::string& link,
            const std::string& license
        ) :
            name(name),
            version(version),
            source_directory(source_directory),
            main_file(main_file),
            output(output),
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
        const std::string main_file;
        const std::string output;
        const std::vector<std::string> additional_files;
        const std::vector<PlatformFiles> platform_files;
        const Version language_version;
        const std::vector<std::string> local_package_paths;
        const std::vector<Package> packages;
        const std::vector<Author> authors;
        const std::string link;
        const std::string license;

        void SaveToFile(const std::string& path);

        static std::unique_ptr<Project> LoadFromFile(const std::string& path);
        static std::unique_ptr<Project> CreateEmpty();
    };

}

#endif