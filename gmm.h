#pragma once
#include "point_cloud.h"
#include <Eigen/Dense>
//using namespace std;
using namespace Eigen;
const double pi = 3.1415;
struct struct_GM
{
	double Nk;
	//均值和方差:
	Vector2d u;
	Vector2d sigma;
	Vector2d alpha;
};
class gmm
{
public:
	double singlegussian(double u, double sigma,double z);
	double e_step(double u_old, double sigma_old,int N);
	gmm();
	~gmm();

private:
	struct_GM* gm;
	piont_cloud p;
};

gmm::gmm()
{

}

gmm::~gmm()
{
}