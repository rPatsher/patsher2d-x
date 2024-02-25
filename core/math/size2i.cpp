#include "size2i.h"



// Constructors
Size2::Size2() : width(0), height(0), position(Vector2()) {}

Size2::Size2(int width, int height) : width(width), height(height), position(Vector2()) {}

// Destructor
Size2::~Size2() {}

// Getter methods
int Size2::get_width() const {
    return width;
}

int Size2::get_height() const {
    return height;
}

Vector2 Size2::get_position() const {
    return position;
}

// Setter methods
void Size2::set_width(int width) {
    this->width = width;
}

void Size2::set_height(int height) {
    this->height = height;
}

void Size2::set_position(const Vector2& pos) {
    position = pos;
}

// Additional methods
int Size2::get_area_size() const {
    return width * height;
}

void Size2::merge(const Size2& other) {
    // Merge by taking the maximum width and height
    width = std::max(width, other.get_width);
    height = std::max(height, other.get_height());
}

bool Size2::intersects_transformed(const Size2& other, int x, int y) const {
    // Check if the transformed rectangle intersects with the current rectangle
    int transformedX = x;
    int transformedY = y;

    int transformedWidth = other.get_width();
    int transformedHeight = other.get_height();

    return (transformedX < (width + x) &&
            (transformedX + transformedWidth) > x &&
            transformedY < (height + y) &&
            (transformedY + transformedHeight) > y);
}

bool Size2::encloses(const Size2& other) const {
    // Check if the current rectangle completely encloses the other rectangle
    return (other.get_width() <= width && other.get_height() <= height);
}

bool Size2::has_area() const {
    // Check if the size has a positive area
    return (width > 0 && height > 0);
}

Size2 Size2::intersection(const Size2& other) const {
    // Calculate the intersection of two rectangles
    int intersectedWidth = std::min(width, other.get_width());
    int intersectedHeight = std::min(height, other.get_height());

    return Size2(intersectedWidth, intersectedHeight);
}

void Size2::grow_by(double amount) {
    // Increase the width and height by the specified amount
    width += static_cast<int>(amount);
    height += static_cast<int>(amount);
}

void Size2::grow_side(int side, double amount) {
    // Increase the specified side by the specified amount
    if (side == 0) { // Grow width
        width += static_cast<int>(amount);
    } else if (side == 1) { // Grow height
        height += static_cast<int>(amount);
    }
}

bool Size2::intersects(const Rect2& rect, bool include_borders) const {
    // Check if the current rectangle intersects with the given rectangle
    int x = position.x;
    int y = position.y;

    int rectX = rect.position.x;
    int rectY = rect.position.y;
    int rectWidth = rect.size.get_width();
    int rectHeight = rect.size.get_height();

    if (include_borders) {
        return (x < (rectX + rectWidth) &&
                (x + width) > rectX &&
                y < (rectY + rectHeight) &&
                (y + height) > rectY);
    } else {
        return (x < rectX + rectWidth &&
                (x + width) > rectX &&
                y < rectY + rectHeight &&
                (y + height) > rectY);
    }
}

bool Size2::intersects_segment(const Point2& from, const Point2& to, Point2* r_pos, Point2* r_normal) const {
    int x = position.x;
    int y = position.y;

    int rectRight = x + width;
    int rectBottom = y + height;

    // Check if the segment is completely outside the rectangle
    if (to.x < x && from.x < x)
        return false;
    if (to.x > rectRight && from.x > rectRight)
        return false;
    if (to.y < y && from.y < y)
        return false;
    if (to.y > rectBottom && from.y > rectBottom)
        return false;

    // Check if the segment starts inside the rectangle
    if (from.x >= x && from.x <= rectRight && from.y >= y && from.y <= rectBottom) {
        if (r_pos) {
            *r_pos = from;
        }
        return true;
    }

    // Check if the segment intersects with the left edge
    if (from.x < x && to.x >= x) {
        float t = (x - from.x) / (to.x - from.x);
        float yIntersect = from.y + t * (to.y - from.y);

        if (yIntersect >= y && yIntersect <= rectBottom) {
            if (r_pos) {
                r_pos->x = x;
                r_pos->y = yIntersect;
            }
            if (r_normal) {
                r_normal->x = -1.0f;
                r_normal->y = 0.0f;
            }
            return true;
        }
    }
    // If no intersection is found
    return false;
}

