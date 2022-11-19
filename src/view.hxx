#pragma once

#include "model.hxx"

using ImageSprite = ge211::Image_sprite;

class View
{
public:
    explicit View(Model const& model);

    void draw(ge211::Sprite_set& set);

private:
    Model const& model_;

    ImageSprite doodler_;
    ImageSprite block;

};
