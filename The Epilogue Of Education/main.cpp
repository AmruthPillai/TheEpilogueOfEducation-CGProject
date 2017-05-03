#include <iostream>
#include <time.h>
#include <math.h>

// Apple Specific Compatibility Issues
#ifdef __APPLE__
	#include "GLUT/glut.h"
#else
	#include "GL\glut.h"
#endif

// Define the value of PI, upto 12 decimal places
#define PI 3.141592653589

// ID to detect which scene the story is in.
int SCENE_ID;

// Variables for Animator Faders
GLfloat title_fade,
	intro_next_text_appear, summary_next_text_appear,
	para1_fade, para2_fade, para3_fade, para4_fade,
	kg_chap_fade, kg_title_fade,
	kg_a_fade, kg_apple_fade, kg_b_fade, kg_ball_fade, kg_soon_fade, kg_subtitle_1_appear,
	ps_chap_fade, ps_title_fade;

// Variables for Translation Animators
GLfloat trans_x_chap1, trans_x_title1,
	trans_x_chap2, trans_y_title2;

// Function to Create Delay
void delay(float secs) {
	float end = clock()/CLOCKS_PER_SEC + secs;
	while((clock()/CLOCKS_PER_SEC) < end);
}

// Function to Print Text
void print(char *string,
	GLfloat r, GLfloat g, GLfloat b, GLfloat a,
	GLint x, GLint y,
	GLfloat w, GLfloat h,
	GLfloat strokeSize) {
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

// Function to Draw Circle
void drawCircle(GLfloat x, GLfloat y,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat radius) {
    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = 0; i < 360; i += 5)
        glVertex2f(radius * sin(i * PI / 180) + x, radius * cos(i * PI / 180) + y);
    glEnd();
}

// Function to Draw Circle
void drawSemiCircle(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b,
	GLfloat radius,
	GLfloat start_angle, GLfloat end_angle) {
		glPushMatrix();

		glTranslatef(tx, ty, 0);
		glScalef(sx, sy, 0);

    glBegin(GL_POLYGON);
		glColor3ub(r, g, b);
    for (GLfloat i = start_angle; i < end_angle; i += 5)
        glVertex2f(radius * sin(i * PI / 180), radius * cos(i * PI / 180));
    glEnd();

		glPopMatrix();
}

// Function to Draw Arc
void drawArc(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat r, GLfloat g, GLfloat b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3ub(r, g, b);
  for ( GLfloat i = 90; i < 270; i++)
    glVertex2f(15 * sin(i * PI / 180), 15 * cos(i * PI / 180));
  glEnd();
	glPointSize(1);

	glPopMatrix();
}

// Function to Draw a Woman
void drawWoman(GLfloat tx, GLfloat ty, GLfloat sx, GLfloat sy,
	GLfloat hair_r, GLfloat hair_g, GLfloat hair_b,
	GLfloat top_r, GLfloat top_g, GLfloat top_b,
	GLfloat ribbon_r, GLfloat ribbon_g, GLfloat ribbon_b,
	GLfloat skirt_r, GLfloat skirt_g, GLfloat skirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

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

	// Hair
	drawSemiCircle(510, 420, 1, .6,
		hair_r, hair_g, hair_b,
		35, -90, 90);

	drawSemiCircle(485, 400, .4, 1,
		hair_r, hair_g, hair_b,
		35, -180, 0);

	// Left Eye
	drawCircle(505, 410,
		250, 250, 250,
		5);
	drawCircle(508, 408,
		10, 10, 10,
		2.5);

	// Right Eye
	drawCircle(530, 410,
		250, 250, 250,
		5);
	drawCircle(532, 408,
		10, 10, 10,
		2.5);

	// Smile
	drawArc(514, 388, .5, .3,
		20, 20, 20);

	// Nose
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(518, 405);
	glVertex2f(522, 398);
	glVertex2f(522, 398);
	glVertex2f(518, 395);
	glEnd();

	// Arms
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
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
	glColor3ub(top_r, top_g, top_b);
	glVertex2f(460, 370);
	glVertex2f(560, 370);
	glVertex2f(540, 300);
	glVertex2f(480, 300);
	glEnd();

	// Skirt
	glBegin(GL_POLYGON);
	glColor3ub(skirt_r, skirt_g, skirt_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glVertex2f(560, 180);
	glVertex2f(460, 180);
	glEnd();

	// Ribbon
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(ribbon_r, ribbon_g, ribbon_b);
	glVertex2f(480, 300);
	glVertex2f(540, 300);
	glEnd();
	glLineWidth(1);

	// Legs
	glLineWidth(10);
	glBegin(GL_LINES);
	glColor3ub(232, 190, 123); // Lighter Skin
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

	glPopMatrix();
}

void drawKidsShirtAndTrousers(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy,
	GLfloat shirt_r, GLfloat shirt_g, GLfloat shirt_b) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Bottom Shirt
	glColor3ub(shirt_r, shirt_g, shirt_b);
	glBegin(GL_POLYGON);
	glVertex2f(0, 20);
	glVertex2f(100, 20);
	glVertex2f(100, 100);
	glVertex2f(0, 100);
	glEnd();

	// Top Shirt
	glBegin(GL_POLYGON);
	glVertex2f(100, 100);
	glVertex2f(135, 105);
	glVertex2f(120, 175);
	glVertex2f(100, 200);
	glVertex2f(50, 180);
	glVertex2f(0, 200);
	glVertex2f(-20, 175);
	glVertex2f(-35, 105);
	glVertex2f(0, 100);
	glEnd();

	// Left Trouser
	glColor3ub(37, 107, 202);
	glBegin(GL_POLYGON);
	glVertex2f(0, 25);
	glVertex2f(0, -100);
	glVertex2f(35, -100);
	glVertex2f(65, 25);
	glEnd();

	// Right Trouser
	glBegin(GL_POLYGON);
	glVertex2f(35, 25);
	glVertex2f(65, -100);
	glVertex2f(100, -100);
	glVertex2f(100, 25);
	glEnd();

	glPopMatrix();
}


