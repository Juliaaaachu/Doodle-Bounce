#pragma once

#include <ge211.hxx>
#include <vector>
#include <doodler.hxx>

using Dimensions = ge211::Dims<int>;
using Position = ge211::Posn<int>;
using Rectangle = ge211::Rect<int>;
using ListofRect = std::vector<Rectangle>;

class Model
{
public:
    //constructor
    Model();

    //remember deconstructor ~Model() if in C; => freeze unnecessary memory

    //returns whether game is finished.
    //True when doodle dies, False if
    bool is_game_over() const;

    //called by on_frame when jumped
    //score => += distance between new block you jumped & screen
    void update_score();

    //updates state of game for one frame and position of doodle
    //Case: calls move_blocks_down, replace_blocks, if_hit_block
    void on_frame(double dt);

    //blocks continually go down (for both actual and frag)
    void move_blocks_down();

    Rectangle add_new_block();

    bool blocks_no_overlap(Position new_block_pos);

    // replace any blocks that move off-screen (for both actual and frag)
    void replace_blocks();

    // move doodler up if it jumps on actual block or replace fragile block
    void if_hit_block();

    // getter functions!
    ListofRect get_actual_blocks() {return this->actual_blocks_;}

    ListofRect get_fragile_blocks() {return this->fragile_blocks_;}

    ListofRect get_all_blocks();

    Doodler get_doodler() {return this->doodler;}

    int get_score() {return this->score_;}

    //move doodle left or right (called in Controller)
    void moves_doodler_left();

    void moves_doodler_right();

    void launch_doodler();


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
