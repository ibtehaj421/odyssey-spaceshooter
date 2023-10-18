#include <SFML/Graphics.hpp>
#include<string.h>
#include <iostream>
using namespace sf;
class PowerUp{
    public:
    Texture shape;
    std::string type;
    Sprite power;
    int x,y;
    bool hit;
    PowerUp(){
        //nothing to be done here.
    }
    virtual void setDetails(std::string png,int xpos,int ypos)=0;
        // nothing to be done here.
    
    virtual void Hit(Sprite &s,bool &op)=0;
        //nothing to be done here.
    
     virtual ~PowerUp(){
        // nothing to be done here.
    }
};
class health: public PowerUp{
    public:
    health(){
        type = "health";
    }
    void setDetails(std::string png,int xpos,int ypos){
        shape.loadFromFile(png);
        power.setTexture(shape);
        x = xpos;
        y = ypos;
        power.setPosition(x,y);
        power.setScale(0.7,0.7);
    }
    void Hit(Sprite &sprite,bool &op){
        if(sprite.getPosition().x < power.getPosition().x + power.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width > power.getPosition().x && sprite.getPosition().y < power.getPosition().y + power.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height > power.getPosition().y){
            op = true;
    }
    }
    ~health(){
        std::cout<<"health"<<std::endl;
        //delete the power object.
    }
};
class sheild: public PowerUp{
    public:
    sheild(){
        type = "sheild";
    }
    void setDetails(std::string png,int xpos,int ypos){
        shape.loadFromFile(png);
        power.setTexture(shape);
        x = xpos;
        y = ypos;
        power.setPosition(x,y);
        power.setScale(0.7,0.7);
    }
    void Hit(Sprite &sprite,bool &op){
        if(sprite.getPosition().x < power.getPosition().x + power.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width > power.getPosition().x && sprite.getPosition().y < power.getPosition().y + power.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height > power.getPosition().y){
            op = true;
    }
    }
    ~sheild(){
        std::cout<<"sheild"<<std::endl;
        //delete the power object.
    }
};
class rFire: public PowerUp{
    public:
    rFire(){
        type = "frenzy";
    }
    void setDetails(std::string png,int xpos,int ypos){
        shape.loadFromFile(png);
        power.setTexture(shape);
        x = xpos;
        y = ypos;
        power.setPosition(x,y);
        power.setScale(0.7,0.7);
    }
    void Hit(Sprite &sprite,bool &op){
        if(sprite.getPosition().x < power.getPosition().x + power.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width > power.getPosition().x && sprite.getPosition().y < power.getPosition().y + power.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height > power.getPosition().y){
            op = true;
    }
    }
    ~rFire(){
        std::cout<<"frenzy"<<std::endl;
        //delete the power object.
    }
};
class fireup: public PowerUp{
    public:
    fireup(){
        type = "fire";
    }
    void setDetails(std::string png,int xpos,int ypos){
        shape.loadFromFile(png);
        power.setTexture(shape);
        x = xpos;
        y = ypos;
        power.setPosition(x,y);
        power.setScale(0.7,0.7);
    }
    void Hit(Sprite &sprite,bool &op){
        if(sprite.getPosition().x < power.getPosition().x + power.getGlobalBounds().width && sprite.getPosition().x + sprite.getGlobalBounds().width > power.getPosition().x && sprite.getPosition().y < power.getPosition().y + power.getGlobalBounds().height && sprite.getPosition().y + sprite.getGlobalBounds().height > power.getPosition().y){
            op = true;
    }
    }
    ~fireup(){
        std::cout<<"fire"<<std::endl;
    }
};
