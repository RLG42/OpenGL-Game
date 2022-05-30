
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <random>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "include/cube.h"
#include "include/gameVariables.h"
#include "include/collision.h"
#include "include/shader.hpp"
#include "include/controls.hpp"
#include "include/objloader.hpp"
#include "include/texture.hpp"
#include "include/vboindexer.hpp"
#include "include/text2D.hpp"

//#define SDL_MAIN_HANDLED
//#include "SDL.h"
//#include "SDL_image.h"

#include "irrKlang.h"
using namespace irrklang;

ISoundEngine* SoundEngine = createIrrKlangDevice();

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
float numberGen();
GLFWwindow* window; 

int main(int argc, const char** argv)
{

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(1280, 720, "OpenGL Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); 

	glfwSetKeyCallback(window, keyCallback); //Controls

    glewExperimental = true; 
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_FALSE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwPollEvents();
    glfwSetCursorPos(window, 1024 / 2, 768 / 2);

    // Background Colour
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // GLSL program from the shaders
    GLuint programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");

    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");

    // Load textures
    GLuint Texture = loadBMP_custom("Images/cubes.BMP");
	GLuint Texture2 = loadBMP_custom("Images/player.BMP");
	GLuint Texture3 = loadBMP_custom("Images/background.BMP");
    //GLuint Texture = loadDDS("uvmap.DDS");

    // Get a handle for our "myTextureSampler" uniform
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");

	static GLfloat g_color_buffer_data[] = {
	  distr(gen),distr(gen),distr(gen)

	};

    // Read .obj file
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec3> normals; 
  bool res = loadOBJ("cube.obj", vertices, uvs, normals);

  std::vector<unsigned short> indices;
  std::vector<glm::vec3> indexed_vertices;
  std::vector<glm::vec2> indexed_uvs;
  std::vector<glm::vec3> indexed_normals;
  indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

  // Load VBO
  GLuint vertexbuffer;
  glGenBuffers(1, &vertexbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
  glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);

  GLuint uvbuffer;
  glGenBuffers(1, &uvbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
  glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

  GLuint normalbuffer;
  glGenBuffers(1, &normalbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
  glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

  GLuint elementbuffer;
  glGenBuffers(1, &elementbuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

  // Get a handle for our "LightPosition" uniform
  glUseProgram(programID);
  GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");

  // Initialize our little text library with the Holstein font
  initText2D("Holstein.DDS");

  // For speed computation
  double lastTime = glfwGetTime();
  int nbFrames = 0;

  for (int i = 0, x = 20, y = -6, z = 0; i < 4; i++)
  {
	  {
		  x += 2; y += 2; z += 1;
	  }
	  Moving[i].cubeX = x; // X position
	  Moving[i].cubeY = y; // Y position
	  Moving[i].cubeZ = z; // Z position
	  Moving[i].cubeSizeY = 1.0;
	  Moving[i].cubeSizeX = 1.0;
	  Moving[i].cubeSizeZ = 1.0;
  }

  // Main Events //

    do {

        double currentTime = glfwGetTime();
        nbFrames++;
        if (currentTime - lastTime >= 1.0) { 
            //printf("%f ms/frame\n", 1000.0 / double(nbFrames));
            nbFrames = 0;
            lastTime += 0.1;
        }
				
		// Player Movement //
		// Move Left
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		{
			playerX -= 0.2;
		}
		// Move Right
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS )
		{
				playerX += 0.2;
		}
		// Move Up
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			playerY += 0.2;
		}
		// Move Down
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			playerY -= 0.2;
		}

		// Laser
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			laserOn == true;
			laserX += laserSPEED;
			laserSizeX = 2.0f;
			laserSizeY = 1.0f;
			
			
		}
		else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
		{
			laserOn == false;
			laserX = playerX-1.1;
			laserY = playerY-0.1;
			laserSizeX = 0.1f;
			laserSizeY = 0.1f;
			laserZ = playerZ - 1;
		}

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);
     
        //// MVP matrix for keyboard and mouse input ////
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();

		//// Lights ////
		glm::vec3 lightPos = glm::vec3(playerX, playerY + 2, playerZ + 2);
		glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
		glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);

		////// Object Rendering //////

		float angle = 0.0f; // For rotations 

		// Player cube //
		glm::mat4 ModelMatrix1 = glm::mat4(1.0);
		ModelMatrix1 = glm::translate(ModelMatrix1, glm::vec3(playerX, playerY, playerZ));
		ModelMatrix1 = glm::scale(ModelMatrix1, glm::vec3(0.5, 0.5, 0.5));	
		glm::mat4 MVP1 = ProjectionMatrix * ViewMatrix * ModelMatrix1;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP1[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix1[0][0]);

		// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture2);
		// Set our "myTextureSampler" sampler to use Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

		glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_SHORT,(void*)0);

		// Cube //		
		glm::mat4 ModelMatrix2 = glm::mat4(1.0);
		ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(Moving[0].cubeX -= SPEED / 4.2, Moving[0].cubeY, Moving[0].cubeZ));
		ModelMatrix2 = glm::scale(ModelMatrix2, glm::vec3(0.7, 0.7, 0.7));
		
		angle += static_cast<float>(glfwGetTime());
		glm::mat4 transform(1.0f);
		ModelMatrix2 = glm::rotate(ModelMatrix2, angle, glm::vec3(3.0f, 4.0f, 100.0f));
		glm::mat4 MVP2 = ProjectionMatrix * ViewMatrix * ModelMatrix2;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP2[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix2[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(TextureID, 0);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
		
		// Cube 1 //
		glm::mat4 ModelMatrix3 = glm::mat4(1.0);
		ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(Moving[1].cubeX -= SPEED / 4.4, Moving[1].cubeY, Moving[1].cubeZ));
		ModelMatrix3 = glm::scale(ModelMatrix3, glm::vec3(0.4, 0.4, 0.4));
		ModelMatrix3 = glm::rotate(ModelMatrix3, angle, glm::vec3(20.0f, 4.0f, 10));
		glm::mat4 MVP3 = ProjectionMatrix * ViewMatrix * ModelMatrix3;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP3[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix3[0][0]);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		// Cube 2 //
		glm::mat4 ModelMatrix4 = glm::mat4(1.0);
		ModelMatrix4 = glm::translate(ModelMatrix4, glm::vec3(Moving[2].cubeX -= SPEED / 4.6, Moving[2].cubeY, Moving[2].cubeZ));
		ModelMatrix4 = glm::scale(ModelMatrix4, glm::vec3(0.5, 0.5, 0.5));
		ModelMatrix4 = glm::rotate(ModelMatrix4, angle, glm::vec3(10.0f, 4.0f, 9.0));
		glm::mat4 MVP4 = ProjectionMatrix * ViewMatrix * ModelMatrix4;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP4[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix4[0][0]);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		// Cube 3 //
		glm::mat4 ModelMatrix5 = glm::mat4(1.0);
		ModelMatrix5 = glm::translate(ModelMatrix5, glm::vec3(Moving[3].cubeX -= SPEED / 4.8, Moving[3].cubeY, Moving[3].cubeZ));
		ModelMatrix5 = glm::scale(ModelMatrix5, glm::vec3(0.6, 0.6, 0.6));
		ModelMatrix5 = glm::rotate(ModelMatrix5, angle, glm::vec3(0.0f, 0.0f, 7.0));
		glm::mat4 MVP5 = ProjectionMatrix * ViewMatrix * ModelMatrix5;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP5[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix5[0][0]);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		// Laser //
		glm::mat4 ModelMatrix6 = glm::mat4(1.0);
		ModelMatrix6 = glm::translate(ModelMatrix6, glm::vec3(laserX += laserSPEED, laserY, laserZ));		
		ModelMatrix6 = glm::scale(ModelMatrix6, glm::vec3(0.3, 0.15, 0.1));
		glm::mat4 MVP6 = ProjectionMatrix * ViewMatrix * ModelMatrix6;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP6[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix6[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture2);
		glUniform1i(TextureID, 0);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		// background //
		glm::mat4 ModelMatrix7 = glm::mat4(1.0);
		ModelMatrix7 = glm::translate(ModelMatrix7, glm::vec3(0, 0, -6));
		ModelMatrix7 = glm::scale(ModelMatrix7, glm::vec3(19.5, 14.5, 1));
		glm::mat4 MVP7 = ProjectionMatrix * ViewMatrix * ModelMatrix7;

		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP7[0][0]);
		glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix7[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, Texture3);
		glUniform1i(TextureID, 0);

		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);

		collision();
		
		// Reset Laser Position //
		if (laserX >= playerX + 25)
		{
			SoundEngine->play2D("audio/Laser_Valenspire_1.mp3", false);
			laserX = playerX;
			laserY = playerY;
		}

		if (laserX >= playerX )
		{

	
	
		}


        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);

		// Text //
		char text[256];
		sprintf(text, "%.2f Time", glfwGetTime());
		printText2D(text, 580, 550, 21);

		char text2[256];
		sprintf(text2, "%d Score", playerScore);
		printText2D(text2, 20, 550, 21);

		char text3[256];
		sprintf(text3, "%d Lives", playerLives);
		printText2D(text3, 300, 550, 21);

        glfwSwapBuffers(window);
		glfwPollEvents();
        

    } 
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window) == 0);

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &uvbuffer);
    glDeleteBuffers(1, &normalbuffer);
    glDeleteBuffers(1, &elementbuffer);
    glDeleteProgram(programID);
    glDeleteTextures(1, &Texture);
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwTerminate();

    return 0;

}

float numberGen()
{

    GLfloat a =  (float(rand()) /float(RAND_MAX));
    return a;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	////Player Controls
	//// Move UP
	//if (glfwGetKey(window, GLFW_KEY_W) )
	//{
	//	switch (action)
	//	{
	//	case GLFW_PRESS:
	//		playerY += 0.1;
	//		break;
	//
	//	case GLFW_REPEAT:
	//		playerY += 0.1;
	//		break;
	//
	//	}
	//}
	// Move Down
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS == 0) {
	
		SoundEngine->play2D("audio/Laser_Valenspire_1.mp3", false);
	}

	

}




