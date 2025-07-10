#include "rectangle.h"
#include "math.h"
namespace pllx {
    const Rectangle Rectangle::Empty{ {0, 0}, {0, 0} };


    Rectangle::Rectangle(Vector2 pos, Vector2 size) : Position(pos), Size(size) {}
    Rectangle::Rectangle(float x, float y, float sX, float sY) : Position(x, y), Size(sX, sY) {}
    Rectangle::Rectangle() : Position(0, 0), Size(0, 0) {}

    Rectangle _fmakerect(float x, float y, float width, float height) {
        return { {x, y}, {width, height} };
    }

    Rectangle Rectangle::NextCenter() {
        return Rectangle({ Position.x + (Size.x / 2), Position.y }, Size);
    }

    Rectangle Rectangle::Scale(float rate) {
        return Rectangle({ Position.x, Position.y }, { Size.x * rate, Size.y * rate });
    }

    Rectangle Rectangle::operator/(float last_center) {
        return Rectangle({ Position.x - (Size.x / last_center), Position.y }, Size);
    }

    Rectangle Rectangle::operator*(float rescale) {
        return Scale(rescale);
    }

    Rectangle Rectangle::incX(float x) {
        return Rectangle({ Position.x + x, Position.y }, Size);
    }

    Rectangle Rectangle::incY(float y) {
        return Rectangle({ Position.x, Position.y + y }, Size);
    }

    Rectangle Rectangle::incWidth(float x) {
        return Rectangle({ Position.x, Position.y }, { Size.x + x, Size.y });
    }

    Rectangle Rectangle::incHeight(float y) {
        return Rectangle({ Position.x, Position.y }, { Size.x , Size.y + y });
    }

    Rectangle& Rectangle::setHeight(float y) {
        Size.y = y;
        return *this;
    }

    Rectangle& Rectangle::setWidth(float x) {
        Size.x = x;
        return *this;
    }

    Rectangle& Rectangle::setX(float x) {
        Position.x = x;
        return *this;
    }

    Rectangle& Rectangle::setY(float y) {
        Position.y = y;
        return *this;
    }

    Rectangle& Rectangle::setPos(float x, float y) {
        Position.x = x;
        Position.y = y;
        return *this;
    }

    Rectangle& Rectangle::setSize(float x, float y) {
        Size.x = x;
        Size.y = y;
        return *this;
    }

    Rectangle& Rectangle::setPos(Vector2 pos) {
        Position = pos;
        return *this;
    }

    Rectangle& Rectangle::setSize(Vector2 size) {
        Size = size;
        return *this;
    }

    Rectangle& Rectangle::setAbsolute(Vector2 start, Vector2 end) {
        Position = start;
        Size = { end.x - start.x, end.y - start.y };
        return *this;
    }

    Rectangle& Rectangle::setCenter(Vector2 center) {
        Position = { center.x - (Size.x / 2), center.y - (Size.y / 2) };
        return *this;
    }

    Rectangle& Rectangle::extend(float px) {
        Position.x -= px;
        Position.y -= px;
        Size.x += px * 2;
        Size.y += px * 2;
        return *this;
    }

    Rectangle& Rectangle::clampHeight(float height) {
        Size.y = pllx::math::min(Size.y, height);
        return *this;
    }

    Rectangle& Rectangle::clampWidth(float width) {
        Size.x = pllx::math::min(Size.y, width); // Nota: ¿debería ser Size.x?
        return *this;
    }

    Vector2 Rectangle::getCenter() {
        return { Position.x + (Size.x / 2), Position.y + (Size.y / 2) };
    }

    bool Rectangle::Contains(const Vector2& point) const {
        return (point.x >= Position.x && point.x <= Position.x + Size.x &&
            point.y >= Position.y && point.y <= Position.y + Size.y);
    }

    Rectangle Rectangle::fromAbsolute(float x, float y, float sX, float sY) {
        return { {x, y}, {sX - x, sY - y} };
    }

    Rectangle Rectangle::multiply(float x, float y, float sX, float sY, float rate) {
        return { {x, y}, {sX * rate, sY * rate} };
    }

    Rectangle Rectangle::multiply(Rectangle& r, float val) {
        return {
            {r.Position.x * val, r.Position.y * val},
            {r.Size.x * val, r.Size.y * val}
        };
    }

    Rectangle Rectangle::merge(const Rectangle& a, const Rectangle& b) {
        float eX = pllx::math::min(a.Position.x, b.Position.x);
        float eY = pllx::math::min(a.Position.y, b.Position.y);
        float sX = pllx::math::max(a.Size.x, b.Size.x);
        float sY = pllx::math::max(a.Size.y, b.Size.y);
        return { {eX, eY}, {sX, sY} };
    }

    Rectangle Rectangle::addPos(Rectangle& r, const Vector2& pos) {
        return { r.Position + pos, r.Size };
    }

    Rectangle Rectangle::subtract(const Rectangle& _left, const Rectangle& _right) {
        return {
            { _left.Position.x - _right.Position.x, _left.Position.y - _right.Position.y },
            { _left.Size.x - _right.Size.x, _left.Size.y - _right.Size.y }
        };
    }

    Rectangle Rectangle::rect(float x, float y, float width, float height) {
        return { {x, y}, { width, height } };
    }

    const Rectangle& Rectangle::operator/(double stub) {
        return rect(Position.x / 2.0f, Position.y / 2.0f, Size.x / 2.0f, Size.y / 2.0f);
    }

    bool Rectangle::operator!=(const Rectangle& x) {
        return x.Size.x != Size.x || x.Size.y != Size.y || Position.x != x.Position.x || Position.y != x.Position.y;
    }

    bool Rectangle::operator==(const Rectangle& x) {
        return !(*this != x);
    }
}