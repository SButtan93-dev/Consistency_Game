					//-------------------------BE PERSISTENT--------------------------------//


/*

		Name of the game: Consistency
		Developer: Saurabh Buttan
		Contact: saurabhbuttan1749@gmail.com

*/

//Please add the libraries to the VS enivronment for the code to execute successfully. If in case of any queries regarding the build, please feel free to contact me on my email-id mentioned above or on +91-8971858048. 
//Implemented using glut(OpenGL Utility Toolkit, DevIL,SFML and IRRKLANG sound library) on release mode.
#include <Windows.h>
#include <random>
#include <GL/glew.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <GL/freeglut.h>
#include <SFML\Window\Mouse.hpp>
#include<time.h>//for rand and srand
#include <array>//array
#include <irrKlang.h>

#include <gl/gl.h>

#include <IL/il.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")//to call the dll file.
#define window_width  1080  //rows and columns of the matrix window
#define window_height 720




bool is_running = true, is_fade_button = true, Pause_0 = false, reset_game = false, music_on = false, lose_state = false, work_all = true, timer = false, beep_done = true;
char name[6];//for name of the user
double radius = 0.30;//radius of circle
double twicePi = 2.0 * 3.142;//value of 2*pi for circle approximation.openGL doesnt support a circle,in order to attain one we need to render the dimensions of the geometric figure
int i = 0,j,count=0,k=250,c,max=0,l=0,temp,hz=450,x_cor,y_cor,a;
float health1 = 1;
float col_1, col_2, col_3;
GLuint *textures = new GLuint[2];
GLuint *num_textures = new GLuint[11];
GLuint *Pause = new GLuint;
GLuint *ext_but = new GLuint;
GLuint *lose_but = new GLuint;
GLuint *you_but = new GLuint;
GLuint *won_but = new GLuint;
GLuint *tgt_score = new GLuint;
ISoundEngine *SoundEngine = createIrrKlangDevice();//Create an object to turn on the sound engine. We can also make use of FLAC format of music for lossless music transfer. Feel free to contact me to give you a Flac version of the game.
std::array<int,10> a1;//array to store the score card
//to make a circle
void num_twos()//score-at zeroth position
{
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(3.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(4.0f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(4.0f, -4.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(3.0f, -4.0f);
	glEnd();


}
void bind_img()//bind the image files using DevIL library for OpenGL.
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); /* use linear interpolation for magnification filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); /* use linear interpolation for minifying filter */
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
		0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData()); /* Texture specification */
}
void num_ones()//score-at ones position
{
	
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(4.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(5.0f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(5.0f, -4.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(4.0f, -4.0f);
	glEnd();

}

void num_zeroth()//score-at zeroth position
{
	glBindTexture(GL_TEXTURE_2D, num_textures[0]);
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f); glVertex2f(5.0f, -5.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(6.0f, -5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(6.0f, -4.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(5.0f, -4.0f);
	glEnd();
}
void you_but_1()//'YOU' texture placement.
{
	glBindTexture(GL_TEXTURE_2D, you_but[0]);
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-3.0f, 5.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(3.5f, 5.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(3.5f, 6.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-3.0f, 6.0f);
	glEnd();
}
void win_lose()//'WIN' or 'LOSE' texture placement.
{
	
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-5.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(5.0f, 2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(5.0f, 4.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-5.0f, 4.0f);
	glEnd();
}
void head_1()//'EXIT' button texture placement.
{
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-1.0f, -2.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(2.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-1.0f, -1.0f);

	glEnd();

}
void head_2()//'START' button texture placement.
{

	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(2.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(2.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-1.0f, 1.0f);

	glEnd();

}

void build_buttons()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);//TITLE-'CONSISTENCY'
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(2.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(2.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-1.0f, 1.0f);

	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);//'START'
	head_1();

	glBindTexture(GL_TEXTURE_2D, textures[2]);//'EXIT'
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(0, 0, -15);
	glColor3f(1, 1, 1);

	//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glBegin(GL_QUADS);

	glTexCoord2f(0.0f, 0.0f);	glVertex2f(-5.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);  glVertex2f(5.0f, 2.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(5.0f, 5.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(-5.0f, 5.0f);

	glEnd();
	if (music_on == false)//TURN ON the song if it is not playing.
	{
		char* name_0 = "Music\01_First_Day_of_Sun.mp3";
		SoundEngine->play2D(name_0, GL_TRUE);
		music_on = true;
	}

}

void pass_in_loop(int j1, int k1)
{
	
	glBegin(GL_TRIANGLE_FAN); //BEGIN CIRCLE
	glVertex2f(j1, k1);// center of circle
	int i;

	for (i = 0; i <= 20; i++)   {

		glVertex2f(
			(j1 + (radius * cos(i * twicePi / 20))), (k1 + (radius * sin(i * twicePi / 20))));//the equation matches well to the coordinate system of a circle. for example  (j(2)+(radius(0.30)*cos(i(2)*2.0*3.142)/20)))) and similarly for sin coordinate system
	}
	glEnd();
	
}
void drawFilledSun(){
	//randomly generating the coordinates in the vertex (x,y)
	int x = rand() % 5;
	if (x < 2)
	{
		x = x - 5;
	}
	srand(time(NULL));
	int y = rand() % 5;
	if (y < 4)
	{
		y = y - 5;
	}
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the window
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(x, y, -15);//the coordinate vector (x,y,z)
	int i, k, j;//k and j are the vertex points for the triangle
	

	
	glColor3ub(255, 0, 0);//red color as RBG color components.


	srand(time(NULL));// seed time	
	j= rand() % 7; //random vertex point
	k = rand() % 5;//random vertex point
	pass_in_loop(j, k);
	
	x = rand() % 3;
	if (x < 2)
	{
		x = x - 5;
	}
	srand(time(NULL));//seed time
	y = rand() % 5;
	if (y < 1)
	{
		y = y - 1;
	}
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(x, y, -15);//the coordinate vector (x,y,z)
	j = rand() % 5;
	k = rand() % 5;//random coordinates
	pass_in_loop(j, k);
	
	x = rand() % 4;
	if (x < 3)
	{
		x = x - 5;
	}
	srand(time(NULL));//seed time
	y = rand() % 3;
	if (y < 2)
	{
		y = y  -4;
	}
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually
	glTranslatef(x, y, -15);//the coordinate vector (x,y,z)
	j = rand() % 8;
	k = rand() % 8;//random coordinates
	pass_in_loop(j, k);
	
	x = rand() % 5;
	if (x < 3)
	{
		x = x - 2;
	}
	srand(time(NULL));//seed time
	y = rand() % 3;
	if (y < 1)
	{
		y = y - 5;
	}
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(x, y, -15);//the coordinate vector (x,y,z)
	j = rand() % 8;
	k = rand() % 8;//random coordinates
	pass_in_loop(j, k);
	
	glColor3ub(255, 255, 0);//yellow color for bonus point as RBG color components
	x = rand() % 2;
	if (x < 2)
	{
		x = x - 5;
	}
	srand(time(NULL));//seed time
	y = rand() % 3;
	if (y < 2)
	{
		y = y + 5;
	}
	glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
	glTranslatef(x, y, -20);//the coordinate vector (x,y,z)
	j = rand() % 10;
	k = rand() % 10;//random coordinates
	pass_in_loop(j, k);
	
	glFlush();//refresh the buffers in order to prevent leakage of data
}



//Display adjustments
void GL_Setup(int width, int height) {
	glEnable(GL_TEXTURE_2D);
	
	
	glMatrixMode(GL_PROJECTION);//specify which matrix is the current matrix,for example as mentioned above, 3x3 matrix at the top-left,top,top-right,bottom etc regions.
	glEnable(GL_DEPTH_TEST);//to see the depth or intensity of the region being constant,if not then it will try to retain its previous value.
	glLoadIdentity();
	
	gluPerspective(45, (float)width / height, .1, 100);//the perspective of the circle as seen from the background and foreground. At 45*,with 1080/720 of aspect ratio in the x(width) and y(height) direction,-1 being the distance from foreground and 100 being the distance from background.
	
	glMatrixMode(GL_MODELVIEW);//to have a feasible view of the matrix.

	
}
void clear_screen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clean GL screen
	glutSwapBuffers();//clean buffer
	glFlush();//refresh elements
}
//Mouse function
void mouse(int button, int state, int x, int y) {
	if (state != GLUT_DOWN)//if the left mouse button is not pressed then return back to the function.In this way compilation time can be reduced.
		return;
	float r1 = 0.994328;//the depth of each circle in the 3D space is 0.994328 for red,0.995996 for yellow and 1.000000 for black foreground.This measurement is important to match the coordinate of the mouse cursor to the circle

	GLfloat depth;//the depth of the circle elements.

	glReadPixels(x, window_height - y - 1, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);//check the depth of each element being (x,y,space(x),space(y),depth_of_component,floating point value,variable)

	x_cor = x; y_cor = y;//store them globally, used for restarting the game.

	if (textures != NULL)
	{
		timer = true;

		//printf("Clicked on pixel depth %f\n",depth);//This is especially commented to check the depth of the elements.Feel free to uncomment this line and check the depth in the 3D space.
		if ((x > 480 && x < 680) && (y > 300 && y < 360)) {//
			x_cor = x; y_cor = y;
			clear_screen();
			printf("\nclick!");
			is_running = false;//TURN OFF THE MAIN MENU.
			health1 = 1;
			if (is_fade_button == true) {// FOR adding the effect after Pressing button 'START'.
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the window

				glLoadIdentity();
				glTranslatef(0, 0, -15);



				glBindTexture(GL_TEXTURE_2D, textures[0]);

				//to keep the circle in its specified field.without this function,the circle will dim eventually.
				glBegin(GL_QUADS);
				glColor3f(1, 1, 0);
				glTexCoord2f(0.0f, 0.0f); 	glVertex2f(-1.0f, 0.0f);
				glTexCoord2f(0.0f, 1.0f);   glVertex2f(2.0f, 0.0f);
				glColor3f(1, 1, 0);
				glTexCoord2f(1.0f, 1.0f);  glVertex2f(2.0f, 1.0f);
				glTexCoord2f(1.0f, 0.0f);  glVertex2f(-1.0f, 1.0f);
				glEnd();
				glutSwapBuffers();
				glDeleteTextures(1, textures);
				for (float h = -3; h <= 0.2; h = h + 0.02)
				{

					glLoadIdentity();
					if (h >= 0) {
						glTranslatef(0 + h, 0, -15);
						//to keep the circle in its specified field.without this function,the circle will dim eventually.
						glBegin(GL_QUADS);
						glColor3f(1, 0, 0);
						glVertex2f(-1.0f, 0.0f);
						glVertex2f(2.0f, 0.0f);
						glColor3f(1, 0, 0);
						glVertex2f(2.0f, 1.0f);
						glVertex2f(-1.0f, 1.0f);
						glEnd();
						glutSwapBuffers();
					}


				}
				Sleep(300);
				is_fade_button = false;
				glDeleteTextures(1, textures);
				textures = 0;
			}
			SoundEngine->stopAllSounds();
			char* name_1 = "Music\01_Golden_Sky.mp3";
			SoundEngine->play2D(name_1, GL_TRUE);
			return;

		}

		if ((x > 480 && x < 680) && (y > 410 && y < 480))//FOR adding the effect on pressing 'EXIT' button.
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the window

			glLoadIdentity();
			glTranslatef(0, 0, -15);



			glBindTexture(GL_TEXTURE_2D, textures[1]);

			head_1();
			glutSwapBuffers();

			for (float h = -3; h <= 0.2; h = h + 0.02)
			{

				glLoadIdentity();
				if (h >= 0) {
					glTranslatef(0 + h, 0, -15);
					//to keep the circle in its specified field.without this function,the circle will dim eventually.
					glBegin(GL_QUADS);
					glColor3f(1, 0, 0);
					glVertex2f(-1.0f, -2.0f);
					glVertex2f(2.0f, -2.0f);
					glColor3f(1, 0, 0);
					glVertex2f(2.0f, -1.0f);
					glVertex2f(-1.0f, -1.0f);
					glEnd();
					glutSwapBuffers();
				}


			}
			Sleep(300);
			
			textures == 0;
			exit(0);
		}
	}

	if ((x > 826 && x < 886) && (y > 18 && y < 67)) 
	{
		Pause_0 = true;
		reset_game = true;
		

		return;

	}

	
	std::cout << x << " " << y;
	if (depth < r1)//for red
	{
		Beep(1500, 400);//if clicked on red then beep(hertz,milliseconds)
		
		i = i + 10;//for points.Increment each time red circle is pressed
		printf("\n%d points\n", i);//display points
		clear_screen();
		
		
	}
	else if (depth == 1.0)//for background
	{
		i = i - 10;//negative points for not clicking on element
		printf("\nwrong!Soryy -10 points \n");//display message
		clear_screen();	
		return;
	}
	else//for bonus points
	{
		Beep(523, 500);//if clicked on yellow then beep(hertz,milliseconds)
		i = i + 20;//add 20 more points.
		printf("\n%d points\n", i);//display
		clear_screen();
		
	}
	glFlush();//refresh elements
}


//function call to make a circle,waiting time,mouse cursor response and timer.
void main_loop_function() {

if (lose_state == true)//LEVEL LOST screen.
{
	reset_game = true;
	work_all = false;
	clear_screen();
	
	
	you_but_1();//'YOU'
	glBindTexture(GL_TEXTURE_2D, lose_but[0]);//'LOST'
		
		win_lose();//position of the 'LOST!' image.
		
		glBindTexture(GL_TEXTURE_2D, Pause[1]);//'RESTART'
		head_2();


		glBindTexture(GL_TEXTURE_2D, ext_but[0]);//'EXIT'
		head_1();
		
		
		glutSwapBuffers();
		if (reset_game == true)//reset game.
		{
			if ((x_cor > 480 && x_cor < 680) && (y_cor > 300 && y_cor < 360)) {

				

				i = 0;
				count = 0;
				Pause_0 = false;
				reset_game = false;
				lose_state = false;
				work_all = true;
				beep_done = true;
			}
			if ((x_cor > 480 && x_cor < 680) && (y_cor > 410 && y_cor < 480))
			{
				exit(0);
			}
		}
		
		Sleep(200);


}

glutMouseFunc(mouse);
		

	  if (work_all == true) {


		  if (i < 0)
		  {
			  i = 0;
		  }

		  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the window
		  if (is_running == true) {//MAIN MENU BUTTONS


			  build_buttons();//display 'TITLE' of the game, along with 'START' and 'EXIT' button options.
			  glBindTexture(GL_TEXTURE_2D, tgt_score[0]);//target score buffer.
			  glLoadIdentity();
			  glTranslatef(0, 0, -15);
			  glColor3f(1, 1, 1);

			  //to keep the circle in its specified field.without this function,the circle will dim eventually.
			  glBegin(GL_QUADS);

			  glTexCoord2f(0.0f, 0.0f);	glVertex2f(-3.0f, -6.0f);
			  glTexCoord2f(0.0f, 1.0f);  glVertex2f(4.0f, -6.0f);
			  glTexCoord2f(1.0f, 1.0f); glVertex2f(4.0f, -4.0f);
			  glTexCoord2f(1.0f, 0.0f); glVertex2f(-3.0f, -4.0f);

			  glEnd();
			  glutSwapBuffers();
			  glFlush();

		  }


		  drawFilledSun();//random circles function.

		  if (is_fade_button == false)//Pause button on top right side of the screen.
		  {

			  glBindTexture(GL_TEXTURE_2D, Pause[0]);
			  glLoadIdentity();//to keep the circle in its specified field.without this function,the circle will dim eventually.
			  glTranslatef(0, 0, -15);
			  glColor3f(1, 1, 1);

			  //to keep the circle in its specified field.without this function,the circle will dim eventually.
			  glBegin(GL_QUADS);

			  glTexCoord2f(0.0f, 0.0f); glVertex2f(5.0f, 5.0f);
			  glTexCoord2f(0.0f, 1.0f); glVertex2f(6.0f, 5.0f);
			  glTexCoord2f(1.0f, 1.0f); glVertex2f(6.0f, 6.0f);
			  glTexCoord2f(1.0f, 0.0f); glVertex2f(5.0f, 6.0f);
			  glEnd();
		  }
		  if (Pause_0 == true)//Pause state TURNED ON.
		  {
			  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the window
			  glBindTexture(GL_TEXTURE_2D, Pause[1]);//Reset button
			  head_2();
			  
			  glBindTexture(GL_TEXTURE_2D, ext_but[0]);//exit button
			  head_1();
			  
			  if (reset_game == true)//reset game
			  {
				  if ((x_cor > 480 && x_cor < 680) && (y_cor > 300 && y_cor < 360)) {//reset game if pressed on reset.

					  clear_screen();

					  i = 0;
					  count = 0;
					  Pause_0 = false;
					  reset_game = false;

				  }
				  if ((x_cor > 480 && x_cor < 680) && (y_cor > 410 && y_cor < 480))//exit game, if pressed on exit.
				  {
					  exit(0);
				  }
			  }


		  }

		  if (i == 0)//if score is 0.
		  {
			 
			  num_zeroth();//zeroth number.
			
		  }
		  //call to create a circle
		  //mouse function
		  if ((i >= 10) && (i < 100))// if score is between 10 and 100
		  {
			  int m = i / 10;
			  glBindTexture(GL_TEXTURE_2D, num_textures[m]);//iterative ones place.
			  num_ones();
			  num_zeroth();//'0' at zeroth place.
		  }
		  else if ((i >= 100) && (i < 200))//if the score is between 100 and 200
		  {
			  if (i == 100)// if score is 100.
			  {
				  glBindTexture(GL_TEXTURE_2D, num_textures[1]);//'1' at twos place.
				  num_twos();
				  glBindTexture(GL_TEXTURE_2D, num_textures[0]);//'0' at ones place.
				  num_ones();
				  num_zeroth();//'0' at zeroth place.

			  }
			  if ((i > 100) && (i < 200))//if score is between 100 and 200.
			  {
				  glBindTexture(GL_TEXTURE_2D, num_textures[1]);//'1' at twos place.
				  num_twos();
				  int out_0 = (i - 100) / 10;
				  glBindTexture(GL_TEXTURE_2D, num_textures[out_0]);// iterative ones place.
				  num_ones();

				  num_zeroth();//'0' at zeroth place.
			  }

		  }
		  else if ((i >= 200) && (i < 300))// if the score '>=' 200 and '<' 300.
		  {

			  if (i == 200)//if score reaches 200.
			  {
				  glBindTexture(GL_TEXTURE_2D, num_textures[2]);//'2'at twos place
				  num_twos();
				  glBindTexture(GL_TEXTURE_2D, num_textures[0]);//zero at ones place.
				  num_ones();
				
				  num_zeroth();//zero at zeroth place.


			  }
			  if ((i > 200) && (i < 300))//if score is between 200 and 300.
			  {
				  glBindTexture(GL_TEXTURE_2D, num_textures[2]);//'2'at twos place
				  num_twos();
				  int out_0 = (i - 200) / 10;
				  glBindTexture(GL_TEXTURE_2D, num_textures[out_0]);//iterative ones place.
				  num_ones();
				  num_zeroth();//zero at zeroth place.
			  }

		  }
		  Sleep(100);//sleep for 100ms
		  glutSwapBuffers();//reset the pixel intensities so that it makes a random flicker
		 if(timer==true)
		  count++;//initially set as 0,this iterates for every millisecond
	  }
	if (count >= 510 && count < 599)//if the clock is at 53rd to 88th second then start beeping for the countdown
	{
		Beep(hz, 300);//hz is 600,defined globally
		hz = hz + 10;//add +10 to the hertz for different sound effects
	}
	
	glFlush();//refresh elements
	if (count > 600)//at approx 90th second, the game stops
	{
		if (beep_done = true)
		{
			
			Beep(300, 200);//beep end of the game
			beep_done = false;
		}
		if (i >= k)//k depends on the level of difficulty.i is the number of points you have scored.
		{	/*
				PLOT the texture for WIN state.
			*/
			clear_screen();
			lose_state = false;// no lose state.
			reset_game = true;//TURN ON reset_game to ON, retreive the coordinates and reset the game.
			
			work_all = false;//dont want the game running when we have already won the level. Condition stays till the counters are reset.
			
			you_but_1();//'YOU'
			glBindTexture(GL_TEXTURE_2D, won_but[0]);
			win_lose();//'WIN'


			glBindTexture(GL_TEXTURE_2D, Pause[1]);
			head_2();//''RESET

			glBindTexture(GL_TEXTURE_2D, ext_but[0]);
			head_1();//'EXIT'


			glutSwapBuffers();
			if (reset_game == true)//reset game
			{
				if ((x_cor > 480 && x_cor < 680) && (y_cor > 300 && y_cor < 360)) {//if pressed at reset.

					clear_screen();
				
					//clean buffer
					i = 0;
					count = 0;
					Pause_0 = false;
					reset_game = false;
					beep_done = true;
					work_all = true;

				}
				if ((x_cor > 480 && x_cor < 680) && (y_cor > 410 && y_cor < 480))//exit game
				{
					exit(0);
				}
			}

			Sleep(200);
			
			
		}
		else//if the level is lost then turn on the lose_state.//beginning of main_loop_function().
		{
			beep_done = false;
			lose_state = true;
			clear_screen();

		}
		
		
		
	}

}

int LoadImage(char *filename)//to acces the image file from memory using DevIL library.
{
	ILboolean success;
	ILuint image;

	ilGenImages(1, &image); /* Generation of one image name */
	ilBindImage(image); /* Binding of image name */
	success = ilLoadImage(filename); /* Loading of the image filename by DevIL */

	if (success) /* If no error occured: */
	{
		/* Convert every colour component into unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (!success)
		{
			return -1;
		}
	}
	else
		return -1;

	return image;
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);//to take the arguments,in command prompt
	glutInitWindowSize(window_width, window_height);//set the width of the window.
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);//RGB,double buffered window.used for the circle dimensions
	glutCreateWindow("Consistency");//title
	glutIdleFunc(main_loop_function);//to handle the operations.
	srand(time(NULL));//seed for time	
	
	GL_Setup(window_width, window_height);//call the display adjustment function
	
	glGenTextures(2, textures);
	int    image[4];

	int num[8];

	int symbol[3];

									


	
	ilInit();/* OpenGL 2D generic init */
	argv[0] = "Images\Capture.jpg";	
	argv[1] = "Images\Capture1.jpg";
	argv[2] = "Images\Capture2.jpg";
	for (int p = 0; p <= 2; p++)
	{
		image[p] = LoadImage(argv[p]);
		if (image[p] == -1)
		{
			printf("Can't load picture \n");
			std::cin >> a;
			return -1;
		}
		glGenTextures(1, &textures[p]); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, textures[p]); /* Binding of texture name */
		bind_img();
	}
	char* exit_button = "Images\Capture1.jpg";
	image[0] = LoadImage(exit_button);
	glGenTextures(1, &ext_but[0]); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, ext_but[0]); /* Binding of texture name */
	bind_img();
	char* lose = "Images\LOSE.jpg";
	image[1] = LoadImage(lose);
	glGenTextures(1, &lose_but[0]); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, lose_but[0]); /* Binding of texture name */
	bind_img();
	char* you = "Images\YOU.jpg";
	image[2] = LoadImage(you);
	glGenTextures(1, &you_but[0]); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, you_but[0]); /* Binding of texture name */
	bind_img();
	char* won = "Images\WON.jpg";
	image[3] = LoadImage(won);
	glGenTextures(1, &won_but[0]); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, won_but[0]); /* Binding of texture name */
	bind_img();
	char* tgt_scr = "Images\TARGET.jpg";
	image[3] = LoadImage(tgt_scr);
	glGenTextures(1, &tgt_score[0]); /* Texture name generation */
	glBindTexture(GL_TEXTURE_2D, tgt_score[0]); /* Binding of texture name */
	bind_img();
	int q = 3;
	argv[3] = "Images\num0.jpg";
	argv[4] = "Images\num1.jpg";
	argv[5] = "Images\num2.jpg"; 
	argv[6] = "Images\num3.jpg";
	argv[7] = "Images\num4.jpg";
	argv[8] = "Images\num5.jpg";
	argv[9] = "Images\num6.jpg";
	argv[10] = "Images\num7.jpg";
	argv[11] = "Images\num8.jpg";
	argv[12] = "Images\num9.jpg";
	argv[13] = "Images\Pause.jpg";
	argv[14] = "Images\Restart.jpg";
	
	for (int p = 0; p <= 9; p++)
	{
		num[p] = LoadImage(argv[q]);

		glGenTextures(1, &num_textures[p]); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, num_textures[p]); /* Binding of texture name */
		bind_img();
		q = q + 1;
	}
	q = 13;
	for (int u = 0; u <=1 ; u++)
	{
		symbol[u] = LoadImage(argv[q]);
		glGenTextures(1, &Pause[u]); /* Texture name generation */
		glBindTexture(GL_TEXTURE_2D, Pause[u]); /* Binding of texture name */
		bind_img();
		q = q + 1;
	}
	glutMainLoop();//iterate again	
	
		system("cls");
		return 0;
}

//Delivering creativity in the form of entertainment.
