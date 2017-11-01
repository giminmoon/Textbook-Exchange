//
//  Game.cpp
//  Game-mac
//
//  Created by Sanjay Madhav on 5/31/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Game.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include "AnimatedSprite.h"


bool Game::Initialize(){
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) == 0) {
        
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        
        window = SDL_CreateWindow(
            "Lab 7",                  // window title
            SDL_WINDOWPOS_UNDEFINED,           // initial x position
            SDL_WINDOWPOS_UNDEFINED,           // initial y position
            1024,                               // width, in pixels
            768,                               // height, in pixels
            SDL_WINDOW_OPENGL                  // flags - see below
        );
        this->window = window;
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        rend = renderer;
        
        //initialize SDL image
        int flags= IMG_INIT_PNG;
        imageInitialize =IMG_Init(flags);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
//        LoadSound("Assets/Player/Jump.wav");
//        LoadSound("Assets/Coin/coin.wav");
        LoadData();
        
        return 1;
    }
    else{
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 0;
    }
}


void Game::ShutDown(){
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    Mix_CloseAudio();
    
}
void Game::ProcessInput(){
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        /* handle your event here */
         switch (event.type) {
             case SDL_QUIT:
                 condition = false;
                 break;
             default:
                 break;
         }
    }
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_ESCAPE]) {
        condition = false;
    }
    
    //loop over all actors and call processinput on each
    for(int i = 0; i < actors.size(); i++)
    {
            actors[i]->ProcessInput(state);
            actors[i]->ActorInput(state);
    }
    
    
}
void Game::UpdateGame(){

    Uint32 timeout = SDL_GetTicks() + 16;
    while(SDL_TICKS_PASSED(SDL_GetTicks(), timeout)){
    }
    
    float currSeconds = 0;
    currSeconds = SDL_GetTicks() / 1000.0f;
    
    if(currSeconds == 0)
    {
        return;
    }
    
    float deltaTime = currSeconds - prevSeconds;
    deltaTime = 1.0 / 60;

    //shallow copy actors
    std::vector<Actor*> tempActors = actors;
    std::vector<Actor*> deadActors;
    
    for(int i = 0; i < tempActors.size(); i++)
    {
        tempActors[i]->Update(deltaTime);
        //add to dead actors if state is dead
        if(tempActors[i]->GetState() == Actor::EDead)
        {
            deadActors.push_back(tempActors[i]);
        }
    }
    
    //delete deadactors
    for(int i = 0; i < deadActors.size(); i++)
    {
        delete deadActors[i];
    }

   
    prevSeconds = currSeconds;
    
}
void Game::GenerateOutput(){
    
    SDL_SetRenderDrawColor(rend, 34,139,34,255);
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor(rend, 34,139,34,255);
    
    //set background to the image png file we set with texture
    //SDL_RenderCopy(rend, texture, nullptr, nullptr);
    
    for(int i = 0; i < sprites.size(); i++)
    {
        sprites[i]->Draw(rend);
    }

    //output the renderer
    SDL_RenderPresent(rend);

}

void Game::RunLoop(){
    
    while(condition)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
    
}

void Game::AddActor(Actor* newActor)
{
    actors.push_back(newActor);
}

void Game::RemoveActor(Actor* actor)
{
    std::vector<Actor*>::iterator it = find (actors.begin(), actors.end(), actor);
    
    //found it in actors
    if (it != actors.end())
    {
        it = actors.erase(it);
    }
}

