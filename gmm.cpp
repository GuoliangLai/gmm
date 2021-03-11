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
//����r��jk��
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
			double* rjktmp;
			rjksum = 0;
			rjktmp = new double[2];
			for (int k = 0; k < 2; k++)
			{
				//p[j].get_point()(2)��j�����������
				rjktmp[k]= gm->alpha(k) * singlegussian(gm->u(k), gm->sigma(k), p[j].get_point()(2));
				//rjk(j, k) = gm->alpha(k) * singlegussian(gm->u(k), gm->sigma(k), p[j].get_point()(2));
				//��rjk
				rjksum += rjktmp[k];
				//cout <<"��"<<j<< "rjkΪ" << rjktmp[k] << endl;
			}
			for (int k = 0; k < 2; k++)
			{
				rjk(j, k) = rjktmp[k] / rjksum;
				//cout << "rjksumΪ" << rjksum << endl;
				
			}
			delete[]rjktmp;

		}
		//����sigma
		for (int k = 0; k < 2; k++)
		{
			double rjkyj_uk2, rjksums,rjkyj_uk2sum;
			rjkyj_uk2 = 0;
			rjksums = 0;
			rjkyj_uk2sum = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjkyj_uk2 = rjk(j, k) * (pow((p[j].get_point()(2) - gm->u(k)), 2));
				rjkyj_uk2sum += rjkyj_uk2;
				rjksums += rjk(j, k);
			}
			gm->sigma(k) =sqrt( rjkyj_uk2sum / rjksums);
			//cout <<k<< "sigmaΪ" << gm->sigma(k) << endl;
		}

		//����u
		for (int k = 0; k < 2; k++)
		{
			double rjkyj, rjksumu,rjkyjsum;
			rjkyj = 0;
			rjksumu = 0;
			rjkyjsum = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjkyj = rjk(j, k) * (p[j].get_point()(2));
				//cout << j << "rjkyjΪ" << rjkyj << endl;
				rjkyjsum += rjkyj;
				rjksumu += rjk(j, k);

			}
			//cout << k << "rjksumΪ" << rjksumu << endl;
			//cout << k << "rjkyjΪ" << rjkyjsum << endl;
			gm->u(k) = rjkyjsum / rjksumu;

		}
		//����alpha

		for (int k = 0; k < 2; k++)
		{
			double  rjksuma;
			rjksuma = 0;
			for (int j = 0; j < p.size(); j++)
			{
				rjksuma += rjk(j, k);
			}
			gm->alpha(k) = rjksuma / p.size();
			//cout << k << "alphaΪ" << gm->alpha(k) << endl;
		}
		//����nk

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
			//cout << k << "NkΪ" << gm->Nk(k) << endl;
		}
		//cout << "��" << N << "�ε�����ֵ1-" << gm->u(0)<< endl;
		//cout << "��" << N << "�ε�����ֵ2-" << gm->u(1) << endl;

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
	cout << "��ʼ���ɹ���" << endl;
	//gm->Nk <<1,1;
	//gm->u << 1, 1;
	//gm->sigma <<1, 1;
	//gm->alpha <<0.5, 0.5;
}

gmm::~gmm()
{
	if (gm != NULL)
	{
		delete[]gm;
		gm = NULL;
	}
	
	cout << "������ɣ�" << endl;
}