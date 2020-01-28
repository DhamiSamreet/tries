// there are two tries-one storing all the suffixes of input string(for insert,remove1,search1)
//                    -second storing only the input string(for insert1,remove2,search2)  


#include <iostream>
using namespace std;

int lenstr(string a)
{
    int i=0;
    while(a[i]!='\0'){
        i++;
    }
    return i;
}
struct Node
{
    struct Node *left;
    struct Node *right;
    int total;
};
Node *getnode()
{
    struct Node *newnode = new Node();
    newnode->total=0;
    newnode->left=NULL;
    newnode->right=NULL;
    return (newnode);
}





Node* insert1(struct Node *root,char k[33])
{
    struct Node *trie=root;
    int i=0;
    for(i=0;i<lenstr(k);i++){
        if(k[i]=='0'){
            if(trie->left==NULL){
                trie->left= getnode();
            }
            trie=trie->left;
            trie->total=trie->total + 1;
        }
        else{
            if(trie->right==NULL){
                trie->right= getnode();
            }
            trie=trie->right;
            trie->total=trie->total + 1;
        }
    }
    return root;
}
int searchtr2(struct Node *root,char k[33]){
    struct Node *trie =root;
    int i=0;
    while(k[i]!='\0'){
        if(k[i]=='0'){
            if(trie->left==NULL){
                return 0;
            }
            else if(trie->left->total==0){
                return 0;
            }
            trie=trie->left;
        }
        else{
            if(trie->right==NULL){
                return 0;
            }
            else if(trie->right->total==0){
                return 0;
            }
            trie=trie->right;
        }
        i++;
    }
    return 1;
}
Node* insert(struct Node *root,char k[33])
{
    struct Node *trie=root;
    int i,j;
    for(j=0;j<lenstr(k);j++){
        Node *trie=root;
        for(i=j;i<lenstr(k);i++){
            if(k[i]=='0'){
                if(trie->left==NULL){
                    trie->left= getnode();
                }
                trie=trie->left;
                trie->total=trie->total + 1;
            }
            else{
                if(trie->right==NULL){
                    trie->right= getnode();
                }
                trie=trie->right;
                trie->total=trie->total + 1;
            }
        }
    }
    return root;
}





Node *remove2(struct Node *root,char k[33]){
    if(searchtr2(root,k)==0){
        return root;
    }
    else{
        int i=0,j=0;
        struct Node *trie=root;
        for(j=0;j<lenstr(k);j++){
                if(k[j]=='0'){
                    trie=trie->left;
                    trie->total=trie->total - 1;
                }
                if(k[j]=='1'){
                    trie=trie->right;
                    trie->total=trie->total - 1;
                }    
            
       }
       return root;
    }
}
Node *remove1(struct Node *root,char k[33]){ 
        int i=0,j=0;
        struct Node *trie=root;
        for(j=0;j<lenstr(k);j++){
            Node *trie=root;
            for(i=j;i<lenstr(k);i++){
                if(k[i]=='0'){
                    trie=trie->left;
                    trie->total=trie->total - 1;
                }
                if(k[i]=='1'){
                    trie=trie->right;
                    trie->total=trie->total - 1;
                }    
            }
       }
       return root;
    }





int search1(struct Node *root,char k[33])
{
    struct Node *trie = root;
    int i=0;
    while(k[i]!='\0'){
        if(k[i]=='1'){
            if(trie->right==NULL){
                return 0;
            }
            trie=trie->right;
        }
        else{
            if(trie->left==NULL){
                return 0;
            }
            trie=trie->left;
        }
        i++;
    }
    return trie->total;
}

int search2(Node *root,char k[33],int index){
    struct Node *trie=root;
    if(trie==NULL){
        return 0;
    }
    if(k[index]=='\0'){
        return trie->total;
    }
    
    if(k[index]=='?'){
        return search2(trie->left,k,index+1) + search2(trie->right,k,index+1) + trie->total;
    }
    else if(k[index]=='1'){
        return search2(trie->right,k,index+1) + trie->total;
    }
    else if(k[index]=='0'){
        return search2(trie->left,k,index+1) + trie->total;
    }
}





int main(){
    int m,i=0;
    cin >> m;
    struct Node* root =getnode();
    struct Node* root1 =getnode();
    for(i=0;i<m;i++){
        char str[33];
        int t;
        cin >> t;
        cin >> str;
        if(t==1){
            root1=insert1(root1,str);
            root=insert(root,str);
        }
        else if(t==2){
            if(searchtr2(root1,str)==1){
                root1=remove2(root1,str);
                root=remove1(root,str);
            }
        }
        else if(t==3){
            cout << search1(root,str) <<endl;
        }
        else{
            cout << search2(root1,str,0) << endl;
        }
    }
}