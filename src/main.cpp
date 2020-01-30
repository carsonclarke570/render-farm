#include <mesh.h>
#include <window.h>
#include <shader.h>
#include <texture.h>
#include <matrix.h>
#include <transform.h>
#include "world.h"

extern TexturePool texture_pool;

World world;

class Sample : public Game {
public:
    Sample() : Game() {}

    void init() {
        world_init(&world, (Game*) this);
    }

    void update(double delta) {
        world_update(&world, (Game*) this, delta);
    }

    void render(double delta) {
        world_render(&world, (Game*) this, delta);
    }

    void cleanup() {
        world_delete(&world);
    }
};


int main() {

    // Start Up Code
    Sample* game = new Sample();

    int err;
    if ((err = engine_init(game))) return err;

    engine_run(game);

    delete game;

    return CODE_SUCCESS;
}