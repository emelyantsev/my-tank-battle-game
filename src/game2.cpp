
#include "game.h"


void Game::InitNewGame() {


    std::srand(std::time(nullptr));

    tank_ = Tank(  sf::Vector2f{ static_cast<float>(20. + std::rand() % 150),  static_cast<float>(40. + std::rand() % 300 ) } ,
            sf::Color(150, 40, 40), 
            sf::Color(200, 20, 30), 
            sf::Color(200, 20, 30),
            this ),
    

    enemy_ = AItank(sf::Vector2f{ static_cast<float>(320. + std::rand() % 150),  static_cast<float>(40. + std::rand() % 300 ) } , 
        sf::Color(50, 50, 250), sf::Color(0, 0, 250), sf::Color(0, 0, 250), this) ;


    enemy_.Rotate(180);


    targets_.clear();
    shells_.clear();
    enemy_shells_.clear();
    obstacles_.clear();

    spawnItems();

    clock1_.restart();
    game_time_ = clock1_.getElapsedTime() ;

    
}


void Game::spawnItems() {

    //std::srand(std::time(nullptr));


    while (obstacles_.size() < 2) {


        std::shared_ptr<Obstacle> p_new_obstacle(new WaterObstacle(
            
                { static_cast<float>(40. + std::rand() % 580),  static_cast<float>(60. + std::rand() % 280 ) } ,

                std::rand() % 2 == 0 ? 
                sf::Vector2f{20.f + static_cast<float>(std::rand() % 10) , 40.f + static_cast<float>(std::rand() % 20)} :
                sf::Vector2f{40.f + static_cast<float>(std::rand() % 20), 20.f + static_cast<float>(std::rand() % 10) }   
                ) 
        );


        if (p_new_obstacle->GetBounds().intersects(tank_.GetBounds() ) || p_new_obstacle->GetBounds().intersects(enemy_.GetBounds() )) {
            continue;
        }

        obstacles_.push_back(p_new_obstacle);
        
    }



    while (obstacles_.size() < 4) {


        std::shared_ptr<Obstacle> p_new_obstacle(new SolidObstacle(
            
                { static_cast<float>(40. + std::rand() % 580),  static_cast<float>(60. + std::rand() % 280 ) } ,
                std::rand() % 2 == 0 ? 
                sf::Vector2f{20.f + static_cast<float>(std::rand() % 10) , 40.f + static_cast<float>(std::rand() % 20)} :
                sf::Vector2f{40.f + static_cast<float>(std::rand() % 20), 20.f + static_cast<float>(std::rand() % 10) }   
                ) 
        );


        if (p_new_obstacle->GetBounds().intersects(tank_.GetBounds() ) || p_new_obstacle->GetBounds().intersects(enemy_.GetBounds() )) {
            continue;
        }

        obstacles_.push_back(p_new_obstacle);
        
    }


/*

    obstacles_.push_back(

            std::shared_ptr<Obstacle>(new SolidObstacle(
                {450.f, 200.f},
                {20.f, 40.f}, 
                sf::Color(150, 150, 150)
                ) 
            )
        );
*/





    for (int i = 0 ; i < 8 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new SimpleTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300 ) }  )  ) );
    }

    for (int i = 0 ; i < 4 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new AdvancedTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300  ) }  )  ) );
    }


    for (int i = 0 ; i < 2 ; ++i) {

        targets_.push_back( std::shared_ptr<Target>(new StarTarget(  { static_cast<float>(20. + std::rand() % 600),  static_cast<float>(40. + std::rand() % 300  ) }  )  ) );
    }

}