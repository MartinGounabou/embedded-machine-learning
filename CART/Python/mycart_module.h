#include <vector>
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
vector<vector<double>> confusion_matrix(vector<double>& targets,vector<double>& outputs);
vector<double> convert_to_vecd(vector<string> x);
string cart_predict(vector<double>feature);
void evaluate(vector<string>& targets,vector<string>& outputs);
void print_conf_mat(vector<vector<double>>& Mat);
matrix1 readCSV_to_double(matrix &result);
void deleteCol( matrix &M, int col  );
void deleteRow( matrix &M, int row );
matrix readCSV( string filename );








