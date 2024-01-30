#ifndef RECT2I_H
#define RECT2I_H

#include <cmath>
#include <algorithm>

struct Rect2i {
    int x;
    int y;
    int width;
    int height;

    // Constructors
    Rect2i() : x(0), y(0), width(0), height(0) {}
    Rect2i(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    // Functions to convert between polar and rectangular coordinates
    static Rect2i fromPolar(int r, double theta) {
        return {static_cast<int>(r * std::cos(theta)), static_cast<int>(r * std::sin(theta)), 0, 0};
    }

    std::pair<int, double> toPolar() const {
        int r = static_cast<int>(std::sqrt(x * x + y * y));
        double theta = std::atan2(y, x);
        return {r, theta};
    }

    // Check if a point is enclosed within the rectangle
    bool encloses(int px, int py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }

    // Check if two rectangles intersect
    bool intersects(const Rect2i& other) const {
        return x < other.x + other.width &&
               x + width > other.x &&
               y < other.y + other.height &&
               y + height > other.y;
    }

    // Get the position of the rectangle as a pair of x and y
    std::pair<int, int> get_position() const {
        return {x, y};
    }

    // Get the area of the rectangle
    int get_area() const {
        return width * height;
    }

    // Get the size of the rectangle as a pair of width and height
    std::pair<int, int> get_size() const {
        return {width, height};
    }

    // Merge this rectangle with another, resulting in the smallest rectangle that encloses both
    Rect2i merge(const Rect2i& other) const {
        int minX = std::min(x, other.x);
        int minY = std::min(y, other.y);
        int maxX = std::max(x + width, other.x + other.width);
        int maxY = std::max(y + height, other.y + other.height);
        return {minX, minY, maxX - minX, maxY - minY};
    }

    // Grow the rectangle by a specified amount
    void grow(int amount) {
        x -= amount;
        y -= amount;
        width += 2 * amount;
        height += 2 * amount;
    }

    // Grow the rectangle to a specified size, keeping the center constant
    void expand(int newWidth, int newHeight) {
        x -= (newWidth - width) / 2;
        y -= (newHeight - height) / 2;
        width = newWidth;
        height = newHeight;
    }

    // Expand the rectangle to include a specified point
    void expand_to(int px, int py) {
        if (px < x) {
            width += x - px;
            x = px;
        } else if (px > x + width) {
            width = px - x;
        }

        if (py < y) {
            height += y - py;
            y = py;
        } else if (py > y + height) {
            height = py - y;
        }
    }

    // Set the position of the bottom-right corner of the rectangle
    void set_end(int endX, int endY) {
        width = endX - x;
        height = endY - y;
    }

    // Get the position of the bottom-right corner of the rectangle
    std::pair<int, int> get_end() const {
        return {x + width, y + height};
    }

    // Get the absolute value of the rectangle's coordinates
    Rect2i abs() const {
        return {std::abs(x), std::abs(y), std::abs(width), std::abs(height)};
    }

    // Check if a point is inside the rectangle
    bool has_point(int px, int py) const {
        return px >= x && px <= x + width && py >= y && py <= y + height;
    }

    // Grow a specific side of the rectangle by a specified amount
    void grow_side(int side, int amount) {
        switch (side) {
            case 0: // Left side
                x -= amount;
                width += amount;
                break;
            case 1: // Top side
                y -= amount;
                height += amount;
                break;
            case 2: // Right side
                width += amount;
                break;
            case 3: // Bottom side
                height += amount;
                break;
        }
    }

    // Operator overloads

    // Equality check
    bool operator==(const Rect2i& other) const {
        return x == other.x && y == other.y && width == other.width && height == other.height;
    }

    // Assignment operator
    Rect2i& operator=(const Rect2i& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            width = other.width;
            height = other.height;
        }
        return *this;
    }
};

#endif // RECT2I_H
