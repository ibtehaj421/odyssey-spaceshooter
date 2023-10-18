#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
using namespace sf;

class Meteor{
 public:
 Texture shape;
 Sprite sprite;
 bool hit;
 Meteor(std::string png){
        srand(time(NULL));
        int r = rand()%400;
        shape.loadFromFile(png);
        sprite.setTexture(shape);
        sprite.setScale(0.7,0.7);
        sprite.setPosition(0,r);
        hit = false;
 }
 void move(){
    sprite.move(2.f,3.f);
 }
 bool bound(){
    if(sprite.getPosition().y >= 760 - 10){
       return true;
    }
    else {
        return false;
    }
 }
 ~Meteor(){

 }
};