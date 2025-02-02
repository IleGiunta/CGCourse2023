#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "..\common\debugging.h"
 

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 800, "code_1_my_first_triangle", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    printout_opengl_glsl_info();

	/// create render data in RAM

	/*
	GLuint positionAttribIndex = 0;
	float positions[] = {	0.0, 0.0,	// 1st vertex
							0.5, 0.0,	// 2nd vertex
							0.5, 0.5	// 3rd vertex
	};

	/// create a buffer for the render data in video RAM

	GLuint positionsBuffer = 0; // added = 0
	glGenBuffers(1, &positionsBuffer); // changed from Create to Gen
	glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);

	/// declare what data in RAM are filling the buffering video RAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);
	glEnableVertexAttribArray(positionAttribIndex);

	/// specify the data format
	glVertexAttribPointer(positionAttribIndex, 2, GL_FLOAT, false, 0, 0);

	GLuint colorAttribIndex = 1;
	float colors[] = {	1.0, 0.0, 0.0,	// 1st vertex
						0.0, 1.0, 0.0,  // 2nd vertex
						0.0, 0.0, 1.0	// 3rd vertex
	};
	/// create a buffer for the render data in video RAM
	GLuint colorsBuffer = 0; // added initialization = 0
	glGenBuffers(1, &colorsBuffer);	// changed from Create to Gen
	glBindBuffer(GL_ARRAY_BUFFER, colorsBuffer);

	/// declare what data in RAM are filling the bufferin video RAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 9, colors, GL_STATIC_DRAW);
	glEnableVertexAttribArray(colorAttribIndex);

	/// specify the data format
	glVertexAttribPointer(colorAttribIndex, 3, GL_FLOAT, false, 0, 0);
	*/

	/// \note exercise first_steps
	/// \details Change the code of code_1_my_first_triangle/main.cpp so that  only one %ARRAY_BUFFER is used (that is, only one ^glBindBuffer and only one ^glBufferData)

	GLuint positionAttribIndex = 0;
	GLuint colorAttribIndex = 1;
	float triangle[] = {
		0.0, 0.0, 1.0, 0.0, 0.0,	// 1st vertex: posX, posY, colR, colG,colB
		0.5, 0.0, 0.0, 1.0, 0.0,	// 2nd vertex
		0.5, 0.5, 0.0, 0.0, 1.0		// 3rd vertex
	};

	/// create a buffer
	GLuint triangleBuffer = 0;
	glGenBuffers(1, &triangleBuffer); //using Gen because for some reason Create doesn't work for me
	glBindBuffer(GL_ARRAY_BUFFER, triangleBuffer);

	/// declare what data in RAM are filling the bufferin video RAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, triangle, GL_STATIC_DRAW);
	glEnableVertexAttribArray(positionAttribIndex);
	glEnableVertexAttribArray(colorAttribIndex);

	/// specify the data format
	glVertexAttribPointer(positionAttribIndex, 2, GL_FLOAT, false, 20, 0);
	glVertexAttribPointer(colorAttribIndex, 3, GL_FLOAT, false, 20, (GLvoid*)8);

/*  \BEGIN IGNORATE DA QUI IN POI */
	/* create a vertex shader */
	std::string  vertex_shader_src = "#version 330\n \
        in vec2 aPosition;\
        in vec3 aColor;\
        out vec3 vColor;\
        void main(void)\
        {\
         gl_Position = vec4(aPosition, 0.0, 1.0);\
         vColor = aColor;\
        }\
       ";
	const GLchar* vs_source = (const GLchar*)vertex_shader_src.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vs_source, NULL);
	glCompileShader(vertex_shader);
	check_shader(vertex_shader);

	/* create a fragment shader */
	std::string   fragment_shader_src = "#version 330 \n \
        out vec4 color;\
        in vec3 vColor;\
        void main(void)\
        {\
            color = vec4(vColor, 1.0);\
        }";
	const GLchar* fs_source = (const GLchar*)fragment_shader_src.c_str();
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fs_source, NULL);
	glCompileShader(fragment_shader);
	check_shader(fragment_shader);

	GLuint program_shader = glCreateProgram();
	glAttachShader(program_shader, vertex_shader);
	glAttachShader(program_shader, fragment_shader);
	glBindAttribLocation(program_shader, positionAttribIndex, "aPosition");
	glBindAttribLocation(program_shader, colorAttribIndex, "aColor");
	glLinkProgram(program_shader);
/*  \END IGNORATE  */


	/* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		
		//glClearColor(0, 191, 255, 1.0);
		
		//glClearColor(127, 128, 204, 1.0); 
		//for some reason this color doesnt work? the bg becomes white if i use this color
		
		glClear(GL_COLOR_BUFFER_BIT);

		//glColor3f(0.0,0.0,1.0);

		glUseProgram(program_shader);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(0);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
