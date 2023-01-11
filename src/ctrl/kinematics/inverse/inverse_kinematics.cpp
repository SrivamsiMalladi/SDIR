
#define _USE_MATH_DEFINES
#include<cmath>
#include<vector>

#include <iostream>
using namespace std;

#include "inverse_kinematics.h"
#include <math.h>
vector<Configuration*>* InvKinematics::get_inv_kinematics(SixDPos* _pos)
{
    //TODO: IMPLEMENT Compute the inverse kinematics for a given position

    vector<Configuration*>* resultVector = Inverse_kinematics_function(_pos->get_X(), _pos->get_Y(), _pos->get_Z(), _pos->get_A(), _pos->get_B(), _pos->get_C(), 0, 0);

    //prepare the result vector for the configurations
    // you should call your inverse kinematics functions here!
    vector<Configuration*>* solutions = new vector<Configuration*>();
    //solutions->push_back(new Configuration({0,0,1,0,0,0}));
    //solutions->push_back(new Configuration({1/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({2/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({3/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({4/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({5/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({6/8 * M_PI,0,1,0,0,0}));
    //solutions->push_back(new Configuration({7/8 * M_PI,0,1,0,0,0}));

    for (auto i = resultVector->begin(); i != resultVector->end(); ++i) {
        solutions->push_back(*i);
    }

    return solutions;
}

//#include <inverse_kinematics.h>

const double PI = 3.14159265359;

//output
double t1, t2, t3, t4, t5, t6;

double aRotationMatrix[3][3],
bRotationMatrix[3][3],
cRotationMatrix[3][3],
transformationMatrix[4][4],
anglesMatrix[3];

double  wx, wy, wz;

// ±185°, -140° / -5°, -120° / 168°, ±350°, ±125°, ±350°

double tLimits[6][2] = {
	{-185.0, 185.0 },
	{-140.0, -5.0},
	{-120.0, 168.0},
	{-350.0, 350.0},
	{-125.0,125.0},
	{-350.0,350.0}
};

double l = 330.0;
double m = 645.0;
double a = 1150.0;
double p = 115.0;
double q = 1220.0;

double wristLength = 215.0;

double b = sqrt(pow(p, 2) + pow(q, 2));

double armJointAngles[6][3];
bool armJointAnglesValidity[6] = { true, true, true, true, true, true };
double allJointAngles[48][6];
bool allJointAnglesValidity[48] = { true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
									true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true,
									true, true, true, true, true, true, true, true, true, true, true, true, true, true, true, true };


//void generateRotationMatrixA(double aAngle) {
//	aRotationMatrix[0][0] = 1;
//	aRotationMatrix[0][1] = 0;
//	aRotationMatrix[0][2] = 0;
//	aRotationMatrix[1][0] = 0;
//	aRotationMatrix[1][1] = cos(aAngle);
//	aRotationMatrix[1][2] = -sin(aAngle);
//	aRotationMatrix[2][0] = 0;
//	aRotationMatrix[2][1] = sin(aAngle);
//	aRotationMatrix[2][2] = cos(aAngle);
//}
//void generateRotationMatrixB(double bAngle) {
//	bRotationMatrix[0][0] = cos(bAngle);
//	bRotationMatrix[0][1] = 0;
//	bRotationMatrix[0][2] = sin(bAngle);
//	bRotationMatrix[1][0] = 0;
//	bRotationMatrix[1][1] = 1;
//	bRotationMatrix[1][2] = 0;
//	bRotationMatrix[2][0] = -sin(bAngle);
//	bRotationMatrix[2][1] = 0;
//	bRotationMatrix[2][2] = cos(bAngle);
//}
//void generateRotationMatrixC(double cAngle) {
//	cRotationMatrix[0][0] = cos(cAngle);
//	cRotationMatrix[0][1] = -sin(cAngle);
//	cRotationMatrix[0][2] = 0;
//	cRotationMatrix[1][0] = sin(cAngle);
//	cRotationMatrix[1][1] = cos(cAngle);
//	cRotationMatrix[1][2] = 0;
//	cRotationMatrix[2][0] = 0;
//	cRotationMatrix[2][1] = 0;
//	cRotationMatrix[2][2] = 1;
//}	

