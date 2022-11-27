#pragma once

#include "model.hxx"


class View
{
public:

    using ImageSprite = ge211::Image_sprite;
    using Dimensions = ge211::Dims<int>;
    using Sprite_set = ge211::Sprite_set;

    explicit View(Model& model);

    // draw func takes in sprite set
    void draw(Sprite_set& set);

    // creating the window for the game
    Dimensions initial_window_dimensions() const;

private:
    // view can access but not edit model
    Model& model_;

    // creating sprites for the game
    ImageSprite doodler_right_ {"doodle_right"};
    ImageSprite doodler_left_ {"doodle_left"};
    ImageSprite actual_block_ {"actual_block"};
    ImageSprite frag_block_ {"frag_block"};

    // used to scale the imported images correctly
    double doodler_scale_ = 1.0;
    double block_scale_ = 1.0;


};
