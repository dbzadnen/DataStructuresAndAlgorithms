#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

vector<int> kanade(vector<int> &vec){
    // always locate maximum sum of size k till the suls becomes negative so it resets and then keep going
    int sum = 0,start = 0,best = 0 , startbs = 0 , endbs = 0,i_min = 0;
    // worst case where all are negatives , take neart abolute value to 0
    int min = (vec[0]);
    for(int i = 0 ;i< vec.size();i++){
        sum += vec[i];
        if(abs(vec[i]) < abs(min)){
            min = vec[i];
            i_min = i;
        }
        if(sum < 0){
            sum = 0;
            start = i+1 ;
        }
            if(sum > best || (sum == best && endbs - startbs < i - start) ){
                    best = sum;
                    startbs = start;
                    endbs = i;
            }
        
    }
    if(best == 0){
        best =  min ;
        if(min != 0){
            startbs = i_min;
            endbs = i_min;
        }
    }
    
    return {best,startbs,endbs};
}
int maxvol(pair< pair<int,int>,pair<int,int> > pi){
   return (abs(pi.first.first - pi.first.second) +1) * (abs(pi.second.first - pi.second.second) +1);
}
int kanade2d(vector<vector<int>> &vec,int n,int h){
    int best = 0;
    pair< pair<int,int>,pair<int,int> > cord = {{0,0},{0,0}}, bestcord,localcord;
    vector<int> runningsum(h,0),current(h,0);
    for(int x =0;x < n;x++ ){
        
        for(int y = 0;y < h;y++){
            runningsum[y] += vec[y][x];
            current[y] = vec[y][x];
        }
        vector<int> result =  kanade(runningsum);

        vector<int> result2 =  kanade(current);
        localcord.second.first = x;
        localcord.second.second = x;
        localcord.first.first = result2[1];
        localcord.first.second = result2[2];
        if(result2[0]> result[0] || ( result[0]== result2[0] && maxvol(localcord) > maxvol(cord) )){
            result= result2;
            cord = localcord;
        }
        if(result[0] < 0){
            cord.second.second = x+1;
            cord.first = {0,0};
            runningsum = vector<int>(h,0);
        }else{
            cord.second.first = x;
            cord.first.first = result[1];
            cord.first.second = result[2];
        }
        cout << "res : " << result[0] << endl << "cord : " << cord.second.second << " " << cord.second.first  ;   
        cout <<  " "<< result[1] << " " << result[2] << endl;
        if(result[0] >best || ( result[0]== best && maxvol(cord) > maxvol(bestcord) )){
            bestcord = cord;
            best = result[0];
        } 
         
    }
    cout <<" final ";
    return best;
}

// a regler , l premier bs puis deux bs 
int main(){
    vector<int> vec =  {-5,6,8,-2,0,8,-100,12};
    vector<vector<int>> vec2d = {
        {1,  2,-1,-4,-20},
        {-8,-3, 4, 2, 1},
        { 3, 8, 10,1, 3},
        {-4,-1, 1, 7,-6}
    };
        //cout << kanade(vec)[0] << endl;

    cout <<  " heeey " << kanade2d(vec2d,5,4) << endl;
    return 0;
}

