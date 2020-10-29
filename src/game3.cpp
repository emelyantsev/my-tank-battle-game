#include "game.h"

#include <iostream>


#include "txt_resources/images/image01.png.hpp"
#include "txt_resources/sounds/aexp2.wav.hpp"
#include "txt_resources/sounds/Gun_Silencer.wav.hpp"

void Game::PrepareMenu() {

    menu_text0_.setFont(font_) ;
    menu_text1_.setFont(font_) ;

    menu_text0_.setString("Tanks");
    menu_text1_.setString("<Enter> to start playing ...\n<F1> for help");
    
    menu_text0_.setCharacterSize(100);


    menu_text0_.setColor(sf::Color(160, 80, 40)) ;
    menu_text0_.setOrigin( menu_text0_.getGlobalBounds().width / 2 , menu_text0_.getGlobalBounds().height / 2) ;


    menu_text1_.setColor(sf::Color(10, 150, 10)) ;
    menu_text1_.setOrigin( menu_text1_.getGlobalBounds().width / 2 , menu_text1_.getGlobalBounds().height / 2) ;
    
   

    menu_text0_.setPosition( {320, 30} );
    menu_text1_.setPosition( {320, 300} );

    //image0_.loadFromFile("resources\\images\\image01.png");

    image0_.loadFromMemory(&image01_png, image01_png_len);

    window_.setIcon(image0_.getSize().x, image0_.getSize().y, image0_.getPixelsPtr() );


    texture0_.loadFromImage(image0_);
    sprite0_.setTexture(texture0_);

    sprite0_.setScale(0.5, 0.5);

    sprite0_.setOrigin( sprite0_.getGlobalBounds().width / 2 , sprite0_.getGlobalBounds().height / 2) ;
    sprite0_.setPosition({280, 150}) ;

}

void Game::RenderMenu() {

    window_.draw(sprite0_);
    window_.draw(menu_text0_);
    window_.draw(menu_text1_);

}


void Game::PreparePause() {

    menu_text2_.setFont(font_) ;
    menu_text3_.setFont(font_) ;

    menu_text2_.setString("Paused");
    menu_text3_.setString("<Enter> to continue playing ...\n<Esc> to exit to menu ...");


    menu_text2_.setCharacterSize(60);
    menu_text2_.setColor(sf::Color(10, 150, 10)) ;
    menu_text2_.setOrigin( menu_text2_.getGlobalBounds().width / 2 , menu_text2_.getGlobalBounds().height / 2) ;


    menu_text3_.setColor(sf::Color(10, 150, 10)) ;
    menu_text3_.setOrigin( menu_text3_.getGlobalBounds().width / 2 , menu_text3_.getGlobalBounds().height / 2) ;


    menu_text2_.setPosition( {320, 120} );
    menu_text3_.setPosition( {320, 280} );


    pause_terrain_.setFillColor(sf::Color(10, 20, 10, 200));
    pause_terrain_.setPosition(5, 5);
    pause_terrain_.setSize({630, 350});
}


void Game::RenderPause() {

    window_.draw(pause_terrain_);
    window_.draw(menu_text2_);
    window_.draw(menu_text3_);

}


void Game::ToggleFullScreen() {

    if (!is_full_screen) {

        is_full_screen = true;
        window_.create( sf::VideoMode(1920, 1080), "Tanks", sf::Style::Fullscreen) ;

    }
    else {

        is_full_screen = false;
        window_.create( sf::VideoMode(640, 360), "Tanks", sf::Style::Titlebar | sf::Style::Close) ;
        window_.setIcon(image0_.getSize().x, image0_.getSize().y, image0_.getPixelsPtr() );
    }

    window_.setView(view_);
    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(false);

}



void Game::PrepareResult() {



    result_text4_.setFont(font_);

    Result result_ = tank_.GetPoints() > enemy_.GetPoints() ? Result::WIN :
                    tank_.GetPoints() == enemy_.GetPoints() ? Result::DRAW : Result::LOST;

    
    std::string result_str_;

    switch (result_) {

        case (Result::WIN) : {

            result_str_ = std::string("You win with score ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Green) ;
            break;
        }

        case (Result::LOST) : {

            result_str_ = std::string("You lost with score ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Red) ;
            break;
        }

        case (Result::DRAW) : {
            
            result_str_ = std::string("The game ended in a draw ") + std::to_string(tank_.GetPoints()) + " : " + std::to_string(enemy_.GetPoints() );
            result_text4_.setColor(sf::Color::Blue) ;
            break;
        }
    }


    result_text4_.setString(result_str_) ;
    result_text4_.setOrigin( result_text4_.getGlobalBounds().width / 2 , result_text4_.getGlobalBounds().height / 2) ;
    result_text4_.setPosition( { 320, 180} ) ;

    clock2_.restart();
}


void Game::RenderResult() {

    window_.draw(pause_terrain_);

    window_.draw(result_text4_);
};




void Game::LoadSounds() {
    

    //buffer0_.loadFromFile("resources\\sounds\\aexp2.wav");
    //buffer1_.loadFromFile("resources\\sounds\\Gun_Silencer.wav");

    buffer0_.loadFromMemory(&aexp2_wav, aexp2_wav_len);
    buffer1_.loadFromMemory(&Gun_Silencer_wav, Gun_Silencer_wav_len);

    sound0_.setBuffer(buffer0_);
    sound1_.setBuffer(buffer1_);
}


void Game::PrepareHelp() {

    help_text_.setFont(font_);


    std::string help_string = std::string("<W> - move forward\n") + 
                                "<S> - move back\n" +
                                "<A> - rotate left\n" +
                                "<D> - rotate right\n" +
                                "<SPACE> - shoot\n" +
                                "<LShift> - upspeed\n" + 
                                "<F11> - toggle full screen" ;


    help_text_.setString(help_string);

    help_text_.setColor(sf::Color(10, 150, 10)) ;
    help_text_.setOrigin( help_text_.getGlobalBounds().width / 2 , help_text_.getGlobalBounds().height / 2) ;

    help_text_.setPosition({320, 180});

}


void Game::RenderHelp() {

    window_.draw(pause_terrain_);
    window_.draw(help_text_) ;
}