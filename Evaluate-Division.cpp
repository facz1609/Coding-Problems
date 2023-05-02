#include <bits/stdc++.h>
using namespace std;

//create a dfs function
void dfs(unordered_map<string , vector<pair<string , double>>>&m ,set<string>&vis , string &src , string &dest , double &ans , double temp){
    if(vis.find(src)!=vis.end()){
        return;
    }
    else{
        vis.insert(src);
        if(src==dest){
            ans=temp;
            return;
        }
        else{
            for(auto child : m[src]){
            dfs(m , vis , child.first,dest,ans , child.second*temp);
            }
        }
    }

}
vector<double> evaluateEquations(vector<pair<string, string>> &equations, vector<pair<string, string>> &queries, vector<double> &values) {
    // create a graph
    int n= values.size();
    unordered_map<string , vector<pair<string , double>>>m;

    // initialize the graph
    for(int i=0;i<n;i++){
        string src= equations[i].first;
        string dest= equations[i].second;
        m[src].push_back({dest , values[i]});
        m[dest].push_back({src , 1/values[i]});
    }
    //create a vector fans 
    vector<double>fans;

    // loop for queries
    double ans=-1;
    for(int i=0;i<queries.size();i++){
        string src=queries[i].first;
        string dest = queries[i].second;

        // if src or dest is not present in graph the ans= -1
        if(m.find(src)==m.end() or m.find(dest)==m.end()){
            ans=-1;
            fans.push_back(ans);
            continue;
        }
        ans=-1;
        //make a visited set
        set<string>vis;

        //call the dfs function for the src and dest for each query
        dfs(m , vis , src , dest , ans , 1.0);
        fans.push_back(ans);
    }
    return fans;
}

