#pragma once
#include "decimal4.h"
#include "ivec.h"
namespace pllx {
    typedef struct Rectangle {
    public:
        Vector2 Position;
        Vector2 Size;

        inline Rectangle();
        inline Rectangle(Vector2 pos, Vector2 size);
        inline Rectangle(float x, float y, float sX, float sY);

        Rectangle NextCenter();
        Rectangle Scale(float rate);
        Rectangle operator/(float last_center);
        Rectangle operator*(float rescale);
        Rectangle incX(float x);
        Rectangle incY(float y);
        Rectangle incWidth(float x);
        Rectangle incHeight(float y);

        Rectangle& setHeight(float y);
        Rectangle& setWidth(float x);
        Rectangle& setX(float x);
        Rectangle& setY(float y);
        Rectangle& setPos(float x, float y);
        Rectangle& setSize(float x, float y);
        Rectangle& setPos(Vector2 pos);
        Rectangle& setSize(Vector2 size);
        Rectangle& setAbsolute(Vector2 start, Vector2 end);
        Rectangle& setCenter(Vector2 center);
        Rectangle& extend(float px);
        Rectangle& clampHeight(float height);
        Rectangle& clampWidth(float width);

        Vector2 getCenter();
        bool Contains(const Vector2& point) const;

        bool operator!=(const Rectangle& x);
        bool operator==(const Rectangle& x);
        const Rectangle& operator/(double stub);

        static Rectangle fromAbsolute(float x, float y, float sX, float sY);
        static Rectangle multiply(float x, float y, float sX, float sY, float rate);
        static Rectangle multiply(Rectangle& r, float val);
        static Rectangle merge(const Rectangle& a, const Rectangle& b);
        static Rectangle addPos(Rectangle& r, const Vector2& pos);
        static Rectangle subtract(const Rectangle& _left, const Rectangle& _right);
        static Rectangle rect(float x, float y, float width, float height);

        static const Rectangle Empty;
    } Rectangle;

}


pllx::Rectangle _fmakerect(float x, float y, float width, float height);
