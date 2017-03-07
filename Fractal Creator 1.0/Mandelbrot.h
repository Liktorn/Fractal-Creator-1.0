#pragma once



namespace bw{


class Mandelbrot{
public:
	static const int MAX_ITERATIONS = 10;

public:
	Mandelbrot();
	~Mandelbrot();

	static int getIterations(double x, double y);
};


}//namespace