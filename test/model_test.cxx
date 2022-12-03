#include "model.hxx"
#include <catch.hxx>

// checks if the doodler correctly keeps moving down until it bounces
TEST_CASE("check bounce")
{
    // initialize with doodler at y = 300 and clear the existing blocks
    Model m1({100,300});
    m1.clear_actual_blocks();
    m1.clear_fragile_blocks();

    // add a new block at desired pos
    Rectangle test_block(100, 355, 60, 10);
    m1.set_new_actual(test_block);

    // check set up is correct
    CHECK(m1.get_actual_blocks().size() == 1);
    CHECK(m1.get_fragile_blocks().size() == 0);
    CHECK(m1.get_actual_blocks()[0].y == 355);
    CHECK(m1.get_doodler().get_position().y == 300);

    int dt = 1;

    // launch the doodler to start the game
    m1.launch_doodler();

    // calls 10 frames and check the doodler is moving down
    for (int i = 0; i < 16; i++) {
        m1.on_frame(dt);
        CHECK(m1.get_doodler().get_dy() > 0);
    }
    // call another frame so the doodler hits the set block
    // check the position of impact
    m1.on_frame(dt);
    CHECK(m1.get_doodler().get_y_botttom() >= m1.get_actual_blocks()[0].y);

    // check after frames delay (negating the down velocity)
    m1.on_frame(dt);
    m1.on_frame(dt);
    CHECK(m1.get_doodler().get_dy() <= 0);

    // call 39 frames so the velocity is once again negated (-0.2 each time)
    for (int i = 0; i < 39; i++) {
        m1.on_frame(dt);
        CHECK(m1.get_doodler().get_dy() <= 0);
    }
    // call another frame so the doodler's velocity is reversed
    m1.on_frame(dt);
    CHECK(m1.get_doodler().get_dy() > 0);

}

// check doodler dies when it hits the bottom of screen
TEST_CASE("check doodler dies")
{
    // initialize with doodler at y = 300 and clear the existing blocks
    Model m3({100,550});
    m3.clear_actual_blocks();
    m3.clear_fragile_blocks();

    int dt = 1;
    m3.launch_doodler();

    // calls 24 frames so the doodler hits bottom of the screen
    for (int i = 0; i < 24; i++) {
        m3.on_frame(dt);
    }

    CHECK(m3.get_doodler().get_position().y == 600);
    CHECK(m3.get_doodler().doodler_dead());
}

// // checks to ensure block sprites are moving down as the game progresses
TEST_CASE("check blocks moves down")
{
    // initialize and clear the existing blocks
    // initialize with doodler at y = 300 and clear the existing blocks
    Model m2({100,500});
    m2.clear_actual_blocks();
    m2.clear_fragile_blocks();

    // add a new block at desired pos
    Rectangle test_block1(100, 555, 60, 10);
    m2.set_new_actual(test_block1);

    // add two blocks that the doodle won't interact with, but will shift down
    Rectangle test_block2(100, 430, 60, 10);
    m2.set_new_actual(test_block2);

    Rectangle test_block3(100, 250, 60, 10);
    m2.set_new_actual(test_block3);

    CHECK(m2.get_actual_blocks().size() == 3);
    CHECK(m2.get_doodler().get_position().y == 500);

    int change_y = 0;
    int dt = 1;
    m2.launch_doodler();

    // calls 17 frames so the doodler hits the bottom block, check this
    for (int i = 0; i < 17; i++) {m2.on_frame(dt);}
    CHECK(m2.get_doodler().get_y_botttom() >= m2.get_actual_blocks()[0].y);

    // call 45 frames so the doodler is moving upwards until negated, check
    for (int i = 0; i < 45; i++) {m2.on_frame(dt);}
    CHECK(m2.get_doodler().get_dy() > 0);

    // call more frames so the doodler moves down, hits block 2, check
    for (int i = 0; i < 18; i++) {
        m2.on_frame(dt);;
        CHECK(m2.get_doodler().get_dy() > 0);
    }
    // call on frame so doodler hits block 2
    m2.on_frame(dt);

    // call more frames so doodler jumps up, this time screen moves up too
    for (int i = 0; i < 20; i++) {
        m2.on_frame(dt);
        if (m2.get_doodler().get_position().y <= 300){
            change_y -= m2.get_doodler().get_dy();
        }
        // manually calculate how far the doodler moved
    }
    // check the block will move off-screen with the next on frame
    CHECK(m2.get_actual_blocks()[0].y >= 600 - 10 +
                                    3*m2.get_doodler().get_dy());

    // call another frame so the bottom of block 1 goes past screen bottom
    m2.on_frame(dt);
    change_y -= m2.get_doodler().get_dy();

    // check the first bottom block is re-rendered at top bc it went off-screen
    CHECK(m2.get_actual_blocks()[0].y == -15);

    // check the two other blocks is re-rendered at lower position by dy change
    CHECK(m2.get_actual_blocks()[1].y == 430 + change_y);
    CHECK(m2.get_actual_blocks()[2].y == 250 + change_y);

}

// checks that the fragile block is replaced when jumped on
TEST_CASE("check fragile block breaks")
{
    // initialize with doodler at y = 300 and clear the existing blocks
    Model m4({100,300});
    m4.clear_actual_blocks();
    m4.clear_fragile_blocks();

    // add a new fragile at desired pos
    Rectangle test_block1(100, 355, 60, 10);
    m4.set_new_fragile(test_block1);

    // add another fragile at diff location (check if right one re-rendered)
    Rectangle test_block2(200, 355, 60, 10);
    m4.set_new_fragile(test_block2);

    CHECK(m4.get_fragile_blocks().size() == 2);
    int dt = 1;
    m4.launch_doodler();

    // calls 16 frames so the doodler reaches fragile block 1
    for (int i = 0; i < 16; i++) {
        m4.on_frame(dt);
    }

    // call another frame so the doodler hits fragile 1
    // check the position of impact
    m4.on_frame(dt);
    CHECK(m4.get_doodler().get_y_botttom() >= m4.get_fragile_blocks()[0].y);

    // call another frame so the re-render occurs
    m4.on_frame(dt);

    // check the first hit fragile block is re-rendered
    // check the other fragile block remains the same
    CHECK(m4.get_fragile_blocks()[0].y == -15);
    CHECK(m4.get_fragile_blocks()[1].x == 200);
}
//

// checks the score updates with the doodle's dy changes
TEST_CASE("check score count")
{
    // initialize with doodler at y = 300 and clear the existing blocks
    Model m5({100,300});
    m5.clear_actual_blocks();
    m5.clear_fragile_blocks();

    // start with one new block at desired pos
    Rectangle test_block1(100, 355, 60, 10);
    m5.set_new_actual(test_block1);

    // create testing score counter
    int score_counter = 0;

    int dt = 1;
    m5.launch_doodler();

    // calls 21 frames so the doodler hits the first block
    for (int i = 0; i < 21; i++) {
        m5.on_frame(dt);
    }

    // call 37 frames so doodle velocity negated, checks score
    for (int i = 0; i < 37; i++) {
        m5.on_frame(dt);
        // manually change the testing score (updates with doodler movement up)
        score_counter -= m5.get_doodler().get_dy();
        CHECK(m5.get_score() == score_counter);
    }
}
