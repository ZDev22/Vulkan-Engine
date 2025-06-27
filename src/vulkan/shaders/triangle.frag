#version 450

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in flat uint fragTextureIndex;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 1) uniform sampler2DArray texSampler;

void main() {
    outColor = texture(texSampler, vec3(fragTexCoord, float(fragTextureIndex))) * fragColor;
}