#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <utility>
using namespace std;

void processing(vector<pair<int,int>> remaining,int target,
	int limit,int stage,string array,int sum,int level);
void kpartition(vector<pair<int,int>> array,int avg,int limit);
void Compare();
void Print();
class Memory{
public:
	vector<vector<int>> combination;
	vector<pair<int,int>> array;
	vector<vector<int>> player;
};
Memory M;
int main(){
	int NumberofTreasure=0;
	int capacity=0;
	int value=0;
	int sum=0;
	int avg=0;
	M.combination.clear();
	M.array.clear();
	M.player.clear();
	vector<pair<int,int>> array;
	array.clear();
	cout<< "Please enter the number of treasure: ";
	cin>> NumberofTreasure;
	if(NumberofTreasure<0){
		cout<< "Number of Treasure less than 0\n";
		return 0;
	}
	cout<< "Please enter the size of backpack: ";
	cin>> capacity;
	if(capacity<=0){
		cout<< "The size of backpack less than or equal to 0\n";
		return 0;
	}
	for(int i=0;i<NumberofTreasure;i++){
		cout<<"treasure " << i << ": ";
		cin>> value;
		if(value==-1){
			cout<< "The value of this Treasure is -1\n";
			return 0;
		}
		array.push_back(make_pair(value,i));
	}
	for(int i=0;i<array.size();i++){
		sum=sum+array[i].first;
	}
	cout<< "sum: " << sum <<endl;
	if(sum%3!=0){
		cout<< "No!\n";
		return 0;
	}
	avg=sum/3;
	cout<< "avg:" <<avg<< endl;
	sort(array.begin(),array.end());
	M.array.assign(array.begin(),array.end());
	kpartition(array,avg,capacity);
	Compare();
	Print();
	return 0;
}
void kpartition(vector<pair<int,int>> array,int avg,int limit){
	vector<pair<int,int>> erasefirst;
	erasefirst.clear();
	string include="1";
	string exclude="0";
	erasefirst.assign(array.begin()+1,array.end());
	processing(erasefirst,avg,limit,0,exclude,0,1);
	processing(erasefirst,avg,limit,1,include,array[0].first,1);
	return;
}
void processing(vector<pair<int,int>> remaining,int target,
	int limit,int stage,string array,int sum,int level){
	if(sum==target){
		vector<int> myNumbers;
		myNumbers.clear();
		for(int i=0;i<(M.array.size()-level);i++){
			array=array+"0";
		}
		for(int i=0;i<array.size();i++){
			myNumbers.push_back(array[i]-'0');
		}
		M.combination.push_back(myNumbers);
		return;
	}else if(stage>=limit){
		return;
	}else if(remaining.size()==0){
		return;
	}else{
		vector<pair<int,int>> erasefirst;
		erasefirst.clear();
		erasefirst.assign(remaining.begin()+1,remaining.end());
		processing(erasefirst,target,limit,stage+1,
			array+"1",sum+remaining[0].first,level+1);
		processing(erasefirst,target,limit,stage,array+"0",sum,level+1);
		return;
	}
}
void Compare(){
	for(int i=0;i<M.combination.size();i++){
		for(int j=0;j<M.combination.size();j++){
			int error=0;
			for(int w=0;w<M.combination[i].size();w++){
					error=error+
					((M.combination[i][w]+M.combination[j][w])==2);
				}
			if(error==0&&i!=j){
				for(int k=0;k<M.combination.size();k++){
					int error1=0;
					for(int v=0;v<M.combination[k].size();v++){
						error1=error1+
							((M.combination[i][v]+M.combination[j][v]+M.combination[k][v])!=1);
					}
					if(error1==0){
						//out << "find!" << "i:" << i << "j:" << j << "k:" << k << endl;
						M.player.push_back(M.combination[i]);
						M.player.push_back(M.combination[j]);
						M.player.push_back(M.combination[k]);
						return;
					}
				}
			}
		}
	}
	cout<< "No!\n";
	return;
}
void Print(){
	for(int i=0;i<3;i++){
		cout<< "player" << i << ":";
		for(int j=0;j<M.player[i].size();j++){
			if(M.player[i][j]==1)
				cout<< " " << M.array[j].second;
		}
		cout<< endl;
	}
	return;
}