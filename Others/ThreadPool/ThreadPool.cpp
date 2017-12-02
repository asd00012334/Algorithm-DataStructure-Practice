#include<bits/stdc++.h>
#include<pthread.h>
#include<semaphore.h>

using namespace std;

template<class type>
struct Get{
	type& obj;
	Get(type& obj):obj(obj){ sem_wait(&obj.lock);}
	~Get(){ sem_post(&obj.lock);}
	type* operator->(){ return &obj;}
};
template<class type>
Get<type> get(type& obj){ return Get<type>(obj);}

template<typename type>
struct ThreadQueue{
	sem_t size;
	sem_t lock;
	queue<type> dataList;
	ThreadQueue(){
		sem_init(&size, 0, 0);
		sem_init(&lock,0,1);
	}
	~ThreadQueue(){
		sem_destroy(&size);
		sem_destroy(&lock);
	}
	void push(type const& obj){
		get(*this)->dataList.push(obj);
		sem_post(&size);
	}
	type pop(bool sizeProtect=true){
		if(sizeProtect) sem_wait(&size);
		sem_wait(&lock);
			type out = dataList.front();
			dataList.pop();
		sem_post(&lock);
		return out;
	}
	inline type front(){ return get(*this)->dataList.front();}
};

class ThreadPool{
	typedef function<void(void)> Task;
	const int threadNum;
	volatile bool activate;
	ThreadQueue<Task> taskAwait;
	vector<pthread_t> tid;
	static void* exec(void * arg){
		ThreadPool& tp = *(ThreadPool*)arg;
		while(1){
			sem_wait(&tp.taskAwait.size);
			if(!tp.activate) break;
			tp.taskAwait.pop(false)();
		}
		return NULL;
	}
public:
	ThreadPool(int n): threadNum(n), tid(n){
		activate = true;
		for(int i=0;i<n;++i)
			pthread_create(&tid[i],NULL,exec,(void*)this);
	}
	~ThreadPool(){
		activate = false;
		for(int i=0;i<tid.size();++i) sem_post(&taskAwait.size);
		for(int i=0;i<tid.size();++i) pthread_join(tid[i],NULL);
	}
	void push(Task func){
		taskAwait.push(func);
	}
};

int main(){
	ThreadPool tp(8);
	sem_t sync;
	sem_init(&sync,0,0);
	for(int i=0;i<20;++i)
		tp.push([i,&sync](){
			for(int j=0;j<20;++j)
				printf("%d, ",i*20+j);
			sem_post(&sync);
		});
	for(int i=0;i<20;++i)
		sem_wait(&sync);
}
