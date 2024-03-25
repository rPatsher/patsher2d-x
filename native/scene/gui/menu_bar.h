#ifndef MENU_BAR_H
#define MENU_BAR_H

#include "core/templates/vector.h"
#include "core/string/ustring.h"
#include "core/typedefs.h"
#include "core/object/ref_counted.h"
#include "core/object/m_object.h"
#include "scene/gui/control.h"

#include <string>
#include <vector>

class MenuBar : public Control { 
    CLASS(MenuBar , Control);

public:
    struct MenuItem {
        String title;
        String tooltip;
        int* action;
        bool disabled;
        bool hidden;
        Vector<MenuItem> menu_cache;
    };

    struct ThemeCache {
        int menuTextSize;
        int buttonTextAlignment;
        int buttonTextPadding;
        int buttonPressedTextAlignment;
        int buttonPressedTextPadding;
        int buttonNormalMirroredTextAlignment;
        int buttonNormalMirroredTextPadding;
        int buttonNormalTextAlignment;
        int buttonNormalTextPadding;
    };

public:
	void set_menu_title(int menuIndex, const std::string& title);
    std::string get_menu_title(int menuIndex);

    void set_menu_tooltip(int menuIndex, const std::string& tooltip);
    std::string get_menu_tooltip(int menuIndex);

    void set_menu_disabled(int menuIndex, bool disabled);
    bool get_menu_disabled(int menuIndex);

    void set_menu_hidden(int menuIndex, bool hidden);
    bool get_menu_hidden(int menuIndex);

    void Draw();

    // Add methods to set and get theme properties
    void set_theme_menu_text_size(int size);
    int get_theme_menu_text_size() const;

    void set_theme_button_text_alignment(int alignment);
    int get_theme_button_text_alignment() const;

    void set_theme_button_text_padding(int padding);
    int get_theme_button_text_padding() const;

    void set_theme_button_pressed_text_alignment(int alignment);
    int get_theme_button_pressed_text_alignment() const;

    void set_theme_button_pressed_text_padding(int padding);
    int get_theme_button_pressed_text_padding() const;

    void set_theme_button_normal_mirrored_text_alignment(int alignment);
    int get_theme_button_normal_mirrored_text_alignment() const;

    void set_theme_button_normal_mirrored_text_padding(int padding);
    int get_theme_button_normal_mirrored_text_padding() const;

    void set_theme_button_normal_text_alignment(int alignment);
    int get_theme_button_normal_text_alignment() const;

    void set_theme_button_normal_text_padding(int padding);
    int get_theme_button_normal_text_padding() const;

    // Popup methods
    bool get_menu_popup() const;
    void open_popup(int index, bool focusItem = false);

    ~MenuBar();
private:
    Rectangle menu_rect;
    Vector<MenuItem> menu;
    ThemeCache theme;
    bool menuPopup;

    // Popup variables
    bool popupActive;
    int popupIndex;
    int popupSelected;

protected:
    void _bind_methods() {}


};


#endif
