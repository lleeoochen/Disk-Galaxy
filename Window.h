#pragma once

struct Window {
	Window(int width, int height) { WIDTH = width; HEIGHT = height; }
	int WIDTH;
	int HEIGHT;
};