#pragma once

#include <ge211.hxx>
#include <vector>
#include <doodler.hxx>

using Position = ge211::Posn<int>;
using Rectangle = ge211::Rect<int>;
using ListofRect = std::vector<Rectangle>;

class Model
{
public:
    //constructor
    Model(Position pos);

    //updates state of game for one frame and position of doodle
    //calls move_blocks_down, replace_blocks, if_hit_block
    void on_frame(double dt);

    // initialize new blocks
    Rectangle add_new_block(int multipler, int gap);

    // RE-RENDERING THE SCREEN
    //blocks continually go down (for both actual and frag)
    void move_blocks_down();

    // replace any blocks that move off-screen (for both actual and frag)
    void replace_blocks();

    // move doodler up if it jumps on actual block or replace fragile block
    void if_hit_block();


    // DOODLER MOVEMENT
    //move doodle left or right or launches it (called in Controller)
    void moves_doodler_left();

    void moves_doodler_right();

    void launch_doodler();

    // GETTER FUNCTIONS BELOW!!
    ListofRect get_actual_blocks() {return this->actual_blocks_;}

    ListofRect get_fragile_blocks() {return this->fragile_blocks_;}

    Doodler get_doodler() {return this->doodler;}

    int get_score() {return this->score_;}


    // TESTING HELPERS
    void clear_actual_blocks(){actual_blocks_.clear();}
    void clear_fragile_blocks(){fragile_blocks_.clear();}
    void set_new_actual(Rectangle block){actual_blocks_.push_back(block);}
    void set_new_fragile(Rectangle block){fragile_blocks_.push_back(block);}

private:

    //the doodler object
    Doodler doodler;
    //blocks the doodler can jump on & amount on screen
    ListofRect actual_blocks_;
    int num_of_blocks = 10;
    // fake blocks the doodler can't jump on & amount on screen
    ListofRect fragile_blocks_;
    int num_of_fblocks = 4;
    // score for the player
    int score_ = 0;


};
