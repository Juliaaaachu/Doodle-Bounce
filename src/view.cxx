#include "view.hxx"
#include "iostream"



// initializing the view (sprites already declared in hxx)
View::View(Model& model)
        : model_(model)
{}

// drawing the scene for each frame update
void
View::draw(Sprite_set& set)
{
    // std::cout<<model_.actual_blocks().size()<<std::endl;

    // drawing all the regular blocks by iterating through
    for (auto block: model_.get_actual_blocks()) {
        // std::cout<<block.x << "," << block.y<< std::endl;

        set.add_sprite(actual_block_, {block.x, block.y}, 0, block_scale);
    }

    // drawing all the fragile blocks by iterating through
    for (auto block: model_.get_fragile_blocks()) {
        set.add_sprite(frag_block_, {block.x, block.y}, 0, block_scale);;
    }

    // drawing the doodler (yikes i need to figure this out)
    Position dood_pos = model_.get_dooler().get_topleft_pos();
    //
    set.add_sprite(doodler_left_, {int(dood_pos.x), int(dood_pos.y)}, 0,
                   doodler_scale);

    // set.add_sprite(doodler_right_, {100, 200}, 0, doodler_scale);
}

// creating the initial window dimensions
View::Dimensions
View::initial_window_dimensions() const
{
    return {300,600};
}

