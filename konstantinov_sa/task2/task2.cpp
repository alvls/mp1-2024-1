#include<iostream>
using namespace std;

#define MY_DEBUG

class Dynamic {
	double* mdata;
	size_t msize;

public:
	Dynamic(size_t size = 0) { //по умолчанию/инициализатор
		msize = size;
		mdata = new double[size];
#ifdef MY_DEBUG
		cout << "init constructor: size " << msize << endl;
#endif
	}

	Dynamic(const Dynamic& other) { //копирования
		msize = other.msize;
		mdata = new double[msize];
		copy(other.mdata, other.mdata + msize, mdata);
#ifdef MY_DEBUG
		cout << "copy constructor: size " << msize << endl;
#endif
	}

	Dynamic(Dynamic&& other) noexcept { //перемещения //пришлось узнать про r-values и <type>&& reference
		msize = other.msize;
		mdata = other.mdata;
		other.msize = 0;
		other.mdata = nullptr;
#ifdef MY_DEBUG
		cout << "move constructor: size " << msize << endl;
#endif
	}

	//changes size of Dynamic, all data is lost
	void setsize(size_t size) {
		msize = size;
		delete[] mdata;
		mdata = new double[size];
	}
	//changes size of Dynamic, data is copied (if fits)
	void resize(size_t size) {
		double* ndata = new double[size];
		memcpy(ndata, mdata, sizeof(double) * size);
		delete[] mdata;
		mdata = ndata;
		msize = size;
	}

	size_t size() {
		return msize;
	}

	void set(size_t index, double value) {
		if (index < msize)
			mdata[index] = value;
	}

	double get(size_t index) {
		if (index < msize)
			return mdata[index];
		cout << "Cant read memory out of bounds\n";
		return 0.;
	}

	const double& operator[](size_t index) const {
		return mdata[index];
	}

	double& operator[](size_t index) {
		if(index<msize)
			return mdata[index];
		cout << "\nHeap corruption attempt!\nYour pc will explode in\n3...\n2...\n1...\nLast element returned instead\n";
		return mdata[msize - 1];
	}

	void print() {
		cout << "{ ";
		for (size_t i = 0; i < msize; i++) {
			cout << mdata[i] << ' ';
		}
		cout <<'}'<< endl;
	}

	size_t findmin() { 
		double mi = mdata[0];
		size_t index = 0;
		for (size_t i = 1; i < msize; i++) {
			if (mdata[i] < mi) {
				index = i;
				mi = mdata[i];
			}
		}
		return index; //выбран индекс. Потому что я вспомнил про поиск в питоне, который возвращает значение, и приходится искать дважды чтобы узнать индекс...

	}

	void nullify() {
		for (size_t i = 0; i < msize; i++) {
			mdata[i] = 0.;
		}
	}

	void initWith(double n) {
		for (size_t i = 0; i < msize; i++) {
			mdata[i] = n;
		}
	}

	bool isSorted() {//"упорядочен" интерпретировано как отсортирован по возрастанию (неубыванию)
		for (size_t i = 1; i < msize; i++) {
			if (mdata[i] < mdata[i-1]) {
				return 0;
			}
		}
		return 1;
	}

	Dynamic createSubarray() {
		Dynamic s(msize/2);
		size_t t = 0;
		for (size_t i = 1; i < msize;i +=2) {
			s.set(t, mdata[i]);
			t++;
		}
		return s;
	}

	~Dynamic() {
#ifdef MY_DEBUG
		cout << "destructor: size ";
		cout << msize<<" deleted\n";
#endif
		delete[] mdata;
	}
};

int main() {
	Dynamic a(10);
	a.nullify();
	a.set(0, 42);
	a.set(2, 999);
	a.set(8, -0.5);
	a[9] = 3;
	a.print();
	cout << a.get(a.findmin())<<endl;

	/*a.resize(3);
	a[1] = 111;
	a.print();
	cout << a.isSorted();
	cout << endl;*/

	/*Dynamic* d = new Dynamic(5);
	cout << "d size " << d->size()<<endl;
	d->set(4, 444.5);
	(*d)[0] = 0.0101;
	d->print();
	delete d;*/

	Dynamic c = a.createSubarray();
	c.print();
	
	system("pause");
}