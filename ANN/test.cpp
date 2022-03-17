#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>


//------------------------------------------------------------------------DOMAINES NAMESPACES
using namespace std;

class CSVReader
{
    string fileName;
    string delimeter;
public:
    CSVReader(string filename, string delm = ",") :
            fileName(filename), delimeter(delm)
    { }
    // Function to fetch data from a CSV File
    vector<vector<string> > getData();
};
/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/
vector<vector<string> > CSVReader::getData()
{
    ifstream file(fileName);
    vector<vector<string> > dataList;
    string line = "";
    // Iterate through each line and split the content using delimeter
    while (getline(file, line))
    {
        
        vector<string> vec;
        boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
        dataList.push_back(vec);
    }
    // Close the File
    file.close();
    return dataList;
}



// Weights file name
const string model_fn = "model-neural-network.dat";

// Report file name
const string report_fn = "testing-report.dat";

// Number of testing samples
const int nTesting = 330;

// Image size in MNIST database
const int width = 100;
const int height = 28;

// n1 = Number of input neurons
// n2 = Number of hidden1 neurons
// n3 = Number of hidden2 neurons
// n4 = Number of output neurons

const int n1 = 512; // without bias neuron 
const int n2 = 256; 
const int n3 = 64; 
const int n4 = 10; // Ten classes: 0 - 9

// From layer 1 to layer 2. Or: Input layer - Hidden layer
double *w1[n1 + 1], *out1;

// From layer 2 to layer 3. Or; Hidden1 layer - Hidden2 layer
double *w2[n2 + 1], *in2, *out2;

// From layer 2 to layer 3. Or; Hidden2 layer - Output layer
double *w3[n3 + 1], *in3, *out3;
// Layer 3 - Output layer
double *in4, *out4;
double expected[n4 + 1];



ofstream report;

// +--------------------+
// | About the software |
// +--------------------+

void about() {
	// Details
	cout << "*************************************************" << endl;
	cout << "*** Testing Neural Network for MNIST database ***" << endl;
	cout << "*************************************************" << endl;
	cout << endl;
	cout << "No. input neurons: " << n1 << endl;
	cout << "No. hidden neurons: " << n2 << endl;
	cout << "No. hidden neurons: " << n3 << endl;
	cout << "No. output neurons: " << n4 << endl;
	cout << endl;
	cout << "No. testing sample: " << nTesting << endl << endl;
}

// +-----------------------------------+
// | Memory allocation for the network |
// +-----------------------------------+

void init_array() {
	// Layer 1 - Layer 2 = Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        w1[i] = new double [n2 + 1];
    }
    
    out1 = new double [n1 + 1];

	// Layer 2 - Layer 3 = Hidden1 layer - Hidden2 layer
    for (int i = 1; i <= n2; ++i) {
        w2[i] = new double [n3 + 1];
    }
    
    in2 = new double [n2 + 1];
    out2 = new double [n2 + 1];

	// Layer 2 - Layer 3 = Hidden layer - Output layer
    for (int i = 1; i <= n3; ++i) {
        w3[i] = new double [n4 + 1];
    }
    
    in3 = new double [n3 + 1];
    out3 = new double [n3 + 1];
	// Layer 3 - Output layer
    in4 = new double [n4 + 1];
    out4 = new double [n4 + 1];
}

// +----------------------------------------+
// | Load model of a trained Neural Network |
// +----------------------------------------+

void load_model(string file_name) {
	ifstream file(file_name.c_str(), ios::in);
	
	// Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
			file >> w1[i][j];
		}
    }
	
	// Hidden1 layer - Hidden2 layer
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
			file >> w2[i][j];
		}
    }

    // Hidden2 layer - Output layer
    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
			file >> w3[i][j];
		}
    }
	
	file.close();
}

// +------------------+
// | Sigmoid function |
// +------------------+

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

// +------------------------------+
// | Forward process - Perceptron |
// +------------------------------+


