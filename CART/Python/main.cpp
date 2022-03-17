#include "mycart_module.h"

int main()
{
   //init();
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
      pred.push_back(cart_predict(x[i]));
      //pred_d.push_back(svm_predict_d(x[i]));
   }
   //true_pred_double=convert_to_vecd(true_pred);

   //Affichage de quelques predictions
   for (int i=4; i<9; i++)
   {
   cout<< "cart_pred : "<< " "<<pred[i]<<" true_val : "<< " "<<true_pred[i]<<endl;
   }

   pred_d=convert_to_vecd(pred);
   true_pred_double=convert_to_vecd(true_pred);
   evaluate(true_pred,pred);
   conf_mat=confusion_matrix(true_pred_double,pred_d);
   print_conf_mat(conf_mat);


    return 0;
}
