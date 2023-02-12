//Bismillah

#include<bits/stdc++.h>
using namespace std;

#define optimize() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define ll long long
#define int long long

int N, x, K;
vector<int> ar;
vector<vector<int>> maxTable, minTable;
int max(int A, int B) {return (A >= B) ? A : B;}
int min(int A, int B) {return (A <= B) ? A : B;}


void buildSparseTable()
{
	for (int i = 0; i < N; i++) {
		maxTable[i][0] = ar[i];
		minTable[i][0] = ar[i];
	}
	for (int j = 1; j <= x; j++) {
		for (int i = 0; i + (1 << j) <= N; i++) {
			maxTable[i][j] = max(maxTable[i][j - 1], maxTable[i + (1 << (j - 1))][j - 1]);
			minTable[i][j] = min(minTable[i][j - 1], minTable[i + (1 << (j - 1))][j - 1]);
		}
	}
}

int query(int l,int r)
{
    int len=(r-l+1);
    //int k=log2(len);
    int p=log2(len);
    int mnValue=min(minTable[l][p],minTable[r+1-(1<<p)][p]);
    int mxValue=max(maxTable[l][p],maxTable[r+1-(1<<p)][p]);
    return mxValue-mnValue;
}

ll binSearch(int l,int r,int k)
{
    int mid,ret;
    while(r>(l+1)){
        mid=(l+r)/2;
        ret=query(l,mid);
        (ret<=k)? l=mid : r=mid;
    }
    return l;
}


signed main()
{

	cin >> N >> K;
	ar.resize(N);

    for(int i=0;i<N;i++)   cin>>ar[i];
	x = ceil(log2(N)) + 1;
	maxTable.resize(N, vector<int>(x + 1, 0));
	minTable.resize(N, vector<int>(x + 1, 0));

    buildSparseTable();

    ll ans=0;
    for(int i=0;i<N;i++){
        ll ret=binSearch(i,N,K);
        ans+=(ret-i+1);
    }

    cout<<ans<<endl;
    return 0;
}

