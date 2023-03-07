module;
#include <GLFW/glfw3.h>
#include <glfw/glfw3.h>

export module Platform;
import Events;
import stdlib;

export namespace PLTF
{
	export class Window
	{
	protected:
		EVNT::EventCallbackFn CallbackFunction;

		Window() = default;

	public:
		virtual ~Window() = default;

		void SetEventCallback(const EVNT::EventCallbackFn& callback) { CallbackFunction = callback; }

		virtual void OnUpdate() = 0;
		virtual bool ShouldClose() = 0;
		virtual void RenameWindow(const char* title) = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void* GetModule() const = 0;
		virtual void* GetMonitor() const = 0;
	};

	class DesktopWindow : public Window
	{
	private:
		static uint32_t WindowsUsingGLFW;
		GLFWwindow* Handle;

	public:
		DesktopWindow(const uint32_t width, const uint32_t height, const char* name = "Window");
		~DesktopWindow();

		virtual void OnUpdate() final override;
		virtual bool ShouldClose() final override;
		virtual void RenameWindow(const char* title) final override;
		virtual void* GetNativeWindow() const final override;
		virtual void* GetModule() const final override;
		virtual void* GetMonitor() const final override;

		GLFWwindow* GetGLFWwindow() const { return Handle; }
	};

	uint32_t DesktopWindow::WindowsUsingGLFW = 0;

	export Window* CreateWindow(const uint32_t width, const uint32_t height, const char* name)
	{
	#ifdef _WIN32
		return new DesktopWindow(width, height, name);
	#endif
	}

	export class Library
	{
	private:
		void* Handle;

	public:
		Library() {};
		Library(const wchar_t* windowsName, const char* unixName);

		void Load(const wchar_t* windowsName, const char* unixName);
		void* GetFunction(const char* name);
	};
}

