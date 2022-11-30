#include "view.hxx"
#include "iostream"
#include <cstring>



// initializing the view (sprites already declared in hxx)
View::View(Model& model)
        : model_(model),
        block_ ({5,10}, ge211::Color::black()),
        test_ ({5,30}, ge211::Color::white()),
        blah_({60,5}, ge211::Color::medium_yellow()),
        score_sprite_(std::to_string(model_.get_score()), sans30_)
{}

// drawing the scene for each frame update
void
View::draw(Sprite_set& set)
{
    //prints out score on the top left screen, keep track of updated value
    ge211::Text_sprite::Builder score_builder(sans30_);
    score_builder.color(ge211::Color::black()) << model_.get_score();
    score_sprite_.reconfigure(score_builder);
    set.add_sprite(score_sprite_, {20, 20});

    for (auto block: model_.get_actual_blocks()) {

        set.add_sprite(actual_block_, {block.x, block.y}, 1, sprite_scale);
    }

    // drawing all the fragile blocks by iterating through
    for (auto block: model_.get_fragile_blocks()) {
        set.add_sprite(frag_block_, {block.x, block.y}, 1, sprite_scale);;
    }

    // drawing the doodler
    Position dood_pos = model_.get_dooler().get_topleft_pos();
    //
    set.add_sprite(doodler_left_, {int(dood_pos.x), int(dood_pos.y)}, 1,
                   sprite_scale);
    set.add_sprite(bg_, {0, 0}, 0, bg_scale);

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
