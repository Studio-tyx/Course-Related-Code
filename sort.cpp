////////////////////////////////////////////////////////////////////////////////
////    author: tyx
////    create time: 2021.06.13 10:39
////    finish time: 2021.06.13 20:58
////    summary: review of Data Structure SORT algorithm
////    description: this code concentrates on a variety of sorting methods:
////        insert sort, shell sort, bubble sort, quick sort, 
////        select sort, merge sort, ...  
////////////////////////////////////////////////////////////////////////////////
#include<iostream>
using namespace std;

void set_initial(int* a, int* res, int length){
    for(int i=0;i<length;i++){
        res[i]=a[i];
    }
}

void show(int* p, int length){
    for(int i=0;i<length;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
}

void show(int* p, int low, int high){
    for(int i=low;i<=high;i++){
        cout<<p[i]<<" ";
    }
    cout<<endl;
}

void swap(int* a, int i, int j){
    int temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

//insert sort:
//  average time complexity: O(n^2)  
//  stable
int* insert_sort(int* a,int length){
    int* res=new int[length];
    int temp;
    set_initial(a,res,length);
    for(int i=1;i<length;i++){
        if(res[i]<=res[i-1]){
            temp=res[i];
            res[i]=res[i-1];
            int j;
            for(j=i-1;j>=0&&temp<res[j];j--){ //look for the correct place to put
                res[j+1]=res[j];
            }
            res[j+1]=temp;  //put the number
        }
    }
    return res;
}

//shell sort of single pass sorting with different step size
int* shell_sort_by_step(int* a, int length, int step){
    int temp;
    int count=0;
    for(int i=step;i<length;i++){
        if(a[i]<=a[i-step]){
            temp=a[i];
            int j;
            for(j=i-step;j>=0&&temp<=a[j];j-=step){
                a[j+step]=a[j];
                count++;
            }
            a[j+step]=temp;
            count++;
        }
    }
    // cout<<"shell count: "<<count<<endl;
    return a;
}

//shell sort:
//  average time complexity: [O(nlogn), O(n^2)] -> O(n^1.3) (after lots of test)
//  unstable
int* shell_sort(int* a, int length){
    int* res=new int[length];
    set_initial(a,res,length);
    res=shell_sort_by_step(res,length,5);
    res=shell_sort_by_step(res,length,2);
    res=shell_sort_by_step(res,length,1);
    return res;
}

//bubble sort:
//  average time complexity: O(n^2)
//  stable
int* bubble_sort(int* a, int length){
    int* res=new int[length];
    set_initial(a,res,length);
    for(int i=0;i<length;i++){
        for(int j=i+1;j<length;j++){
            if(res[i]>res[j]){
                swap(res,i,j);
            }
        }
    }
    return res;
}

/*
algorithm: SPLIT(A[low,...high])
input: array A[low,...high]
output: the new position of the datum element w
    using A[low] as the base element to divide the array A
    1. x←A[low]
    2. while (low<high)
    3. while (low<high && A[high]>x) --high;
    4. A[low] ←A[high]
    5. while (low<high && A[low]≤x) ++low;
    6. A[high] ←A[low]
    7. end while
    8. A[low] ← x
    9. w←low
    10.return A and w 
*/
int split(int* a, int low, int high){
    int w;
    int temp=a[low];
    w=a[low];
    while(low<high){
        while(low<high&&a[high]>=w)  high--;
        a[low]=a[high];
        while(low<high&&a[low]<=w)   low++;
        a[high]=a[low];
    }
    a[low]=temp;
    return low;
}

void quick_sort_content(int* a, int low, int high){
    int mid;
    if(low<high){
        mid=split(a,low,high);
        quick_sort_content(a,low,mid-1);
        quick_sort_content(a,mid+1,high);
    }
}

//quick sort:
//  average time complexity: [O(nlogn), O(n^2)]
//  unstable
int* quick_sort(int* a, int length){
    int* res=new int[length];
    set_initial(a,res,length);
    quick_sort_content(res,0,length-1);
    return res;
}

//select sort:
//  average time complexity: O(n^2)
//  unstable
int* select_sort(int* a, int length){
    int* res=new int[length];
    set_initial(a,res,length);
    int min_value;
    int min_index;
    for(int i=0;i<length;i++){  //find the i-th min number
        min_value=0xffff,min_index=length;
        for(int j=i;j<length;j++){
            if(res[j]<min_value){
                min_value=res[j];
                min_index=j;
            }
        }
        if(min_index!=length){
            swap(res,min_index,i);
        }
    }
    return res;
}
/*
Algorithm: MERGE(A, p, q, r)
input: array A[p...q] and A[q+1...r], both in order
output: merge A[p...q] and A[q+1...r]
1. i←p; j←q+1; k←p; 
2. while i≤q and j≤r
3. if A[i] ≤A[j] then 
4. B[k]←A[i]
5. i ←i+1
6. else
7. B[k]←A[j]
8. j←j+1
9. end if
10. k←k+1
11.end while
12. if i=q+1 then B[k...r] ←A[j...r]
13. else B[k...r] ←A[i...q]
14. end if
15. A ← B
*/
void merge(int* a, int p, int q, int r){
    int* b=new int[r+1];
    int i=p,j=q+1,k=p;
    while(i<=q&&j<=r){
        if(a[i]<=a[j]) b[k]=a[i++];
        else b[k]=a[j++];
        k++;
    }
    int ii,jj;
    if(i==q+1){
        jj=j;
        for(ii=k;ii<=r;ii++) b[ii]=a[jj++];
    }
    else {
        jj=i;
        for(ii=k;ii<=r;ii++) b[ii]=a[jj++];
    }
    for(int i=p;i<=r;i++){
        a[i]=b[i];
    }
    delete[] b;
}

void merge_content(int* a, int low, int high){
    if(low<high){
        int mid=(low+high)/2;
        merge_content(a,low,mid);
        merge_content(a,mid+1,high);
        merge(a,low,mid,high);
    }
}

//merge sort:
//  average time complexity: O(nlogn)
//  stable
int* merge_sort(int* a, int length){
    int* res=new int[length];
    set_initial(a,res,length);
    merge_content(res,0,length-1);
    return res;
}

int main(){
    int a[]={49,39,65,97,76,13,27,69};
    int* p;
    show(a,8);

    p=insert_sort(a,8);
    cout<<"insert sort:\t";
    show(p,8);

    p=shell_sort(a,8);
    cout<<"shell sort:\t";
    show(p,8);

    p=bubble_sort(a,8);
    cout<<"bubble sort:\t";
    show(p,8);

    p=quick_sort(a,8);
    cout<<"quick sort:\t";
    show(p,8);

    p=select_sort(a,8);
    cout<<"select sort:\t";
    show(p,8);

    p=merge_sort(a,8);
    cout<<"merge sort:\t";
    show(p,8);

    //do as pause (please do not delete)
    cin.get();
    return 0;
}
