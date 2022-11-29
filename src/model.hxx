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

    //remember deconstuructor ~Model() if in C; => freeze unnecessary memory

    //returns whether game is finished.
    //True when doodle dies, False if
    bool is_game_over() const;

    //this will be the function that is removing blocks at the bottom
    //and (semi) randomly initialize new block at the to (push_back_
    //we only call the function whenever the screen moves
    void update_blocks();

    //called by on_frame when jumped
    //score => += distance between new block you jumped & screen
    void update_score();

    //Makes doodle jump at initialization
    void launch();
    //move doodle left or right depending on key input
    //called in Controller
    void moves_doodle_left();
    void moves_doodle_right();

    //updates state of game for one frame
    //always update position of doodle
    //Case: When doodle jump on a new block  (moves block down)
    //      the whole screen (aka every blocks on screen) moves down
    //      by the distance between the jumped-on-block and the bottom
    //      (maybe remember to add offset a bit to keep block in view)
    //      of the screen
    //      calls update_blocks to remove block off-screen & add new block
    void on_frame(double dt);

    ListofRect actual_blocks();
    ListofRect fragile_blocks();


private:

    //the doodler object
    Doodler doodler;
    //this is a list of all blocks on screen
    //which doodle can jump on
    ListofRect actual_blocks_;
    ListofRect fragile_blocks_;

    void set_game_over();

    int score_;

};
