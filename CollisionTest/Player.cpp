#include "Player.h"
#include <math.h>
#include <iostream>

#define SIN(x) sin(x * 3.141592653589 / 180)
#define COS(x) cos(x * 3.141592653589 / 180)


Player::Player(int xPos, int yPos, int width, int height) :
	_xPosition(xPos), _yPosition(yPos), _width(width), _height(height)
{
	CreatePoints();

}

Player::~Player() {
	for (int i = 0; i < 2; i++)
	{
		delete _drawPoints[i];
	}

	delete[] _drawPoints;
}

void Player::CreatePoints() {
	_drawPoints = new double* [2];

	for (int i = 0; i < 2; i++)
	{
		_drawPoints[i] = new double[3];
	}

	_drawPoints[0][0] = -_width;
	_drawPoints[0][1] = 0;
	_drawPoints[0][2] = _width;

	_drawPoints[1][0] = _height;
	_drawPoints[1][1] = -_height;
	_drawPoints[1][2] = _height;
}

double** Player::GetPoints() {
	return _drawPoints;
}

double Player::GetXPosition() {
	return _xPosition;
}

double Player::GetYPosition() {
	return _yPosition;
}

void Player::Rotate(int direction) {

	double rotationMatrix[2][2];
	

	double cosValue = COS(direction);
	double sinValue = SIN(direction);

	rotationMatrix[0][0] = cosValue;
	rotationMatrix[1][0] = sinValue;

	rotationMatrix[0][1] = -sinValue;
	rotationMatrix[1][1] = cosValue;

	// Want to do _currentrotation value * column in rotationMatrix

	/*double multiplication[2][2];
	
	multiplication[0][0] = rotationMatrix[0][0] * _currentRotation[0][0] + rotationMatrix[0][1] * _currentRotation[1][0];
	multiplication[1][0] = rotationMatrix[1][0] * _currentRotation[0][0] + rotationMatrix[1][1] * _currentRotation[1][0];

	multiplication[0][1] = rotationMatrix[0][0] * _currentRotation[0][1] + rotationMatrix[0][1] * _currentRotation[1][1];
	multiplication[1][1] = rotationMatrix[1][0] * _currentRotation[0][1] + rotationMatrix[1][1] * _currentRotation[1][1];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_currentRotation[i][j] = multiplication[i][j];
		}

	}*/

	double pro[2][2];

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			pro[i][j] = 0;

			for (int k = 0; k < 2; k++)
				pro[i][j] = pro[i][j] + (_currentRotation[i][k] * rotationMatrix[k][j]);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			_currentRotation[i][j] = pro[i][j];
		}
	}



	for (int i = 0; i < 3; i++)
	{
		double x_shifted = _drawPoints[0][i];
		double y_shifted = _drawPoints[1][i];

		_drawPoints[0][i] = rotationMatrix[0][0] * x_shifted + rotationMatrix[1][0] * y_shifted;
		_drawPoints[1][i] = rotationMatrix[0][1] * x_shifted + rotationMatrix[1][1] * y_shifted;
	}

}

void Player::Move() {
	double x = _movementVector[0];
	double y = _movementVector[1];

	_xPosition += _currentRotation[0][0] * x + _currentRotation[1][0] * y;
	_yPosition += _currentRotation[0][1] * x + _currentRotation[1][1] * y;
}