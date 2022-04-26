#ifndef SHIELD_H
#define SHIELD_H

#include "Bullet.h"
#include "Laser.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>


class Shield : public sf::Sprite{
private:
    sf::Texture shield_txt;
    sf::SoundBuffer shield_b;
    sf::Sound shield_s;
public:
    int lives = 7;
    Shield(int a, int b){
        shield_txt.loadFromFile("Textures/shields.png");
        setTexture(shield_txt);
        setScale(1.7,1.7);
        setTextureRect(sf::IntRect(0,0,70,20));
        setPosition(a,b);
        shield_b.loadFromFile("Sounds/Bomb+1.wav");
        shield_s.setBuffer(shield_b);
    }
    virtual ~Shield()=default;
    void Lives(std::vector<std::unique_ptr<Bullet>> &bullets, std::vector<std::unique_ptr<Laser>> &lasers,
               std::vector<std::unique_ptr<Ufo>> &ufos){
        if(lives<=6){
            setTextureRect(sf::IntRect(0,0,70,20));
        }

        if(lives<=4){
            setTextureRect(sf::IntRect(0,20,70,20));
        }
        if(lives<=3){
            setTextureRect(sf::IntRect(0,40,70,20));
        }
        if(lives<=2){
            setTextureRect(sf::IntRect(0,60,70,20));
        }
        if(lives<=1){
            setTextureRect(sf::IntRect(0,80,70,20));
        }
        // bullets
        for(unsigned int b=0;b<bullets.size();b++){
            if(bullets[b]->getGlobalBounds().intersects(getGlobalBounds())){
                bullets.erase(bullets.begin()+b);
                lives--;
            }
        }
        //lasers
        for(unsigned int b=0;b<lasers.size();b++){
            if(lasers[b]->getGlobalBounds().intersects(getGlobalBounds())){
                lasers.erase(lasers.begin()+b);
                lives--;
            }
        }
        //ufos
        for(unsigned int b=0;b<ufos.size();b++){
            if(ufos[b]->getGlobalBounds().intersects(getGlobalBounds())){
                lives=0;
            }
        }

    }
    void Sound(){
        shield_s.play();
    }
};
#endif // SHIELD_H
