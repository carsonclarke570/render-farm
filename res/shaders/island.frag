#version 330 core
layout (location = 0) out vec4 buf_position; // Metal
layout (location = 1) out vec4 buf_normal;  // Roughness
layout (location = 2) out vec3 buf_albedo;

// Fragment data
in S_VAR {
    vec3 position;
    vec3 normal;
    vec3 world_normal;
} fs_in;

uniform vec3 top_color;
uniform vec3 bottom_color;

vec3 get_color() {
    float a = (normalize(fs_in.normal).y + 1.0f) / 2.0f;
    return mix(bottom_color, top_color, a);
}

void main() {
    buf_position.rgb = fs_in.position;
    buf_position.a = 1.0;
    buf_normal.rgb = normalize(fs_in.world_normal);
    buf_normal.a = 0.1;
    buf_albedo.rgb = get_color().xyz;
}

