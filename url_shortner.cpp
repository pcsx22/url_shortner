#include<iostream>
#include<vector>
#include<cstring>
#include<fstream>
#include<cmath>
#include<algorithm>
using namespace std;

vector<pair<string,string> > url_map;
int map_idx = 10000;
int offset = 10000;

char getChar(int x){
	int base = 0;
	if(x < 26){
		return char(97 + x);
	}
	else if(x >= 26 && x < 52){
		return char(65 + x % 26);
	}
	else{
		x -= 52;
		return char(30 + x);
	}
}

int getInt(char x){
	if(x >= 97 && x <= 122)
		return int(x - 97);
	else if(x >= 65 && x <= 90)
		return int(26 + x - 65);
	else if(x >= 48 && x <= 57)
		return int(52 + x - 48);
}

string getShort(string url){
	int tempIdx = map_idx;
	string shortUrl = "";
	while(tempIdx != 0){
		shortUrl += getChar(tempIdx % 62);
		tempIdx /= 62;
	}
	map_idx++;
	reverse(shortUrl.begin(),shortUrl.end());
	return shortUrl;
}

int getUrlIdx(string url){
	int idx = 0;
	int itr = 0;
	string urlHandler(url.begin() + url.find_last_of("/") + 1,url.end());
	reverse(urlHandler.begin(),urlHandler.end());
	for(int i = 0;i<urlHandler.length();i++){
		idx += getInt(urlHandler[i]) * pow(62,i);
	}
	return idx;
}

int main(){
	
	ifstream ifs ("urls.txt");
	string url;
	while(getline(ifs,url)){
		string shortUrl = getShort(url);
		url_map.push_back(pair<string,string>(url,shortUrl));
	}	
	ifs.close();

	for(int i = 0;i<url_map.size();i++){
		cout<<url_map[i].first<<" -> "<<"www.myshorturl.com/"<<url_map[i].second<<endl;
	}
	cout<<"------------------------------"<<endl;

	cout<<"Mapping of www.mySs.com/cNR "<<" -> "<<url_map[getUrlIdx("www.mySs.com/cNR") - offset].first<<endl;
	
	return 0;
}
