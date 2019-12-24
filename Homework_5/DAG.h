#pragma once
#include<vector>
#include<string>
#include<stdio.h>
#include<iostream>
#include<map>
using namespace std;

class MidCode;
class DAGNode;
class BasicBlock;

BasicBlock DAGOptimizer(BasicBlock block);
void DFS(vector<DAGNode> graph, int num);
BasicBlock exportCode(map<string, int> name2Index, vector<DAGNode> graph, BasicBlock tempBlock);
void DAGActive();
bool find(vector<string> strs, string str);