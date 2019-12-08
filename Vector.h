//
//  Vector.h
//  Project_2
//
//  Created by abdullah on 04/12/2019.
//  Copyright © 2019 Momin Salar. All rights reserved.
//

#ifndef Vector_h
#define Vector_h
template<typename T>
class Vector{
    //Data Members and some functions
    T *arr;
    int cs;
    int maxSize;
public:
    Vector<T>(int defaultSize=4){
        maxSize = defaultSize;
        cs = 0;
        arr = new T[maxSize];
    }
    
    
    
//    void operator()(string s)
//    {
//        cout<<s<<" is an awesome place";
//    }
//
    T & operator[](const int i)
    {
        if (i<maxSize && i>size())
            cs = i;
       return arr[i];
    }
//    bool operator==(T & vec)
//    {
//        for (int i = 0; i<size(); i++){
//            if (arr[i]==vec)
//                return true;
//        }
//        return false;
//    }
//
//    bool operator!=(T & vec){
//        if (*this==vec){
//            return false;
//        }
//        return true;
//    }
    
    Vector<T> & operator=(Vector<T> & vec)
    {
        cs = vec.size();
        maxSize = vec.maxSize;
        arr = new T[maxSize];
        for (int i=0; i<size(); i++){
            arr[i] = vec[i];
        }
        return *this;
    }
    
    void operator = (T & data ){
        arr[cs] = data;
        cs++;
    }
//    Vector<T>(Vector<T>& vec){
//        *this = vec;
//    }
    void push_back(T & data){
        if(cs==maxSize){
            //Doubling Operations
            T *oldArr = arr;
            arr = new T[2*maxSize];
            maxSize = 2*maxSize;
            for(int i=0;i<cs;i++){
                arr[i] = oldArr[i];
            }
            //Delete the oldArr
            //delete [] oldArr;
        }
        arr[cs] = data;
        cs++;
    }
    bool empty(){
        return cs==0;
    }
    int size(){
        return cs;
    }
    int getMaxSize(){
        return maxSize;
    }
    void pop_back(){
        if(!empty()){
            cs--;
        }
    }
    void print(){
        for(int i=0;i<cs;i++){
            if (i<cs-1)
                cout<<arr[i]<<"->";
            else
                cout<<arr[i];
        }
    }
    int at(int i){
        return arr[i];
    }
};

#endif /* Vector_h */
