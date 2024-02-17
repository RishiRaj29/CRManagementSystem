#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <regex>
#include <algorithm>
#include <ctype.h>

using namespace std;

string commandArg1,commandArg2,buildingName,floorName,confName,time;
int startTime,endTime;

vector<string> buildings;

map<string,vector<string>> buildingFloors;

map<pair<string,string>,vector<string>> confRooms;

void printStructure()
{
    for(auto it:confRooms)
    {
        cout<<"Building Name "<<it.first.first<<" Floor Name "<<it.first.second<<"\n";
        cout<<"The Conference rooms are - \n";
        for(auto i:it.second)
        {
            cout<<i<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

string toLowerCase(string name)
{
    string ans="";
    for(int i=0;i<name.length();i++)
    {
        if(name[i]>='A' and name[i]<='Z')
            ans+=(char)tolower(name[i]);
        else
            ans+=name[i];
    }
    return ans;
}

bool buildingExistence(string buildingName)
{
    for(int i=0;i<buildings.size();i++)
    {
        if(buildings[i]==buildingName)
            return true;
    }
    return false;
}

bool floorExistence(string buildingName,string floorName)
{
    for(int i=0;i<buildingFloors[buildingName].size();i++)
    {
        if(buildingFloors[buildingName][i]==floorName)
            return true;
    }
    return false;
}

bool confExistence(string buildingName,string floorName,string confName)
{
    for(int i=0;i<confRooms[make_pair(buildingName,floorName)].size();i++)
    {
        if(confRooms[make_pair(buildingName,floorName)][i]==confName)
            return true;
    }
    return false;
}

void addBuilding(string buildingName)
{
    buildingName=toLowerCase(buildingName);
    if(buildingExistence(buildingName))
    {
        cout<<"The Building already Exists!\n";
        return;
    }
    buildings.push_back(buildingName);
    cout<<"The Building has been added to our System!\n";
}

void addFloorToBuilding(string buildingName,string floorName)
{
    buildingName=toLowerCase(buildingName);
    floorName=toLowerCase(floorName);
    if(buildingExistence(buildingName))
    {
        if(floorExistence(buildingName,floorName))
        {
            cout<<"The Floor already Exists in the building mentioned!\n";
            return;
        }
        buildingFloors[buildingName].push_back(floorName);
        cout<<"The Floor has been added to the building in our System!\n";
    }
    else
    {
        cout<<"This building does not exist in our records!\n";
        return;
    }
}

void addConf(string buildingName,string floorName,string confName)
{
    buildingName=toLowerCase(buildingName);
    floorName=toLowerCase(floorName);
    confName=toLowerCase(confName);
    if(buildingExistence(buildingName))
    {
        if(floorExistence(buildingName,floorName))
        {
            if(confExistence(buildingName,floorName,confName))
            {
                cout<<"The ConfRoom already Exists for the floor in the building mentioned!\n";
                return;
            }
            confRooms[make_pair(buildingName,floorName)].push_back(confName);
            cout<<"The conference room has been added!\n";
        }
        else
        {
            cout<<"This Floor for given building does not exist in our records!\n";
            return;
        }
    }
    else
    {
        cout<<"This building does not exist in our records!\n";
        return;
    }
}

vector<int> split(string time, char del)
{
    string temp="";
    vector<int> ans;
    for(int i=0;i<(int)time.size();i++)
    {
        if(time[i]!=del)
        {
            temp+=time[i];
        }
        else
        {
            int t=stoi(temp);
            ans.push_back(t);
        }
    } 
    return ans;
}

void bookSlot(string buildingName,string floorName,string confName,string time)
{
    vector<int>interval=split(time,':');
    startTime=interval[0];
    endTime=interval[1];
    buildingName=toLowerCase(buildingName);
    floorName=toLowerCase(floorName);
    confName=toLowerCase(confName);
}

int main()
{
    cout<<"********Conference Room Reservation System*********\n";
    while(1)
    {
        cin>>commandArg1;
        if(commandArg1=="ADD")
        {
            cin>>commandArg2;
            if(commandArg2=="BUILDING")
            {
                cin>>buildingName;
                addBuilding(buildingName);
            }
            else if(commandArg2=="FLOOR")
            {
                cin>>buildingName>>floorName;
                addFloorToBuilding(buildingName,floorName);
            }
            else if(commandArg2=="CONFROOM")
            {
                cin>>buildingName>>floorName>>confName;
                addConf(buildingName,floorName,confName);
            }
        }
        else if(commandArg1=="BOOK")
        {
            cin>>time>>buildingName>>floorName>>confName;
            bookSlot(buildingName,floorName,confName,time);
        }
        else if(commandArg1=="EXIT")
        {
            cout<<"Thank You! \n";
            break;
        }
    }
    cout<<"The current building structure is as follows - \n";
    printStructure();
    return 0;
}