void drawKid(GLfloat tx, GLfloat ty,
	GLfloat sx, GLfloat sy) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glScalef(sx, sy, 0);

	// Neck
	drawSemiCircle(-1, -35, .6, 1,
		203, 166, 108,
		20, -90, 90);

	// Face
  drawCircle(0, 0,
		232, 190, 123,
		24);

	// Hands
	drawCircle(-42, -82,
		232, 190, 123,
		10);
	drawCircle(38, -82,
		232, 190, 123,
		10);

	// Shirt and Trousers
	drawKidsShirtAndTrousers(-32, -125,
		.6, .5,
		250, 0, 0);

	// Left Shoe
	drawSemiCircle(-21, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	// Right Shoe
	drawSemiCircle(18, -178,
		1.2, 1,
		20, 20, 20,
		10,
		-90, 90);

	glPopMatrix();
}

/*
* Scene 0 - Introduction Screen
*/
void introduction() {
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
void summary() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Summary Title
	print("Summary",
		1, 1, 1, 1, 75, 650, .3, .3, 1.5);

	// Summary Text
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

// Function to Draw Ceiling
void KG_drawCeiling() {
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
}

// Function to Draw Side Wall
void KG_drawSideWall() {
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
}

// Function to Draw Center Wall
void KG_drawCenterWall() {
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
}

// Function to Draw Floor
void KG_drawFloor() {
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
}

// Function to Draw Outside Background
void KG_drawOutside() {
	// Outside
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(0, 600);
	glVertex2f(180, 540);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(180, 165);
	glVertex2f(0, 75);
	glEnd();
}

// Function to Draw Door
void KG_drawDoor() {
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
}

// Function to Draw Kid's Head
void KG_drawKidsHead(GLfloat tx, GLfloat ty) {
	glPushMatrix();

	glTranslatef(tx, ty, 0);

	// Kid's Face
	drawCircle(480, 110,
		232, 190, 123, // Lighter Skin
		25);

	int hair_line;

	// Kid's Hair Strands
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

	glPopMatrix();
}

// Function to Draw Blackboard
void KG_drawBlackboard() {
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
}

// Function to Draw Teacher's Table
void KG_drawTeachersTable() {
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
}

// Function to Draw Children's Desks
void KG_drawChildrensDesks() {
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
}

/*
* Scene 2 - Kindergarten Title Screen
*/
void kindergartenTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 1",
		1, 1, 1, kg_chap_fade, 300 + trans_x_chap1, 400, .2, .2, 2);
	print("Kindergarten",
		1, 1, 1, kg_title_fade, 300 + trans_x_title1, 350, .3, .3, 2);
}

