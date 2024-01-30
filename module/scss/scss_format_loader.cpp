#include "scss_format_loader.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

ScssFormatLoader::ScssFormatLoader(const std::string& filePath) : filePath(filePath), cssProvider(nullptr), lastError(STATUS_LOAD_OK) {
    cssProvider = gtk_css_provider_new();
    
    // Check if the file exists
    if (fs::exists(filePath)) {
        // Load and apply the CSS from the file
        std::ifstream fileStream(filePath);
        std::string cssContent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());

        if (gtk_css_provider_load_from_data(cssProvider, cssContent.c_str(), -1, nullptr)) {
            lastError = STATUS_LOAD_OK;
        } else {
            lastError = ERROR_CSS_LOAD_FAILED;
            std::cerr << "Error: Failed to load CSS from file - " << filePath << std::endl;
        }
    } else {
        lastError = ERROR_FILE_NOT_FOUND;
        std::cerr << "Error: File not found - " << filePath << std::endl;
    }
}

ScssFormatLoader::~ScssFormatLoader() {
    if (cssProvider) {
        g_object_unref(cssProvider);
    }
}

GtkCssProvider* ScssFormatLoader::get_css_provider() {
    return cssProvider;
}

CallError ScssFormatLoader::get_last_error() const {
    return lastError;
}

void ScssFormatLoader::bind_methods() {
   	Object::bind_method("get_css_provider", &ScssFormatLoader::get_css_provider);
	Object::bind_method("get_last_error", &ScssFormatLoader::get_last_error);
}
