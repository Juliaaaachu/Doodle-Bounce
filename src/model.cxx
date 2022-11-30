#include "model.hxx"
#include <stdlib.h>
#include<ctime>

Model::Model()
{
    // set seed to time(0)
    srand(time(0));

    //Initialize 10 blocks on screen
    for (int i = 0 ; i < num_of_blocks; i++) {
        //assuming screen dim is 300*600
        //TODO: game config file to store all constant
        //height random will be in range 50 - 550
        Position brick_pos = Position(rand() % 300,rand() % 500 + 100 );

        Rectangle block = Rectangle (brick_pos.x,
                                     brick_pos.y,
                                     60,
                                     10);

        this->actual_blocks_.push_back(block);
    }

    for (int i = 0 ; i < 4; i++) {
        //assuming screen dim is 300*600
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

    //block continula go down
    if (doodler.position_.y < 300) {
        for (int i = 0; i < num_of_blocks; i++) {

            Rectangle block = this->actual_blocks_[i];
            doodler.position_.y = 300;
            this->actual_blocks_[i].y = this->actual_blocks_[i].y -
                                        doodler.dy;
        };
        for (int j = 0; j < num_of_fblocks; j++) {
            Rectangle block = this->fragile_blocks_[j];
            doodler.position_.y = 300;
            this->fragile_blocks_[j].y = this->fragile_blocks_[j].y -
                                        doodler.dy;
        }
    }

    //if jumpblocks return a block (posn)
    Rectangle anchorblock = this->doodler.jump_blocks(this->actual_blocks_);
    if (anchorblock.height != -1) {

        //if we hit a block, bounce backup
        // this->doodler.dy = -5;
        this->doodler.dy = -8;

        //increase y posn for all block in list  (moving them down on screen)
        for (int i = 0; i < num_of_blocks; i++) {

            Rectangle block = this->actual_blocks_[i];
            //if block is out of screen (within a threshold)
            //re-render it on somewhere in screen (instead of removing it in
            // memory)
            if (block.top_left().y > 550) {
                Rectangle new_block = Rectangle(rand() % 300,
                                                rand() % 300,
                                                60,
                                                10);

                this->actual_blocks_[i] = new_block;
            }
        }

        for (int i = 0; i < num_of_fblocks; i++) {
            Rectangle block = this->fragile_blocks_[i];
            //if block is out of screen (within a threshold)
            //re-render it on somewhere in screen (instead of removing it in
            // memory)
            if (block.top_left().y > 550) {
                Rectangle new_block = Rectangle(rand() % 300,
                                                rand() % 300,
                                                60,
                                                10);

                this->fragile_blocks_[i] = new_block;
            }
        }
    }
    //fragile block disappear once being hit
    Rectangle fragilehit = this->doodler.jump_blocks(this->fragile_blocks_);

    for (int k = 0; k < num_of_fblocks; k++) {
        Rectangle curb = this->fragile_blocks_[k];

        if (curb == fragilehit) {
            Rectangle new_block = Rectangle(rand() % 300,
                                            rand() % 300,
                                            60,
                                            10);

            this->fragile_blocks_[k] = new_block;
        }
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

