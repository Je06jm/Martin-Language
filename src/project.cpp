#include <project.hpp>
#include <nlohmann/json.hpp>
#include <logging.hpp>

#include <fstream>
#include <sstream>

namespace Martin {

    void Project::SaveToFile(const std::string& path) {
        std::ofstream file(path);
        if (!file.is_open()) {
            Error("Could not write project file $\n", path);
            return;
        }

        nlohmann::json j;

        j["name"] = name;
        
        std::string level;
        switch (version.level) {
            case Version::Level::Alpha:
                level = "alpha";
                break;
            
            case Version::Level::Beta:
                level = "beta";
                break;
            
            case Version::Level::ReleaseCandidate:
                level = "release-candidate";
                break;
            
            case Version::Level::Release:
                level = "release";
                break;
        }
        j["project-version"] = {version.major, version.minor, version.patch, level};
        j["source-directory"] = source_directory;
        j["main-file"] = main_file;
        j["output"] = output;
        
        j["additional-files"] = nlohmann::json::array();
        for (auto item : additional_files) {
            j["additional-files"].push_back(item);
        }

        j["additional-files-platforms"] = nlohmann::json::array();
        for (auto item : platform_files) {
            j["additional-files-platforms"][item.name] = nlohmann::json::array();
            for (auto subitem : item.files) {
                j["additional-files-platforms"][item.name].push_back(subitem);
            }
        }

        switch (language_version.level) {
            case Version::Level::Alpha:
                level = "alpha";
                break;
            
            case Version::Level::Beta:
                level = "beta";
                break;
            
            case Version::Level::ReleaseCandidate:
                level = "release-candidate";
                break;
            
            case Version::Level::Release:
                level = "release";
                break;
        }

        j["language-version"] = {language_version.major, language_version.minor, language_version.patch, level};

        j["local-package-paths"] = nlohmann::json::array();
        for (auto item : local_package_paths) {
            j["local-package-paths"].push_back(item);
        }

        j["packages"] = nlohmann::json::array();
        for (auto pkg : packages) {
            switch (pkg.version.level) {
                case Version::Level::Alpha:
                    level = "alpha";
                    break;
                
                case Version::Level::Beta:
                    level = "beta";
                    break;
                
                case Version::Level::ReleaseCandidate:
                    level = "release-candidate";
                    break;
                
                case Version::Level::Release:
                    level = "release";
                    break;
            }

            j["packages"][pkg.name] = {pkg.version.major, pkg.version.minor, pkg.version.patch, level};
        }

        j["authors"] = nlohmann::json::array();
        for (auto auth : authors) {
            j["authors"][auth.name] = auth.email;
        }

        j["link"] = link;
        j["license"] = license;

        std::string data = j.dump(4);
        file << data;
        file.close();
    }

