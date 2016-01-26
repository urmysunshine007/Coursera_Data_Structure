#include <iostream>
#include <list>
using namespace std;

template<class T>
class Link{
public:
	T data;
	Link<T> * next;
	Link(const T value, Link<T> * nextValue = NULL){
		data = value;
		next = nextValue;
	}
	Link(Link<T>* nextValue = NULL){
		next = nextValue;
	}
};
template<class T>
class lnklist :public list<T>{
public:
	Link<T> *head, *tail;
	Link<T> *setPos(const int p); //pointer to the pth element
	lnklist(int s);
	bool isEmpty();
	void clear();
	int length();
	bool append(const T value);
	bool insert(const int p, const T value);
	bool delete1(const int p);
	bool getValue(const int p, T& value);
	bool getPos(int &p, const T value);
};

template<class T>
lnklist<T>::lnklist(int s){
	head = new Link<T>;
	tail = head;
	int i = 1;
	while (s>0){
		append(i);
		s--;
		i++;
	}
}

template<class T>
Link<T>* lnklist<T>::setPos(const int i){
	int count = 0;
	if (i == -1)
		return head;
	Link<T> * p = head->next;
	while (p != NULL && count<i){
		p = p->next;
		count++;
	}
	return p;
}

template<class T>
bool lnklist<T>::insert(const int i, const T value){
	Link<T> *p, *q;
	if ((p = setPos(i - 1)) == NULL){
		return false;
	}
	q = new Link<T>(value, p->next);
	p->next = q;
	if (p == tail)
		tail = q;
	return true;
}

template<class T>
bool lnklist<T>::delete1(const int i){
	Link<T> *p, *q;
	if ((p = setPos(i - 1)) == NULL || p == tail){
		return false;
	}
	q = p->next;
	if (q == tail){
		tail = p;
		p->next = NULL;
	}
	else{
		p->next = q->next;
	}
	delete q;
	return true;
}
template<class T>
bool lnklist<T>::append(const T value){
	if (isEmpty()){
		Link<T> *p = new Link<T>(value, NULL);
		head->next = p;
		tail = p;
	}
	else{
		Link<T> *p = new Link<T>(value, NULL);
		tail->next = p;
		tail = p;
	}
	return true;
}
template<class T>
bool lnklist<T>::isEmpty(){
	if (head->next == NULL){
		return true;
	}
	return false;
}
template<class T>
int lnklist<T>::length(){
	int len = 0;
	Link<T> *p = head;
	while (p != tail){
		len++;
		p = p->next;
	}
	return len;
}

int main(){
	int n, m;
	cin >> n >> m;
	lnklist<int> mylist(n);
	mylist.tail->next = mylist.head;
	int count = 0;
	Link<int> *p = mylist.head, *q;
	while (mylist.length() >1){

		if (count == m - 1){
			if (p->next == mylist.head){
				q = mylist.head->next;
				mylist.head->next = q->next;
				delete q;
			}
			else if (p->next == mylist.tail){
				q = p->next;
				p->next = q->next;
				delete q;
				mylist.tail = p;
			}
			else{
				q = p->next;
				p->next = q->next;
				delete q;
			}
			count++;
		}
		p = p->next;
		if (p == mylist.head){
			p = p->next;
		}
		count++;
		count = count%m;
	}
	cout << mylist.tail->data;
	return 0;
}