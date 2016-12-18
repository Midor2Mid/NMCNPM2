using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace TileMapEditor
{
    public partial class TileMapEditor : Form
    {
        public TileMapEditor()
        {
            InitializeComponent();
            ListTile = new List<Tile>();
            ListObj = new List<ObjectGame>();
            ListObjectOnMap = new List<ObjectGame>();
            ObjWidth = 100;
            TileWidth = 16;
            TileHeight = 16;
            isSetSpaceMove = false;
            isAllowRemoveObjectFromMap = false;
            isMouseDownToSetSpaceMove = false;
        }

        private int[,] MatrixTile;
        private List<Tile> ListTile;
        private List<ObjectGame> ListObj;
        public static List<ObjectGame> ListObjectOnMap;
        private Bitmap bmObjOnMap;
        private Tile curTile;
        private ObjectGame curObj;
        private ObjectGame curDelObj;
        private int TileWidth;
        private int TileHeight;
        private int IndexHeight;
        private int ImageWidth;
        private int ObjWidth;
        private int mousePicMapX, mousePicMapY;
        private Point pspaceMove1;
        private Point pspaceMove2;
        private Point pRemoveObject;
        private bool isSetSpaceMove;
        private bool isAllowRemoveObjectFromMap;
        private bool isMouseDownToSetSpaceMove;
        private QuadNode rootNode;

        public static Rectangle viewPort;
        public static int viewPortWidth = 272;
        public static int viewPortHeight = 192;
        public static int ScrHeight;

        private int CalculateValue(Point p)
        {
            return p.Y*10000 + p.X;
        }

        private int tileWidthCount
        {
            get { return (int) (picMap.Width/TileWidth); }
        }

        private int tileHeightCount
        {
            get { return (int) (picMap.Height/TileHeight); }
        }

        private void AddTile(Tile tile)
        {
            tile.ID = ListTile.Count;
            ListTile.Add(tile);
        }

        private void RemoveTile(Tile tile, ObjectGame obj)
        {
            int tileperrow = tileWidthCount;
            int tilewidth = TileWidth;
            int tileheight = TileHeight;
            for (int i = IndexHeight; i < tileperrow; i++)
                for (int j = 0; j < tileperrow; j++)
                {
                    if (MatrixTile[i, j] == tile.ID)
                    {
                        ObjectGame o = new ObjectGame(obj.bm, obj.objName, obj.objectType.ToString());
                        o.SetLocation(j*tilewidth + 1, i*tileheight + 1, picMap.Height);
                        AddObjectToListObjOnMap(o);
                        DrawImage(bmObjOnMap, o.bm, o.GetLocation(picMap.Height),
                            new Rectangle(0, 0, tile.bm.Width, tile.bm.Height));
                        Pen p = new Pen(Color.SteelBlue);
                        Graphics.FromImage(picMap.BackgroundImage).FillRectangle(p.Brush,
                                new Rectangle(j*tilewidth, i*tileheight, tile.bm.Width, tile.bm.Height));
                    }
                }

            Graphics.FromImage(picTile.BackgroundImage)
                .FillRectangle(Brushes.DarkGray, new Rectangle(tile.ID*TileWidth, 0, TileWidth, TileHeight));
            ListTile.Remove(tile);
            picTile.Invalidate();
            Graphics.FromImage(picTile.Image).Clear(Color.Transparent);
        }

        private void DrawImage(Image bmDrawTo, Image bmDraw, Point pos, Rectangle rectClip)
        {
            Graphics.FromImage(bmDrawTo)
                .DrawImage(bmDraw, new Rectangle(pos.X, pos.Y, rectClip.Width, rectClip.Height), rectClip,
                    GraphicsUnit.Pixel);
        }

        private Bitmap bmClip(Image src, Rectangle rectClip)
        {
            Bitmap b = new Bitmap(rectClip.Width, rectClip.Height);
            DrawImage(b, src, Point.Empty, rectClip);
            return b;
        }

        public bool Compare(Bitmap bmp1, Bitmap bmp2)
        {
            if (bmp1 == null || bmp2 == null)
                return false;
            if (object.Equals(bmp1, bmp2))
                return true;
            if (!bmp1.Size.Equals(bmp2.Size) || !bmp1.PixelFormat.Equals(bmp2.PixelFormat))
                return false;

            int bytes = bmp1.Width*bmp1.Height*(Image.GetPixelFormatSize(bmp1.PixelFormat)/8);

            bool result = true;
            byte[] b1bytes = new byte[bytes];
            byte[] b2bytes = new byte[bytes];

            BitmapData bitmapData1 = bmp1.LockBits(new Rectangle(0, 0, bmp1.Width - 1, bmp1.Height - 1),
                ImageLockMode.ReadOnly, bmp1.PixelFormat);
            BitmapData bitmapData2 = bmp2.LockBits(new Rectangle(0, 0, bmp2.Width - 1, bmp2.Height - 1),
                ImageLockMode.ReadOnly, bmp2.PixelFormat);

            Marshal.Copy(bitmapData1.Scan0, b1bytes, 0, bytes);
            Marshal.Copy(bitmapData2.Scan0, b2bytes, 0, bytes);

            for (int n = 0; n <= bytes - 1; n++)
            {
                if (b1bytes[n] != b2bytes[n])
                {
                    result = false;
                    break;
                }
            }

            bmp1.UnlockBits(bitmapData1);
            bmp2.UnlockBits(bitmapData2);

            return result;
        }

        private void DrawDashGrid()
        {
            float[] dashValues = {10, 2};

            Graphics g = Graphics.FromImage(bmObjOnMap);
            int tileheight = TileHeight;
            int tileheightcount = tileHeightCount;
            int tilewidth = TileWidth;
            int imagewidth = ImageWidth;
            Pen blackPen = new Pen(Color.DarkGreen);
            blackPen.DashPattern = dashValues;
            for (int i = IndexHeight; i < tileheightcount; i++)
            {
                g.DrawLine(blackPen, new Point(0, i*tileheight), new Point(imagewidth, i*tileheight));
            }

            for (int j = 0; j < tileheightcount; j++)
            {
                blackPen.DashPattern = dashValues;
                g.DrawLine(blackPen, new Point(j*tilewidth, IndexHeight*tileheight), new Point(j*tilewidth, imagewidth));
            }
        }

        private void AddObjectToListObjOnMap(ObjectGame obj)
        {
            obj.ID = ListObjectOnMap.Count;
            int i;
            for (i = 0; i < ListObjectOnMap.Count; i++)
            {
                if (CalculateValue(ListObjectOnMap[i].GetLocation()) > CalculateValue(obj.GetLocation()))
                    break;
            }
            ListObjectOnMap.Insert(i, obj);
        }

        private void AddObject(ObjectGame obj)
        {
            ListObj.Add(obj);
            if (ListObj.Count == 1)
            {
                picObject.Width = ObjWidth;
                picObject.BackgroundImage = new Bitmap(picObject.Width, picObject.Height);
                Graphics.FromImage(picObject.BackgroundImage).Clear(Color.DarkGray);
                DrawImage(picObject.BackgroundImage, obj.bm,
                    new Point((ObjWidth - obj.bm.Width)/2, (picObject.Height - obj.bm.Height)/2),
                    new Rectangle(0, 0, obj.bm.Width, obj.bm.Height));
            }
            else
            {
                Bitmap bm = (Bitmap) picObject.BackgroundImage;
                picObject.Width += ObjWidth;
                picObject.BackgroundImage = new Bitmap(picObject.Width, picObject.Height);
                Graphics.FromImage(picObject.BackgroundImage).Clear(Color.DarkGray);
                DrawImage(picObject.BackgroundImage, bm, Point.Empty, new Rectangle(0, 0, bm.Width, bm.Height));
                DrawImage(picObject.BackgroundImage, obj.bm,
                    new Point(bm.Width + (ObjWidth - obj.bm.Width)/2, (bm.Height - obj.bm.Height)/2),
                    new Rectangle(0, 0, obj.bm.Width, obj.bm.Height));
            }
            cbVisibleInMap_CheckedChanged(cbShowObject, EventArgs.Empty);

        }

        private void Open_Click(object sender, EventArgs e)
        {
            openImage.ShowDialog();
            try
            {
                Bitmap bm = (Bitmap) Image.FromFile(openImage.FileName);
                picMap.Width = bm.Width;
                picMap.Height = bm.Width;


                Bitmap bm1 = new Bitmap(bm.Width, bm.Width);

                //picMap.Image = new Bitmap(bm.Width, bm.Width);

                Graphics.FromImage(bm1).Clear(Color.Black);


                DrawImage(bm1, bm, new Point(0, bm.Width - bm.Height), new Rectangle(0, 0, bm.Width, bm.Height));

                IndexHeight = (bm.Width - bm.Height)/TileWidth;

                picMap.BackgroundImage = bm1;

                ImageWidth = bm.Width;

                bmObjOnMap = new Bitmap(bm.Width, bm.Width);
                cbVisibleInMap_CheckedChanged(cbShowObject, EventArgs.Empty);
                //picMap.Image = bmObjOnMap;

                DrawDashGrid();

                MatrixTile = new int[tileWidthCount, tileHeightCount];

                viewPort = new Rectangle(16, bm.Width - viewPortHeight - 17*16, viewPortWidth, viewPortHeight);

                Graphics.FromImage(bmObjOnMap).DrawRectangle(new Pen(Color.DarkOrange, 2), viewPort);               
                CreateTileFromMap();

                ScrHeight = picMap.Height;

                
            }
            catch
            {


            }

        }

        private void CreateTileFromMap()
        {
            int tileheight = TileHeight;
            int tilewidth = TileWidth;
            int tilewidthcount = tileWidthCount;
            int tileheightcount = tileHeightCount;
            bool suscess = true;
            for (int i = IndexHeight; i < tileheightcount; i++)
            {
                for (int j = 0; j < tilewidthcount; j++)
                {
                    Bitmap bm = bmClip(picMap.BackgroundImage,
                        new Rectangle(j*tilewidth, i*tileheight, tilewidth, tileheight));

                    suscess = true;
                    foreach (Tile tile in ListTile)
                    {
                        if (Compare(bm, tile.bm))
                        {
                            suscess = false;
                            MatrixTile[i, j] = tile.ID;
                            break;
                        }
                    }
                    if (suscess)
                    {
                        AddTile(new Tile(bm));
                        MatrixTile[i, j] = ListTile[ListTile.Count - 1].ID;
                    }
                }
            }

            picTile.Width = ListTile.Count*tilewidth;

            picTile.BackgroundImage = new Bitmap(picTile.Width, picTile.Height);
            picTile.Image = new Bitmap(picTile.Width, picTile.Height);
            Graphics.FromImage(picTile.BackgroundImage).Clear(Color.DarkGray);
            for (int i = 0; i < ListTile.Count; i++)
            {
                DrawImage(picTile.BackgroundImage, ListTile[i].bm, new Point(i*tilewidth, 0),
                    new Rectangle(0, 0, tilewidth, tileheight));
            }
        }

        String getdir(String path)
        {
            return path.Remove(path.LastIndexOf('\\'));
        }

        private void Save_Click(object sender, EventArgs e)
        {
            DialogResult result = saveInfo.ShowDialog();          
            string dir = "";
            //string path = "";
            if (result == DialogResult.OK)
            {                                        
                dir = getdir(saveInfo.FileName);

                // lưu ma trận tile map
                StreamWriter writer1 = new StreamWriter(dir + "\\MatrixTile.txt");     
                writer1.Write(TileWidth + "  ");
                writer1.WriteLine(TileHeight);
                writer1.Write(tileWidthCount + "  ");
                writer1.WriteLine(tileHeightCount);

                for (int i = 0; i < tileHeightCount; i++)
                {
                    string str = "";
                    for (int j = 0; j < tileWidthCount; j++)
                    {
                        str += MatrixTile[i, j] + "  ";
                    }
                    writer1.WriteLine(str);
                }                          
                writer1.Close();

                // lưu ảnh tile
                picTile.BackgroundImage.Save(dir + "\\TileInMap.png");

                // lưu ảnh object
                Directory.CreateDirectory(dir);
                foreach (ObjectGame obj in ListObj)
                {
                    obj.bm.Save(dir + "\\" + obj.objName + ".png");
                }

                // lưu game object
                StreamWriter writer2 = new StreamWriter(dir +"\\ObjectInMap.txt");
                writer2.WriteLine(ListObjectOnMap.Count + "\n");

                foreach (ObjectGame obj in ListObjectOnMap)
                {
                    writer2.Write(obj.ID + "\t");
                    writer2.Write(obj.GetLocation(ScrHeight).X + "\t");
                    writer2.Write(obj.GetLocation(ScrHeight).Y + "\t");
                    writer2.Write(obj.Width + "\t");
                    writer2.WriteLine(obj.Height);
                }
                writer2.Close();

                // lưu quadtree
                StreamWriter writer3 = new StreamWriter(dir + "\\QuadTree.txt");
                WriteNode(rootNode, writer3);
                writer3.Close();
            }           

           
        }

        
        private void WriteNode(QuadNode node, StreamWriter wr)
        {
            if (node == null)
                return;
            wr.Write(node.nodeID + "\t\t");
            wr.Write(node.getRect().X + "\t\t");
            wr.Write(node.getRect().Y + "\t\t");
            wr.Write(node.getRect().Width + "\t\t");
            wr.Write(node.getRect().Height + "\t\t");
            if (node.listObj.Count > 0)
            {
                foreach (ObjectGame obj in node.listObj)
                {
                    wr.Write(obj.ID + "\t\t");
                }
                wr.Write("\n");
            }
            else
            {
                wr.Write("\n");
                WriteNode(node.tl, wr);
                WriteNode(node.tr, wr);
                WriteNode(node.bl, wr);
                WriteNode(node.br, wr);
            }
        }

        private String getName(String path)
        {
            path = path.Remove(path.LastIndexOf('.'));
            String[] l = path.Split('\\');

            return l[l.Count() - 1];
        }

        private void AddObj_Click(object sender, EventArgs e)
        {
            openFolder.ShowDialog();

            try
            {
                //String path = @"C:\Users\SONY\Desktop\ground";
                String[] listImage = Directory.GetFiles(openFolder.SelectedPath);
                foreach (String img in listImage)
                {
                    String name = getName(img);
                    Bitmap bm = (Bitmap) Bitmap.FromFile(img);
                    ObjectGame obj = new ObjectGame(bm, name, "Thing");
                    obj.ID = ListObj.Count;
                    AddObject(obj);

                    foreach (Tile tile in ListTile)
                    {
                        if (Compare(obj.bm, tile.bm))
                        {
                            RemoveTile(tile, obj);
                            break;
                        }
                    }

                    Graphics g = Graphics.FromImage(picMap.BackgroundImage);
                    Pen p = new Pen(Color.DarkGreen);
                }
            }
            catch
            {

            }
        }


        private void picMap_Paint(object sender, PaintEventArgs e)
        {
            //picMap.Invalidate();
            if (curObj != null && !isSetSpaceMove)
            {
                int x, y, w, h;
                int tilewidth = TileWidth;
                int tileheight = TileHeight;
                //x = (mousePicMapX / tilewidth) * tilewidth;
                //y = (mousePicMapY / tileheight) * tileheight ;

                x = mousePicMapX;
                y = mousePicMapY;

                if (curObj.bm.Width % tilewidth == 0)
                    w = curObj.bm.Width;
                else
                    w = curObj.bm.Width + (tilewidth - curObj.bm.Width % tilewidth);

                if (curObj.bm.Height % tileheight == 0)
                    h = curObj.bm.Height;
                else
                    h = curObj.bm.Height + (tileheight - curObj.bm.Height % tileheight);

                e.Graphics.DrawImage(curObj.bm, new Rectangle(x, y, curObj.bm.Width, curObj.bm.Height), new Rectangle(0, 0, curObj.bm.Width, curObj.bm.Height), GraphicsUnit.Pixel);

                e.Graphics.DrawRectangle(Pens.Red, new Rectangle(x, y, w, h));

                e.Graphics.DrawString(String.Format("({0};{1})", x + curObj.bm.Width / 2, picMap.Height - y - curObj.bm.Height / 2), Font, Brushes.Chocolate, new Point(x + curObj.bm.Width + 10, y));

            }


            if (isSetSpaceMove)
            {
                if (pspaceMove1 != null && pspaceMove2 != null)
                {
                    e.Graphics.DrawRectangle(Pens.Brown, RectSpaceMove());
                }
            }

            if (isAllowRemoveObjectFromMap)
            {
                Point p = getPointInTile(pRemoveObject.X, pRemoveObject.Y);
                int tileheight = TileHeight;
                foreach (ObjectGame obj in ListObjectOnMap)
                {
                    if (obj.GetLocation(ScrHeight).X == p.X && obj.GetLocation(ScrHeight).Y >= p.Y && obj.GetLocation(ScrHeight).Y <= p.Y + tileheight)
                    {
                        curDelObj = obj;
                        e.Graphics.DrawRectangle(Pens.Maroon, new Rectangle(p, getSizeFitTile(obj.bm.Width, obj.bm.Height)));
                        break;
                    }
                }

            }
        }

        Point getPointInTile(int x, int y)
        {
            if (!(x % TileWidth == 0))
                x = x - x % TileWidth;
            if (!(y % TileHeight == 0))
                y = y - y % TileHeight;
            return new Point(x, y);
        }

        Size getSizeFitTile(int w, int h)
        {
            if (!(w % TileWidth == 0))
                w += TileWidth - w % TileWidth;
            if (!(h % TileHeight == 0))
                h += TileHeight - h % TileHeight;
            return new Size(w, h);
        }

        private void picMap_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                isAllowRemoveObjectFromMap = false;
                curObj = null;
                if (picObject.Image != null)
                    Graphics.FromImage(picObject.Image).Clear(Color.Transparent);
            }
            if (e.Button == MouseButtons.Left)
            {
                if (curObj != null)
                {
                    isAllowRemoveObjectFromMap = false;
                    if (!isSetSpaceMove)
                    {
                        
                        int x = mousePicMapX;
                        int y = mousePicMapY;
                        Point p = new Point(x, y);
                        DrawImage(picMap.Image, curObj.bm, p, new Rectangle(0, 0, curObj.bm.Width, curObj.bm.Height));
                        cbVisibleInMap_CheckedChanged(cbShowObject, EventArgs.Empty);
                        ObjectGame obj = new ObjectGame(curObj.bm, curObj.objName, curObj.objectType.ToString());
                        obj.SetLocation(p.X, p.Y, picMap.Height);                      
                        AddObjectToListObjOnMap(obj);
                        curObj = obj;
                        isMouseDownToSetSpaceMove = true;
                        
                    }
                    if (curObj.objectType == ObjectType.Enemy && isSetSpaceMove)
                    {
                        pspaceMove1 = e.Location;
                        isMouseDownToSetSpaceMove = true;
                    }

                }
                else
                {
                    isAllowRemoveObjectFromMap = true;
                    pRemoveObject = new Point(e.X, e.Y);
                }

            }

            picObject.Invalidate();
        }

        private void picMap_MouseMove(object sender, MouseEventArgs e)
        {
            if (isSetSpaceMove && isMouseDownToSetSpaceMove)
            {
                pspaceMove2 = e.Location;
            }

            mousePicMapX = e.X;
            mousePicMapY = e.Y;
            picMap.Invalidate();
        }

        private void picMap_MouseUp(object sender, MouseEventArgs e)
        {
            if (isSetSpaceMove && isMouseDownToSetSpaceMove)
            {
                curObj.spaceMove = RectSpaceMove();

                Graphics.FromImage(picMap.Image).DrawRectangle(new Pen(Color.DarkBlue, 2), RectSpaceMove());
                isSetSpaceMove = false;
                isMouseDownToSetSpaceMove = false;
                pspaceMove1 = new Point(-1, -1);
                pspaceMove2 = new Point(-1, -1);
            }

            if (isMouseDownToSetSpaceMove && curObj != null && curObj.objectType == ObjectType.Enemy)
            {
                isSetSpaceMove = true;
                isMouseDownToSetSpaceMove = false;
            }

            picMap.Invalidate();
        }

        private Rectangle RectSpaceMove()
        {
            int l = Math.Min(pspaceMove1.X, pspaceMove2.X);
            int r = Math.Max(pspaceMove1.X, pspaceMove2.X);
            int t = Math.Min(pspaceMove1.Y, pspaceMove2.Y);
            int b = Math.Max(pspaceMove1.Y, pspaceMove2.Y);

            l = l - l%TileWidth;
            r = r + TileWidth - (r%TileHeight);

            t -= t%TileHeight;
            b += TileHeight - (b%TileHeight);

            return new Rectangle(l, t, r - l, b - t);


        }


        private void picTile_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Y > 16)
                return;
            Graphics.FromImage(picTile.Image).Clear(Color.Transparent);
            int tilewidth = TileWidth;
            int i = e.X / TileWidth;
            btnAddObject.Enabled = true;
            foreach (Tile tile in ListTile)
            {
                if (tile.ID == i)
                {
                    curTile = tile;
                    Graphics.FromImage(picTile.Image).DrawRectangle(Pens.Red, new Rectangle(i * tilewidth, 0, tile.bm.Width, tile.bm.Height));
                    picTile.Invalidate();
                    return;
                }
            }
        }

        private void btnAddObject_Click(object sender, EventArgs e)
        {
            frmAddNewObject frmAdd = new frmAddNewObject(curTile.bm);
            frmAdd.txtID.Text = ListObj.Count.ToString();
            frmAdd.ShowDialog();

            if (frmAdd.Result)
            {
                ObjectGame obj = new ObjectGame(curTile.bm, frmAdd.txtName.Text, frmAdd.cbbObjType.Text);
                obj.ID = ListObj.Count;

                AddObject(obj);

                RemoveTile(curTile, obj);

            }


            btnAddObject.Enabled = false;
        }

        private void picObject_MouseDown(object sender, MouseEventArgs e)
        {
            picObject.Image = new Bitmap(picObject.BackgroundImage.Width, picObject.BackgroundImage.Height);

            int i = e.X / ObjWidth;
            btnAddObject.Enabled = true;
            cbbObjType.Enabled = true;
            foreach (ObjectGame obj in ListObj)
            {
                if (obj.ID == i)
                {
                    txtObjName.Text = obj.objName;
                    txtObjID.Text = obj.ID.ToString();
                    curObj = obj;
                    Graphics.FromImage(picObject.Image).DrawRectangle(Pens.Red, new Rectangle(i * ObjWidth + (ObjWidth - obj.bm.Width) / 2, (ObjWidth - obj.bm.Height) / 2, obj.bm.Width, obj.bm.Height));
                    picObject.Invalidate();
                    cbbObjType.Text = curObj.objectType.ToString();
                    return;
                }
            }
        }

        private void cbbObjType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (curObj == null)
                return;
            if (cbbObjType.Text == "Enemy")
                curObj.objectType = ObjectType.Enemy;
            else
                curObj.objectType = ObjectType.Thing;
        }

        private void btnBuild_Click(object sender, EventArgs e)
        {
            if (rootNode != null)
                ReDrawPicMapImage();
            rootNode = new QuadNode(new Rectangle(picMap.Width / 2, picMap.Height / 2, picMap.Width, picMap.Height), "");
            rootNode.listObj = new List<ObjectGame>();
            foreach (ObjectGame obj in ListObjectOnMap)
            {
                rootNode.listObj.Add(obj);
            }
            rootNode.Build();
            DrawNode(rootNode);
        }

        void DrawNode(QuadNode node)
        {
            if (node == null)
                return;
            Pen p = new Pen(Color.Yellow, 3);

            Graphics.FromImage(bmObjOnMap).DrawRectangle(p, node.getRect());
            DrawNode(node.tl);
            DrawNode(node.tr);
            DrawNode(node.bl);
            DrawNode(node.br);
        }

        void ReDrawPicMapImage()
        {
            Graphics.FromImage(bmObjOnMap).Clear(Color.Transparent);

            DrawDashGrid();
            Graphics.FromImage(bmObjOnMap).DrawRectangle(new Pen(Color.DarkOrange, 2), viewPort);

            foreach (ObjectGame obj in ListObjectOnMap)
            {
                DrawImage(bmObjOnMap, obj.bm, obj.GetLocation(ScrHeight), new Rectangle(0, 0, obj.bm.Width, obj.bm.Height));
                if (obj.objectType == ObjectType.Enemy)
                {
                    Graphics.FromImage(bmObjOnMap).DrawRectangle(new Pen(Color.DarkBlue, 2), obj.spaceMove);
                }
            }

        }

        private void cbVisibleInMap_CheckedChanged(object sender, EventArgs e)
        {
            if (!cbShowObject.Checked)
            {
                picMap.Image = new Bitmap(ImageWidth, ImageWidth);
            }
            else
                picMap.Image = bmObjOnMap;
        }

        private void TileMapEditor_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
                curObj = null;
        }

        private void txtObjName_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.KeyCode == Keys.Enter && curObj != null)
                curObj.objName = txtObjName.Text;  
        }

        private void btnGroupObject_Click(object sender, EventArgs e)
        {
            (new frmGroupObject()).ShowDialog();
        }
    }
}
