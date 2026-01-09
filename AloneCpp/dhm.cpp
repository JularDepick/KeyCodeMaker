/* 兑换码生成
* 命令行参数说明:
  -n 表示下一个参数是生成的兑换码个数
  -l 表示下一个参数是生成的兑换码长度
  -f 表示输出到文件(dhm-output-latest.txt)
  -all 表示组成兑换码的字符集切换为[0-9A-Z]
  -num 表示组成兑换码的字符集切换为[0-9]
  -abc 表示组成兑换码的字符集切换为[A-Z]
  -hex 表示组成兑换码的字符集切换为[0-9A-F]即十六进制
*
*/

#include<bits/stdc++.h>
#include<windows.h>
#include<time.h>
using namespace std;

int BASEN=36;
string base="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string modestr[4]={"-all","-num","-abc","-hex"};

bool is_num(string s) {
	if(s[0]=='-') {
		reverse(s.begin(),s.end());
		s.pop_back();
		reverse(s.begin(),s.end());
	}
	if(s.empty()) {
		return 0;
	}
    for(char c:s) {
    	if(c<'0' || '9'<c) {
    		return 0;
		}
	}
	if(s=="0") {
		return 1;
	}
	return (s[0]!='0');
}

long long intFstr(string s) {
	//must is_num(s)==1
	bool neg=(s[0]=='-');
	if(neg) {
		reverse(s.begin(),s.end());
		s.pop_back();
		reverse(s.begin(),s.end());
	}
	long long n=0;
	for(char c:s) {
		n+=(c-'0');
		n*=10;
	}
	n/=10;
	return ((neg? -1:1)*n);
}

string intTstr(long long n) {
	if(n==0) {
		return "0";
	}
	bool neg=0;
	if(n<0) {
		n*=-1;
		if(n<0) {
			return "";
		}
		neg=1;
	}
	string s="";
	while(n) {
		s.push_back(n%10+'0');
		n/=10;
	}
	reverse(s.begin(),s.end());
	if(neg) {
		s=("-"+s);
	}
	return s;
}

string secTstr(long long t) {
	if(t<0) {
		return "";
	}
	int s=t%60;
	t/=60;
	int m=t%60;
	int h=t/60;
	string res="";
	if(h<10) {
		res="0";
	}
	res+=intTstr(h);
	res+=":";
	if(m<10) {
		res+="0";
	}
	res+=intTstr(m);
	res+=":";
	if(s<10) {
		res+="0";
	}
	res+=intTstr(s);
	return res;
}

int n=1,l=16;
int mode=0;
bool bn=1,bl=1,bf=1,bm=1;

int main(int argc,char* argv[]) {
	if(argc>=1) {
	for(int i=1;i<argc && (bn||bl||bf||bm);i++) {
		string pos=argv[i];
		if(pos[0]=='-') {
			if(pos=="-n" && bn) {
				if(i>=argc-1) {
					cout<<"MISS ARGUMENT AFTER OPTION -n !"<<endl;
					return 0;
				}
				if(is_num(argv[i+1])) {
					int an=intFstr(argv[i+1]);
					if(an<=0) {
						cout<<"ERROR ARGUMENT AFTER OPTION -n : "<<argv[i+1]<<" NOT POSITIVE!"<<endl;
						return 0;
					}
					n=an;
					bn=0;
					i++;
				} else {
                    cout<<"ERROR ARGUMENT AFTER OPTION -n : "<<argv[i+1]<<" NOT NUMBER!"<<endl;
                    return 0;
				}
			}
			if(pos=="-l" && bl) {
				if(i>=argc-1) {
					cout<<"MISS ARGUMENT AFTER OPTION -l !"<<endl;
					return 0;
				}
				if(is_num(argv[i+1])) {
					int an=intFstr(argv[i+1]);
					if(an<=0) {
						cout<<"ERROR ARGUMENT AFTER OPTION -l : "<<argv[i+1]<<" !"<<endl;
						return 0;
					}
					l=an;
					bl=0;
					i++;
				} else {
                    cout<<"ERROR ARGUMENT AFTER OPTION -l : "<<argv[i+1]<<" NOT NUMBER!"<<endl;
                    return 0;
				}
			}
			if(pos=="-f" && bf) {
				bf=0;
			}
			if(pos=="-num" && bm) {
				bm=0;
				mode=1;
			}
			if(pos=="-abc" && bm) {
				bm=0;
				mode=2;
			}
			if(pos=="-hex" && bm) {
				bm=0;
				mode=3;
			}
		} else {
			cout<<"ERROR OPTION OR ARGUMENT: "<<pos<<" !"<<endl;
			return 0;
		}
	}
	if(mode==1) {
		base="0123456789";
		BASEN=10;
	} else if(mode==2) {
		base="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		BASEN=26;
	} else if(mode==3) {
		base="0123456789ABCDEF";
		BASEN=16;
	}
}
	long long cnt=0,i=0;
	map<string,bool> hadmaken={};
	ofstream fout;
	if(!bf) {
		fout.open("dhm-output-latest.txt",ios::out);
	}
	int begintime=time(0);
	int begintime_base=begintime;
	int lastshowcharn=-1;
	while(cnt<n) {
		long tseed=time(0);
		string code="";
		long long len=0;
		while(len<l) {
			srand(1.0*(i+1)/(len+1)*tseed+i+len+tseed+cnt+BASEN+len*i+len*GetTickCount());
			code.push_back(base[rand()%BASEN]);
			len++;
		}
		i++;
		if(time(0)-begintime>1.5) {
			cout<<"\nERROR: OVERFLOW TIME LIMIT! BECAUSE YOUR ARGUMENT AFTER -n IS TOO LARGE OR ARGUMENT AFTER -l IS TOO SMALL!"<<endl<<"WARN: WE HAD MAKEN "<<cnt<<" CODES, THEN PAUSE WITH ERROR!"<<endl;
			return 0;
		}
		if(hadmaken.count(code)) {
			continue;
		}
		hadmaken[code]=1;
		begintime=time(0);
		if(!bf) {
			fout<<code<<endl;
			int showcharn=(1.0*cnt/n*40);
			if(lastshowcharn!=showcharn) {
				for(int j=0;j<51;j++) {
					cout<<'\b';
				}
				cout<<"RUNNING: [";
				for(int j=0;j<showcharn;j++) {
					cout<<'=';
				}
				for(int j=0;j<40-showcharn;j++) {
					cout<<'#';
				}
				cout<<"]";
				lastshowcharn=showcharn;
			}
		} else {
			cout<<code<<endl;
		}
		cnt++;
	}
	if(!bf) {
		for(int j=0;j<51;j++) {
			cout<<'\b';
		}
		cout<<"RUNNING: [";
		for(int j=0;j<40;j++) {
			cout<<'=';
		}
		cout<<"]";
	}
	cout<<"\nSUCCESS: -n "<<n<<" -l "<<l<<" "<<modestr[mode]<<"("<<mode<<")"<<(bf? "":" -f")<<endl;
	cout<<"LOG: COST TIME = "<<secTstr(time(0)-begintime_base)<<endl;

    return 0;
}

