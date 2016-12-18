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
    public partial class frmAddNewObject : Form
    {
        public bool Result;
        public frmAddNewObject(Bitmap b)
        {
            InitializeComponent();
            picObject.BackgroundImageLayout = ImageLayout.Stretch;
            picObject.BackgroundImage = b;
            Result = false;
            cbbObjType.Text = "Thing";
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            Result = true;
            this.Close();
        }

        private void txtName_TextChanged(object sender, EventArgs e)
        {
            btnSave.Enabled = txtName.Text.Length >= 1;
        }
    }
}
