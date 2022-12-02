#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

using Key = ge211::events::Key;
using Position = ge211::Posn<int>;

class Controller : public ge211::Abstract_game
{
public:

    Controller();


protected:

    // creating the initial window for the game
    ge211::Dims<int> initial_window_dimensions() const override;

    // creating window title
    std::string initial_window_title() const override;

    // calling model_.on_frame through controller
    void on_frame(double dt) override;

    // drawing the screen to update by frame
    void draw(ge211::Sprite_set& set) override;

    // creating on key functions, passing in left, right, and space
    void on_key(Key key) override;

private:
    Model model_;
    View view_;
};
