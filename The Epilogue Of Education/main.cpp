#include <iostream>
#include <math.h>

// Apple Specific Compatibility Issues
#ifdef __APPLE__
	#include "GLUT/glut.h"
#else
	#include "GL\glut.h"
#endif

#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;

// Variables for Animator Faders
GLfloat title_fade,
intro_next_text_appear, summary_next_text_appear,
para1_fade, para2_fade, para3_fade, para4_fade,
kg_a_fade, kg_apple_fade, kg_b_fade, kg_ball_fade, kg_soon_fade, kg_subtitle_1_appear;

// Function to Print Text
void print(char *string,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize)
{
	glPushMatrix();

	glColor4f(r, g, b, a);
	glTranslatef(x, y, 0);
	glScalef(w, h, 0);
	glPointSize(strokeSize);
	glLineWidth(strokeSize);

	while (*string)
		glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, *string++);

	glPopMatrix();
}

// Function to draw Circle
void drawCircle(GLfloat x, GLfloat y, GLfloat r, GLfloat g, GLfloat b, GLfloat radius)
{
	int triangleAmount = 1000;
	GLfloat twicePi = 2.0f * PI;

	glLineWidth(5.0);

	glBegin(GL_LINES);
	glColor3ub(r, g, b);
	for (int i = 0; i <= triangleAmount; i++) {
		glVertex2f(x, y);
		glVertex2f(x + (radius * cos(i * twicePi / triangleAmount)), y + (radius * sin(i * twicePi / triangleAmount)));
	}
	glEnd();

	glLineWidth(1.0);
}

// Function to draw Teacher
void drawTeacher()
{
	// Neck
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(203, 166, 108); // Darker Skin
	glVertex2f(507, 380);
	glVertex2f(507, 360);
	glVertex2f(513, 380);
	glVertex2f(513, 360);
	glEnd();
	glLineWidth(1);

	// Face
	drawCircle(510, 407,
		232, 190, 123, // Lighter Skin
		30);

	// Arms
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123);
	glVertex2f(470, 340);
	glVertex2f(470, 240);
	glVertex2f(475, 340);
	glVertex2f(475, 240);
	glVertex2f(480, 340);
	glVertex2f(480, 240);

	glVertex2f(540, 340);
	glVertex2f(540, 240);
	glVertex2f(545, 340);
	glVertex2f(545, 240);
	glVertex2f(550, 340);
	glVertex2f(550, 240);
	glEnd();
	glLineWidth(1);

	// Top
	glBegin(GL_POLYGON);
	glColor3ub(229, 49, 49); // Red
	glVertex2f(460, 370);
	glVertex2f(560, 370);
	glVertex2f(540, 300);
	glVertex2f(480, 300);
	glEnd();

	// Skirt
	glBegin(GL_POLYGON);
	glColor3ub(229, 49, 49); // Red
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glVertex2f(560, 180);
	glVertex2f(460, 180);
	glEnd();

	// Ribbon
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(37, 107, 202);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glEnd();
	glLineWidth(1);

	// Legs
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123);
	glVertex2f(490, 180);
	glVertex2f(490, 150);
	glVertex2f(495, 180);
	glVertex2f(495, 150);

	glVertex2f(525, 180);
	glVertex2f(525, 150);
	glVertex2f(530, 180);
	glVertex2f(530, 150);
	glEnd();
	glLineWidth(1);
}

/*
* Scene 0 - Introduction Screen
*/
void introduction(void)
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("The Epilogue of Education",
		1, 1, 1, title_fade, 280, 380, .3, .3, 2);

	print("by Raja Rajan A.",
		1, 1, 1, title_fade, 790, 345, .15, .15, 1);
	print("(1DS15CS417)",
		1, 1, 1, title_fade, 840, 320, .1, .1, 1);

	print("Press N to read the story...",
		1, 1, 1, intro_next_text_appear, 560, 10, .09, .09, 1);
}

