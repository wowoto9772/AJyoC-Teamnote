#include <bits/stdc++.h>
using namespace std;
 
#define MAXM 100005
#define MAXL 300005
 
char S[MAXL], buf[MAXL];
 
struct NODE{
    NODE (): is_end(0), count(0), f(0), o(0){ for (int i=0;i<26;i++) nxt[i] = 0; }
    bool is_end; int count;
    NODE *nxt[26], *f, *o;
    // f = 실패 링크, o = 출력 링크
} *root;
NODE *my_end_node[MAXM];
 
void dfs(NODE *now)
{
    for (int i=0;i<26;i++) if (now->nxt[i]) dfs(now->nxt[i]);
    if (now->is_end && now->f->o) now->f->o->count += now->count;
}
 
int main()
{
 
    int M;
    scanf("%d", &M);
 
    // 입력과 동시에 Trie 구성
    root = new NODE();
    for (int i=1; i<=M; i++){
        scanf("%s", buf+1); int n = strlen(buf+1);
        NODE *now = root;
        for (int j=1; j<=n; j++){
            int c = buf[j] - 'a';
            if (!now->nxt[c]) now->nxt[c] = new NODE();
            now = now->nxt[c];
        }
        now->is_end = 1;
        my_end_node[i] = now;
    }
 
    // BFS를 통해 실패 링크와 출력 링크를 계산
    queue <NODE*> que;
    for (int i=0; i<26; i++) if (root->nxt[i]){
        root->nxt[i]->f = root;
        que.push(root->nxt[i]);
    }
 
    while (!que.empty()){
        NODE *q = que.front(); que.pop();
        if (q->is_end) q->o = q;
        else q->o = q->f->o;
        for (int i=0; i<26; i++) if (q->nxt[i]){
            NODE *t = q->nxt[i];
            t->f = q->f;
            while (t->f != root && !t->f->nxt[i]) t->f = t->f->f;
            if (t->f->nxt[i]) t->f = t->f->nxt[i];
            que.push(t);
        }
    }
 
    // 문자열 S에서 패턴 검색
    NODE *now = root;
 
    int N;
    scanf("%d", &N);
 
    while(N--){
 
        scanf("%s", S+1);
        int L = strlen(S+1);
 
        bool flag = false;
 
        for (int i=1; i<=L; i++){
            int c = S[i] - 'a';
            while (now != root && !now->nxt[c]) now = now->f;
            if (now->nxt[c]) now = now->nxt[c];
            if (now->o){
 
                flag = true;
                printf("YES\n");
                break;
 
            }
        }
 
        if(!flag)printf("NO\n");
 
    }
 
}
