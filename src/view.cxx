#include "view.hxx"



// initializing the view (sprites already declared in hxx)
View::View(Model& model)
        : model_(model)
{}

// drawing the scene for each frame update
void
View::draw(Sprite_set& set)
{
    // drawing all the regular blocks by iterating through
    for (auto block : model_.actual_blocks()){
        set.add_sprite(actual_block_, {block.x, block.y}, 0);
    }
    // drawing all the fragile blocks by iterating through
    for (auto block : model_.fragile_blocks()){
        set.add_sprite(frag_block_, {block.x, block.y}, 0);
    }
    // drawing the doodler (yikes i need to figure this out)
    set.add_sprite(doodler_left_, {150, 200}, 0);
    set.add_sprite(doodler_right_, {150, 200}, 0);
}

// creating the initial window dimensions
View::Dimensions
View::initial_window_dimensions() const
{
    return {300,500};
}

