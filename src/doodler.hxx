//
// Created by Julia Chu on 11/19/22.
//
//avoid duplicated import
#ifndef GAME_DOODLER_HXX
#define GAME_DOODLER_HXX

#include <ge211.hxx>
#include <model.hxx>


class Doodler
{
public:
    using Position = ge211::Posn<int>;
    using Velocity = ge211::Dims<int>;
    using Rectangle = ge211::Rect<int>;
    using ListofRect = std::vector<Rectangle>;


    // return the state of the doodler after 'dt' seconds have passed
    // => should return new doodle with updated position
    // 1. serves also as onframe  => update pos based on dt
    // 2. receive keyboard signal (left right)
    // 3. check if it has jumped on any blocks  (jump forward)
    void on_frame(double dt);


    //get the bottom y position of the doodle
    //aka the feet => where we use it to detect jump block or dead
    int doodle_bottom_y() {
        return this->position_.y - (this->dims_.height / 2);
    }

    //check all blocks
    // return null (if didn't jump on block) or return block (if jumped)
    Rectangle jump_blocks(ListofRect blocks);

    //determine if doodler jumps on a block
    //    => similar x-coord (block dim)
    //    => its bottom is the same as the block's top y
    //INPUT: need this->actual_blocks
    bool jump_block(Rectangle block) ;

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
    void reflect_vertical() {
        velocity_.height *= -1;
    }

    ge211::Image_sprite const& get_sprite() const {
        return doodle_sprites.at(index);
    }

    void update_index() {
        index++;
        if (index >= doodle_sprites.size()) {
            index = 0;
        }
    }

private:
    //current position

    //center
    Position position_;
    ge211::Dims<int> dims_;
    Velocity velocity_;

    //ge211::Image_sprite doodle_sprite;
    std::vector<ge211::Image_sprite> doodle_sprites;

    //stores which position you're on doodle_sprites
    int index = 0;

    friend class Model;
};


#endif //GAME_DOODLER_HXX

