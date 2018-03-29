#include <iostream>
#include <cmath>
#include <unordered_map>
#include <cstdint>
#include <array>
#include <vector>
#include <string>
using namespace std;
typedef array<int32_t, 4> vector4;
typedef array<vector4, 4> matrix4x4;

unordered_map<char, int32_t> encodeLookup;
unordered_map<int32_t, char> decodeLookup;
void initLookups() {
	for (char c = 'a'; c <= 'z'; c++) {
		int32_t v = c - ('a' - 1);
		encodeLookup[c] = v;
		decodeLookup[v] = c;
	}
}
vector<vector4> preproc(string s) {
	vector<vector4> ret;
	if (s.length() == 0) return ret;
	if (s.length() % 4 != 0) s=s.append(" ", s.length() % 4);
	for (int chunkPtr = 0; chunkPtr < s.length() / 4; chunkPtr += 4) {
		string chunk_s = s.substr(chunkPtr, 4);
		vector4 chunk_v;
		for (int elemIdx = 0; elemIdx < 4; elemIdx++) {
			chunk_v[elemIdx] = encodeLookup[chunk_s[elemIdx]];
		}
		ret.push_back(chunk_v);
	}
}
vector4 mul(vector4 v,matrix4x4 m) {
	vector4 ret = { 0,0,0,0 };
	for (int y=0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			ret[y] += v[x]*m[y][x];
			
		}
		cout << endl;
	}
	return ret;
}
void testMul() {
	matrix4x4 m = { vector4{ 0,-1,0,0 },{ 1,0,0,0 },{ 0,0,1,0 },{ 0,0,0,1 } };
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			cout << (int)m[y][x] << " ";
		}
		cout << "\n";
	}
	vector4 x = { 1,0,0,0 };
	x = mul(x, m);
	for (int i = 0; i < 4; i++) {
		cout << x[i] << " ";
	}
	x = mul(x, m);
	for (int i = 0; i < 4; i++) {
		cout << x[i] << " ";
	}
	x = mul(x, m);
	for (int i = 0; i < 4; i++) {
		cout << x[i] << " ";
	}
	x = mul(x, m);
	for (int i = 0; i < 4; i++) {
		cout << x[i] << " ";
	}
	cout << "\n";
	cout << endl;
}
int main(int argc, char* argv[]) {
	
	
	cout << endl;
	cin.get();
}


