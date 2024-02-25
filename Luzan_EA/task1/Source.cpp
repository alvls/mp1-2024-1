#include <iostream>

using namespace std;

const long long UI_MAX = 4294967296;
//const short UI_MAX = 256;


class LN {

public:
	LN(long long out) {
		if (out >= 0) {
			lp = out % UI_MAX;
			bp = (out - lp) / UI_MAX;
		}
		else {
			lp = UI_MAX + (out % UI_MAX);
			bp = (out - lp) / UI_MAX;
		}
	}

	LN(long  bp_, long  lp_) {
		bp = bp_;
		lp = lp_;
	}

	LN() {
		bp = 0;
		lp = 0;
	}

	void printLN() {
		long long tmp = bp * UI_MAX + lp;
		cout << tmp << endl;
	}

	void testPrint() {
		printf_s("%i  %i\n", bp, lp);
	}

	LN add_(LN x, LN y) {
		LN res(0, 0);
		res.lp = x.lp + y.lp;
		if (res.lp < x.lp) { res.bp++; }

		res.bp += x.bp + y.bp;
		
		return res;
	}

	LN testadd(LN x, LN y) {
		long long tmp1 = x.makeLL();
		long long tmp2 = y.makeLL();
		long long tmp3 = tmp1 + tmp2;
		LN res(tmp3);
		return res;
	}

	LN minus_(LN x, LN y) {
		LN tmp = y;
		tmp.makeNegative();
		return x.add_(x, tmp);
	}
	
	void makeNegative() {
		lp = UI_MAX - lp;
		bp = -bp - 1;
		if (lp == 0) { bp++; } // 256 - 0 = 256 -> 0
	}

	LN testminus(LN x, LN y) {
		long long tmp1 = x.makeLL();
		long long tmp2 = y.makeLL();
		long long tmp3 = tmp1 - tmp2;
		LN res(tmp3);
		return res;
	}


	LN mult_(LN x, LN y) {
		LN res;
		long long tmp = x.lp * y.lp;
		res.lp = tmp % UI_MAX;
		res.bp = tmp / UI_MAX;

		res.bp += x.lp * y.bp + x.bp * y.lp + x.bp * y.bp * UI_MAX;
		return res;
	}


	LN testmult(LN x, LN y) {
		long long tmp1 = x.makeLL();
		long long tmp2 = y.makeLL();
		long long tmp3 = tmp1 * tmp2;
		LN res(tmp3);
		return res;
	}

	LN div_(LN x, LN y) {
		LN res;
		LN yPos = y, xPos = x;
		if (y.makeLL() < 0) { yPos = y; yPos.makeNegative(); }
		if (x.makeLL() < 0) { xPos = x; xPos.makeNegative(); }

		// ... знаки, но ... 0
		if (yPos.makeLL() == 0) { cout << "Div by zero!" << endl; res.bp = UI_MAX - 1; return res; }
		if ((xPos.makeLL() == 0) || (xPos.makeLL() < yPos.makeLL())) { return res; }

		res.lp = 1;
		long long Edif = yPos.makeLL();
		long long dif = Edif - xPos.makeLL();

		while (dif >= Edif) {
			long long tmp = res.lp;
			dif = xPos.makeLL() - (res.mult_(xPos, res.mult_(yPos, res))).makeLL();
			res.lp += 1;
			if (res.lp < tmp) { res.bp++; }
		}
		
		if (((y.makeLL() < 0) && (x.makeLL() > 0)) || ((y.makeLL() > 0) && (x.makeLL() < 0))) {
			res.makeNegative();
		}
		return res;

	}

	LN testdiv(LN x, LN y) {
		long long tmp1 = x.makeLL();
		long long tmp2 = y.makeLL();
		long long tmp3 = tmp1 / tmp2;
		LN res(tmp3);
		return res;
	}

	long long makeLL() {
		long long tmp = bp * UI_MAX + lp;
		return tmp;
	}

	LN mDiv_(LN x, LN y) {
		LN res = res.minus_(x, mult_( div_(x, y), y));
		return res;
	}

	LN testmDiv(LN x, LN y) {
		long long tmp1 = x.makeLL();
		long long tmp2 = y.makeLL();
		long long tmp3 = tmp1 % tmp2;
		LN res(tmp3);
		return res;
	}

private:
	long  bp;
	unsigned long  lp;

};



long  main() {
	LN obj1(300), obj2(200);
	LN obj3, tmp;

	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "add\n";
	obj3 = obj3.add_(obj1, obj2);
	tmp = tmp.testadd(obj1, obj2);
	obj3.printLN();
	obj3.testPrint();
	tmp.printLN();
	tmp.testPrint();

	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "minus\n";
	obj3 = obj3.minus_(obj1, obj2);
	tmp = tmp.testminus(obj1, obj2);
	obj3.printLN();
	obj3.testPrint();
	tmp.printLN();
	tmp.testPrint();

	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "mult\n";
	obj3 = obj3.mult_(obj1, obj2);
	tmp = tmp.testmult(obj1, obj2);
	obj3.printLN();
	obj3.testPrint();
	tmp.printLN();
	tmp.testPrint();

	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "div\n";
	obj3 = obj3.div_(obj1, obj2);
	tmp = tmp.testdiv(obj1, obj2);
	obj3.printLN();
	obj3.testPrint();
	tmp.printLN();
	tmp.testPrint();

	cout << "\n\n-------------------------------------------------------------------\n\n";
	cout << "mdiv\n";
	obj3 = obj3.mDiv_(obj1, obj2);
	tmp = tmp.testmDiv(obj1, obj2);
	obj3.printLN();
	obj3.testPrint();
	tmp.printLN();
	tmp.testPrint();

	return 0;
}