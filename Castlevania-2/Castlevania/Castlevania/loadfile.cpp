#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>
#include "loadfile.h"
#include "Camera.h"
#include "QuadTree.h"
#include "GameObject.h"

using namespace std;

vector<string> loadLink(char* filename)
{
	vector<string> temp;
	temp.clear();
	ifstream fileStream(filename);
	if (fileStream.is_open())
		while (!fileStream.eof())
		{
			string line;
			getline(fileStream, line);
			temp.push_back(line);
		}
	return temp;
}

Id::Id(int id, int type)
{
	_Id = id;
	_Type = type;
}

int Id::getId()
{
	return _Id;
}

int Id::getType()
{
	return _Type;
}

void Id::set(int id, int type)
{
	_Id = id;
	_Type = type;
} 

void Id::setId(int id)
{
	_Id = id;
}

void Id::setType(int type)
{
	_Type = type;
}

int clip(TreeObject obj, QNode node)
{
	bool	LEFT = false,
		RIGHT = false,
		TOP = false,
		BOTTOM = false;
	if (obj.x0 < node.x0)
	{
		obj.x0 = node.x0;
		LEFT = true;
	}
	else
	if (obj.x0 < node.x1)
		LEFT = true;
	if (obj.x1 > node.x1)
	{
		obj.x1 = node.x1;
		RIGHT = true;
	}
	else
	if ((obj.x1> node.x0))
		RIGHT = true;


	if (obj.y0 < node.y0)
	{
		obj.y0 = node.y0;
		TOP = true;
	}
	else
	if (obj.y0 < node.y1)
		TOP = true;

	if (obj.y1 > node.y1)
	{
		obj.y1 = node.y1;
		BOTTOM = true;
	}
	else
	if (obj.y1 > node.y0)
		BOTTOM = true;

	if (LEFT && RIGHT && TOP && BOTTOM && (obj.x1 - obj.x0 > 0) && (obj.y1 - obj.y0 > 0))
		return node.NodeID;
	return -1;
}

LoadFile::LoadFile()
{
	rows = 0;
}

LoadFile::~LoadFile()
{
}

int LoadFile::getType(int id)
{
	return _DirectGetType[id];
}

void LoadFile::Load(char* filepath)
{
	ReadfileMatrix(filepath);
	filepath[strlen(filepath) - 1] = 'o';
	Readfile(filepath);
}

void LoadFile::GetNodeIDObject(Box simonbox)
{
	renderingObject.clear();
	collidingObject.clear();
	bgObject.clear();
	CameraObject.x0 = cmr.pos.x;
	CameraObject.y0 = cmr.pos.y - SCREENHEIGHT;
	CameraObject.x1 = cmr.pos.x + SCREENWIDTH;
	CameraObject.y1 = cmr.pos.y;

	SimonObject.x0 = simonbox.x;
	SimonObject.x1 = simonbox.x + simonbox.w;
	SimonObject.y0 = simonbox.y;
	SimonObject.y1 = simonbox.y + simonbox.h;

	LoadList(root2);
	LoadBackGround(root3);
}

void LoadFile::BuildTree3(QNodeOptimize* n)
{
	if (stlmap3.find(n->NodeID) != stlmap3.end())
	{
		for (int i = 0; i < stlmap3[n->NodeID].ObjectId.size(); i++)
		{
			int id = stlmap3[n->NodeID].ObjectId.at(i);
			n->ObjectId.push_back(id);
		}
		n->lt = new QNodeOptimize(n->x0, n->y0, n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2);
		n->rt = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0, n->x1, n->y0 + (n->y1 - n->y0) / 2);
		n->lb = new QNodeOptimize(n->x0, n->y0 + (n->y1 - n->y0) / 2, n->x0 + (n->x1 - n->x0) / 2, n->y1);
		n->rb = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2, n->x1, n->y1);

		n->lt->NodeID = n->NodeID * 4 + 1;
		n->rt->NodeID = n->NodeID * 4 + 2;
		n->lb->NodeID = n->NodeID * 4 + 3;
		n->rb->NodeID = n->NodeID * 4 + 4;

		BuildTree3(n->lt);
		BuildTree3(n->rt);
		BuildTree3(n->lb);
		BuildTree3(n->rb);
	}
}

