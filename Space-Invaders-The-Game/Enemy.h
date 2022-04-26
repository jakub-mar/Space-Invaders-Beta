#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>

class Ufo : public sf::Sprite{
private:
    sf::Texture ufo_txt;
    sf::Texture ufo_2_txt;
    // Killed sound
    sf::SoundBuffer killed_b;
    sf::Sound killed_s;
    bool shooted = false;
public:
    void SetTexture(){
        setTexture(ufo_2_txt);
    }
    int dir = 20;
    void ChangeVel(){
        dir=-dir;
    }
    void Shooted(){
        shooted=true;
    }
    bool isShooted(){
        return shooted;
    }
    Ufo(int xpos,int ypos){
        ufo_txt.loadFromFile("Textures/enemy.png");
        ufo_2_txt.loadFromFile("Textures/enemy_2.png");
        ufo_txt.setSmooth(true);
        setTexture(ufo_txt);
        setScale(0.093,0.124);
        setPosition(xpos,ypos);
        killed_b.loadFromFile("Sounds/invaderkilled.wav");
        killed_s.setBuffer(killed_b);
        killed_s.setVolume(20);


    }
    virtual ~Ufo()=default;
    void KilledSound(){
        killed_s.play();
    }
    void Accelerate(){
        dir=dir*1.3;
    }

};

#endif // ENEMY_H
