#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include "..\common\debugging.h"
#include "..\common\renderable.h"
#include "..\common\shaders.h"

renderable r;

/*	this function  sets up the buffers for rendering a box  made
	of nx by ny quadrilateral, each made of two triangles. 
*/
//quadrato fatto da nx triangoli in larghezza, e ny triangoli in lunghezza
void create_box2d(int nx, int ny) {

    //matrice 2nx per 2ny (servono 2nx*2ny vertici)
    //is there a way to color them too so i can distinguish them more clearly?
    int nvertici = 2*nx + 2*ny;

    std::vector<float> pos;
    float xadd = 0.2/nx; // 
    float yadd = 0.2/ny; // need a way to not have too many decimal places hmmm

    float x = -0.1; float y = -0.1;

    //genero le posizioni, a partire da quella più "negativa" fino a quella più positiva
    /*
    gli indici corrisponderanno a questo più o meno
                1----3----5
                |  / |  / |
                | /  | /  |
                0----2----4

    */
    for (int i = 0; i <= nx; i++) {
        y = -0.1;
        for (int j = 0; j <= ny; j++) {
            pos.push_back(x); pos.push_back(y);
                y += yadd;

        }
        x += xadd;
    }

	float positions[] = { 
        -0.1, -0.1,	// 1st vertex
		0.1, -0.1,  // 2nd vertex
		0.1, 0.1,	// 3nd vertex
		-0.1, 0.1    // 4th vertex
	};
	//unsigned int ind[] = { 0,1,2, 0,2,3 };
    unsigned int ind[] = { 
        0,1,3, 
        0,2,3,
        2,3,5,
        2,4,5
    };

    std::vector<unsigned int> indici;
    int a = 0; int b = 1; int c = nx + ny - 1; //3 vertici del triangolino alto del singolo quadratino
    for (int index = 0; index < nx*ny; index++) {
        indici.push_back(a);
        indici.push_back(b);
        indici.push_back(c);

        //triangolino basso
        indici.push_back(a);
        indici.push_back(b+ny);
        indici.push_back(b+ny+1);

        //TODO incrementare i vertici
    }

	r.create();
	r.add_vertex_attribute<float>(&pos[0], sizeof(float) * nvertici, 0, 2);
    r.add_indices(ind, sizeof(unsigned int) * 12, GL_TRIANGLES);
}

int main(void)
{

	
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 800, "code_3_box2d", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glewInit();

    printout_opengl_glsl_info();

    int nx = 1;
    int ny = 1;
    int nverts = nx*ny*6;
	create_box2d(nx, ny);
	r.bind();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

		/* here the call to render the box --*/
        glDrawElements(GL_TRIANGLES, (GLsizei)nverts, GL_UNSIGNED_INT, 0); // nverts replaces 4
		/* -------------------------------------*/
		
		/* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
