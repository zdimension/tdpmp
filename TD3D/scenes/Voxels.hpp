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

static constexpr BlockType EMPTY{{.a = 0}};
static constexpr BlockType DIRT{{100, 70, 36}};

struct Block
{
    BlockType type;
};

class Chunk : public Entity
{
    static constexpr int CHUNK_SIZE = 16;
public:
    Octree<Block> tree{CHUNK_SIZE, {EMPTY}};

    void draw() const override
    {
        Cube drawCube{{1, 1, 1}, {0, 0, 0}, {0, 0, 0}};
        for ( int z = 0; z < CHUNK_SIZE; ++z ) {
            auto tmp = tree.zSlice(z);
            for ( int y = 0; y < CHUNK_SIZE; ++y ) {
                for ( int x = 0; x < CHUNK_SIZE; ++x ) {
                    auto& truc = tmp(y,x);
                    if (truc.type.color.a != 0)
                    {
                        drawCube.color = {truc.type.color};
                        drawCube.position = {0.5 + x, 0.5 + y, 0.5 + z};
                        drawCube.draw();
                    }
                }
            }
        }
    }

    void update(Uint32 elapsed) override
    {

    }
};

class Voxels : public Scene<Chunk>
{
public:
    Voxels() : Scene<Chunk>()
    {
        auto chunk = add({});
        chunk->tree(1, 1, 1) = {{DIRT}};
    }
};

#endif //TD3D_VOXELS_HPP
