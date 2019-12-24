#include "DAG.h"
#include "Optimizer.h"
#include "Class.h"

vector<int> flag;

void DAGActive() {
	extern map<int, BasicBlock> num2Block;
	extern map<string, vector<int>> funcName2Nums;
	map<int, BasicBlock> temp;
	vector<int> nums;
	for (map<string, vector<int>>::iterator iter_1 = funcName2Nums.begin(); iter_1 != funcName2Nums.end(); iter_1++) {
		nums = iter_1->second;
		for (int j = 0; j < nums.size(); j++) {
			temp[nums[j]] = DAGOptimizer(num2Block[nums[j]]);
		}
	}

	num2Block.clear();
	for (map<int, BasicBlock>::iterator iter = temp.begin(); iter != temp.end(); iter++) {
		num2Block[iter->first] = iter->second;
	}
}

bool find(vector<string> strs, string str) {
	for (int i = 0; i < strs.size(); i++) {
		if (strs[i] == str) return true;
	}
	return false;
}

BasicBlock DAGOptimizer(BasicBlock block) {
	map<string, int>name2Index;
	vector<DAGNode> graph;

	for (int i = 0; i < block.midCodes.size(); i++) {
		MidCode temp = block.midCodes[i];
		if (temp.op == "=") {										// 赋值，直接将x在节点表内指向y的index
			if (name2Index.find(temp.y) == name2Index.end()) {
				name2Index.insert(make_pair(temp.y, graph.size()));
				graph.push_back(DAGNode(temp.y));
			}
			if (name2Index.find(temp.x) != name2Index.end()) {
				if (graph[name2Index[temp.x]].mainName == temp.x) {
					graph[name2Index[temp.x]].flag = true;
				}
			}
			name2Index[temp.x] = name2Index[temp.y];
			graph[name2Index[temp.x]].flag = false;
		}
		else if (isOp(temp) || temp.op == "[]" || temp.op == "[]=") {					// 运算，首先得到x 和 y的index，若不在节点表内则建点
			if (name2Index.find(temp.x) == name2Index.end()) {
				name2Index.insert(make_pair(temp.x, graph.size()));
				graph.push_back(DAGNode(temp.x));
			}
			if (name2Index.find(temp.y) == name2Index.end()) {
				name2Index.insert(make_pair(temp.y, graph.size()));
				graph.push_back(DAGNode(temp.y));
			}
			int index = -1;
			for (int j = 0; j < graph.size(); j++) {
				if (graph[j].name == temp.op
					&& graph[j].leftSon == name2Index[temp.x]
					&& graph[j].rightSon == name2Index[temp.y]) {
					index = j;
					break;
				}
			}
			if (name2Index.find(temp.z) != name2Index.end()) {
				if (graph[name2Index[temp.z]].mainName == temp.z) {
					graph[name2Index[temp.z]].flag = true;
				}
			}
			if (index == -1 || graph[index].name == "[]=") {
				graph.push_back(DAGNode(temp.op));
				graph.back().mainName = temp.z;
				graph.back().leftSon = name2Index[temp.x];
				graph.back().rightSon = name2Index[temp.y];
				name2Index[temp.z] = graph.size() - 1;
			}
			else {
				if (graph[index].flag == true || find(block.outVars, temp.z)) {
					graph[index].mainName = temp.z;
					graph[index].flag = false;
				}
				name2Index[temp.z] = index;
			}
		}
		else if (temp.op == "cmp") {
			if (name2Index.find(temp.x) == name2Index.end()) {
				name2Index.insert(make_pair(temp.x, graph.size()));
				graph.push_back(DAGNode(temp.x));
			}
			if (name2Index.find(temp.z) == name2Index.end()) {
				name2Index.insert(make_pair(temp.z, graph.size()));
				graph.push_back(DAGNode(temp.z));
			}
			graph.push_back(DAGNode(temp));
			graph.back().leftSon = name2Index[temp.x];
			graph.back().rightSon = name2Index[temp.z];
		}
		else if (temp.op == "printf") {
			if (name2Index.find(temp.z) == name2Index.end()) {
				name2Index.insert(make_pair(temp.z, graph.size()));
				graph.push_back(DAGNode(temp.z));
			}
			graph.push_back(DAGNode(temp.op));
			graph.back().x = temp.x;
			graph.back().y = temp.y;
			graph.back().leftSon = name2Index[temp.z];
		}
		else if (temp.op == "push") {
			if (name2Index.find(temp.x) == name2Index.end()) {
				name2Index.insert(make_pair(temp.x, graph.size()));
				graph.push_back(DAGNode(temp.x));
			}
			graph.push_back(DAGNode(temp.op));
			graph.back().leftSon = name2Index[temp.x];
		}
		else if (temp.op == "scanf") {
			if (name2Index.find(temp.y) != name2Index.end()) {
				if (graph[name2Index[temp.y]].mainName == temp.y) {
					graph[name2Index[temp.y]].flag = true;
				}
			}
			graph.push_back(DAGNode(temp));
			graph.back().mainName = temp.y;
			name2Index[temp.y] = graph.size() - 1;
		}
		else if (temp.op == "return") {
			if (name2Index.find(temp.x) == name2Index.end()) {
				name2Index.insert(make_pair(temp.x, graph.size()));
				graph.push_back(DAGNode(temp.x));
			}
			graph.push_back(DAGNode(temp));
			graph.back().leftSon = name2Index[temp.x];
		}
		else {
			graph.push_back(DAGNode(temp));
		}
	}

	flag.clear();
	for (int i = 0; i < graph.size(); i++) {
		flag.push_back(0);
	}

	return exportCode(name2Index, graph, block);
}

