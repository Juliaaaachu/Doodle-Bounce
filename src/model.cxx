#include "model.hxx"
#include <stdlib.h>
#include<ctime>

// initializing the model
Model::Model()
{
    // set seed to time(0)
    srand(time(0));

    //Initialize 10 blocks on screen
    for (int i = 0; i < num_of_blocks; i++) {
        // Rectangle new_block =  Rectangle(rand() % 200 + 50,
        //                                  rand() % 500 + 50,
        //                                  60,
        //                                  10);
        this->actual_blocks_.push_back(add_new_block());
    }
    Rectangle initial_block = Rectangle(110,530,60,10);
    this->actual_blocks_.push_back(initial_block);

    for (int i = 0 ; i < 4; i++) {
        // Rectangle new_block =  Rectangle(rand() % 200 + 50,
        //                                  rand() % 500 + 50,
        //                                  60,
        //                                  10);
        this->fragile_blocks_.push_back(add_new_block());
    }

}

Rectangle
Model::add_new_block()
{
    // randomize a position within screen dimensions
    Position block_pos = Position(rand() % 200 + 50,
                                  rand() % 500 + 50);

    while (!blocks_no_overlap(block_pos))
    {
        block_pos = Position(rand() % 200 + 50,
                             rand() % 500 + 50);
    }
    // if all conditions pass, return block
    return Rectangle(block_pos.x, block_pos.y,60, 10);
}

bool
Model::blocks_no_overlap(Position new_block_pos)
{
    bool holder;

    if (actual_blocks_.empty()){
        return true;
    }

    for (auto block: get_all_blocks()) {
        // blocks shouldn't be within 30px to right or left of orig block
        Position block_range_x = {block.x - 90, block.x + 90};
        // blocks shouldn't be within 30px above or below of orig block
        Position block_range_y_min = {block.y - 40, block.y + 40};
        // blocks shouldn't be more than 100px above orig block
        Position block_range_y_max = {block.y - 80, block.y + 80};

        // checking through the ranges, first x, then y min and max
        if (new_block_pos.x < block_range_x.x ||
            new_block_pos.x > block_range_x.x) {
            if (new_block_pos.y < block_range_y_min.x ||
                new_block_pos.y > block_range_y_min.y){
                if (new_block_pos.y < block_range_y_max.x ||
                        new_block_pos.y > block_range_y_max.y){
                    holder = true;
                }
                else {holder = false;}
            }
            else {holder = false;}
        }
        else{holder = false;}
    }
    return holder;
}

void
Model::replace_blocks()
{
    //checking if the shifted blocks are off-screen, then re-render
    for (int i = 0; i < num_of_blocks; i++) {
        //if block is off-screen, re-render it on somewhere in screen
        // (instead of removing it in memory)
        if (this->actual_blocks_[i].top_left().y > 580) {
            this->actual_blocks_[i] = Rectangle(rand() % 200,
                                                -15,
                                                60,
                                                10);
        }
    }
    for (int j = 0; j < num_of_fblocks; j++) {
        if (this->fragile_blocks_[j].top_left().y > 580) {
            this->fragile_blocks_[j] = Rectangle(rand() % 200,
                                                 -15,
                                                 60,
                                                 10);
        }
    }
}

void
Model::move_blocks_down(){
    //moves blocks down as if doodler moves above center of screen
    if (doodler.position_.y < 300) {
        // iterating through actual blocks
        for (int i = 0; i < num_of_blocks + 1; i++) {
            // keeping doodler max height at center of screen
            doodler.position_.y = 300;
            // moving the old block downwards
            this->actual_blocks_[i].y = this->actual_blocks_[i].y - doodler.dy;
        }
        // iterating through fragile blocks
        for (int j = 0; j < num_of_fblocks; j++) {
            doodler.position_.y = 300;
            this->fragile_blocks_[j].y = this->fragile_blocks_[j].y -doodler.dy;
        }
    }
    replace_blocks();
}

void
Model::if_hit_block()
{
    // first moving doodler up if it jumps on actual block
    // create a new var to check if jumped on block exists
    Rectangle actualhit = this->doodler.jumped_on_block(this->actual_blocks_);
    // if the block actually exists
    if (actualhit.height != -1) {
        //if we hit a block, bounce backup with a boost
        this->doodler.dy = -8;
    }

    //fragile block disappears once hit
    // create a new var representing the hit frag block
    Rectangle fragilehit = this->doodler.jumped_on_block(this->fragile_blocks_);
    // iterate through all fragile blocks to replace the hit one
    for (int k = 0; k < num_of_fblocks; k++) {
        if (this->fragile_blocks_[k] == fragilehit) {
            Rectangle new_block = Rectangle(rand() % 200,
                                            -15,
                                            60,
                                            10);
            this->fragile_blocks_[k] = new_block;
        }
    }
}

void
Model::on_frame(double dt) {

    //if doodler is dead, don't update anything
    if (this->doodler.doodler_dead()) return;

    if (doodler.live) {
        //call doodler on frame to let doodler move
        this->doodler.on_frame(1);
        //score updates as doodler lives longer
        this->score_ += 1;
        // move the blocks down
        move_blocks_down();
        // checks if any blocks (actual or frag) are hit
        if_hit_block();
    }
}


// moving the doodler left, signify its facing left now
void
Model::moves_doodler_left() {
    this->doodler.position_ = this->doodler.position_.left_by(10);
    doodler.face_left_ = true;
}

// moving the doodler right, signify its facing right now
void
Model::moves_doodler_right() {
    this->doodler.position_ = this->doodler.position_.right_by(10);
    doodler.face_left_ = false;
}

// launches the doodler by making it live
void
Model::launch_doodler(){
    doodler.live = true;
}


ListofRect
Model::get_all_blocks(){
    ListofRect all_blocks = get_actual_blocks();
    for (auto block : fragile_blocks_){
        all_blocks.push_back(block);
    }
    return all_blocks;
}