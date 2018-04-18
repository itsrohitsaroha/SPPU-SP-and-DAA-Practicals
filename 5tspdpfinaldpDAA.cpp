#include<bits/stdc++.h>
using namespace std;
void print(int n,map<pair<int ,pair<vector<int >, int > >, int >dp)
{
    cout<<"\n";
    for(int i=0;i<=n-1;i++)
    {
        for(map<pair<int ,pair<vector<int >, int > >, int > :: iterator itr = dp.begin(); itr != dp.end(); itr++)
        {
            if(itr -> first.second.first.size() == i /*&& itr -> second != INT_MAX*/)
            {
                cout<<"Cost of f(";
                cout<<itr->first.first<<" ( ";
                for(int j=0; j < itr -> first.second.first.size(); j++)
                    cout<<itr -> first.second.first[j]<<" ";
                cout<<") ";
                cout<<itr -> first.second.second<<" ) = "<<itr -> second<<"\n ";//<<path[{itr->first.first, {itr->first.second.first, 1}}]<<"\n";
            }
        }
        cout<<"\n";
    }
}
int TSP(int a, vector<int >v, int **cost, map<pair<int ,pair<vector<int >, int > >, int > &dp, map<pair<int ,pair<vector<int >, int > >, int > &path)
{
    if(dp[{a, {v, 0}}])
        return dp[{a, {v, 0}}];
    else
        dp[{a, {v, 0}}] = INT_MAX;
    if(v.size() == 0)
    {
        dp[{a, {v, 0}}] = cost[a][0];
        return dp[{a, {v, 0}}];
    }
    else
    {
        for(int i=0; i<v.size(); i++)
        {
            if(cost[a][v[i]]!=INT_MAX)
            {
                vector<int >v2;
                for(int j=0; j<v.size(); j++)
                {
                    if(i != j)
                    {
                        v2.push_back(v[j]);
                    }
                }
                int rec = TSP(v[i], v2, cost, dp, path);
                if(rec != INT_MAX)
                {
                    int ans = cost[a][v[i]] + rec;
                    if(dp[{a, {v, 0}}] > ans)
                    {
                        path[{a, {v, 0}}] = i;
                        cout<<a<<" "<<v[i]<<"\n";
                        dp[{a, {v, 0}}] = ans;
                    }

                }
            }
        }
        return dp[{a, {v, 0}}];
    }
}
main()
{
    int n, i, j;
    int **cost;
    map<pair<int ,pair<vector<int >, int > >, int >dp, path;
	//cout<<"\n Enter the number of vertices : ";
    cin>>n;
    cost = (int **)malloc(sizeof(int ) * (n ));
    for(int i=0; i<n; i++)
    {
        cost[i] = (int *)malloc(sizeof(int ) * (n));
    }
    vector<int >v;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            cost[i][j] = INT_MAX;
        }
    }
    int edges;
	//cout<<"\n Enter the number of edges : ";
    cin>>edges;
    for(int i=0; i<edges; i++)
    {
        int x, y, z;
        cin>>x>>y>>z;    // x=starting y=ending z=cost 
        cost[x][y] = z;
    }
    for(i=1; i<n; i++)
    {
        v.push_back(i);
    }
    cout<<"\n";
    int cost1 = TSP(0, v, cost, dp, path);
    if(cost1 == INT_MAX)
    {
        cout<<"There is no path\n";
        return 0;
    }
    print(n, dp);
    cout<<"\n";
    cout<<"path is ";
    cout<<"0 -> ";
    int a = path[{0, {v, 0}}];
    while(v.size())
    {
        int p =v[a];
        cout<<p<<" -> ";
        v.erase(v.begin() + a);
        a = path[{p, {v, 0}}];
    }
    cout<<"0";
    cout<<"\ncost is "<<cost1;

 cout<<"---------------------------------------------------------------------------------------------------------";
	for(map<pair<int ,pair<vector<int >, int > >, int > :: iterator itr = dp.begin(); itr != dp.end(); itr++)
        {
		
		
            if(itr -> first.second.first.size() == i /*&& itr -> second != INT_MAX*/)
            {
                cout<<"Cost of f(";
                cout<<itr->first.first<<" ( ";
                for(int j=0; j < itr -> first.second.first.size(); j++)
                    cout<<itr -> first.second.first[j]<<" ";
                cout<<") ";
                cout<<itr -> first.second.second<<" ) = "<<itr -> second<<"\n "<<path[{itr->first.first, {itr->first.second.first, 1}}]<<"\n";
            }
        }  	

}

/*
0 24 11 10 9
8 0 2 5 11
26 12 0 8 7
11 23 24 0 6
5 4 8 11 0

0 0 15 20
5 0 9 10
6 13 0 12
8 8 9 0
ans = 40

0 10 15 20
5 0 9 10
6 13 0 12
8 8 9 0
ans = 35

has[v[i]][v[j]]\

0 2 6
2 0 0
0 5 0

0 2 6
0 0 0
0 5 0
3
3
0 1 1
1 2 2
2 1 3

3
4
0 1 2
0 2 6
1 0 2
2 1 5
*/
