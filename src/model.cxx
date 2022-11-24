#include "model.hxx"

void
Model::on_frame(double dt) {
    //if jumpblocks return a block (posn)
    //anchor_y = jumpblocks().y

    //assume screen dim height = 600
    //assume we always want jumped block to be 100 pix
    //above screen bottom
    //=> assume lowest block will always be at 500 y
    int dist2anchor = 500 - anchor_y;

    //increase y posn for all block in list  (moving them down on screen)
    for (auto &block: this->actual_blocks) {
        block.top_left().down_by(dist2anchor);
    }

}