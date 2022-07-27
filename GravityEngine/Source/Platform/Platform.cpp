module;
#ifdef _WIN32
#include <windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#endif
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Core/DebugUtils.h"

module Platform;

namespace PLTF 
{
    DesktopWindow::DesktopWindow(const uint32_t width, const uint32_t height, const char* name)
    {
        if (WindowsUsingGLFW == 0) {
            int result = glfwInit();
            verify(result == GLFW_TRUE, "GLFW could not be initialized.")
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); //TODO: make dynamic, only vulkan
        Handle = glfwCreateWindow(width, height, name, nullptr, nullptr);
        glfwSetWindowUserPointer(Handle, this);
        glfwMakeContextCurrent(Handle);
        WindowsUsingGLFW++;

        glfwSetFramebufferSizeCallback(Handle, [](GLFWwindow* window, int width, int height)
            {
                while (width == 0 && height == 0) {
                    glfwGetFramebufferSize(window, &width, &height);
                    glfwWaitEvents();
                }

                DesktopWindow& userWindow = *(DesktopWindow*)glfwGetWindowUserPointer(window);

                EVNT::WindowResizeEvent resizeEvent(width, height);
                userWindow.CallbackFunction(resizeEvent);
            });

        glfwSetWindowCloseCallback(Handle, [](GLFWwindow* window)
            {
                DesktopWindow& userWindow = *(DesktopWindow*)glfwGetWindowUserPointer(window);

                EVNT::WindowCloseEvent closeEvent;
                userWindow.CallbackFunction(closeEvent);
            });
    }

    DesktopWindow::~DesktopWindow()
    {
        glfwDestroyWindow(Handle);

        if (--WindowsUsingGLFW == 0) {
            glfwTerminate();
        }
    }

    void DesktopWindow::OnUpdate()
    {
        glfwPollEvents();
    }

    bool DesktopWindow::ShouldClose()
    {
        return glfwWindowShouldClose(Handle);
    }

    void DesktopWindow::RenameWindow(const char* title)
    {
        glfwSetWindowTitle(Handle, title);
    }

    void* DesktopWindow::GetNativeWindow() const
    {
        #ifdef _WIN32
        return (void*)glfwGetWin32Window(Handle);
        #endif
    }
}