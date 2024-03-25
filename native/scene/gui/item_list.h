#ifndef ITEM_LIST_H
#define ITEM_LIST_H


class ListView {
public:
    enum Mode {
        ICON_MODE_LEFT,
        ICON_MODE_TOP
    };

    enum SelectMode {
        SELECT_SINGLE,
        SELECT_MULTI
    };
public:
    ItemList();
    ~ItemList();
public:
    void update();
    void draw();

    void add_item(const char* itemText);
    void add_icon_item(const char* itemText, Texture2D icon);
    void add_resized_icon_item(const char* itemText, Texture2D icon, int width, int height);
    const char* get_item(int index) const;
    int get_max_scroll() const;
    float get_max_scroll_speed() const;
    void set_icon_size(int width, int height);
    void update_size(int width, int height);

    bool is_item_disabled(int index) const;
    void set_item_disabled(int index, bool disabled);

    void set_item_tooltip_enabled(int index, bool enabled);
    void set_item_tag_icon(int index, std::shared_ptr<Texture2D> tagIcon);

    void set_item_tooltip(int index, const char* tooltip);
    const char* get_item_tooltip(int index) const;

    void set_item_custom_bg_color(int index, const Color& customBgColor);
    void set_item_custom_fg_color(int index, const Color& customFgColor);

    Rectangle get_item_rect(int index, bool expand = true) const;
    void set_item_text(int index, const char* text);

    void set_icon_scale(float scale);

    void set_display_mode(Mode mode);

    void set_select_mode(SelectMode mode);
    bool is_item_selected(int index) const;
    void toggle_item_selected(int index);
protected:

private:
    Rectangle bounds;
    int* scrollIndex;
    int active;
    int maxScroll;
    std::vector<std::pair<const char*, Texture2D>> items;
    std::vector<bool> disabledItems;
    std::vector<bool> tooltipEnabledItems;
    std::vector<std::shared_ptr<Texture2D>> tagIcons;
    std::vector<const char*> tooltips;
    std::vector<Color> customBgColors;
    std::vector<Color> customFgColors;
    float iconScale;
    int iconWidth;
    int iconHeight;
    Mode displayMode;
    SelectMode selectMode;
    std::vector<bool> selectedItems;
};





#endif // 
