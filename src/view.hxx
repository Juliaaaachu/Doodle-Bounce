#pragma once

#include "model.hxx"


class View
{
public:

    using ImageSprite = ge211::Image_sprite;
    using Dimensions = ge211::Dims<int>;
    using Sprite_set = ge211::Sprite_set;

    explicit View(Model& model);

    // draw functions takes in sprite set
    void draw(Sprite_set& set);

    void draw_doodler(Sprite_set& set);

    void draw_blocks(Sprite_set& set);

    // creating the window for the game
    Dimensions initial_window_dimensions() const;

    // creating window title
    std::string initial_window_title() const;

private:
    // view can access but not edit model
    Model& model_;

    // creating var. for score sprites/font
    ge211::Font sans30_{"font.ttf",25};
    ge211::Text_sprite score_sprite_;

    // importing in the sprites for the doodler
    ImageSprite doodler_right_ {"doodler_right.png"};
    ImageSprite doodler_left_ {"doodler_left.png"};
    ImageSprite doodler_left_squat {"doodler_left_squat.png"};

    // importing the sprites for the blocks
    ImageSprite actual_block_ {"actual_block.png"};
    ImageSprite frag_block_ {"frag_block.png"};

    // importing background and game over
    ImageSprite bg_ {"bg.png"};
    ImageSprite game_over_ {"game_over.png"};

    // used to scale the imported images correctly
    ge211::Transform sprite_scale = ge211::Transform{}.set_scale(0.1);
    ge211::Transform bg_scale = ge211::Transform{}.set_scale(0.2);
    ge211::Transform game_over_scale = ge211::Transform{}.set_scale(0.05);

};
