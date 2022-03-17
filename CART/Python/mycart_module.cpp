#include "mycart_module.h"



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


string cart_predict(vector<double>feature)
{
   string classical="classical";
   string reggae= "reggae";
   string rock="rock";
   string blues="blues";
   string disco="disco";
   string jazz="jazz";
   string hiphop="hiphop";
   string metal="metal";
   string country="country";
   string pop="pop";

   if (feature[383]<=6.333945)
   {
      if (feature[2]<=291.623)
      {
         if (feature[323]<=26.7708)
         {
            if (feature[5]<=25.94815)
            {
               return jazz;
            }
            else{
               if (feature[257]<=188.19799999999998)
               {
                  return classical;
               }
               else{
                  if (feature[0]<=58.05155)
                  {
                     return jazz;
                  }
                  else{
                     return classical;
                  }
               }
            }
         }
         else{
            if (feature[6]<=87.76604999999999)
            {
               return classical;
            }
            else{
               return jazz;
            }
         }
      }
      else{
         if (feature[38]<=66.69284999999999)
         {
            return jazz;
         }
         else{
            return blues;
         }
      }
   }
   else{
      if (feature[507]<=72.5764)
      {
         if (feature[411]<=11.7117)
         {
            if (feature[256]<=124.1545)
            {
               if (feature[117]<=6.5957349999999995)
               {
                  if (feature[28]<=101.25999999999999)
                  {
                     if (feature[36]<=17.976799999999997)
                     {
                        return blues;
                     }
                     else{
                        if (feature[57]<=17.90795)
                        {
                           if (feature[0]<=38.047349999999994)
                           {
                              return jazz;
                           }
                           else{
                              return hiphop;
                           }
                        }
                        else{
                           return country;
                        }
                     }
                  }
                  else{
                     return classical;
                  }
               }
               else{
                  if (feature[4]<=528.278)
                  {
                     if (feature[296]<=180.80450000000002)
                     {
                        if (feature[384]<=22.7006)
                        {
                           return jazz;
                        }
                        else{
                           return country;
                        }
                     }
                     else{
                        if (feature[0]<=39.9507)
                        {
                           return country;
                        }
                        else{
                           return reggae;
                        }
                     }
                  }
                  else{
                     if (feature[46]<=79.9367)
                     {
                        return country;
                     }
                     else{
                        if (feature[0]<=88.29925)
                        {
                           return jazz;
                        }
                        else{
                           return rock;
                        }
                     }
                  }
               }
            }
            else{
               if (feature[261]<=416.649)
               {
                  if (feature[257]<=542.761)
                  {
                     if (feature[0]<=364.779)
                     {
                        if (feature[0]<=103.3215)
                        {
                           return blues;
                        }
                        else{
                           return country;
                        }
                     }
                     else{
                        return jazz;
                     }
                  }
                  else{
                     return reggae;
                  }
               }
               else{
                  return blues;
               }
            }
         }
         else{
            if (feature[258]<=2331.3450000000003)
            {
               if (feature[59]<=138.451)
               {
                  if (feature[258]<=780.0005)
                  {
                     if (feature[477]<=2.795585)
                     {
                        if (feature[264]<=267.1135)
                        {
                           if (feature[58]<=41.68085)
                           {
                              if (feature[26]<=77.45609999999999)
                              {
                                 if (feature[0]<=6.8902)
                                 {
                                    return blues;
                                 }
                                 else{
                                    if (feature[0]<=22.321595)
                                    {
                                       return reggae;
                                    }
                                    else{
                                       return classical;
                                    }
                                 }
                              }
                              else{
                                 return country;
                              }
                           }
                           else{
                              if (feature[0]<=163.409)
                              {
                                 if (feature[4]<=948.9085)
                                 {
                                    return rock;
                                 }
                                 else{
                                    return metal;
                                 }
                              }
                              else{
                                 return disco;
                              }
                           }
                        }
                        else{
                           if (feature[404]<=20.73005)
                           {
                              if (feature[54]<=43.54685)
                              {
                                 if (feature[0]<=356.4535)
                                 {
                                    return disco;
                                 }
                                 else{
                                    return blues;
                                 }
                              }
                              else{
                                 return country;
                              }
                           }
                           else{
                              if (feature[32]<=179.5235)
                              {
                                 if (feature[264]<=343.7685)
                                 {
                                    if (feature[39]<=76.2422)
                                    {
                                       return blues;
                                    }
                                    else{
                                       return rock;
                                    }
                                 }
                                 else{
                                    return blues;
                                 }
                              }
                              else{
                                 if (feature[2]<=700.2405)
                                 {
                                    return rock;
                                 }
                                 else{
                                    if (feature[0]<=193.559)
                                    {
                                       return country;
                                    }
                                    else{
                                       return jazz;
                                    }
                                 }
                              }
                           }
                        }
                     }
                     else{
                        if (feature[124]<=25.4422)
                        {
                           if (feature[272]<=227.847)
                           {
                              if (feature[27]<=148.72750000000002)
                              {
                                 if (feature[440]<=12.44145)
                                 {
                                    return country;
                                 }
                                 else{
                                    if (feature[5]<=336.90999999999997)
                                    {
                                       return jazz;
                                    }
                                    else{
                                       return rock;
                                    }
                                 }
                              }
                              else{
                                 return pop;
                              }
                           }
                           else{
                              if (feature[2]<=514.704)
                              {
                                 return pop;
                              }
                              else{
                                 if (feature[151]<=19.147100000000002)
                                 {
                                    if (feature[40]<=179.5365)
                                    {
                                       return country;
                                    }
                                    else{
                                       return reggae;
                                    }
                                 }
                                 else{
                                    return reggae;
                                 }
                              }
                           }
                        }
                        else{
                           if (feature[410]<=22.99485)
                           {
                              if (feature[3]<=647.981)
                              {
                                 return jazz;
                              }
                              else{
                                 return classical;
                              }
                           }
                           else{
                              if (feature[317]<=112.945)
                              {
                                 if (feature[270]<=219.94)
                                 {
                                    if (feature[0]<=277.09)
                                    {
                                       return metal;
                                    }
                                    else{
                                       return blues;
                                    }
                                 }
                                 else{
                                    if (feature[101]<=59.38895)
                                    {
                                       return rock;
                                    }
                                    else{
                                       return disco;
                                    }
                                 }
                              }
                              else{
                                 if (feature[260]<=333.4435)
                                 {
                                    if (feature[0]<=94.075)
                                    {
                                       return jazz;
                                    }
                                    else{
                                       return disco;
                                    }
                                 }
                                 else{
                                    return rock;
                                 }
                              }
                           }
                        }
                     }
                  }
                  else{
                     if (feature[6]<=556.6295)
                     {
                        if (feature[28]<=155.01600000000002)
                        {
                           if (feature[149]<=21.82545)
                           {
                              if (feature[485]<=0.721201)
                              {
                                 if (feature[0]<=238.63150000000002)
                                 {
                                    return disco;
                                 }
                                 else{
                                    return hiphop;
                                 }
                              }
                              else{
                                 if (feature[3]<=1267.13)
                                 {
                                    if (feature[1]<=1640.15)
                                    {
                                       return reggae;
                                    }
                                    else{
                                       return hiphop;
                                    }
                                 }
                                 else{
                                    return blues;
                                 }
                              }
                           }
                           else{
                              if (feature[380]<=89.33355)
                              {
                                 if (feature[256]<=213.11399999999998)
                                 {
                                    return disco;
                                 }
                                 else{
                                    if (feature[3]<=917.1255)
                                    {
                                       return hiphop;
                                    }
                                    else{
                                       return disco;
                                    }
                                 }
                              }
                              else{
                                 return reggae;
                              }
                           }
                        }
                        else{
                           if (feature[123]<=27.27555)
                           {
                              if (feature[1]<=694.218)
                              {
                                 if (feature[0]<=139.947)
                                 {
                                    return classical;
                                 }
                                 else{
                                    return country;
                                 }
                              }
                              else{
                                 return reggae;
                              }
                           }
                           else{
                              if (feature[465]<=49.528000000000006)
                              {
                                 if (feature[7]<=604.6585)
                                 {
                                    return disco;
                                 }
                                 else{
                                    return hiphop;
                                 }
                              }
                              else{
                                 if (feature[0]<=555.178)
                                 {
                                    return reggae;
                                 }
                                 else{
                                    return hiphop;
                                 }
                              }
                           }
                        }
                     }
                     else{
                        if (feature[227]<=2.001785)
                        {
                           if (feature[10]<=285.4305)
                           {
                              if (feature[0]<=515.8655)
                              {
                                 return blues;
                              }
                              else{
                                 return country;
                              }
                           }
                           else{
                              if (feature[336]<=88.37205)
                              {
                                 if (feature[1]<=1611.4099999999999)
                                 {
                                    return rock;
                                 }
                                 else{
                                    return metal;
                                 }
                              }
                              else{
                                 if (feature[1]<=763.2764999999999)
                                 {
                                    return rock;
                                 }
                                 else{
                                    return country;
                                 }
                              }
                           }
                        }
                        else{
                           if (feature[500]<=26.0166)
                           {
                              if (feature[380]<=36.55975)
                              {
                                 return jazz;
                              }
                              else{
                                 if (feature[455]<=23.8491)
                                 {
                                    return reggae;
                                 }
                                 else{
                                    if (feature[273]<=399.07349999999997)
                                    {
                                       return disco;
                                    }
                                    else{
                                       return hiphop;
                                    }
                                 }
                              }
                           }
                           else{
                              if (feature[318]<=121.8235)
                              {
                                 if (feature[299]<=96.96695)
                                 {
                                    if (feature[0]<=268.8095)
                                    {
                                       return disco;
                                    }
                                    else{
                                       return rock;
                                    }
                                 }
                                 else{
                                    return pop;
                                 }
                              }
                              else{
                                 if (feature[149]<=65.71005)
                                 {
                                    if (feature[38]<=107.196)
                                    {
                                       return hiphop;
                                    }
                                    else{
                                       return pop;
                                    }
                                 }
                                 else{
                                    return disco;
                                 }
                              }
                           }
                        }
                     }
                  }
               }
               else{
                  if (feature[301]<=139.1055)
                  {
                     if (feature[55]<=116.928)
                     {
                        if (feature[0]<=146.4925)
                        {
                           return country;
                        }
                        else{
                           return reggae;
                        }
                     }
                     else{
                        if (feature[32]<=212.8225)
                        {
                           return metal;
                        }
                        else{
                           return disco;
                        }
                     }
                  }
                  else{
                     if (feature[72]<=228.8785)
                     {
                        if (feature[262]<=592.1275)
                        {
                           if (feature[221]<=4.4877400000000005)
                           {
                              if (feature[341]<=78.45230000000001)
                              {
                                 if (feature[0]<=182.4925)
                                 {
                                    return disco;
                                 }
                                 else{
                                    return metal;
                                 }
                              }
                              else{
                                 return rock;
                              }
                           }
                           else{
                              if (feature[52]<=139.4675)
                              {
                                 return disco;
                              }
                              else{
                                 if (feature[11]<=512.177)
                                 {
                                    if (feature[229]<=27.4007)
                                    {
                                       return disco;
                                    }
                                    else{
                                       return rock;
                                    }
                                 }
                                 else{
                                    if (feature[4]<=893.873)
                                    {
                                       return classical;
                                    }
                                    else{
                                       return country;
                                    }
                                 }
                              }
                           }
                        }
                        else{
                           if (feature[444]<=52.376149999999996)
                           {
                              if (feature[33]<=161.244)
                              {
                                 return country;
                              }
                              else{
                                 return blues;
                              }
                           }
                           else{
                              if (feature[415]<=91.91415)
                              {
                                 if (feature[7]<=780.0275)
                                 {
                                    return disco;
                                 }
                                 else{
                                    if (feature[0]<=435.97900000000004)
                                    {
                                       return country;
                                    }
                                    else{
                                       return metal;
                                    }
                                 }
                              }
                              else{
                                 return hiphop;
                              }
                           }
                        }
                     }
                     else{
                        if (feature[19]<=515.6025)
                        {
                           return metal;
                        }
                        else{
                           return disco;
                        }
                     }
                  }
               }
            }
            else{
               if (feature[38]<=162.76100000000002)
               {
                  return hiphop;
               }
               else{
                  if (feature[0]<=1117.0935)
                  {
                     return reggae;
                  }
                  else{
                     return disco;
                  }
               }
            }
         }
      }
      else{
         if (feature[266]<=710.886)
         {
            if (feature[0]<=244.279)
            {
               if (feature[0]<=227.927)
               {
                  return reggae;
               }
               else{
                  return disco;
               }
            }
            else{
               return pop;
            }
         }
         else{
            if (feature[0]<=616.0464999999999)
            {
               return hiphop;
            }
            else{
               return pop;
            }
         }
      }
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


