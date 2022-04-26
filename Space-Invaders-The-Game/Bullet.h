#ifndef CLASS_H
#define CLASS_H

#include "Enemy.h"
#include "Laser.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <random>


int iscore=300;

int randomi(int a, int b){
    static std::random_device d;
    static std::mt19937 r(d());
    std::uniform_int_distribution<std::mt19937::result_type> re(a,b);
    return re(r);
}

//=====================================================================================
class Bullet : public sf::Sprite{
private:
    sf::Texture bull_txt;
    bool to_remove = false;
public:
    void Changepos(int a, int b){
        setPosition(a,b);
    }
    bool To_remove(){
        return to_remove;
    }
    Bullet(const int playerx, const int playery){        // sf::Time &elapsed
        bull_txt.loadFromFile("Textures/bullet.png");
        setTexture(bull_txt);
        setOrigin(bull_txt.getSize().x/2,bull_txt.getSize().y/2);
        setScale(0.5,0.5);
        Changepos(playerx,playery);


    }
    virtual ~Bullet()=default;
    void Boom(std::vector<std::unique_ptr<Ufo>> &ufos, std::vector<std::unique_ptr<Laser>> &lasers){
        for(auto &a : ufos){

            if(a->getGlobalBounds().intersects(getGlobalBounds())){
                a->KilledSound();
                a->Shooted();
                //a->SetTexture();
                iscore+=10;

                to_remove=true;
            }

        }
        for(unsigned int i=0;i<lasers.size();i++){
            if(lasers[i]->getGlobalBounds().intersects(getGlobalBounds())){
                to_remove=true;
                lasers.erase(lasers.begin()+i);
                iscore+=20;

            }
        }

    }

};










#endif // CLASS_H
