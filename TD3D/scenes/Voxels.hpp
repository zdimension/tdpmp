//
// Created by Tom on 21/10/2021.
//

#ifndef TD3D_VOXELS_HPP
#define TD3D_VOXELS_HPP

#include "../vendor/octree/octree.h"

struct BlockType
{
    Color color;
};

static constexpr BlockType DIRT{{100, 70, 36}};

struct Block
{
    BlockType type;
};

class Chunk : public Entity
{
    Octree<Block, 16> tree;

public:
    void draw() const override
    {
        for ( int z = 0; z < ...; ++z ) {
            tmp = octree.zSlice(z);
            for ( int y = 0; y < ...; ++y ) {
                for ( int x = 0; x < ...; ++x ) {
                    ... = tmp(y,x);
                }
            }
        }
    }
};

class Voxels : public Scene<Chunk>
{
public:
    Voxels() : Scene<Chunk>()
    {
    }
};

#endif //TD3D_VOXELS_HPP
