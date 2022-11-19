//
// Created by Julia Chu on 11/19/22.
//

#ifndef GAME_DOODLER_HXX
#define GAME_DOODLER_HXX

#endif //GAME_DOODLER_HXX

#include <ge211.hxx>

using Position = ge211::Posn<int>;
using Velocity = ge211::Dims<int>;

class Doodler
{
public:

    //return the state of the doodler after 'dt' seconds have passed
    Doodler next(double dt) const;

    //get the bottom x,y position of the doodle
    //aka the feet => where we use it to detect jump block or dead
    Position doodle_bottom();

    //determine if doodler jumps on a block
    //aka => its bottom is the same as the block's top y
    bool jump_block() const;

    //check if doodle is dead
    //by comparing doodle_bottom to board dimension
    bool doodle_dead() const;

    //change doodler direction if
    //case 1: if traveling upward (velocity > 0):
    //        when distance_travel > 100 (temp val)
    //        reflect_vertical (aka doodle falls)
    //case 2: if traveling downward (velocity < 0):
    //        if doodler hit a block (jump_block):
    //        reflect vertical (doodle jump upward)
    void reflect_vertical();
    //velocity_.height *= -1


private:
    //current position
    Position position_;
    Velocity velocity_;

};
