#pragma once

//color values go from 0 -> 1
//sometimes 0->255 ig :/ in esp.cpp lmao
struct Color {
	float values[4]; //r,g,b,a

	Color() {
		values[0] = 0;
		values[1] = 0;
		values[2] = 0;
		values[3] = 1.f;
	}

	Color(float r, float g, float b, float a = 255) {
		this->values[0] = r;
		this->values[1] = g;
		this->values[2] = b;
		this->values[3] = a;
	}

	Color(std::vector<float> arr) {
		this->values[0] = arr[0];
		this->values[1] = arr[1];
		this->values[2] = arr[2];
		this->values[3] = arr[3];
	}

	Color operator+(float v) {
		return Color(getR() + v, getB() + v, getG() + v, getA());
	}

	//doesn't work
	Color operator=(std::vector<float> arr) {
		//this->values[0] = arr[0];
		//this->values[1] = arr[1];
		//this->values[2] = arr[2];
		//this->values[3] = arr[3];
		return Color(arr[0], arr[1], arr[2], arr[3]);
	}

	float* ToArray() {
		float ret[4];
		ret[0] = getR();
		ret[1] = getB();
		ret[2] = getG();
		ret[3] = getA();

		return ret;
	}

	//for conversion to json
	std::vector<float> ToVector() {
		std::vector<float> ret;
		ret.push_back(getR());
		ret.push_back(getG());
		ret.push_back(getB());
		ret.push_back(getA());

		return ret;
	}

	Color To255() {
		return Color(values[0] * 255, values[1] * 255, values[2] * 255, values[3] * 255);
	}

	float getA() {
		return values[3];
	}
	float getR() {
		return values[0];
	}
	float getG() {
		return values[1];
	}
	float getB() {
		return values[2];
	}
};