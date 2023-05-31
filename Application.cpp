#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

//For Resizing Viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//Esc to close
void ProcessInput(GLFWwindow* window);

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource_A = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource_B = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main()
{
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGl", nullptr, nullptr);

	if(window == nullptr)
	{
		std::cout << "Failed to Create Window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	int success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	unsigned int fragmentShader_A = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_A, 1, &fragmentShaderSource_A, nullptr);
	glCompileShader(fragmentShader_A);

	glGetShaderiv(fragmentShader_A, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader_A, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT_A::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader_B = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader_B, 1, &fragmentShaderSource_B, nullptr);
	glCompileShader(fragmentShader_B);

	glGetShaderiv(fragmentShader_B, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader_B, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT_B::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram_A = glCreateProgram();
	glAttachShader(shaderProgram_A, vertexShader);
	glAttachShader(shaderProgram_A, fragmentShader_A);
	glLinkProgram(shaderProgram_A);

	glGetProgramiv(shaderProgram_A, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram_A, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM_A::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram_B = glCreateProgram();
	glAttachShader(shaderProgram_B, vertexShader);
	glAttachShader(shaderProgram_B, fragmentShader_B);
	glLinkProgram(shaderProgram_B);

	glGetProgramiv(shaderProgram_B, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram_B, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM_B::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	float verticesA[] = {
		0.0f, 0.75f, 0.0f,
		0.0f, 0.5f, 0.0f,
		-0.25f, 0.625f, 0.0f
	};

	float verticesB[] = {
		0.0f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		+0.5f, -0.5f, 0.0f
	};

	unsigned int VBOs[2], VAOs[2];
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);

	
	glBindVertexArray(VAOs[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesA), verticesA, GL_STATIC_DRAW);
	//Telling OpenGl how to interpret our data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesB), verticesB, GL_STATIC_DRAW);
	//Telling OpenGl how to interpret our data
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window))
	{
		//Input
		ProcessInput(window);

		//Rendering Commands
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram_A);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram_B);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteProgram(shaderProgram_A);
	glDeleteProgram(shaderProgram_B);

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
