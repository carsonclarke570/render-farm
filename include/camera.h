/*
    Copyright 2019 Carson Clarke-Magrab

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

#ifndef CAMERA_H
#define CAMERA_H

#include "matrix.h"
#include "vector.h"
#include "window.h"
#include "common.h"

typedef struct Camera_t {
    // Camera attributes
    vec3 position;
    vec3 up;
    vec3 right;
    vec3 front;

    // Euler angles
    float yaw;
    float pitch;

    // Camera options
    float speed;
    float sensitivity;

} Camera;

/**
 * Initializes the Camera.
 *
 * @param camera    Pointer to Camera struct
 */
void init_camera(Camera *camera);

/**
 * Generates a view matrix from the camera data.
 *
 * @param camera    Pointer to Camera struct
 * @param view      Resulting view matrix.
 */
void get_view(Camera *camera, mat4 view);

/**
 * Moves the camera.
 *
 * @param camera    Pointer to Camera struct
 * @param window    Pointer to window to get input from
 * @param delta     Time passed since last update.
 */
void move_camera(Camera *camera, Window *window, float delta);

/**
 * Makes the camera look.
 *
 * @param camera    Pointer to Camera struct
 * @param offset    The offset from the last update
 */
void look_camera(Camera *camera, vec2 offset);

#endif
