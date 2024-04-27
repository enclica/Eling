#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include "include/json.hpp" // Make sure to have this include path correct
#include <curl/curl.h>

namespace fs = std::filesystem;
using json = nlohmann::json;
using namespace std;

// Utility functions declaration
void initializeEnvironment(const string& home);
void loadConfiguration(const string& configFile, json& config);
void saveConfiguration(const string& configFile, const json& config);
bool isInstalled(const string& packageName, const json& config);
void downloadAndInstall(const string& packageName);
void installPackage(const string& packageName, json& config);
void uninstallPackage(const string& packageName, json& config);
void updatePackage(const string& packageName, json& config);
void searchPackage(const string& packageName);
void listPackages(const json& config);
void addServer(const string& serverUrl, json& config);
void removeServer(const string& serverUrl, json& config);
void listServers(const json& config);

// Main program entry
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Usage: baton <command> [args]" << endl;
        return 1;
    }

    string home = getenv("HOME") ? getenv("HOME") : "";
    if (home.empty()) {
        cerr << "Error: HOME environment variable not set." << endl;
        return 1;
    }

    string configPath = home + "/.eling/baton.conf";
    json config;
    initializeEnvironment(home);
    loadConfiguration(configPath, config);

    string command = argv[1];
    if (command == "install" && argc > 2) {
        installPackage(argv[2], config);
    } else if (command == "uninstall" && argc > 2) {
        uninstallPackage(argv[2], config);
    } else if (command == "update" && argc > 2) {
        updatePackage(argv[2], config);
    } else if (command == "search" && argc > 2) {
        searchPackage(argv[2]);
    } else if (command == "list") {
        listPackages(config);
    } else if (command == "addserver" && argc > 2) {
        addServer(argv[2], config);
    } else if (command == "removeserver" && argc > 2) {
        removeServer(argv[2], config);
    } else if (command == "listserver") {
        listServers(config);
    } else if (command == "version") {
        cout << "Baton version 0.0.1" << endl;
    
    }else if (command == "help") {
        cout << "Baton package manager\n"
             << "Version 0.0.1 by Enclica Software\n\n"
             << "Usage: baton <command> [args]\n"
             << "Commands:\n"
             << "  install <package>    Install a package\n"
             << "  uninstall <package>  Uninstall a package\n"
             << "  update <package>     Update a package\n"
             << "  search <package>     Search for a package\n"
             << "  list                 List installed packages\n"
             << "  addserver <url>      Add a package server\n"
             << "  removeserver <url>   Remove a package server\n"
             << "  listserver           List all package servers\n"
             << "  version              Print the version of baton\n"
             << "  help                 Print this help message\n";
    } else {
        cerr << "Unknown command or insufficient arguments." << endl;
        return 1;
    }

    saveConfiguration(configPath, config);
    return 0;
}

// Callback function for writing data received by libcurl
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

// Function to download a file using libcurl
bool downloadFile(const std::string& url, const std::string& outputPath) {
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outputPath.c_str(), "wb");
        if (fp == nullptr) {
            std::cerr << "Failed to open file for writing: " << outputPath << std::endl;
            return false;
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return false;
        }
        return true;
    }
    return false;
}

void initializeEnvironment(const string& home) {
    cout << "Checking for necessary directories and files..." << endl;
    string elingDir = home + "/.eling";
    fs::create_directories(elingDir + "/packages"); // Ensures all directories are created

    if (!fs::exists(elingDir + "/baton.conf")) {
        cout << "No configuration file found. Creating one..." << endl;
        json conf = {
            {"packages", json::array()},
            {"version", "0.0.1"},
            {"package_servers", {"https://baton.enclica.com/packages"}}
        };
        ofstream configFile(elingDir + "/baton.conf");
        configFile << conf.dump(4);
        configFile.close();
        cout << "Created configuration file at " << elingDir + "/baton.conf" << endl;
    }
}