/*
* Scene 3 - Kindergarten
*/
void kindergarten() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	KG_drawCeiling();
	KG_drawSideWall();
	KG_drawCenterWall();
	KG_drawFloor();

	KG_drawOutside();

	KG_drawDoor();

	KG_drawBlackboard();

	// Teacher
	drawWoman(0, 0, 1, 1,
		60, 60, 60,
		229, 49, 49, // top
		37, 107, 202, // ribbon
		229, 49, 49 // skirt
	);

	KG_drawTeachersTable();

	KG_drawChildrensDesks();

	KG_drawKidsHead(0, 0);
	KG_drawKidsHead(140, 0);
	KG_drawKidsHead(460, 0);
	KG_drawKidsHead(600, 0);

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

/*
*	Scene 4 - Primary School Title Screen
*/
void primarySchoolTitleScreen() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Story Title
	print("CHAPTER 2",
		1, 1, 1, ps_chap_fade, 300 + trans_x_chap2, 400, .2, .2, 2);
	print("Primary School",
		1, 1, 1, ps_title_fade, 400, 250 + trans_y_title2, .3, .3, 2);
}

// Function to Draw Ceiling
void PS_drawCeiling() {
	// Ceiling
	glBegin(GL_POLYGON);
	glColor3ub(65, 105, 120); // Aqua
	glVertex2f(0, 800);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(1400, 650);
	glVertex2f(1400, 800);
	glEnd();

	// Border for Ceiling
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(0, 800);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(1400, 650);
	glVertex2f(1400, 800);
	glEnd();
}

// Function to Draw Side Wall
void PS_drawSideWall() {
	// Side Wall
	glBegin(GL_POLYGON);
	glColor3ub(176, 204, 217); // Light Aqua
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(100, 200);
	glVertex2f(0, 75);
	glEnd();

	// Border for Side Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(0, 700);
	glVertex2f(100, 650);
	glVertex2f(100, 200);
	glVertex2f(0, 75);
	glEnd();
}

// Function to Draw Center Wall
void PS_drawCenterWall() {
	// Center Wall
	glBegin(GL_POLYGON);
	glColor3ub(120, 160, 175);
	glVertex2f(100, 650);
	glVertex2f(700, 650);
	glColor3ub(164, 191, 203);
	glVertex2f(700, 200);
	glVertex2f(100, 200);
	glEnd();

	// Border for Center Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(100, 650);
	glVertex2f(700, 650);
	glVertex2f(700, 200);
	glVertex2f(100, 200);
	glEnd();
}

// Function to Draw Dividing Wall
void PS_drawDividingWall() {
	// Dividing Wall
	glBegin(GL_POLYGON);
	glColor3ub(176, 204, 217); // Light Aqua
	glVertex2f(700, 650);
	glVertex2f(850, 800);
	glVertex2f(850, 75);
	glVertex2f(700, 200);
	glEnd();

	// Border for Dividing Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(700, 650);
	glVertex2f(850, 800);
	glVertex2f(850, 75);
	glVertex2f(700, 200);
	glEnd();
}

// Function to Draw Kitchen Wall
void PS_drawKitchenWall() {
	// Kitchen Wall
	glBegin(GL_POLYGON);
	glColor3ub(164, 191, 203);
	glVertex2f(850, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 75);
	glVertex2f(850, 75);
	glEnd();

	// Border for Kitchen Wall
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(850, 800);
	glVertex2f(1400, 800);
	glVertex2f(1400, 75);
	glVertex2f(850, 75);
	glEnd();
}

// Function to Draw Floor
void PS_drawFloor() {
	// Floor
	glBegin(GL_POLYGON);
	glColor3ub(120, 160, 175);
	glVertex2f(100, 200);
	glVertex2f(700, 200);
	glVertex2f(850, 75);
	glVertex2f(0, 75);
	glEnd();

	// Border for Floor
	glBegin(GL_LINE_LOOP);
	glColor3ub(0, 0, 0);
	glVertex2f(100, 200);
	glVertex2f(700, 200);
	glVertex2f(850, 75);
	glVertex2f(0, 75);
	glEnd();
}

// Function to Draw Door
void PS_drawDoor() {
	// Door
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 200);
	glVertex2f(300, 200);
	glEnd();

	// Border
	glLineWidth(5);
	glBegin(GL_LINES);
	glColor3ub(122, 76, 29); // Wood Dark Brown
	glVertex2f(300, 200);
	glVertex2f(300, 500);
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 500);
	glVertex2f(500, 200);
	glEnd();
	glLineWidth(1);
}

