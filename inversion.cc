const ll p = 1000000007;

ll inv[100003];

ll Inv(int i){

    if(inv[i] != -1)return inv[i];

    return inv[i] = ((((-p/i)+p) % p) * Inv(p%i)) % p;

}

int main(){

    int n;
    scanf("%d", &n);

    inv[1] = 1;

    for(int i=2; i<=n; i++){
        inv[i] = -1;
    }

}
