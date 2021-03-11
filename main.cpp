
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
	double pointx[1000] = { 0 };
	double pointy[1000] = { 0 };
	double pointz[1000] = { 0 };
	double pointz2[1000] = { 0 };
	default_random_engine e(time(0));
	uniform_real_distribution<double> u(1, 10);
	default_random_engine q(time(0));
	uniform_real_distribution<double> w(20,80);

	default_random_engine r(time(0));
	uniform_real_distribution<double> t(1, 80);
	std::vector<piont_cloud> p1;
	std::vector<piont_cloud> p2;
	for (int i = 0; i < 500; i++)
	{
		
		pointz[i] = u(e)/10.0;

	}
	for (int i = 0; i < 1000; i++)
	{
	
		pointz2[i] = u(e)/10.0;
	}

	for (int i = 500; i < 1000; i++)
	{

		pointz[i] = t(r)/10.0;
	}
	for (int i = 0; i < 1000; i++)
	{

		pointx[i] = t(r);
	}
	for (int i = 0; i < 1000; i++)
	{

		pointy[i] = t(r);
	}
	for (int i = 0; i < 1000; i++)
	{
		piont_cloud pc1;
		pc1.set_point(pointx[i], pointy[i], pointz[i]);
		p1.push_back(pc1);
	}
	for (int i = 0; i < 1000; i++)
	{
		piont_cloud pc2;
		pc2.set_point(pointx[i], pointy[i], pointz2[i]);
		p2.push_back(pc2);
	}
	gmm test;
	test.gm;
	test.input_point(p1);
	for (int i = 0; i < 2; i++) {
		test.gm->alpha(i) = 0.5;
		test.gm->sigma(i) = 1;
		test.gm->u(i) = pointz[i];
	}

	test.em_step(0.2, 0.2, 6);
	for (int i = 0; i < 2; i++) {
		cout <<"栅格A均值为："<< test.gm->u(i) << endl;
		cout << "栅格A方差为：" << test.gm->sigma(i) << endl;
		cout << "栅格A-NK为：" << test.gm->Nk(i) << endl;
	}

	gmm test2;
	test2.gm;
	test2.input_point(p2);
	for (int i = 0; i < 2; i++) {
		test2.gm->alpha(i) = 0.5;
		test2.gm->sigma(i) = 1;
		test2.gm->u(i) = pointz2[i];
		
	}

	test2.em_step(0.2, 0.2, 5);
	for (int i = 0; i < 2; i++) {
		cout << "栅格B均值为：" << test2.gm->u(i) << endl;
		cout << "栅格B方差为：" << test2.gm->sigma(i) << endl;
		cout << "栅格B-NK为：" << test2.gm->Nk(i) << endl;
	}
	return EXIT_SUCCESS;
}
