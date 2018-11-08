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

public enum EnumID
{
    // Player
    Megaman,
    MegamanBullet,

    // Boss
    BlastHornet,
    Byte,
    Shurikein,

    // Creep
    CarryArm,
    HeadGunner,
    Helit,
    NotoBanger,
    Hangerter,
    Bee,

    // Ground
    Cargo,
    Door,
    Ladder,
    BigElevator,
    SmallElevator,
    Conveyor,
    Thorn,
    Box,
    BreakableWall,
    Roof,
    BreakPlatform,
    UpGround,
    DownGround,
    Platform,

    //weapon
    Canon,
    GunnerRocket,
    HeliRocket,
    ByteBomb,

    //Item
    SmallEnergy,
    BigEnergy,
    ChimeraArmor,
};


namespace MapEditor
{
    public partial class Form1 : Form
    {
        public Form1()
        {

            InitializeComponent();
            listTile = new List<Bitmap>();
            listobjmap = new List<ObjectGame>();
        }

        // ObjectGame curObj;

        List<Bitmap> listTile;
        int[,] matTile;
        int countCol, countRow;
        Bitmap curTile;

        public static Rectangle viewPort;
        public static List<ObjectGame> listobjmap;
        public static int scrHeight;
        QuadNode rootNode;
        int[,] listMatrix;

        int countMatrixCol,countMatrixRow;
        string writeMatrix,readMatrix;
        string fileDirectory; 
        String fileName;
        Point startMouse;
        Point currentMouse;
       // QuadNode rootNode;
        private void btn_New_Click(object sender, EventArgs e)
        {
            
            openFileDialog1.ShowDialog();
            try
            {
                pictureBox1.BackgroundImage = Image.FromFile(openFileDialog1.FileName);
                pictureBox1.Width = pictureBox1.BackgroundImage.Width;
                pictureBox1.Height = pictureBox1.BackgroundImage.Height;
                countCol = pictureBox1.Width / 32;
                countRow = pictureBox1.Height / 32;
                matTile = new int[countRow, countCol];
                pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);

                DrawDash(countRow,countCol);
               Cut(pictureBox1.BackgroundImage);
           
            }
            catch
            {

            }


        }
        void DrawDash(int row, int col) //ve luoi
        {
            Graphics g = Graphics.FromImage(pictureBox1.Image);
            float[] dashValue = { 5, 2 };

            
            Pen p = new Pen(Color.Silver);
            p.DashPattern = dashValue;
            for (int i = 0; i < col; i++)
            {
                g.DrawLine(p, new Point(i * 32, 0), new Point(i * 32, pictureBox1.Height));
            }

            for (int i = 0; i < row; i++)
            {
                g.DrawLine(p, new Point(0, i * 32), new Point(pictureBox1.Width, i * 32));
            }
        }

        public bool Compare(Bitmap bmp1, Bitmap bmp2)
        {
            if (bmp1 == null || bmp2 == null)
                return false;
            if (object.Equals(bmp1, bmp2))
                return true;
            if (!bmp1.Size.Equals(bmp2.Size) || !bmp1.PixelFormat.Equals(bmp2.PixelFormat))
                return false;

            int bytes = bmp1.Width * bmp1.Height * (Image.GetPixelFormatSize(bmp1.PixelFormat) / 8);

            bool result = true;
            byte[] b1bytes = new byte[bytes];
            byte[] b2bytes = new byte[bytes];

            BitmapData bitmapData1 = bmp1.LockBits(new Rectangle(0, 0, bmp1.Width - 1, bmp1.Height - 1), ImageLockMode.ReadOnly, bmp1.PixelFormat);
            BitmapData bitmapData2 = bmp2.LockBits(new Rectangle(0, 0, bmp2.Width - 1, bmp2.Height - 1), ImageLockMode.ReadOnly, bmp2.PixelFormat);

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
        } //so sanh

        void DrawImage(Image bmDrawTo, Image bmDraw, Point pos, Rectangle rectClip) //ve
        {
            
            Graphics.FromImage(bmDrawTo).DrawImage(bmDraw, new Rectangle(pos.X, pos.Y, rectClip.Width, rectClip.Height), rectClip, GraphicsUnit.Pixel );
        }

