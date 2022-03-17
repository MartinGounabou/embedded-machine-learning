#include "coef_def.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <typeinfo>
#include <stdlib.h>
#include <math.h> 

using namespace std;

using vec = vector<string>;
using vec1= vector<double>;
using matrix = vector<vec>;
using matrix1 = vector<vec1>;

// cree une matrice de string d'un fichier csv
matrix readCSV( string filename )
{
   char separator = ',';
   matrix result;
   string row, item;

   ifstream in( filename );
   while( getline( in, row ) )
   {
      vec R;
      stringstream ss( row );
      while ( getline ( ss, item, separator ) ) R.push_back( item );
      result.push_back( R );
   }
   in.close();

   return result;
}

void deleteRow( matrix &M, int row )
{
   if ( row < M.size() ) M.erase( M.begin() + row );
}

void deleteCol( matrix &M, int col  )
{
   for ( vec &row : M )
   {
      if ( col < row.size() ) row.erase( row.begin() + col );
   }
}

//Transforme une matrice csv string en matrice de doubles
matrix1 readCSV_to_double(matrix &result)
{
   deleteRow(result,0);
   deleteCol(result,512);
   double n,m;
   n=result.size();
   m=result[0].size();
   vector<vector<double>> x(n,vector<double>(m,0));

   for (int i=0; i<n ; i++)
		{
			for (int j=0; j<m ; j++)
				{
					x[i][j]=atof(result[i][j].c_str());
				 }
				}
   return x;
}

// Prédiction d'un element
string svm_predict(vector<double> x)
{
	double predicted =-100000.0;
	double best_predict =-1000000000.0;
	unsigned int pred =0;
	string predict;
	double y;

	for (int i=0; i<10; i++)
	{
		predicted =0;
		for (int j=0;j<512;j++)
		{	
			predicted+=w[i][j]*((x[j]-mu[j])/sqrt(var[j]));
		} 
		predicted+=b[i];
		if (predicted>best_predict)
		{
			best_predict=predicted;
			pred=i;
		}
		if (pred==0)
			predict= "blues";
		if (pred==1)
			predict= "classical";
		if (pred==2)
			predict= "country";
		if (pred==3)
			predict= "disco";
		if (pred==4)
			predict= "hiphop";
		if (pred==5)
			predict= "jazz";
		if (pred==6)
			predict= "metal";
		if (pred==7)
			predict= "pop";
		if (pred==8)
			predict= "reggea";
		if (pred==9)
			predict= "rock";
	}
	return predict;
}


// Prédiction d'un element au format double
double svm_predict_d(vector<double> x)
{
	double predicted =-100000.0;
	double best_predict =-1000000000.0;
	unsigned int pred =0;
	string predict;
	double y;
	for (int i=0; i<10; i++)
	{
		predicted =0;
		for (int j=0;j<512;j++)
		{	
			predicted+=w[i][j]*((x[j]-mu[j])/sqrt(var[j]));
		} 
		predicted+=b[i];
		if (predicted>best_predict)
		{
			best_predict=predicted;
			pred=i;
		}
	}
	return pred;
}

//converti les labels en vecteur encodé de 0 à 10
vector<double> convert_to_vecd(vector<string> x)
{
	vector<double> x1;
	double predict =0;
	for (int i=0; i<x.size(); i++)
	{
		predict =0;
		if (x[i]=="blues")
			predict= 0;
		if (x[i]=="classical")
			predict= 1;
		if (x[i]=="country")
			predict= 2;
		if (x[i]=="disco")
			predict= 3;
		if (x[i]=="hiphop")
			predict= 4;
		if (x[i]=="jazz")
			predict= 5;
		if (x[i]=="metal")
			predict= 6;
		if (x[i]=="pop")
			predict= 7;
		if (x[i]=="reggae")
			predict= 8;
		if (x[i]=="rock")
			predict= 9;
		x1.push_back(predict);
	} 
	return x1;	
}

vector<vector<double>> confusion_matrix(vector<double>& targets,vector<double>& outputs)
{
    int n=targets.size();
    double a,b,c,d,e,f,g,h,i,j=0;


    vector<vector<double>> conf_matrix;
    vector<double> vec;

    for (int k=0; k<10; k++)
    {
    	  a=0;b=0;c=0;d=0;e=0;f=0;g=0;h=0;i=0;j=0;
        for (int l=0; l<n; l++)
        {
        if (outputs[l]==k and targets[l]==0)
            a+=1;
        if (outputs[l]==k and targets[l]==1)
            b+=1;
        if (outputs[l]==k and targets[l]==2)
            c+=1;
        if (outputs[l]==k and targets[l]==3)
            d+=1;
        if (outputs[l]==k and targets[l]==4)
            e+=1;
        if (outputs[l]==k and targets[l]==5)
            f+=1;
        if (outputs[l]==k and targets[l]==6)
            g+=1;
        if (outputs[l]==k and targets[l]==7)
            h+=1;
        if (outputs[l]==k and targets[l]==8)
            i+=1;
        if (outputs[l]==k and targets[l]==9)
            j+=1;
        }
        vec ={a,b,c,d,e,f,g,h,i,j};
        conf_matrix.push_back(vec);
    }


    return conf_matrix;
}

void print_conf_mat(vector<vector<double>>& Mat)
{
	 cout<< "  -----confusion_matrix-----"<<endl;
	 cout<<endl;
    for (int i = 0; i < Mat.size(); ++i) 
    {
        for (int j = 0; j < Mat.size(); ++j) {
            cout << Mat[i][j] << " ";
        }
        cout <<endl;
     }
}

void evaluate(vector<string>& targets,vector<string>& outputs)
{
	double c=0;
	for (int i=0; i<targets.size(); i++)
	{
		if (outputs[i]==targets[i])
			c+=1;
	}
		cout<< " "<<endl;
	cout<< "Accuracy : "<< (c/targets.size()) <<endl;
	cout<< " "<<endl;
}


int main()
{
	init();
	matrix x1;
	matrix1 x;
	vector<string> true_pred;
	vector<string> pred;
	vector<double> pred_d;
	vector<double> true_pred_double;
	vector<vector<double>> conf_mat;
	x1=readCSV("../../DATASETS/features_test.csv");
	x=readCSV_to_double(x1);

	for (int i=0; i<x1.size(); i++)
	{
			true_pred.push_back(x1[i][512]);
	}
	for (int i=0; i<x.size(); i++)
	{
		pred.push_back(svm_predict(x[i]));
		pred_d.push_back(svm_predict_d(x[i]));
	}
	true_pred_double=convert_to_vecd(true_pred);

//Affichage de quelques predictions
	for (int i=4; i<9; i++)
	{
	cout<< "svm_pred : "<< " "<<pred[i]<<" true_val : "<< " "<<true_pred[i]<<endl;
	}

// Evaluation
   evaluate(true_pred,pred);
	conf_mat=confusion_matrix(true_pred_double,pred_d);
	print_conf_mat(conf_mat);

    return 0;
}

