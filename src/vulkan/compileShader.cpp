#include <iostream>
#include <string>

bool success;
int result;

bool compileShader(const std::string& inputFile, const std::string& outputFile, const std::string& stage) {
    std::string command = "glslc -fshader-stage=" + stage + " " + inputFile + " -o " + outputFile;
    result = std::system(command.c_str());
    if (result == 0) { return true; }
    else { std::cerr << "Failed to compile " << inputFile << " (exit code: " << result << ")" << std::endl; return false; }
}

bool compile() {
    success = true;
    success &= compileShader("vulkan/shaders/triangle.vert", "vulkan/shaders/triangle.vert.spv", "vert");
    success &= compileShader("vulkan/shaders/triangle.frag", "vulkan/shaders/triangle.frag.spv", "frag");
    return success;
}