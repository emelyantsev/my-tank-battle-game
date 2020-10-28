#include "game.h"

#include <iostream>
#include <ctime>
#include <string>




void Game::checkShellsTargetsCollisions() {


    std::list<Shell>::iterator it_shells = shells_.begin();

    while (it_shells != shells_.end()) {

        bool it_shells_increased = false;

        auto it_targets = targets_.begin();

        while (it_targets != targets_.end() ) {


            if ( (*it_targets)->GetBounds().contains( it_shells->GetPosition()  ) ) {


                if ( (*it_targets)->GetState() == Target::State::ALIVE) {    

                    (*it_targets)->Blow();
                    tank_.UpdatePoints(1);

                }


                it_shells = shells_.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_targets;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }



    it_shells = enemy_shells_.begin();


    while (it_shells != enemy_shells_.end()) {

        bool it_shells_increased = false;

        auto it_targets = targets_.begin();

        while (it_targets != targets_.end() ) {


            if ( (*it_targets)->GetBounds().contains( it_shells->GetPosition()  ) ) {

                if ( (*it_targets)->GetState() == Target::State::ALIVE) {    

                    (*it_targets)->Blow();
                    enemy_.UpdatePoints(1);

                }

                it_shells = shells_.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_targets;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }






}


void Game::checkShellsTanksCollisions() {


    std::list<Shell>::iterator it_shells = shells_.begin();

    while (it_shells != shells_.end()) {


        if (enemy_.GetBounds().contains( it_shells->GetPosition() ) ) {

            
            tank_.UpdatePoints(1);

            sound1_.play();

            it_shells = shells_.erase(it_shells);

            continue;
        } 

        
        ++it_shells;

    }



    it_shells = enemy_shells_.begin();

    while (it_shells != enemy_shells_.end()) {


        if (tank_.GetBounds().contains( it_shells->GetPosition() ) ) {

            
            enemy_.UpdatePoints(1);
            sound1_.play();
            it_shells = enemy_shells_.erase(it_shells);

            continue;
        } 
        
        ++it_shells;
    }
}



void Game::checkShellsObstaclesCollisions() {


    std::list<Shell>::iterator it_shells = shells_.begin();

    while (it_shells != shells_.end()) {

        bool it_shells_increased = false;

        auto it_obstacles = obstacles_.begin();

        while (it_obstacles != obstacles_.end() ) {


            if ( (*it_obstacles)->GetBounds().contains( it_shells->GetPosition()  ) 
                    && ( (*it_obstacles)->GetQuality() == Obstacle::Quality::UNPENETRABLE ) ) {


                it_shells = shells_.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_obstacles;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }


    it_shells = enemy_shells_.begin();

    while (it_shells != enemy_shells_.end()) {

        bool it_shells_increased = false;

        auto it_obstacles = obstacles_.begin();

        while (it_obstacles != obstacles_.end() ) {


            if ( (*it_obstacles)->GetBounds().contains( it_shells->GetPosition()  ) 
                    && ( (*it_obstacles)->GetQuality() == Obstacle::Quality::UNPENETRABLE ) ) {


                it_shells = shells_.erase(it_shells);
                it_shells_increased = true;
                break;
            };
            
            ++it_obstacles;
        }


        if (!it_shells_increased) {
            ++it_shells;
        }
    }



}



void Game::updateStatus() {

    std::string status_0 = std::string("You : " ) + std::to_string(tank_.GetPoints() );
    std::string status_1 = std::string("Enemy : " ) + std::to_string(enemy_.GetPoints() ) ;

    status_text_0.setString(status_0);
    status_text_1.setString(status_1);


    game_time_ += clock1_.restart();


    if (game_time_.asSeconds() >= game_duration_) {

        game_time_ = sf::seconds(game_duration_);
        state_ = State::DISPLAY_RESULT;
        PrepareResult();
    }

    std::string status_3 = std::to_string(int(game_time_.asSeconds()) / 60 ) + ":" + 

            (int(game_time_.asSeconds()) % 60  < 10 ? "0" : "") +

            std::to_string(int(game_time_.asSeconds()) % 60 ) ;

    time_str_.setString(status_3);
}