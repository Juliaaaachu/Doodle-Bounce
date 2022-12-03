#include "doodler.hxx"
#include "model.hxx"

// constructing the doodler
Doodler::Doodler(Position pos)
        : position_(pos)
{}

// see if doodler hits screen bottom
bool
Doodler::doodler_dead() const {
    return (this->position_.y >= 600);
}

// check if the doodler jumps on a block
bool
Doodler::is_jump_block(Rectangle block)
{
    // if the doodler is moving down
    if (this->dy > 0) {
        // setting up variables for block height and width dimensions
        auto block_pos = block.top_left();
        int block_x_min = block_pos.x;
        int block_x_max = block_pos.x + block.width;
        int block_y_min = block_pos.y;
        int block_y_max = block_pos.y + block.height;
        //check if doodler & block overlap
        if (block_y_min < get_y_botttom() && get_y_botttom() < block_y_max) {
            if ((get_x_left() < block_x_min && block_x_min < get_x_right()) ||
                (block_x_min < get_x_left() && get_x_left() < block_x_max)) {
                return true;
            }
        }
    }
    return false;
}

// return the block that was jumped on
Rectangle
Doodler::jumped_on_block(ListofRect blocks){
    // iterate through the blocks, return if jumped on
    for (auto curblock : blocks) {
        if (is_jump_block(curblock)) {
            return curblock;
        }
    }
    // otherwise return null block
    return Rectangle(-1, -1, -1, -1);
}

// update doodler position
void
Doodler::on_frame(double dt)
{
    dy += 0.2;
    //for every frame, we increase y by 0.2 pixels (always falling down)
   this->position_.y += this->dy;
}