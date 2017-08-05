#include<iostream>
#include<cstdio>
#define INIT_CAP 3

using namespace std;

class String{
    char* str;
    size_t len;
    size_t capacity;
public:
    String():str(new char[INIT_CAP]),len(0),capacity(INIT_CAP){str[0]='\0';}
    String(String const& init):len(init.len),capacity(init.capacity){
        str = new char[capacity];
        for(int cnt=0;cnt<len;cnt++)
            str[cnt]=init.str[cnt];
        str[len]='\0';
    }

    String(char const* c_str){
        int size=0;
        while(c_str[size]!='\0')
            ++size;
        resize(size);
        for(int cnt=0;cnt<size;cnt++)
            str[cnt]=c_str[cnt];
        str[size]='\0';
    }

    ~String(){
        delete[] str;
    }

    char& front(){
        if(!len) throw exception();
        return str[0];
    }

    char& front()const{
        if(!len) throw exception();
        return str[0];
    }

    char& back(){
        if(!len) throw exception();
        return str[len-1];
    }

    char& back()const{
        if(!len) throw exception();
        return str[len-1];
    }

    void push_back(char element){
        if(len+1>=capacity/2){
            capacity = (len+1)*4+1;
            char* temp = new char[capacity];
            for(int cnt=0;cnt<len;cnt++)
                temp[cnt]=str[cnt];
            delete[] str;
            str=temp;
        }
        str[len++]=element;
        str[len]='\0';
    }

    void pop_back(){
        if(!len) throw exception();
        if(len-1<capacity/4){
            capacity = (len-1)*2+1;
            char* temp = new char[capacity];
            for(int cnt=0;cnt<len-1;cnt++)
                temp[cnt]=str[cnt];
            delete[] str;
            str=temp;
        }
        str[--len]='\0';
    }

    void resize(int newSize){
        if(newSize<0) throw exception();
        if(newSize>=capacity/2 || newSize<capacity/4){
            char* temp = new char[capacity=newSize*3+1];
            for(int cnt=0;cnt<newSize;cnt++)
                temp[cnt]=str[cnt];
            delete[] str;
            str=temp;
        }
        str[len=newSize]='\0';
    }

    char& operator[](int term){
        return str[term];
    }

    char& operator[](int term)const{
        return str[term];
    }

    String& operator=(String const& right){
        len = right.len;
        capacity = right.capacity;
        delete[] str;
        str = new char[capacity];
        for(int cnt=0;cnt<=len;cnt++)
            str[cnt] = right.str[cnt];
    }

    friend String operator+(String const& left, String const& right){
        String out;
        out.resize(left.len+right.len);
        for(int cnt=0;cnt<left.len;cnt++)
            out.str[cnt]=left.str[cnt];
        for(int cnt=left.len;cnt<out.len;cnt++)
            out.str[cnt]=right.str[cnt];
        out.str[out.len]='\0';
        return out;
    }

    String& operator+=(String const& right){
        String& left = *this;
        size_t origSize = left.len;
        left.resize(left.len+right.len);
        for(int cnt=origSize;cnt<left.len;cnt++)
            left.str[cnt]=right.str[cnt];
        left.str[left.len]='\0';
        return left;
    }

    void swap(String& toSwap){
        std::swap(len,toSwap.len);
        std::swap(capacity,toSwap.capacity);
        std::swap(str,toSwap.str);
    }

    inline friend ostream& operator<<(ostream& out, String const& right){
        return out<<right.str;
    }

    friend istream& operator>>(istream& in, String& right){
        int temp;
        while(1){
            temp=in.get();
            if(temp==' '||temp=='\n'||temp==EOF||temp=='\0') break;
            right.push_back(temp);
        }

        return in;
    }

    friend int getline(istream& in, String& str){
        int temp;
        str.resize(0);
        while(1){
            temp=in.get();
            if(temp==EOF||temp=='\n') break;
            str.push_back(temp);
        }
        return temp;
    }

    friend int getfile(istream& in, String& str){
        int temp;
        str.resize(0);
        while(1){
            temp=in.get();
            if(temp==EOF) break;
            str.push_back(temp);
        }
        return temp;
    }

    friend bool operator==(String const& left, String const& right){
        if(left.len!=right.len) return false;
        for(int cnt=0;cnt<left.len;cnt++)
            if(left.str[cnt]!=right.str[cnt])
                return false;
        return true;
    }

    friend bool operator!=(String const& left, String const& right){
        if(left.len!=right.len) return true;
        for(int cnt=0;cnt<left.len;cnt++)
            if(left.str[cnt]!=right.str[cnt])
                return true;
        return false;
    }

    size_t size()const{
        return len;
    }

    String slice(size_t left, size_t right)const{
        String output;
        if(left>right) return output;
        output.resize(right-left+1);
        for(int cnt=left;cnt<=right&&cnt<len;cnt++)
            output.str[cnt-left]=str[cnt];
        return output;
    }

    size_t find(String const& pat)const{
        /// Brute Force
        int match=0;
        int left=0;
        while(left+pat.len<=len&&match<pat.len){
            if(str[left+match]==pat.str[match])
                ++match;
            else{
                match=0;
                ++left;
            }
        }
        return match==pat.len?left:-1;
    }

    const char* c_str(){return str;}
};