/*
* Scene 1 - Summary Screen
*/
void summary(void)
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("Summary",
		1, 1, 1, 1, 75, 650, .3, .3, 1.5);

	print("As children, we are taught to follow, not to lead. We are taught to learn, not to explore.",
		1, 1, 1, para1_fade, 75, 575, .125, .125, 1.25);
	print("We are taught to by heart, not to understand.",
		1, 1, 1, para1_fade, 75, 550, .125, .125, 1.25);

	print("When we grow up, things don't change. We are given a meagre choice of either choosing",
		1, 1, 1, para2_fade, 75, 475, .125, .125, 1.25);
	print("to be a Doctor or an Engineer, and the rest of the options are at bleak focus. ",
		1, 1, 1, para2_fade, 75, 450, .125, .125, 1.25);

	print("Choosing to be a doctor is a rich man's dream.",
		1, 1, 1, para3_fade, 75, 375, .125, .125, 1.25);
	print("Ending up as an engineer has become a curse. ",
		1, 1, 1, para3_fade, 75, 350, .125, .125, 1.25);

	print("Engineering is a field to invent and innovate, not to follow orders from higher officials.",
		1, 1, 1, para4_fade, 75, 275, .125, .125, 1.25);
	print("We might as well study the lives of Hitler�s Soldiers if we were to do so",
		1, 1, 1, para4_fade, 75, 250, .125, .125, 1.25);
	print("for the rest of out lives.",
		1, 1, 1, para4_fade, 75, 225, .125, .125, 1.25);

	print("Press N to move on...",
		1, 1, 1, summary_next_text_appear, 580, 10, .09, .09, 1);
}

/*
* Scene 2 - Kindergarten
*/
void kindergarten(void)
{
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 800);
	glEnd();
	glLineWidth(1);

	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 800);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(0, 800);
	glVertex2f(200, 700);
	glVertex2f(200, 175);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);

	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(200, 700);
	glColor3ub(251, 242, 233); // Light Brown
	glVertex2f(1400, 700);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(1400, 175);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glEnd();

	// Border for Center Wall
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 700);
	glVertex2f(1400, 700);
	glVertex2f(1400, 175);
	glVertex2f(200, 175);
	glEnd();
	glLineWidth(1);

	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(166, 148, 124); // Dark Brown
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();

	// Border for Floor
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0); // Black
	glVertex2f(200, 175);
	glVertex2f(1400, 175);
	glVertex2f(1400, 75);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);

	// Outside
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();

	// Door Hinges
	glLineWidth(6);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();
	glLineWidth(1);

	// Door
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(180, 540);
	glVertex2f(30, 520);
	glVertex2f(30, 180);
	glVertex2f(180, 165);
	glEnd();

	// Door Knob
	drawCircle(45, 350,
		223, 189, 31, // Goldish Yellow
		5);

	// Blackboard
	glBegin(GL_POLYGON);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();

	// Blackboard Border
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(450, 540);
	glVertex2f(1100, 540);
	glVertex2f(1100, 300);
	glVertex2f(450, 300);
	glEnd();
	glLineWidth(1);

	// Teacher in Kindergarten
	drawTeacher();

	// Teacher's Table
	glBegin(GL_POLYGON);
	glColor3ub(63, 36, 19); // Chocolate Brown
	glVertex2f(510, 260);
	glVertex2f(470, 200);
	glVertex2f(1080, 200);
	glVertex2f(1040, 260);
	glEnd();

	// Teacher's Table Edge
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(470, 200);
	glVertex2f(470, 190);
	glVertex2f(1080, 190);
	glVertex2f(1080, 200);
	glEnd();

	// Left Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(530, 190);
	glVertex2f(540, 190);
	glVertex2f(540, 130);
	glVertex2f(530, 130);
	glEnd();

	// Right Table Leg
	glBegin(GL_POLYGON);
	glColor3ub(54, 28, 16); // Darker Chocolate Brown
	glVertex2f(1020, 190);
	glVertex2f(1010, 190);
	glVertex2f(1010, 130);
	glVertex2f(1020, 130);
	glEnd();

	// Left Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(400, 150);
	glVertex2f(700, 150);
	glVertex2f(730, 120);
	glVertex2f(370, 120);
	glEnd();

	// Left Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(370, 120);
	glVertex2f(370, 115);
	glVertex2f(730, 115);
	glVertex2f(730, 120);
	glEnd();

	// Right Children's Desk
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); // Wood Brown
	glVertex2f(850, 150);
	glVertex2f(1150, 150);
	glVertex2f(1180, 120);
	glVertex2f(820, 120);
	glEnd();

	// Right Children's Desk Edge
	glBegin(GL_POLYGON);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(820, 120);
	glVertex2f(820, 115);
	glVertex2f(1180, 115);
	glVertex2f(1180, 120);
	glEnd();

	// First Kid
	drawCircle(480, 110,
		203, 166, 108, // Face Color #1 - Darker
		25);

	// Second Kid
	drawCircle(620, 110,
		232, 190, 123, // Face Color #2 - Lighter
		25);

	// Third Kid
	drawCircle(940, 110,
		232, 190, 123, // Face Color #2 - Lighter
		25);

	// Third Kid
	drawCircle(1080, 110,
		203, 166, 108, // Face Color #1 - Darker
		25);

	int hair_line;

	// First Kid's Hair
	hair_line = 400;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);

	// Second Kid's Hair
	hair_line = 540;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);

	// Third Kid's Hair
	hair_line = 860;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);

	// Fourth Kid's Hair
	hair_line = 1000;
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(20, 20, 20); // Almost Black
	glVertex2f(hair_line + 60, 138);
	glVertex2f(hair_line + 65, 128);

	glVertex2f(hair_line + 70, 140);
	glVertex2f(hair_line + 75, 130);

	glVertex2f(hair_line + 80, 140);
	glVertex2f(hair_line + 85, 130);

	glVertex2f(hair_line + 90, 138);
	glVertex2f(hair_line + 95, 128);
	glEnd();
	glLineWidth(1);

	print("A",
		1, 1, 1, kg_a_fade, 600, 440, .3, .3, 3);

	print("- Apple",
		1, 1, 1, kg_apple_fade, 655, 445, .2, .2, 1);

	print("B",
		1, 1, 1, kg_b_fade, 600, 380, .3, .3, 3);

	print("- Ball",
		1, 1, 1, kg_ball_fade, 655, 385, .2, .2, 1);

	print("... and so on",
		1, 1, 1, kg_soon_fade, 560, 220, .2, .2, 1.5);

	print("This is where our educational journey begins...",
		1, 1, 1, kg_subtitle_1_appear, 380, 30, .14, .14, 1);
}

