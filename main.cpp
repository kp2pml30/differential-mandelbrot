#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <thread>
#include <mutex>

#include <QApplication>

#include "Shader.h"
#include "sliderwindow.h"

namespace
{
	void error_callback(int error, char const* description) { std::cerr << "Error : " << description << std::endl; }

	class File
	{
	private:
		std::string path;
		std::filesystem::file_time_type lastChange;

	public:
		File(std::string const& path)
		: path(path)
		{
			lastChange = std::filesystem::last_write_time(this->path);
		}

		bool Changed() const
		{
			auto cur = std::filesystem::last_write_time(path);
			return lastChange != cur;
		}

		std::string Read()
		{
			lastChange = std::filesystem::last_write_time(path);
			std::string ret;
			std::string line;
			auto f = std::ifstream(path);
			while (std::getline(f, line))
				ret += line, ret += "\n";
			return ret;
		}
	};

	void WindowGoes(std::function<void(std::string const&, double)> callback, QApplication** app)
	{
		int argc = 0;
		*app = new QApplication(argc, nullptr);
		SliderWindow w;
		w.callback = callback;
		w.on_SliderB_valueChanged(500);
		w.on_SliderGamma_valueChanged(500);
		w.on_SliderEpsilon_valueChanged(500 + 0.25 * 500);
		w.on_SliderForce_valueChanged(500);
		w.show();
		(*app)->exec();
		// delete *app; // leak of segfault?
		*app = nullptr;
	}
} // namespace

int main()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
		return 1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(640, 480, "diff mandelbrot", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	if (auto err = glewInit(); err != GLEW_OK)
	{
		std::cerr << "glew init error " << glewGetErrorString(err) << std::endl;
		return 1;
	}
	auto vert = File("vert.glsl");
	auto frag = File("frag.glsl");
	auto shd = Shader(vert.Read(), frag.Read());
	shd.Apply();
	std::mutex shaderMutex;
	std::map<std::string, float> params;

	QApplication *app = nullptr;
	std::thread thr(
		[&]() {
			WindowGoes([&](std::string const& s, double v) {
				auto lck = std::unique_lock(shaderMutex);
				params[s] = v;
				}, &app);
		});

	glClearColor(0, 0, 0, 0);

	int iteration = 0;
	while (!glfwWindowShouldClose(window))
	{
		if (++iteration == 64)
		{
			iteration = 0;
			if (vert.Changed() || frag.Changed())
				try
				{
					auto lck = std::unique_lock(shaderMutex);
					shd = Shader(vert.Read(), frag.Read());
					shd.Apply();
					std::cout << "shader reloaded" << std::endl;
				}
				catch (std::exception const& e)
				{
					std::cout << "Failed to update shader\n" << e.what() << std::endl;
				}
		}
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = height / (float)width;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto const& p : params)
		{
			int i = shd.GetUniformLocation(p.first);
			if (i < 0)
				std::cout << "bad location for " << p.first << " err " << glGetError() << std::endl;
			else
				glUniform1f(i, p.second);
		}

		{
			auto lck = std::unique_lock(shaderMutex);
			glBegin(GL_TRIANGLES);
				glVertex2f(-1, -1);
				glVertex2f(4, -1);
				glVertex2f(-1, 4);
			glEnd();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	if (app != nullptr)
		app->quit();
	thr.join();
	glfwDestroyWindow(window);
	glfwTerminate();
}
