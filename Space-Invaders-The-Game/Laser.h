#ifndef LASER_H
#define LASER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>


class Laser : public sf::Sprite{
private:
    sf::Texture laser_txt;
    bool to_remove=false;
public:
    void Changepos(int a, int b){
        setPosition(a,b);
    }

    Laser(const int playerx, const int playery){        // sf::Time &elapsed
        laser_txt.loadFromFile("Textures/laser.png");
        setTexture(laser_txt);
        setOrigin(laser_txt.getSize().x/2,laser_txt.getSize().y/2);
        setScale(0.5,0.5);
        Changepos(playerx,playery);


    }
    virtual ~Laser()=default;
    bool To_remove(){
        return to_remove;
    }


};


#endif // LASER_H
