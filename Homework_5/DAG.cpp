//#pragma once
//#include"Optimizer.h"
//#include"DAG.h"
//using namespace std;
//extern vector<MidCode> versionFive;
//vector<MidCode> versionSix;
//
//void updateCodes() {
//	MidCode temp;
//	for (int i = 0; i < versionFive.size(); i++) {
//		temp.op = versionFive[i].op;
//		if (versionFive[i].op == "=" && versionFive[i].x.back() == ']') {			// 改变四元式 a[i] = t -> []= i t a
//			temp.op = "[]=";
//			int j;
//			for (j = 0; j < versionFive[i].x.size(); j++) {
//				if (versionFive[i].x[j] == '[') {
//					break;
//				}
//			}
//			temp.x = versionFive[i].x.substr(j, versionFive[i].x.size() - j - 2);
//			temp.y = versionFive[i].y;
//			temp.z = versionFive[i].x.substr(0, j + 1);
//		}
//		else if (versionFive[i].op == "=" && versionFive[i].y.back() == ']') {
//			temp.op == "[]";
//			int j;
//			for (j = 0; j < versionFive[i].y.size(); j++) {
//				if (versionFive[i].y[j] == '[') {
//					break;
//				}
//			}
//			temp.x = versionFive[i].y.substr(0, j + 1);
//			temp.y = versionFive[i].y.substr(j, versionFive[i].y.size() - j - 2);
//			temp.z = versionFive[i].x;
//		}
//	}
//}
//
//void getContent(string name) {
//	for (int i = 0; i < name.size(); i++) {
//		if (name[i] == '[') {
//
//		}
//	}
//}
//
//map<string, DAGNode> getNodes(vector<MidCode> codes) {
//	vector<DAGNode> DAGMap;					// DAG图
//	map<string, int> name2Index;		// 名字到结点的映射
//	vector<MidCode> head;
//	vector<MidCode> end;
//
//	for (int i = 0; i < codes.size(); i++) {
//		if (codes[i].op != "printf" || !isOp(codes[i]) || codes[i].op == "push" || codes[i])
//	}
//
//	for (int i = 0; i < codes.size(); i++) {
//		MidCode temp = codes[i];
//		DAGNode tempNode;
//		if (temp.op == "printf") {
//			if (!name2Index.count(temp.z)) {
//				DAGMap.push_back(DAGNode(temp.z, DAGMap.size()));						// 在DAG图中加入temp.z
//				name2Index.insert(make_pair(temp.z, DAGMap.size() - 1));		// 向节点表中加入temp.z
//				if (!isNum(temp.z) && temp.z[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.setX(temp.x);
//			tempNode.setY(temp.y);
//			tempNode.leftSon = name2Index[temp.z];
//			DAGMap.push_back(tempNode);
//		}
//		else if (temp.op == "+" || temp.op == "-" || temp.op == "*" || temp.op == "/") {
//			if (!name2Index.count(temp.x)) {
//				DAGMap.push_back(DAGNode(temp.x, DAGMap.size()));
//				name2Index.insert(make_pair(temp.x, DAGMap.size() - 1));
//				if (!isNum(temp.x) && temp.x[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			if (!name2Index.count(temp.y)) {
//				DAGMap.push_back(DAGNode(temp.y, DAGMap.size()));
//				name2Index.insert(make_pair(temp.y, DAGMap.size() - 1));
//				if (!isNum(temp.y) && temp.x[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//
//			if (temp.z[temp.z.size() - 1] == ']') {
//
//			}
//
//			int k = -1;
//			for (int j = 0; j < DAGMap.size(); j++) {
//				if (DAGMap[j].signal == temp.op && DAGMap[j].leftSon == name2Index[temp.x] && DAGMap[j].rightSon == name2Index[temp.y]) {
//					k = j;
//					break;
//				}
//			}
//			if (k == -1) {
//				tempNode = DAGNode(temp.z, DAGMap.size());
//				tempNode.leftSon = name2Index[temp.x];
//				tempNode.rightSon = name2Index[temp.y];
//				tempNode.signal = temp.op;
//				k = tempNode.index;
//				DAGMap.push_back(tempNode);
//			}
//			if (name2Index.count(temp.z)) {
//				name2Index[temp.z] = k;
//			}
//			else {
//				name2Index.insert(make_pair(temp.z, k));
//			}
//		}
//		else if (temp.op == "=") {
//			if (!name2Index.count(temp.y)) {
//				DAGMap.push_back(DAGNode(temp.y, DAGMap.size()));
//				name2Index.insert(make_pair(temp.y, DAGMap.size() - 1));
//				if (!isNum(temp.y) && temp.y[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			if (!name2Index.count(temp.x)) {
//				name2Index.insert(make_pair(temp.x, name2Index[temp.y]));
//			}
//			else {
//				name2Index[temp.x] = name2Index[temp.y];
//			}
//		}
//		else if (temp.op == "scanf") {
//			if (!name2Index.count(temp.y)) {
//				DAGMap.push_back(DAGNode(temp.y, DAGMap.size()));
//				name2Index.insert(make_pair(temp.y, DAGMap.size() - 1));
//				if (!isNum(temp.y) && temp.y[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.setX(temp.x);
//			tempNode.setY("");
//			tempNode.leftSon = name2Index[temp.y];
//			DAGMap.push_back(tempNode);
//		}
//		else if (temp.op == "cmp") {
//			if (!name2Index.count(temp.x)) {
//				DAGMap.push_back(DAGNode(temp.x, DAGMap.size()));
//				name2Index.insert(make_pair(temp.x, DAGMap.size() - 1));
//				if (!isNum(temp.x) && temp.x[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			if (!name2Index.count(temp.y)) {
//				DAGMap.push_back(DAGNode(temp.y, DAGMap.size()));
//				name2Index.insert(make_pair(temp.y, DAGMap.size() - 1));
//				if (!isNum(temp.y) && temp.y[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.setX("");
//			tempNode.setY(temp.y);
//			tempNode.leftSon = name2Index[temp.x];
//			tempNode.rightSon = name2Index[temp.z];
//			DAGMap.push_back(tempNode);
//		}
//		else if (temp.op == "push") {
//			if (!name2Index.count(temp.x)) {
//				DAGMap.push_back(DAGNode(temp.x, DAGMap.size()));
//				name2Index.insert(make_pair(temp.x, DAGMap.size() - 1));
//				if (!isNum(temp.x) && temp.x[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.leftSon = name2Index[temp.x];
//			DAGMap.push_back(tempNode);
//		}
//		else if (temp.op == "return") {
//			if (!name2Index.count(temp.x)) {
//				DAGMap.push_back(DAGNode(temp.x, DAGMap.size()));
//				name2Index.insert(make_pair(temp.x, DAGMap.size() - 1));
//				if (!isNum(temp.x) && temp.x[0] != '\'') {
//					DAGMap.back().signal = "#0#" + DAGMap.back().mainname;
//				}
//			}
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.leftSon = name2Index[temp.x];
//			tempNode.setY(temp.y);
//			DAGMap.push_back(tempNode);
//		}
//		else if (temp.op == "use" || temp.op == "BZ" || temp.op == "BNZ" || temp.op == "label" || temp.op == "GOTO") {
//			tempNode = DAGNode(temp.op, DAGMap.size());
//			tempNode.setX(temp.x);
//		}
//	}
//}
//
//void buildDAG(vector<MidCode> codes) {
//
//}