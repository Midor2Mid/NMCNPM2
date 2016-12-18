using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TileMapEditor
{
    class Tile
    {
        public int ID;
        public Bitmap bm;
        public Tile(Bitmap b)
        {
            bm = b;
        }

        public void setID(int id)
        {
            ID = id*10 + 1;
        }
    }
}
