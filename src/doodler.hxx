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
    Doodler();

    // moves the doodler downwards continuously
    void on_frame(double dt);

    //get the bottom y position of the doodle
    //aka the feet => where we use it to detect jump block or dead
    int doodle_bottom_y() {return this->position_.y + (this->dims_.height / 2);}

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
    Position get_topleft_pos () {
        Position pos = this->position_;
        Position t_l = Position(pos.x - dims_.width / 2,
                                pos.y - dims_.height/2);
        return t_l;
    }

    bool get_face_left(){return face_left_;}

    bool get_live(){return live_;}

private:
    //doodler's center
    Position position_;
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