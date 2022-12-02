#include "model.hxx"
#include <stdlib.h>
#include<ctime>

// initializing the model
Model::Model()
{
    // set seed to time(0)
    srand(time(0));

    //Initialize 10 blocks on screen
    for (int i = 0 ; i < num_of_blocks; i++) {
        this->actual_blocks_.push_back(add_new_block(i, 60));
    }
    Rectangle initial_block = Rectangle(110,530,60,10);
    this->actual_blocks_.push_back(initial_block);

    // initialize 4 fragile blocks on screen
    for (int j = 0 ; j < num_of_fblocks; j++) {
        this->fragile_blocks_.push_back(add_new_block(j, 100));
    }
}

// function for initializing new blocks
Rectangle
Model::add_new_block(int multipler, int gap){
    // randomize a position within screen dimensions
    Position block_pos = Position(rand() % 140 + 50,
                                  500 - multipler * gap);
    return Rectangle(block_pos.x, block_pos.y,60, 10);
}

// replacing the blocks when the screen re-renders
void
Model::replace_blocks()
{
    //checking if the shifted blocks are off-screen, then re-render
    for (int i = 0; i < num_of_blocks; i++) {
        //if block is off-screen, re-render it on somewhere in screen
        // (instead of removing it in memory)
        if (this->actual_blocks_[i].top_left().y > 580) {
            this->actual_blocks_[i] = Rectangle(rand() % 140 + 50,
                                                -15,
                                                60,
                                                10);
        }
    }
    for (int j = 0; j < num_of_fblocks; j++) {
        if (this->fragile_blocks_[j].top_left().y > 580) {
            this->fragile_blocks_[j] = Rectangle(rand() % 140 + 50,
                                                 -15,
                                                 60,
                                                 10);
        }
    }
}

// move the blocks down when the doodler jumps on a new block
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
        score_ += (-doodler.dy);
        // iterating through fragile blocks
        for (int j = 0; j < num_of_fblocks; j++) {
            doodler.position_.y = 300;
            this->fragile_blocks_[j].y = this->fragile_blocks_[j].y -doodler.dy;
        }
    }
    replace_blocks();
}

// when the doodler hits both actual or fragile blocks, boost or delete frag.
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

// change the frame as time passes
void
Model::on_frame(double dt) {

    //if doodler is dead, don't update anything
    if (this->doodler.doodler_dead()) return;

    if (doodler.live_) {
        //call doodler on frame to let doodler move
        this->doodler.on_frame(1);
        // move the blocks down
        move_blocks_down();
        // checks if any blocks (actual or frag) are hit
        if_hit_block();
    }
}

// moving the doodler left, signify its facing left now
void
Model::moves_doodler_left() {
    if (doodler.live_) {
        this->doodler.position_ = this->doodler.position_.left_by(10);
        doodler.face_left_ = true;
    }
}

// moving the doodler right, signify its facing right now
void
Model::moves_doodler_right() {
    if (doodler.live_) {
        this->doodler.position_ = this->doodler.position_.right_by(10);
        doodler.face_left_ = false;
    }
}

// launches the doodler by making it live
void
Model::launch_doodler(){
    doodler.live_ = true;
}