// Comparison operators
bool Size2::operator==(const Size2& other) const {
    return (width == other.width && height == other.height && position == other.position);
}

bool Size2::operator!=(const Size2& other) const {
    return !(*this == other);
}

void Size2::grow_individual(int p_left, int p_top, int p_right, int p_bottom) {
    // Grow each side individually
    width += p_left + p_right;
    height += p_top + p_bottom;
}

void Size2::grow_side_bind(uint32_t p_side, int p_amount) {
    // Grow a specific side by the specified amount
    if (p_side & 0x01)  {// Grow left
        width += p_amount;
    }
    if (p_side & 0x02)  { 
        height += p_amount;
    } 
    
}


#include <cmath>

// Constructors
Point2::Point2() : x(0.0f), y(0.0f) {}

Point2::Point2(float x, float y) : x(x), y(y) {}

// Destructor
Point2::~Point2() {}

// Getter methods
float Point2::getX() const {
    return x;
}

float Point2::getY() const {
    return y;
}

// Setter methods
void Point2::setX(float x) {
    this->x = x;
}

void Point2::setY(float y) {
    this->y = y;
}

void Point2::set_end(const Point2& end) {
    // Set the end point based on another point
    x = end.x;
    y = end.y;
}

// Comparison operators
bool Point2::operator==(const Point2& other) const {
    return (x == other.x && y == other.y);
}

bool Point2::operator!=(const Point2& other) const {
    return !(*this == other);
}

// New methods
void Point2::shift(float delta_x, float delta_y) {
    // Shift the point by the specified amounts
    x += delta_x;
    y += delta_y;
}

void Point2::bind_shift(uint32_t shift_mask, float delta_amount) {
    // Shift the point based on the specified bitmask
    if (shift_mask & 0x01) // Shift along x-axis
        x += delta_amount;
    if (shift_mask & 0x02) // Shift along y-axis
        y += delta_amount;
}

void Point2::grow_individual(float p_left, float p_top, float p_right, float p_bottom) {
    // Grow each side individually
    x += p_left + p_right;
    y += p_top + p_bottom;
}

void Point2::grow_side(Side p_side, float p_amount) {
    // Grow a specific side by the specified amount
    switch (p_side) {
        case LEFT:
            x -= p_amount;
            break;
        case TOP:
            y -= p_amount;
            break;
        case RIGHT:
            x += p_amount;
            break;
        case BOTTOM:
            y += p_amount;
            break;
        // You can add more cases for other sides if needed
    }
}

void Point2::grow_side_bind(uint32_t p_side, float p_amount) {
    // Grow a specific side by the specified amount
    if (p_side & LEFT)
        x -= p_amount;
    if (p_side & TOP)
        y -= p_amount;
    if (p_side & RIGHT)
        x += p_amount;
    if (p_side & BOTTOM)
        y += p_amount;
}

void Point2::grow(float p_amount) {
    // Grow the point by the specified amount in both x and y directions
    x += p_amount;
    y += p_amount;
}

bool Point2::has_point(const Point2& point) const {
    // Check if the point matches the current point
    return (*this == point);
}

bool Point2::encloses(const Point2& other_point) const {
    // Check if the current point encloses the specified point
    // In this case, a point always encloses itself, so return true
    return (*this == other_point);
}

void Point2::abs() {
    // Calculate the absolute values of x and y
    x = std::fabs(x);
    y = std::fabs(y);
}