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

#include "world.h"
#include "mcubes.h"
#include "simplex_noise.h"

//#define CONWAY

extern TexturePool texture_pool;
Mesh* mcube_mesh;
double life_time = 0.0f;


void world_init(World* world, Game* game) {
    fprintf(stdout, "\nWORLD: Loading resources...\n");

    /* Marching Cubes */
	fprintf(stdout, "WORLD: \t\tGenerating world...\n");
#ifdef CONWAY
    world->life = new GameOfLife(20, 20, 20);
    world->life->populate(30);
    world->life->step();
#else
    Grid* grid = new Grid(8, 8, 8);
	simplex_noise(grid);
#endif

	fprintf(stdout, "WORLD: \t\tGenerating marching cubes...\n");
#ifdef CONWAY
    mcube_mesh = MarchingCubeGenerator::generate(world->life->m_current);
#else
	mcube_mesh = MarchingCubeGenerator::generate(grid);
	delete grid;
#endif
    
    // TEXTURES
    fprintf(stdout, "WORLD: \t\tLoading textures...\n");
    texture_pool_allocate(6);
    create_texture(&texture_pool.textures[0], TEXTURE_DIFFUSE);
    create_texture(&texture_pool.textures[1], TEXTURE_NORMAL);
    create_texture(&texture_pool.textures[2], TEXTURE_SPECULAR);
    texture_sampling(&texture_pool.textures[0], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_sampling(&texture_pool.textures[1], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_sampling(&texture_pool.textures[2], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_load(&texture_pool.textures[0], "gold_ore.png");
    texture_load(&texture_pool.textures[1], "gold_ore_n.png");
    texture_load(&texture_pool.textures[2], "gold_ore_s.png");

    create_texture(&texture_pool.textures[3], TEXTURE_DIFFUSE);
    create_texture(&texture_pool.textures[4], TEXTURE_NORMAL);
    create_texture(&texture_pool.textures[5], TEXTURE_SPECULAR);
    texture_sampling(&texture_pool.textures[3], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_sampling(&texture_pool.textures[4], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_sampling(&texture_pool.textures[5], GL_CLAMP_TO_EDGE, GL_LINEAR);
    texture_load(&texture_pool.textures[3], "blocks.png");
    texture_load(&texture_pool.textures[4], "blocks_n.png");
    texture_load(&texture_pool.textures[5], "blocks_s.png");

    fprintf(stdout, "WORLD: \t\tLoading shaders...\n");
    /* PBR Lighting Shader */
    world->pbr_shader.load_file(VERTEX, "light.vert");
    world->pbr_shader.load_file(FRAGMENT, "light.frag");
    world->pbr_shader.compile();

     /* Geometry Pass Shader */
    world->geometry.load_file(VERTEX, "geometry.vert");
    world->geometry.load_file(FRAGMENT, "geometry.frag");
    world->geometry.compile();

    /* Skybox Shader */
    world->sky_shader.load_file(VERTEX, "skybox.vert");
    world->sky_shader.load_file(FRAGMENT, "skybox.frag");
    world->sky_shader.compile();

    /* Island Shader */
    world->island.load_file(VERTEX, "island.vert");
    world->island.load_file(FRAGMENT, "island.frag");
    world->island.compile();

    fprintf(stdout, "WORLD: \t\tConfiguring shaders...\n");
    /* PBR Shader Configuration */
    world->pbr_shader.bind();
    world->pbr_shader.uniform_int("buf_position", 0);
    world->pbr_shader.uniform_int("buf_normal", 1);
    world->pbr_shader.uniform_int("buf_albedo", 2);
    //world->pbr_shader.uniform_int("buf_depth", 3);
    world->pbr_shader.unbind();

    /* Geometry Pass Configuration */
    world->geometry.bind();
    world->geometry.bind_ubo("mvp_mat", 0);
    world->geometry.register_texture(&texture_pool.textures[3], 5);
    world->geometry.register_texture(&texture_pool.textures[4], 6);
    world->geometry.register_texture(&texture_pool.textures[5], 7);
    world->pbr_shader.unbind();

    /* Day/Night Cycle COnfiguration*/
    const vec3 day_sky = {0.0, 0.0, 1.0};
    const vec3 day_hor = {0.32, 0.92, 1.0};
    const vec3 night_sky = {0.0, 0.0, 1.0};
    const vec3 night_hor = {0.32, 0.92, 1.0};
    world->day_cycle.time = 0.0f;
    world->day_cycle.lerp = 0.0f;

    world->sky_shader.bind();
    world->sky_shader.uniform_vec3("day_sky", day_sky);
    world->sky_shader.uniform_vec3("day_hor", day_hor);
    world->sky_shader.uniform_vec3("night_sky", night_sky);
    world->sky_shader.uniform_vec3("night_hor", night_hor);
    world->sky_shader.bind_ubo("mvp_mat", 0);
    world->sky_shader.unbind();

    /* Island Shader Configuration */
    const vec3 top = {0.1f, 0.1f, 0.1f};
    const vec3 bottom = {0.0f, 1.0f, 0.0f};
    world->island.bind();
    world->island.uniform_vec3("top_color", top);
    world->island.uniform_vec3("bottom_color", bottom);
    world->island.unbind();

    // Create Skybox
    cubemap_create(&world->sky_box);

    /* G-buffer Creation */
    Attachment attachments[] = {
            {GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_TEXTURE_2D, GL_NEAREST},      // Position + metallic
            {GL_RGBA16F, GL_RGBA, GL_FLOAT, GL_TEXTURE_2D, GL_NEAREST},      // Normal + roughness
            {GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_TEXTURE_2D, GL_NEAREST},  // Color
            // {GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT, GL_TEXTURE_2D, GL_LINEAR}
    };
    ivec2  size;
    size[0] = WIN_WIDTH;
    size[1] = WIN_HEIGHT;
    framebuffer_create(&world->g_buffer, attachments, 4, size, true);

    /* Screen Quad Creation */
    mesh_quad(&world->frame);

    fprintf(stdout, "WORLD: \t\tConfiguring transformation matrices...\n");
    /* Model View Projection Uniform buffer */
    uniform_buffer_create(&world->mvp_mat, 3 * sizeof(mat4), 0);
    mat4 v_mat;
    mat4 p_mat;

    // PROJECTION MATRIX
    mat4_perspective(p_mat, 45.0f, 0.1f, 100.0f, (float) WIN_WIDTH / (float) WIN_HEIGHT);
    uniform_buffer_store(&world->mvp_mat, 2 * sizeof(mat4), sizeof(mat4), p_mat);

    // VIEW MATRIX
    init_camera(&world->camera);
    get_view(&world->camera, v_mat);
    uniform_buffer_store(&world->mvp_mat, sizeof(mat4), sizeof(mat4), v_mat);

    // TRANSFORM
    transform_default(&world->cube_t);
    world->cube_t.translation[0] = -5.0f;
    world->cube_t.translation[2] = -10.0f;
    fprintf(stdout, "WORLD: \t\tConfigured transformation matrices\n");
}

void world_update(World* world, Game* game, double delta) {

    // Update camera
    move_camera(&world->camera, game->m_window, delta);
    look_camera(&world->camera, game->m_input->cursor_offset);

    /* DAY NIGHT CYCLE */
    day_update(&world->day_cycle, delta);

    /* OTHER UPDATES */
    float t = glfwGetTime();
    float s = sinf(t / 2.0f);

#ifdef CONWAY
    life_time += delta;
    if (life_time >= 1.0f) {
        //printf("%f ", life_time);
        life_time -= 1.0f;
        world->life->step();

        mesh_delete(mcube_mesh);
        mcube_mesh = MarchingCubeGenerator::generate(world->life->m_current);
    }
#endif

    quat q;
    vec3 axis = {0.0f, 1.0f, 0.0f};
    quat_axis_angle(q, axis, s * 360.0f);

    // Cube
    //memcpy(world->cube_t.rotation, q, sizeof(quat));

    // Chunk
    //memcpy(world->chunk_t.rotation, q, sizeof(quat));
}

void world_render(World* world, Game* game, double delta) {
    world_geometry_pass(world);
    world_lighting_pass(world);
    world_sky_pass(world);
}

void world_scene(World* world) {
    mat4 mat;

    bind_texture(&texture_pool.textures[0], 5);
    bind_texture(&texture_pool.textures[1], 6);
    bind_texture(&texture_pool.textures[2], 7);

    //Shader::push(&world->island);
    transform_to_matrix(&world->cube_t, mat);
    uniform_buffer_store(&world->mvp_mat, 0, sizeof(mat4), mat);
    mesh_render(mcube_mesh);
    //Shader::pop();
}

void world_geometry_pass(World* world) {
    mat4 view;

    glViewport(0, 0, world->g_buffer.size[0], world->g_buffer.size[1]);
    framebuffer_bind(&world->g_buffer);

    get_view(&world->camera, view);
    uniform_buffer_store(&world->mvp_mat, sizeof(mat4), sizeof(mat4), view);

    Shader::push(&world->island);
    world_scene(world);
    Shader::pop();

    framebuffer_unbind();
}

void world_lighting_pass(World* world) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Ambient light
    Shader::push(&world->pbr_shader);
    framebuffer_bind_textures(&world->g_buffer, &world->pbr_shader);
    world->pbr_shader.uniform_vec3("eye_pos", world->camera.position);
    day_shader_update(&world->day_cycle, &world->pbr_shader);
    //shader_bind(&world->pbr_shader);
    mesh_render(&world->frame);
    Shader::pop();

    framebuffer_blit_depth(&world->g_buffer);
}

void world_sky_pass(World* world) {
    Shader::push(&world->sky_shader);
    world->sky_shader.uniform_float("percent", world->day_cycle.lerp);
    cubemap_render(&world->sky_box, &world->sky_shader);
    Shader::pop();
}

void world_delete(World* world) {
    // Clean up
    cubemap_delete(&world->sky_box);

    // Meshes
    mesh_delete(&world->frame);
    mesh_delete(mcube_mesh);

    // Framebuffers
    framebuffer_delete(&world->g_buffer);

    // Textures
    texture_delete(&texture_pool.textures[0]);
    texture_delete(&texture_pool.textures[1]);
    texture_delete(&texture_pool.textures[2]);

    // Conway
    delete world->life;

    // Global cleanup
    texture_pool_delete();
}
