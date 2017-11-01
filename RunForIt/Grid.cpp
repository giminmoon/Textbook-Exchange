#include "Grid.h"
#include "Tile.h"
#include <SDL/SDL.h>
#include <algorithm>
#include <iostream>
#include "Game.h"



Grid::Grid(class Game* game)
	:Actor(game)
	,mSelectedTile(nullptr)
{
	// 7 rows, 16 columns
	mTiles.resize(NumRows);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NumCols);
	}
	
	// Create tiles
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			mTiles[i][j] = new Tile(GetGame());
			mTiles[i][j]->SetPosition(Vector2(TileSize/2.0f + j * TileSize, StartY + i * TileSize));
		}
	}
	
	// Set start/end tiles
	GetStartTile()->SetTileState(Tile::EStart);
	GetEndTile()->SetTileState(Tile::EBase);
	
	// Set up adjacency lists
	for (size_t i = 0; i < NumRows; i++)
	{
		for (size_t j = 0; j < NumCols; j++)
		{
			if (i > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i-1][j]);
			}
			if (i < NumRows - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i+1][j]);
			}
			if (j > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j-1]);
			}
			if (j < NumCols - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j+1]);
			}
		}
	}
    
    if(TryFindPath())
    {
        UpdatePathTiles();
    }
}

void Grid::SelectTile(size_t row, size_t col)
{
	// Make sure it's a valid selection
	Tile::TileState tstate = mTiles[row][col]->GetTileState();
	if (tstate != Tile::EStart && tstate != Tile::EBase)
	{
		// Deselect previous one
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

Tile* Grid::GetStartTile()
{
	return mTiles[3][0];
}

Tile* Grid::GetEndTile()
{
	return mTiles[3][15];
}

void Grid::ActorInput(const Uint8 * keyState)
{
	// Process mouse click to select a tile
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
   
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		// Calculate the x/y indices into the grid
		y -= static_cast<int>(StartY - TileSize / 2);
		if (y >= 0)
		{
			x /= static_cast<int>(TileSize);
			y /= static_cast<int>(TileSize);
			if (x >= 0 && x < static_cast<int>(NumCols) && y >= 0 && y < static_cast<int>(NumRows))
			{
				SelectTile(y, x);
			}
		}
	}
    
    if(keyState[SDL_SCANCODE_SPACE])
    {
        //finding leading edge
        if(!mSpacePressed && mSelectedTile)
        {
            mNeedToBuild = true;
            mSpacePressed = true;
        }
        else{
            mSpacePressed = true;
            
        }
    }
    else{
        mSpacePressed = false;
    }

}

void Grid::UpdateActor(float deltaTime)
{
    if(mNeedToBuild)
    {
        Buildtower(mSelectedTile);
        mNeedToBuild = false;
    }
    timer -= deltaTime;
    if(timer <= 0.0f)
    {
        Plane* plane = new Plane(mGame);
        Vector2 position = GetStartTile()->GetPosition();
        plane->SetPosition(position);
        SpriteComponent* sc = new SpriteComponent(plane, 200);
        sc->SetTexture(GetGame()->GetTexture("Assets/Airplane.png"));
        plane->SetSprite(sc);
        timer = 1.0f;
    }
    
}

bool Grid::TryFindPath()
{
    //resetting
    for(unsigned int i = 0 ; i < mTiles.size(); i++)
    {
        for(unsigned int j = 0; j < mTiles[i].size(); j++)
        {
            mTiles[i][j]->mInClosedSet = false;
            mTiles[i][j]->g = 0.0f;
        }
    }
    
    Tile* current = GetEndTile();
    std::vector<Tile*> openSet;
    //set bool to true if the tile is in closedset
//    For the open set, we need operations to:
//    – Test for membership (is the node in the open set?)
//        – Find the lowest cost node
//        • We’ll just use a vector in our code
//
    current->mInClosedSet = true;
    while(current != GetStartTile())
    {
        for(unsigned int i = 0; i < current->mAdjacent.size(); i++)
        {
            //check if ClosedSet contains n
            if(current->mAdjacent[i]->mInClosedSet)
            {
                continue;
            }
            else if(std::find(openSet.begin(), openSet.end(), current->mAdjacent[i]) != openSet.end())
            {
                if(current->g + TileSize < current->mAdjacent[i]->g)
                {
                    current->mAdjacent[i]->mParent = current;
                    current->mAdjacent[i]->g = current->g + TileSize;
                    current->mAdjacent[i]->f = current->mAdjacent[i]->g + current->mAdjacent[i]->h;
                }
            }
            // not in the open set
            else{
                current->mAdjacent[i]->mParent = current;
                                current->mAdjacent[i]->g = current->g + TileSize;
                float heru = std::abs(current->mAdjacent[i]->GetPosition().x - GetStartTile()->GetPosition().x)+std::abs(current->mAdjacent[i]->GetPosition().y - GetStartTile()->GetPosition().y);
                current->mAdjacent[i]->h = heru;
                current->mAdjacent[i]->f = current->mAdjacent[i]->g + current->mAdjacent[i]->h;
                // dont add if its blocked
                if(!current->mAdjacent[i]->mBlocked){
                    openSet.push_back(current->mAdjacent[i]);
                }
            }
        }
        if(openSet.size() == 0)
        {
            //no path if we can't there is nothing in the openset anymore
            return false;
        }
        //finds lowest and erases it
        current = findLowest(openSet);
        current->mInClosedSet = true;
    }
    return true;
}

Tile* Grid::findLowest(std::vector<Tile*>& openSet)
{
    float minimum = std::numeric_limits<float>::max();
    Tile* min = nullptr;
    int index = 0;
    for(unsigned int i = 0; i < openSet.size(); i++)
    {
        if(minimum > openSet[i]->f)
        {
            min = openSet[i];
            minimum = openSet[i]->f;
            index = i;
        }
    }
    openSet.erase(openSet.begin()+index);
    return min;
}

void Grid::UpdatePathTiles()
{
    for(int i = 0; i < mTiles.size(); i++)
    {
        for(int j = 0; j < mTiles[i].size();j++)
        {
            if(mTiles[i][j] != GetEndTile() && mTiles[i][j] != GetStartTile())
            {
                mTiles[i][j]->SetTileState(Tile::EDefault);
            }
        }
    }
    Tile* temp = GetStartTile();
    
    while(temp != GetEndTile()){
        
        temp->SetTileState(Tile::EPath);
        temp= temp->mParent;
    }
    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);
    
}
void Grid::Buildtower(Tile* selectedTile)
{
    if(selectedTile && !selectedTile->mBlocked)
    {
        selectedTile->mBlocked = true;
        while(!TryFindPath())
        {
            selectedTile->mBlocked = false;
        }
        UpdatePathTiles();
        Tower* tower = new Tower(GetGame());
        Vector2 position = selectedTile->GetPosition();
        tower->SetPosition(position);
        SpriteComponent* sc = new SpriteComponent(tower, 200);
        sc->SetTexture(GetGame()->GetTexture("Assets/Tower.png"));
    }
}
