//
// Created by Julia Chu on 11/19/22.
//
#include "doodler.hxx"
#include "model.hxx"

bool
Doodler::doodle_dead() const {
    return (this->position_.y >= 600);
}

bool
Doodler::jump_block(Rectangle block) {
    int doodle_y = this->doodle_bottom_y();

    //x is a range
    int doodle_x_min = this->position_.x - this->dims_.width / 2;
    int doodle_x_max = this->position_.x + this->dims_.width / 2;

    auto block_pos = block.top_left();
    int block_x_min = block_pos.x;
    int block_x_max = block_pos.x + block.width;
    int block_y_min = block_pos.y;
    int block_y_max = block_pos.y + block.height;

    //check if doodle & block overlap

    if (block_y_min < doodle_y && doodle_y < block_y_max) {
        if (doodle_x_min < block_x_min && block_x_min < doodle_x_max ||
            block_x_min < doodle_x_min &&  doodle_x_min < block_x_max) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}


Rectangle
Doodler::jump_blocks(ListofRect blocks)
{
    for (auto curblock : blocks) {
        if (jump_block(curblock)) {
            return curblock;
        };
    }
    return nullptr;
}

//update doodler position
void
Doodler::on_frame(double dt)
{
    // ge211::Dims<int> dy = this->velocity_.y;
    int dy = 0;

    //for every frame, we change y by 0.2 pixels (always falling down)
    dy += 0.2;
    this->position_.y += dy;

}