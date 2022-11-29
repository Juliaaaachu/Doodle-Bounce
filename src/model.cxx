#include "model.hxx"
#include <stdlib.h>
#include<ctime>
#include "iostream"


Model::Model()
{
    // set seed to time(0)
    srand(time(0));

    //Initialize 10 blocks on screen
    for (int i = 0 ; i < 10; i++) {
        //assuming screen dim is 300*600
        //TODO: game config file to store all constant
        //height random will be in range 50 - 550
        Position brick_pos = Position(rand() % 250,rand() % 500 + 50 );

        Rectangle block = Rectangle (brick_pos.x,
                                     brick_pos.y,
                                     60,
                                     10);

        this->actual_blocks_.push_back(block);
    }

    for (int i = 0 ; i < 4; i++) {
        //assuming screen dim is 300*600
        //TODO: game config file to store all constant
        //height random will be in range 50 - 550
        Position brick_pos = Position(rand() % 250,rand() % 500 + 50 );

        Rectangle block = Rectangle (brick_pos.x,
                                     brick_pos.y,
                                     60,
                                     10);

        this->fragile_blocks_.push_back(block);
    }



}

void
Model::on_frame(double dt) {

    //if doodler is dead, dont update anything
    if (this->doodler.doodle_dead()) return;


    //call doodler onframe to let doodler move
    this->doodler.on_frame(1);

    //score updates as doodler lives longer
    this->score_ += 1;

    //if jumpblocks return a block (posn)
    Rectangle anchorblock = this->doodler.jump_blocks(this->actual_blocks_);
    if (anchorblock.height != -1) {

        //if we hit a block, bounce backup
        this->doodler.dy = -5;

        int anchor_y = anchorblock.height;


        //assume screen dim height = 600
        //assume we always want jumped block to be 100 pix above screen bottom
        //=> assume lowest block will always be at 500 y
        int dist2anchor = 500 - anchor_y;
        //
        // //increase y posn for all block in list  (moving them down on screen)
        // for (int i = 0; i < 10; i++) {
        //
        //     Rectangle block = this->actual_blocks_[i];
        //     block.x = block.top_left().down_by(dist2anchor).x;
        //     block.y = block.top_left().down_by(dist2anchor).y;
        //
        //     //if block is out of screen (within a threshold)
        //     //re-render it on somewhere in screen (instead of removing it in
        //     // memory)
        //     if (block.top_left().y > 550) {
        //         Rectangle new_block = Rectangle(rand() % 300,
        //                                         rand() % dist2anchor,
        //                                         60,
        //                                         10);
        //
        //         this->actual_blocks_[i] = new_block;
        //     }
        // }

    }
    //fragile block disappear once being hit 
    Rectangle fragilehit = this->doodler.jump_blocks(this->fragile_blocks_);
    if (fragilehit.height != -1) {
        fragilehit = this->fragile_blocks_.back();
        this->fragile_blocks_.pop_back();
    }
}



ListofRect
Model::get_actual_blocks()
{
    return actual_blocks_;
}

ListofRect
Model::get_fragile_blocks(){
    return fragile_blocks_;
}

// launching doodler at game start (going up, neg height velocity)
void
Model::launch() {
    this->doodler.velocity_.height = -10;
}

// moving the doodler left, signify its facing left now
void
Model::moves_doodle_left() {
    this->doodler.position_ = this->doodler.position_.left_by(10);
}

// moving the doodler right, signify its facing right now
void
Model::moves_doodle_right() {
    this->doodler.position_ = this->doodler.position_.right_by(10);
}

