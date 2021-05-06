//
// Created by Asus on 2021/4/28.
//
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// 窗口大小调整时调用
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

// 使用一个函数处理输入控制
void processInput(GLFWwindow* window){
    // 按下 ESC 退出
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// 顶点着色器
const char *vertexShaderSource =
        "#version 330 core \n"
        "layout (location=0) in vec3 aPos;\n"
        "void main() { \n"
        "    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

// 片段着色器
const char *fragmentShaderSource =
        "#version 330 core \n"
        "out vec4 FragColor; \n"
        "void main() { \n"
        "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \n"
        "} \0";

int main()
{
    glfwInit();

    // 使用 glfwWindowHint 配置 glfw,第一个参数为枚举值，第二个参数为设置这个选项的值
    // 设置 OpenGL 版本 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // 设置 OpenGL 模式为 Core-profile 核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Mac OS X 系统
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 创建窗口
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 将窗口 window 的上下文设置为当前进程的主上下文
    glfwMakeContextCurrent(window);

    // init glad
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 设置视口 viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 顶点数组对象 VAO -- 顶点缓冲对象 VBO -- 索引缓冲对象 EBO/IBO
    // 顶点着色器,图元装配 --> 几何着色器,光栅化 --> 片段着色器,混合
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);     // 链接着色器源码
    glCompileShader(vertexShader);                                  // 编译着色器

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // 检测编译是否成功
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 着色器程序
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检测链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // glUseProgram(shaderProgram);    // 激活着色器程序
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
    };

    // VAO
    // -------  VAO 绘制物体过程  -------
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);                  // 缓冲ID 对应 缓冲对象VBO
    // -------  VBO 绘制物体过程  -------
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     // 绑定缓冲目标
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      // 复制数据至缓冲内存

    // 链接顶点属性,解释如何解析顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // glUseProgram(shaderProgram);
    // someOpenGLFunctionThatDrawsOurTriangle();
    // -------  VBO 绘制物体过程  -------

    // while 循环中
    // glUseProgram(shaderProgram);
    // glBindVertArray(VAO);
    // someOpenGLFunctionThatDrawsOurTriangle();
    // -------  VAO 绘制物体过程  -------

    // 保证窗口不关闭
    while(!glfwWindowShouldClose(window)){
        // 输入
        processInput(window);

        // 渲染指令
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 状态设置函数
        // glClear(GL_COLOR_BUFFER_BIT);           // 状态使用函数
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwPollEvents();           // 检查触发事件
        glfwSwapBuffers(window);    // 交换缓冲,更新绘制
    }

    // 释放资源
    glfwTerminate();
    return 0;
}