        private void btn_Save_Click(object sender, EventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
           // saveFileDialog1.Filter = "Images|*.bmp;";
            ImageFormat format = ImageFormat.Png;
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                fileDirectory = Path.GetDirectoryName(saveFileDialog1.FileName);
                fileName = Path.GetFileName(saveFileDialog1.FileName);
                format = ImageFormat.Bmp;
                pictureBox2.BackgroundImage.Save(Path.Combine(fileDirectory,fileName+".bmp"), format);
                //  StreamWriter writer = new StreamWriter(Path.Combine(fileDirectory,Name+"txt"));
                string text = "";
                text += listTile.Count + "\r\n";
                text += countRow + "\r\n";
                text += countCol + "\r\n";
                text += writeMatrix;
                File.WriteAllText(Path.Combine(fileDirectory,fileName+".txt"),text);


                String s = "";

                StreamWriter writer = new StreamWriter(saveFileDialog1.FileName+"OBJ.txt");

                s += listobjmap.Count + "\r\n" + "\r\n";

                foreach (ObjectGame obj in listobjmap)
                {
                    s += obj.ID + "\r\n";
                    s += obj.topLeft.X + "\r\n";
                    s += obj.topLeft.Y + "\r\n";
                    s += obj.width + "\r\n";
                    s += obj.height + "\r\n";
                    s += "\r\n";
                }
                writer.Write(s);
                writer.Close();

                StreamWriter quadtree = new StreamWriter(saveFileDialog1.FileName + "Quadtree.txt");
                rootNode = new QuadNode("0", new Rectangle(0, 0, pictureBox1.Width, pictureBox1.Height));
                int ind = 0;
                foreach (ObjectGame obj in listobjmap)
                {
                    obj.index = ind;
                    ind++;
                }
                rootNode.listObj = listobjmap;
                rootNode.BuildTree();
                rootNode.Save(quadtree);
                quadtree.Close();
                MessageBox.Show("Saved");
            }

        }

        private void btn_Open_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            try
            {
                fileDirectory = Path.GetDirectoryName(openFileDialog1.FileName);
                fileName = Path.GetFileName(openFileDialog1.FileName).Substring(0, Path.GetFileName(openFileDialog1.FileName).LastIndexOf("."));
                pictureBox2.BackgroundImage = Image.FromFile(openFileDialog1.FileName);
                pictureBox2.Width = pictureBox2.BackgroundImage.Width;
                pictureBox2.Height = pictureBox2.BackgroundImage.Height;
                readMatrix=File.ReadAllText(Path.Combine(fileDirectory, fileName + ".txt"));
                countRow = pictureBox2.Height / 32;
                countCol = pictureBox2.Width / 32;
                matTile = new int[countRow, countCol];
                
                Cut(pictureBox2.BackgroundImage);
                decodeMatrix();


               // FileStream fileStream = new FileStream("")
                String readObj = File.ReadAllText(Path.Combine(fileDirectory,fileName+"OBJ.txt"));
                decodeObj(readObj);
               
                buildBackground();
                //pictureBox1.Width = pictureBox1.BackgroundImage.Width;
                //pictureBox1.Height = pictureBox1.BackgroundImage.Height;
                //pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
                String readQuadTree = File.ReadAllText(Path.Combine(fileDirectory, fileName + "QuadTree.txt"));
                rootNode = new QuadNode("0", new Rectangle(0, 0, pictureBox1.Width, pictureBox1.Height));
                rootNode.LoadNode(readQuadTree, listobjmap);
                DrawDash(countMatrixRow, countMatrixCol);
            }

            
            catch
            {

            }
        }


        private void decodeObj(string readObj)
        {
            int currentIndex = 0;
            int numOfObj = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n\r\n", currentIndex) - currentIndex));
            currentIndex = readObj.IndexOf("\r\n\r\n", currentIndex) + 4;
            for (int i=0;i<numOfObj; i++)
            {
                EnumID id = (EnumID) int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int x = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int y = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                ObjectGame obj = new ObjectGame(getImage((EnumID)id),id, new Point(x,y));
                listobjmap.Add(obj);
                currentIndex = readObj.IndexOf("\r\n\r\n", currentIndex) + 4;
            }

        }

        private Bitmap getImage(EnumID ID)
        {
            switch (ID)
            {
                //case EnumID.Megaman:
                //    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\tripleshot.png"));
                //    break;
                //case EnumID.BlastHornet:
                //    break;
                //case EnumID.Byte:
                //    break;
                //case EnumID.Shurikein:
                //    break;
                //case EnumID.CarryArm:
                //    break;
                //case EnumID.HeadGunner:
                //    break;
                //case EnumID.Helit:
                //    break;
                //case EnumID.NotoBanger:
                //    break;
                //case EnumID.Hangerter:
                //    break;
                //case EnumID.Bee:
                //    break;
                //case EnumID.Door:
                //    break;
                //case EnumID.Ladder:
                //    break;
                //case EnumID.BigElevator:
                //    break;
                //case EnumID.Conveyor:
                //    break;
                //case EnumID.Thorn:
                //    break;
                //case EnumID.Box:
                //    break;
                //case EnumID.Roof:
                //    break;
                //case EnumID.BreakPlatform:
                //    break;
                //case EnumID.Canon:
                //    break;
                //case EnumID.GunnerRocket:
                //    break;
                //case EnumID.HeliRocket:
                //    break;
                //case EnumID.ByteBomb:
                //    break;
                //case EnumID.SmallEnergy:
                //    break;
                //case EnumID.BigEnergy:
                //    break;
                //case EnumID.ChimeraArmor:
                //    break;
                //case EnumID.MegamanBullet:
                //    break;
                //case EnumID.Cargo:
                //    break;
                //case EnumID.SmallElevator:
                //    break;
                //case EnumID.BreakableWall:
                //    break;
                //case EnumID.UpGround:
                //    break;
                //case EnumID.DownGround:
                //    break;
                case EnumID.Platform:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                default:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
            }
        }

        private void buildBackground()
        {
            pictureBox1.Width = 32 * countMatrixCol;
            pictureBox1.Height = 32 * countMatrixRow;
            pictureBox1.BackgroundImage = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            for(int i=0;i<countMatrixRow; i++)
            {
                for(int j=0;j<countMatrixCol;j++)
                {
                    int x = i;
                    int a = listMatrix[i, j];
                    Bitmap tile = listTile[a];
                    DrawImage(pictureBox1.BackgroundImage, tile, new Point(j*32, i*32), new Rectangle(0, 0, 32, 32));
               
                }
            }
            pictureBox1.Width = pictureBox1.BackgroundImage.Width;
            pictureBox1.Height = pictureBox1.BackgroundImage.Height;
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            for (int i=0;i< listobjmap.Count();i++)
            {
                DrawImage(pictureBox1.Image, listobjmap[i].bm, listobjmap[i].topLeft, new Rectangle(0, 0, listobjmap[i].bm.Width, listobjmap[i].bm.Height));
            }
            pictureBox1.Refresh();
        }

        private void decodeMatrix()
        {
            
            int currentIndex = 0;
            countMatrixRow = int.Parse(readMatrix.Substring(0,readMatrix.IndexOf("\r\n",currentIndex)-currentIndex));
            currentIndex = readMatrix.IndexOf("\r\n", currentIndex)+2;
            
            countMatrixCol = int.Parse(readMatrix.Substring(currentIndex, readMatrix.IndexOf("\r\n", currentIndex)-currentIndex));
            currentIndex = readMatrix.IndexOf("\r\n", currentIndex)+2;
            listMatrix = new int[countMatrixRow, countMatrixCol];
            for (int i=0;i < countMatrixRow; i++)
            {
                string row = "";
                row = readMatrix.Substring(currentIndex, readMatrix.IndexOf("\r\n", currentIndex) - currentIndex);
                int currentRowIndex = 0;
                for (int j = 0; j < countMatrixCol; j++)
                {

                    //int currentCol = 0;
                    int currentTile = int.Parse(row.Substring(currentRowIndex, row.IndexOf(" ", currentRowIndex) - currentRowIndex));
                    listMatrix[i, j] = currentTile;

                    currentRowIndex = row.IndexOf(" ", currentRowIndex) + 1;

                }
                currentIndex = readMatrix.IndexOf("\r\n", currentIndex)+2; 
            }
        }

        void Cut(Image Image) //get tile
        {
            //int a = 0;
            writeMatrix = "";
            for (int i = 0; i < countRow; i++)
            {
                for (int j = 0; j < countCol; j++)
                {
                    Bitmap b = new Bitmap(32, 32);
                    int indexOf = 0;
                    DrawImage(b, Image, new Point(0, 0), new Rectangle(j * 32, i * 32, 32, 32));
                    bool allowAdd = true;
                    foreach (Bitmap bm in listTile)
                    {
                        if (Compare(b, bm))
                        {
                            allowAdd = false;
                            indexOf = listTile.IndexOf(bm);
                            matTile[i, j] = (int)bm.Tag;
                        }
                            
                    }
                    if (allowAdd)
                    {
                        b.Tag = listTile.Count;
                        listTile.Add(b);
                        matTile[i, j] = (int)b.Tag;
                        writeMatrix += b.Tag+" ";

                    }
                    else
                    {
                        writeMatrix += indexOf + " ";
                    }


                }
                writeMatrix += Environment.NewLine;
            }

            //string text = "";
            //text += countRow + "\r\n";
            //text += countCol + "\r\n";
            //text += writeMatrix;
            //readMatrix = text;
            //decodeMatrix();


            pictureBox2.Width = 32 * listTile.Count;
            pictureBox2.Height = 32;
            pictureBox2.BackgroundImage = new Bitmap(pictureBox2.Width, pictureBox2.Height);


            for (int i = 0; i < listTile.Count; i++)
            {
                DrawImage(pictureBox2.BackgroundImage, listTile[i], new Point(i * 32, 0), new Rectangle(0, 0, 32, 32));
            }
        }

        private void pictureBox2_MouseDown(object sender, MouseEventArgs e) //tao vien vuong luc chon tile
        {
            if (e.Y > 32)
            {
                return;
            }

            pictureBox2.Image = new Bitmap(pictureBox2.Width, pictureBox2.Height);
            Graphics g = Graphics.FromImage(pictureBox2.Image);
            g.DrawRectangle(new Pen(Color.Tomato), new Rectangle((e.X / 32) * 32, 0, 32, 32));
            curTile = listTile[e.X / 32];
        }

        String getName(String path)
        {
            path = path.Remove(path.LastIndexOf('.'));
            String[] l = path.Split('\\');

            return l[l.Count() - 1];
        }

        private void label1_Click(object sender, EventArgs e)
        {
        }

        private void pictureBox3_MouseDown(object sender, MouseEventArgs e)
        {
            //no
        }

        private void pictureBox1_Paint(object sender, PaintEventArgs e)
        {

        }

        private EnumID curentType;

        private void Draw(EnumID type) {
            switch (type)
            {
                case EnumID.Megaman:
                case EnumID.BlastHornet:
                    break;
                case EnumID.Byte:
                    break;
                case EnumID.Shurikein:
                    break;
                case EnumID.CarryArm:
                    break;
                case EnumID.HeadGunner:
                    break;
                case EnumID.Helit:
                    break;
                case EnumID.NotoBanger:
                    break;
                case EnumID.Hangerter:
                    break;
                case EnumID.Bee:
                    break;
                case EnumID.Door:
                    break;
                case EnumID.Ladder:
                    break;
                case EnumID.Conveyor:
                    break;
                case EnumID.Thorn:
                    break;
                case EnumID.Box:
                    break;
                case EnumID.Roof:
                    break;
                case EnumID.BreakPlatform:
                    break;
                case EnumID.Canon:
                    break;
                case EnumID.GunnerRocket:
                    break;
                case EnumID.HeliRocket:
                    break;
                case EnumID.ByteBomb:
                    break;
                case EnumID.SmallEnergy:
                    break;
                case EnumID.BigEnergy:
                    break;
                case EnumID.ChimeraArmor:
                    break;
                case EnumID.MegamanBullet:
                    break;
                case EnumID.Cargo:
                    break;
                case EnumID.BigElevator:
                    break;
                case EnumID.SmallElevator:
                    break;
                case EnumID.BreakableWall:
                    break;
                case EnumID.UpGround:
                    break;
                case EnumID.DownGround:
                    break;
                case EnumID.Platform:
                    drawItem(@"resource\platform.png", type); break;
                default:
                    break;
            }

        }

        private void pictureBox1_MouseDown_1(object sender, MouseEventArgs e)
        {
            textBox1.Text = curentType.ToString();
            startMouse = new Point(e.X, e.Y);
            currentMouse = new Point(e.X, e.Y);
            if (e.Button.Equals(MouseButtons.Left))
            {
                if (curentType != EnumID.Platform) {
                    Draw(curentType);
                }
                return;
            }

            if (e.Button.Equals(MouseButtons.Middle))
            {
                removeObject(currentMouse);
                return;
            }
        }


     
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            currentMouse = new Point(e.X, e.Y);
            if (e.Button.Equals(MouseButtons.Left))
            {
                if (curentType != EnumID.Platform)
                {
                    Draw(curentType);
                } else
                {
                    Bitmap bm = new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                    DrawImage(pictureBox1.Image, bm, startMouse, new Rectangle(0, 0, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y));
                    bm.Dispose();
                    pictureBox1.Refresh();
              
                }

            }
       
        }

        private void drawItem(String path, EnumID ID)
        {
            Bitmap bm = new Bitmap(Path.Combine(Application.StartupPath, path));
            ObjectGame obj;
            if (curentType == EnumID.Platform) {
                if (startMouse.X >= currentMouse.X || startMouse.Y >= currentMouse.Y) {
                    return;
                }
                DrawImage(pictureBox1.Image, bm, startMouse, new Rectangle(0, 0, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y));
                obj = new ObjectGame(ID, startMouse, currentMouse);
            } else {
                DrawImage(pictureBox1.Image, bm, currentMouse, new Rectangle(0, 0, bm.Width, bm.Height));
                obj = new ObjectGame(bm, ID, currentMouse);
            }
            pictureBox1.Refresh();
           
            addObject(obj);
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            currentMouse = new Point(e.X, e.Y);
            if (e.Button.Equals(MouseButtons.Left))
            {
                if (curentType == EnumID.Platform)
                {
                    Draw(curentType);
                }
                return;
            }
        }

        private void platformToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Platform;
        }

        private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            textBox1.Text = curentType.ToString();
            currentMouse = new Point(e.X, e.Y);
          
            removeObject(currentMouse);
            return;
        }

        void addObject(ObjectGame obj)
        {
            //foreach (ObjectGame objectGame in listobjmap)
            //{
            //    if (obj == objectGame)
            //    {
            //        return;
            //    }
            //}
            listobjmap.Add(obj);

        }

        void removeObject(Point obj)
        {
            int index = 0;
            foreach (ObjectGame objectGame in listobjmap)
            {
                if (objInRange(currentMouse, objectGame))
                {

                    int numOfCol = objectGame.bm.Width / 32;
                    int numOfRow = objectGame.bm.Height / 32;
                    if ((objectGame.topLeft.X + objectGame.bm.Width) % 32 != 0)
                    {
                        numOfCol++;
                    }

                    if ((objectGame.topLeft.Y + objectGame.bm.Height) % 32 != 0)
                    {
                        numOfRow++;
                    }

                    for (int col = 0; col < numOfCol; col++)
                    {
                        for (int row = 0; row < numOfRow; row++)
                        {
                            Point point = new Point((objectGame.topLeft.X / 32) * 32 + col * 32, (objectGame.topLeft.Y / 32) * 32 + row * 32);
                            int bitmapIndex = matTile[objectGame.topLeft.Y / 32 + row, objectGame.topLeft.X / 32 + col];
                            Bitmap bm = listTile[bitmapIndex];
                            DrawImage(pictureBox1.Image, bm, point, new Rectangle(0, 0, bm.Width, bm.Height));
                        }
                    }
                    for (int col = 0; col < numOfCol; col++)
                    {
                        for (int row = 0; row < numOfRow; row++)
                        { 
                            Graphics g = Graphics.FromImage(pictureBox1.Image);
                            float[] dashValue = { 5, 2 };
                            Pen p = new Pen(Color.Silver);
                            p.DashPattern = dashValue;
                            g.DrawRectangle(p, (objectGame.topLeft.X / 32) * 32 + col * 32, (objectGame.topLeft.Y / 32) * 32 + row * 32, 32, 32);
                        }
                    }


                    pictureBox1.Refresh();
                    listobjmap.RemoveAt(index);
                    return;
                }
                index++;
            }
        }

        bool objInRange(Point clickPoint, ObjectGame obj)
        {
            if (clickPoint.X < obj.topLeft.X || clickPoint.X > obj.topLeft.X + obj.bm.Width || clickPoint.Y > obj.topLeft.Y + obj.bm.Height || clickPoint.Y < obj.topLeft.Y)
            {
                return false;
            }
            return true;
        }

    }
}
