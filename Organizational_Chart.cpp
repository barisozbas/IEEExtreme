#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
#define NN 200001

std::unordered_map<string, int> index;
int root;

long long divArr[NN], allArr[NN];
long long divMinArr[NN], allMinArr[NN];
long long divMaxArr[NN], allMaxArr[NN];
long long chArr[NN];
int parentArr[NN], bebeHeadArr[NN], bebeTailArr[NN], siblingArr[NN];

void childPreprocess(int);
void parentPreprocess(int);
void minPass(int);
void maxPass(int, long long);

int main() {
	int count = 1, ind, indexParent;
	int ii, type, N, Q;
	long long div, all;
	string node, parent;
	
	cin >> N >> Q;

	count = 1;
	for(ii=1; ii<=N; ii++) {
		cin >> node >> parent >> div >> all;
		// cout << node << " " << parent << " " << div << " " << all << endl;

		if(index[node] == 0) {
			index[node] = count;
			count++;
		}
		ind = index[node];
		
		divArr[ind] = div;
		allArr[ind] = all;
		chArr[ind] = 0;
		siblingArr[ind] = 0;

		if(parent == "NONE") {
			root = ind;
			parentArr[ind] = 0;
		} else {
			if(index[parent] == 0) {
				index[parent] = count;
				bebeHeadArr[count] = bebeTailArr[count] = 0;
				count++;
			}
			indexParent = index[parent];

			if(bebeHeadArr[indexParent] == 0) {
				bebeHeadArr[indexParent] = bebeTailArr[indexParent] = ind;
			} else {
				siblingArr[bebeTailArr[indexParent]] = ind;
				bebeTailArr[indexParent] = ind;
			}
			parentArr[ind] = indexParent;
		}
	}

	childPreprocess(root);
	parentPreprocess(root);
	childPreprocess(root);

	minPass(root);
	maxPass(root, (long long) 6000000000);

	for(ii=1; ii<=Q; ii++) {
		cin >> node >> type;
		ind = index[node];

		if(type == 1) {
			cout << divMinArr[ind] << " " << divMaxArr[ind] << endl;
		} else {
			cout << allMinArr[ind] << " " << allMaxArr[ind] << endl;
		}
	}
}

void childPreprocess(int node) {
	bool childrenAllKnown = 1;
	long long childrenAllSum = 0;

	int child = bebeHeadArr[node];
	while(child) {
		childPreprocess(child);
		
		long long childAll = allArr[child];
		childrenAllSum += childAll;
		if(childAll == 0) {
			childrenAllKnown = 0;
		}

		child = siblingArr[child];
	}

	if(childrenAllKnown) {
		long long nodeAll = allArr[node];
		long long nodeDiv = divArr[node];

		chArr[node] = childrenAllSum;
		if((nodeAll == 0) && (nodeDiv != 0)) {
			allArr[node] = nodeDiv +childrenAllSum;
		} else if((nodeAll != 0) && (nodeDiv == 0)) {
			divArr[node] = nodeAll -childrenAllSum;
		}
	} else {
		chArr[node] = 0;
	}
}

void parentPreprocess(int node) {
	long long nodeAll = allArr[node];
	if(nodeAll != 0) {
		long long nodeDiv = divArr[node];
		if(nodeDiv != 0) {
			int childrenUnknown = 0;
			int childUnknown = 0;
			long long childrenSum = 0;
			if(chArr[node] == 0) {
				int child = bebeHeadArr[node];
				while(child) {
					childrenSum += allArr[child];
					if(allArr[child] == 0) {
						childrenUnknown++;
						childUnknown = child;
						if(childrenUnknown == 2) {
							break;
						}
					}
					child = siblingArr[child];
				}
			}

			if(childrenUnknown == 1) {
				long long childAll = allArr[childUnknown] = nodeAll -nodeDiv -childrenSum;
				long long childDiv = divArr[childUnknown];
				long long childCh = chArr[childUnknown];
				if((childCh != 0) && (childDiv == 0)) {
					divArr[childUnknown] = childAll -childCh;
				}
			}
		}
	}

	int child = bebeHeadArr[node];
	while(child) {
		parentPreprocess(child);
		child = siblingArr[child];
	}
}

void minPass(int node) {
	long long nodeDiv = divArr[node];
	long long nodeAll = allArr[node];

	if(nodeDiv == 0) {
		divMinArr[node] = 1;
	} else {
		divMinArr[node] = nodeDiv;
	}

	long long childrenAllSum = 0;
	int child = bebeHeadArr[node];
	while(child) {
		minPass(child);
		
		long long childAll = allMinArr[child];
		childrenAllSum += childAll;
		child = siblingArr[child];
	}

	if(nodeAll == 0) {
		allMinArr[node] = divMinArr[node] +childrenAllSum;
	} else {
		allMinArr[node] = nodeAll;
	}
}

void maxPass(int node, long long allMax) {
	long long nodeDiv = divArr[node];
	long long nodeAll = allArr[node];

	long long nodeAllMax = nodeAll;
	if(nodeAll == 0) {
		nodeAllMax = allMax;
	}
	allMaxArr[node] = nodeAllMax;

	long long childrenAllSum = 0;
	int child = bebeHeadArr[node];
	while(child) {
		long long childAll = allMinArr[child];
		childrenAllSum += childAll;
		child = siblingArr[child];
	}

	if(nodeDiv == 0) {
		divMaxArr[node] = allMaxArr[node] -childrenAllSum;
	} else {
		divMaxArr[node] = nodeDiv;
	}

	long long slack = nodeAllMax -divMinArr[node] -childrenAllSum;
	child = bebeHeadArr[node];
	while(child) {
		maxPass(child, allMinArr[child] +slack);
		child = siblingArr[child];
	}
}
