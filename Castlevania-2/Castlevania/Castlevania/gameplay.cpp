#include "gameplay.h"

CGamePlay::CGamePlay()
{
	level = 1;
	isloadsavinggame = false;
}

int CGamePlay::isActiveHolyCross()
{
	return isactiveholycross;
}

void CGamePlay::resetCamera()
{
	simonstage = ((64 * 6 - simon.getY()) / (64 * 6));

	if (simonstage < 0)
		simonstage = 0;
	else
	if (simonstage >= loadObject.rows / 6)
		simonstage = (loadObject.rows / 6) - 1;

	for (int i = 0; i < cameraMaxX.at(simonstage).size(); i++)
	if (simon.getX() < cameraMaxX.at(simonstage).at(i))
	{
		currentstage = i;
		cmr.setMaxMovingX(cameraMaxX.at(simonstage).at(i));
		break;
	}

	for (int i = cameraMinX.at(simonstage).size() - 1; i >= 0; i--)
	if (simon.getX() > cameraMinX.at(simonstage).at(i))
	{
		cmr.setMinMovingX(cameraMinX.at(simonstage).at(i));
		break;
	}
	cmr.pos.y = SCREENHEIGHT - (simonstage * 64 * 6 - 32);
	medusasub.clear();
}

void CGamePlay::initialize()
{
	blackboardpause.load("resource/image/blackboardpause.png", 1, 1);
	pausemenusprite.load("resource/image/paused.png", 1, 1);
	blackboardpause.setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	pausemenusprite.setPosition(SCREENWIDTH / 2, SCREENHEIGHT / 2);
	blackboardpause.setCamera(1);
	pausemenusprite.setCamera(1);
	blackboardpause.Color.setA(128);
	pausemenu = 0;
	pausemenuitem[0] = "Resume";
	pausemenuitem[1] = "Save";
	pausemenuitem[2] = "Exit";
	arialsmaller.initialize();
	arialbigger.initialize(32);
	currentchoosenpausedmenu = 0;
	
	isExit = 0;
	isactiveholycross = false;
	timeregainperhealth = 20;
	currenttimeregainperhealth = 0; 
	timewaitingfornextlevel = 5000;

	arial.initialize();
	gameboard.load("resource/image/blackboard.png", 1, 1);
	gameboard.setCamera(1);
	gameboard.setPosition(SCREENWIDTH / 2, SCREENHEIGHT - gameboard.getHeight() / 2);
	simon.load("resource/image/simon.png", 8, 3);
	
	healthbar.load("resource/image/heal.png", 90, 50);
	snake.load("resource/image/boss/2.png", 2, 1);

	//thiet lap hien thi secondary weapon
	SecondaryWeapon[0].load("resource/image/item/4.png", 1, 1);
	SecondaryWeapon[1].load("resource/image/item/5.png", 1, 1);
	SecondaryWeapon[2].load("resource/image/item/7.png", 1, 1);
	SecondaryWeapon[3].load("resource/image/item/8.png", 1, 1);
	SecondaryWeapon[4].load("resource/image/item/9.png", 1, 1);

	SecondaryWeaponLimit[0].load("resource/image/item/11-2.png", 1, 1);
	SecondaryWeaponLimit[1].load("resource/image/item/12-2.png", 1, 1);

	//hinh thi loai vu khi thu 2 tren bang dieu khien
	for (int i = 0; i < 5; i++)
	{
		SecondaryWeapon[i].setPosition(342, 402);
		//chon camera dung yen
		SecondaryWeapon[i].setCamera(1);
	}
	
	for (int i = 0; i < 2; i++)
	{
		SecondaryWeaponLimit[i].setPosition(480, 380);
		//chon camera dung yen
		SecondaryWeaponLimit[i].setCamera(1);
	}

	LoadMap();

	//tao checkpoint
	simon.CreateCheckPoint();

	//load hieu ung
	additionallink = loadLink("resource/link4.txt");
	sprite.load((char*)additionallink.at(0).c_str(), 1, 1);
	sprite2.load((char*)additionallink.at(1).c_str(), 3, 1);

	//load cac item
	itemlink = loadLink("resource/items.txt");
	itemsprite[0].load((char*)itemlink.at(0).c_str(), 1, 1, 0);
	itemsprite[1].load((char*)itemlink.at(1).c_str(), 1, 1, 1);
	itemsprite[2].load((char*)itemlink.at(2).c_str(), 3, 1, 2);
	itemsprite[3].load((char*)itemlink.at(3).c_str(), 1, 1, 3);
	itemsprite[4].load((char*)itemlink.at(4).c_str(), 1, 1, 4);
	itemsprite[5].load((char*)itemlink.at(5).c_str(), 1, 1, 5);
	itemsprite[6].load((char*)itemlink.at(6).c_str(), 1, 1, 6);
	itemsprite[7].load((char*)itemlink.at(7).c_str(), 1, 1, 7);
	itemsprite[8].load((char*)itemlink.at(8).c_str(), 1, 1, 8);
	itemsprite[9].load((char*)itemlink.at(9).c_str(), 1, 1, 9);
	itemsprite[10].load((char*)itemlink.at(10).c_str(), 1, 1, 10);
	itemsprite[11].load((char*)itemlink.at(11).c_str(), 1, 1, 11);
	itemsprite[12].load((char*)itemlink.at(12).c_str(), 1, 1, 12);
	itemsprite[13].load((char*)itemlink.at(13).c_str(), 2, 1, 13);
	itemsprite[13].animate(20, 0, 1);

	//load sound
	holycross	= LoadSound("resource/sound/holycross.wav");
	holywater	= LoadSound("resource/sound/holywater.wav");
	hitmonster	= LoadSound("resource/sound/hit.wav");
	hitcannon	= LoadSound("resource/sound/hitcannon.wav");
	collectitem = LoadSound("resource/sound/collectitem.wav");
	weaponcollect = LoadSound("resource/sound/collectweapon.wav");
	bossmusic	= LoadSound("resource/music/Boss_Battle_Poison_Mind.wav");
	clearstage = LoadSound("resource/music/Stage_Clear.wav");
	deathsound = LoadSound("resource/music/Life_Lost.wav");
	opendoorsound = LoadSound("resource/sound/opendoor.wav");
	fallingsound = LoadSound("resource/sound/falling.wav");
	decreaseweaponusepointsound = LoadSound("resource/sound/decreaseweaponusepoint.wav");
	fallingdownwatersurface = LoadSound("resource/sound/fallingdownwatersurface.wav");
}

void CGamePlay::changecamera(int delta)
{
	if (simon._OnLadder)
	{
#pragma region
		if (simon.GetStepOnLadderDirection() == 0 || simon.GetStepOnLadderDirection() == 2)
		if (simon.getBox().y + simon.getBox().h > cmr.pos.y - SCREENHEIGHT + 64 * 6 )
		{
			simon.tranferY(64);
			simonstage--;
			if (simonstage < 0)
				simonstage = 0;
			else
			if (simonstage >= loadObject.rows / 6)
				simonstage = (loadObject.rows / 6) - 1;

			for (int i = 0; i < cameraMaxX.at(simonstage).size(); i++)
				if (simon.getX() < cameraMaxX.at(simonstage).at(i))
				{
					cmr.setMaxMovingX(cameraMaxX.at(simonstage).at(i));
					break;
				}

			for (int i = cameraMinX.at(simonstage).size() - 1; i >= 0; i--)
			if (simon.getX() > cameraMinX.at(simonstage).at(i))
			{
				cmr.setMinMovingX(cameraMinX.at(simonstage).at(i) - 16);
				currentstage = i;
				break;
			}
			cmr.pos.y = SCREENHEIGHT - (simonstage * 64 * 6 - 32);
		}
#pragma endregion chuyen camera len tren
		
#pragma region
		if (simon.GetStepOnLadderDirection() == 1 || simon.GetStepOnLadderDirection() == 3)
		if (simon.getBox().y < cmr.pos.y - SCREENHEIGHT)
		{
			simon.tranferY(-64);
			simonstage++;
			if (simonstage < 0)
				simonstage = 0;

			for (int i = 0; i < cameraMaxX.at(simonstage).size(); i++)
			if (simon.getX() < cameraMaxX.at(simonstage).at(i))
			{
				cmr.setMaxMovingX(cameraMaxX.at(simonstage).at(i));
				break;
			}

			for (int i = 0; i < cameraMinX.at(simonstage).size(); i++)
			if (simon.getX() > cameraMinX.at(simonstage).at(i))
			{
				cmr.setMinMovingX(cameraMinX.at(simonstage).at(i) - 16);
				break;
			}
			cmr.pos.y = SCREENHEIGHT - (simonstage * 64 * 6 - 32);
		}
#pragma endregion chuyen camera xuong
	}
	else
	{
		if (!simon.death)
		{
			if (simon.getBox().y < cmr.pos.y - SCREENHEIGHT)
			{
				simon.death = true;
				simon.HealthPoint = -1;
				if (levelmusic != NULL)
					StopSound(levelmusic);
				PlaySound(deathsound);
			}
		}
	}
}

