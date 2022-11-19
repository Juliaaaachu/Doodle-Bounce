#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

using Dimension = ge211::Dims<int>;
class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    Dimension initial_window_dimensions() const override;

    void draw(ge211::Sprite_set& set) override;

    //on left & right, moves doodle horizontal position
    void on_key_left (ge211::Key);

    void on_key_right (ge211::Key);

    //on ' '(space) starts game
    void on_key_space(ge211:Key);

private:
    Model model_;
    View view_;
    Dimension screen_dimensions_;
};
