namespace TileMapEditor
{
    partial class TileMapEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.Open = new System.Windows.Forms.ToolStripButton();
            this.Save = new System.Windows.Forms.ToolStripButton();
            this.AddObj = new System.Windows.Forms.ToolStripButton();
            this.label1 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.picMap = new System.Windows.Forms.PictureBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.picTile = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.saveInfo = new System.Windows.Forms.SaveFileDialog();
            this.openFolder = new System.Windows.Forms.FolderBrowserDialog();
            this.openImage = new System.Windows.Forms.OpenFileDialog();
            this.panel3 = new System.Windows.Forms.Panel();
            this.picObject = new System.Windows.Forms.PictureBox();
            this.label3 = new System.Windows.Forms.Label();
            this.btnAddObject = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.txtObjName = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cbbObjType = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.txtObjID = new System.Windows.Forms.TextBox();
            this.btnBuild = new System.Windows.Forms.Button();
            this.cbShowObject = new System.Windows.Forms.CheckBox();
            this.btnGroupObject = new System.Windows.Forms.Button();
            this.toolStrip1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picMap)).BeginInit();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picTile)).BeginInit();
            this.panel3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picObject)).BeginInit();
            this.SuspendLayout();
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.Open,
            this.Save,
            this.AddObj});
            this.toolStrip1.Location = new System.Drawing.Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(1166, 25);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // Open
            // 
            this.Open.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Open.Image = global::TileMapEditor.Properties.Resources.Open;
            this.Open.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Open.Name = "Open";
            this.Open.Size = new System.Drawing.Size(23, 22);
            this.Open.Text = "Open";
            this.Open.Click += new System.EventHandler(this.Open_Click);
            // 
            // Save
            // 
            this.Save.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.Save.Image = global::TileMapEditor.Properties.Resources.Save;
            this.Save.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.Save.Name = "Save";
            this.Save.Size = new System.Drawing.Size(23, 22);
            this.Save.Text = "Save";
            this.Save.Click += new System.EventHandler(this.Save_Click);
            // 
            // AddObj
            // 
            this.AddObj.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.AddObj.Image = global::TileMapEditor.Properties.Resources._1477311996_sign_add;
            this.AddObj.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.AddObj.Name = "AddObj";
            this.AddObj.Size = new System.Drawing.Size(23, 22);
            this.AddObj.Text = "AddObj";
            this.AddObj.Click += new System.EventHandler(this.AddObj_Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.Red;
            this.label1.Location = new System.Drawing.Point(295, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(327, 39);
            this.label1.TabIndex = 1;
            this.label1.Text = "TILE MAP EDITOR";
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.AutoScroll = true;
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel1.Controls.Add(this.picMap);
            this.panel1.Location = new System.Drawing.Point(12, 91);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(994, 261);
            this.panel1.TabIndex = 2;
            // 
            // picMap
            // 
            this.picMap.Location = new System.Drawing.Point(0, 3);
            this.picMap.Name = "picMap";
            this.picMap.Size = new System.Drawing.Size(313, 152);
            this.picMap.TabIndex = 0;
            this.picMap.TabStop = false;
            this.picMap.Paint += new System.Windows.Forms.PaintEventHandler(this.picMap_Paint);
            this.picMap.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picMap_MouseDown);
            this.picMap.MouseMove += new System.Windows.Forms.MouseEventHandler(this.picMap_MouseMove);
            this.picMap.MouseUp += new System.Windows.Forms.MouseEventHandler(this.picMap_MouseUp);
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.panel2.AutoScroll = true;
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel2.Controls.Add(this.picTile);
            this.panel2.Location = new System.Drawing.Point(12, 418);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(479, 116);
            this.panel2.TabIndex = 3;
            // 
            // picTile
            // 
            this.picTile.Location = new System.Drawing.Point(0, 0);
            this.picTile.Name = "picTile";
            this.picTile.Size = new System.Drawing.Size(19, 14);
            this.picTile.TabIndex = 0;
            this.picTile.TabStop = false;
            this.picTile.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picTile_MouseDown);
            // 
            // label2
            // 
            this.label2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(9, 400);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 15);
            this.label2.TabIndex = 4;
            this.label2.Text = "List Tile Map";
            // 
            // saveInfo
            // 
            this.saveInfo.Filter = "txt File| *.txt";
            // 
            // openImage
            // 
            this.openImage.FileName = "openFileDialog1";
            // 
            // panel3
            // 
            this.panel3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel3.AutoScroll = true;
            this.panel3.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.panel3.Controls.Add(this.picObject);
            this.panel3.Location = new System.Drawing.Point(542, 418);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(612, 116);
            this.panel3.TabIndex = 5;
            // 
            // picObject
            // 
            this.picObject.Location = new System.Drawing.Point(0, 3);
            this.picObject.Name = "picObject";
            this.picObject.Size = new System.Drawing.Size(104, 106);
            this.picObject.TabIndex = 0;
            this.picObject.TabStop = false;
            this.picObject.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picObject_MouseDown);
            // 
            // label3
            // 
            this.label3.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(539, 402);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(57, 13);
            this.label3.TabIndex = 6;
            this.label3.Text = "List Object";
            // 
            // btnAddObject
            // 
            this.btnAddObject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left)));
            this.btnAddObject.Enabled = false;
            this.btnAddObject.Location = new System.Drawing.Point(379, 393);
            this.btnAddObject.Name = "btnAddObject";
            this.btnAddObject.Size = new System.Drawing.Size(112, 23);
            this.btnAddObject.TabIndex = 7;
            this.btnAddObject.Text = "Add Object";
            this.btnAddObject.UseVisualStyleBackColor = true;
            this.btnAddObject.Click += new System.EventHandler(this.btnAddObject_Click);
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(818, 402);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(51, 13);
            this.label4.TabIndex = 8;
            this.label4.Text = "ObjName";
            // 
            // txtObjName
            // 
            this.txtObjName.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.txtObjName.Location = new System.Drawing.Point(875, 396);
            this.txtObjName.Name = "txtObjName";
            this.txtObjName.Size = new System.Drawing.Size(100, 20);
            this.txtObjName.TabIndex = 9;
            this.txtObjName.KeyDown += new System.Windows.Forms.KeyEventHandler(this.txtObjName_KeyDown);
            // 
            // label5
            // 
            this.label5.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(999, 402);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(47, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "ObjType";
            // 
            // cbbObjType
            // 
            this.cbbObjType.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.cbbObjType.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cbbObjType.Enabled = false;
            this.cbbObjType.FormattingEnabled = true;
            this.cbbObjType.Items.AddRange(new object[] {
            "Enemy",
            "Thing"});
            this.cbbObjType.Location = new System.Drawing.Point(1052, 394);
            this.cbbObjType.Name = "cbbObjType";
            this.cbbObjType.Size = new System.Drawing.Size(102, 21);
            this.cbbObjType.TabIndex = 11;
            this.cbbObjType.SelectedIndexChanged += new System.EventHandler(this.cbbObjType_SelectedIndexChanged);
            // 
            // label6
            // 
            this.label6.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(667, 403);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(18, 13);
            this.label6.TabIndex = 12;
            this.label6.Text = "ID";
            // 
            // txtObjID
            // 
            this.txtObjID.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.txtObjID.Location = new System.Drawing.Point(691, 396);
            this.txtObjID.Name = "txtObjID";
            this.txtObjID.ReadOnly = true;
            this.txtObjID.Size = new System.Drawing.Size(100, 20);
            this.txtObjID.TabIndex = 13;
            // 
            // btnBuild
            // 
            this.btnBuild.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnBuild.Location = new System.Drawing.Point(1033, 96);
            this.btnBuild.Name = "btnBuild";
            this.btnBuild.Size = new System.Drawing.Size(121, 29);
            this.btnBuild.TabIndex = 14;
            this.btnBuild.Text = "Build Quad Tree";
            this.btnBuild.UseVisualStyleBackColor = true;
            this.btnBuild.Click += new System.EventHandler(this.btnBuild_Click);
            // 
            // cbShowObject
            // 
            this.cbShowObject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.cbShowObject.Checked = true;
            this.cbShowObject.CheckState = System.Windows.Forms.CheckState.Checked;
            this.cbShowObject.Location = new System.Drawing.Point(1033, 131);
            this.cbShowObject.Name = "cbShowObject";
            this.cbShowObject.Size = new System.Drawing.Size(121, 32);
            this.cbShowObject.TabIndex = 15;
            this.cbShowObject.Text = "Show Object";
            this.cbShowObject.UseVisualStyleBackColor = true;
            this.cbShowObject.CheckedChanged += new System.EventHandler(this.cbVisibleInMap_CheckedChanged);
            // 
            // btnGroupObject
            // 
            this.btnGroupObject.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.btnGroupObject.Location = new System.Drawing.Point(1033, 169);
            this.btnGroupObject.Name = "btnGroupObject";
            this.btnGroupObject.Size = new System.Drawing.Size(121, 30);
            this.btnGroupObject.TabIndex = 16;
            this.btnGroupObject.Text = "Group Object";
            this.btnGroupObject.UseVisualStyleBackColor = true;
            this.btnGroupObject.Click += new System.EventHandler(this.btnGroupObject_Click);
            // 
            // TileMapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(1166, 535);
            this.Controls.Add(this.btnGroupObject);
            this.Controls.Add(this.cbShowObject);
            this.Controls.Add(this.btnBuild);
            this.Controls.Add(this.txtObjID);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.cbbObjType);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.txtObjName);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.btnAddObject);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.panel3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.toolStrip1);
            this.Name = "TileMapEditor";
            this.Text = "TileMapEditor";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.TileMapEditor_MouseDown);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.panel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picMap)).EndInit();
            this.panel2.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picTile)).EndInit();
            this.panel3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picObject)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton Open;
        private System.Windows.Forms.ToolStripButton Save;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.PictureBox picMap;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.PictureBox picTile;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.SaveFileDialog saveInfo;
        private System.Windows.Forms.FolderBrowserDialog openFolder;
        private System.Windows.Forms.OpenFileDialog openImage;
        private System.Windows.Forms.ToolStripButton AddObj;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.PictureBox picObject;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button btnAddObject;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox txtObjName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cbbObjType;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txtObjID;
        private System.Windows.Forms.Button btnBuild;
        private System.Windows.Forms.CheckBox cbShowObject;
        private System.Windows.Forms.Button btnGroupObject;

    }
}

