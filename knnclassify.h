  #include<vector>
#include<cmath>
#include<algorithm>
#include<numeric>
#define rows 150
#define col 4
#define cols 5
using namespace std;
class knn{
public:
 knn();
array<array<double,rows>,rows> EuclideanDistance(array<array<double,cols>,rows>data){

array<double,col>point1,point2;
double temp{0};
array<array<double,rows>,rows>distancematrix;
  for(size_t i{0}; i<rows; i++)
    {
        for(size_t j{0}; j<rows; j++)
        {
            temp=0;
            for(size_t k{0}; k<col; k++)
            {
            point1[k]=data[i][k];
            point2[k]=data[j][k];
            temp=temp+pow(point1[k]-point2[k],2);
            }
    if(temp==0){
     distancematrix[i][j]=INT_MAX;
    }
    else{
distancematrix[i][j]=sqrt(temp);
    }

    }

    }
    return distancematrix;
}

    double acc(array<array<double,cols>,rows>data,array<array<double,rows>,rows>sorting, int k)
    {
        int acccounter{0};

       vector<int>label(k);
        for(size_t j{0}; j<rows; j++)
        {
            for(size_t i{0}; i<k; i++)
            {
                label[i]=data[sorting[j][i]][4];
               // cout<<label[i];
            }
        // cout<<endl;
            int number=label[0];
            int mode=number;
            int counter,countMode{1};
            for (int i{1}; i<k; i++)
            {
                if (label[i] == number)
                {
                    ++counter;
                }
                else
                {
                    if (counter > countMode)
                    {
                        countMode = counter;
                        mode = number;
                    }
                    counter = 1;
                    number = label[i];
                }
            }
            double k=mode-data[j][4];
            if(k==0)
            {
                acccounter++;
            }
        }
        return (double)acccounter;
    }
private:
array<double,col> point1,point2;
};
knn::knn(){};
