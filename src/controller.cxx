#include "controller.hxx"
#include "view.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

void Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

void
Controller::on_key(Key key)
{
    if (key == Key::left()){
        // move doodler left
        model_.moves_doodle_left();
    }
    if (key == Key::right()){
        // move doodler right
        model_.moves_doodle_right();
    }
    if (key == Key::code(' ')){
        // launch doodler
        model_.launch();
    }
    if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::on_key_down(ge211::events::Key key)
{
    if (key == Key::left()){
        // move doodler left
        model_.moves_doodle_left();
    }
    else if (key == Key::right()){
        // move doodler right
        model_.moves_doodle_right();
    }
    else if (key == Key::code(' ')){
        // launch doodler
        model_.launch();
    }

}
