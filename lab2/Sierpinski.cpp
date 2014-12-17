/*
 * File: Sierpinski.cpp
 * ----------------------
 * Student ID: 5120379076
 * Name: 熊伟伦
 * This file is the starter project for the Sierpinski Triangle problem.
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

const double SQRT3 = sqrt(3);

GWindow* win;

void drawTriangle(GPoint a, GPoint b, GPoint c) {
  win->drawLine(a, b);
  win->drawLine(b, c);
  win->drawLine(c, a);
}

void drawTriangle_by_center(const GPoint& center, const double& len) {
	double center_x = center.getX();
	double center_y = center.getY();
	GPoint a(center_x-len/2, center_y-SQRT3/6*len);
	GPoint b(center_x+len/2, center_y-SQRT3/6*len);
	GPoint c(center_x, center_y+SQRT3/3*len);
	drawTriangle(a, b, c);
}

void drawSierpinski(const GPoint& center, const double& len, const int& order) {
	drawTriangle_by_center(center, len);
	int new_order = order-1;
	if (new_order > 0) {
		double center_x = center.getX();
		double center_y = center.getY();
		GPoint center_a(center_x-len/2, center_y+SQRT3/6*len);
		GPoint center_b(center_x+len/2, center_y+SQRT3/6*len);
		GPoint center_c(center_x, center_y-SQRT3/3*len);
		drawSierpinski(center_a, len/2, new_order);
		drawSierpinski(center_b, len/2, new_order);
		drawSierpinski(center_c, len/2, new_order);
	}
}

int main() {
	win = new GWindow(640, 480);
	double len = getReal("Please input the length of edge: ");
	int order = getInteger("Please input the order of the Sierpinski Triangle: ");
	GPoint center(320,(len>0)? 320: 160);
	if (order >= 0)
		drawTriangle_by_center(center, -len);
	if (order >= 1)
		drawSierpinski(center, len/2, order);
	return 0;
}
