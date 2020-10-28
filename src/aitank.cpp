#include "aitank.h"

#include <iostream>

#include "game.h"

#define PI 3.14159265

AItank::AItank(sf::Vector2f position, sf::Color color, sf::Color color1, sf::Color color2, Game * p_game) : Tank(position, color, color1, color2, p_game) {};

void AItank::Update(float time_diff) {


    /*

    if (clock_.getElapsedTime().asSeconds() < 3.0) {
        return;
    }

    clock_.restart();

    //float angle_ = Tank::corpus_.getRotation();

    //std::cout << angle_ << std::endl;
    //std::cout << p_game_->tank_.GetRotation() << std::endl;


    sf::Vector2f dv = p_game_->tank_.GetPosition() -  corpus_.getPosition() ;

    //std::cout << dv.x << " : " << dv.y << std::endl;

    float rot_angle = calc_angle(dv, {static_cast<float>(cos (angle_ * PI/180)), static_cast<float>(sin (angle_ * PI/180) )}) * 180 / PI ;

    //std::cout <<  rot_angle << std::endl;


    if (abs(rot_angle) > 30 ) {

        rot_angle > 0 ? Rotate(-30) : Rotate(30);
        return;
    } 

    Rotate(-rot_angle);

    Fire();

    */

    Tank::Update(time_diff);

    if (clock_.getElapsedTime().asSeconds() < 3.0) {
        return;
    }

    clock_.restart();

    sf::Vector2f dv = p_game_->tank_.GetPosition() -  corpus_.getPosition() ;

    float rot_angle = calc_angle(dv, {static_cast<float>(cos (angle_ * PI/180)), static_cast<float>(sin (angle_ * PI/180) )}) * 180 / PI ;

    if (abs(rot_angle) > 30 ) {

        rot_angle > 0 ? Rotate(-30) : Rotate(30);
        Stop();
        return;
    } 

    Rotate(-rot_angle);

    Move(25);

    Fire();

}


float AItank::calc_angle(sf::Vector2f v1, sf::Vector2f v2) {

    float dot = v1.x * v2.x + v1.y * v2.y;
    float det = v1.x * v2.y - v1.y * v2.x;

    return atan2(det, dot);
}


 void AItank::Fire() {

    p_game_->enemy_shells_.push_back(Tank::Fire()) ;

    //std::cout << "ai tank fire" << std::endl;

 };