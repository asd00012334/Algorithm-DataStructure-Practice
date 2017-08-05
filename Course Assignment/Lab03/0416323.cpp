#include <bits/stdc++.h>
#define byteRange 256
using namespace std;

/// Outline:
/// This is a file compression application based on Huffman Encoding
/// For compression, first write in the array of frequencies of bytes
/// Then build and encode the bytes according to the constructed Huffman Tree
/// For decompression, extract out the frequency array, build the Huffman Tree accordingly
/// Then according to the compressed code and the Huffman Tree, restore the original bytes

struct Node{
    int weight; /// or byte
    Node* left;
    Node* right;
    Node(): weight(0),left(NULL),right(NULL){}
    Node(int weight):weight(weight),left(NULL),right(NULL){}
    Node(int weight, Node* left, Node* right):weight(weight), left(left), right(right){}
    friend void eliminate(Node* head){
        if(head==NULL) return;
        if(head->left) eliminate(head->left);
        if(head->right) eliminate(head->right);
        delete head;
    }

    friend Node* join(Node* left, Node* right){
        return new Node(left->weight+right->weight,left,right);
    }
};

void byteCollect(fstream& fin,vector<unsigned char>& byteCollection){
    while(1){
        int temp=fin.get();
        if(temp==EOF) break;
        byteCollection.push_back(temp);
    }
}

void statistic(vector<unsigned char>& byteCollection, int weight[byteRange]){
    memset(weight,0,byteRange*sizeof(int));
    for(int cnt=0;cnt<byteCollection.size();cnt++)
        weight[byteCollection[cnt]]++;
}

Node* buildHuff(int weight[byteRange]){
    priority_queue<tuple<int,int,Node*> > pQ; ///weight id node
    for(int byte=0;byte<byteRange;byte++){
        pQ.push(
            tuple<int,int,Node*>(
                -weight[byte],
                byte,
                new Node(weight[byte], new Node(byte), NULL)
            )
        );
    }
    while(pQ.size()>1){
        int newId=-1;
        Node* left=get<2>(pQ.top());
        newId=max(newId,get<1>(pQ.top()));
        pQ.pop();
        Node* right=get<2>(pQ.top());
        newId=max(newId,get<1>(pQ.top()));
        pQ.pop();
        Node* root=join(right,left);
        pQ.push(tuple<int,int,Node*>(-root->weight,newId,root));
    }
    return get<2>(pQ.top());
}

void buildByteEncode(unordered_map<unsigned char,string>& byteEncode, Node *head, string& code){
    if(head==NULL) return;
    if(head->right==NULL)
        byteEncode[head->left->weight]=code;
    else{
        buildByteEncode(byteEncode,head->left,code+="0");code.pop_back();
        buildByteEncode(byteEncode,head->right,code+="1");code.pop_back();
    }
}

void writeBuffer(fstream& fout, string& buffer){
    for(int form=0;form<buffer.size();form+=8){
        unsigned char byte=0;
        for(int cnt=0;cnt<8;cnt++)
            if(buffer[form+cnt]=='1')
                byte|=1<<cnt;
        fout.put(byte);
    }
}

void compress(string oldDir, string newDir){
    unordered_map<unsigned char, string> byteEncode;
    fstream oldFile(oldDir,ios::in|ios::binary);
    vector<unsigned char> byteCollection;
    int weight[byteRange];
    string buffer;
    int remain;
    Node* huff;
    byteCollect(oldFile,byteCollection);
    statistic(byteCollection,weight);
    huff=buildHuff(weight);
    buildByteEncode(byteEncode,huff,buffer);
    eliminate(huff);
    for(int cnt=0;cnt<byteCollection.size();cnt++)
        buffer+=byteEncode[byteCollection[cnt]];
    remain=buffer.size()%8;
    buffer.resize(buffer.size()+(remain?(8-remain):0));
    fstream newFile(newDir,ios::out|ios::binary);
    newFile.write((char*)&remain,sizeof(remain));
    newFile.write((char*)&weight,sizeof(weight));
    writeBuffer(newFile,buffer);
    oldFile.close();
    newFile.close();
}

void extract(string oldDir, string newDir){
    fstream oldFile(oldDir,ios::in|ios::binary);
    int remain;
    int weight[byteRange];
    oldFile.read((char*)&remain,sizeof(remain));
    oldFile.read((char*)&weight,sizeof(weight));
    Node* huff=buildHuff(weight);
    string buffer;
    while(1){
        int byte=oldFile.get();
        if(byte==EOF) break;
        for(int cnt=0;cnt<8;cnt++)
            if(byte&(1<<cnt))
                buffer+="1";
            else buffer+="0";
    }
    buffer.resize(buffer.size()-(remain?8-remain:0));
    fstream newFile(newDir,ios::out|ios::binary);
    Node* cur=huff;
    int idx=0;
    while(1){
        if(cur->right==NULL){
            newFile.put((unsigned char)cur->left->weight);
            if(idx>=buffer.size())break;
            cur=huff;
        }
        else{
            if(buffer[idx]=='1')
                cur=cur->right;
            else cur=cur->left;
            idx++;
        }
    }
    eliminate(huff);
    oldFile.close();
    newFile.close();
}

/// Interface:
/// First, input in-line a command index i.e. 1, 2 or 3
/// Then input in-line the relative directory of your target file
/// The output file with extension .huff represent compressed file,
/// The output file with extension .extract represent decompressed file
/// Usually, after compress and decompress, one file may have *.huff.extract
/// Rename *.huff.extract into *, the file will be fully identical

int main(){
    printf("[1]Compress\n[2]Extract\n[3]Quit\n");
    while(1){
        int cmd=-1;
        printf("Your Command:$");
        cin>>cmd;
        while(cin.get()!='\n');
        string file;
        switch(cmd){
        case 1:
            cout<<"Directory:$";
            getline(cin,file);
            compress(file,file+".huff");
            break;
        case 2:
            cout<<"Directory:$";
            getline(cin,file);
            extract(file,file+".extract");
            break;
        case 3:
            return 0;
        default:
            cout<<"Error\n";
            break;
        }
    }
}
