#include "gmm.h"
#include "point_cloud.h"
#include <cmath>
#include <Eigen/Dense>
double gmm::singlegussian(double u, double sigma,double z)
{
	double fai,tmp;
	tmp = exp(-pow((z - u),2)/(2*pow(sigma,2)));
	fai = tmp / (sqrt(2 * pi) * sigma);
	return fai;
}
//º∆À„r£®jk£©
double gmm::e_step(double u_old, double sigma_old,int N)
{
	Matrix2d rjk;
	double rjksum;
	for (int j = 0; j < 2; j++)
	{
		for (int k = 0; k < 2; k++)
		{
			rjk(j, k) = gm->alpha(k) * singlegussian(gm->u(k), gm->sigma(k), p.get_point()(2));
			rjksum += rjk(j,k);
		}
	}
}