#include <iostream>

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
para1_fade, para2_fade, para3_fade, para4_fade;

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
		1, 1, 1, 1, 790, 345, .15, .15, 1);
	print("(1DS15CS417)",
		1, 1, 1, 1, 840, 320, .1, .1, 1);

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
	print("Summary", 1, 1, 1, 1, 75, 650, .3, .3, 1.5);

	print("As children, we are taught to follow, not to lead. We are taught to learn, not to explore.",
		1, 1, 1, para1_fade, 75, 575, .125, .125, 1.25);
	print("We are taught to by heart, not to understand.",
		1, 1, 1, para1_fade, 75, 550, .125, .125, 1.25);

	print("When we grow up, things don’t change. We are given a meagre choice of either choosing",
		1, 1, 1, para2_fade, 75, 475, .125, .125, 1.25);
	print("to be a Doctor or an Engineer, and the rest of the options are at bleak focus. ",
		1, 1, 1, para2_fade, 75, 450, .125, .125, 1.25);

	print("Choosing to be a doctor is a rich man’s dream.",
		1, 1, 1, para3_fade, 75, 375, .125, .125, 1.25);
	print("Ending up as an engineer has become a curse. ",
		1, 1, 1, para3_fade, 75, 350, .125, .125, 1.25);

	print("Engineering is a field to invent and innovate, not to follow orders from higher officials.",
		1, 1, 1, para4_fade, 75, 275, .125, .125, 1.25);
	print("We might as well study the lives of Hitler’s Soldiers if we were to do so",
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
	glColor3ub(0, 0, 0);
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
	glColor3ub(0, 0, 0);
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
	glColor3ub(0, 0, 0);
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
	glColor3ub(0, 0, 0);
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
	drawCircle(45, 350, 223, 189, 31, 5);
}

// Function to Render Scene
void renderScene(void)
{
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
	case 'b':
	case 'B':
		if (SCENE_ID == 0)
			break;
		SCENE_ID--;
		break;
	case 'n':
	case 'N':
		SCENE_ID++;
		break;
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

	glutDisplayFunc(renderScene);

	glutKeyboardFunc(keyPress);
	glutMouseFunc(mouseClick);

	initializeScreen();

	glutTimerFunc(25, update, 0);

	glutMainLoop();

	return 0;
}