void generateTransformationMatrix(double x, double y, double z, double alpha, double beta, double gamma) {
	double transformationMatrix[4][4] = {
		{(cos(beta) * cos(gamma)),	(sin(alpha) * sin(beta) * cos(gamma)) - (cos(alpha) * sin(gamma)),		(cos(alpha) * sin(beta) * cos(gamma)) + (sin(alpha) * sin(gamma)),		x},
		{(cos(beta) * sin(gamma)),	((sin(alpha) * sin(beta) * sin(gamma)) + (cos(alpha) * cos(gamma))),	((cos(alpha) * sin(beta) * sin(gamma)) - (sin(alpha) * cos(gamma))),	y},
		{-sin(beta),				sin(alpha) * cos(beta),													cos(alpha) * cos(beta),													z},
		{0,							0,																		0,																		1}
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			::transformationMatrix[i][j] = transformationMatrix[i][j];
		}
	}
}

void degradeTransformationMatrix() {
	double alpha = atan2(transformationMatrix[2][1], transformationMatrix[2][2]);
	double beta = -asin(transformationMatrix[2][0]);
	double gamma = atan2(transformationMatrix[1][0], transformationMatrix[0][0]);

	double anglesMatrix[3] = { alpha, beta, gamma };

	for (int i = 0; i < 3; i++) {
		::anglesMatrix[i] = anglesMatrix[i];
	}
}

