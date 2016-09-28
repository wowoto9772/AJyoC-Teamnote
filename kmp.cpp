#include <stdio.h>

#include <string.h>

#include <string>
#include <vector>

using namespace std;

#define LEN 1000003

char org[LEN], ptn[LEN];
int pi[LEN];
int pl, ol;

// 1 base only

void getPi(){

	int p = 0;

	pi[1] = 0;

	for(int i=2; i<=pl; i++){

		while(p && (ptn[p+1] != ptn[i]))p = pi[p];
		if(ptn[p+1] == ptn[i])p++;
		pi[i] = p;

	}

}

// count ptn in org

int getAns(){

	int ret = 0;

	int p = 0;

	for(int i=1; i<=ol; i++){

		while(p && (ptn[p+1] != org[i]))p = pi[p];
		if(ptn[p+1] == org[i])p++;
		if(p == pl){
			// find !
			p = pi[p];
			ret++;
		}

	}

	return ret;

}

int main(){

	scanf("%s", ptn+1);
	pl = strlen(ptn+1);

	getPi();

	scanf("%s", org);
	ol = strlen(org);

	printf("%d\n", getAns());

}
