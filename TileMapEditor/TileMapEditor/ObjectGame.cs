using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileMapEditor
{
    public enum ObjectType
    {
        Enemy,
        Thing
    }
    public class ObjectGame
    {
        //public float Gravity = -0.001f;
        //public int Fps = 10;
        //public int DefaultSide = -1;
        //public float VxMaxToGo = 0.1f;
        public int Width;
        public int Height;

        public string objName;
        public int ID;
        public List<string> listIDInTree;
        public Bitmap bm;
        public Rectangle spaceMove;
        public Point location;

        public ObjectGame() { }
        public ObjectGame(Bitmap b,String name,String type)
        {
            bm = new Bitmap(b);
            objName = name;
            if (type == "Enemy")
                objectType = ObjectType.Enemy;
            else
                objectType = ObjectType.Thing;
            spaceMove = new Rectangle();
            listIDInTree = new List<string>();
            Width = bm.Width;
            Height = bm.Height;
        }
        public ObjectType objectType;
        public void SetID(int id)
        {
            ID = id * 10 + 2;
        }

        public void SetLocation(int x,int y,int height)
        {
            location = new Point(x + Width / 2, height - y - Height / 2);
        }
        public int Right
        {
            get
            {
                return location.X + Width / 2;
            }
        }
        public int Left
        {
            get
            {
                return location.X - Width / 2;
            }
        }
        public Point GetLocation(int height)
        {
            return new Point(location.X - Width / 2, height - location.Y - Height / 2-1);
        }
        
        public Point GetLocation()
        {
            return location;
        }

       

    }
}
