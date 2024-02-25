#ifndef SIZE2_H
#define SIZE2_H

#include "core/math/vector2.h"
#include "core/math/rect2.h"

#include <cmath>

class Size2 {
public:
	Size2();
    Size2(int width, int height);

    // Destructor
    ~Size2();
public:
    int get_width() const;
    int get_height() const;
    Vector2 get_position() const;

    // Setter methods
    void set_width(int width);
    void set_height(int height);
    void set_position(const Vector2& pos);

    // Additional methods
    int get_area_size() const;
    void merge(const Size2& other);
    bool intersects_transformed(const Size2& other, int x, int y) const;
    bool encloses(const Size2& other) const;
    bool has_area() const;
    Size2 intersection(const Size2& other) const;
    void grow_by(double amount);
    void grow_side(int side, double amount);
    bool intersects(const Rect2& rect, bool include_borders) const;
    bool intersects_segment(const Point2& from, const Point2& to, Point2* r_pos = nullptr, Point2* r_normal = nullptr) const;


protected:
	void bind_methods() {}

private:
    int width;
    int height;
    Vector2 position; // Assuming Vector2 represents a 2D position
};


class Point2 {
public:
    // Constructors
    Point2();
    Point2(float x, float y);

    // Destructor
    ~Point2();

    // Getter methods
    float get_x() const;
    float get_y() const;

    // Setter methods
    void set_x(float x);
    void set_y(float y);
    void set_end(const Point2& end);

    // Comparison operators
    bool operator==(const Point2& other) const;
    bool operator!=(const Point2& other) const;

    // New methods
    void shift(float delta_x, float delta_y);
    void bind_shift(uint32_t shift_mask, float delta_amount);
    void grow_individual(float p_left, float p_top, float p_right, float p_bottom);
    void grow_side(Side p_side, float p_amount);
    void grow_side_bind(uint32_t p_side, float p_amount);
    void grow(float p_amount);
    bool has_point(const Point2& point) const;
    bool encloses(const Point2& other_point) const;
    void abs();

protected:
	void _bind_methods() {}
private:
    float x;
    float y;
    Vector2 position;
};





#endif // SIZE2_H