    std::unique_ptr<Project> Project::LoadFromFile(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            Error("Could not find project file $\n", path);
            return nullptr;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        std::string data = buffer.str();

        nlohmann::json j;
        
        try {
            j = nlohmann::json::parse(data);
        } catch (...) {
            Fatal("Could not parse project file $\n", path);
        }

        std::string name = "Project";
        Version version;
        std::string source_directory = "./";
        std::string main_file = "main.martin";
        std::string output = "Project";
        std::vector<std::string> additional_files;
        std::vector<PlatformFiles> platform_files;
        Version language_version;
        std::vector<std::string> local_package_paths;
        std::vector<Package> packages;
        std::vector<Author> authors;
        std::string link;
        std::string license = "Unknown";

        try {
            if (j.contains("name")) {
                name = j["name"];
            } else {
                Warning("Project has no name\n");
            }
        } catch (...) {
            Fatal("Malformed project name\n");
        }

        try {
            if (j.contains("project-version")) {
                auto items = j["project-version"];
                if (items.size() == 3) {
                    version.major = items[0].get<uint32_t>();
                    version.minor = items[1].get<uint32_t>();
                    version.patch = items[2].get<uint32_t>();
                } else if (items.size() == 4) {
                    version.major = items[0].get<uint32_t>();
                    version.minor = items[1].get<uint32_t>();
                    version.patch = items[2].get<uint32_t>();
                    
                    std::string level = items[3].get<std::string>();
                    if (level == "alpha") {
                        version.level = Version::Level::Alpha;
                    } else if (level == "beta") {
                        version.level = Version::Level::Beta;
                    } else if (level == "release-candidate") {
                        version.level = Version::Level::ReleaseCandidate;
                    } else if (level == "release") {
                        version.level = Version::Level::Release;
                    } else {
                        Fatal("Unknown version level $\n", level);
                    }
                } else {
                    Fatal("Malformed project version\n");
                }
            } else {
                Warning("Project has no project version\n");
            }
        } catch (...) {
            Fatal("Malformed project version\n");
        }

        try {
            if (j.contains("source-directory")) {
                source_directory = j["source-directory"];
            } else {
                Warning("Project has no source directory\n");
            }
        } catch (...) {
            Fatal("Malformed project source directory\n");
        }

        try {
            if (j.contains("main-file")) {
                main_file = j["main-file"];
            } else {
                Warning("Project has no main file\n");
            }
        } catch (...) {
            Fatal("Malformed project main file\n");
        }

        try {
            if (j.contains("output")) {
                output = j["output"];
            } else {
                Warning("Project has no output\n");
            }
        } catch (...) {
            Fatal("Malformed project output\n");
        }

        try {
            if (j.contains("additional-files")) {
                auto items = j["additional-files"];
                for (auto item : items) {
                    additional_files.push_back(item.get<std::string>());
                }
            }
        } catch (...) {
            Fatal("Malformed project additional files\n");
        }

        try {
            if (j.contains("additional-files-platforms")) {
                auto items = j["additional-files-platforms"];
                for (auto [name, files] : items.items()) {
                    std::vector<std::string> fls;

                    for (auto file_name : files) {
                        fls.push_back(file_name.get<std::string>());
                    }

                    PlatformFiles plt {
                        name,
                        fls
                    };

                    platform_files.push_back(plt);
                }
            }
        } catch (...) {
            Fatal("Malformed project additional files platforms\n");
        }

        try {
            if (j.contains("language-version")) {
                auto items = j["language-version"];
                if (items.size() == 3) {
                    language_version.major = items[0].get<uint32_t>();
                    language_version.minor = items[1].get<uint32_t>();
                    language_version.patch = items[2].get<uint32_t>();
                } else if (items.size() == 4) {
                    language_version.major = items[0].get<uint32_t>();
                    language_version.minor = items[1].get<uint32_t>();
                    language_version.patch = items[2].get<uint32_t>();
                    
                    std::string level = items[3].get<std::string>();
                    if (level == "alpha") {
                        language_version.level = Version::Level::Alpha;
                    } else if (level == "beta") {
                        language_version.level = Version::Level::Beta;
                    } else if (level == "release-candidate") {
                        language_version.level = Version::Level::ReleaseCandidate;
                    } else if (level == "release") {
                        language_version.level = Version::Level::Release;
                    } else {
                        Fatal("Unknown language version level $\n", level);
                    }
                } else {
                    Fatal("Malformed language version\n");
                }
            } else {
                Warning("Project has no language version\n");
            }
        } catch (...) {
            Fatal("Malformed project language version\n");
        }

        try {
            if (j.contains("local-package-paths")) {
                auto items = j["local-package-paths"];
                for (auto item : items) {
                    local_package_paths.push_back(item.get<std::string>());
                }
            }
        } catch (...) {
            Fatal("Malformed project local package paths\n");
        }

        try {
            if (j.contains("packages")) {
                auto items = j["packages"];
                for (auto [name, version_list] : items.items()) {
                    Version ver;
                    if (version_list.size() == 3) {
                        ver.major = version_list[0].get<uint32_t>();
                        ver.minor = version_list[1].get<uint32_t>();
                        ver.patch = version_list[2].get<uint32_t>();
                    } else if (version_list.size() == 4) {
                        ver.major = version_list[0].get<uint32_t>();
                        ver.minor = version_list[1].get<uint32_t>();
                        ver.patch = version_list[2].get<uint32_t>();
                        
                        std::string level = version_list[3].get<std::string>();
                        if (level == "alpha") {
                            ver.level = Version::Level::Alpha;
                        } else if (level == "beta") {
                            ver.level = Version::Level::Beta;
                        } else if (level == "release-candidate") {
                            ver.level = Version::Level::ReleaseCandidate;
                        } else if (level == "release") {
                            ver.level = Version::Level::Release;
                        } else {
                            Fatal("Unknown package $ version level $\n", name, level);
                        }
                    } else {
                        Fatal("Malformed package $ version\n", name);
                    }
                    Package pkg {
                        name,
                        ver
                    };
                    packages.push_back(pkg);
                }
            }
        } catch (...) {
            Fatal("Malformed project packages\n");
        }

        try {
            if (j.contains("authors")) {
                auto items = j["authors"];
                for (auto [name, email] : items.items()) {
                    Author auth {
                        name,
                        email.get<std::string>()
                    };
                    authors.push_back(auth);
                }
            }
        } catch (...) {
            Fatal("Malformed project authors\n");
        }

        try {
            if (j.contains("link")) {
                link = j["link"];
            }
        } catch (...) {
            Fatal("Malformed project link\n");
        }

        try {
            if (j.contains("license")) {
                license = j["license"];
            } else {
                Warning("Project has no licence\n");
            }
        } catch (...) {
            Fatal("Malformed project license\n");
        }

        auto project = std::unique_ptr<Project>(new Project(
            name,
            version,
            source_directory,
            main_file,
            output,
            additional_files,
            platform_files,
            language_version,
            local_package_paths,
            packages,
            authors,
            link,
            license
        ));

        return project;
    }

    std::unique_ptr<Project> Project::CreateEmpty() {
        std::string name = "Project";
        Version version;
        std::string source_directory = "./";
        std::string main_file = "main.martin";
        std::string output = "Project";
        std::vector<std::string> additional_files;
        std::vector<PlatformFiles> platform_files;
        Version language_version;
        std::vector<std::string> local_package_paths;
        std::vector<Package> packages;
        std::vector<Author> authors;
        std::string link;
        std::string license = "Unknown";

        auto project = std::unique_ptr<Project>(new Project(
            name,
            version,
            source_directory,
            main_file,
            output,
            additional_files,
            platform_files,
            language_version,
            local_package_paths,
            packages,
            authors,
            link,
            license
        ));

        return project;
    }

}