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
        public int ID;
        public int indexanotherobj;
        public int index;
        public Point location;
        public List<String> listIDInTree;
       
        public Rectangle moveSpace;
        public ObjectGame()
        { }
        public ObjectGame(Bitmap b, int id)
        {
            bm = b;
            ID = id;
            moveSpace = new Rectangle();
            indexanotherobj = -1;
        }

        public void SetLocation(int x, int y)
        {
            location = new Point(x, y);
        }

        public Point GetLocation()
        {
            return new Point(location.X, location.Y);
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
            if (firstObject.location != secondObject.location)
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
            if (firstObject.location != secondObject.location)
            {
                return true;
            }
            return false;
        }
    }
}
