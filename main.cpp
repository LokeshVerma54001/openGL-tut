#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = 
	"#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShader1Source = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\n\0";


const char* fragmentShader2Source = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
	"}\n\0";


int main() {


	
	//triangle vertices coords
	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	0.5f, -0.5f, 0.0f,
	//	0.0f, 0.5f, 0.0f 
	//};

	//exercise triangles vertices coords
	//float vertices[] = {
	//	-0.8f, -0.5f, 0.0f,
	//	-0.1f, -0.5f, 0.0f,
	//	-0.4f, 0.5f, 0.0f,
	//	0.8f, -0.5f, 0.0f,
	//	0.1f, -0.5f, 0.0f,
	//	0.4f, 0.5f, 0.0f
	//};

	//exercise triangle one
	float firstTriangle[] = {
		-0.9f, -0.5f, 0.0f,  // left 
        -0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
	};
	//exercise triangle two
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};

	//square vertices coords
	//float vertices[] = {
	//	0.5f, 0.5f, 0.0f, //top right		- 0
	//	0.5f, -0.5f, 0.0f, //bottom right	- 1
	//	-0.5f, -0.5f, 0.0f, //bottom left	- 2
	//	-0.5f, 0.5f, 0.0f, //top left		- 3
	//};

	//unsigned int indices[] = {
	//	0, 1, 3, //triangle 1
	//	1, 2, 3	 //triangle 2
	//};

	//variables
	unsigned int VBOs[2]; //vertex buffer object
	unsigned int VAOs[2]; //vertex array object
	//unsigned int EBO; //element buffer object
	unsigned int vertexShader;
	unsigned int fragmentShaderOrange;
	unsigned int fragmentShaderYellow;
	unsigned int shaderProgramOrange;
	unsigned int shaderProgramYellow;
	int success;
	char infoLog[512];
	

	glfwInit(); // inits the glfw window
	//telling glfw the major and minor version of openGl 
	//being used in the project
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//creating a new GLFW window of 800x600
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGlWindow", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to intialize GLAD" << endl;
		return -1;
	}



	//creating a vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//attaching the shader source to shader object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//compiling the shaders
	glCompileShader(vertexShader);
	//shaders compilation debugging
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "Error::Shader::Vertex::Compilation_failed\n" << infoLog << endl;
	}

	//creating fragment shader(similar process)
	fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
	fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
	glCompileShader(fragmentShaderOrange);
	glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
	glCompileShader(fragmentShaderYellow);

	//creating shader program
	shaderProgramOrange = glCreateProgram();
	shaderProgramYellow = glCreateProgram();
	glAttachShader(shaderProgramOrange, vertexShader);
	glAttachShader(shaderProgramYellow, vertexShader);
	glAttachShader(shaderProgramOrange, fragmentShaderOrange);
	glAttachShader(shaderProgramYellow, fragmentShaderYellow);
	glLinkProgram(shaderProgramOrange);
	glLinkProgram(shaderProgramYellow);

	//shader objects cleanup
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderOrange);
	glDeleteShader(fragmentShaderYellow);



	//genrates VBO, VAO and EBO objects
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	//glGenBuffers(1, &EBO);
	//bind vertex array
	glBindVertexArray(VAOs[0]);
	//binding VBO to GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	//function to copy vertex data to buffer's memory
//•	GL_STREAM_DRAW: the data is set only once and used by the GPU at most a few times.
//• GL_STATIC_DRAW : the data is set only once and used many times.
//• GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	//we bind the indices similarly with a static draw to EBO
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 1. then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// note that this is allowed, the call to 
	// glVertexAttribPointer registered VBO as the 
	// vertex attribute's bound vertex buffer object so 
	// afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO 
	// calls won't accidentally modify this VAO, but 
	// this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways 
	// so we generally don't unbind VAOs (nor VBOs) when 
	// it's not directly necessary.
	glBindVertexArray(0);

	//second VBO and VAO setup
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		// clear black color and sets the screen color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//first triangle and vao
		glUseProgram(shaderProgramOrange);
		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//second triangle and vao
		glUseProgram(shaderProgramYellow);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(GL_TRIANGLES, 0, 6); two triangle exercise
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0);

		// glfw: swap buffers and poll IO events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//clean up
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgramOrange);
	glDeleteProgram(shaderProgramYellow);

	glfwTerminate();
	return 0;
}

//process all input : query GLFW whether relevant keys 
// are pressed / released this frame and react accordingly
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//glfw: whenever the window size changed 
// (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}