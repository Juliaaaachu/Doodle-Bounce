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

    // creating window title
    std::string initial_window_title() const;

private:
    // view can access but not edit model
    Model& model_;

    // creating sprites for the game
    ge211::sprites::Rectangle_sprite block_;
    ge211::sprites::Rectangle_sprite test_;
    ge211::sprites::Rectangle_sprite blah_;
    ImageSprite doodler_right_ {"doodler_right.png"};
    ImageSprite doodler_left_ {"doodler_left.png"};
    ImageSprite actual_block_ {"actual_block.png"};
    ImageSprite frag_block_ {"frag_block.png"};
    ImageSprite bg_ {"bg.png"};


    // used to scale the imported images correctly
    ge211::Transform sprite_scale = ge211::Transform{}.set_scale(0.1);
    ge211::Transform bg_scale = ge211::Transform{}.set_scale(0.2);

};