void LoadFile::BuildTree(QNodeOptimize* n)
{
	if (stlmap.find(n->NodeID) != stlmap.end())
	{
		for (int i = 0; i < stlmap[n->NodeID].ObjectId.size(); i++)
		{
			int id = stlmap[n->NodeID].ObjectId.at(i);
			n->ObjectId.push_back(id);
		}
		n->lt = new QNodeOptimize(n->x0, n->y0, n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2);
		n->rt = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0, n->x1, n->y0 + (n->y1 - n->y0) / 2);
		n->lb = new QNodeOptimize(n->x0, n->y0 + (n->y1 - n->y0) / 2, n->x0 + (n->x1 - n->x0) / 2, n->y1);
		n->rb = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2, n->x1, n->y1);

		n->lt->NodeID = n->NodeID * 4 + 1;
		n->rt->NodeID = n->NodeID * 4 + 2;
		n->lb->NodeID = n->NodeID * 4 + 3;
		n->rb->NodeID = n->NodeID * 4 + 4;

		BuildTree(n->lt);
		BuildTree(n->rt);
		BuildTree(n->lb);
		BuildTree(n->rb);
	}
}

void LoadFile::BuildTree2(QNodeOptimize* n)
{
	if (stlmap2.find(n->NodeID) != stlmap2.end())
	{
		for (int i = 0; i < stlmap2[n->NodeID].ObjectId.size(); i++)
		{
			int id = stlmap2[n->NodeID].ObjectId.at(i);
			n->ObjectId.push_back(id);
		}
		n->lt = new QNodeOptimize(n->x0, n->y0, n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2);
		n->rt = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0, n->x1, n->y0 + (n->y1 - n->y0) / 2);
		n->lb = new QNodeOptimize(n->x0, n->y0 + (n->y1 - n->y0) / 2, n->x0 + (n->x1 - n->x0) / 2, n->y1);
		n->rb = new QNodeOptimize(n->x0 + (n->x1 - n->x0) / 2, n->y0 + (n->y1 - n->y0) / 2, n->x1, n->y1);

		n->lt->NodeID = n->NodeID * 4 + 1;
		n->rt->NodeID = n->NodeID * 4 + 2;
		n->lb->NodeID = n->NodeID * 4 + 3;
		n->rb->NodeID = n->NodeID * 4 + 4;

		BuildTree2(n->lt);
		BuildTree2(n->rt);
		BuildTree2(n->lb);
		BuildTree2(n->rb);
	}
}

void LoadFile::LoadBackGround(QNodeOptimize *n)
{
	if (isCliped(CameraObject, n))
	{
		if (n->ObjectId.size() != 0)
			bgObject.insert(n->ObjectId.begin(), n->ObjectId.end());
		if (n->lt != NULL)
			LoadBackGround(n->lt);
		if (n->lb != NULL)
			LoadBackGround(n->lb);
		if (n->rt != NULL)
			LoadBackGround(n->rt);
		if (n->rb != NULL)
			LoadBackGround(n->rb);
	}
}

