#include<bits/stdc++.h>
using namespace std;
template<class T>
class ArraySort{
    private:
        T* arr;
        int cap;
        int size;
        static void swap(T* a, T* b){
            T temp = *(a);
            *a = *b;
            *b = temp;
        }
        static void SortSegment(T*,T*,int,int);
        static void Merge(T*,T*,T*);
        static T* Partition(T*,T*);
        static void Heapify(T*,T*,int);
    public:
        ArraySort(){}
        ~ArraySort(){}
        static double TestTime(void(*)(T*,T*),T*,T*);
        static double TestTime(void(*)(T*,T*,int),T*, T*,int);
        static void PrintArray(T*,T*);
        static void InterchangeSort(T*,T*);
        static void MergeSort(T*,T*);
        static void QuickSort(T*,T*);
        static void HeapSort(T*,T*);
        static void ShellSort(T*,T*,int);
        static void HybridSort(T*,T*,int);
        static void TimSort(T*,T*,int);
};
template<class T>
double ArraySort<T>::TestTime(void(*SortAlg)(T*,T*),T* start, T* end){
    time_t bt,et;
    bt = clock();
    SortAlg(start,end);
    et = clock();
    return (double)(et-bt)/CLOCKS_PER_SEC;
}
template<class T>
double ArraySort<T>::TestTime(void(*SortAlg)(T*,T*,int),T* start, T* end,int min_size){
    time_t bt,et;
    bt = clock();
    SortAlg(start,end,min_size);
    et = clock();
    return (double)(et-bt)/CLOCKS_PER_SEC;
}
template<class T>
void ArraySort<T>::PrintArray(T* start,T* end){
    int n = end - start + 1;
    for(int i = 0; i < n; i++){
        cout << *(start+i) << " ";
    }
    cout << endl;
}
template<class T>
void ArraySort<T>::InterchangeSort(T* start, T* end){
    int n = end - start + 1;
    for(int i = 0; i < n; i++){
        for(int j = i+ 1; j < n; j++){
            if(*(start+i) > *(start+j)){
                ArraySort::swap(start+i,start+j);
            }
        }
    }
}
template<class T>
void ArraySort<T>::SortSegment(T*start,T* end,int segment, int jump){
    int size = end-start + 1;
    int current = segment + jump;
    while(current < size){
        T temp = *(start+current);
        int walker = current-jump;
        while(walker >= 0 && temp < *(start+walker)){
            *(start+walker+jump) = *(start+walker);
            walker -= jump;
        }
        *(start+walker+jump) = temp;
        current += jump;
    }
}
template<class T>
void ArraySort<T>::ShellSort(T* start,T* end, int jump){
    int n = end - start + 1;
    while(jump >= 1){
        int segment = 0;
        while(segment <= jump){
            ArraySort::SortSegment(start,end,segment,jump);
            segment++;
        }
        jump = jump/2;
    }
}
template<class T>
void ArraySort<T>::Merge(T* start,T* mid,T* end){
    int size = end - start + 1;
    int size1 = mid - start + 1;
    int size2 = end - mid;
    int current1 = 0, current2 = 0;
    int current_res = 0;
    T* L1 = new T[size1];
    T* L2 = new T[size2];
    for(int i = 0; i < size1; i++){
        L1[i] = *(start + i);
    }
    for(int i = 0; i < size2; i++){
        L2[i] = *(mid + 1 + i);
    }
    while(size1 > 0 && size2 > 0){
        if(L1[current1] <= L2[current2]){
            *(start+current_res)= L1[current1];
            current_res++;
            current1++;
            size1--;
        }
        else{
            *(start+current_res) = L2[current2];
            current_res++;
            current2++;
            size2--;
        }
    }
    while(size1 > 0){
        *(start+current_res) = L1[current1];
        current_res++;
        current1++;
        size1--;
    }
    while(size2 > 0){
        *(start + current_res) = L2[current2];
        current_res++;
        current2++;
        size2--;
    }
}
template<class T>
void ArraySort<T>::MergeSort(T* start,T* end){
    
    if(end-start<= 0) return;
    T* middle = start + (end-start) / 2;
    ArraySort::MergeSort(start,middle);
    ArraySort::MergeSort(middle + 1,end);
    ArraySort::Merge(start,middle,end);
}
template<class T>
void ArraySort<T>::TimSort(T* start, T* end, int min_size){
    int size = end - start + 1;
    for(int i = 0; i < size; i+= min_size){
        int k = min((i+min_size-1),(size-1));
        ArraySort::ShellSort(start + i,start+k,1);
    }
    for(int temp = min_size;temp < size;temp = temp*2){
        for(int left = 0;left < size;left += 2*temp){
            int mid = left + temp - 1;
            int right = min((left + 2* temp -1),(size - 1));
            if(mid < right){
                ArraySort::Merge(start+left,start+mid,start+right);
            }
        }
    }
}
template<class T>
T* ArraySort<T>::Partition(T* start,T* end){
    int size = end - start + 1;
    T pivot = *start;
    int left = 1;
    int right = size - 1;
    while(right > left){
        while(*(start+right) > pivot && right > left){
            right--;
        }
        while(*(start+left) <= pivot && left < right){
            left++;
        }
        if(left < right){
            ArraySort::swap(start+right,start+left);
            right--;
            left++;
        }
    } 
    if(*(start+right) < pivot){
        ArraySort::swap(start+right,start); 
        return start + right;
        }
    else{
        ArraySort::swap(start+right-1,start);
        return start+right-1;
    }
}
template<class T>
void ArraySort<T>::QuickSort(T* start,T* end){
    if(end- start > 0){
        T* pivot = ArraySort::Partition(start,end);
        ArraySort::QuickSort(start,pivot-1);
        ArraySort::QuickSort(pivot+1,end);
    }
}
template<class T>
void ArraySort<T>::HybridSort(T* start, T* end,int min_size){
   while (start - end < 0) {
        if (end - start < min_size) {
            ArraySort::ShellSort(start, end,1);
            break;
        }
        else {
            T* pivot = Partition(start, end);
            ArraySort::HybridSort(start, pivot-1, min_size);
            start = pivot + 1;
            ArraySort::HybridSort(pivot + 1, end, min_size);
            end = pivot - 1;
        }
    }
}
template<class T>
void ArraySort<T>::HeapSort(T* start, T* end){
    int n = end - start + 1;
    for(int i = (n/2) -1; i >=0; i--){
        ArraySort::Heapify(start,end,i);
    }
    for(int i = n -1; i >= 0; i--){
        ArraySort::swap(start,start + i);
        ArraySort::Heapify(start,start+i-1,0);
    }
}
template<class T>
void ArraySort<T>::Heapify(T* start, T* end,int index){
    int n = end - start + 1;
    int largest = index;
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if(l < n && *(start+l) > *(start+largest)){
        largest = l;
    }
    if(r < n && *(start+r) > *(start+largest)){
        largest = r;
    }
    if(largest != index){
        ArraySort::swap(start+index,start+largest);
        ArraySort::Heapify(start,end,largest);
    }    
}


int main(){
    int N = 100000;
    int* arr = new int[N];
    for(int i  =  0; i < N;i++){
        arr[i] = rand() % 100000001;
    }
    //cout << "Time run QuickSort: " << ArraySort<int>::TestTime(ArraySort<int>::QuickSort,&arr[0],&arr[N-1]) << " s" << endl;
    cout << "Time run TimSort: " << ArraySort<int>::TestTime(ArraySort<int>::TimSort,&arr[0],&arr[N-1],10) << " s" << endl;
    //cout << "Time run ShellSort: " << ArraySort<int>::TestTime(ArraySort<int>::ShellSort,&arr[0],&arr[N-1],N/2) << " s" << endl;
    //cout << "Time run HeapSort: " << ArraySort<int>::TestTime(ArraySort<int>::HeapSort,&arr[0], &arr[N-1]) << " s"<<endl;
    //cout << "Time run HybridSort: " << ArraySort<int>::TestTime(ArraySort<int>::HybridSort,&arr[0],&arr[N-1],10) << " s"<<endl;
    //cout << "Time run MergeSort: " << ArraySort<int>::TestTime(ArraySort<int>::MergeSort,&arr[0],&arr[N-1]) << " s"<<endl;
    return 0;
}
