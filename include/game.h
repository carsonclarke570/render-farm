/*
    Copyright 2020 Carson Clarke-Magrab

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _GAME_H_
#define _GAME_H_

#include "input.h"
#include "window.h"

class Game {
public:
    Window* m_window;
    Input* m_input;

    /**
     *  Constructs a new Game object.
     */
    Game();

    /**
     *  Destroys a Game object.
     */
    ~Game();

    /**
     *  Initializes the game.
     */
    virtual void init() = 0;

    /**
     *  Controls the update logic of the game.
     * 
     *  @param delta    The time passed in seconds since the last update. 
     */
    virtual void update(double delta) = 0;

    /**
     *  Controls the render logic of the game.
     * 
     *  @param delta    The time passed in seconds since the last render. 
     */
    virtual void render(double delta) = 0;

    /**
     *  Cleans up the resources in the game.
     */
    virtual void cleanup() = 0;
};

#endif