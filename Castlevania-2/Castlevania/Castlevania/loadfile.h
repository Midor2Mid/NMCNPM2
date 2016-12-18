#ifndef _LOADMAP_H
#define	_LOADMAP_H

#include	<iostream>
#include	<fstream>
#include	<string>
#include	<vector>
#include	<map>
#include	<unordered_set>

#include	"GameObject.h"
#include	"QuadTree.h"
#include	"sweptaabb.h"
#include	"game.h"
using namespace std;

extern vector<string> loadLink(char*);

class Id{
private:
	int _Id, _Type;
public:
	Id(int, int);
	int getId();
	int getType();
	void setId(int);
	void setType(int);
	void set(int, int);
};

class LoadFile
{
private:
	map<int, int>				_DirectGetType;
	map<int, QNodeOptimize>		stlmap;
	map<int, int>				quickfindstlmap;
	map<int, QNodeOptimize>		stlmap2;
	map<int, int>				quickfindstlmap2;
	map<int, QNodeOptimize>		stlmap3;	//stl map cho background;
	map<int, int>				quickfindstlmap3;

	TreeObject					CameraObject;
	TreeObject					SimonObject;
	TreeObject					otherObject;
public:
	unordered_set<int>					bgObject;
	unordered_set<int>					renderingObject;
	unordered_set<int>					collidingObject;
	unordered_set<int>					othercollidingObject;
	QNodeOptimize* root;
	QNodeOptimize* root2;
	QNodeOptimize* root3;
	void Load(char* filepath);
	LoadFile();
	~LoadFile();
	int					rows;
	vector<GameObject>	gameObject;
	vector<GameObject>  backGroundObject;
	vector<int>			deadobject;

	void				readTxt(char* filepath);
	void				Readfile(char* filepath);
	void				ReadfileMatrix(char* filepath);
	void				getLeafNode();
	void				GetNodeIDObject(Box simonbox);
	void				GetNodeOtherIDObject(Box otherbox);
	void				LoadList(QNodeOptimize* node);	
	void				LoadList2(QNodeOptimize* node);
	void				LoadBackGround(QNodeOptimize *n);
	int					getType(int id);
	void				BuildTree(QNodeOptimize* node);
	void				BuildTree2(QNodeOptimize* node);
	void				BuildTree3(QNodeOptimize* node);
	void				deleteObjectonTree(QNodeOptimize* node, int id);
	void				deleteObject(int);
	void				GetNodeIDOtherObject(Box other);
};

#endif // !_LOADGAME_H
