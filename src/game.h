#pragma once

#include <SFML/Graphics.hpp>

#include "tank.h"
#include "target.h"
#include "aitank.h"
#include "obstacle.h"

#include <memory>
#include <vector>




class Game {

    enum class State {
        
        MENU,
        PAUSED,
        RUNNING,
        DISPLAY_RESULT,
        DISPLAY_HELP,
    };

    enum class Result {

        WIN,
        LOST, 
        DRAW
    };


    public:

        Game() ;

        void run() ;

    private:

        void handleInput() ;
        void update() ;
        void render() ;


        void spawnItems() ;
        void checkShellsTargetsCollisions() ;

        void checkShellsTanksCollisions() ;
        void checkShellsObstaclesCollisions() ;
        
        void updateStatus() ;

        sf::FloatRect getField();


        void InitNewGame() ;

        sf::RenderWindow window_;       
        sf::Clock clock_;

        // ---------------  Items ----------------- //

        Tank tank_;

        std::list<Shell> shells_;

        std::list<std::shared_ptr<Target>> targets_ ;

        AItank enemy_;
        std::list<Shell> enemy_shells_;


        sf::Font font_;
        sf::Text status_text_0;
        sf::Text status_text_1;

        sf::Clock clock1_;
        sf::Time game_time_;
        sf::Text time_str_;

        sf::RectangleShape terrain_;

        std::vector<std::shared_ptr<Obstacle>> obstacles_;


        sf::View view_;

        State state_ = State::MENU;

        float game_duration_ = 60.f;

        // ---------------  Handle FullScreen ----------------- //

        void ToggleFullScreen() ;
        bool is_full_screen = false;


        // ---------------  Menu ----------------- //


        void PrepareMenu() ;
        void RenderMenu() ;


        sf::Text menu_text0_;
        sf::Text menu_text1_;
        sf::Image image0_;
        sf::Texture texture0_;
        sf::Sprite sprite0_;


        // ---------------  Pause ----------------- //

        void PreparePause();
        void RenderPause();

        sf::Text menu_text2_;
        sf::Text menu_text3_;
        sf::RectangleShape pause_terrain_;
        

        // ---------------  Result ----------------- //

        sf::Text result_text4_;
        sf::Clock clock2_;

        void PrepareResult();
        void RenderResult();

        

        // ---------------  Sounds ----------------- //

        sf::SoundBuffer buffer0_;
        sf::SoundBuffer buffer1_;
        sf::Sound sound0_;
        sf::Sound sound1_;

        void LoadSounds();

        // ---------------  Help ----------------- //

        sf::Text help_text_;
        void PrepareHelp();
        void RenderHelp();


    friend class Tank; 
    friend class AItank;
    
};
