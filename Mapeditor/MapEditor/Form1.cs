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
    Megaman_ID,
    MegamanBullet_ID,
    CheckPoint_ID,

    // Boss
    BlastHornet_ID,
    Byte_ID,
    Shurikein_ID,

    // Creep
    CarryArm_ID,
    LeftFaceHeadGunner_ID,
    RightFaceHeadGunner_ID,
    Helit_ID,
    NotorBanger_ID,
    Bee_ID,

    // Ground
    Cargo_ID,
    Door_ID,
    BigElevator_ID,
    SmallElevator_ID,
    LeftBlueConveyor_ID,
    RightBlueConveyor_ID,
    LeftYellowConveyor_ID,
    RightYellowConveyor_ID,
    LeftSmallConveyor_ID,
    RightSmallConveyor_ID,
    Thorn_ID,
    Box_ID,
    DoubleBox_ID,
    TrippleBox_ID,
    QuadraBox_ID,
    VerticalBombBox_ID,
    HorizontalBombBox_ID,
    Roof_ID,
    BreakPlatform_ID,
    UpPlatform_ID,
    DownPlatform_ID,
    Platform_ID,
    WallHoleLeft_ID,
    WallHoleRight_ID,
    HallHole_ID,

    //weapon
    Canon_ID,
    GunnerRocket_ID,
    HeliRocket_ID,
    ByteBomb_ID,

    //Item
    SmallEnergy_ID,
    BigEnergy_ID,
    ChimeraArmor_ID,
    CameraRange_ID
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
            listCameraRange = new List<Rectangle>();
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

            Graphics g = Graphics.FromImage(pictureBox2.BackgroundImage);
            float[] dashValue = { 5, 2 };


            Pen p = new Pen(Color.Silver);
            p.DashPattern = dashValue;
            for (int i = 0; i < listTile.Count; i++)
            {
                g.DrawLine(p, new Point(i * 32, 0), new Point(i * 32, pictureBox2.Height));
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
        public static List<Rectangle> listCameraRange;
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
                //worker.RunWorkerAsync();
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
            //if (!canSave)
            //{
            //    MessageBox.Show("Image cutting is processing, Please wait!", "Inprogress", MessageBoxButtons.OK, MessageBoxIcon.Error);
            //    return;
            //}

            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            // saveFileDialog1.Filter = "Images|*.bmp;";
            ImageFormat format = ImageFormat.Png;
            if (saveFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                //fileDirectory = Path.GetDirectoryName(saveFileDialog1.FileName);
                //fileName = Path.GetFileName(saveFileDialog1.FileName);
                //format = ImageFormat.Bmp;
                //pictureBox2.BackgroundImage.Save(Path.Combine(fileDirectory, fileName + ".bmp"), format);
                ////  StreamWriter writer = new StreamWriter(Path.Combine(fileDirectory,Name+"txt"));
                //string text = "";
                //text += listTile.Count + "\r\n";
                //text += countRow + "\r\n";
                //text += countCol + "\r\n";
                //text += writeMatrix;
                //File.WriteAllText(Path.Combine(fileDirectory, fileName + ".txt"), text);


                String objString = "";

                StreamWriter objWriter = new StreamWriter(saveFileDialog1.FileName + "OBJ.txt");

                objString += listobjmap.Count + "\r\n" + "\r\n";

                foreach (ObjectGame obj in listobjmap)
                {
                    objString += (int) obj.ID + "\r\n";
                    objString += obj.topLeft.X + "\r\n";
                    objString += obj.topLeft.Y + "\r\n";
                    objString += obj.width + "\r\n";
                    objString += obj.height + "\r\n";
                    objString += "\r\n";
                }
                objWriter.Write(objString);
                objWriter.Close();

                String cameraString = "";

                StreamWriter writer = new StreamWriter(saveFileDialog1.FileName + "CAM.txt");

                cameraString += listCameraRange.Count + "\r\n" + "\r\n";
                foreach (Rectangle rect in listCameraRange)
                {
                    cameraString += rect.Left + "\r\n";
                    cameraString += rect.Top + "\r\n";
                    cameraString += rect.Width + "\r\n";
                    cameraString += rect.Height + "\r\n";
                    cameraString += "\r\n";
                }
                writer.Write(cameraString);
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
                case EnumID.Platform_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                case EnumID.BlastHornet_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\blast_hornet.png"));
                case EnumID.Shurikein_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\shurikein.png"));
                case EnumID.CarryArm_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\carry_arm.png"));
                case EnumID.LeftFaceHeadGunner_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\left_face_head_gunner.png"));
                case EnumID.Helit_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\helit.png"));
                case EnumID.NotorBanger_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\notor_banger.png"));
                case EnumID.Cargo_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\cargo.png"));
                case EnumID.Door_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\door.png"));
                case EnumID.BigElevator_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\big_elevetor.png"));
                case EnumID.SmallElevator_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_elevetor.png"));
                case EnumID.Thorn_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\thorn.png"));
                case EnumID.Box_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\box.png"));
                case EnumID.Roof_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\roof.png"));
                case EnumID.UpPlatform_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\up_ground.png"));
                case EnumID.DownPlatform_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\down_ground.png"));
                case EnumID.SmallEnergy_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_energy.png"));
                case EnumID.BigEnergy_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\big_energy.png"));
                case EnumID.ChimeraArmor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\chimera.png"));
                case EnumID.Byte_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\byte.png"));
                case EnumID.RightFaceHeadGunner_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\right_face_head_gunner.png"));
                case EnumID.LeftBlueConveyor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\left_blue_conveyor.png"));
                case EnumID.RightBlueConveyor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\right_blue_conveyor.png"));
                case EnumID.LeftYellowConveyor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\left_yellow_conveyor.png"));
                case EnumID.RightYellowConveyor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\right_yellow_conveyor.png"));
                case EnumID.LeftSmallConveyor_ID:
                case EnumID.RightSmallConveyor_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\small_conveyor.png"));
                case EnumID.CameraRange_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\platform.png"));
                case EnumID.CheckPoint_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\checkpoint.png"));
                case EnumID.DoubleBox_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\double_box.png"));
                case EnumID.TrippleBox_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\tripple_box.png"));
                case EnumID.QuadraBox_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\quadra_box.png"));
                case EnumID.VerticalBombBox_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\vertical_bomb_box.png"));
                case EnumID.HorizontalBombBox_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\horizontal_bomb_box.png"));
                case EnumID.WallHoleLeft_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\wall_hole_left.png"));
                case EnumID.WallHoleRight_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\wall_hole_right.png"));
                case EnumID.HallHole_ID:
                    return new Bitmap(Path.Combine(Application.StartupPath, @"resource\hall_hole.png"));
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
                    DrawImage(bitMap, Image, new Point(0, 0), new Rectangle(j * 32, i * 32, 32, 32));
                    bool allowAdd = true;
                    foreach (Bitmap bm in listTile)
                    {
                        if (Compare(bitMap, bm))
                        {
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
                        writeMatrix += bitMap.Tag + "\t";

                    }
                    else
                    {
                        writeMatrix += indexOf + "\t";
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
                case EnumID.Megaman_ID:
                    break;
                case EnumID.BlastHornet_ID:
                    drawItem(@"resource\blast_hornet.png");
                    break;
                case EnumID.Shurikein_ID:
                    drawItem(@"resource\shurikein.png");
                    break;
                case EnumID.CarryArm_ID:
                    drawItem(@"resource\carry_arm.png");
                    break;
                case EnumID.LeftFaceHeadGunner_ID:
                    drawItem(@"resource\head_gunner.png");
                    break;
                case EnumID.Helit_ID:
                    drawItem(@"resource\helit.png");
                    break;
                case EnumID.NotorBanger_ID:
                    drawItem(@"resource\notor_banger.png");
                    break;
                case EnumID.Bee_ID:
                    break;
                case EnumID.Door_ID:
                    drawItem(@"resource\door.png");
                    break;
                case EnumID.Thorn_ID:
                    drawItem(@"resource\thorn.png");
                    break;
                case EnumID.Box_ID:
                    drawItem(@"resource\box.png");
                    break;
                case EnumID.Roof_ID:
                    drawItem(@"resource\roof.png");
                    break;
                case EnumID.SmallEnergy_ID:
                    drawItem(@"resource\small_energy.png");
                    break;
                case EnumID.BigEnergy_ID:
                    drawItem(@"resource\big_energy.png");
                    break;
                case EnumID.ChimeraArmor_ID:
                    drawItem(@"resource\chimera.png");
                    break;
                case EnumID.MegamanBullet_ID:
                    break;
                case EnumID.Cargo_ID:
                    drawItem(@"resource\cargo.png");
                    break;
                case EnumID.BigElevator_ID:
                    drawItem(@"resource\big_elevator.png");
                    break;
                case EnumID.SmallElevator_ID:
                    drawItem(@"resource\small_elevator.png");
                    break;
                case EnumID.UpPlatform_ID:
                    drawItem(@"resource\up_ground.png");
                    break;
                case EnumID.DownPlatform_ID:
                    drawItem(@"resource\down_ground.png");
                    break;
                case EnumID.Platform_ID:
                    drawItem(@"resource\platform.png");
                    break;
                case EnumID.Byte_ID:
                    drawItem(@"resource\byte.png");
                    break;
                case EnumID.RightFaceHeadGunner_ID:
                    drawItem(@"resource\right_face_head_gunner.png");
                    break;
                case EnumID.LeftBlueConveyor_ID:
                    drawItem(@"resource\left_blue_conveyor.png");
                    break;
                case EnumID.RightBlueConveyor_ID:
                    drawItem(@"resource\right_blue_conveyor.png");
                    break;
                case EnumID.LeftYellowConveyor_ID:
                    drawItem(@"resource\left_yellow_conveyor.png");
                    break;
                case EnumID.RightYellowConveyor_ID:
                    drawItem(@"resource\right_yellow_conveyor.png");
                    break;
                case EnumID.LeftSmallConveyor_ID:
                case EnumID.RightSmallConveyor_ID:
                    drawItem(@"resource\small_conveyor.png");
                    break;
                case EnumID.CameraRange_ID:
                    drawItem(@"resource\platform.png");
                    break;
                case EnumID.CheckPoint_ID:
                    drawItem(@"resource\checkpoint.png");
                    break;
                case EnumID.DoubleBox_ID:
                    drawItem(@"resource\double_box.png");
                    break;
                case EnumID.TrippleBox_ID:
                    drawItem(@"resource\tripple_box.png");
                    break;
                case EnumID.QuadraBox_ID:
                    drawItem(@"resource\quadra_box.png");
                    break;
                case EnumID.VerticalBombBox_ID: 
                    drawItem(@"resource\vertical_bomb_box.png");
                    break;
                case EnumID.HorizontalBombBox_ID:
                    drawItem(@"resource\horizontal_bomb_box.png");
                    break;
                case EnumID.WallHoleLeft_ID:
                    drawItem(@"resource\wall_hole_left.png");
                    break;
                case EnumID.WallHoleRight_ID:
                    drawItem(@"resource\wall_hole_right.png");
                    break;
                case EnumID.HallHole_ID:
                    drawItem(@"resource\hall_hole.png");
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
                if (curentType == EnumID.Platform_ID || curentType == EnumID.CameraRange_ID)
                {
                    return;
                }
                Draw(curentType);
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
                if (curentType == EnumID.Platform_ID || curentType == EnumID.CameraRange_ID)
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

            if (curentType == EnumID.CameraRange_ID)
            {
                if (startMouse.X >= currentMouse.X || startMouse.Y >= currentMouse.Y)
                {
                    return;
                }
                DrawImage(pictureBox1.Image, bm, startMouse, new Rectangle(0, 0, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y));
                Rectangle rect = new Rectangle(startMouse.X, startMouse.Y, currentMouse.X - startMouse.X, currentMouse.Y - startMouse.Y);
                pictureBox1.Refresh();
                listCameraRange.Add(rect);
                return;
            }

            if (curentType == EnumID.Platform_ID)
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
                if (curentType == EnumID.Platform_ID || curentType == EnumID.CameraRange_ID)
                {
                    Draw(curentType);
                }
                return;
            }
        }

        private void platformToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Platform_ID;
        }

        private void pictureBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            textBox1.Text = curentType.ToString();
            currentMouse = new Point(e.X, e.Y);

            removeObject(currentMouse);
            return;
        }

        private void blastHornetToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BlastHornet_ID;
        }

        private void shurikeinToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Shurikein_ID;
        }

        private void headGunnerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.LeftFaceHeadGunner_ID;
        }

        private void helitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Helit_ID;
        }

        private void notoBangerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.NotorBanger_ID;
        }

        private void carryArmToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.CarryArm_ID;
        }

        private void cargoToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Cargo_ID;
        }

        private void doorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Door_ID;
        }

        private void bigElevatorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BigElevator_ID;
        }

        private void smallElevatorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallElevator_ID;
        }

        private void yellowConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.LeftYellowConveyor_ID;
        }

        private void smallConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // TODO
            curentType = EnumID.LeftSmallConveyor_ID;
        }

        private void conveyorToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            curentType = EnumID.LeftBlueConveyor_ID;
        }


        private void thornToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Thorn_ID;
        }

        private void boxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Box_ID;
        }

        private void roofToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.Roof_ID;
        }

        private void upGroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.UpPlatform_ID;
        }

        private void downGroundToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.DownPlatform_ID;
        }

        private void smallEnergyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.SmallEnergy_ID;
        }

        private void bigEnergyToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.BigEnergy_ID;
        }

        private void chimeraArmorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.ChimeraArmor_ID;
        }

        private void cameraToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
            curentType = EnumID.CameraRange_ID;
        }

        private void rightFaceHeadGunnerToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.RightFaceHeadGunner_ID;
        }

        private void rightYellowConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.RightYellowConveyor_ID;
        }

        private void rightBlueConveyprToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.RightBlueConveyor_ID;
        }

        private void trippleBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.TrippleBox_ID;
        }

        private void quadraBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.QuadraBox_ID;
        }

        private void verticalBombBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.VerticalBombBox_ID;
        }

        private void horizontalBombBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.HorizontalBombBox_ID;
        }

        private void rightSmallConveyorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.RightSmallConveyor_ID;
        }

        private void checkpointToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.CheckPoint_ID;
        }

        private void doubleBoxToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.DoubleBox_ID;
        }

        private void wallHoleLeftToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.WallHoleLeft_ID;
        }

        private void wallHoleRightToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.WallHoleRight_ID;
        }

        private void hallHoleToolStripMenuItem_Click(object sender, EventArgs e)
        {
            curentType = EnumID.HallHole_ID;
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

                  
                    Point point = new Point(objectGame.topLeft.X, objectGame.topLeft.Y);
                    DrawImage(pictureBox1.Image, image, point, new Rectangle(objectGame.topLeft.X, objectGame.topLeft.Y, objectGame.width, objectGame.height));

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
