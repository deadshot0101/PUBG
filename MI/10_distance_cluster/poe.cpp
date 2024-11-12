#include<bits/stdc++.h>
#include<fstream>
using namespace std;
void cal_center(vector<vector<double>>points,double x,double y)
{
    
    for(auto it:points)
    {
        x+=it[0];
        y+=it[1];
    }
    double n=points.size();
    x/=n;
    y/=n;
}
double cal_dist(double x1,double x2,double y1,double y2)
{
    return (sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2))));
}
int main()
{
    ifstream in("input.csv");
    ofstream out("output1.csv");
    vector<vector<double>>points;
    vector<string>label;
    string line;
    while(getline(in,line))
    {
        stringstream ss(line);
        string data;
        vector<double>point;
        while(getline(ss,data,','))
        {
            point.push_back(stod(data));
        }
        points.push_back(point);
        string point_name="point"+ to_string(points.size());
        label.push_back(point_name);
    }

    //compute center
    double x=0.0,y=0.0;
    cal_center(points,x,y);
    out<<"center: {"<<x<<","<<y<<"}\n";
    int i,j,n=points.size();
    out<<"distanec matrix:\n";
    out<<"point,";
    for(auto it:label)
    out<<it<<",";
    out<<"\n";
    for(i=0;i<n;i++)
    {
        out<<label[i]<<",";
        for(j=0;j<i;j++)
        out<<",";
        for(j=i;j<n;j++)
        {
            out<<cal_dist(points[i][0],points[j][0],points[i][1],points[j][1])<<",";
        }
        out<<"\n";
    }


}