void PS_drawBackground() {
	glBegin(GL_POLYGON);
	glColor3ub(12, 172, 232); // Sky Blue
	glVertex2f(300, 500);
	glVertex2f(500, 500);
	glColor3ub(82, 163, 42); // Green Grass
	glVertex2f(500, 275);
	glVertex2f(300, 275);
	glEnd();
}

void PS_drawRoad() {
	glBegin(GL_POLYGON);
	glColor3ub(40, 40, 40);
	glVertex2f(300, 275);
	glVertex2f(500, 275);
	glVertex2f(500, 200);
	glVertex2f(300, 200);
	glEnd();

	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3ub(255, 255, 255);
	glVertex2f(300, 235);
	glVertex2f(380, 235);
	glVertex2f(420, 235);
	glVertex2f(500, 235);
	glEnd();
	glLineWidth(1);
}

void PS_drawOutside() {
	PS_drawBackground();
	PS_drawRoad();
}

void PS_drawKitchenCounter() {
	// Kitchen Counter
	glBegin(GL_POLYGON);
	glColor3ub(138, 82, 32); //Wood Brown
	glVertex2f(950, 300);
	glVertex2f(980, 325);
	glVertex2f(1300, 325);
	glVertex2f(1300, 300);
	glEnd();
}

void PS_drawKitchen() {
	glBegin(GL_POLYGON);
	glColor3ub(247, 239, 187);
	glVertex2f(950, 550);
	glVertex2f(1300, 550);
	glVertex2f(1300, 300);
	glVertex2f(950, 300);
	glEnd();

	drawWoman(620, 50, 1, 1,
		20, 20, 20,
		229, 49, 49, // top
		37, 107, 202, // bottom
		229, 49, 49 // skirt
	);

	// Hack to Hide Woman's Body
	glBegin(GL_POLYGON);
	glColor3ub(164, 191, 203);
	glVertex2f(1050, 300);
	glVertex2f(1200, 300);
	glVertex2f(1200, 140);
	glVertex2f(1050, 140);
	glEnd();
}
/*
*	Scene 5 - Primary School
*/
void primarySchool() {
	// Background
	glClearColor(0.05, 0.05, 0.05, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	PS_drawCeiling();
	PS_drawSideWall();
	PS_drawCenterWall();
	PS_drawDividingWall();
	PS_drawFloor();

	PS_drawDoor();

	PS_drawOutside();

	PS_drawKitchenWall();
	PS_drawKitchen();

	drawKid(250, 370,
		1, 1);
}

// Function to Render Scene
void renderScene() {
	// Switch to know which scene is playing
	switch (SCENE_ID) {
	case 0:
		introduction();
		break;
	case 1:
		summary();
		break;
	case 2:
		kindergartenTitleScreen();
		break;
	case 3:
		kindergarten();
		break;
	case 4:
		primarySchoolTitleScreen();
		break;
	case 5:
		primarySchool();
		break;
	default:
		break;
	}

	// glFush sends it to the Display Buffer
	glFlush();
}

// Function to Handle Mouse Clicks
void mouseClick(int button, int state, int x, int y) {
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

	// Kindergarten Title Screen
	if (SCENE_ID == 2) {
		if (trans_x_chap1 < 100)
			trans_x_chap1 += 1.5;
		if (trans_x_title1 < 100)
			trans_x_title1 += 1;

		if (kg_chap_fade < 1)
			kg_chap_fade += .01;

		if (kg_title_fade < 1)
			kg_title_fade += .01;
	}

	// Kindergarten
	if (SCENE_ID == 3) {
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

	// Primary School Title Screen
	if (SCENE_ID == 4) {
		if (trans_x_chap2 < 100)
			trans_x_chap2 += 1.5;
		if (trans_y_title2 < 100)
			trans_y_title2 += 1;

		if (ps_chap_fade < 1)
			ps_chap_fade += .01;

		if (ps_title_fade < 1)
			ps_title_fade += .01;
	}

	// Recalls the Display Function
	glutPostRedisplay();

	// Creates a Timer of 25ms
	glutTimerFunc(25, update, 0);
}

// Keyboard Action
void keyPress(unsigned char key, int x, int y) {
	switch (key) {
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
void initializeScreen() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1400, 0, 800);
}

// Main Function
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1400, 800);
	glutCreateWindow("The Epilogue of Education");

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
