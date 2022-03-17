
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <iostream>
#include <fstream>  
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <chrono>

//------------------------------------------------------------------------NAMESPACES DOMAINES
using namespace std;
using namespace std::chrono;


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

//--------------------------------------------------------------endread


// Weights file name
const string model_fn = "model-neural-network.dat";

// Report file name
const string report_fn = "training-report.dat";

// Number of training samples
const int nTraining = 670;

// Image size in MNIST database
const int width = 100;
const int height = 28;

// n1 = Number of input neurons
// n2 = Number of hidden1 neurons
// n3 = Number of hidden2 neurons
// n4 = Number of output neurons
// epochs = Number of iterations for back-propagation algorithm
// learning_rate = Learing rate
// momentum = Momentum (heuristics to optimize back-propagation algorithm)
// epsilon = Epsilon, no more iterations if the learning error is smaller than epsilon

const int n1 = 512; //  without bias neuron 
const int n2 = 256; 
const int n3 = 64; 
const int n4 = 10; // Ten classes: 0 - 9
const int epochs = 1000;
const double learning_rate = 1e-3;
const double momentum = 0.9;
const double epsilon = 1e-3;

// From layer 1 to layer 2. Or: Input layer - Hidden layer
double *w1[n1 + 1], *delta1[n1 + 1], *out1;

// From layer 2 to layer 3. Or; Hidden1 layer - Hidden2 layer
double *w2[n2 + 1], *delta2[n2 + 1], *in2, *out2, *theta2;

// From layer 2 to layer 3. Or; Hidden2 layer - Output layer
double *w3[n3 + 1], *delta3[n3 + 1], *in3, *out3, *theta3;

// Layer 3 - Output layer
double *in4, *out4, *theta4;
double expected[n4 + 1];

int d[width + 1][height + 1];


ofstream report;

// +--------------------+
// | About the software |
// +--------------------+

void about() {
	// Details
	cout << "**************************************************" << endl;
	cout << "*** Training Neural Network for MNIST database ***" << endl;
	cout << "**************************************************" << endl;
	cout << endl;
	cout << "No. input neurons: " << n1 << endl;
	cout << "No. hidden neurons: " << n2 << endl;
	cout << "No. output neurons: " << n3 << endl;
	cout << "No. output neurons: " << n4 << endl;
	cout << endl;
	cout << "No. iterations: " << epochs << endl;
	cout << "Learning rate: " << learning_rate << endl;
	cout << "Momentum: " << momentum << endl;
	cout << "Epsilon: " << epsilon << endl;
	cout << endl;
	cout << "No. training sample: " << nTraining << endl << endl;
}

// +-----------------------------------+
// | Memory allocation for the network |
// +-----------------------------------+

void init_array() {
	// Layer 1 - Layer 2 = Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        w1[i] = new double [n2 + 1];
        delta1[i] = new double [n2 + 1];
    }
    
    out1 = new double [n1 + 1];

	// Layer 2 - Layer 3 = Hidden1 layer - Hidden1 layer
    for (int i = 1; i <= n2; ++i) {
        w2[i] = new double [n3 + 1];
        delta2[i] = new double [n3 + 1];
    }
    
    in2 = new double [n2 + 1];
    out2 = new double [n2 + 1];
    theta2 = new double [n2 + 1];

	// Layer 3 - Layer 4 = Hidden2 layer - Output layer
    for (int i = 1; i <= n3; ++i) {
        w3[i] = new double [n4 + 1];
        delta3[i] = new double [n4 + 1];
    }
    
    in3 = new double [n2 + 1];
    out3 = new double [n2 + 1];
    theta3 = new double [n2 + 1];

	// Layer 4 - Output layer
    in4 = new double [n3 + 1];
    out4 = new double [n3 + 1];
    theta4 = new double [n3 + 1];
    
    // Initialization for weights from Input layer to Hidden layer
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            int sign = rand() % 2;

            // Another strategy to randomize the weights - quite good 
            // w1[i][j] = (double)(rand() % 10 + 1) / (10 * n2);
            
            w1[i][j] = (double)(rand() % 6) / 10.0;
            if (sign == 1) {
				w1[i][j] = - w1[i][j];
			}
        }
	}
	
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
            int sign = rand() % 2;
			
			// Another strategy to randomize the weights - quite good 
            // w2[i][j] = (double)(rand() % 6) / 10.0;

            w2[i][j] = (double)(rand() % 10 + 1) / (10.0 * n3);
            if (sign == 1) {
				w2[i][j] = - w2[i][j];
			}
        }
	}

	// Initialization for weights from Hidden layer to Output layer
    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
            int sign = rand() % 2;
			
			// Another strategy to randomize the weights - quite good 
            // w2[i][j] = (double)(rand() % 6) / 10.0;

            w3[i][j] = (double)(rand() % 10 + 1) / (10.0 * n4);
            if (sign == 1) {
				w3[i][j] = - w3[i][j];
			}
        }
	}
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

