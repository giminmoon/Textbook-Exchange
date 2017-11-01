#pragma once
#ifndef GAME_H
#define GAME_H
#include <iostream>

#include "Actor.h"
#include <algorithm>
#include <unordered_map>
#include <algorithm>
#include "Player.h"
#include "SDL/SDL_mixer.h"
#include "Grid.h"
#include "Plane.h"


class Game{
    
public:
    SDL_Window* window;
    SDL_Renderer* rend;
    
    
    int direction = 0;
    float prevSeconds;
    bool condition = true;
    int imageInitialize;
    SDL_Texture *texture;
    SDL_Surface *image;
    std::vector<Actor*> actors;
    std::unordered_map<std::string, SDL_Texture*> hashmap;
    std::vector<SpriteComponent*> sprites;
    
    std::unordered_map<std::string, Mix_Chunk*> sounds;
    SDL_Point velocity = {250, 250};
    
    Grid* mGrid;
    const Vector2& GetCameraPos() const;
    void SetCameraPos(const Vector2& cameraPos) {mCameraPos = cameraPos;};
    Vector2 mCameraPos;
    Player* player;
    bool Initialize();
    void ShutDown();
    void RunLoop();
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void AddActor(Actor* newActor);
    void RemoveActor(Actor* actor);
    void LoadData();
    void UnloadData();
    void LoadTexture(std::string filename);
    SDL_Texture* GetTexture(std::string filename);
    void AddSprite(SpriteComponent* sprite);
    void RemoveSprite(SpriteComponent* sprite);
    void LoadSound(const std::string& filename);
    Mix_Chunk* GetSound(const std::string& filename);
    Player* GetPlayer(){return player;};
    std::vector<Plane*> planes;
};
#endif
// TODO