void CGamePlay::GeneratingItem(Box DestroyedObject)
{
	int randomresult = rand() % 260;
	if (simon.PrimaryWeapon == 2)//neu roi cua simon dai
	{
#pragma region
		if (randomresult < 130)
		{
			itemsprite[0].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[0]);
		}
		else
		if (randomresult < 160)
		{
			itemsprite[1].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[1]);
		}
		else
		if (randomresult <= 200)
		{
			itemsprite[2].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			itemsprite[2].animate(false);
			int moneybagvalue = rand() % 10;
			if (moneybagvalue <= 7)
			{
				itemsprite[2].setCurrentFrame(0);
			}
			else
			if (moneybagvalue <= 9)
			{
				itemsprite[2].setCurrentFrame(1);
			}
			else
			if (moneybagvalue <= 10)
			{
				itemsprite[2].setCurrentFrame(2);
			}
			Item.push_back(itemsprite[2]);
		}
		else
		if (randomresult <= 206)
		{
			itemsprite[4].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[4]);
		}
		else
		if (randomresult <= 212)
		{
			itemsprite[5].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[5]);
		}
		else
		if (randomresult <= 218)
		{
			itemsprite[6].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[6]);
		}
		else
		if (randomresult <= 224)
		{
			itemsprite[7].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[7]);
		}
		else
		if (randomresult <= 230)
		{
			itemsprite[8].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[8]);
		}
		else
		if (randomresult <= 236)
		{
			itemsprite[9].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[9]);
		}
		else
		if (randomresult <= 242)
		{
			itemsprite[10].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[10]);
		}
		else
		if (randomresult <= 246)
		{
			itemsprite[11].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[11]);
		}
		else
		if (randomresult <= 250)
		{
			itemsprite[12].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
			Item.push_back(itemsprite[12]);
		}
#pragma endregion ti le roi do cua simon khi roi dai
	}
	else
	{
#pragma region
		if (simon.PrimaryWeapon < 2)//neu roi cua simon ngan
		{
			if (randomresult < 160)
			{
				itemsprite[3].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[3]);
			}
			else
			if (randomresult < 190)
			{
				itemsprite[0].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[0]);
			}
			else
			if (randomresult <= 215)
			{
				itemsprite[1].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[1]);
			}
			else
			if (randomresult <= 230)
			{
				itemsprite[2].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				itemsprite[2].animate(false);
				int moneybagvalue = rand() % 10;
				if (moneybagvalue <= 7)
				{
					itemsprite[2].setCurrentFrame(0);
				}
				else
				if (moneybagvalue <= 9)
				{
					itemsprite[2].setCurrentFrame(1);
				}
				else
				if (moneybagvalue <= 10)
				{
					itemsprite[2].setCurrentFrame(2);
				}
				Item.push_back(itemsprite[2]);
			}
			else
			if (randomresult <= 233)
			{
				itemsprite[4].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[4]);
			}
			else
			if (randomresult <= 236)
			{
				itemsprite[5].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[5]);
			}
			else
			if (randomresult <= 239)
			{
				itemsprite[6].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[6]);
			}
			else
			if (randomresult <= 242)
			{
				itemsprite[7].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[7]);
			}
			else
			if (randomresult <= 245)
			{
				itemsprite[8].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[8]);
			}
			else
			if (randomresult <= 248)
			{
				itemsprite[9].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[9]);
			}
			else
			if (randomresult <= 251)
			{
				itemsprite[10].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[10]);
			}
			else
			if (randomresult <= 255)
			{
				itemsprite[11].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[11]);
			}
			else
			if (randomresult <= 259)
			{
				itemsprite[12].setPosition(DestroyedObject.x + DestroyedObject.w / 2, DestroyedObject.y + DestroyedObject.h / 2);
				Item.push_back(itemsprite[12]);
			}
		}
#pragma endregion ti le roi do khi roi ngan
	}
}

