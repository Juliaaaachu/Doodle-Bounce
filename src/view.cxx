#include "view.hxx"
#include "iostream"



// initializing the view (sprites already declared in hxx)
View::View(Model& model)
        : model_(model),
        score_sprite_(std::to_string(model_.get_score()), sans30_)
{}

// drawing the scene for each frame update
void
View::draw(Sprite_set& set)
{
    //prints out score on the top left screen, keep track of updated value
    ge211::Text_sprite::Builder score_builder(sans30_);
    score_builder.color(ge211::Color::medium_red()) << model_.get_score();
    score_sprite_.reconfigure(score_builder);
    set.add_sprite(score_sprite_, {20, 24},3);

    // if the doodler is dead, show game over
    if (model_.get_doodler().doodler_dead()){
        set.add_sprite(game_over_, {40, 250},
                       5, game_over_scale);
    }
    // otherwise draw the screen as usual
    else{
        draw_doodler(set);
        draw_blocks(set);
    }
    // draw the background
    set.add_sprite(bg_, {0, 0}, 0, bg_scale);
}

// drawing the blocks
void
View::draw_blocks(View::Sprite_set& set){
    // drawing all the actual blocks by iterating through
    for (auto block: model_.get_actual_blocks()) {
        set.add_sprite(actual_block_, {block.x, block.y},
                                                1, sprite_scale);
    }
    // drawing all the fragile blocks by iterating through
    for (auto block: model_.get_fragile_blocks()) {
        set.add_sprite(frag_block_, {block.x, block.y},
                                            1, sprite_scale);;
    }
}

// drawing the doodler
void
View::draw_doodler(View::Sprite_set& set){
    // drawing the doodler
    Position dood_pos = model_.get_doodler().get_topleft_pos();
    // if the doodler is facing left, add sprites
    if (model_.get_doodler().get_face_left()) {
        // if the game just started, the doodle is squatting
        if (!model_.get_doodler().get_live()){
            set.add_sprite(doodler_left_squat,
                           {int(dood_pos.x),int(dood_pos.y)},
                           3,sprite_scale);
        }
        // otherwise, the doodler is standing during the game
        else {
            set.add_sprite(doodler_left_,
                           {int(dood_pos.x),int(dood_pos.y)},
                           3,sprite_scale);
        }
    }
    // draw the doodler facing right
    else {
        set.add_sprite(doodler_right_,
                       {int(dood_pos.x),int(dood_pos.y)},
                       3,sprite_scale);
    }
}

// creating the initial window dimensions
View::Dimensions
View::initial_window_dimensions() const
{
    return {300,600};
}

std::string
View::initial_window_title() const
{
    // You can change this if you want:
    return "!!! doodle bounce !!!";
}