vector<Configuration*>* InvKinematics::Inverse_kinematics_function(double x, double y, double z, double al, double be, double gm, double pt1, double pt4)
{

	//cout << "PI " << PI << "\n";
	//cout << "Enter x, y and z co-ordinates of the target point seperated by space: ";
	//cin >> x >> y >> z;
	//cout << "Enter the required orientation with respect to x, y and z axes respectively sepereated by space in degrees: ";
	//cin >> alpha >> beta >> gamma;

	//alpha = alpha * (180 / PI);
	//beta = beta * (180 / PI);
	//gamma = gamma * (180 / PI);

	cout << "Entered Coordinate points are\n";
	cout << x << " " << y << " " << z << "\n";

	cout << "Entered Euler angles are\n";
	cout << al << " " << be << " " << gm << "\n";

	//Generating Homogenious Matrix
	generateTransformationMatrix(x, y, z, al, be, gm);

	//double transformationMatrix[4][4] = {
	//	{-0.507791870, 0.635025673, -0.582142433, -718.376830},
	//	{0.262242221, 0.757620537, 0.597695691, 1897.42719},
	//	{0.820595171, 0.150842688, -0.551244092, 232.490439},
	//	{0.00000000, 0.00000000, 0.00000000, 1.00000000}
	//};

	//long double transformationMatrix[4][4] = {
	//	{ 0.258343520, - 0.928688786,   0.266074735,   314.099985},
	//	{0.939694139,   0.305474825,   0.153818259,   31.3148732 },
	//	{-0.224128425,   0.210290919,   0.951600850,   2934.78492},
	//	{0,   0,   0,   1}
	//};
	//double transformationMatrix[4][4] = {
	//	{ -0.0442438962,	0.957043695,	0.286548154,   92.4075420},
	//	{-0.974010246,		0.0224551327,	-0.225388126, -668.540585 },
	//	{-0.222140762,		-0.289072887,   0.931176862,   2741.34524},
	//	{0,   0,   0,   1}
	//};
	cout << "Transformation matrix: \n";

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			::transformationMatrix[i][j] = transformationMatrix[i][j];
			cout << transformationMatrix[i][j] << " ";
		}
		cout << "\n";
	}

	//cout << "Euler Angles are:\n";
	//for (int i = 0; i < 3; i++) {
	//	cout << ::anglesMatrix[i] << " ";
	//}
	//cout << "\n";

	//degradeTransformationMatrix();

	//cout << "Euler Angles are:\n";
	//for (int i = 0; i < 3; i++) {
	//	cout << ::anglesMatrix[i] << " ";
	//}
	//cout << "\n";

	//cout << "Before generating transformation matrix: \n";
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		::transformationMatrix[i][j] = 0;
	//		cout << ::transformationMatrix[i][j] << " ";
	//	}
	//	cout << "\n";
	//}
	//
	//generateTransformationMatrix(transformationMatrix[0][3], transformationMatrix[1][3], transformationMatrix[2][3], ::anglesMatrix[0], ::anglesMatrix[1], ::anglesMatrix[2]);

	//cout << "Generated Transformation is: \n";
	//
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		cout << ::transformationMatrix[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	//double transformationMatrix[4][4] = {
	//	{0.258343520, -0.928688786,   0.266074735,   314.099985},
	//{0.939694139,   0.305474825,   0.153818259,   31.3148732 },
	//{-0.224128425,   0.210290919,   0.951600850,  2934.78492},
	//{0,   0,   0,   1 }
	//};

	//double transformationMatrix[4][4] = {
	//	{ -0.0442438962,   0.957043695,   0.286548154,   92.4075420},
	//{-0.974010246,   0.0224551327, -0.225388126, -668.540585 },
	//{-0.222140762, - 0.289072887,   0.931176862,   2741.34524},
	//{0,   0,   0,   1} 
	//};

	//cout << "Transformation Matrix:\n";
	//for (int i = 0; i < 4; i++) {
	//	for (int j = 0; j < 4; j++) {
	//		cout << transformationMatrix[i][j];
	//		cout << " ";
	//	}
	//	cout << "\n";
	//}
	//cout << "\n";

	//Finding Tool Center Point
	wx = transformationMatrix[0][3] - (wristLength * transformationMatrix[0][2]);
	wy = transformationMatrix[1][3] - (wristLength * transformationMatrix[1][2]);
	wz = transformationMatrix[2][3] - (wristLength * transformationMatrix[2][2]);

	//wx = 389.099763753;
	//wy = 32.9008637566;
	//wz = 2878.61642142;

	//cout << "Wrist co-ordinates are " << "\n" << wx << " " << wy << " " << wz << "\n";

	//Front half plane
	//First joint angle

	//Overhead Singularity

	if (wx == 0 && wy == 0) {
		cout << "Wrist singularity occured\n";
		t1 = pt1;
	}
	else {
		t1 = -atan2(wy, wx) * (double)(180 / PI);
		if (t1 >= tLimits[0][0] && t1 <= tLimits[0][1]) {
			armJointAnglesValidity[0] = true;
			armJointAngles[0][0] = t1;

			armJointAnglesValidity[1] = true;
			armJointAngles[1][0] = t1;
		}
		else {
			armJointAnglesValidity[0] = false;
			armJointAnglesValidity[1] = false;
		}
	}

	//Second joint angle
	double wx2 = sqrt(pow(wx, 2) + pow(wy, 2));
	double wz2 = wz;

	double c = sqrt(pow((wx2 - l), 2) + pow((wz2 - m), 2));

	double i1 = acos((pow(a, 2) + pow(c, 2) - pow(b, 2)) / (2 * a * c));
	double i2 = atan2((wz2 - m), (wx2 - l));

	//Elbow up
	t2 = -((i2 + i1) * (180 / PI));
	if ((t2 >= tLimits[1][0]) && (t2 <= tLimits[1][1]) && (armJointAnglesValidity[0] == true)) {
		armJointAngles[0][1] = t2;
	}
	else {
		armJointAnglesValidity[0] = false;
	}
	//Elbow down
	t2 = -((i2 - i1) * (180 / PI));
	if ((t2 >= tLimits[1][0]) && (t2 <= tLimits[1][1]) && (armJointAnglesValidity[1] == true)) {
		armJointAngles[1][1] = t2;
	}
	else {
		armJointAnglesValidity[1] = false;
	}

	//Third joint angle
	double i3 = acos((pow(a, 2) + pow(b, 2) - pow(c, 2)) / (2 * a * b));
	double i4 = atan2(p, q);

	//Elbow down
	t3 = 180 - ((i3 - i4) * (180 / PI));
	if ((t3 >= tLimits[2][0]) && (t3 <= tLimits[2][1]) && (armJointAnglesValidity[0] == true)) {
		armJointAngles[0][2] = t3;
	}
	else {
		armJointAnglesValidity[2] = false;
	}

	//Elbow up
	t3 = -(180 - ((i3 + i4) * (180 / PI)));
	if ((t3 >= tLimits[2][0]) && (t3 <= tLimits[2][1]) && (armJointAnglesValidity[1] == true)) {
		armJointAngles[1][2] = t3;
	}
	else {
		armJointAnglesValidity[2] = false;
	}

	//Back half plane
	//First joint angle
	t1 = -(180 - t1);
	if ((t1 >= tLimits[0][0]) && (t1 <= tLimits[0][1])) {
		if (armJointAnglesValidity[2] == true) {
			armJointAngles[2][0] = t1;
		}

		if (armJointAnglesValidity[3] == true) {
			armJointAngles[3][0] = t1;
		}
	}
	else {
		armJointAnglesValidity[2] = true;
		armJointAnglesValidity[3] = true;
	}

	t1 = (360 + t1);
	if (t1 >= tLimits[0][0] && t1 <= tLimits[0][1]) {
		if (armJointAnglesValidity[4] == true) {
			armJointAngles[4][0] = t1;
		}
		if (armJointAnglesValidity[5] == true) {
			armJointAngles[5][0] = t1;
		}
	}
	else {
		armJointAnglesValidity[4] = true;
		armJointAnglesValidity[5] = true;
	}

	//Second joint angle
	double cb = sqrt(pow((wx2 + l), 2) + pow((wz2 - m), 2));

	double i1b = acos((pow(a, 2) + pow(cb, 2) - pow(b, 2)) / (2 * a * cb));
	double i2b = atan2((wz2 - m), (wx2 + l));

	//Elbow up
	t2 = -(180 - ((i2b + i1b) * (180 / PI)));
	if (t2 >= tLimits[1][0] && t2 <= tLimits[1][1]) {
		if (armJointAnglesValidity[2] == true) {
			armJointAngles[2][1] = t2;
		}
		if (armJointAnglesValidity[4] == true) {
			armJointAngles[4][1] = t2;
		}
	}
	else {
		armJointAnglesValidity[2] = false;
		armJointAnglesValidity[4] = false;
	}
	//Elbow down
	t2 = -(180 - ((i2b - i1b) * (180 / PI)));
	if (t2 >= tLimits[1][0] && t2 <= tLimits[1][1]) {
		if (armJointAnglesValidity[3] == true) {
			armJointAngles[3][1] = t2;
		}
		if (armJointAnglesValidity[5] == true) {
			armJointAngles[5][1] = t2;
		}
	}
	else {
		armJointAnglesValidity[3] = false;
		armJointAnglesValidity[5] = false;
	}

	//Third joint angle
	double i3b = acos((pow(a, 2) + pow(b, 2) - pow(cb, 2)) / (2 * a * b));
	double i4b = atan2(p, q);

	//Elbow up
	t3 = -(180 - ((i3b + i4b) * (180 / PI)));
	if (t3 >= tLimits[2][0] && t3 <= tLimits[2][1]) {
		if (armJointAnglesValidity[2] == true) {
			armJointAngles[2][2] = t3;
		}
		if (armJointAnglesValidity[4] == true) {
			armJointAngles[4][2] = t3;
		}
	}
	else {
		armJointAnglesValidity[2] = false;
		armJointAnglesValidity[4] = false;
	}

	//Elbow down
	t3 = 180 - ((i3b - i4b) * (180 / PI));
	if (t3 >= tLimits[2][0] && t3 <= tLimits[2][1]) {
		if (armJointAnglesValidity[3] == true) {
			armJointAngles[3][2] = t3;
		}
		if (armJointAnglesValidity[5] == true) {
			armJointAngles[5][2] = t3;
		}
	}
	else {
		armJointAnglesValidity[3] = false;
		armJointAnglesValidity[5] = false;
	}

	//cout << "First three joint angles are \n";
	//for (int i = 0; i < 6; i++) {
	//	for (int j = 0; j < 3; j++) {
	//		cout << armJointAngles[i][j] << " ";
	//	}
	//	cout << "\n";
	//}

	//Wrist angles

	for (int i = 0; i < 6; i++) {
		if (armJointAnglesValidity[i]) {
			for (int j = 0; j < 8; j++) {
				allJointAngles[(i * 8) + j][0] = armJointAngles[(int)(i)][0];
				allJointAngles[(i * 8) + j][1] = armJointAngles[(int)(i)][1];
				allJointAngles[(i * 8) + j][2] = armJointAngles[(int)(i)][2];

				allJointAnglesValidity[i + j] = allJointAnglesValidity[i];
			}

			t1 = armJointAngles[i][0] * (PI / 180);
			t2 = armJointAngles[i][1] * (PI / 180);
			t3 = armJointAngles[i][2] * (PI / 180);



			double baseToWristMatrix[3][3] = {
				{cos(t1) * sin(t2 + t3),    sin(t1),        -cos(t1) * cos(t2 + t3)},
				{-sin(t1) * sin(t2 + t3),   cos(t1),        sin(t1) * cos(t2 + t3)},
				{cos(t2 + t3),              0,              sin(t2 + t3)}
			};

			//cout << "----baseToWristMatrix for" << t1 * (180 / PI) << " " << t2 * (180 / PI) << " " << t3 * (180 / PI)  << "----\n";
			//for (int j = 0; j < 3; j++) {
			//	for (int k = 0; k < 3; k++) {
			//		cout << baseToWristMatrix[j][k] << " ";
			//	}
			//	cout << "\n";
			//}

			double baseToWristMatrixTranspose[3][3];
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					baseToWristMatrixTranspose[i][j] = baseToWristMatrix[j][i];
				}
			}

			double wristToToolMatrix[3][3] = {
				{0, 0, 0},
				{0, 0, 0},
				{0, 0, 0}
			};

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					for (int k = 0; k < 3; k++) {
						wristToToolMatrix[i][j] += baseToWristMatrixTranspose[i][k] * transformationMatrix[k][j];
					}
				}
			}

			//cout << "----wristToToolMatrix----\n";
			//for (int j = 0; j < 3; j++) {
			//	for (int k = 0; k < 3; k++) {
			//		cout << wristToToolMatrix[j][k] << " ";
			//	}
			//	cout << "\n";
			//}

			t5 = atan2(sqrt(1 - pow(-wristToToolMatrix[2][2], 2)), -wristToToolMatrix[2][2]);
			if (t5 >= tLimits[4][0] && t5 <= tLimits[4][1]) {
				for (int j = 0; j < 4; j++) {
					allJointAngles[(i * 8) + j][4] = t5 * (180 / PI);
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					allJointAnglesValidity[(i * 8) + j] = false;
				}
			}

			if (t5 == 0) {
				cout << "Wrist singularity occured";
				t4 = pt4;
				t6 = atan2(-wristToToolMatrix[0][1], -wristToToolMatrix[0][0]) - t4;
			}
			else {
				t4 = atan2(-wristToToolMatrix[1][2] / sin(t5), -wristToToolMatrix[0][2] / sin(t5));
				t6 = atan2(wristToToolMatrix[2][1] / sin(t5), wristToToolMatrix[2][0] / sin(t5));

			}

			if (t4 * (180 / PI) >= tLimits[3][0] && t4 * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8)] && allJointAnglesValidity[(i * 8) + 1]) {
				allJointAngles[(i * 8)][3] = t4 * (180 / PI);
				allJointAngles[(i * 8) + 1][3] = t4 * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8)] = false;
				allJointAnglesValidity[(i * 8) + 1] = false;
			}

			if ((t4 + (2 * PI)) * (180 / PI) >= tLimits[3][0] && (t4 + (2 * PI)) * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8) + 2] && allJointAnglesValidity[(i * 8) + 3]) {
				allJointAngles[(i * 8) + 2][3] = (t4 + (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 3][3] = (t4 + (2 * PI)) * (180 / PI);
			}
			else if ((t4 - (2 * PI)) * (180 / PI) >= tLimits[3][0] && (t4 - (2 * PI)) * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8) + 2] && allJointAnglesValidity[(i * 8) + 3]) {
				allJointAngles[(i * 8) + 2][3] = (t4 - (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 3][3] = (t4 - (2 * PI)) * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 2] = false;
				allJointAnglesValidity[(i * 8) + 3] = false;
			}

			if (t6 * (180 / PI) >= tLimits[5][0] && t6 * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8)] && allJointAnglesValidity[(i * 8) + 2]) {
				allJointAngles[(i * 8)][5] = t6 * (180 / PI);
				allJointAngles[(i * 8) + 2][5] = t6 * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8)] = false;
				allJointAnglesValidity[(i * 8) + 2] = false;
			}

			if ((t6 + (2 * PI)) * (180 / PI) >= tLimits[5][0] && (t6 + (2 * PI)) * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8) + 1] && allJointAnglesValidity[(i * 8) + 3]) {
				allJointAngles[(i * 8) + 1][5] = (t6 + (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 3][5] = (t6 + (2 * PI)) * (180 / PI);
			}
			else if ((t6 - (2 * PI)) * (180 / PI) >= tLimits[5][0] && (t6 - (2 * PI)) * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8) + 1] && allJointAnglesValidity[(i * 8) + 3]) {
				allJointAngles[(i * 8) + 1][5] = (t6 - (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 3][5] = (t6 - (2 * PI)) * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 1] = false;
				allJointAnglesValidity[(i * 8) + 3] = false;
			}

			if (t5 != 0) {
				t5 = -t5;
				t4 = atan2(-wristToToolMatrix[1][2] / sin(t5), -wristToToolMatrix[0][2] / sin(t5));
				t6 = atan2(wristToToolMatrix[2][1] / sin(t5), wristToToolMatrix[2][0] / sin(t5));
			}
			else {
				t4 = t4 + PI;
				t6 = t6 + PI;
			}
			if (t5 * (180 / PI) >= tLimits[4][0] && t5 <= tLimits[4][1]) {
				for (int j = 4; j < 8; j++) {
					allJointAngles[(i * 8) + j][4] = t5 * (180 / PI);
				}
			}
			else {
				for (int j = 4; j < 8; j++) {
					allJointAnglesValidity[(i * 8) + j] = false;
				}
			}


			if (t4 * (180 / PI) >= tLimits[3][0] && t4 * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8) + 4] && allJointAnglesValidity[(i * 8) + 5]) {
				allJointAngles[(i * 8) + 4][3] = t4 * (180 / PI);
				allJointAngles[(i * 8) + 5][3] = t4 * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 4] = false;
				allJointAnglesValidity[(i * 8) + 5] = false;
			}

			if ((t4 + (2 * PI)) * (180 / PI) >= tLimits[3][0] && (t4 + (2 * PI)) * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8) + 6] && allJointAnglesValidity[(i * 8) + 7]) {
				allJointAngles[(i * 8) + 6][3] = (t4 + (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 7][3] = (t4 + (2 * PI)) * (180 / PI);
			}
			else if ((t4 - (2 * PI)) * (180 / PI) >= tLimits[3][0] && (t4 - (2 * PI)) * (180 / PI) <= tLimits[3][1] && allJointAnglesValidity[(i * 8) + 6] && allJointAnglesValidity[(i * 8) + 7]) {
				allJointAngles[(i * 8) + 6][3] = (t4 - (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 7][3] = (t4 - (2 * PI)) * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 6] = false;
				allJointAnglesValidity[(i * 8) + 7] = false;
			}


			if (t6 * (180 / PI) >= tLimits[5][0] && t6 * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8) + 4] && allJointAnglesValidity[(i * 8) + 6]) {
				allJointAngles[(i * 8) + 4][5] = t6 * (180 / PI);
				allJointAngles[(i * 8) + 6][5] = t6 * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 4] = false;
				allJointAnglesValidity[(i * 8) + 6] = false;
			}

			if ((t6 + (2 * PI)) * (180 / PI) >= tLimits[5][0] && (t6 + (2 * PI)) * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8) + 5] && allJointAnglesValidity[(i * 8) + 7]) {
				allJointAngles[(i * 8) + 5][5] = (t6 + (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 7][5] = (t6 + (2 * PI)) * (180 / PI);
			}
			else if ((t6 - (2 * PI)) * (180 / PI) >= tLimits[5][0] && (t6 - (2 * PI)) * (180 / PI) <= tLimits[5][1] && allJointAnglesValidity[(i * 8) + 5] && allJointAnglesValidity[(i * 8) + 7]) {
				allJointAngles[(i * 8) + 5][5] = (t6 - (2 * PI)) * (180 / PI);
				allJointAngles[(i * 8) + 7][5] = (t6 - (2 * PI)) * (180 / PI);
			}
			else {
				allJointAnglesValidity[(i * 8) + 5] = false;
				allJointAnglesValidity[(i * 8) + 7] = false;
			}
		}
		else {
			allJointAnglesValidity[i] = false;
		}
	}

	cout << "------ALL ANGLES------\n";
	for (int i = 0; i < 48; i++) {
		for (int j = 0; j < 6; j++) {
			cout << allJointAngles[i][j] << " ";
		}
		cout << "\n";
	}

	vector<Configuration*>* IKResult = new vector<Configuration*>();;
	for (int i = 0; i < 48; i++) {
		if (allJointAnglesValidity[i]) {
			IKResult->push_back(new Configuration({ allJointAngles[i][0], allJointAngles[i][1], allJointAngles[i][2], allJointAngles[i][3], allJointAngles[i][4], allJointAngles[i][5] }));
		}
	}
	return IKResult;
}