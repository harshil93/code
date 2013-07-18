#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <utility>
#include <queue>
#include <algorithm>

using namespace::std;

struct info
{
	int pos_index;
	int disk_index;

	int weight;
};

bool operator<(const info &in1, const info &in2)
{
	return (in1.weight > in2.weight);
}

main()
{
	int T;
	scanf("%d", &T);

	for (int t = 0; t < T; t++)
	{
		int N, M, W;
		scanf("%d", &N);
		scanf("%d", &M);
		scanf("%d", &W);

		vector<pair<int, int> > pos(N, make_pair(0, 0));
		for (int i = 0; i < N; i++)
		{
			int x, y;
			scanf("%d", &x);
			scanf("%d", &y);

			pos[i].first = x;
			pos[i].second = y;
		}

		vector<pair<int, int> > disk(M, make_pair(0, 0));
		for (int i = 0; i < M; i++)
		{
			int x, y;
			scanf("%d", &x);
			scanf("%d", &y);

			disk[i].first = x;
			disk[i].second = y;
		}

		// std::cout << "input read" << std::endl;
		std::sort(disk.begin(), disk.end());

		vector<pair<int, int> > cand = vector<pair<int, int> >();
		for (int i = disk.size() - 1; i >=0; --i)
		{
			bool flag = true;
			for (int j = i+1; j < disk.size(); ++j)
			{
				if(disk[j].second<=disk[i].second){
					flag = false;
					break;
				}
			}
			if(flag){
				cand.push_back(disk[i]);
			}
		}
		
		sort(cand.begin(),cand.end());
		int m = cand.size();
		vector<int> next_cand(N, m - 1);
		priority_queue<info> pq = priority_queue<info>();
		for (int i = 0; i < N; i++)
		{
			while (next_cand[i] >= 0)
			{
				if (pos[i].second <= cand[next_cand[i]].first)
				{
					info in;
					in.pos_index = i;
					in.disk_index = next_cand[i];
					in.weight = cand[next_cand[i]].second;
					// cout<<i<<" "<<next_cand[i]<<" "<<in.weight<<endl;
					pq.push(in);

					//std::cout << "pushing " << in.pos_index << ", " << in.disk_index << std::endl;
					next_cand[i]--;
				}
				else
					break;
			}
		}

// return 0;
		vector<vector<long double> > dist(N, vector<long double>(N, 0));
		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				long double dx = (long double) pos[i].first - (long double) pos[j].first;
				long double dy = (long double) pos[i].second - (long double) pos[j].second;

				dist[i][j] = dist[j][i] = sqrtl(dx * dx + dy * dy);
			}
		}

		int ans = -1;
		while (!pq.empty())
		{
			info in = pq.top();
			pq.pop();

			//std::cout << "popping " << in.pos_index << ", " << in.disk_index << std::endl;
			
			int p = in.pos_index;
			int q = in.disk_index;

			if ((pos[p].second + cand[q].first) >= W)
			{
				ans = in.weight;
				break;
			}

			for (int i = 0; i < N; i++)
			{
				while (next_cand[i] >= 0)
				{
					long double sum = (long double) cand[q].first + (long double) cand[next_cand[i]].first;
					if ((sum + 1e-9) >= dist[p][i])
					{
						info in1;
						in1.pos_index = i;
						in1.disk_index = next_cand[i];
						in1.weight = in.weight + cand[next_cand[i]].second;
					
						//std::cout << "pushing " << in1.pos_index << ", " << in1.disk_index << std::endl;
						
						pq.push(in1);
						next_cand[i]--;
					}
					else
						break;
				}
			}
		}

		if (ans == -1)
			printf("impossible\n");
		else
			printf("%d\n", ans);
	}
}