void loadConfiguration(const string& configFile, json& config) {
    ifstream file(configFile);
    if (file.is_open()) {
        file >> config;
    } else {
        cerr << "Failed to open configuration file." << endl;
        exit(1);
    }
}

void saveConfiguration(const string& configFile, const json& config) {
    ofstream file(configFile);
    if (file.is_open()) {
        file << config.dump(4);
    } else {
        cerr << "Failed to save configuration file." << endl;
    }
}

bool isInstalled(const string& packageName, const json& config) {
    auto it = find(config["packages"].begin(), config["packages"].end(), packageName);
    return it != config["packages"].end();
}

void downloadAndInstall(const std::string& packageName) {
    std::cout << "Downloading and installing " << packageName << "..." << std::endl;

    

    std::string outputPath = "./eling_packages/" + packageName + ".zip";  // or other appropriate extension based on the package

    //get servers from config
    json config;
    string home = getenv("HOME") ? getenv("HOME") : "";
    string configPath = home + "/.eling/baton.conf";
    loadConfiguration(configPath, config);
    auto servers = config["package_servers"];

    string url;

    // Try to download the package from each server
    bool downloaded = false;
    for (const auto& server : servers) {
        url = server.get<std::string>() + "/" + packageName + ".zip";
        std::cout << "Downloading from " << url << "..." << std::endl;
        if (downloadFile(url, outputPath)) {
            downloaded = true;
            break;
        }
    }

    // Try to download the package
    if (downloadFile(url, outputPath)) {
        std::cout << packageName << " installed successfully." << std::endl;
    } else {
        std::cout << "Failed to download " << packageName << "." << std::endl;
    }
}

void installPackage(const string& packageName, json& config) {
    //create local package directory in the current directory in a eling_packages folder
if (!fs::exists("./eling_packages")) {
    fs::create_directory("./eling_packages");
}

    if (isInstalled(packageName, config)) {
        cout << "Package " << packageName << " is already installed." << endl;
    } else {
        downloadAndInstall(packageName);
        config["packages"].push_back(packageName); // Update the configuration
    }
}

void uninstallPackage(const string& packageName, json& config) {
    auto& packages = config["packages"];
    auto it = find(packages.begin(), packages.end(), packageName);
    if (it != packages.end()) {
        packages.erase(it);
        cout << "Package " << packageName << " has been uninstalled." << endl;
    } else {
        cout << "Package " << packageName << " is not installed." << endl;
    }
}

void updatePackage(const string& packageName, json& config) {
    if (isInstalled(packageName, config)) {
        cout << "Found updates for " << packageName << ", updating..." << endl;
        // Simulate update
        cout << "Package " << packageName << " has been updated." << endl;
    } else {
        cout << "Package " << packageName << " is not installed. Install it first." << endl;
    }
}

void searchPackage(const string& packageName) {
    cout << "Searching for package: " << packageName << endl;
    // Simulate search
    cout << "Package " << packageName << " found on the server." << endl;
}

void listPackages(const json& config) {
    cout << "Listing installed packages:" << endl;
    for (const auto& package : config["packages"]) {
        cout << "- " << package << endl;
    }
}

void removeServer(const string& serverUrl, json& config) {
    auto& servers = config["package_servers"];
    auto it = find(servers.begin(), servers.end(), serverUrl);
    if (it != servers.end()) {
        servers.erase(it);
        cout << "Server " << serverUrl << " removed successfully.\n";
    } else {
        cout << "Server " << serverUrl << " not found.\n";
    }
}


void addServer(const string& serverUrl, json& config) {
    // Check if the server already exists in the configuration
    auto& servers = config["package_servers"];
    if (find(servers.begin(), servers.end(), serverUrl) == servers.end()) {
        servers.push_back(serverUrl);
        cout << "Server " << serverUrl << " added successfully.\n";
    } else {
        cout << "Server " << serverUrl << " already exists.\n";
    }
}

void listServers(const json& config) {
    cout << "Listing all package servers:\n";
    for (const auto& server : config["package_servers"]) {
        cout << "-\033[32m " << server << endl;
    }
}