void LoadFile::LoadList(QNodeOptimize *n)
{
	bool moreleaf = true;
	if (n->x1 - n->x0 >= 515 * 5 / 8)
		moreleaf = false;

	if ((isCliped(CameraObject, n) && !moreleaf)
		|| (isCliped(SimonObject, n) && moreleaf))
	{
		for (int i = 0; i < deadobject.size(); i++)
		{
			for (int j = 0; j < n->ObjectId.size(); j++)
			if (deadobject.at(i) == n->ObjectId.at(j))
			{
				n->ObjectId.erase(n->ObjectId.begin() + j);
				deadobject.erase(deadobject.begin() + i);//chua xoa vi con cay collision chua xoa
				break;
			}
		}
		if (quickfindstlmap[n->NodeID] == 1)
		{
			for (int i = 0; i < deadobject.size(); i++)
			{
				for (int j = 0; j < stlmap[n->NodeID].ObjectId.size(); j++)
				if (deadobject.at(i) == stlmap[n->NodeID].ObjectId.at(j))
				{
					stlmap[n->NodeID].ObjectId.erase(stlmap[n->NodeID].ObjectId.begin() + j);
					break;
				}
				
			}
		}

		if (n->ObjectId.size()	!= 0)
			collidingObject.insert(n->ObjectId.begin(), n->ObjectId.end());

		if (!moreleaf)
		{
			if (quickfindstlmap[n->NodeID] == 1 && stlmap[n->NodeID].ObjectId.size() != 0)
			{
				renderingObject.insert(stlmap[n->NodeID].ObjectId.begin(), stlmap[n->NodeID].ObjectId.end());
			}
		}

		if (n->lt != NULL)
			LoadList(n->lt);
		if (n->lb != NULL)
			LoadList(n->lb);
		if (n->rt != NULL)
			LoadList(n->rt);
		if (n->rb != NULL)
			LoadList(n->rb);
	}
}

void LoadFile::GetNodeOtherIDObject(Box bx)
{
	othercollidingObject.clear();

	otherObject.x0 = bx.x;
	otherObject.x1 = bx.x + bx.w;
	otherObject.y0 = bx.y;
	otherObject.y1 = bx.y + bx.h;

	LoadList2(root2);
}

void LoadFile::LoadList2(QNodeOptimize *n)
{
	if (isCliped(otherObject, n))
	{
		if (n->ObjectId.size() != 0)
			othercollidingObject.insert(n->ObjectId.begin(), n->ObjectId.end());

		if (n->lt != NULL)
			LoadList(n->lt);
		if (n->lb != NULL)
			LoadList(n->lb);
		if (n->rt != NULL)
			LoadList(n->rt);
		if (n->rb != NULL)
			LoadList(n->rb);
	}
}

void LoadFile::ReadfileMatrix(char* filepath)
{
	rows = 0; 
	_DirectGetType.clear();
	stlmap3.clear();
	quickfindstlmap3.clear();
	backGroundObject.clear();
	bgObject.clear();
	ifstream fileStream(filepath);
	int Section = 0;
	if (fileStream.is_open())
	{
		int id = 1;
		while (!fileStream.eof())
		{
			if (Section == 0)
			{
				string line;
				getline(fileStream, line);
				if (line != "END")
				{
					istringstream iss(line);
					string sub;
					int space = 0;
					for (int i = 0; i < line.length(); i++)
						if (line[i] == ' ')
							space++;
					int	currentcolumns = 0;
					for (int i = 0; i < space; i++)
					{
						id++;
						iss >> sub;
						GameObject GO;
						GO.id = id;
						GO.type = stoi(sub);
						GO.x0 = currentcolumns * 64;
						GO.y0 = (6 - rows) * 64;
						_DirectGetType[GO.id] = GO.type;
						backGroundObject.push_back(GO);
						currentcolumns++;
					}
					rows++;
				}
				else
					Section = 1;
			}

			if (Section == 1)
			{
				vector<string> str;
				string line;
				int space = 0;
				getline(fileStream, line);
				if (line != "END")
				{
					for (int i = 0; i < (int)line.length(); i++)
						if (line[i] == ' ')
							space++;
					istringstream iss(line);
					string sub;
					for (int i = 0; i < space; i++)
					{
						iss >> sub;
						str.push_back(sub);
					}
					QNodeOptimize QN;
					QN.NodeID = stoi(str.at(0));
					QN.x0 = stoi(str.at(1));
					QN.y0 = stoi(str.at(2));
					QN.x1 = stoi(str.at(3));
					QN.y1 = stoi(str.at(4));
					for (int i = 5; i < (int)str.size(); i++)
					{
						
						int id = stoi(str.at(i));
						QN.ObjectId.push_back(id);
					}
					stlmap3[stoi(str.at(0))] = QN;
					quickfindstlmap3[stoi(str.at(0))] = 1;
				}

			}
		}
	}
	root3 = &stlmap3[0];
	if (root3->ObjectId.size()==0)
		BuildTree3(root3);
	int x = 0;
}

