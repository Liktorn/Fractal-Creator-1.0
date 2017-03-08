#include <iostream>
#include <cstdint>
#include <memory>
#include <time.h>
#include "Bitmap.h"
#include "Mandelbrot.h"

using namespace std;
using namespace bw;

int main() {

	int const WIDTH = 800;
	int const HEIGHT = 600;


	Bitmap bitmap(WIDTH, HEIGHT);

	double min = 999999;
	double max = -999999;

	unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 });
	unique_ptr<int[]> fractal(new int[WIDTH * HEIGHT]{ });

	int timer = time(NULL);
	cout << "Time Start: " << timer << endl;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			double xFractal = (x - WIDTH / 2-200) * 2.0 / HEIGHT;
			double yFractal = (y - HEIGHT / 2) * 2.0 / HEIGHT;

			int iterations = Mandelbrot::getIterations(xFractal, yFractal);

			fractal[y * WIDTH + x] = iterations;

			if(iterations != Mandelbrot::MAX_ITERATIONS)
				histogram[iterations]++;

			

			/*if (yFractal < min) min = yFractal;
			if (yFractal > max) max = yFractal;*/
		}
		//cout << y << endl;
	}
	//bitmap.setPixel(x, y, 255, 0, 0);


	int total = 0;
	for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
		total += histogram[i];
	}

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			int iterations = fractal[y * WIDTH + x];
			uint8_t color = (uint8_t)(256 * (double)iterations / Mandelbrot::MAX_ITERATIONS);

			double hue = 0.0;
			for (int i = 0; i <= iterations; i++) {
				hue += ((double)histogram[i]) / total;
			}

			color = color * color * color;

			bitmap.setPixel(x, y, 0, color, 0);

			if (color < min) min = color;
			if (color > max) max = color;
		}
	}


	cout << "Time Finished: " << time(NULL) << endl;
	cout << "Time taken: " << time(NULL) - timer << endl;


	bitmap.write("test.bmp");

	cout << "KLART!!!" << endl;

	return 0;
}
