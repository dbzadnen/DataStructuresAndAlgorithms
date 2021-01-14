#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
typedef pair<int,int> pi;
typedef pair<pi,pi> quad;

int kadane(vector<int> &vec,int& besti,int& beste){
    // always locate maximum sum of size k till the suls becomes negative so it resets and then keep going
    int sum = 0,start = 0,best = 0 , startbs = 0 , endbs = 0,i_min = 0;
    // worst case where all are negatives , take neart abolute value to 0
    int min = (vec[0]);
    for(int i = 0 ;i< (int)vec.size();i++){
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
    besti = startbs;
    beste = endbs;
    return best;
}
int maxvol(quad pi){
   return (abs(pi.first.first - pi.first.second) +1) * (abs(pi.second.first - pi.second.second) +1);
}
int compute(vector<vector<int>> &grid,vector<vector<int>> &cmsum,int start,int end,int& upper,int &lower,int h,int n){
    vector<int> rect (h,0);
    for(int y = 0;y < h;y++){
        rect[y] = cmsum[y][end] - cmsum[y][start] + grid[y][start];
    }
    int result = kadane(rect,upper,lower);
    return result;
}
/*int kadane2d(vector<vector<int>> &vec,int n,int h){
    // Time Complexity : n*h + n²*h
    vector<vector<int>> cumsum (h,vector<int>(n,0));
    for(int x = 0;x < n;x++){
        for(int y = 0;y < h;y++){
            cumsum[y][x] = cumsum[y][max(x-1,0)] + vec[y][x];
        }
    }
    quad localrect = {{0,0},{0,0}},bestrect = {{0,0},{0,0}};
    int best = vec[0][0];
    for(int globalend =1;globalend < n;globalend++ ){
        localrect.second.first = globalend;
        for(int globalstart =0;globalstart <= globalend;globalstart++ ){
            localrect.second.second = globalstart;
            int upper=0,bottom=0;
            int result = compute(vec,cumsum,globalstart,globalend,upper,bottom,h,n);
            localrect.first.first = bottom;
            localrect.first.second = upper;
            if(result > best || (result == best && maxvol(localrect) > maxvol(bestrect))){
                best = result;
                bestrect = localrect;
            }
        }
    }
    return best;
}
*/
int eval(vector<vector<int>>& vec,vector<vector<int>> &cumsum,int start,int &end,int &localbest,quad &localbestrect,quad &localrect,int h,int n){
    localrect.second.second = start;
    int upper=0,bottom=0;
    int result = compute(vec,cumsum,start,end,upper,bottom,h,n);
    localrect.first.first = bottom;
    localrect.first.second = upper;
    localrect.second.first = end;
    if(result > localbest || (result == localbest && maxvol(localrect) > maxvol(localbestrect))){
        localbest = result;
        localbestrect = localrect;
        return 1;
    }else {
        return 0;
    }
}
/*int kadane2d(vector<vector<int>> &vec,int n,int h,quad &fin){

    // Time Complexity : n*h + h*n*log(n)
    vector<vector<int>> cumsum (h,vector<int>(n,0));
    for(int x = 0;x < n;x++){
        for(int y = 0;y < h;y++){
            cumsum[y][x] = cumsum[y][max(x-1,0)] + vec[y][x];
        }
    }
    quad localrect = {{0,0},{0,0}},globalbestrect = {{0,0},{0,0}};
    int globalbest = vec[0][0];
    for(int globalend =0;globalend < n;globalend++ ){
        //cout <<"current end is :" << globalend << endl;
        //fixed end point
        localrect.second.first = globalend;

        //bs parameters of the left segment
        int globalstart = 0;
        int virtualend = globalend;
        
        int bestupper=0,bestbottom=0;
        int localbest = compute(vec,cumsum,globalstart,globalend,bestupper,bestbottom,h,n);
        quad localbestrect = {{bestbottom,bestupper},{globalend,globalstart}};
        bool repeat = true;

        while(globalstart <= virtualend){
                        //if there are only 2 rows then get the max , if there is one take it otherwise binary search

            int mid = (globalstart + (virtualend - globalstart) / 2);
            if(virtualend - globalstart == 1){
                eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n);
                eval(vec,cumsum,mid+1,globalend,localbest,localbestrect,localrect,h,n);
                break;
            }else if(virtualend - globalstart == 0){
                eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n);
                break;
            } else if(eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n) == 1){
                globalstart = mid;
            }else{
                virtualend = mid;
            }
        }

        if(localbest > globalbest || (localbest == globalbest && maxvol(localbestrect) > maxvol(globalbestrect))){
            globalbest = localbest;
            globalbestrect = localbestrect;
        }

    }
    fin = globalbestrect;
    return globalbest;
}*/
int kadane2dOptimal(vector<vector<int>> &vec,int n,int h,quad &fin){

    //Time complexity of :  n*h + h*(log(n)+log(n-k)) where k is the optimal left segment x position : upperbounded by (n*h) and lower bounded by (n*h) => asymptotcily n*h time complexity and also n*h space complexity  
    vector<vector<int>> cumsum (h,vector<int>(n,0));
    for(int x = 0;x < n;x++){
        for(int y = 0;y < h;y++){
            cumsum[y][x] = cumsum[y][max(x-1,0)] + vec[y][x];
        }
    }

    quad localrect = {{0,0},{0,0}},globalbestrect = {{0,0},{0,0}};
    int globalbest = vec[0][0];

        /////// FINDING THE LEFT SEGMENT    
        int globalend =n-1;
        //cout <<"current end is :" << globalend << endl;
        //fixed end point
        localrect.second.first = globalend;

        //bs parameters of the left segment
        int globalstart = 0;
        int virtualend = globalend;
        
        int bestupper=0,bestbottom=0;
        int localbest = compute(vec,cumsum,globalstart,globalend,bestupper,bestbottom,h,n);
        quad localbestrect = {{bestbottom,bestupper},{globalend,globalstart}};
        bool repeat = true;

        while(globalstart <= virtualend){
            //if there are only 2 rows then get the max , if there is one take it otherwise binary search

            int mid = (globalstart + (virtualend - globalstart) / 2);
            if(virtualend - globalstart == 1){
                eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n);
                eval(vec,cumsum,mid+1,globalend,localbest,localbestrect,localrect,h,n);
                break;
            }else if(virtualend - globalstart == 0){
                eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n);
                break;
            } else if(eval(vec,cumsum,mid,globalend,localbest,localbestrect,localrect,h,n) == 1){
                globalstart = mid;
            }else{
                virtualend = mid;
            }
        }

        int virutalStart  = globalstart;
        while(virutalStart<= globalend){

            int mid = (virutalStart + (globalend - virutalStart) / 2);
            if(abs(globalend - virutalStart) <= 1){
                eval(vec,cumsum,globalstart,mid,localbest,localbestrect,localrect,h,n);
                if(abs(globalend-virutalStart) == 1){
                    mid++;
                eval(vec,cumsum,globalstart,(mid),localbest,localbestrect,localrect,h,n);
                }
                break;
            }else if (eval(vec,cumsum,globalstart,mid,localbest,localbestrect,localrect,h,n)){
                globalend = mid;
            }else{
                virutalStart = mid;
            }
        }

        if(localbest > globalbest || (localbest == globalbest && maxvol(localbestrect) > maxvol(globalbestrect))){
            globalbest = localbest;
            globalbestrect = localbestrect;
        }

    /////
    fin = globalbestrect;
    return globalbest;
}
int main(){
    vector<int> vec =  {-5,6,8,-2,0,8,-100,12};
    //test kadane 1d with vec 
   /*   vector<vector<int>> vec2d =  { { 1, 2, -1, -4, -20 },
                        { -8, -3, 4, 2, 1 },
                        { 3, 8, 10, 1, 3 },
                        { -4, -1, 1, 7, -6 } };*/
    vector<vector<int>> vec2d =  { { -7, 6, -6 },
                        { -6, 1, -1 },
                        { 1, 2, -7 } }; 
              
    quad cord;
    int n = 3;
    int result = kadane2dOptimal(vec2d,3,3,cord);
    printf("(top,left) (%d,%d)\n(bottom,right) (%d,%d)\nMaximum sum : %d",cord.first.second,cord.second.second,cord.first.first,cord.second.first, result)   ; 
 
    return 0;
}
