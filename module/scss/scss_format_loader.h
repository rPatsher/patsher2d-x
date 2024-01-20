#ifndef SCSS_FORMAT_LOADER_H
#define SCSS_FORMAT_LOADER_H

#include <string>
#include <gtk/gtk.h>

#include "core/object/ref_counted.h"
#include "core/object/m_object.h"

class ScssFormatLoader : public RefCounted {
      CLASS(ScssFormatLoader , RefCounted);
public:
   enum CallError {
    STATUS_LOAD_OK,
    ERROR_FILE_NOT_FOUND,
    ERROR_CSS_LOAD_FAILED
   };
public:
    ScssFormatLoader(const std::string& filePath);
    ~ScssFormatLoader();

    GtkCssProvider* getCssProvider();
    CallError getLastError() const;
    
    void bind_methods();

private:
    std::string filePath;
    GtkCssProvider* cssProvider;
    CallError lastError;
};

#endif // SCSS_FORMAT_LOADER_H
