#include "model.hxx"
#include <stdlib.h>

Model::Model()
{
    //Initialize 10 blocks on screen
    for (int i = 0 ; i < 10; i++) {
        //assuming screen dim is 300*600
        //TODO: game config file to store all constant
        //height random will be in range 50 - 550
        Position brick_pos = Position(rand() % 300,rand() % 500 + 50 );

        Rectangle block = Rectangle (brick_pos.x,
                                     brick_pos.y,
                                     30,
                                     10);

        this->actual_blocks().push_back(block);
    }

}

void
Model::on_frame(double dt) {

    //if doodler is dead, dont update anything
    if (this->doodler.doodle_dead()) return;

    //if jumpblocks return a block (posn)
    Rectangle anchorblock = this->doodler.jump_blocks(this->actual_blocks_);
    if (anchorblock.height != -1) {

        //if we hit a block, bounce backup
        this->doodler.velocity_.height = -10;

        int anchor_y = anchorblock.height;

        //assume screen dim height = 600
        //assume we always want jumped block to be 100 pix above screen bottom
        //=> assume lowest block will always be at 500 y
        int dist2anchor = 500 - anchor_y;

        //increase y posn for all block in list  (moving them down on screen)
        for (int i = 0; i < 10; i++) {

            Rectangle block = this->actual_blocks_[i];
            block.top_left().down_by(dist2anchor);

            //if block is out of screen (within a threshold)
            //re-render it on somewhere in screen (instead of removing it in
            // memory)
            if (block.top_left().y > 550) {
                Rectangle new_block = Rectangle(rand() % 300,
                                                rand() % dist2anchor,
                                                30,
                                                10);

                this->actual_blocks_[i] = new_block;
            }
        }

    }

}

ListofRect
Model::actual_blocks(){
    return actual_blocks_;
}

ListofRect
Model::fragile_blocks(){
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
    this->doodler.position_.left_by(5);
}

// moving the doodler right, signify its facing right now
void
Model::moves_doodle_right() {
    this->doodler.position_.right_by(5);
}

