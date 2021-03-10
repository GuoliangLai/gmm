
#include <iostream>
#include <Eigen\Dense>

using namespace std;

typedef Eigen::Matrix<double, 3, 3> Matrix3d;

int main()
{
	Matrix3d m1;
	m1 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
	cout << "m1 = \n" << m1 << endl;

	Matrix3d m2;
	m2 << 1, 0, 0, 0, 1, 0, 0, 0, 1;
	cout << "m2 = \n" << m2(1,1) << endl;

	cout << "m1 * m2 = \n" << (m1 * m2) << endl;

	return 0;
}