void CGamePlay::update(int delta)
{
	if (!pausemenu)
	{
	simon.reset();
	if (simon.nextlevel)
	{
		level++;
		LoadMap();
		simon.resetCharacterForNextLevel();
		simon.nextlevel = false;
	}
	else
	if (simon.isReset)
	{
		LoadMap();
		simon.ResetToCheckPoint();
		simon.resetCharacter();
		simon.isReset = false;
		resetCamera();
		if (bossmusic != NULL)
			StopSound(bossmusic);
	}

	changecamera(delta);
	Box simonbox = simon.getBox();
	loadObject.GetNodeIDObject(simonbox);
	{
		if (!onGate)
		{
#pragma region
			cmr.Update(simon.getX());
			int dimension;
			int dimension2;

#pragma region
			listActiveEnemies.clear();
			for (int i = 0; i < ListEnemies.size(); i++)
			{
				int id = ListEnemies.at(i);
				int type = _DirectGetType[id];
				{
						if (Object[type]->isActive(id) && Object[type]->isActive(id) != 100)
						{
							listActiveEnemies.push_back(id);
						}
						else
						if (Object[type]->isActive(id) == 100)
						{

							ListEnemies.erase(ListEnemies.begin() + i);
							i--;
						}
				}
			}
#pragma endregion check for active enemies

			for (unordered_set<int>::iterator it = loadObject.renderingObject.begin(); it != loadObject.renderingObject.end(); it++)
			{
				int id = *it;							//lay id cua vat the
				int type = loadObject.getType(id);		//lay loai vat the
				Box bx = Object[type]->getBox(id);
				switch (type)
				{
				case 10:
				case 11:
#pragma region
					//kiem tra va cham voi vu khi thu 2
					for (int n = 0; n < simon._Weapon.size(); n++)
					{
						Box bx2 = simon._Weapon.at(n).getBox();
						if (Collide(bx2, bx))
						{
							PlaySound(hitmonster);
							loadObject.deleteObject(id);

							if (simon._Weapon.at(n).getType() == 1)
								simon._Weapon.at(n).setStatus(100);

							//tao hieu ung danh trung
							int spritex, spritey;
							spritey = bx2.y;
							if (!simon.isFlip())
								spritex = bx.x + bx.w;
							else
								spritex = bx.x;
							sprite.setPosition(spritex, spritey);
							sprite.animate(true);
							sprite.animate(50, 0, 0);
							hit.push_back(sprite);

							//tao hieu ung chet
							int sprite2x, sprite2y;
							sprite2y = bx.y + bx.h / 2;
							sprite2x = bx.x + bx.w / 2;
							sprite2.setPosition(sprite2x, sprite2y);
							sprite2.animate(true);
							sprite2.animate(35, 0, 2);
							destroyflame.push_back(sprite2);
						}
					}

					if (simon.checkFightCollision())
					{
						Box bx2 = simon.getPrimaryBox();
						if (CollideCheck(bx2, bx))
						{
							PlaySound(hitmonster);
							//xoa doi tuong trong node
							loadObject.deleteObject(id);

							//tao hieu ung danh trung
							int spritex, spritey;
							spritey = bx2.y;
							if (!simon.isFlip())
								spritex = bx.x + bx.w;
							else
								spritex = bx.x;
							sprite.setPosition(spritex, spritey);
							sprite.animate(true);
							sprite.animate(50, 0, 0);
							hit.push_back(sprite);

							//tao hieu ung chet
							int sprite2x, sprite2y;
							sprite2y = bx.y + bx.h / 2;
							sprite2x = bx.x + bx.w / 2;
							sprite2.setPosition(sprite2x, sprite2y);
							sprite2.animate(true);
							sprite2.animate(35, 0, 2);
							destroyflame.push_back(sprite2);

							//tao item khi danh trung
							GeneratingItem(bx);
						}
					}
					Object[type]->update(delta, id);
#pragma endregion xu ly va cham voi cay nen
					break;
				case 12:
#pragma region
					dimension = Collide(simonbox, bx);
					if (dimension)
					{
						BoxCollision bxc(type, dimension, id, bx.x, bx.y, bx.w, bx.h);
						simon.ObjectCollided.push_back(bxc);
					}
#pragma region
					for (int k = 0; k < listActiveEnemies.size(); k++)
					{
						int id2 = listActiveEnemies.at(k);
						int type2 = _DirectGetType[id2];
						int isActive = Object[type2]->isActive(id2);
						Box bx2 = Object[type2]->getBox(id2);
						if (isActive)
						{
							switch (type2)
							{
							case 1:
							case 4:
							case 5:
								if (isActive == 2) // 2 la trang thai roi zombie
								{
									dimension2 = CollideCheck(bx2, bx);
									if (dimension2 == 3)
									{
										Object[type2]->setStatus(1, id2);
										if (simonbox.x + simonbox.w / 2 > bx2.x + bx2.w / 2)
										{
											Object[type2]->setFlip(1, id2);
										}
										else
											Object[type2]->setFlip(0, id2);
									}
								}
								break;
							case 2:
								if (isActive == 2) // 2 la trang thai roi cua con meo
								{
									dimension2 = CollideCheck(bx2, bx);
									if (dimension2 == 3)
									{
										Object[type2]->setStatus(1, id2);
										if (simonbox.x + simonbox.w / 2 > bx2.x + bx2.w / 2)
										{
											Object[type2]->setFlip(1, id2);
										}
										else
											Object[type2]->setFlip(0, id2);
									}
								}
								break;
							case 3:
								if (isActive == 3) //3 la trang thai roi cua con ca
								{
									dimension2 = CollideCheck(bx2, bx);
									if (dimension2 == 3)
									{
										PlaySound(fallingsound);
										Object[type2]->setStatus(2, id2);
										if (simonbox.x + simonbox.w / 2 > bx2.x + bx2.w / 2)
										{
											Object[type2]->setFlip(1, id2);
										}
										else
											Object[type2]->setFlip(0, id2);
									}
								}
								break;
							}
						}
					}
#pragma endregion xu ly cham cua quai vat voi nen

#pragma region
					for (int i = 0; i < Item.size(); i++)
					{
						Box bx2 = Item.at(i).getBox();
						if (Item.at(i).status == 1)
						{
							if (Collide(bx2, bx))
							{
								Item.at(i).status = 2;
							}
						}
					}

#pragma endregion xu ly cham nen voi item

#pragma region
					for (int n = 0; n < simon._Weapon.size(); n++)
					{
						if (simon._Weapon.at(n).getType() == 2)
						{
							Box bx2 = simon._Weapon.at(n).getBox();
							dimension = Collide(bx2, bx);
							if (dimension)
							{
								PlaySound(holywater);
								simon._Weapon.at(n).setStatus(2);
							}
						}
					}
#pragma endregion xu ly cham nen voi holy water

#pragma region
					for (int s = 0; s < medusasub.size(); s++)
					{
						Box bx2 = medusasub.at(s).getBox();
						dimension = Collide(bx2, bx);
						if (dimension == 3)
						{
							medusasub.at(s).setStatus(1);
						}
					}
#pragma endregion xu ly cham nen voi con ran

#pragma endregion xu ly va cham nen
					break;
				case 13:
#pragma region
					dimension = AABBCheck(simonbox, bx);
					if (dimension)
					{
						BoxCollision bxc(type, dimension, id, bx.x, bx.y, bx.w, bx.h);
						simon.LadderCollided.push_back(bxc);
					}
					if (!simon._OnLadder && dimension)
					{
						simon._LadderX = bx.x;
						simon._LadderY = bx.y;
					}
					Object[type]->update(delta, id);
#pragma endregion xu ly len thang
					break;
				case 14:
#pragma region
					//xu ly di
					dimension = Collide(simonbox, bx);
					if (dimension)
					{
						BoxCollision bxc(type, dimension, id, bx.x, bx.y, bx.w, bx.h);
						simon.ObjectCollided.push_back(bxc);
						simon.LadderCollided.push_back(bxc);
						if (!simon._OnLadder)
						{
							simon._LadderX = bx.x;
							simon._LadderY = bx.y;
						}
					}
					//xu ly roi cua cac quai vat
					for (int k = 0; k < listActiveEnemies.size(); k++)
					{
						int id2 = listActiveEnemies.at(k);
						int type2 = _DirectGetType[id2];
						Box bx2 = Object[type2]->getBox(id2);
						switch (type2)
						{
						case 2:
							if (CollideCheck(bx2, bx) == 3)
							{
								Object[type2]->setStatus(1, id2);
								if (simonbox.x + simonbox.w / 2 > bx2.x + bx2.w / 2)
								{
									Object[type2]->setFlip(1, id2);
								}
								else
									Object[type2]->setFlip(0, id2);
							}
							break;
						case 3:
							if (CollideCheck(bx2, bx) == 3)
							{
								Object[type2]->setStatus(2, id2);
								if (simonbox.x + simonbox.w / 2 > bx2.x + bx2.w / 2)
								{
									Object[type2]->setFlip(1, id2);
								}
								else
									Object[type2]->setFlip(0, id2);
							}
							break;
						}
					}
					Object[type]->update(delta, id);
#pragma endregion xu ly va cham nen va len thang
					break;
				case 15:
#pragma region
					dimension = CollideCheck(simonbox, bx);
					if (dimension)
					{
						simon._LadderDirection = Object[type]->isFlip(id);
						BoxCollision bxc(type, dimension, id, bx.x, bx.y, bx.w, bx.h);
						simon.LadderCollided.push_back(bxc);
					}
#pragma endregion xu ly cham voi co hieu di len thang
					break;
				case 16:
#pragma region
					dimension = CollideCheck(simonbox, bx);
					if (dimension)
					{
						simon._LadderDirection = Object[type]->isFlip(id);
						BoxCollision bxc(type, dimension, id, bx.x, bx.y, bx.w, bx.h);
						simon.LadderCollided.push_back(bxc);
					}
#pragma endregion xu ly cham voi co hieu di xuong thang
					break;
				case 17:
#pragma region
					if (Object[type]->isActive(id) == 1)
					{
						for (int t = 0; t < listSpecialObject.size(); t++)
						{
							int id2 = listSpecialObject.at(t);
							int type2 = _DirectGetType[id2];
							Box bx2 = Object[type2]->getBox(id2);
							if (type2 == 25)
							{
								if (Collide(bx, bx2))
								{
									Object[type]->setStatus(id, 2);
									break;
								}
							}
						}
						if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable)
						{
							if (AABBCheck(simonbox, bx))
							{
								if (simon._Action == 2)
								{
									simon.endJump();
									simon._Action = 1;
								}
								simon._JumpInitialize = false;
								simon.setKnockBack(true);
								simon.HealthPoint -= 5;
							}
						}
						//lam mo simon tren thang
						if (!simon.invulnerable && simon._OnLadder)
						{
							if (AABBCheck(simonbox, bx))
							{
								simon.invulnerable = true;
								simon.HealthPoint -= 5;
							}
						}
					}
					
					Object[type]->update(delta, id);
#pragma endregion xu ly bay gai
					break;
				case 19:
#pragma region 
					if (simon._OnFlyingObject!=2)
					{
						dimension = Collide(simonbox, bx);
						if ((dimension == 3 || dimension == 5))
						{
							if (simonbox.y > bx.y + bx.h - 15 &&
								simonbox.y < bx.y + bx.h + 15 &&
								simonbox.x + simonbox.w > bx.x + 5 &&
								simonbox.x < bx.x + bx.w - 5)
							{
								BoxCollision bxc(12, dimension, id, bx.x, bx.y, bx.w, bx.h);
								simon.ObjectCollided.push_back(bxc);
								simon.setflyingObjectVx(bx.vx);
								simon._OnFlyingObject = 1;
							}
						}
					}

					for (int q = 0; q < listSpecialObject.size(); q++)
					{
						int id2 = listSpecialObject.at(q);
						int type2 = _DirectGetType[id2];
						Box bx2 = Object[type2]->getBox(id2);
						if (type2 == 24)
						{
							if (Collide(bx, bx2))
							{
								if (Object[type2]->isFlip(id2))
								{
									if (!Object[type]->isActive(id))
									if (bx.vx > 0)
									{
										Object[type]->_Box.at(Object[type]->findVectorPosition(id)).vx = 2;
										Object[type]->setStatus(id, 1);
									}
								}
								else
								{
									if (Object[type]->isActive(id))
									if (bx.vx < 0)
									{
										Object[type]->_Box.at(Object[type]->findVectorPosition(id)).vx = -2;
										Object[type]->setStatus(id, 0);
									}
								}
							}
						}
					}
					Object[type]->update(delta, id);
#pragma endregion flying block
					break;
				case 20:
#pragma region
					if (!bossBattle && !simon.isFighting())
					{
						
						dimension = CollideCheck(simonbox, bx);
						if (dimension != 0)
						{
							simon._Box.at(0).vx = 0;
							if (dimension == 5)
							if(!Object[type]->isFlip(id))
							{
								if (simonbox.x < bx.x + bx.w / 2 && (simonbox.y < bx.y + 5 && simonbox.y > bx.y - 5))
								{
									touchGateOnAir = 1;
								}

							}
							else
							{
								if (simonbox.x > bx.x + bx.w / 2 && (simonbox.y < bx.y + 5 && simonbox.y > bx.y - 5))
								{
									touchGateOnAir = 2;
								}
							}

							if (dimension == 2 && !Object[type]->isFlip(id) && (simonbox.y < bx.y + 5&& simonbox.y > bx.y - 5))
							{
								touchGateOnAir = 1;
							}
							else
							if (dimension == 1 && Object[type]->isFlip(id) && (simonbox.y < bx.y + 5 && simonbox.y > bx.y - 5))
							{
								touchGateOnAir = 2;
							}
							else
							{
								BoxCollision bxc(12, dimension, id, bx.x, bx.y, bx.w, bx.h);
								simon.ObjectCollided.push_back(bxc);
							}


							//chong truogn hop nhay len tren khong ma di qua cua
							switch (touchGateOnAir)
							{
							case 1:
								if (simon._Action == 1)
								{
									int simonstage = ((64 * 6 - simon.getY()) / (64 * 6));
									if (simonstage < 0)
										simonstage = 0;
									else
									if (simonstage >= loadObject.rows / 6)
										simonstage = (loadObject.rows / 6) - 1;
									currentstage++;
									if (currentstage >= cameraMaxX.at(simonstage).size())
									{
										currentstage = cameraMaxX.at(simonstage).size() - 1;
									}
									cmr.setMaxMovingX(cameraMaxX.at(simonstage).at(currentstage));
									gateX = bx.x;
									onGate = 1;
									currentGateID = id;
									DoorAnimation._Box.at(0).x = bx.x + 20;
									DoorAnimation._Box.at(0).y = bx.y;
									DoorAnimation.setFlip(Object[type]->isFlip(id));
									touchGateOnAir = 0;
								}
								else
									simon._Box.at(0).vx = 0;
								break;
							case 2:
								if (simon._Action == 1)
								{
									int simonstage = ((64 * 6 - simon.getY()) / (64 * 6));
									if (simonstage < 0)
										simonstage = 0;
									else
									if (simonstage >= loadObject.rows / 6)
										simonstage = (loadObject.rows / 6) - 1;
									if (currentstage < 1)
										currentstage = 1;
									cmr.setMinMovingX(cameraMinX.at(simonstage).at(currentstage - 1));
									gateX = bx.x;
									onGate = 1;
									currentGateID = id;
									DoorAnimation._Box.at(0).x = bx.x - 20;
									DoorAnimation._Box.at(0).y = bx.y;
									DoorAnimation.setFlip(Object[type]->isFlip(id));
									touchGateOnAir = 0;
								}
								else
									simon._Box.at(0).vx = 0;
								break;
							}
						}
					}
					Object[type]->update(delta, id);
#pragma endregion xu ly dung vao cua
					break;
				case 21:
#pragma region
					if (simon._Action == 1)
					{
						dimension = CollideCheck(simonbox, bx);
						if (dimension)
						{
							simon._Action = 3;
							simon.CastleGateX = bx.x;
							simon.CastleGateWidth = bx.w;
							simon.isCollideWithCastleGate = true;
						}
							
					}
#pragma endregion xu ly cham vao lau dai
					break;
				case 23:
#pragma region
					for (int k = 0; k < ListEnemies.size(); k++)
					{
						int type2 = _DirectGetType[ListEnemies.at(k)];
						int id2 = ListEnemies.at(k);
						if (Object[type2]->isActive(id2))
						{
							if (type2 == 3)
							{
								dimension = CollideCheck(Object[type2]->getBox(id2), Object[type]->getBox(id));
								if (dimension == 3)
								{
									PlaySound(fallingdownwatersurface);
									ListEnemies.erase(ListEnemies.begin());
									_splashwater.load("resource/image/other/2.png", Object[type2]->getX(id2), Object[type2]->getY(id2));
									SplashWater.push_back(_splashwater);
								}
							}
						}
					}
#pragma endregion xu ly va cham roi xuong nuoc
					break;
				}
			}
			//kiem tra va cham giua simon va cac quai vat
#pragma region
			for (int j = 0; j < ListEnemies.size(); j++)
			{
				int id = ListEnemies.at(j);
				int type = _DirectGetType[id];
				Box bx = Object[type]->getBox(id);
				if (Object[type]->isActive(id))
				{
					
#pragma region
 					for (int n = 0; n < simon._Weapon.size(); n++)
					{
						Box bx2 = simon._Weapon.at(n).getBox();
						if (CollideCheck(bx2, bx))
						{
							if (type != 26 && type != 27)
							{
#pragma region					
								if (type != 4 && type != 5 && type != 8 && type != 9)
								{
#pragma region
									PlaySound(hitmonster);
									if (simon._Weapon.at(n).getType() == 1)
										simon._Weapon.at(n).setStatus(100);
									ListEnemies.erase(ListEnemies.begin() + j);
									j--;

									//tao hieu ung danh trung
									int spritex, spritey;
									spritey = bx2.y;
									if (!simon.isFlip())
										spritex = bx.x + bx.w;
									else
										spritex = bx.x;
									sprite.setPosition(spritex, spritey);
									sprite.animate(true);
									sprite.animate(100, 0, 0);
									hit.push_back(sprite);

									//tao hieu ung chet
									int sprite2x, sprite2y;
									sprite2y = bx.y + bx.h / 2;
									sprite2x = bx.x + bx.w / 2;
									sprite2.setPosition(sprite2x, sprite2y);
									sprite2.animate(true);
									sprite2.animate(80, 0, 2);
									destroyflame.push_back(sprite2);

									//tao item khi danh trung
									GeneratingItem(bx);
#pragma endregion xu ly danh trung voi quai vat 1 hit chet (dam phat chet luon)
								}
								else
								{
									int vectorPosition = Object[type]->findVectorPosition(id);
									if (type == 4 && !armorevil.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										armorevil.invulnerable.at(vectorPosition) = 1;
										//neu la armor thi trau hon xiu
										if (simon._Weapon.at(n).getType() == 1)
											simon._Weapon.at(n).setStatus(100);
										armorevil.health.at(vectorPosition)--;
										if (armorevil.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.x / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh voi armor evil
									}
									else
									if (type == 5 && !lancer.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										lancer.invulnerable.at(vectorPosition) = 1;
										//neu la armor thi trau hon xiu
										if (simon._Weapon.at(n).getType() == 1)
											simon._Weapon.at(n).setStatus(100);
										lancer.health.at(vectorPosition)--;
										if (lancer.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh voi lancer
									}
									else
									if (type == 8 && !dragoncannon.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										dragoncannon.invulnerable.at(vectorPosition) = 1;
										//neu la armor thi trau hon xiu
										if (simon._Weapon.at(n).getType() == 1)
											simon._Weapon.at(n).setStatus(100);
										dragoncannon.health.at(vectorPosition)--;
										if (dragoncannon.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung dragon cannon
									}
									else
									if (type == 9 && !ghost.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										ghost.invulnerable.at(vectorPosition) = 1;
										//neu la armor thi trau hon xiu
										if (simon._Weapon.at(n).getType() == 1)
											simon._Weapon.at(n).setStatus(100);
										ghost.health.at(vectorPosition)--;
										if (ghost.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung con ma
									}
								}
#pragma endregion tao hieu ung danh trung creep
							}
							else
							{
#pragma region 
								if (bossBattle)
								{
									switch (type)
									{
									case 26:
										if (!bossbat.invulnerable)
										if (bossbat.health > 0)
										{
											bossbat.invulnerable = true;
											bossbat.health--;
											PlaySound(hitmonster);
											if (simon._Weapon.at(n).getType() == 2)
											{
												bossbat.setStopUpdate(true);
											}
										}
										else
										{
											PlaySound(hitmonster);
											
											//khi boss chet
											itemsprite[13].setPosition(cmr.pos.x + SCREENWIDTH / 2, cmr.pos.y - SCREENHEIGHT / 2);
											Item.push_back(itemsprite[13]);
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											bossbat.health = -1;
											healthbar.update(simon.HealthPoint, bossbat.health);
										}
										
										break;
									case 27:
										if (!bossmedusa.invulnerable)
										if (bossmedusa.health > 0)
										{
											if (simon._Weapon.at(n).getType() == 2)
											{
												bossbat.setStopUpdate(true);
											}
											bossmedusa.invulnerable = true;
											bossmedusa.health--;
											PlaySound(hitmonster);
											if (simon._Weapon.at(n).getType() == 2)
												bossmedusa.setStopUpdate(true);
										}
										else
										{
											PlaySound(hitmonster);
											
											//khi boss chet
											itemsprite[13].setPosition(cmr.pos.x + SCREENWIDTH / 2, cmr.pos.y - SCREENHEIGHT / 2);
											Item.push_back(itemsprite[13]);
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											bossmedusa.health = -1;
											healthbar.update(simon.HealthPoint, bossmedusa.health);
										}
										break;
									}
								}

#pragma endregion xu ly danh trung boss
							}
						}
					}

#pragma endregion xu ly vu khi thu 2

#pragma region

#pragma region
					if (type != 26 && type != 27)
					{
						//knock back simon
						if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable)
						{
							if (CollideCheck(simonbox, bx))
							{
								if (simon._Action == 2)
								{
									simon.endJump();
									simon._Action = 1;
								}
								simon._JumpInitialize = false;
								simon.setKnockBack(true);
								if (type == 5)
								{
									simon.HealthPoint -= 3;
								}
								else
									simon.HealthPoint--;
							}
						}
						//lam mo simon tren thang
						if (!simon.invulnerable && simon._OnLadder)
						{
							if (CollideCheck(simonbox, bx))
							{
								simon.invulnerable = true;
								if (type == 5)
								{
									simon.HealthPoint -= 3;
								}
								else
									simon.HealthPoint--;
							}
						}
					}
					else
					{
						if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable && bossBattle)
						{
							if (CollideCheck(simonbox, bx))
							{
								if (simon._Action == 2)
								{
									simon.endJump();
									simon._Action = 1;
								}
								simon._JumpInitialize = false;
								simon.setKnockBack(true);
								simon.HealthPoint--;
							}
						}
						//lam mo simon tren thang
						if (!simon.invulnerable && simon._OnLadder && bossBattle)
						{
							if (CollideCheck(simonbox, bx))
							{
								simon.invulnerable = true;
								simon.HealthPoint--;
							}
						}
					}
#pragma endregion khi simon dung phai quai vat

#pragma region
					if (simon.checkFightCollision())
					{
						Box bx2 = simon.getPrimaryBox();
						if (CollideCheck(bx2, bx))
						{
							if (type != 26 && type != 27)
							{
#pragma region
								if (type != 4 && type != 5 && type != 8 && type != 9)
								{
									PlaySound(hitmonster);
									ListEnemies.erase(ListEnemies.begin() + j);
									j--;

									//tao hieu ung danh trung
									int spritex, spritey;
									spritey = bx2.y;
									if (!simon.isFlip())
										spritex = bx.x + bx.w;
									else
										spritex = bx.x;
									sprite.setPosition(spritex, spritey);
									sprite.animate(true);
									sprite.animate(100, 0, 0);
									hit.push_back(sprite);

									//tao hieu ung chet
									int sprite2x, sprite2y;
									sprite2y = bx.y + bx.h / 2;
									sprite2x = bx.x + bx.w / 2;
									sprite2.setPosition(sprite2x, sprite2y);
									sprite2.animate(true);
									sprite2.animate(80, 0, 2);
									destroyflame.push_back(sprite2);

									//tao item khi danh trung
									GeneratingItem(bx);
								}
								else
								{
									int vectorPosition = Object[type]->findVectorPosition(id);
									if (type == 4 && !armorevil.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										//neu la armor thi trau hon xiu
										armorevil.invulnerable.at(vectorPosition) = 1;
										armorevil.health.at(vectorPosition)--;
										if (armorevil.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung voi armor evil
									}
									else
									if (type == 5 && !lancer.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										//neu la armor thi trau hon xiu
										lancer.invulnerable.at(vectorPosition) = 1;
										lancer.health.at(vectorPosition)--;
										if (lancer.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = simon.getPrimaryBox().y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung voi lancer
									}
									else
									if (type == 8 && !dragoncannon.invulnerable.at(vectorPosition))
									{
#pragma region 
										PlaySound(hitmonster);
										//neu la armor thi trau hon xiu
										dragoncannon.invulnerable.at(vectorPosition) = 1;
										dragoncannon.health.at(vectorPosition)--;
										if (dragoncannon.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung voi dragoncannon
									}
									else
									if (type == 9 && !ghost.invulnerable.at(vectorPosition))
									{
#pragma region
										PlaySound(hitmonster);
										//neu la armor thi trau hon xiu
										ghost.invulnerable.at(vectorPosition) = 1;
										ghost.health.at(vectorPosition)--;
										if (ghost.health.at(vectorPosition) < 1)
										{
											ListEnemies.erase(ListEnemies.begin() + j);
											j--;
											//tao hieu ung chet
											int sprite2x, sprite2y;
											sprite2y = bx.y + bx.h / 2;
											sprite2x = bx.x + bx.w / 2;
											sprite2.setPosition(sprite2x, sprite2y);
											sprite2.animate(true);
											sprite2.animate(80, 0, 2);
											destroyflame.push_back(sprite2);

											//tao item khi danh trung
											GeneratingItem(bx);
										}

										//tao hieu ung danh trung
										int spritex, spritey;
										spritey = bx2.y;
										if (!simon.isFlip())
											spritex = bx.x + bx.w;
										else
											spritex = bx.x;
										sprite.setPosition(spritex, spritey);
										sprite.animate(true);
										sprite.animate(100, 0, 0);
										hit.push_back(sprite);
#pragma endregion xu ly danh trung con ma
									}
								}
#pragma endregion tao hieu ung danh trung voi quat vat
							}
							else
							{
#pragma region				
								if (type == 26)
								{
									if (!bossbat.invulnerable)
									if (bossbat.health > 0)
									{
										bossbat.invulnerable = true;
										bossbat.health--;
										PlaySound(hitmonster);
									}
									else
									{
										PlaySound(hitmonster);
										itemsprite[13].setPosition(cmr.pos.x + SCREENWIDTH / 2, cmr.pos.y - SCREENHEIGHT / 2);
										Item.push_back(itemsprite[13]);
										bossbat.health = -1;
										ListEnemies.erase(ListEnemies.begin() + j);
										healthbar.update(simon.HealthPoint, bossbat.getHealth());
										j--;
									}
								}
								else
								if (type == 27)
								{
									if (!bossmedusa.invulnerable)
									if (bossmedusa.health > 0)
									{
										bossmedusa.invulnerable = true;
										bossmedusa.health--;
										PlaySound(hitmonster);
									}
									else
									{
										PlaySound(hitmonster);
										itemsprite[13].setPosition(cmr.pos.x + SCREENWIDTH / 2, cmr.pos.y - SCREENHEIGHT / 2);
										Item.push_back(itemsprite[13]);
										bossmedusa.health = -1;
										ListEnemies.erase(ListEnemies.begin() + j);
										j--;
										healthbar.update(simon.HealthPoint, bossmedusa.getHealth());
									}
								}
#pragma endregion xu ly danh trung boss
							}
						}
					}
#pragma endregion xy ly vu khi chinh

					//tao hieu ung nuoc vang len
					if (type == 3)
					{
						if (bx.vy == 11)
						{
							//nuoc vang len
							_splashwater.load("resource/image/other/2.png", bx.x + bx.w / 2, bx.y + bx.h / 2);
							_splashwater.setPosition(bx.x + bx.w / 2, bx.y + bx.h / 2);
							SplashWater.push_back(_splashwater);
						}
					}


					if (type != 26 && type != 27)
					{
						for (int k = 0; k < listSpecialObject.size(); k++)
						{
							int id2 = listSpecialObject.at(k);
							int type2 = _DirectGetType[id2];
							Box bx2 = Object[type2]->getBox(id2);
							switch (type2)
							{
							case 22:
#pragma region
								dimension = CollideCheck(bx2, bx);
								switch (type)
								{
								case 2:
								case 4:
								case 5:
									if (dimension)
									{
										Object[type]->setStatus(2, id);
									}
									break;
								case 3:
									if (dimension)
									{
										Object[type]->setStatus(3, id);
									}
									break;
								}
#pragma endregion xu ly va cham roi cua quai vat
								break;
							case 24:
#pragma region
								switch (type)
								{
								case 1:
								case 2:
								case 3:
								case 4:
								case 5:
								case 7:
								case 8:
								case 9:
									if (CollideCheck(Object[type]->getBox(id), Object[type2]->getBox(id2)))
									{
										if (Object[type2]->isFlip(id2))
											Object[type]->setFlip(0, id);
										else
											Object[type]->setFlip(1, id);
									}
									break;
								}
#pragma endregion xu ly cham de quai vat di nguoc 
								break;
							}
						}
						if (type == 8)
						{
							dragoncannon.getSimonbox(simonbox);
							for (int i = 0; i < dragoncannon.getListFire(id).size(); i++)
							{
								Box bx2 = dragoncannon.getListFire(id).at(i);
								if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable&&
									Collide(simonbox, bx2))
								{

									if (simon._Action == 2)
									{
										simon.endJump();
										simon._Action = 1;
									}
									simon._JumpInitialize = false;
									simon.setKnockBack(true);
									simon.HealthPoint--;
								}
								//lam mo simon tren thang
								if (!simon.invulnerable && simon._OnLadder&&CollideCheck(simonbox, bx2))
								{
									simon.invulnerable = true;
									simon.HealthPoint--;
								}
							}

						}
						if (type == 9)
						{
							ghost.getSimonbox(simonbox);
						}
						if (!simon.isStopTime())
							Object[type]->update(delta, id);
					}
					else
					{
#pragma region
						if (Object[type]->getStatus() != 2)
						{
							switch (type)
							{
							case 26:
								if (Object[type]->getStatus() == 1 && simon.getX() >= bx.x + 128)
								{
									Object[type]->setStatus(2, id);
									cmr.setMinMovingX(cmr.pos.x);
									bossBattle = true;
									if (levelmusic != NULL)
										StopSound(levelmusic);
									LoopSound(bossmusic);
								}
								break;
							case 27:
								if (Object[type]->getStatus() == 1 && simon.getX() < bx.x - 100)
								{
									Object[type]->setStatus(2, id);
									cmr.setMaxMovingX(cmr.pos.x + SCREENWIDTH);
									bossBattle = true;
									if (levelmusic != NULL)
										StopSound(levelmusic);
									LoopSound(bossmusic);
								}
								break;
							}
						}
						if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable && bossBattle)
						{
							dimension = CollideCheck(simonbox, bx);
							if (dimension)
							{
								switch (dimension)
								{
								case 1:
									simon.setFlip(false);
									break;
								case 2:
									simon.setFlip(true);
									break;
								}
								if (simon._Action == 2)
								{
									simon.endJump();
									simon._Action = 1;
								}
								simon._JumpInitialize = false;
								simon.setKnockBack(true);
								simon.HealthPoint--;
							}
						}
						if (!simon.invulnerable && simon._OnLadder)
						{
							if (CollideCheck(simonbox, bx))
							{
								simon.invulnerable = true;
							}
						}
						if (bossBattle)
							healthbar.update(simon.HealthPoint, Object[type]->getHealth());
						if (!simon.isStopTime())
							Object[type]->update(delta, simonbox, id);
#pragma endregion xu ly voi boss

#pragma endregion xu ly voi cac quai vat va boss
					}
#pragma region
					if (bossBattle && type == 27)
					if (bossmedusa.getStatus() == 2)
					{
						snake.setPosition(bossmedusa.getX(id), bossmedusa.getY(id));
						if (simon.getX() > bossmedusa.getX(id))
						{
							snake.setFlip(1);
						}
						else
						{
							snake.setFlip(0);
						}
						snake.setStatus(2);
						medusasub.push_back(snake);
					}
#pragma endregion xu ly tao ra con ran con cua medusa
				}
				else
				{
					if (type == 26||type == 27)
						Object[type]->update(delta,simonbox, id);
					else
						Object[type]->update(delta, id);
				}
					
			}
#pragma endregion update cac con quai vat

			//kiem tra voi con ran
#pragma region
			if (bossBattle)
			for (int s = 0; s < medusasub.size(); s++)
			{
				int bossid = bossmedusa._Id.at(1);
				Box bx = medusasub.at(s).getBox(bossid);
#pragma region
				
				for (int n = 0; n < simon._Weapon.size(); n++)
				{
					if (CollideCheck(simon._Weapon.at(n).getBox(), bx))
					{
						if (simon._Weapon.at(n).getType() == 1)
							simon._Weapon.at(n).setStatus(100);
						medusasub.erase(medusasub.begin() + s);
						if (s > 0)
							s--;
						if (medusasub.size() == 0)
							break;
						//tao hieu ung danh trung
						int spritex, spritey;
						spritey = simon.getPrimaryBox().y;
						if (!simon.isFlip())
							spritex = bx.x + bx.w;
						else
							spritex = bx.x;
						sprite.setPosition(spritex, spritey);
						sprite.animate(true);
						sprite.animate(100, 0, 0);
						hit.push_back(sprite);

						//tao hieu ung chet
						int sprite2x, sprite2y;
						sprite2y = medusasub.at(s).getY(bossid);
						sprite2x = medusasub.at(s).getX(bossid);
						sprite2.setPosition(sprite2x, sprite2y);
						sprite2.animate(true);
						sprite2.animate(80, 0, 2);
						destroyflame.push_back(sprite2);
					}
				}
#pragma endregion kiem tra snake voi vu khi thu 2

#pragma region
				if (medusasub.size() != 0)
				if (simon.checkFightCollision())
				if (CollideCheck(simon.getPrimaryBox(), medusasub.at(s).getBox()))
				{
					medusasub.erase(medusasub.begin() + s);
					if(s > 0)
						s--;
					if (medusasub.size() == 0)
						break;
					//tao hieu ung danh trung
					int spritex, spritey;
					spritey = simon.getPrimaryBox().y;
					if (!simon.isFlip())
						spritex = medusasub.at(s).getBox().x + medusasub.at(s).getBox().w;
					else
						spritex = medusasub.at(s).getBox().x;
					sprite.setPosition(spritex, spritey);
					sprite.animate(true);
					sprite.animate(100, 0, 0);
					hit.push_back(sprite);

					//tao hieu ung chet
					int sprite2x, sprite2y;
					sprite2y = medusasub.at(s).getY();
					sprite2x = medusasub.at(s).getX();
					sprite2.setPosition(sprite2x, sprite2y);
					sprite2.animate(true);
					sprite2.animate(80, 0, 2);
					destroyflame.push_back(sprite2);
				}
#pragma endregion kiem tra snake voi cay roi

#pragma region
				if (medusasub.size() != 0)
				if (!simon.isKnockBack() && !simon._OnLadder && !simon.invulnerable)
				{
					if (CollideCheck(simon.getBox(), medusasub.at(s).getBox()))
					{
						if (simon._Action == 2)
						{
							simon.endJump();
							simon._Action = 1;
						}
						simon._JumpInitialize = false;
						simon.setKnockBack(true);
						simon.HealthPoint--;
					}
				}
				//lam mo simon tren thang
				if (medusasub.size() != 0)
				if (!simon.invulnerable && simon._OnLadder)
				{
					if (CollideCheck(simon.getBox(), medusasub.at(s).getBox()))
					{
						simon.invulnerable = true;
						simon.HealthPoint--;
					}
				}
#pragma endregion kiem tra snake cham voi simon

#pragma region
				for (int k = 0; k < listSpecialObject.size(); k++)
				{
					int id2 = listSpecialObject.at(k);
					int type2 = _DirectGetType[id2];
					Box bx2 = Object[type2]->getBox(id2);
					switch (type2)
					{
					case 22:
#pragma region
						dimension = CollideCheck(bx2, bx);
						if (dimension)
							medusasub.at(s).setStatus(2);
#pragma endregion xu ly va cham roi cua quai vat
						break;
					case 24:
#pragma region
						if (CollideCheck(bx, Object[type2]->getBox(id2)))
						{
							if (Object[type2]->isFlip(id2))
								medusasub.at(s).setFlip(0);
							else
								medusasub.at(s).setFlip(1);
						}
#pragma endregion xu ly cham de quai vat di nguoc 
						break;
					}
				}
#pragma endregion kiem tra snake voi special object

				//update con ran
				if (!simon.isStopTime() && medusasub.size() != 0)
				medusasub.at(s).update(delta);
			}
#pragma endregion kiem tra va cham voi con ran, con cua medusa

			//update hieu ung nuoc vang
			for (int i = 0; i < SplashWater.size(); i++)
			{
				SplashWater.at(i).update(delta);
			}

			if (bossBattle)
			{
#pragma region
				if (!_playdeathsound)
				if (simon.HealthPoint < 0)
				{
					if (bossmusic != NULL)
						StopSound(bossmusic);
					PlaySound(deathsound);
					_playdeathsound = true;
				}
			}
			else
			{
				if (!_playdeathsound)
				if (simon.HealthPoint < 0)
				{
					if (levelmusic != NULL)
						StopSound(levelmusic);
					PlaySound(deathsound);
					_playdeathsound = true;
				}

#pragma endregion tat mo nhac khi chet duoi tay boss
			}
			//cap nhat simon
			if (!winningScene)
			{
				simon.input(delta);
			}
			else
			{
#pragma region
				if (simon._Action == 1)
				{
					switch (winningScene)
					{
					case 1:
						simon.stand(delta);
						currenttimeregainperhealth += delta;
						if (simon.HealthPoint < 19)
						{
							if (currenttimeregainperhealth > 80)
							{
								simon.HealthPoint++;
								currenttimeregainperhealth = 0;
							}
						}
						if (simon.HealthPoint >= 19 && currenttimeregainperhealth > timewaitingfornextlevel)
						{
							currenttimeregainperhealth = 0;
							simon.HealthPoint = 19;
							winningScene = 2;
						}
						break;
					case 2:
						currenttimeregainperhealth += delta;
						if (simon.SecondaryWeaponUsePoint >= 0)
						{
							if (currenttimeregainperhealth > 120)
							{
								PlaySound(decreaseweaponusepointsound);
								simon.SecondaryWeaponUsePoint--;
								if (simon.SecondaryWeaponUsePoint >= 0)
									simon.score += 100;
								currenttimeregainperhealth = 0;
							}
						}
						if (simon.SecondaryWeaponUsePoint < 0)
						{
							if (currenttimeregainperhealth < 300)
							{
								currenttimeregainperhealth = 0;
								simon.SecondaryWeaponUsePoint = 0;
								simon.nextlevel = true;
								winningScene = 0;
							}
						}
						break;
					}
					healthbar.update(simon.HealthPoint, -1);
				}
#pragma endregion tao su kien hoi mau va cong diem khi thang boss va an crystal
			}
#pragma endregion trang thai khong di qua cua
		}
		else
		{
#pragma region
			
			if (simon._Action == 1)
			{
				//trang thai di qua cua
				if (!Object[20]->isFlip(currentGateID))
					switch (onGate)
				{
					case 1:
						if (cmr.pos.x < gateX - SCREENWIDTH / 2)
						{
							simon.stand(delta);
							cmr.pos.x += 3;
						}
						else
						{
							Object[20]->animate(false);
							Object[20]->setCurrentFrame(1);
							DoorAnimation.animate(true);
							DoorAnimation.animate(30, 0, 3);
							PlaySound(opendoorsound);
							onGate = 2;
						}
						break;
					case 2:
						if (DoorAnimation.getCurrentFrame() == 2)
						{
							DoorAnimation.animate(false);
							onGate = 3;
						}
						break;
					case 3:
						if (simon.getX() < gateX + 90)
							simon.moveRight(delta);
						else
						{
							simon.stand(delta);
							DoorAnimation.animate(true);
							onGate = 4;
						}
						break;
					case 4:
						if (DoorAnimation.getCurrentFrame() == 0)
						{
							PlaySound(opendoorsound);
							DoorAnimation.animate(false);
							Object[20]->animate(false);
							Object[20]->setCurrentFrame(0);
							onGate = 5;
						}
						break;
					case 5:
						if (cmr.pos.x < gateX)
						{
							cmr.pos.x += 3;
							simon.stand(delta);
						}
						else
						{
							//cmr.setMinMovingX(gateX + 48);
							onGate = 0;
							simon.CreateCheckPoint();
							resetCamera();
						}
						break;
				}
				else
				{
					switch (onGate)
					{
					case 1:
						if (cmr.pos.x > gateX - SCREENWIDTH / 2)
						{
							simon.stand(delta);
							cmr.pos.x -= 3;
						}
						else
						{
							Object[20]->animate(false);
							Object[20]->setCurrentFrame(1);
							DoorAnimation.animate(true);
							DoorAnimation.animate(30, 0, 3);
							PlaySound(opendoorsound);
							onGate = 2;
						}
						break;
					case 2:
						if (DoorAnimation.getCurrentFrame() == 2)
						{
							DoorAnimation.animate(false);
							onGate = 3;
						}
						break;
					case 3:
						if (simon.getX() > gateX - 90)
							simon.moveLeft(delta);
						else
						{
							simon.stand(delta);
							DoorAnimation.animate(true);
							onGate = 4;
						}
						break;
					case 4:
						if (DoorAnimation.getCurrentFrame() == 0)
						{
							PlaySound(opendoorsound);
							DoorAnimation.animate(false);
							Object[20]->animate(false);
							Object[20]->setCurrentFrame(0);
							onGate = 5;
						}
						break;
					case 5:
						if (cmr.pos.x + SCREENWIDTH > gateX + 18)
						{
							cmr.pos.x -= 3;
							simon.stand(delta);
						}
						else
						{
							cmr.setMaxMovingX(gateX + 18);
							onGate = 0;
							simon.CreateCheckPoint();
							resetCamera();
						}
						break;
					}
				}
			}
			else
				simon._Box.at(0).vx = 0;
#pragma endregion di qua cua
		}
	}

#pragma region
	for (int i = 0; i < Item.size(); i++)
	{
		Item.at(i).update(delta);
		if (Collide(simon.getBox(), Item.at(i).getBox()))
		{
			switch (Item.at(i).type)
			{
			case 0:
				simon.SecondaryWeaponUsePoint++;
				PlaySound(collectitem);
				break;
			case 1:
				simon.SecondaryWeaponUsePoint += 5;
				PlaySound(collectitem);
				break;
			case 2:
				switch (Item.at(i).getCurrentFrame())
				{
				case 0:
					simon.score += 100;
					PlaySound(collectitem);
					break;
				case 1:
					simon.score += 400;
					PlaySound(collectitem);
					break;
				case 2:
					simon.score += 700;
					PlaySound(collectitem);
					break;
				}
				break;
			case 3:
				if (simon.PrimaryWeapon < 2)
				{
					simon.PrimaryWeapon++ ;
					PlaySound(weaponcollect);
				}
				break;
			case 4:
				simon.SecondaryWeapon = 1;
				PlaySound(weaponcollect);
				break;
			case 5:
				simon.SecondaryWeapon = 5;
				PlaySound(weaponcollect);
				break;
			case 6:
				if (!isactiveholycross)
				{
					PlaySound(holycross);
					for (int s = 0; s < ListEnemies.size(); s++)
					{
						int isbosstype = _DirectGetType[ListEnemies.at(s)];
						if (isbosstype != 26 && isbosstype != 27)
						{
							for (int d = 0; d < listActiveEnemies.size(); d++)
							if (ListEnemies.at(s) == listActiveEnemies.at(d))
							{
								ListEnemies.erase(ListEnemies.begin() + s);
								s--;
								listActiveEnemies.erase(listActiveEnemies.begin() + d);
								break;
							}
						}
						else
						{
							if (bossBattle)
							{
								switch (isbosstype)
								{
								case 26:
									bossbat.health -= 5;
									if (bossbat.health <= -1)
										bossbat.health = -1;
									break;
								case 27:
									bossmedusa.health -= 5;
									if (bossmedusa.health <= -1)
										bossmedusa.health = -1;
									break;
								}
							}
						}
					}
					medusasub.clear();
					isactiveholycross = true;
				}
				break;
			case 7:
				simon.SecondaryWeapon = 3;
				PlaySound(weaponcollect);
				break;
			case 8:
				simon.SecondaryWeapon = 4;
				PlaySound(weaponcollect);
				break;
			case 9:
				simon.SecondaryWeapon = 2;
				PlaySound(weaponcollect);
				break;
			case 10:
				PlaySound(collectitem);
				simon.HealthPoint += 6;
				if (simon.HealthPoint > 19)
					simon.HealthPoint = 19;
				break;
			case 11:
				PlaySound(collectitem);
				simon.SecondaryWeaponLimit = 2;
				break;
			case 12:
				PlaySound(collectitem);
				simon.SecondaryWeaponLimit = 3;
				break;
			case 13:
				iseatencrystal = true;
				
			}
			Item.erase(Item.begin() + i);
		}
		else
			if (Item.at(i).status == 3)
				Item.erase(Item.begin() + i);
	}

	if (iseatencrystal && simon._Action==1)
	{
		iseatencrystal = false;
		StopSound(bossmusic);
		PlaySound(clearstage);
		timewaitingfornextlevel = 5000 - (19 - simon.HealthPoint) * 80 + 150;
		winningScene = 1;
	}
#pragma endregion xu ly va cham giua simon va item

	//knock back simon
	if (simon.isKnockBack())
		simon.knockBack();
	simon.update(delta);
	if(!bossBattle)
		healthbar.update(simon.HealthPoint, 19);

#pragma region
	if (isactiveholycross)
	{
		holycrosscount += delta;
		if (holycrosscount > 800)
		{
			holycrosscount = 0;
			isactiveholycross = false;
		}
	}
#pragma endregion active holy cross
	}
}

void CGamePlay::render(int delta)
{
	for (unordered_set<int>::iterator it = loadObject.bgObject.begin(); it != loadObject.bgObject.end(); it++)
		MainBackGround.renderTile(delta, *it);
	
	
	for (int i = 10; i < 28; i++)
	{
		Object[i]->animate(delta);
	}
	

	//ve cac vat the
	for (unordered_set<int>::iterator it = loadObject.renderingObject.begin(); it != loadObject.renderingObject.end(); it++)
	{
		int id = *it;
		int type = loadObject.getType(id);
		switch (type)
		{
		case 12:
			Object[type]->renderMergeObject(delta, id);
			break;
		case 15:
		case 16:
		case 21:
		case 23:
			break;
		default:
			Object[type]->render(delta, id);
			break;
		}
	}
	//animation cac con quai vat
	for (int k = 0; k < 10; k++)
	{
		if (k != 2 || k != 0)
			Object[k]->animate(delta);
	}
	//ve cac con quai vat
	for (int j = 0; j < listActiveEnemies.size(); j++)
	{
		int id = listActiveEnemies.at(j);
		int type = _DirectGetType[id];
		Object[type]->render(delta, id);
	}

	for (int j = 0; j < medusasub.size(); j++)
	{
		medusasub.at(j).animate(delta);
		medusasub.at(j).render(delta);
	}
	
	/*
	for (int j = 0; j < listSpecialObject.size(); j++)
	{
		int id = listSpecialObject.at(j);
		int type = _DirectGetType[id];
		Object[type]->render(delta, id);
	}*/

	for (int i = 0; i < Item.size(); i++)
	{
		Item.at(i).animate(delta);
		Item.at(i).render(delta);
	}

	//ve hieu ung chay
	for (int i = 0; i < hit.size(); i++)
	{
		hit.at(i).animate(delta);
		hit.at(i).render(delta);
		if (hit.at(i).isAnimationEnd())
			hit.erase(hit.begin() + i);
	}
	for (int i = 0; i < destroyflame.size(); i++)
	{
		destroyflame.at(i).animate(delta);
		destroyflame.at(i).render(delta);
		if (destroyflame.at(i).isAnimationEnd())
			destroyflame.erase(destroyflame.begin() + i);
	}

	//ve hieu ung nuoc vang
	for (int i = 0; i < SplashWater.size(); i++)
	{
		SplashWater.at(i).render(delta);
		if (SplashWater.at(i).isEnd())
		{
			SplashWater.erase(SplashWater.begin() + i); i--;
		}
			
	}

	if (onGate)
	{
		DoorAnimation.animate(delta);
		DoorAnimation.render(delta);
	}

	gameboard.render(delta);
	healthbar.render(delta);

	switch (simon.SecondaryWeapon)
	{
	case 2:
		SecondaryWeapon[4].render(delta);
		break;
	case 1:
		SecondaryWeapon[0].render(delta);
		break;
	case 3:
		SecondaryWeapon[2].render(delta); 
		break;
	case 4:
		SecondaryWeapon[3].render(delta);
		break;
	case 5:
		SecondaryWeapon[1].render(delta);
		break;
	}

	switch (simon.SecondaryWeaponLimit)
	{
	case 2:
		SecondaryWeaponLimit[0].render(delta);
		break;
	case 3:
		SecondaryWeaponLimit[1].render(delta);
		break;
	default:
		break;
	}
	simon.animate(delta);
	simon.render(delta);

	if (pausemenu)
	{
		blackboardpause.render(delta);
		pausemenusprite.render(delta);
	}
}

void CGamePlay::renderText(int delta)
{
	if (!pausemenu)
	leveltime += delta / 10;
	int time = leveltime / 25;
	arial.onlost();
	arial.render("SCORE", 5, 0);
	arial.render((char*)to_string(simon.score).c_str(), 100, 0);
	arial.render("TIME", 230, 0);
	arial.render((char*)to_string(time).c_str(), 310, 0);
	arial.render("STAGE", 400, 0);
	arial.render((char*)to_string(level).c_str(), 490, 0);
	arial.render("PLAYER", 5, 20);
	arial.render("ENEMY", 5, 40);
	arial.render((char*)to_string(simon.SecondaryWeaponUsePoint).c_str(), 420, 30);

	if (pausemenu)
	switch (currentchoosenpausedmenu)
	{
	case 0:
		arialbigger.render(pausemenuitem[0], 200, 300);
		arialsmaller.render(pausemenuitem[1], 228, 335);
		arialsmaller.render(pausemenuitem[2], 233, 360);
		break;
	case 1:
		arialsmaller.render(pausemenuitem[0], 220, 300);
		arialbigger.render(pausemenuitem[1], 223, 324);
		arialsmaller.render(pausemenuitem[2], 233, 360);
		break;
	case 2:
		arialsmaller.render(pausemenuitem[0], 220, 300);
		arialsmaller.render(pausemenuitem[1], 228, 335);
		arialbigger.render(pausemenuitem[2], 228, 355);
		break;
	}

}

int CGamePlay::OnKeyUp(int KeyCode)
{
	switch (KeyCode)
	{

	}
	return 0;
}

int CGamePlay::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_ESCAPE)
	{
		currentchoosenpausedmenu = 0;
		if (!pausemenu)
			pausemenu = true;
		else
			pausemenu = false;
	}

	if (!pausemenu)
	if (!onGate&&!winningScene)
	{
		Box bx;
		switch (KeyCode)
		{
		case DIK_SPACE:
			simon.jump();
			break;
		case DIK_RETURN:
			if (Key_Down(DIK_W))
				simon.fight(1);
			else
				simon.fight(0);
			break;
		case DIK_F1:
			if (!isactiveholycross)
			{
				PlaySound(holycross);
				for (int s = 0; s < ListEnemies.size(); s++)
				{
					int isbosstype = _DirectGetType[ListEnemies.at(s)];
					if (isbosstype != 26 && isbosstype != 27)
					{
						for (int d = 0; d < listActiveEnemies.size(); d++)
						if (ListEnemies.at(s) == listActiveEnemies.at(d))
						{
							ListEnemies.erase(ListEnemies.begin() + s);
							s--;
							listActiveEnemies.erase(listActiveEnemies.begin() + d);
							break;
						}
					}
					else
					{
						if (bossBattle)
						{
							switch (isbosstype)
							{
							case 26:
								bossbat.health -= 5;
								if (bossbat.health <= -1)
									bossbat.health = -1;
								break;
							case 27:
								bossmedusa.health -= 5;
								if (bossmedusa.health <= -1)
									bossmedusa.health = -1;
								break;
							}
						}
					}
				}
				medusasub.clear();
				isactiveholycross = true;
			}
			break;
		case DIK_F2:
			bx.x = cmr.pos.x;
			bx.w = SCREENWIDTH;
			bx.y = cmr.pos.y - SCREENHEIGHT;
			bx.h = SCREENHEIGHT;
			GeneratingItem(bx);
			break;
		}
	}


	if (pausemenu)
	{
		switch (KeyCode)
		{
		case DIK_W:
			currentchoosenpausedmenu--;
			if (currentchoosenpausedmenu < 0)
				currentchoosenpausedmenu = 2;
			break;
		case DIK_S:
			currentchoosenpausedmenu++;
			if (currentchoosenpausedmenu > 2)
				currentchoosenpausedmenu = 0;
			break;
		case DIK_RETURN:
			switch (currentchoosenpausedmenu)
			{
			case 0:
				pausemenu = false;
				break;
			case 1:
				_savegame("savegame.sav");
				//save game
				break;
			case 2:
				if (bossmusic != NULL)
					StopSound(bossmusic);
				if (levelmusic != NULL)
					StopSound(levelmusic);
				isExit = 1;
				//back to menu
				break;
			}
			break;
		}
	}
	return 0;
}

