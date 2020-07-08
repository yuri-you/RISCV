#include<iostream>
using namespace std;	
unsigned sext(unsigned x, int n) {
	return (x & (1U << (n - 1))) ? (((0xffffffff >> n) << n)& x): x;
}
unsigned J(unsigned data) {
	unsigned ans;
	ans = ((data & (((1U << 32) - 1U) & (~((1U << 21) - 1U)))) >> 20);//21-31 to 1-11
	ans |= (data & (1U << 20)) >> 9;//20 to 11
	ans |= (data & ((1U << 20) - 1U) & (~((1U << 12) - 1U)));//12-19 to 12-19;
	ans |= (data & (1U << 31)) >> 11;//31 to 20
	return sext(ans, 21);
}
int main() {
	unsigned int a[10];
	for (int i = 0; i < 10; ++i) {
		a[i] = 0xffff0000;
	}
	cout << (unsigned)(*(unsigned short*)((unsigned char*)(a)+1));
	return 0;
}