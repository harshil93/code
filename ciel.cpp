#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;
#define PR(x) cout << #x " = " << x << "\n";

int no[20];
int main(){
	no[0]=8;
	int cnt=0;
	int len=1;
	while(1){
	
		int freq[10]={0};
		
		for (int i = 0; i < 20; ++i)
		{
			freq[no[i]]++;
			if (no[i]==0)
			{
				break;
			}
			
		}

		if (freq[8]>=freq[5] && freq[5]>=freq[3])
		{
			int64_t temp=0;
			// PR(len);
			for (int i = len -1; i>=0; --i)
			{
				putchar(no[i]+'0');
			}
			putchar('\n');
			cnt++;
			if (cnt==50000)
			{
				break;
				return 0;
			}
		}

		for (int i = 0;; ++i)
		{
			int flag=1;
			switch(no[i]){
				case 8:
					no[i]=3;
					flag=0;
					break;
				case 5:
					no[i]=8;
					break;
				case 3:
					no[i]=5;
					break;
				case 0:
					no[i]=3;
					len = i+1;
					break;
			}

			if (flag)
			{
				break;
			}
		}
	}
}