#include "model.hxx"
#include "view.hxx"
#include <catch.hxx>

struct Test_access
{
    Model& model;

    // Constructs a `Test_access` with a reference to the Model under test.
    explicit Test_access(Model&);
    void set_actual_block (Position p);
    void set_fragile_block (Position p);
    void set_doodler (Position p);
    void clear_blocks(ListofRect blocks);
};

//
// test case checks if the doodler correctly keeps moving down until it bounces
TEST_CASE("check bounce")
{
    // initialize and clear the existing blocks
    Model model;
    Test_access access(model);
    access.clear_blocks(model.get_actual_blocks());
    access.clear_blocks(model.get_fragile_blocks());
    double dt = 1;

    // add a new block at desired pos and doodler slightly above
    access.set_actual_block({100, 400});
    access.set_doodler({100, 300});
    // check the initialization works
    CHECK(model.get_doodler().get_y_botttom() == 50);

    // launch the doodler to start the game
    model.launch_doodler();

    // calls 10 frames and check the doodler is moving down
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
        CHECK(model.get_doodler().get_y_botttom() == 50);
        CHECK(model.get_doodler().get_dy() > 0);
    }
    // call another frame so the doodler hits the set block
    // check the position of impact, check the doodler is moving up
    model.on_frame(dt);
    CHECK(model.get_doodler().get_y_botttom() == 50);
    CHECK(model.get_doodler().get_dy() < 0);

    // call 10 frame and check the doodler keeps moving up
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
        CHECK(model.get_doodler().get_y_botttom() == 50);
        CHECK(model.get_doodler().get_dy() < 0);
    }
    // call another frame so the doodler's velocity is reversed
    model.on_frame(dt);
    CHECK(model.get_doodler().get_dy() > 0);

}


// checks to ensure the block sprites are moving down as the game progresses
TEST_CASE("check blocks moves down")
{
    // initialize and clear the existing blocks
    Model model;
    Test_access access(model);
    access.clear_blocks(model.get_actual_blocks());
    access.clear_blocks(model.get_fragile_blocks());
    double dt = 1;

    // set blocks above the doodler
    access.set_actual_block({100, 280});
    access.set_actual_block({100, 250});

    // add a new block at desired pos and doodler slightly above
    access.set_actual_block({100, 400});
    access.set_doodler({100, 300});

    // launch the doodler to start the game
    model.launch_doodler();

    // calls 10 frames so the doodler hits the bottom block
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
    }

    // check the first bottom block is re-rendered at top bc it went off-screen
    CHECK(model.get_actual_blocks()[0].y == -15);

    // check the two other blocks is re-rendered at a lower position
    CHECK(model.get_actual_blocks()[1].y == 400 - model.get_doodler().get_dy());
    CHECK(model.get_actual_blocks()[2].y == 400 - model.get_doodler().get_dy());

}

// check doodler dies when it hits the bottom of screen
TEST_CASE("check doodler dies")
{
    // initialize and clear the existing blocks
    Model model;
    Test_access access(model);
    access.clear_blocks(model.get_actual_blocks());
    access.clear_blocks(model.get_fragile_blocks());
    double dt = 1;

    // no new blocks initialized bc doodler has to free fall
    // set doodler at a desired pos
    access.set_doodler({100, 300});

    // launch the doodler to start the game
    model.launch_doodler();

    // calls 10 frames so the doodler hits bottom of the screen
    for (int i = 0; i < 20; i++) {
        model.on_frame(dt);
    }

    CHECK(model.get_doodler().doodler_dead());
}

TEST_CASE("check fragile block breaks")
{
    // initialize and clear the existing blocks
    Model model;
    Test_access access(model);
    access.clear_blocks(model.get_actual_blocks());
    access.clear_blocks(model.get_fragile_blocks());
    double dt = 1;

    // set fragile blocks below the doodler
    access.set_fragile_block({100, 400});
    access.set_fragile_block({200, 400});

    // set the doodler above fragile block 1 (the one we're testing with)
    access.set_doodler({100, 300});

    // launch the doodler to start the game
    model.launch_doodler();

    // calls 10 frames so the doodler hits fragile block 1
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
    }

    // check the first hit fragile block is re-rendered
    // check the other fragile block remains the same
    CHECK(model.get_fragile_blocks()[0].y == -15);
    CHECK(model.get_fragile_blocks()[1].x == 200);
    CHECK(model.get_fragile_blocks()[1].y == 400);
}

TEST_CASE("check score count")
{
    // initialize and clear the existing blocks
    Model model;
    Test_access access(model);
    access.clear_blocks(model.get_actual_blocks());
    access.clear_blocks(model.get_fragile_blocks());
    double dt = 1;

    // create a manual counter for testing
    int score_counter = 0;

    // set three blocks
    access.set_actual_block({100, 500});
    access.set_actual_block({100, 420});
    access.set_actual_block({100, 340});

    // no new blocks initialized bc doodler has to free fall
    // set doodler at a desired pos
    access.set_doodler({100, 430});

    // launch the doodler to start the game
    model.launch_doodler();

    // calls 10 frames so the doodler hits the first block
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
    }
    // check the score increases correctly
    CHECK(model.get_score() == score_counter - model.get_doodler().get_dy());

    // calls 10 frames so the doodler hits the second block
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
    }
    // update the score counter manually, check with real score
    score_counter -= model.get_doodler().get_dy();
    CHECK(model.get_score() == score_counter);

    // calls 10 frames so the doodler hits the second block
    for (int i = 0; i < 10; i++) {
        model.on_frame(dt);
    }

    // update the score counter manually, check with real score
    score_counter -= model.get_doodler().get_dy();
    CHECK(model.get_score() == score_counter);

}

Test_access::Test_access(Model& model)
        : model(model)
{ }

void
Test_access::set_actual_block(Position p){
    Rectangle test_block(p.x, p.y, 60, 10);
    model.get_actual_blocks().push_back(test_block);
}

void
Test_access::set_fragile_block(Position p){
    Rectangle test_block(p.x, p.y, 60, 10);
    model.get_fragile_blocks().push_back(test_block);
}

void
Test_access::set_doodler(Position p){
    model.get_doodler().set_doodler_position(p);
}

void
Test_access::clear_blocks(ListofRect blocks){
    blocks.clear();
}