void perceptron() {
    for (int i = 1; i <= n2; ++i) {
		in2[i] = 0.0;
	}

    for (int i = 1; i <= n3; ++i) {
		in3[i] = 0.0;
	}

    for (int i = 1; i <= n4; ++i) {
		in4[i] = 0.0;
	}

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            in2[j] += out1[i] * w1[i][j];
		}
	}

    for (int i = 1; i <= n2; ++i) {
		out2[i] = sigmoid(in2[i]);
	}

    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
            in3[j] += out2[i] * w2[i][j];
		}
	}

    for (int i = 1; i <= n3; ++i) {
		out3[i] = sigmoid(in3[i]);
	}

    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
            in4[j] += out3[i] * w3[i][j];
		}
	}

    for (int i = 1; i <= n4; ++i) {
		out4[i] = sigmoid(in4[i]);
	}
}

// +---------------+
// | Norm L2 error |
// +---------------+

double square_error(){
    double res = 0.0;
    for (int i = 1; i <= n4; ++i) {
        res += (out4[i] - expected[i]) * (out4[i] - expected[i]);
	}
    res *= 0.5;
    return res;
}

// +--------------------------------------------------------------+
// | Reading input - Features and the corresponding label |
// +--------------------------------------------------------------+

int input(vector<vector<double>> X, vector<double> y, int cpt) {

    int i=0;

    for(auto it = X[cpt].cbegin(); it != X[cpt].cend(); ++it) {
        out1[i] = *it;
        i = i+1;
    }

	// Reading label
    for (int i = 1; i <= n4; ++i) {
		expected[i] = 0.0;
	}
    expected[(int)y[cpt] + 1] = 1.0;
    
    cout << "Label: " << y[cpt] << endl;

    return (int)y[cpt];
}


// +--------------------------------------------------------------+
// | Confusion matrix |
// +--------------------------------------------------------------+


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

// +--------------+
// | Main Program |
// +--------------+

int main(int argc, char *argv[]) {

    //--------------------------------------------------------

 // Creating an object of CSVWriter
    CSVReader reader("../DATASETS/features_test.csv");

    // Get the data from CSV File
    vector<vector<string> > dataList = reader.getData();
    vector<vector<double>> X;

    vector<string> y_string;
    vector<double> y;

    vector<double> y_pred;

	vector<vector<double>> conf_mat;

    for ( int i=0; i<nTesting; i++){
        vector<double> vec;
        for(auto it = dataList[i].cbegin(); it != dataList[i].cend()-1; ++it) {
            vec.push_back(atof((*it).c_str()) );
        
            }
        X.push_back(vec);
    } 

    for ( int i=0; i<nTesting; i++){
        y_string.push_back(dataList[i][512]);

    } 
    
    y = convert_to_vecd(y_string);

    //--------------------------------------------------------------------------------

	about();
	
    report.open(report_fn);
	
	// Neural Network Initialization
    init_array(); // Memory allocation
    load_model(model_fn); // Load model (weight matrices) of a trained Neural Network
    
    int nCorrect = 0;
    for (int sample = 1; sample <= nTesting; ++sample) {
        cout << "Sample " << sample << endl;
        
        // Getting (features, label)

        int label = input(X, y, sample-1);
        
		
		// // Classification - Perceptron procedure
        perceptron();
        
        // // Prediction
        int predict = 1;
        for (int i = 2; i <= n4; ++i) {
			if (out4[i] > out4[predict]) {
				predict = i;
			}
		}
		--predict;

        y_pred.push_back(predict);
		// // Write down the classification result and the squared error
		double error = square_error();
		printf("Error: %0.6lf\n", error);
		
		if (label == predict) {
			++nCorrect;
			cout << "Classification: YES. Label = " << label << ". Predict = " << predict << endl << endl;
			report << "Sample " << sample << ": YES. Label = " << label << ". Predict = " << predict << ". Error = " << error << endl;
		} else {
			cout << "Classification: NO.  Label = " << label << ". Predict = " << predict << endl;
			cout << "STFT:" << endl;
			cout << endl;
			report << "Sample " << sample << ": NO.  Label = " << label << ". Predict = " << predict << ". Error = " << error << endl;
		}
    }

	// Summary
    double accuracy = (double)(nCorrect) / nTesting * 100.0;
    cout << "Number of correct samples: " << nCorrect << " / " << nTesting << endl;
    printf("Accuracy: %0.2lf\n", accuracy);
    
    report << "Number of correct samples: " << nCorrect << " / " << nTesting << endl;
    report << "Accuracy: " << accuracy << endl;
    conf_mat=confusion_matrix(y,y_pred);
	print_conf_mat(conf_mat);
    report.close();
 
    return 0;
}