void DFS(vector<DAGNode> graph, int num) {
	if (num == -1) {
		return;
	}
	else if (flag[num] == 1) {
		return;
	}
	flag[num] = 1;
	DFS(graph, graph[num].leftSon);
	DFS(graph, graph[num].rightSon);
	return;
}

BasicBlock exportCode(map<string, int> name2Index, vector<DAGNode> graph, BasicBlock tempBlock) {
	BasicBlock block;
	for (map<string, int>::iterator iter = name2Index.begin(); iter != name2Index.end(); iter++) {
		if (find(tempBlock.outVars, iter->first) || iter->first.substr(0, 8) == "_GLOBAL_") {
			DFS(graph, iter->second);
		}
	}

	for (int i = 0; i < graph.size(); i++) {
//		cout << i << endl;
		DAGNode temp = graph[i];
		//if (flag[i] == 0) {
		//	continue;
		//}
		if (temp.name == "printf") {
			block.addMidCode(MidCode(temp.name, temp.x, temp.y, graph[temp.leftSon].mainName));
		}
		else if (temp.name == "+" || temp.name == "-" || temp.name == "*"
			|| temp.name == "/" || temp.name == "[]" || temp.name == "[]=") {
			block.addMidCode(MidCode(temp.name, graph[temp.leftSon].mainName, graph[temp.rightSon].mainName, temp.mainName));
		}
		else if (temp.name == "push") {
			block.addMidCode(MidCode(temp.name, graph[temp.leftSon].mainName, "", ""));
		}
		else if (temp.name == "return") {
			block.addMidCode(MidCode(temp.name, graph[temp.leftSon].mainName, temp.mid.y, temp.mid.z));
		}
		else if (temp.name == "cmp") {
			block.addMidCode(MidCode(temp.name, graph[temp.leftSon].mainName, temp.mid.y, graph[temp.rightSon].mainName));
		}
		else if (isNum(temp.name) || temp.name[0] == '\'') {

		} 
		else if (graph[i].leftSon == -1 && graph[i].rightSon == -1 && graph[i].mid.op == "") {

		}
		else {
			block.addMidCode(temp.mid);
		}

		for (int j = 0; j < tempBlock.outVars.size(); j++) {
			if (name2Index.find(tempBlock.outVars[j]) != name2Index.end() && name2Index[tempBlock.outVars[j]] == i
				&& tempBlock.outVars[j] != temp.mainName) {
				block.addMidCode(MidCode("=", tempBlock.outVars[j], temp.mainName, ""));
			}
		}
		
		for (map<string, int>::iterator iter = name2Index.begin(); iter != name2Index.end(); iter++) {
			if (iter->first.substr(0, 8) == "_GLOBAL_" && i == iter->second && iter->first != temp.mainName) {
				block.addMidCode(MidCode("=", iter->first, temp.mainName, ""));
			}
		}
	}

	return block;
}

