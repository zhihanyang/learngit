#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N=100001;

int last,cnt;
unsigned long long ans;
struct node{
    int len;
    int ch[26];
    int fa;
    int size;
}SAM[N<<1];

void insert(int c){
    int p=last;
    int np=++cnt;SAM[np].len=SAM[p].len+1;
    SAM[np].size=1;
    for (; p&&!SAM[p].ch[c] ; p=SAM[p].fa)
        SAM[p].ch[c]=np;
    last=np;
    if(!p)SAM[np].fa=1;
    else{
        int q=SAM[p].ch[c];
        if(SAM[q].len==SAM[p].len+1)SAM[np].fa=q;
        else{
            int nq=++cnt;
            memcpy(SAM[nq].ch,SAM[q].ch,sizeof(SAM[q].ch));
            SAM[nq].len=SAM[p].len+1;SAM[nq].size=0;SAM[nq].fa=SAM[q].fa;
            for (;SAM[p].ch[c]==q ; p=SAM[p].fa)
                SAM[p].ch[c]=nq;
            SAM[np].fa=SAM[q].fa=nq;
        }
    }
}

int main() {
    char in[N]={};
    scanf("%s",in);
    int n=strlen(in);
    last=cnt=1;
    for (int i = 0; i < n ; ++i) {
        insert(in[i]-'a');
    }
    int c[cnt+1]={},a[cnt+1]={};
    for (int i = 1; i <=cnt ; ++i) ++c[SAM[i].len];
    for (int i = 1; i <=cnt ; ++i) c[i]+=c[i-1];
    for (int i = 1; i <=cnt ; ++i) a[c[SAM[i].len]--]=i;
    for (int i = cnt;i; --i) {
        int p=a[i];
        SAM[SAM[p].fa].size+=SAM[p].size;
        if(SAM[p].size>1)ans=max(ans,((unsigned long long)SAM[p].size)*SAM[p].len);
    }
    printf("%lld\n",ans);
    return 0;
}