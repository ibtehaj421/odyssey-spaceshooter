#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;


class Bullet{
	public:
	//int delay; // delay timer for a bullet such that bullets are not made consecutively and with a delay.
	Sprite bul;
	int x;
	int y;
	bool hit;
	Bullet(){
		//nothing to be done here.
	}
	Bullet(sf::Texture &laser, int x,int y){
		bul.setTexture(laser);
		this->x = x +34;
		this->y = y - 17;
		bul.setPosition(sf::Vector2f(x,y));
		bul.setScale(0.7f,0.7f);
		
	}
	~Bullet(){

	}
};