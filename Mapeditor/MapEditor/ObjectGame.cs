using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace MapEditor
{


    public class ObjectGame
    {
        public Bitmap bm;
        public EnumID ID;
        public int index;
        public Point topLeft;
        public int width;
        public int height;
        public List<String> listIDInTree;
       
        public ObjectGame()
        { }

        public ObjectGame(Bitmap bm, EnumID ID, Point topLeft)
        {
            this.bm = bm;
            this.ID = ID;
            this.topLeft = topLeft;
            width = bm.Width;
            height = bm.Height;
        }

        public ObjectGame(EnumID ID, Point topLeft, Point botRight)
        {
            int a = Math.Abs(botRight.X - topLeft.X);
            int b = Math.Abs(botRight.Y - topLeft.Y);
            bm = new Bitmap(Math.Abs(botRight.X - topLeft.X), Math.Abs(botRight.Y - topLeft.Y));
            this.ID = ID;
            this.topLeft = topLeft;
            width = bm.Width;
            height = bm.Height;
        }

        public Point GetLocation()
        {
            return new Point(topLeft.X, topLeft.Y);
        }

        //public Point GetLocation()
        //{
        //    return location;
        //}

        public static bool operator == (ObjectGame firstObject, ObjectGame secondObject)
        {
            if (firstObject.ID != secondObject.ID)
            {
                return false;
            }
            if (firstObject.topLeft != secondObject.topLeft)
            {
                return false;
            }
            return true;
        }

        public static bool operator !=(ObjectGame firstObject, ObjectGame secondObject)
        {
            if (firstObject.ID != secondObject.ID)
            {
                return true;
            }
            if (firstObject.topLeft != secondObject.topLeft)
            {
                return true;
            }
            return false;
        }
    }
}