void CGamePlay::LoadMap()
{
	iseatencrystal = false;
	touchGateOnAir = 0;
	_playdeathsound = false;
	leveltime = 0;
	cameraMaxX.clear();
	cameraMinX.clear();
	ListEnemies.clear();
	_DirectGetType.clear();
	SplashWater.clear();
	bossBattle = false;
	listSpecialObject.clear();
	listActiveSpecialObject.clear();

	loadObject.gameObject.clear();
	loadObject.backGroundObject.clear();
	if (levelmusic!=NULL)
		StopSound(levelmusic);

	if (level > 3)
		level = 1;
	else
	if (level < 1)
		level = 1;

	if (isloadsavinggame)
	{
		//load level
		level = atoi(gamesave.at(0).c_str());
	}

	switch (level)
	{
	case 1:
	case 2:
		levelmusic = LoadSound("resource/music/Stage_01_Vampire_Killer.wav");
		DoorAnimation.load("resource/image/ground/Gate.png", 4, 1);
		break;
	case 3:
		levelmusic = LoadSound("resource/music/Stage_04_Stalker.wav");
		DoorAnimation.load("resource/image/ground/Gate2.png", 4, 1);
		break;
	default:
		levelmusic = LoadSound("resource/music/Stage_01_Vampire_Killer.wav");
		DoorAnimation.load("resource/image/ground/Gate.png", 4, 1);
		break;
	}

	LoopSound(levelmusic);

	vector<string> maplink = loadLink("resource/link3.txt");

	//Load Background first
	loadObject.Load((char*)maplink.at((level - 1) * 3).c_str());
	MainBackGround.loadBackGround((char*)maplink.at((level - 1) * 3 + 1).c_str());

	MainBackGround.ClearAll();
	int max = loadObject.backGroundObject.at(0).x0 + 32;
	int min = loadObject.backGroundObject.at(0).x0;
	for (int i = 0; i < loadObject.backGroundObject.size(); i++)
	{
		MainBackGround.addNewObject(loadObject.backGroundObject.at(i).id, loadObject.backGroundObject.at(i).type,
			loadObject.backGroundObject.at(i).x0, loadObject.backGroundObject.at(i).y0, 0, 0);
		if (max < loadObject.backGroundObject.at(i).x0 + 32)
			max = loadObject.backGroundObject.at(i).x0 + 32;
		if (min > loadObject.backGroundObject.at(i).x0)
			min = loadObject.backGroundObject.at(i).x0;
	}

	vector<string> link;
	switch (level)
	{
	case 1:
		link = loadLink("resource/map1object.txt");
		break;
	case 2:
		link = loadLink("resource/map2object.txt");
		break;
	case 3:
		link = loadLink("resource/map3object.txt");
		break;
	case 4:
		link = loadLink("resource/map1object.txt");
		break;
	}

	Object[0] = &bat;
	Object[1] = &zombie;
	Object[2] = &cat;
	Object[3] = &fish;
	Object[4] = &armorevil;
	Object[5] = &lancer;
	Object[6] = &medusahead;
	Object[7] = &skeleton;
	Object[8] = &dragoncannon;
	Object[9] = &ghost;
	Object[10] = &largecandle;
	Object[11] = &candle;
	Object[12] = &StaticObject[0];
	Object[13] = &StaticObject[1];
	Object[14] = &StaticObject[2];
	Object[15] = &StaticObject[3];
	Object[16] = &StaticObject[4];
	Object[17] = &spiketrap;
	Object[18] = &StaticObject[5];
	Object[19] = &flyingblock;
	Object[20] = &door;
	Object[21] = &StaticObject[6];
	Object[22] = &StaticObject[7];
	Object[23] = &StaticObject[8];
	Object[24] = &StaticObject[9];
	Object[25] = &StaticObject[10];
	Object[26] = &bossbat;
	Object[27] = &bossmedusa;

	for (int i = 0; i < 28; i++)
	{
		Object[i]->ClearAll();
		Object[i]->load((char*)link[i].c_str()); 
	}

	//tao ra gioi han cho camera
	vector<float> maxX;
	vector<float> minX;
	for (int i = 0; i < loadObject.rows / 6; i++)
	{
		vector<float> stagelength;
		cameraMinX.push_back(stagelength);
		cameraMaxX.push_back(stagelength);
		maxX.push_back(min);
		minX.push_back(max);
	}

	for (int i = 0; i < loadObject.gameObject.size(); i++)
	{
		if (loadObject.gameObject.at(i).type < 26 && loadObject.gameObject.at(i).type >= 10&&
			loadObject.gameObject.at(i).type != 22 && loadObject.gameObject.at(i).type != 24 && 
			loadObject.gameObject.at(i).type != 25)
		{
			//tao object
			Object[loadObject.gameObject.at(i).type]->addNewObject(loadObject.gameObject.at(i).id,
				loadObject.gameObject.at(i).x0, loadObject.gameObject.at(i).y0, loadObject.gameObject.at(i).x1, 
				loadObject.gameObject.at(i).y1, loadObject.gameObject.at(i).flip);

			//xac dinh vat the nam o gioi han camera de chia gioi han cho camera
			int stage = ((64 * 6 - loadObject.gameObject.at(i).y0) / (64 * 6));
			if (stage < 0)
				stage = 0;
			else
			if (stage >= loadObject.rows / 6)
				stage = ((loadObject.rows / 6) - 1);

			if (maxX.at(stage) < loadObject.gameObject.at(i).x0 + loadObject.gameObject.at(i).x1 / 2)
				maxX.at(stage) = loadObject.gameObject.at(i).x0 + loadObject.gameObject.at(i).x1 / 2;
			if (minX.at(stage) > loadObject.gameObject.at(i).x0 - loadObject.gameObject.at(i).x1 / 2 + 16)
				minX.at(stage) = loadObject.gameObject.at(i).x0 - loadObject.gameObject.at(i).x1 / 2 + 16;

			if (loadObject.gameObject.at(i).type == 20)
			{
				cameraMaxX.at(stage).push_back(loadObject.gameObject.at(i).x0 + loadObject.gameObject.at(i).x1 / 2);
				cameraMinX.at(stage).push_back(loadObject.gameObject.at(i).x0 - loadObject.gameObject.at(i).x1 / 2);
			}
		}
		else
		if (loadObject.gameObject.at(i).type == 28)
		{
			//thiet lap vi tri cho simon
			simon.setPosition(loadObject.gameObject.at(i).x0, loadObject.gameObject.at(i).y0);
			simon.setFlip(loadObject.gameObject.at(i).flip);
		}
		else
		if (loadObject.gameObject.at(i).type < 10 || (loadObject.gameObject.at(i).type > 25 && loadObject.gameObject.at(i).type < 28))
		{
			Object[loadObject.gameObject.at(i).type]->addNewObject(loadObject.gameObject.at(i).id,
				loadObject.gameObject.at(i).x0, loadObject.gameObject.at(i).y0, loadObject.gameObject.at(i).x1, 
				loadObject.gameObject.at(i).y1, loadObject.gameObject.at(i).flip);

			ListEnemies.push_back(loadObject.gameObject.at(i).id);
			_DirectGetType[loadObject.gameObject.at(i).id] = loadObject.gameObject.at(i).type;
		}
		else
		if (loadObject.gameObject.at(i).type == 22 || loadObject.gameObject.at(i).type == 24 ||
			loadObject.gameObject.at(i).type == 25)
		{
			Object[loadObject.gameObject.at(i).type]->addNewObject(loadObject.gameObject.at(i).id,
				loadObject.gameObject.at(i).x0, loadObject.gameObject.at(i).y0, loadObject.gameObject.at(i).x1,
				loadObject.gameObject.at(i).y1, loadObject.gameObject.at(i).flip);
			listSpecialObject.push_back(loadObject.gameObject.at(i).id);
			_DirectGetType[loadObject.gameObject.at(i).id] = loadObject.gameObject.at(i).type;
		}
	}

	if (isloadsavinggame)
	{
		simon.setPosition(atoi(gamesave.at(1).c_str()), atoi(gamesave.at(2).c_str()));
		simon.SecondaryWeapon = atoi(gamesave.at(3).c_str());
		simon.SecondaryWeaponUsePoint = atoi(gamesave.at(4).c_str());
		simon.HealthPoint = atoi(gamesave.at(5).c_str());
		simon.score = atoi(gamesave.at(6).c_str());
		isloadsavinggame = false;
		gamesave.clear();
	}

	#pragma region
	for (int i = 0; i < cameraMaxX.size(); i++)
		cameraMaxX.at(i).push_back(maxX.at(i));

	for (int k = 0; k < cameraMaxX.size(); k++)
	{
		for (int i = 0; i < cameraMaxX.at(k).size(); i++)
			for (int j = i+1; j < cameraMaxX.at(k).size(); j++)
				if (cameraMaxX.at(k).at(i) >= cameraMaxX.at(k).at(j))
				{
					float temp = cameraMaxX.at(k).at(i);
					cameraMaxX.at(k).at(i) = cameraMaxX.at(k).at(j);
					cameraMaxX.at(k).at(j) = temp;
				}

	}

	for (int i = 0; i < cameraMinX.size(); i++)
		cameraMinX.at(i).insert(cameraMinX.at(i).begin(), minX.at(i));

	for (int i = 0; i < cameraMinX.size(); i++)
	{
		for (int j = 0; j < cameraMinX.at(i).size(); j++)
		{
			for (int k = j + 1; k < cameraMinX.at(i).size(); k++)
			{
				if (cameraMinX.at(i).at(j) > cameraMinX.at(i).at(k))
				{
					float temp = cameraMinX.at(i).at(j);
					cameraMinX.at(i).at(j) = cameraMinX.at(i).at(k);
					cameraMinX.at(i).at(k) = temp;
				}
			}
		}
	}
	

	#pragma endregion tao camera va thiet lap camera
	resetCamera();

	//cmr.pos.y = SCREENHEIGHT - (simonstage * 64 * 6 - 32);
	for (int i = 0; i < Object[12]->_Box.size(); i++)
		Object[12]->_Box.at(i)._Type = 12;
	if(simon.nextlevel)
		simon.CreateCheckPoint();

	
}

void CGamePlay::_savegame(char* filename)
{
	ofstream	outfile;
	outfile.open(filename);
	outfile << level << "\n";
	outfile << simon.getX()<<"\n";
	outfile << simon.getY() << "\n";
	outfile << simon.SecondaryWeapon << "\n";
	outfile << simon.SecondaryWeaponUsePoint << "\n";
	outfile << simon.HealthPoint << "\n";
	outfile << simon.score << "\n";
	outfile.close();
}

void CGamePlay::LoadSaveGame()
{
	ifstream file("savegame.sav");
	if (file)
	{
		isloadsavinggame = true;
		gamesave.clear();
		gamesave = loadLink("savegame.sav");
	}
	else
		level = 1;
}