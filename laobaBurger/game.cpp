#include "game.h"

using namespace sf;

Game::Game()
{
    Init();
}

Game::~Game()
{

}

void Game::Init()
{
    dir = Down;
    body.push_back(Hanbaoer);
    if (!puke_buffer.loadFromFile("/Users/taodafen/Desktop/laobaBurger/sound/puke.wav"))
        std::cout<<"err"<<std::endl;
    puke_sound.setBuffer(puke_buffer);

    if (!buffer[Baba].loadFromFile("/Users/taodafen/Desktop/laobaBurger/sound/baba.wav"))
        std::cout<<"err"<<std::endl;
    food_sound[Baba].setBuffer(buffer[Baba]);

    if (!buffer[Coudoufu].loadFromFile("/Users/taodafen/Desktop/laobaBurger/sound/coudoufu.wav"))
        std::cout<<"err"<<std::endl;
    food_sound[Coudoufu].setBuffer(buffer[Coudoufu]);

    if (!buffer[Fulu].loadFromFile("/Users/taodafen/Desktop/laobaBurger/sound/fulu.wav"))
        std::cout<<"err"<<std::endl;
    food_sound[Fulu].setBuffer(buffer[Fulu]);

    if (!buffer[Ningmeng].loadFromFile("/Users/taodafen/Desktop/laobaBurger/sound/ningmeng.wav"))
        std::cout<<"err"<<std::endl;
    food_sound[Ningmeng].setBuffer(buffer[Ningmeng]);

    background.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/white.png");
    coudoufu_bg.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/coudoufu.png");
    ningmeng_bg.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/ningmeng.png");
    baba_bg.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/baba.png");
    fulu_bg.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/fulu.png");
    hanbaoer_bg.loadFromFile("/Users/taodafen/Desktop/laobaBurger/pic/hanbaoer.png");

    sprite1.setTexture(background);
    sprite[Coudoufu].setTexture(coudoufu_bg);
    sprite[Ningmeng].setTexture(ningmeng_bg);
    sprite[Baba].setTexture(baba_bg);
    sprite[Fulu].setTexture(fulu_bg);
    sprite[Hanbaoer].setTexture(hanbaoer_bg);

}

void Game::start(sf::RenderWindow &window)
{
    srand(time(0));

    Clock clock;
    float timer = 0, delay = 0.3;

    f[Coudoufu].x=rand()%N;
    f[Coudoufu].y=rand()%M;

    f[Ningmeng].x=rand()%N;
    f[Ningmeng].y=rand()%M;

    f[Baba].x=rand()%N;
    f[Baba].y=rand()%M;

    f[Fulu].x=rand()%N;
    f[Fulu].y=rand()%M;

    while(window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        Event e;
        while(window.pollEvent(e))
        {
            if(e.type == Event::Closed)
            {
                window.close();
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)&&dir!=Right) dir=Left;
        if(Keyboard::isKeyPressed(Keyboard::Right)&&dir!=Left) dir=Right;
        if(Keyboard::isKeyPressed(Keyboard::Up)&&dir!=Down) dir=Up;
        if(Keyboard::isKeyPressed(Keyboard::Down)&&dir!=Up) dir=Down;


        if (timer>delay){timer = 0; Tick();}

        //draw------
        window.clear();

        for(int i=0; i<N; i++)
        {
            for(int j = 0; j<M; j++)
            {
                sprite1.setPosition(i*SIZE,j*SIZE); 
                window.draw(sprite1);
            }
        }

        for(int i=0;i<body.size();i++)
        {
            sprite[body[i]].setPosition(s[i].x*SIZE,s[i].y*SIZE);
            window.draw(sprite[body[i]]);
        }

        sprite[Coudoufu].setPosition(f[Coudoufu].x*SIZE,f[Coudoufu].y*SIZE);
        window.draw(sprite[Coudoufu]);

        sprite[Ningmeng].setPosition(f[Ningmeng].x*SIZE,f[Ningmeng].y*SIZE);
        window.draw(sprite[Ningmeng]);

        sprite[Baba].setPosition(f[Baba].x*SIZE,f[Baba].y*SIZE);
        window.draw(sprite[Baba]);

        sprite[Fulu].setPosition(f[Fulu].x*SIZE,f[Fulu].y*SIZE);
        window.draw(sprite[Fulu]);

        window.display();
    }

}

void Game::Tick()
{
    for(int i=body.size();i>0;--i)
    {
        s[i].x = s[i-1].x;
        s[i].y = s[i-1].y; 
    }

    if(dir==0) s[0].y+=1;
    if(dir==1) s[0].x-=1;
    if(dir==2) s[0].x+=1;
    if(dir==3) s[0].y-=1;

    //found food------
    for(int i = 0; i<FOOD_SIZE; i++)
    {
        if((s[0].x==f[i].x)&&(s[0].y==f[i].y))
        {
            body.push_back(i);
            food_sound[i].play();
            f[i].x = rand()%N;
            f[i].y = rand()%M;
        }
    }

    //eat itself-------
    for(int i = 1;i<body.size();i++)
    {
        if(s[0].x==s[i].x && s[0].y == s[i].y)
        {
            puke_sound.play();
        }
    }

    //hit wall------
    if(s[0].x>N) s[0].x = 0; if(s[0].x<0) s[0].x = N;
    if(s[0].y>M) s[0].y = 0; if(s[0].y<0) s[0].y = M;
}