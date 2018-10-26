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

enum EnumID
{

    //enemy
    BlastHornet,
    Byte,
    CarryArm,
    Shurikein,
    HeadGunner,
    Helit,
    NotoBanger,
    Hangerter,

    //ground
    MovingPlatform_ID,
    StairLeft_ID,
    StairRight_ID,
    StairTopLeft_ID,
    StairTopRight_ID,
    StairBotLeft_ID,
    StairBotRight_ID,
    Door_ID,
    Tele_ID,
    Trap_ID,
    Brick_ID,
    Breakable_ID,
    Candle_ID,

    //boss
    Medusa_ID,
    Count_Dracula_ID,

    //Item
    MorningStar_ID,
    SmallHeart_ID,
    BigHeart_ID,
    MoneyBag400_ID,
    MoneyBag700_ID,
    PorkChop_ID,
    Crown_ID,
    TreasureChest_ID,
    DoubleShot_ID,
    TripleShot_ID,
    SpiritBall_ID,
    Cross_ID,

    //weapon
    Axe_ID,
    Boomerang_ID,
    Knife_ID,
    FireBomb_ID,
    StopWatch_ID,
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
                    s += obj.location.X + "\r\n";
                    s += obj.location.Y + "\r\n";
                    s += obj.bm.Width + "\r\n";
                    s += obj.bm.Height + "\r\n";
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
                int id = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int x = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int y = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                ObjectGame obj = new ObjectGame(getImage(id),id);
                obj.SetLocation(x, y);
                listobjmap.Add(obj);
                currentIndex = readObj.IndexOf("\r\n\r\n", currentIndex) + 4;
            }

        }

        private Bitmap getImage(int ID)
        {
            
            switch(ID)
            {
                case (int) EnumID.Count_Dracula_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\boss\dracula.png"));
                case (int) EnumID.Medusa_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\boss\medusa.png"));
                case (int) EnumID.MedusaHead_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\medusahead.png"));
                case (int) EnumID.Ghost_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\ghost.png"));
                case (int) EnumID.Bat_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\bat.png"));
                case (int) EnumID.BonePillar_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\turret.png"));
                case (int) EnumID.Eagle_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\eagle.png"));
                case (int) EnumID.PhantomBat_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\phantombat.png"));
                case (int) EnumID.Pleaman_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\pleaman.png"));
                case (int) EnumID.Skeletons_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\skeleton.png"));
                case (int) EnumID.SpearGuard_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\enemy\spearman.png"));
                case (int) EnumID.Breakable_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\break.png"));
                case (int) EnumID.Candle_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\candle.png"));
                case (int) EnumID.Door_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\door.png"));
                case (int) EnumID.MovingPlatform_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\movingplatform.png"));
                case (int) EnumID.StairLeft_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairleft.png"));
                case (int) EnumID.StairRight_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairright.png"));
                case (int)EnumID.StairTopLeft_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairleft.png"));
                case (int)EnumID.StairTopRight_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairright.png"));
                case (int)EnumID.StairBotLeft_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairleft.png"));
                case (int)EnumID.StairBotRight_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\stairright.png"));
                case (int) EnumID.Tele_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\tele.png"));
                case (int) EnumID.Trap_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\trap.png"));
                case (int) EnumID.Brick_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\ground\ground.png"));
                case (int) EnumID.Axe_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\axe.png"));
                case (int) EnumID.BigHeart_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\bigheart.png"));
                case (int) EnumID.Boomerang_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\boomerang.png"));
                case (int) EnumID.Knife_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\dagger.png"));
                case (int) EnumID.Cross_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\cross.png"));
                case (int) EnumID.Crown_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\crown.png"));
                case (int) EnumID.DoubleShot_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\doubleshot.png"));
                case (int) EnumID.FireBomb_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\firebomb.png"));
                case (int) EnumID.MoneyBag400_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\moneybag400.png"));
                case (int) EnumID.MoneyBag700_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\moneybag700.png"));
                case (int) EnumID.MorningStar_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\morningstar.png"));
                case (int) EnumID.PorkChop_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\porkchop.png"));
                case (int) EnumID.SmallHeart_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\smallheart.png"));
                case (int) EnumID.SpiritBall_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\magicball.png"));
                case (int) EnumID.StopWatch_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\watch.png"));
                case (int) EnumID.TreasureChest_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\treasure.png"));
                default:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\image\item\tripleshot.png"));
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
                DrawImage(pictureBox1.Image, listobjmap[i].bm, listobjmap[i].location, new Rectangle(0, 0, listobjmap[i].bm.Width, listobjmap[i].bm.Height));
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

        private void Draw(EnumID type)
        {
            switch (type)
            {
                case EnumID.MedusaHead_ID:
                    drawItem(@"resource\image\enemy\medusahead.png", (int)EnumID.MedusaHead_ID);
                    break;
                case EnumID.Bat_ID:
                    drawItem(@"resource\image\enemy\bat.png", (int)EnumID.Bat_ID);
                    break;
                case EnumID.SpearGuard_ID:
                    drawItem(@"resource\image\enemy\spearman.png", (int)EnumID.SpearGuard_ID);
                    break;
                case EnumID.BonePillar_ID:
                    drawItem(@"resource\image\enemy\turret.png", (int)EnumID.BonePillar_ID);
                    break;
                case EnumID.Ghost_ID:
                    drawItem(@"resource\image\enemy\ghost.png", (int)EnumID.Ghost_ID);
                    break;
                case EnumID.PhantomBat_ID:
                    drawItem(@"resource\image\enemy\phantombat.png", (int)EnumID.PhantomBat_ID);
                    break;
                case EnumID.Eagle_ID:
                    drawItem(@"resource\image\enemy\eagle.png", (int)EnumID.Eagle_ID);
                    break;
                case EnumID.Skeletons_ID:
                    drawItem(@"resource\image\enemy\skeleton.png", (int)EnumID.Skeletons_ID);
                    break;
                case EnumID.Pleaman_ID:
                    drawItem(@"resource\image\enemy\pleaman.png", (int)EnumID.Pleaman_ID);
                    break;
                case EnumID.MovingPlatform_ID:
                    drawItem(@"resource\image\ground\movingground.png", (int)EnumID.MovingPlatform_ID);
                    break;
                case EnumID.StairLeft_ID:
                    drawItem(@"resource\image\ground\stairleft.png", (int)EnumID.StairLeft_ID);
                    break;
                case EnumID.StairRight_ID:
                    drawItem(@"resource\image\ground\stairright.png", (int)EnumID.StairRight_ID);
                    break;
                case EnumID.StairTopLeft_ID:
                    drawItem(@"resource\image\ground\stairleft.png", (int)EnumID.StairTopLeft_ID);
                    break;
                case EnumID.StairTopRight_ID:
                    drawItem(@"resource\image\ground\stairright.png", (int)EnumID.StairTopRight_ID);
                    break;
                case EnumID.StairBotLeft_ID:
                    drawItem(@"resource\image\ground\stairleft.png", (int)EnumID.StairBotLeft_ID);
                    break;
                case EnumID.StairBotRight_ID:
                    drawItem(@"resource\image\ground\stairright.png", (int)EnumID.StairBotRight_ID);
                    break;
                case EnumID.Door_ID:
                    drawItem(@"resource\image\ground\door.png", (int)EnumID.Door_ID);
                    break;
                case EnumID.Tele_ID:
                    drawItem(@"resource\image\ground\tele.png", (int)EnumID.Tele_ID);
                    break;
                case EnumID.Trap_ID:
                    drawItem(@"resource\image\ground\trap.png", (int)EnumID.Trap_ID);
                    break;
                case EnumID.Brick_ID:
                    drawItem(@"resource\image\ground\ground.png", (int)EnumID.Brick_ID);
                    break;
                case EnumID.Breakable_ID:
                    drawItem(@"resource\image\ground\break.png", (int)EnumID.Breakable_ID);
                    break;
                case EnumID.Candle_ID:
                    drawItem(@"resource\image\ground\candle.png", (int)EnumID.Candle_ID);
                    break;
                case EnumID.Medusa_ID:
                    drawItem(@"resource\image\boss\medusa.png", (int)EnumID.Medusa_ID);
                    break;
                case EnumID.Count_Dracula_ID:
                    drawItem(@"resource\image\boss\dracula.png", (int)EnumID.Count_Dracula_ID);
                    break;
                case EnumID.MorningStar_ID:
                    drawItem(@"resource\image\item\morningstar.png", (int)EnumID.MorningStar_ID);
                    break;
                case EnumID.SmallHeart_ID:
                    drawItem(@"resource\image\item\smallheart.png", (int)EnumID.SmallHeart_ID);
                    break;
                case EnumID.BigHeart_ID:
                    drawItem(@"resource\image\item\bigheart.png", (int)EnumID.BigHeart_ID);
                    break;
                case EnumID.MoneyBag400_ID:
                    drawItem(@"resource\image\item\moneybag400.png", (int)EnumID.MoneyBag400_ID);
                    break;
                case EnumID.MoneyBag700_ID:
                    drawItem(@"resource\image\item\moneybag700.png", (int)EnumID.MoneyBag700_ID);
                    break;
                case EnumID.PorkChop_ID:
                    drawItem(@"resource\image\item\porkchop.png", (int)EnumID.PorkChop_ID);
                    break;
                case EnumID.Crown_ID:
                    drawItem(@"resource\image\item\crown.png", (int)EnumID.Crown_ID);
                    break;
                case EnumID.TreasureChest_ID:
                    drawItem(@"resource\image\item\treasure.png", (int)EnumID.TreasureChest_ID);
                    break;
                case EnumID.DoubleShot_ID:
                    drawItem(@"resource\image\item\doubleshot.png", (int)EnumID.DoubleShot_ID);
                    break;
                case EnumID.TripleShot_ID:
                    drawItem(@"resource\image\item\tripleshot.png", (int)EnumID.TripleShot_ID);
                    break;
                case EnumID.SpiritBall_ID:
                    drawItem(@"resource\image\item\magicball.png", (int)EnumID.SpiritBall_ID);
                    break;
                case EnumID.Cross_ID:
                    drawItem(@"resource\image\item\cross.png", (int)EnumID.Cross_ID);
                    break;
                case EnumID.Axe_ID:
                    drawItem(@"resource\image\item\axe.png", (int)EnumID.Axe_ID);
                    break;
                case EnumID.Boomerang_ID:
                    drawItem(@"resource\image\item\boomerang.png", (int)EnumID.Boomerang_ID);
                    break;
                case EnumID.Knife_ID:
                    drawItem(@"resource\image\item\dagger.png", (int)EnumID.Knife_ID);
                    break;
                case EnumID.FireBomb_ID:
                    drawItem(@"resource\image\item\firebomb.png", (int)EnumID.FireBomb_ID);
                    break;
                case EnumID.StopWatch_ID:
                    drawItem(@"resource\image\item\watch.png", (int)EnumID.StopWatch_ID);
                    break;
                default:
                    break;
            }

        }

        private void pictureBox1_MouseDown_1(object sender, MouseEventArgs e)
        {
            textBox1.Text = curentType.ToString();
            currentMouse = new Point(e.X, e.Y);
            if (e.Button.Equals(MouseButtons.Left))
            {
                Draw(curentType);
            }

            if (e.Button.Equals(MouseButtons.Middle))
            {
                removeObject(currentMouse);
            }
        }


     
        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            currentMouse = new Point(e.X, e.Y);
            if (e.Button.Equals(MouseButtons.Left))
            {
                Draw(curentType);

            }
            if (e.Button.Equals(MouseButtons.Middle))
            {
                removeObject(currentMouse);
            }
        }

        private void batToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Count_Dracula_ID;
        }

        private void maskToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Medusa_ID;
        }

        private void batToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Bat_ID;
        }

        private void ghostToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.PhantomBat_ID;
        }

        private void catToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Pleaman_ID;
        }

        private void mermanToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Ghost_ID;
        }

        private void spearGuardToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SpearGuard_ID;
        }

        private void medusaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.MedusaHead_ID;
        }

        private void skeletonToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Skeletons_ID;
        }

        private void eagleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Eagle_ID;
        }

        private void bonePillarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BonePillar_ID;
        }

        private void fireToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Trap_ID;
        }

        private void fireToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Candle_ID;
        }

        private void tileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Brick_ID;
        }

        private void bigTileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.MovingPlatform_ID;
        }

        private void gateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Door_ID;
        }

        private void stairToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairRight_ID;
        }

        private void stairLeftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairLeft_ID;
        }

        private void smallHeartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallHeart_ID;
        }

        private void bigHeartToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BigHeart_ID;
        }

        private void axeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Axe_ID;
        }

        private void boomerangToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Boomerang_ID;
        }

        private void crossToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Cross_ID;
        }

        private void daggerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Knife_ID;
        }

        private void doubleShotToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.DoubleShot_ID;
        }

        private void fireBombToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.FireBomb_ID;
        }

        private void morningStarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.MorningStar_ID;
        }

        private void porkChopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.PorkChop_ID;           
        }

        private void trippleShotToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.TripleShot_ID;
        }

        private void ưToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            curentType = EnumID.StopWatch_ID;
        }

        private void magicBallToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SpiritBall_ID;
        }

        private void breakableToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Breakable_ID;
        }

        private void teleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Tele_ID;
        }

        private void moneyBag400ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.MoneyBag400_ID;
        }

        private void moneyBag700ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.MoneyBag700_ID;
        }

        private void treasureToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.TreasureChest_ID;
        }

        private void crowwnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Crown_ID;
        }

        private void drawItem(String path,int ID)
        {
            string pa = Path.Combine(Application.StartupPath, path);
            Bitmap bm = new Bitmap(Path.Combine(Application.StartupPath, path));
            if(ID == (int) EnumID.Brick_ID || ID == (int)EnumID.StairLeft_ID || ID == (int)EnumID.StairRight_ID 
                || ID == (int)EnumID.Door_ID || ID == (int)EnumID.StairTopLeft_ID || ID == (int)EnumID.StairTopRight_ID 
                || ID == (int)EnumID.StairBotLeft_ID || ID == (int)EnumID.StairBotRight_ID)
            {
                currentMouse = new Point((currentMouse.X / 32) * 32, (currentMouse.Y / 32) * 32);
            }
            DrawImage(pictureBox1.Image, bm, currentMouse, new Rectangle(0, 0, bm.Width, bm.Height));
            pictureBox1.Refresh();
            ObjectGame obj = new ObjectGame(bm, ID);
            obj.SetLocation(currentMouse.X, currentMouse.Y);
            addObject(obj);
        }

        private void stairTopLeftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairTopLeft_ID;
        }

        private void stairTopRightToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairTopRight_ID;

        }

        private void stairBotLeftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairBotLeft_ID;

        }

        private void stairBotRightToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.StairBotRight_ID;

        }
        private void brickToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Brick_ID;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {

        }

        void addObject(ObjectGame obj)
        {
            foreach (ObjectGame objectGame in listobjmap)
            {
                if (obj == objectGame)
                {
                    return;
                }
            }
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
                    if ((objectGame.location.X + objectGame.bm.Width) % 32 != 0)
                    {
                        numOfCol++;
                    }

                    if ((objectGame.location.Y + objectGame.bm.Height) % 32 != 0)
                    {
                        numOfRow++;
                    }

                    for (int col = 0; col < numOfCol; col++)
                    {
                        for (int row = 0; row < numOfRow; row++)
                        {
                            Point point = new Point((objectGame.location.X / 32) * 32 + col * 32, (objectGame.location.Y / 32) * 32 + row * 32);
                            int bitmapIndex = matTile[objectGame.location.Y / 32 + row, objectGame.location.X / 32 + col];
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
                            g.DrawRectangle(p, (objectGame.location.X / 32) * 32 + col * 32, (objectGame.location.Y / 32) * 32 + row * 32, 32, 32);
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
            if (clickPoint.X < obj.location.X || clickPoint.X > obj.location.X + obj.bm.Width || clickPoint.Y > obj.location.Y + obj.bm.Height || clickPoint.Y < obj.location.Y)
            {
                return false;
            }
            return true;
        }
        
    }
}