// +----------------------------+
// | Back Propagation Algorithm |
// +----------------------------+

void back_propagation() {
    double sum;

    for (int i = 1; i <= n4; ++i) {
        theta4[i] = out4[i] * (1 - out4[i]) * (expected[i] - out4[i]);
	}

    for (int i = 1; i <= n3; ++i) {
        sum = 0.0;
        for (int j = 1; j <= n4; ++j) {
            sum += w3[i][j] * theta4[j];
		}
        theta3[i] = out3[i] * (1 - out3[i]) * sum;
    }

    for (int i = 1; i <= n2; ++i) {
        sum = 0.0;
        for (int j = 1; j <= n3; ++j) {
            sum += w2[i][j] * theta3[j];
		}
        theta2[i] = out2[i] * (1 - out2[i]) * sum;
    }

    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
            delta3[i][j] = (learning_rate * theta4[j] * out3[i]) + (momentum * delta3[i][j]);
            w3[i][j] += delta3[i][j];
        }
	}
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
            delta2[i][j] = (learning_rate * theta3[j] * out2[i]) + (momentum * delta2[i][j]);
            w2[i][j] += delta2[i][j];
        }
	}

    for (int i = 1; i <= n1; ++i) {
        for (int j = 1 ; j <= n2 ; j++ ) {
            delta1[i][j] = (learning_rate * theta2[j] * out1[i]) + (momentum * delta1[i][j]);
            w1[i][j] += delta1[i][j];
        }
	}
}

// +-------------------------------------------------+
// | Learning process: Perceptron - Back propagation |
// +-------------------------------------------------+

int learning_process() {
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
			delta1[i][j] = 0.0;
		}
	}

    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
			delta2[i][j] = 0.0;
		}
	}

    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
			delta3[i][j] = 0.0;
		}
	}

    for (int i = 1; i <= epochs; ++i) {
        perceptron();
        back_propagation();
        if (square_error() < epsilon) {
			return i;
		}
    }
    return epochs;
}

// +--------------------------------------------------------------+
// | Reading input - Sound SFTP and the corresponding label |
// +--------------------------------------------------------------+

void input(vector<vector<double>> X, vector<double> y, int cpt) {
	// Reading image

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

    
}

// +------------------------+
// | Saving weights to file |
// +------------------------+

void write_matrix(string file_name) {
    ofstream file(file_name.c_str(), ios::out);
	
	// Input layer - Hidden layer
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
			file << w1[i][j] << " ";
		}
		file << endl;
    }
	// Hidden1 layer - Hidden1 layer
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
			file << w2[i][j] << " ";
		}
        file << endl;
    }
	// Hidden2 layer - Output layer
    for (int i = 1; i <= n3; ++i) {
        for (int j = 1; j <= n4; ++j) {
			file << w3[i][j] << " ";
		}
        file << endl;
    }

	file.close();
}

// +------------------------+
// | converti les labels en vecteur encodé de 0 à 10 |
// +------------------------+

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
    CSVReader reader("../DATASETS/features_train.csv");

    // Get the data from CSV File
    vector<vector<string> > dataList = reader.getData();
    vector<vector<double>> X;

    vector<string> y_string;
    vector<double> y;


    for ( int i=0; i<nTraining; i++){
        vector<double> vec;
        for(auto it = dataList[i].cbegin(); it != dataList[i].cend()-1; ++it) {
            vec.push_back(atof((*it).c_str()) );
        
            }
        X.push_back(vec);
    } 
    for ( int i=0; i<nTraining; i++){
        y_string.push_back(dataList[i][512]);

    } 
    
    y = convert_to_vecd(y_string);


    
    //--------------------------------------------------------------------------------
	about();
	
    report.open(report_fn);
	// Neural Network Initialization
    init_array();
    
    auto start = high_resolution_clock::now();

    for (int sample = 1; sample <= nTraining; ++sample) {
        cout << "Sample " << sample << endl;
        
        // Getting (features, label)
        input(X,y,sample-1);
		
		// Learning process: Perceptron (Forward procedure) - Back propagation
        int nIterations = learning_process();

		// Write down the squared error
		cout << "No. iterations: " << nIterations << endl;
        printf("Error: %0.6lf\n\n", square_error());
        report << "Sample " << sample << ": No. iterations = " << nIterations << ", Error = " << square_error() << endl;
		
		// Save the current network (weights)
		if (sample % 100 == 0) {
			cout << "Saving the network to " << model_fn << " file." << endl;
			write_matrix(model_fn);
		}
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
  
	
	// Save the final network
    write_matrix(model_fn);

    report.close();
// To get the value of duration use the count()
// member function on the duration object

    cout << "**************************************************" << endl;
	cout << "*** Complexite temporelle du reseaux de neurones : "<< duration.count()  << "  secondes ***" << endl;
	cout << "**************************************************" << endl;
    return 0;
}
