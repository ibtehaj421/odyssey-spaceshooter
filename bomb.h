#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;


class Bomb{
	public:
	//int delay; // delay timer for a bullet such that bullets are not made consecutively and with a delay.
	Sprite bul;
	int x;
	int y;
	bool hit;
	Bomb(){
		//nothing to be done here.
	}
	Bomb(sf::Texture &bomb, int x,int y){
		bul.setTexture(bomb);
		this->x = x +34;
		this->y = y - 17;
		bul.setPosition(sf::Vector2f(x,y));
		bul.setScale(0.6f,0.6f);
		
	}
	~Bomb(){

	}
};