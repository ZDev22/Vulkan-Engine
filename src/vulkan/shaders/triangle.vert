#version 450

// Input vertex attributes
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec4 inColor;
layout(location = 2) in vec2 inTexCoord;

// Output to fragment shader
layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;

// Push constant for projection matrix
layout(push_constant) uniform PushConstants {
    mat4 projection;
} push;

// Define the SpriteData struct OUTSIDE the buffer block
struct SpriteData {
    vec2 translation;
    vec2 scale;
    vec4 color;
    float rotation;
};

// Correct buffer block using the pre-defined struct
layout(set = 0, binding = 0) readonly buffer SpriteDataBuffer {
    SpriteData sprites[];
};

void main() {
    uint instanceIndex = gl_InstanceIndex;

    vec2 translation = sprites[instanceIndex].translation;
    vec2 scale = sprites[instanceIndex].scale;
    float rotation = radians(sprites[instanceIndex].rotation);

    mat2 rotMatrix = mat2(
        cos(rotation), -sin(rotation),
        sin(rotation), cos(rotation)
    );

    vec2 transformedPos = rotMatrix * (inPosition * scale) + translation;

    gl_Position = push.projection * vec4(transformedPos, 0.0, 1.0);
    fragColor = sprites[instanceIndex].color;
    fragTexCoord = inTexCoord;
}