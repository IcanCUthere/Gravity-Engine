import Application;

int main(int argc, const char* argv[])
{
	Application& app = Application::Initialize("Gravity: Control");

	app.Run();

	Application::Terminate();

	return 0;
}

int WinMain(int argc, const char* argv[])
{
	Application& app = Application::Initialize("Gravity: Control");

	app.Run();

	Application::Terminate();

	return 0;
}