void LoadFile::deleteObject(int id)
{
	deadobject.push_back(id);
}

void LoadFile::Readfile(char* filepath)
{
	//rows = 0;
	_DirectGetType.clear();
	stlmap.clear();
	stlmap2.clear();
	quickfindstlmap.clear();
	quickfindstlmap2.clear();
	gameObject.clear();
	ifstream fileStream(filepath);
	string data;
	int tick = 0;
	GameObject GO;
	int Section = 0;
	if ( fileStream.is_open())
	{
		while(!fileStream.eof())
		{
			if(Section == 0)
			{
				char c = fileStream.get();
				data += c;
				if(data!="END")
				{
					if(c==' ')
					{
						switch(++tick)
						{
						case 1:
							GO.id = stoi(data);
							break;
						case 2:
							GO.type = stoi(data);
							break;
						case 3:
							GO.flip = stoi(data);
							break;
						case 4:
							GO.x0 = (float)stoi(data);
							break;
						case 5:
							GO.y0 = (float)stoi(data);
							break;
						case 6:
							GO.x1 = (float)stoi(data);
							break;
						case 7:
							GO.y1 = (float)stoi(data);
							tick = 0;
							gameObject.push_back(GO);
							_DirectGetType[GO.id] = GO.type;
							break;
						}
						data="";
					}
				}
				else {
					Section = 1;
					for (int i = 0; i < 1; i++)
						char c = fileStream.get();
				}
				if(data == "\n")
					data = "";
			}
			if (Section == 1)
			{
				vector<string> str;
				string line;
				int space = 0;
				getline(fileStream, line);
				if(line!="END")
				{
					for (int i = 0; i < (int)line.length(); i++)
						if(line[i]==' ')
							space++;
					istringstream iss(line);
					string sub;
					for (int i = 0; i < space; i++)
					{
						iss >> sub;
						str.push_back(sub);
					}
					QNodeOptimize QN;
					QN.NodeID	= stoi(str.at(0));
					QN.x0		= stoi(str.at(1));
					QN.y0		= stoi(str.at(2));
					QN.x1		= stoi(str.at(3));
					QN.y1		= stoi(str.at(4));
					for (int i = 5; i < (int)str.size(); i++)
					{
						int id = stoi(str.at(i));
						QN.ObjectId.push_back(id);
					}
					stlmap[stoi(str.at(0))] = QN;		
					quickfindstlmap[stoi(str.at(0))] = 1;
				}
				else
				{
					root = &stlmap[0];
					if (root->ObjectId.size() == 0)
						BuildTree(root);
					Section = 2;
				}
			
			}
			if (Section == 2)
			{
				vector<string> str;
				string line;
				int space = 0;
				getline(fileStream, line);
				if (line != "END")
				{
					for (int i = 0; i < (int)line.length(); i++)
					if (line[i] == ' ')
						space++;
					istringstream iss(line);
					string sub;
					for (int i = 0; i < space; i++)
					{
						iss >> sub;
						str.push_back(sub);
					}
					QNodeOptimize QN;
					QN.NodeID = stoi(str.at(0));
					QN.x0 = stoi(str.at(1));
					QN.y0 = stoi(str.at(2));
					QN.x1 = stoi(str.at(3));
					QN.y1 = stoi(str.at(4));
					for (int i = 5; i < (int)str.size(); i++)
					{

						int id = stoi(str.at(i));
						QN.ObjectId.push_back(id);
					}
					stlmap2[stoi(str.at(0))] = QN;
					quickfindstlmap2[stoi(str.at(0))] = 1;
				}
				else
				{
					root2 = &stlmap2[0];
					if (root2->ObjectId.size() == 0)
						BuildTree2(root2);
				}

			}
		}
	}
}

void LoadFile::readTxt(char* filepath)
{
	ifstream fileStream(filepath);
	string data;
	int tick = 0;
	GameObject GO;
	QNode QN;
	int Section = 0;
	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			vector<string> str;
			string line;
			getline(fileStream, line);
		}
	}
}