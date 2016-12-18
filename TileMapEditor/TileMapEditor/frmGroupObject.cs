using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TileMapEditor
{
    public partial class frmGroupObject : Form
    {
        public bool valueReturn;
        public frmGroupObject()
        {
            InitializeComponent();
            valueReturn = false;
            foreach (ObjectGame obj in TileMapEditor.ListObjectOnMap)
            {
                bool allowToAdd = true;
                foreach (String s in cbbListObj.Items)
                {
                    if (s.Equals(obj.objName))
                    {
                        allowToAdd = false;
                    }
                }
                if (allowToAdd)
                {
                    cbbListObj.Items.Add(obj.objName);
                }
            }
            cbbListObj.Text = cbbListObj.Items[0].ToString();
        }

    
        private void btnOk_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < TileMapEditor.ListObjectOnMap.Count; i++)
            {
                if (TileMapEditor.ListObjectOnMap[i].objName.Equals(cbbListObj.Text))
                {
                    for (int j = i + 1; j < TileMapEditor.ListObjectOnMap.Count; j++)
                    {
                        if (TileMapEditor.ListObjectOnMap[j].Left - TileMapEditor.ListObjectOnMap[i].Right > 10 || TileMapEditor.ListObjectOnMap[j].GetLocation().Y != TileMapEditor.ListObjectOnMap[i].GetLocation().Y || !TileMapEditor.ListObjectOnMap[j].objName.Equals(TileMapEditor.ListObjectOnMap[i].objName))
                            break;

                        TileMapEditor.ListObjectOnMap[i].location.X += TileMapEditor.ListObjectOnMap[j].Width / 2;
                        TileMapEditor.ListObjectOnMap[i].Width += TileMapEditor.ListObjectOnMap[j].Width;

                        TileMapEditor.ListObjectOnMap.Remove(TileMapEditor.ListObjectOnMap[j]);
                        j--;
                    }
                }
            }
        }

        private void btnCancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

    }
}
