using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
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
    Bee,

    // Ground
    Cargo,
    Door,
    Ladder,
    BigElevator,
    SmallElevator,
    BlueConveyor,
    YellowConveyor,
    SmallConveyor,

    Thorn,
    Box,
    BoxWall,
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
            initWorker();
        }

        private void initWorker()
        {
            if (worker != null)
            {
                worker.Dispose();
            }

            worker = new BackgroundWorker
            {
                WorkerReportsProgress = true,
                WorkerSupportsCancellation = true
            };
            worker.DoWork += DoWork;
            worker.RunWorkerCompleted += RunWorkerCompleted;
        }

        void DoWork(object sender, DoWorkEventArgs e)
        {
            if (worker.CancellationPending)
            {
                e.Cancel = true;
            }
            else
            {
                Cut(image);
            }
        }

        void RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            if (e.Cancelled)
            {
                // Display some message to the user that task has been
                // cancelled
            }
            else if (e.Error != null)
            {
                // Do something with the error
            }

            pictureBox2.Width = 32 * listTile.Count;
            pictureBox2.Height = 32;
            pictureBox2.BackgroundImage = new Bitmap(pictureBox2.Width, pictureBox2.Height);


            for (int i = 0; i < listTile.Count; i++)
            {
                DrawImage(pictureBox2.BackgroundImage, listTile[i], new Point(i * 32, 0), new Rectangle(0, 0, 32, 32));
            }
            canSave = true;
            pictureBox2.Refresh();
        }
        // ObjectGame curObj;

        List<Bitmap> listTile;
        Image image;
        int[,] matTile;
        int countCol, countRow;
        Bitmap curTile;

        public static Rectangle viewPort;
        public static List<ObjectGame> listobjmap;
        public static int scrHeight;
        QuadNode rootNode;
        int[,] listMatrix;

        int countMatrixCol, countMatrixRow;
        string writeMatrix, readMatrix;
        string fileDirectory;
        String fileName;
        Point startMouse;
        Point currentMouse;
        BackgroundWorker worker;
        bool canSave = false;

        // QuadNode rootNode;
        private void btn_New_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
            try
            {
                pictureBox1.BackgroundImage = Image.FromFile(openFileDialog1.FileName);
                image = (Image) pictureBox1.BackgroundImage.Clone();
                pictureBox1.Width = pictureBox1.BackgroundImage.Width;
                pictureBox1.Height = pictureBox1.BackgroundImage.Height;
                countCol = pictureBox1.Width / 32;
                countRow = pictureBox1.Height / 32;
                matTile = new int[countRow, countCol];
                pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
                DrawDash(countRow, countCol);
                canSave = false;
                worker.RunWorkerAsync();
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
            Graphics.FromImage(bmDrawTo).DrawImage(bmDraw, new Rectangle(pos.X, pos.Y, rectClip.Width, rectClip.Height), rectClip, GraphicsUnit.Pixel);
        }

        private void btn_Save_Click(object sender, EventArgs e)
        {
            if (!canSave)
            {
                MessageBox.Show("Image cutting is processing, Please wait!", "Inprogress", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            // saveFileDialog1.Filter = "Images|*.bmp;";
            ImageFormat format = ImageFormat.Png;
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                fileDirectory = Path.GetDirectoryName(saveFileDialog1.FileName);
                fileName = Path.GetFileName(saveFileDialog1.FileName);
                format = ImageFormat.Bmp;
                pictureBox2.BackgroundImage.Save(Path.Combine(fileDirectory, fileName + ".bmp"), format);
                //  StreamWriter writer = new StreamWriter(Path.Combine(fileDirectory,Name+"txt"));
                string text = "";
                text += listTile.Count + "\r\n";
                text += countRow + "\r\n";
                text += countCol + "\r\n";
                text += writeMatrix;
                File.WriteAllText(Path.Combine(fileDirectory, fileName + ".txt"), text);


                String s = "";

                StreamWriter writer = new StreamWriter(saveFileDialog1.FileName + "OBJ.txt");

                s += listobjmap.Count + "\r\n" + "\r\n";

                foreach (ObjectGame obj in listobjmap)
                {
                    s += (int) obj.ID + "\r\n";
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
                readMatrix = File.ReadAllText(Path.Combine(fileDirectory, fileName + ".txt"));
                countRow = pictureBox2.Height / 32;
                countCol = pictureBox2.Width / 32;
                matTile = new int[countRow, countCol];

                Cut(pictureBox2.BackgroundImage);
                decodeMatrix();


                // FileStream fileStream = new FileStream("")
                String readObj = File.ReadAllText(Path.Combine(fileDirectory, fileName + "OBJ.txt"));
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
            for (int i = 0; i < numOfObj; i++)
            {
                EnumID id = (EnumID)int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int x = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                currentIndex = readObj.IndexOf("\r\n", currentIndex) + 2;
                int y = int.Parse(readObj.Substring(currentIndex, readObj.IndexOf("\r\n", currentIndex) - currentIndex));
                ObjectGame obj = new ObjectGame(getImage((EnumID)id), id, new Point(x, y));
                listobjmap.Add(obj);
                currentIndex = readObj.IndexOf("\r\n\r\n", currentIndex) + 4;
            }

        }

        private Bitmap getImage(EnumID ID)
        {
            switch (ID)
            {
                case EnumID.Platform:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                case EnumID.BlastHornet:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\blast_hornet.png"));
                case EnumID.Shurikein:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\shurikein.png"));
                case EnumID.CarryArm:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\carry_arm.png"));
                case EnumID.HeadGunner:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\head_gunner.png"));
                case EnumID.Helit:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\helit.png"));
                case EnumID.NotoBanger:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\notor_banger.png"));
                case EnumID.Cargo:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\cargo.png"));
                case EnumID.Door:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\door.png"));
                case EnumID.BigElevator:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\big_elevetor.png"));
                case EnumID.SmallElevator:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_elevetor.png"));
                case EnumID.BlueConveyor:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\blue_conveyor.png"));
                case EnumID.YellowConveyor:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\yellow_conveyor.png"));
                case EnumID.SmallConveyor:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_conveyor.png"));
                case EnumID.Thorn:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\thorn.png"));
                case EnumID.Box:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\box.png"));
                case EnumID.BoxWall:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\box_wall.png"));
                case EnumID.Roof:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\roof.png"));
                case EnumID.UpGround:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\up_ground.png"));
                case EnumID.DownGround:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\down_ground.png"));
                case EnumID.SmallEnergy:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_energy.png"));
                case EnumID.BigEnergy:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\big_energy.png"));
                case EnumID.ChimeraArmor:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\chimera.png"));
                default:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
            }
        }

        private void buildBackground()
        {
            pictureBox1.Width = 32 * countMatrixCol;
            pictureBox1.Height = 32 * countMatrixRow;
            pictureBox1.BackgroundImage = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            for (int i = 0; i < countMatrixRow; i++)
            {
                for (int j = 0; j < countMatrixCol; j++)
                {
                    int x = i;
                    int a = listMatrix[i, j];
                    Bitmap tile = listTile[a];
                    DrawImage(pictureBox1.BackgroundImage, tile, new Point(j * 32, i * 32), new Rectangle(0, 0, 32, 32));

                }
            }
            pictureBox1.Width = pictureBox1.BackgroundImage.Width;
            pictureBox1.Height = pictureBox1.BackgroundImage.Height;
            pictureBox1.Image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            for (int i = 0; i < listobjmap.Count(); i++)
            {
                DrawImage(pictureBox1.Image, listobjmap[i].bm, listobjmap[i].topLeft, new Rectangle(0, 0, listobjmap[i].bm.Width, listobjmap[i].bm.Height));
            }
            pictureBox1.Refresh();
        }

        private void decodeMatrix()
        {

            int currentIndex = 0;
            countMatrixRow = int.Parse(readMatrix.Substring(0, readMatrix.IndexOf("\r\n", currentIndex) - currentIndex));
            currentIndex = readMatrix.IndexOf("\r\n", currentIndex) + 2;

            countMatrixCol = int.Parse(readMatrix.Substring(currentIndex, readMatrix.IndexOf("\r\n", currentIndex) - currentIndex));
            currentIndex = readMatrix.IndexOf("\r\n", currentIndex) + 2;
            listMatrix = new int[countMatrixRow, countMatrixCol];
            for (int i = 0; i < countMatrixRow; i++)
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
                currentIndex = readMatrix.IndexOf("\r\n", currentIndex) + 2;
            }
        }

        void Cut(Image Image) //get tile
        {
            //int a = 0;
            writeMatrix = "";
            long a = 0;
            long b = 0;
            long c = 0;
            long d = 0;
            for (int i = 0; i < countRow; i++)
            {
                for (int j = 0; j < countCol; j++)
                {
                    Bitmap bitMap = new Bitmap(32, 32);
                    int indexOf = 0;
                    a = DateTime.Now.Millisecond;
                    DrawImage(bitMap, Image, new Point(0, 0), new Rectangle(j * 32, i * 32, 32, 32));
                    b = DateTime.Now.Millisecond;
                    bool allowAdd = true;
                    foreach (Bitmap bm in listTile)
                    {
                        c = DateTime.Now.Millisecond;

                        if (Compare(bitMap, bm))
                        {
                            d =DateTime.Now.Millisecond;

                            allowAdd = false;
                            indexOf = listTile.IndexOf(bm);
                            matTile[i, j] = (int)bm.Tag;
                            break;
                        }

                    }
                    if (allowAdd)
                    {
                        bitMap.Tag = listTile.Count;
                        listTile.Add(bitMap);
                        matTile[i, j] = (int)bitMap.Tag;
                        writeMatrix += bitMap.Tag + " ";

                    }
                    else
                    {
                        writeMatrix += indexOf + " ";
                    }
                }
                int x = i;
                writeMatrix += Environment.NewLine;
            }

            //pictureBox2.Width = 32 * listTile.Count;
            //pictureBox2.Height = 32;
            //pictureBox2.BackgroundImage = new Bitmap(pictureBox2.Width, pictureBox2.Height);


            //for (int i = 0; i < listTile.Count; i++)
            //{
            //    DrawImage(pictureBox2.BackgroundImage, listTile[i], new Point(i * 32, 0), new Rectangle(0, 0, 32, 32));
            //}

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
                case EnumID.Megaman:
                    break;
                case EnumID.BlastHornet:
                    drawItem(@"resource\blast_hornet.png");
                    break;
                case EnumID.Byte:

                    break;
                case EnumID.Shurikein:
                    drawItem(@"resource\shurikein.png");
                    break;
                case EnumID.CarryArm:
                    drawItem(@"resource\carry_arm.png");
                    break;
                case EnumID.HeadGunner:
                    drawItem(@"resource\head_gunner.png");
                    break;
                case EnumID.Helit:
                    drawItem(@"resource\helit.png");
                    break;
                case EnumID.NotoBanger:
                    drawItem(@"resource\notor_banger.png");
                    break;
                case EnumID.Bee:
                    break;
                case EnumID.Door:
                    drawItem(@"resource\door.png");
                    break;
                case EnumID.Ladder:
                    break;
                case EnumID.Thorn:
                    drawItem(@"resource\thorn.png");
                    break;
                case EnumID.Box:
                    drawItem(@"resource\box.png");
                    break;
                case EnumID.Roof:
                    drawItem(@"resource\roof.png");
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
                    drawItem(@"resource\small_energy.png");
                    break;
                case EnumID.BigEnergy:
                    drawItem(@"resource\big_energy.png");
                    break;
                case EnumID.ChimeraArmor:
                    drawItem(@"resource\chimera.png");
                    break;
                case EnumID.MegamanBullet:
                    break;
                case EnumID.Cargo:
                    drawItem(@"resource\cargo.png");
                    break;
                case EnumID.BigElevator:
                    drawItem(@"resource\big_elevator.png");
                    break;
                case EnumID.SmallElevator:
                    drawItem(@"resource\small_elevator.png");
                    break;
                case EnumID.BoxWall:
                    drawItem(@"resource\box_wall.png");
                    break;
                case EnumID.UpGround:
                    drawItem(@"resource\up_ground.png");
                    break;
                case EnumID.DownGround:
                    drawItem(@"resource\down_ground.png");
                    break;
                case EnumID.Platform:
                    drawItem(@"resource\platform.png");
                    break;
                case EnumID.BlueConveyor:
                    drawItem(@"resource\blue_conveyor.png");
                    break;
                case EnumID.YellowConveyor:
                    drawItem(@"resource\yellow_conveyor.png");
                    break;
                case EnumID.SmallConveyor:
                    drawItem(@"resource\small_conveyor.png");
                    break;
                default:
                    drawItem(@"resource\platform.png");
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
                if (curentType != EnumID.Platform)
                {
                    Draw(curentType);
                }
                return;
            }

            if (e.Button.Equals(MouseButtons.Middle))
            {
                textBox1.Text = curentType.ToString();
                currentMouse = new Point(e.X, e.Y);

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
                    return;
                }
                else
                {
                    Bitmap bm = new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                    DrawImage(pictureBox1.Image, bm, startMouse, new Rectangle(0, 0, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y));
                    bm.Dispose();
                    pictureBox1.Refresh();

                }

            }

        }

        private void drawItem(String path)
        {
            Bitmap bm = new Bitmap(Path.Combine(Application.StartupPath, path));
            ObjectGame obj;
            if (curentType == EnumID.Platform)
            {
                if (startMouse.X >= currentMouse.X || startMouse.Y >= currentMouse.Y)
                {
                    return;
                }
                DrawImage(pictureBox1.Image, bm, startMouse, new Rectangle(0, 0, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y));
                obj = new ObjectGame(curentType, startMouse, currentMouse);
            }
            else
            {
                DrawImage(pictureBox1.Image, bm, currentMouse, new Rectangle(0, 0, bm.Width, bm.Height));
                obj = new ObjectGame(bm, curentType, currentMouse);
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

        private void conveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void blastHornetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BlastHornet;
        }

        private void shurikeinToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Shurikein;
        }

        private void headGunnerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.HeadGunner;
        }

        private void helitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Helit;
        }

        private void notoBangerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.NotoBanger;
        }

        private void carryArmToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.CarryArm;
        }

        private void cargoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Cargo;
        }

        private void doorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Door;
        }

        private void bigElevatorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BigElevator;
        }

        private void smallElevatorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallElevator;
        }

        private void yellowConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.YellowConveyor;
        }

        private void smallConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallConveyor;
        }

        private void conveyorToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            curentType = EnumID.BlueConveyor;
        }

        private void thornToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Thorn;
        }

        private void boxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Box;
        }

        private void breakableWallToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BoxWall;
        }

        private void roofToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Roof;
        }

        private void upGroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.UpGround;
        }

        private void downGroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.DownGround;
        }

        private void smallEnergyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallEnergy;
        }

        private void bigEnergyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BigEnergy;
        }

        private void chimeraArmorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.ChimeraArmor;
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
