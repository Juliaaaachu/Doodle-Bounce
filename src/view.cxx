#include "view.hxx"
#include "iostream"



// initializing the view (sprites already declared in hxx)
View::View(Model& model)
        : model_(model),
        block_ ({5,10}, ge211::Color::black()),
        test_ ({5,30}, ge211::Color::white())
{}

// drawing the scene for each frame update
void
View::draw(Sprite_set& set)
{
    // set.add_sprite(test_, {, 100}, 2);
    // std::cout<<model_.actual_blocks().size()<<std::endl;
    // drawing all the regular blocks by iterating through
    for (auto block: model_.get_actual_blocks()) {
        // std::cout<<block.x << "," << block.y<< std::endl;

        // set.add_sprite(block_, {block.x, block.y}, 2);
        auto block_pos = block.top_left();
        int block_x_min = block_pos.x;
        int block_x_max = block_pos.x + block.width;
        int block_y_min = block_pos.y;
        int block_y_max = block_pos.y + block.height;

        set.add_sprite(test_, {block_x_min, block_y_min}, 2);
        set.add_sprite(test_, {block_x_max, block_y_min}, 2);


        set.add_sprite(actual_block_, {block.x, block.y}, 1, sprite_scale);
    }

    // drawing all the fragile blocks by iterating through
    for (auto block: model_.get_fragile_blocks()) {
        set.add_sprite(frag_block_, {block.x, block.y}, 1, sprite_scale);;
    }

    // drawing the doodler (yikes i need to figure this out)
    Position dood_pos = model_.get_dooler().get_topleft_pos();
    //
    set.add_sprite(doodler_left_, {int(dood_pos.x), int(dood_pos.y)}, 1,
                   sprite_scale);
    set.add_sprite(bg_, {0, 0}, 0, bg_scale);
    int doodle_xmin = model_.get_dooler().get_position().x - model_
                                                                     .get_dooler().get_dims_().width/2;
    int doodle_xmax = model_.get_dooler().get_position().x + model_
                                                                     .get_dooler().get_dims_().width/2;

    set.add_sprite(block_, {doodle_xmin, int(dood_pos.y)}, 2);
    set.add_sprite(test_, {doodle_xmax, int(dood_pos.y)}, 2);
    // set.add_sprite(doodler_right_, {100, 200}, 0, doodler_scale);
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
