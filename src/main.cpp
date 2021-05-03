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

    // 保证窗口不关闭
    while(!glfwWindowShouldClose(window)){
        // 输入
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);   // 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);           // 状态使用函数

        glfwPollEvents();           // 检查触发事件
        glfwSwapBuffers(window);    // 交换缓冲,更新绘制
    }

    // 释放资源
    glfwTerminate();
    return 0;
}
