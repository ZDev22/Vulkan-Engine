#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;

struct SpriteData {
    vec2 translation;
    vec2 scale;
    vec4 color;

    uint textureIndex;
    float rotation;
};

layout(std140, binding = 0) readonly buffer SpriteDataBuffer {
    SpriteData sprites[];
};

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) flat out uint textureId;

void main() {
    SpriteData sprite = sprites[gl_InstanceIndex];

    vec2 scaled = inPosition * sprite.scale;
    vec2 rotated = vec2(
        scaled.x * cos(sprite.rotation) - scaled.y * sin(sprite.rotation),
        scaled.x * sin(sprite.rotation) + scaled.y * cos(sprite.rotation)
    );

    gl_Position = vec4(sprite.translation + rotated, 0.0, 1.0);

    fragColor = sprite.color;
    fragTexCoord = inTexCoord;
    //textureId = sprite.textureIndex;
}