#include <iostream>
#include <math.h>
#include <random>
using namespace std;

#define N 100
#define rnd_resol 1000
#define trials 100000
#define stride 0.1
#define range 15.0

struct normal
{
	double prob;
	double amp;
	double theory;
};

int main()
{
	int i,j;
	double k;
	double l;
	double theta_n_I=0.0;
	double theta_n_Q=0.0;
	int r_I=0.0;
	int r_Q=0.0;
	double tmp_I;
	double tmp_Q;
	double tmp_R;
	int addr=0;
	int size=0;
	double var_I=0.0;
	double var_Q=0.0;
	double theory_sum_I=0.0;
	double theory_sum_Q=0.0;
	double theory_sum_R=0.0;

	size = 2*range/stride;
	normal I[size];
	normal Q[size];
	normal R[size];

	//I[],Q[],R[]初期化
	for(i=0;i<size;i++)
	{
		I[i].prob=0.0;
		I[i].amp=0.0;
		I[i].theory=0.0;

		Q[i].prob=0.0;
		Q[i].amp=0.0;
		Q[i].theory=0.0;

		R[i].prob=0.0;
		R[i].amp=0.0;
		R[i].theory=0.0;
	}

	//乱数生成器の生成
	random_device rnd_I;
	random_device rnd_Q;

	//cos(θn),sin(θn)の計算
	for(j=0;j<trials;j++)
	{
		tmp_I = 0.0;
		tmp_Q = 0.0;
		tmp_R = 0.0;
		for(i=0;i<N;i++)
		{
			//0~rnd_resolの乱数を生成する
			r_I = rnd_I()%(rnd_resol+1);
			r_Q = rnd_Q()%(rnd_resol+1);
			//θnを生成[0,2π]
			theta_n_I = 2.0*M_PI*r_I/rnd_resol;
			theta_n_Q = 2.0*M_PI*r_Q/rnd_resol;

			tmp_I += cos(theta_n_I);
			tmp_Q += sin(theta_n_Q);
			//tmp_R += sqrt(pow(tmp_I, 2.0)+pow(tmp_Q, 2.0));
		}

		tmp_R = sqrt(pow(tmp_I, 2.0)+pow(tmp_Q, 2.0));

		//cout << tmp << endl;
		k = -(double)N;
		l = 0.0;
		addr = 0;
		while(k<range)
		{
			if((k <= tmp_I) && (tmp_I < k+stride))
			{
				I[addr].prob += 1.0/(double)trials;
			}

			if((k <= tmp_Q) && (tmp_Q < k+stride))
			{
				Q[addr].prob += 1.0/(double)trials;
			}

			if((l <= tmp_R) && (tmp_R < l+stride))
			{
				R[addr].prob += 1.0/(double)trials;
			}

			k += (double)stride;
			l += (double)stride;
			addr += 1;
		}
	}

	//分散の計算
	for(i=0;i<size;i++)
	{
		I[i].amp = -(double)N+i*stride;
		Q[i].amp = -(double)N+i*stride;
		R[i].amp = i*stride;

		var_I += pow(I[i].amp, 2.0)*I[i].prob;
		var_Q += pow(Q[i].amp, 2.0)*Q[i].prob;
		//cout << var << endl;
	}

	//正規分布・レイリー分布の理論値
	for(i=0;i<size;i++)
	{
		I[i].theory = exp(-pow(I[i].amp, 2.0)/2.0/var_I)/sqrt(2.0*M_PI*var_I);
		Q[i].theory = exp(-pow(Q[i].amp, 2.0)/2.0/var_Q)/sqrt(2.0*M_PI*var_Q);
		R[i].theory = exp(-pow(R[i].amp, 2.0)/2.0/var_I)*R[i].amp/var_I;
		theory_sum_I += I[i].theory;
		theory_sum_Q += Q[i].theory;
		theory_sum_R += R[i].theory;
	}
	//項目の出力
	cout << "Amplitude" << "," << "IProbability" << "," << "ITheory" << ",";
	cout << "Amplitude" << "," << "QProbability" << "," << "QTheory" << ",";
	cout << "Amplitude" << "," << "Rayleigh" << "," << "Rtheory" << endl;
	//結果の出力
	for(i=0;i<size;i++)
	{
		cout << I[i].amp << "," << I[i].prob << "," << I[i].theory/theory_sum_I;
		cout << "," << Q[i].amp << "," << Q[i].prob << "," << Q[i].theory/theory_sum_Q;
		cout << "," << R[i].amp << "," << R[i].prob << "," << R[i].theory/theory_sum_R << endl;
	}

	return 0;
}
