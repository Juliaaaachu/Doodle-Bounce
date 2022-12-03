#pragma once

#include <ge211.hxx>
#include <vector>

//Forward Declaration
class Model;


class Doodler
{
public:
    using Position = ge211::Posn<int>;
    using Rectangle = ge211::Rect<int>;
    using ListofRect = std::vector<Rectangle>;

    //Constructor
    Doodler(Position pos);

    // moves the doodler downwards continuously
    void on_frame(double dt);

    //check all blocks
    // return null (if didn't jump on block) or return block (if jumped)
    Rectangle jumped_on_block(ListofRect blocks);

    //determine if doodler jumps on a block
    //    => similar x-coord (block dim)
    //    => its bottom is the same as the block's top y
    //INPUT: need this->actual_blocks
    bool is_jump_block(Rectangle block) ;

    //check if doodle is dead
    //by comparing doodle_bottom to board dimension
    bool doodler_dead() const;


    // GETTER FUNCTIONS BELOW!

    // get the top left of the doodler -> used to draw the screen
    Position get_topleft_pos() {
        Position pos = this->position_;
        doodler_top_left_ = Position(pos.x - dims_.width / 2,
                                     pos.y - dims_.height/2);
        return doodler_top_left_;
    }

    //get the bottom y position of the doodler (feet) for jump/dead detection
    int get_y_botttom (){
        doodler_y_bottom = this->position_.y + (this->dims_.height / 2);
        return doodler_y_bottom;
    }
    // get the left side of the doodler (nose) for jump detection
    int get_x_left() {
        return this->position_.x - this->dims_.width / 2 + 15;
    }
    // get the right side of the doodler (butt) for jump detection
    int get_x_right() {
        return this->position_.x + this->dims_.width / 2 - 15;
    }

    bool get_face_left() {return face_left_;}

    bool get_live() {return live_;}

    float get_dy() {return dy;}

    Position get_position(){return position_;}

private:
    //doodler's center
    Position position_;

    Position doodler_top_left_ {0,0};

    int doodler_y_bottom;
    // doodler dimensions
    ge211::Dims<int> dims_ {64, 63};
    // doodler velocity boost
    float dy = 0;
    // doodler facing dir. (for view)
    bool face_left_ = true;
    // whether the doodler has been launched
    bool live_ = false;

    friend class Model;
};