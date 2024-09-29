#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<ctime>

using namespace std;

typedef pair<int,int> PII;

const int MAX = 9999999.0;

bool cmp(PII x,PII y)
{
	if(x.first == y.first)return x.second < y.second;
	else return x.first < y.first;
}

void BaoLi(vector<PII> & px)
{
	double min_dis = MAX;
	//遍历每一个某个点与其他所有点之间的距离，求出举例最小的点
	for(auto i : px){
		for(auto j : px){
			if(i.first != j.first || i.second != j.second){
				double dis = sqrt(1.0 * (i.first - j.first) * (i.first - j.first)  + 1.0 * (i.second - j.second) * (i.second - j.second));
				if(dis < min_dis)min_dis = dis;
			}
		}
	}
	cout << min_dis << endl;
}

double merge(vector<PII> & p,int l,int r)
{
	if(r - l <= 1){				//最简情况是怎样的，需要仔细思考
		if(r - l == 1){
			double dis = sqrt(1.0 * (p[l].first - p[r].first) * (p[l].first - p[r].first)  + 1.0 * (p[l].second - p[r].second) * (p[l].second - p[r].second));
			if(dis > 0)return dis;
			else return MAX;
		}
		else{
			return MAX;
		}
	}				
	int mid = l + r >> 1;
	double lmin = merge(p,l,mid);
	double rmin = merge(p,mid + 1, r);
	double min = lmin < rmin ? lmin : rmin,res = min;				//找到两侧中最小的
	double ll = p[mid].first - min,rr = p[mid].first + min;
	//确认从mid两边取点时的新形成的区域的下标范围
	int low = mid,high = mid;
	while(p[low].first > ll && low > l) low --;
	while(p[high].first < rr && high < r) high ++;
	//比较该区域的mid两侧的点的距离与min，确认最小值
	int i = low,j = mid + 1,cnt;
	while(i <= mid){
		cnt = 0;
		//对于左侧的每一个点，若是右侧的点有符合半矩形定理的点，则将该点的到左侧访问点的距离 与 当前最小距离min作比较，取较小值
		while(p[i].first + min > p[j].first && p[i].second + min > p[j].second && p[i].second - min < p[j].second && j <= high && cnt < 6){
			double dis = sqrt(1.0 * (p[i].first - p[j].first) * (p[i].first - p[j].first)  + 1.0 * (p[i].second - p[j].second) * (p[i].second - p[j].second));
			if(dis < res)res = dis;
			j++;
			cnt++;
		}
		j = mid + 1;
		i++;
	}
	return res;			//返回当前区间的最小点对距离
}

void gett(int t,int n)
{
	//数据初始化
	int q = 20;
	vector<double> meo;
	vector<PII> p;			//p为按照x升序的点对存放的序列,如果x相同，则按照y升序
	//生成随机点对
	while(q--){
		srand(10000 + q);
		//生成随机数据
		for(int i = 0;i < n;i++){
			int x = rand() % (10000 + n),y = rand() % (10000 + n);
			p.push_back({x,y});
		}
		sort(p.begin(),p.end(),cmp);
		
		//计算耗时并存储
		struct timeb startTime,endTime;
		ftime(&startTime);
		if(t >= 3){
			for(int i = 0;i < 10000;i++){
				merge(p,0,n - 1);
			}
		}
		else{
			for(int i = 0;i < 100;i++){
				merge(p,0,n - 1);
			}
		}
		ftime(&endTime);
		if(t >= 3)meo.push_back(((endTime.time - startTime.time) * 1000 + endTime.millitm - startTime.millitm) * 1.0 / 10000);
		else meo.push_back(((endTime.time - startTime.time) * 1000 + endTime.millitm - startTime.millitm) * 1.0 / 100);
		p.clear();
	}
	cout << "点对的数量级为" << n << "时的耗时分别为:\n";
    double sum = 0.0;
    for(int i = 0;i < meo.size();i++){
        sum += meo[i];
        if(i != (meo.size() / 2 - 1))printf("%lf    ",meo[i]);
        else{
            printf("%lf    ",meo[i]);
            puts("");
        }
    }
    printf("\n平均耗时为: %lf\n\n",sum / meo.size());
}
int main()
{
	cout << "以下为分治算法的实验\n";
    for(int i = 0;i < 50; i++)
    {
        cout << '*';
    }
	puts("");
	int n = 100,t = 4;
	while(t){
		gett(t,n);
		n *= 10;
		t--;
	}
	system("pause");
	return 0;
}