// not yet
void Game::LoadData()
{
    LoadTexture("Assets/Airplane.png");
    LoadTexture("Assets/Bullet.png");
    LoadTexture("Assets/TileBrown.png");
    LoadTexture("Assets/TileBrownSelected.png");
    LoadTexture("Assets/TileGreen.png");
    LoadTexture("Assets/TileGrey.png");
    LoadTexture("Assets/TileSelected.png");
    LoadTexture("Assets/TileTan.png");
    LoadTexture("Assets/Tower.png");
    
    Grid* grid = new Grid(this);
    
    mGrid = grid;
    

//    Actor* bg = new Actor(this);
//    Vector2 position3 = Vector2(1024/2,768/2);
//    bg->SetPosition(position3);
//    SpriteComponent* sc3 = new SpriteComponent(bg, 80);
//    sc3->SetTexture(GetTexture("Assets/Background.png"));
//    bg->SetSprite(sc3);
//  
    std::string line;
    std::ifstream myfile ("Assets/Level.txt");
    int row = 0;
    if (myfile.is_open())
    {
        while(getline(myfile,line))
        {
            for(int i = 0; i < line.length(); i++)
            {
//                if(line[i] == 'A')
//                {
//                    Block *blockA = new Block(this);
//                    Vector2 position = Vector2(64*i+32, 32*row+16);
//                    blockA->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockA, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockA.png"));
//                    blockA->SetSprite(sc);
//                }
//                else if(line[i] == 'B')
//                {
//                    Block *blockB = new Block(this);
//                    Vector2 position = Vector2(64*i+32 , 32*row+16);
//                    blockB->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockB, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockB.png"));
//                    blockB->SetSprite(sc);
//                }
//                else if(line[i] == 'C')
//                {
//                    Block *blockC = new Block(this);
//                    Vector2 position = Vector2(64*i+32 , 32*row+16);
//                    blockC->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockC, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockC.png"));
//                    blockC->SetSprite(sc);
//                }
//                else if(line[i] == 'D')
//                {
//                    Block *blockD = new Block(this);
//                    Vector2 position = Vector2(64*i+32, 32*row+16);
//                    blockD->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockD, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockD.png"));
//                    blockD->SetSprite(sc);
//                }
//                else if(line[i] == 'E')
//                {
//                    Block *blockE = new Block(this);
//                    Vector2 position = Vector2(64*i+32, 32*row+16);
//                    blockE->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockE, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockE.png"));
//                    blockE->SetSprite(sc);
//                }
//                else if(line[i] == 'F')
//                {
//                    Block *blockF = new Block(this);
//                    Vector2 position = Vector2(64*i + 32 ,32*row+16);
//                    blockF->SetPosition(position);
//                    SpriteComponent* sc = new SpriteComponent(blockF, 100);
//                    sc->SetTexture(GetTexture("Assets/BlockF.png"));
//                    blockF->SetSprite(sc);
//                }
//                else if (line[i] == 'P')
//                {
//                    player = new Player(this);
//                    Vector2 playerPosition = Vector2(64*i+32 ,32*row + 16);
//                    player->SetPosition(playerPosition);
//                    AnimatedSprite* playerSC = new AnimatedSprite(player,200);
//                    playerSC->SetTexture(GetTexture("Assets/Player/Idle.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run1.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run2.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run3.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run4.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run5.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run6.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run7.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run8.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run9.png"));
//                    playerSC->AddImage(GetTexture("Assets/Player/run10.png"));
//                    player->SetSprite(playerSC);
//                    
//                }
//                else if(line[i] == 'O')
//                {
//                    BarrelSpawner *barrel = new BarrelSpawner(this);
//                    Vector2 position = Vector2(64*i + 32 ,32*row+16);
//                    barrel->SetPosition(position);
//                }
//                else if(line[i] == '*')
//                {
//                    Coin *coin = new Coin(this);
//                    Vector2 position = Vector2(64*i + 32, 32*row);
//                    AnimatedSprite* coinSC = new AnimatedSprite(coin,200);
//                    coinSC->SetTexture(GetTexture("Assets/Coin/coin1.png"));
//                    coin->SetPosition(position);
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin1.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin2.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin3.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin4.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin5.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin6.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin7.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin8.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin9.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin10.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin11.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin12.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin13.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin14.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin15.png"));
//                    coinSC->AddImage(GetTexture("Assets/Coin/coin16.png"));
//                    coin->SetSprite(coinSC);
//                    
//                }
//            }
            }
            row++;
        }
    }
    myfile.close();
    
    
    

}

void Game::UnloadData()
{
    ShutDown();
    while(!actors.empty())
    {
        delete actors.back();
    }
    //destroy texture in all the map
    for (auto it = hashmap.begin(); it != hashmap.end(); ++it )
    {
        SDL_DestroyTexture(it->second);
    }
    hashmap.clear();
    
    for(auto it = sounds.begin(); it!= sounds.end(); ++it)
    {
        Mix_FreeChunk(it->second);
        it->second = NULL;
    }
    sounds.clear();
}

void Game::LoadTexture(std::string filename)
{
    int flags= IMG_INIT_PNG;
    imageInitialize =IMG_Init(flags);
    
    SDL_Texture *NewTexture;
    //convert from String to char *
    image = IMG_Load(filename.c_str());
    NewTexture = SDL_CreateTextureFromSurface(rend, image);
    //add to the hashmap
    std::pair<std::string, SDL_Texture*> element (filename, NewTexture);
    hashmap.insert(element);
}

SDL_Texture* Game::GetTexture(std::string filename)
{
    //attempt to find the element
    std::unordered_map<std::string, SDL_Texture*>::const_iterator map_it = hashmap.find (filename);
    //if found, return the SDL_Texture
    if(map_it != hashmap.end())
    {
        return map_it->second;
    }
    else
    {
        return NULL;
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    //add to vector of sprites
    sprites.push_back(sprite);
    
    //sort
    // mSprites is std::vector<SpriteComponent*>
    std::sort(sprites.begin(), sprites.end(),
              [](SpriteComponent* a, SpriteComponent* b) {
                  return a->GetDrawOrder() < b->GetDrawOrder();
    });
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    std::vector<SpriteComponent*>::iterator vec_it = std::find(sprites.begin(), sprites.end(), sprite);
    //find sprite within vector and delete it
    if(vec_it != sprites.end())
    {
        sprites.erase(vec_it);
    }
}

void Game::LoadSound(const std::string &filename)
{
    Mix_Chunk* sample;
    sample= Mix_LoadWAV(filename.c_str());
    sounds.insert(std::make_pair(filename, sample));
}

Mix_Chunk* Game::GetSound(const std::string& filename)
{
    std::unordered_map<std::string, Mix_Chunk*>::iterator it = sounds.find(filename);
    if(it != sounds.end())
    {
        return it->second;
    }
    else
    {
        return NULL;
    }
}

const Vector2& Game::GetCameraPos() const{
    return mCameraPos;
}















