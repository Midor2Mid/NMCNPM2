using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileMapEditor
{
    class QuadNode
    {
        public string nodeID;
        public QuadNode tl, tr, bl, br;
        public Rectangle rectClip;
        public List<ObjectGame> listObj;

        public QuadNode(Rectangle rectclip,string nodeid)
        {
            rectClip = new Rectangle(rectclip.X,rectclip.Y,rectclip.Width,rectclip.Height);
            nodeID = nodeid;
        }
        Rectangle getRect(int x,int y,int w,int h)
        {
            return new Rectangle(x - w / 2, TileMapEditor.ScrHeight - y - h / 2, w, h);
        }
        Rectangle getRect(Rectangle r)
        {
            return getRect(r.X, r.Y, r.Width, r.Height);
        }
        public Rectangle getRect()
        {
            return getRect(rectClip);
        }
        void AddObject(List<ObjectGame> listobj)
        {
            int l;
            int t ;
            int r ;
            int b ;
            listObj = new List<ObjectGame>();
            foreach (ObjectGame obj in listobj)
            {
                if (obj.objectType == ObjectType.Thing)
                {
                    l = obj.GetLocation(TileMapEditor.ScrHeight).X;
                    t = obj.GetLocation(TileMapEditor.ScrHeight).Y;
                    r = l + obj.Width;
                    b = t + obj.Height;
                }
                else
                {
                    l = obj.spaceMove.Left;
                    r = obj.spaceMove.Right;
                    t = obj.spaceMove.Top;
                    b = obj.spaceMove.Bottom;
                }
                Rectangle rectObj = new Rectangle(l, t, r - l, b - t);
                
                Rectangle rect = getRect(rectClip);

                if (rect.IntersectsWith(rectObj))
                {
                    obj.listIDInTree.Add(nodeID + listObj.Count.ToString());
                    listObj.Add(obj);
                }
            }
        }
        public void Build()
        {

            if (listObj.Count == 0 || rectClip.Width < TileMapEditor.viewPortWidth * 2 / 3)
            {
                return;
            }

            int w = rectClip.Width / 2;
            int h = rectClip.Height / 2;
            int x1 = rectClip.X + w / 2;
            int x2 = rectClip.X - w / 2;
            int y1 = rectClip.Y + h / 2;
            int y2 = rectClip.Y - h / 2;

            tl = new QuadNode(new Rectangle(x2, y1, w, h), nodeID + "1");
            tl.AddObject(listObj);
            tl.Build();

            tr = new QuadNode(new Rectangle(x1, y1, w, h), nodeID + "2");
            tr.AddObject(listObj);
            tr.Build();

            bl = new QuadNode(new Rectangle(x2, y2, w, h), nodeID + "3");
            bl.AddObject(listObj);
            bl.Build();

            br = new QuadNode(new Rectangle(x1, y2, w, h), nodeID + "4");
            br.AddObject(listObj);
            br.Build();

            listObj.Clear();

        }

    }
}
