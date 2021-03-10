
#include <iostream>
#include <Eigen\Dense>
#include <vector>
#include "point_cloud.h"
#include "gmm.h"
#include<ctime>
#include<random>
using namespace std;

int main()
{
	double pointx[80] = { 0 };
	double pointy[80] = { 0 };
	double pointz[80] = { 0 };
	double pointz2[80] = { 0 };
	default_random_engine e(time(0));
	uniform_real_distribution<double> u(1, 5);
	default_random_engine q(time(0));
	uniform_real_distribution<double> w(60,68);

	default_random_engine r(time(0));
	uniform_real_distribution<double> t(0, 1500);
	std::vector<piont_cloud> p1;
	std::vector<piont_cloud> p2;
	for (int i = 0; i < 40; i++)
	{
		
		pointz[i] = u(e);
	}
	for (int i = 0; i < 80; i++)
	{

		pointz2[i] = u(e);
	}
	for (int i = 40; i < 80; i++)
	{

		pointz[i] = w(q);
	}

	for (int i = 0; i < 80; i++)
	{

		pointx[i] = t(r);
	}
	for (int i = 0; i < 80; i++)
	{

		pointy[i] = t(r);
	}
	for (int i = 0; i < 80; i++)
	{
		piont_cloud pc1;
		pc1.set_point(pointx[i], pointy[i], pointz[i]);
		p1.push_back(pc1);
	}
	for (int i = 0; i < 80; i++)
	{
		piont_cloud pc2;
		pc2.set_point(pointx[i], pointy[i], pointz2[i]);
		p2.push_back(pc2);
	}
	gmm test;
	test.gm;
	test.input_point(p1);
	test.em_step(0.2, 0.2, 1);
	for (int i = 0; i < 2; i++) {
		cout <<"栅格A均值为："<< test.gm->u(i) << endl;
		cout << "栅格A方差为：" << test.gm->sigma(i) << endl;
		cout << "栅格A-NK为：" << test.gm->Nk(i) << endl;
	}

	gmm test2;
	test2.gm;
	test2.input_point(p2);
	test2.em_step(0.2, 0.2, 1);
	for (int i = 0; i < 2; i++) {
		cout << "栅格B均值为：" << test2.gm->u(i) << endl;
		cout << "栅格B方差为：" << test2.gm->sigma(i) << endl;
		cout << "栅格B-NK为：" << test2.gm->Nk(i) << endl;
	}
	return EXIT_SUCCESS;
}