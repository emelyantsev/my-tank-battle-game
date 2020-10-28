#include "game.h"

#include <iostream>
#include <ctime>
#include <string>

#include "txt_resources\fonts\ARCADE.TTF.hpp"

Game::Game() : 
    
    window_(sf::VideoMode(640, 360), "Tanks", sf::Style::Titlebar | sf::Style::Close )
    
{

    window_.setFramerateLimit(60);
    window_.setMouseCursorVisible(false);

    // if ( !font_.loadFromFile("resources\\fonts\\ARCADE.ttf") ) {
    //     exit(-1);
    // }

    if ( !font_.loadFromMemory(&ARCADE_TTF, ARCADE_TTF_len) ) {
         exit(-1);
    }


    status_text_0.setFont(font_);
    status_text_1.setFont(font_);

    status_text_0.setPosition(50, 0);
    status_text_1.setPosition(450, 0);

    status_text_0.setColor(sf::Color::Green);
    status_text_1.setColor(sf::Color::Blue);

    time_str_.setFont(font_);
    time_str_.setPosition(300, 0);
    time_str_.setColor(sf::Color(120, 120, 120));


    terrain_.setFillColor(sf::Color(10, 10, 10));
    terrain_.setPosition(20, 40);
    terrain_.setSize({600, 300});


    view_.setCenter({320, 180});
    view_.setSize({640, 360});
    window_.setView(view_);


    PrepareMenu();
    PreparePause() ;

    LoadSounds();

    PrepareHelp();
}



void Game::run() {


    while (window_.isOpen() ) {

        handleInput();
        update();
        render();
    }

}



void Game::handleInput() {

    
    sf::Event event;

    while (window_.pollEvent(event)) {


        if (event.type == sf::Event::Closed) {

            window_.close();

        }


        switch (state_) {

            case State::MENU: {


                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        window_.close();
                    }
                    else if (event.key.code == sf::Keyboard::Return) {

                        InitNewGame();
                        state_ = State::RUNNING;
                    }
                    else if (event.key.code == sf::Keyboard::F11) {

                        ToggleFullScreen();
                    }
                    else if (event.key.code == sf::Keyboard::F1) {
                        state_ = State::DISPLAY_HELP;
                    }

                }



                break;
            }    

            case State::PAUSED:  {

                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        state_ = State::MENU;
                    }
                    else if (event.key.code == sf::Keyboard::Return) {

                        clock1_.restart();
                        state_ = State::RUNNING;
                    }
                    else if (event.key.code == sf::Keyboard::F11) {
                        ToggleFullScreen();
                    }

                }

                break;
            }

            case State::DISPLAY_RESULT : {


                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        state_ = State::MENU;
                    }
                    
                    else if (event.key.code == sf::Keyboard::F11) {
                        ToggleFullScreen();
                    }
                }

                break;

            }


            case State::DISPLAY_HELP : {


                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                        
                        state_ = State::MENU;
                    }
                    
                    else if (event.key.code == sf::Keyboard::F11) {
                        ToggleFullScreen();
                    }
                }

                break;

            }


            case State::RUNNING:

                {

                if (event.type == sf::Event::KeyPressed) {

                    if (event.key.code == sf::Keyboard::Escape) {
                            state_ = State::PAUSED ;
                            clock1_.restart();
                    }

                    
                    if (event.key.code == sf::Keyboard::W ) {


                            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ) {
                                tank_.Move(50);
                            }
                            else {
                                tank_.Move(25);
                            }
                            
                    }
                    else if (event.key.code == sf::Keyboard::LShift) {

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
                                tank_.Move(50);
                        }
                        
                    }

                    else if (event.key.code == sf::Keyboard::S ) {
                            tank_.Move(-25);
                    }

                    else if (event.key.code == sf::Keyboard::A ) {
                        tank_.Rotate(-5);
                    }

                    else if (event.key.code == sf::Keyboard::D ) {
                        tank_.Rotate(5);
                    }    

                    else if (event.key.code == sf::Keyboard::Space ) {

                        if (tank_.GetElapsedTimeForShooting() > 500) {

                            shells_.push_back( tank_.Fire() );
                        }
                    }


                    else if (event.key.code == sf::Keyboard::F11) {
                        ToggleFullScreen();
                    }

                }

                else if (event.type == sf::Event::KeyReleased) {


                    if (event.key.code == sf::Keyboard::W ) {
                            tank_.Stop();
                    }

                    else if (event.key.code == sf::Keyboard::S ) {
                            tank_.Stop();
                    }

                    else if (event.key.code == sf::Keyboard::LShift) {

                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
                                tank_.Move(10);
                        }
                        
                    }


                }

                break;
                }

        }

    }

    
}




void Game::update() {


    if (state_ == State::MENU) {
        return ;
    }

    else if (state_ == State::PAUSED) {
        return ;
    }

    else if (state_ == State::DISPLAY_RESULT) {

        if (clock2_.getElapsedTime().asSeconds() > 5) {
            state_ = State::MENU;
        }

        return ;
    }
    else if (state_ == State::DISPLAY_HELP) {

        return ;
    }

    


    float time_diff = clock_.restart().asSeconds();

    tank_.Update(time_diff) ;
    enemy_.Update(time_diff) ;

    for (auto& shell : shells_) {

        shell.Update(time_diff);           
    }


    std::list<Shell>::iterator it = shells_.begin();

    while (it != shells_.end()) {

        float distance = sqrt(pow(tank_.GetPosition().x - it->GetPosition().x, 2) +  pow(tank_.GetPosition().y - it->GetPosition().y, 2));

        if (distance > 200) {
            it = shells_.erase(it);
        }
        else {
            ++it;
        }
    }


   

    for (auto& shell : enemy_shells_) {

        shell.Update(time_diff);           
    }


    it = enemy_shells_.begin();

    while (it != enemy_shells_.end()) {

        float distance = sqrt(pow(enemy_.GetPosition().x - it->GetPosition().x, 2) +  pow(enemy_.GetPosition().y - it->GetPosition().y, 2));


        if (distance > 200) {
            it = enemy_shells_.erase(it);
        }
        else {
            ++it;
        }
    }





    for (auto& target : targets_) {
        
        target->Update(time_diff);
         
    }


    checkShellsTargetsCollisions();
    checkShellsTanksCollisions();
    checkShellsObstaclesCollisions() ;

    updateStatus();

}

void Game::render() {

    window_.clear();


    if (state_ == State::MENU) {
        
        RenderMenu();
    }
    else if (state_ == State::DISPLAY_HELP) {
        
        RenderHelp();
    }


    else if (state_ == State::RUNNING || state_ == State::PAUSED || state_ == State::DISPLAY_RESULT) {

        window_.draw(terrain_);


        for (auto obstacle : obstacles_) {
            obstacle->Render(window_);
        }


        
        for (const auto& target : targets_) {
            
            target->Render(window_);
            
        }

        for (const auto& shell : shells_) {
            shell.Render(window_);
        }


        for (const auto& shell : enemy_shells_) {
            shell.Render(window_);
        }


        enemy_.Render(window_);
        tank_.Render(window_);

        window_.draw(status_text_0);
        window_.draw(status_text_1);
        window_.draw(time_str_);

    }

    if (state_ == State::PAUSED) {

        RenderPause();
    }
    else if (state_ == State::DISPLAY_RESULT) {
        
        RenderResult();
    }


    window_.display();
}

