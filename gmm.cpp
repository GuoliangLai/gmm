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
//计算r（jk）
void gmm::em_step(double u_old, double sigma_old,int N)
{
	Eigen::MatrixXd rjk;
	rjk = Eigen::Matrix<double, Dynamic, Dynamic>();
	rjk.resize(p.size(), 2); //resize 2 * 200
	while (--N>=0)
	{


		for (int j = 0; j < p.size(); j++)
		{
			double rjksum;
			rjksum = 0;
			for (int k = 0; k < 2; k++)
			{
				//p[j].get_point()(2)第j个点的纵坐标
				rjk(j, k) = gm->alpha(k) * singlegussian(gm->u(k), gm->sigma(k), p[j].get_point()(2));
				//Σrjk
				rjksum += rjk(j, k);
				//cout <<"第"<<j<< "rjk为" << rjk(j, k) << endl;
			}
			for (int k = 0; k < 2; k++)
			{
				rjk(j, k) = rjk(j, k) / rjksum;
				//cout << "rjksum为" << rjksum << endl;
				
			}

		}
		//计算sigma
		for (int k = 0; k < 2; k++)
		{
			double rjkyj_uk2, rjksums;
			rjkyj_uk2 = 0;
			rjksums = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjkyj_uk2 = rjk(j, k) * (pow((p[j].get_point()(2) - gm->u(k)), 2));
				rjkyj_uk2 += rjkyj_uk2;
				rjksums += rjk(j, k);
			}
			gm->sigma(k) = rjkyj_uk2 / rjksums;
			//cout <<k<< "sigma为" << gm->sigma(k) << endl;
		}

		//计算u
		for (int k = 0; k < 2; k++)
		{
			double rjkyj, rjksumu;
			rjkyj = 0;
			rjksumu = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjkyj = rjk(j, k) * p[j].get_point()(2);
				rjkyj += rjkyj;
				rjksumu += rjk(j, k);
			}
			gm->u(k) = rjkyj / rjksumu;
			//cout << k << "u为" << gm->u(k) << endl;
		}
		//计算alpha

		for (int k = 0; k < 2; k++)
		{
			double  rjksuma;
			rjksuma = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjksuma += rjk(j, k);
			}
			gm->alpha(k) = rjksuma / p.size();
			//cout << k << "alpha为" << gm->alpha(k) << endl;
		}
		//计算nk

		for (int k = 0; k < 2; k++)
		{
			double  rjksumn;
			rjksumn = 0;
			gm->Nk(k) = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjksumn += rjk(j, k);
			}
			gm->Nk(k) = rjksumn ;
			//cout << k << "Nk为" << gm->Nk(k) << endl;
		}

	}
	

	
}
void gmm::input_point(std::vector<piont_cloud> m_p)
{
	p = m_p;
	/*for (int i = 0; i < p.size(); i++)
	{
		cout << p[i].get_point()(2) << endl;
	}*/

}
gmm::gmm()
{
	cout << "初始化成功！" << endl;
	gm->Nk <<1,1;
	gm->u << 1, 1;
	gm->sigma <<2, 10;
	gm->alpha <<0.5, 0.5;
}

gmm::~gmm()
{
	cout << "析构完成！" << endl;
}