// Function to Render Scene
void renderScene(void)
{
	// Switch to know which scene is playing
	switch (SCENE_ID)
	{
	case 0:
		introduction();
		break;
	case 1:
		summary();
		break;
	case 2:
		kindergarten();
		break;
	default:
		break;
	}

	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		std::cout << x << "\t" << 800 - y << "\n";
}

// Animator Updation Function
void update(int) {
	// Introduction
	if (SCENE_ID == 0) {
		if (title_fade < 1)
			title_fade += .003;
		else
			intro_next_text_appear = 1;
	}

	// Summary
	if (SCENE_ID == 1) {
		if (para1_fade < 1)
			para1_fade += .005;
		else
			if (para2_fade < 1)
				para2_fade += .005;
			else
				if (para3_fade < 1)
					para3_fade += .005;
				else
					if (para4_fade < 1)
						para4_fade += .005;
					else
						summary_next_text_appear = 1;
	}

	// Kindergarten
	if (SCENE_ID == 2) {
		if (kg_a_fade < 1)
			kg_a_fade += .01;
			else
				if (kg_apple_fade < 1)
					kg_apple_fade += .01;
				else
					if (kg_b_fade < 1)
						kg_b_fade += .01;
					else
						if (kg_ball_fade < 1)
							kg_ball_fade += .01;
						else
							if (kg_soon_fade < 1)
								kg_soon_fade += .005;
							else
								kg_subtitle_1_appear = 1;

	}

	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y)
{
	switch (key)
	{
	// Go to Previous Scene
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
	// Go to Next Scene
	case 'n':
	case 'N':
		SCENE_ID++;
		break;
	// Quit Story
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

// Function to Initialize Screen
void initializeScreen(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("OpenGL First Window");

	// Enables Transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Enable Smoothening
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

	// Display Function
	glutDisplayFunc(renderScene);

	// Input Functions
	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	// Timer Function
	// every 25 milliseconds, update function is called
	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}
