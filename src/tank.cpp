#include "tank.h"

#include <math.h>
#define PI 3.14159265

#include <iostream>

#include "game.h"

#include <algorithm>


Tank::Tank(sf::Vector2f position, sf::Color color, sf::Color color1, sf::Color color2, Game * p_game ) : p_game_(p_game) {

    corpus_.setSize( {20,10} );
    corpus_.setOrigin( {10,5} );
    corpus_.setFillColor(color);
    corpus_.setPosition(position);

    tower_.setRadius(5);
    tower_.setOrigin( {5, 5} );
    tower_.setPosition(position);
    tower_.setFillColor( color1 );
    
   
    gun_.setSize( {15, 2} );
    gun_.setOrigin( {0, 1} );
    gun_.setPosition(position);
    gun_.setFillColor( color2 );

}


void Tank::Render(sf::RenderWindow& l_window) {

    l_window.draw(corpus_);
    l_window.draw(tower_);
    l_window.draw(gun_);
    
}


void Tank::Move(int speed) {
    
    speed_ = speed;
}

void Tank::Stop() {
    
    speed_ = 0;
}

void Tank::Rotate(float angle) {
    


    sf::RectangleShape new_corpus(corpus_);
    new_corpus.rotate(angle);


    if (   &(p_game_->tank_) != this   && p_game_->tank_.GetBounds().intersects(new_corpus.getGlobalBounds() )       )    {
        return;
    }


    if (   &(p_game_->enemy_) != this   && p_game_->enemy_.GetBounds().intersects(new_corpus.getGlobalBounds())       )    {
        return;
    }



    corpus_.rotate(angle);
    gun_.rotate(angle);
    angle_ = corpus_.getRotation();


}


void Tank::Update(float time_diff) {

    float vx = cos (angle_ * PI/180) * speed_ * time_diff;
    float vy = sin (angle_ * PI/180) * speed_ * time_diff;


    sf::Vector2f new_position = GetPosition() + sf::Vector2f(vx, vy);

    if (!p_game_->getField().contains(new_position)) {
        Stop();
        return;
    }

    
    if (std::any_of(p_game_->obstacles_.begin(), p_game_->obstacles_.end(), 

        [&](std::shared_ptr<Obstacle> p_item){ return p_item->GetBounds().contains(new_position)  ;  }  )  ) {
            Stop();
            return;
        }


    sf::FloatRect new_rect = GetBounds();
    
    new_rect.left += vx;
    new_rect.top += vy;


    if (   &(p_game_->tank_) != this   && p_game_->tank_.GetBounds().intersects(new_rect)       )    {
        Stop();
        return;
    }


    if (   &(p_game_->enemy_) != this   && p_game_->enemy_.GetBounds().intersects(new_rect)       )    {
        Stop();
        return;
    }



    corpus_.move(vx, vy);
    tower_.move(vx, vy);
    gun_.move(vx, vy);

}


sf::Vector2f Tank::GetPosition() const {

    return corpus_.getPosition();
}

float Tank::GetRotation() const {
    
    return corpus_.getRotation();
};

sf::FloatRect Tank::GetBounds() const {

    return corpus_.getGlobalBounds();
};


void Tank::UpdatePoints(int points) { 
    
    points_ += points;
}

int Tank::GetPoints() const {return points_; }


// Shell


Shell Tank::Fire() {

    shooting_timer_.restart();

    float sx = cos (angle_ * PI/180) * 15 ;
    float sy = sin (angle_ * PI/180) * 15 ;

    sf::Vector2f new_shell_position( { corpus_.getPosition().x + sx, corpus_.getPosition().y + sy }) ;


    float vx = cos (angle_ * PI/180) * 50.0 ;
    float vy = sin (angle_ * PI/180) * 50.0 ;


    p_game_->sound0_.play();

    return Shell(new_shell_position, {vx, vy});

}


int Tank::GetElapsedTimeForShooting() const {

    return shooting_timer_.getElapsedTime().asMilliseconds();
}


Shell::Shell(sf::Vector2f position, sf::Vector2f v_speed) : v_speed_(v_speed) {

    body_.setPosition(position);
    body_.setFillColor(sf::Color::Yellow);
    body_.setRadius(3);
    body_.setOrigin({3,3});

}

void Shell::Render(sf::RenderWindow& l_window) const {

    l_window.draw(body_);
}


void Shell::Update(float time_diff) {

    body_.move( v_speed_ * time_diff );
}

sf::Vector2f Shell::GetPosition() const {

    return body_.getPosition();
}




sf::FloatRect Game::getField() {

    return sf::FloatRect({20, 40}, {600, 300})  ;
};


