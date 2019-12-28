#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>

#include<glm/glm.hpp>
#include<glm/gtc//matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "stb_image.h"
#include "model.h"
#include "camera.h"

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;
//���ڵ�����С�Ļص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


float vertices[] = {
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,  9.0f,  9.0f),
	glm::vec3(9.0f, 9.0f, 0.0f),
	glm::vec3(0.0f,  5.0f, 0.0f),
};//����λ��
glm::vec3 pointLightColors[] = {
glm::vec3(1.6f, 1.6f, 1.6f),
glm::vec3(0.0f, 4.0f, 4.0f),
};//������ɫ
// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// ��������
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// �ı䴰�ڴ�С�Ĵ���
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// ����ƶ��Ļص�����
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// ���ֵĻص�����
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}
int main(int argc, char** argv)
{
	//ʵ����GLFW����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGLCourse1", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//����������ع��
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);
	//ע��ص�����
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	Shader ourShader("./shaders/shader.vert", "./shaders/shader.frag"); //ʹ�������Լ��������ɫ��
	Shader lightingShader("./shaders/color.vert", "./shaders/color.frag");
	Shader lampShader("./shaders/lamp.vert", "./shaders/lamp.frag");


	unsigned int VBO, cubeVAO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(cubeVAO);

	// ��������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// ����������
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	Model ourModel(("./model/AIBoss/model.obj"));
	Model scene(("./model/changjing.obj"));

	//���ϻ��ƣ������û�����
	while (!glfwWindowShouldClose(window))
	{
		//����deltatime���߼�
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//��������
		processInput(window);
		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //��Ȳ��ԣ�

		ourShader.use();
		//����3D��ģ�;���ģ��ת������������
		glm::mat4 model = glm::mat4(1.0f); // �ǵó�ʼ������
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		view = glm::translate(view, glm::vec3(0.0f, -5.0f, -20.0f));
		projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		//��ģ�ͺ������λ��ת��Ϊuniform������shader
		unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
		unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

		// ����shader
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
		// ��Ȼ������ѭ�������ã�����û���α䣬���Կ��Է�������
		ourShader.setMat4("projection", projection);

// 		unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
// 		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		// 		//��uniform������ɫ
		// 		float timeValue = glfwGetTime();
		// 		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		// 		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		// 		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
				//
		//ʹ�ù�����ɫ��
		glBindVertexArray(cubeVAO);
		lightingShader.use();

		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("shininess", 32.0f);
		// ��������
		 // ���Դ1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.05, pointLightColors[0].y * 0.05, pointLightColors[0].z * 0.05);
		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x * 1, pointLightColors[0].y * 1, pointLightColors[0].z * 1);
		lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x * 1, pointLightColors[0].y * 1, pointLightColors[0].z * 1);
		lightingShader.setFloat("pointLights[0].constant", 0.2f);
		lightingShader.setFloat("pointLights[0].linear", 0.09);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032);
		// ���Դ2
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.05, pointLightColors[1].y * 0.05, pointLightColors[1].z * 0.05);
		lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x * 1, pointLightColors[1].y * 1, pointLightColors[1].z * 1);
		lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x * 1, pointLightColors[1].y * 1, pointLightColors[1].z * 1);
		lightingShader.setFloat("pointLights[1].constant", 0.2f);
		lightingShader.setFloat("pointLights[1].linear", 0.09);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032);


		lightingShader.setMat4("model", model);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);

		ourModel.Draw(lightingShader);

		lightingShader.use();

		lightingShader.setVec3("viewPos", camera.Position);
		lightingShader.setFloat("shininess", 32.0f);
		// ��������
		 // ���Դ1
		lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
		lightingShader.setVec3("pointLights[0].ambient", pointLightColors[0].x * 0.2, pointLightColors[0].y * 0.2, pointLightColors[0].z * 0.2);
		lightingShader.setVec3("pointLights[0].diffuse", pointLightColors[0].x * 1, pointLightColors[0].y * 1, pointLightColors[0].z * 1);
		lightingShader.setVec3("pointLights[0].specular", pointLightColors[0].x * 1, pointLightColors[0].y * 1, pointLightColors[0].z * 1);
		lightingShader.setFloat("pointLights[0].constant", 0.2f);
		lightingShader.setFloat("pointLights[0].linear", 0.09);
		lightingShader.setFloat("pointLights[0].quadratic", 0.032);
		// ���Դ2
		lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
		lightingShader.setVec3("pointLights[1].ambient", pointLightColors[1].x * 0.2, pointLightColors[1].y * 0.20, pointLightColors[1].z * 0.2);
		lightingShader.setVec3("pointLights[1].diffuse", pointLightColors[1].x * 1, pointLightColors[1].y * 1, pointLightColors[1].z * 1);
		lightingShader.setVec3("pointLights[1].specular", pointLightColors[1].x * 1, pointLightColors[1].y * 1, pointLightColors[1].z * 1);
		lightingShader.setFloat("pointLights[1].constant", 0.2f);
		lightingShader.setFloat("pointLights[1].linear", 0.09);
		lightingShader.setFloat("pointLights[1].quadratic", 0.032);
		model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(270.f), glm::vec3(1.0, 0.0, 0.0));
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 12.0f));
		lightingShader.setMat4("model", model);
		lightingShader.setMat4("view", view);
		lightingShader.setMat4("projection", projection);

		scene.Draw(lightingShader);


		// ��Ⱦ�����Ʊ�ʾ��Դ
		lampShader.use();
		lightingShader.setInt("material.diffuse", 0);
		lightingShader.setInt("material.specular", 1);
		lampShader.setMat4("projection", projection);
		lampShader.setMat4("view", view);
		glBindVertexArray(lightVAO);
		for (unsigned int i = 0; i < 2; i++)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); //��С�ķ���
			lampShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
		//
		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	//�˳�ǰɾ��VAO VBO �ͷ��Դ�
// 	glDeleteVertexArrays(1, &VAO);
// 	glDeleteBuffers(1, &VBO);
// 	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}