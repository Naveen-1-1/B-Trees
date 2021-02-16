#include<bits/stdc++.h>
using namespace std;

struct bdnode
{
	int cnt;
	int key[100];
	bdnode *e[101];
};

typedef struct bdnode *ptr;
ptr root=0;

void isort(ptr t, int key)
{
	int i=t->cnt-1;
	while(i>=0 && key<t->key[i])
	{
		t->key[i+1]=t->key[i];
		i--;
	}
	t->key[i+1]=key;
	t->cnt++;
	t->e[t->cnt]=0;
}

int index(ptr t, int key)
{
	int i=t->cnt-1;
	while(i>=0 && key<t->key[i])
		i--;
	return i+1;
}
	

ptr rootcreate(ptr t,int d)
{
	int i=0;
	ptr p=new(bdnode),c=new(bdnode);
	c->cnt=0;
	p->key[0]=t->key[d];
	for(i=0;i<2*d+1;i++)
		p->e[i]=0;
	p->cnt=1;
	for(i=0;i<d;i++)
	{
		c->key[i]=t->key[d+i+1];
		c->e[i]=t->e[d+i+1];
		t->e[d+i+1]=0;
		c->cnt++;
	}
	t->cnt=d;
	c->e[i]=t->e[2*i+1];
	t->e[2*i+1]=0;
	p->e[0]=t;
	p->e[1]=c;
	return p;
}

void padd(ptr t, ptr b)
{
	int i=t->cnt-1;
	while(i>=0 && b->key[0]<t->key[i])
	{
		t->key[i+1]=t->key[i];
		t->e[i+2]=t->e[i+1];
		t->e[i+1]=t->e[i];
		i--;
	}
	i++;
	t->key[i]=b->key[0];
	t->e[i]=b->e[0];
	t->e[i+1]=b->e[1];
	t->cnt++;
}

ptr create(ptr t, int key, int d, int &f)
{
	if(t)
	{
		int i;
		ptr b=0;
		if(t->e[0])
		{
			i=index(t,key);
			b=create(t->e[i],key,d,f);
			t->e[i]=b;
		}
		else
		{
			isort(t,key);
			if(t->cnt>2*d)
			{
				t=rootcreate(t,d);
				f=1;
			}
			return t;
		}
		if(b && f)
		{
			if(b->e[0])
			{
				if(b->cnt<=b->e[0]->cnt)
				{
					f=0;
					padd(t,b);
					if(t->cnt>2*d)
					{
						t=rootcreate(t,d);
						f=1;
					}
					return t;
				}
			}
		}
		return t;
	}
	else
	{
		ptr t1=new(bdnode);
		t1->cnt=0;
		t1->key[t1->cnt++]=key;
		for(int i=0;i<=2*d+1;i++)
			t1->e[i]=0;
		return t1;
	}
}

void inorder(ptr t)
{
	if(t)
	{
		for(int j=0;j<t->cnt;j++)
		{
			inorder(t->e[j]);
			cout<<t->key[j]<<" ";	
		}
		inorder(t->e[t->cnt]);
	}
}

void level(queue <ptr> q)
{
	if(!q.empty())
	{
		ptr t=q.front();
		q.pop();
		if(t->cnt==-1)
		{
			cout<<endl;
			if(!q.empty())
				q.push(t);
		}
		else
		{
			int i;
			for(i=0;i<t->cnt;i++)
			{
				cout<<t->key[i]<<" ";
				if(t->e[i])
					q.push(t->e[i]);
			}
			cout<<"\t";
			if(t->e[t->cnt])
				q.push(t->e[t->cnt]);
		}
		level(q);
	}
}
	
int main()
{
	int d,x;
	queue <ptr> q;
	cout<<"Enter d: ";
	cin>>d;
	ptr t=0,t1=new(bdnode);
	t1->cnt=-1;
	t1->e[0]=0;
	while(1)
	{
		int f=0;
		cout<<"Enter key: -1 to break ";
		cin>>x;
		if(x==-1)
			break;
		t=create(t,x,d,f);
		inorder(t);
		cout<<endl;
		queue <ptr> q1;
		q1.push(t),q1.push(t1);
		level(q1);
	}
	q.push(t),q.push(t1);
	cout<<endl;
	level(q);
	return 0;
}
		
		
