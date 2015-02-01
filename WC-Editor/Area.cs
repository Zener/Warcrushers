using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Windows.Forms;


namespace WC_Editor
{
    

    public class Area
    {
        public int construccion;
        public int unidentro;
        public int unifuera;
        public int unienemigo;
        public int people;
        public int raceowner;
        public int racestriker;
        public int integrity;
        public int explored;
        public int evervisible;

        public void Reset()
        {
            construccion = 0;
            unidentro = 0;
            unifuera = 0;
            unienemigo = 0;
            people = 0;
            raceowner = 0;
            racestriker = 0;
            integrity = 0;
            explored = 0;
            evervisible = 0;
        }


        public void Refresh(Image img)
        {
        }


        public void Selecciona()
        {
        }


    }
}
