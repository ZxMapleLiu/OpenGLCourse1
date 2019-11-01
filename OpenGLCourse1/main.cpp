#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>

#include<glm/glm.hpp>
#include<glm/gtc//matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"
/*using namespace std;*/
// 
// //使用GLSL定义顶点着色器
// const GLchar* vertexShaderSource =
// "#version 330 core\n"
// "layout (location = 0) in vec3 position;\n"//位置变量属性位置值为0
// "layout (location = 1) in vec3 aColor;\n"//颜色变量属性位置值为1
// "out vec3 vertexColor;\n"
// "void main()\n"
// "{\n"
// "gl_Position = vec4(position,1.0);\n"
// //"vertexColor = vec4(0.5f,0.0f,0.0f,1.0f);\n"
// "vertexColor = aColor;\n"
// "}\0";
// //使用GLSL定义片段着色器
// const GLchar* fragmentShaderSource = "#version 330 core\n"
// "out vec4 color;\n"
// //"uniform vec4 ourColor;\n"
// "in vec3 vertexColor;\n"
// "void main()\n"
// "{\n"
// //"color = ourColor;\n"// 使用uniform传来的颜色信息
// "color = vec4(vertexColor,1.0);\n" //使用顶点着色器传来的颜色信息
// "}\n\0";

const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;


//窗口调整大小的回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main(int argc, char** argv)
{
	//实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建一个窗口对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLCourse1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
// 	//	//编译顶点着色器
// 	unsigned int vertexShader;
// 	vertexShader = glCreateShader(GL_VERTEX_SHADER);
// 	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
// 	glCompileShader(vertexShader);
// 	int success;
// 	char infoLog[512];
// 	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
// 		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
// 	}
// 	//编译片段着色器
// 	unsigned int fragmentShader;
// 	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
// 	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
// 	glCompileShader(fragmentShader);
// 	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
// 	if (!success)
// 	{
// 		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
// 		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
// 	}
// 	//创建着色器程序
// 	unsigned int shaderProgram;
// 	shaderProgram = glCreateProgram();
// 	//连接着色器
// 	glAttachShader(shaderProgram, vertexShader);
// 	glAttachShader(shaderProgram, fragmentShader);
// 	glLinkProgram(shaderProgram);
// 	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
// 	if (!success) {
// 		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
// 		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
// 	}
// 	//删除不用的着色器
// 	glDeleteShader(vertexShader);
// 	glDeleteShader(fragmentShader);
	//输入顶点数据
// 	GLfloat vertices[] = {
// 		-0.5f,-0.5f,0.0f,
// 		0.5f,-0.5f,0.0f,
// 		0.5f,0.5f,0.0f,
// 		0.5f,0.5f,0.5f
// 	};
	float vertices[] = {
		//位置 纹理
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	//纹理坐标
	//可以写进顶点坐标数组
// 	GLfloat texCoords[] = {
// 		0.0f,0.0f,
// 		1.0f,0.0f,
// 		0.5f,1.0f
// 	};
	unsigned int indices[] =
	{
		0,1,3,//第一个三角形
		1,2,3,//第二个三角形
	};

	//创建顶点缓冲对象VBO,VAO，EBO
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	//将数组与VBO绑定
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//将EBO绑定
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//告诉VAO怎么解析
	//位置
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	//纹理
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	/*	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//描边模式*/
	Shader ourShader("./shaders/shader.vert", "./shaders/shader.frag"); //使用我们自己定义的着色器
	//第一个纹理
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//调整纹理的环绕方式为重复
	//坐标轴：S,R,T
	//GL_REPEAT,GL_MIRRORED_REPEAT,GL_CLAMP_TO_BORDER,GL_CLAMP_TO_EDGE
	//如果使用GL_CLAMP_TO_BORDER, 还需要定义边界颜色值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//将缩小（Minify）时的纹理过滤选项调整为邻近纹理过滤
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//将放大（Magnify）时纹理过滤选项调整为线性纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//多级渐远纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载纹理
	int width, height, nrChannels;
	unsigned char* data = stbi_load("./texture/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(true);//翻转Y轴

	//第一个纹理
	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	//调整纹理的环绕方式为重复
	//坐标轴：S,R,T
	//GL_REPEAT,GL_MIRRORED_REPEAT,GL_CLAMP_TO_BORDER,GL_CLAMP_TO_EDGE
	//如果使用GL_CLAMP_TO_BORDER, 还需要定义边界颜色值
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//将缩小（Minify）时的纹理过滤选项调整为邻近纹理过滤
	// 	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//将放大（Magnify）时纹理过滤选项调整为线性纹理过滤
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);//多级渐远纹理
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//加载纹理
	data = stbi_load("./texture/awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	ourShader.use();
	//手动设置uniform的ID
	glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
	//或者使用shader的类函数设置
	ourShader.setInt("texture2", 1);
	//形变矩阵
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
	//将变换矩阵转换到uniform中
	unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));


	//不断绘制，接受用户输入
	while (!glfwWindowShouldClose(window))
	{
		//接受输入
		processInput(window);
		//渲染
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 		//画图形
		// 		glUseProgram(shaderProgram);    // 使用自己的着色器时仅有这一行被替换了，
												//程序中前面创建vertexShader和fragmentShader的部分也可以删除
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

// 		// 进行变换
// 		glm::mat4 transform = glm::mat4(1.0f); // 先初始化矩阵
// 		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
// 		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

		ourShader.use();
		//进入3D！模型矩阵将模型转换到世界中来
		glm::mat4 model = glm::mat4(1.0f); // 记得初始化矩阵
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//将模型和摄像机位置转换为uniform并传入shader
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
		// 传入shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// 虽然我们在循环内设置，但他没有形变，所以可以放在外面
		ourShader.setMat4("projection", projection);

// 		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
// 		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		// 		//用uniform更新颜色
		// 		float timeValue = glfwGetTime();
		// 		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// 		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// 		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
				//
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//
		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	//退出前删除VAO VBO 释放显存
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}