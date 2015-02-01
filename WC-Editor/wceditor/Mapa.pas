unit Mapa;

interface

uses Area, COntrols, Graphics, ImgList, ExtCtrls, ComCtrls, StdCtrls, Types;

type
  TMapa = class(TObject)
  private
    { Private declarations }
  public
    areas: array[0..4, 0..9] of TArea;
    inix, iniy: integer;
    inigold : integer;
    selx : integer;
    sely : integer;
    daytime: integer;
    dificulty: integer;
    procedure Reset();
    procedure Init();
    procedure Refresh();
    procedure DrawRect();
    procedure Build(i:integer);
    procedure Select(i,j:integer);
    procedure AreaOwner(i:integer);
    procedure Incrementa(e, val:integer);
    function SetValue(row,value:integer):integer;
    { Public declarations }
  end;

implementation
uses WCEditorMain;

procedure TMapa.DrawRect();
var i1, i2, i3, i4 :integer;
    var t1,t2: TRect;
begin
   if (areas[sely, selx].construccion < 0) then begin
      t1.Left := 0;
      t1.Top := 0;
      t1.Right := 640;
      t1.Bottom := 400;
      FormMain.display.Canvas.FillRect(t1);
      exit;
   end;
      i1 := 4+selx*7 * sely*2 - (selx-sely)*13;
      i2 := 2+(sely -selx)*13-10*3+selx*17;
      i3 := 1+i1 + selx;
      i4 := 3+i1+ i2;
      i1 := i1 mod 5;
      i2 := i2 mod 5;
      i3 := i3 mod 5;
      i4 := i4 mod 5;
      if i1 < 0 then i1 := i1+5;
      if i2 < 0 then i2 := i2+5;
      if i3 < 0 then i3 := i3+5;
      if i4 < 0 then i4 := i4+5;
      t1.Left := 0;
      t1.Top := 0;
      t1.Right := 320;
      t1.Bottom := 200;
      t2.Left := 320*i1;
      t2.Top := 0;
      t2.Right := (320*(i1+1));
      t2.Bottom := 200;
      FormMain.display.Canvas.BrushCopy(t1, FormMain.ImgGround.Picture.Bitmap, t2, clNone);
      t1.Left := 320-1;
      t1.Top := 0;
      t1.Right := 640-1;
      t1.Bottom := 200;
      t2.Left := 320*i2;
      t2.Top := 0;
      t2.Right := (320*(i2+1));
      t2.Bottom := 200;
      FormMain.display.Canvas.BrushCopy(t1, FormMain.ImgGround.Picture.Bitmap, t2, clNone);
      t1.Left := 0;
      t1.Top := 200;
      t1.Right := 320;
      t1.Bottom := 400;
      t2.Left := 320*i3;
      t2.Top := 0;
      t2.Right := (320*(i3+1))-1;
      t2.Bottom := 200;
      FormMain.display.Canvas.BrushCopy(t1, FormMain.ImgGround.Picture.Bitmap, t2, clNone);
      t1.Left := 320-1;
      t1.Top := 200;
      t1.Right := 640-1;
      t1.Bottom := 400;
      t2.Left := 320*i4;
      t2.Top := 0;
      t2.Right := (320*(i4+1))-1;
      t2.Bottom := 200;
      FormMain.display.Canvas.BrushCopy(t1, FormMain.ImgGround.Picture.Bitmap, t2, clNone);
end;


procedure Tmapa.Refresh();
var     i, j , sel:integer;
        img : TImage;
begin
   sel := 0;
   while (sel < FormMain.GroupBox1.controlcount) and (not (FormMain.GroupBox1.Controls[sel] is TImage)) do sel := sel+1;

   for i := 0 to 4 do
      for j := 0 to 9 do begin
         img := TImage(FormMain.GroupBox1.Controls[sel]);
         areas[i, j].Refresh(img);
         sel := sel + 1;
         while (sel < FormMain.GroupBox1.controlcount) and (not (FormMain.GroupBox1.Controls[sel] is TImage)) do sel := sel+1;
         if sel >= FormMain.GroupBox1.controlcount then exit;
      end;
   //Select(sely, selx);
end;

procedure Tmapa.Init();
var     i, j :integer;
begin
   for i := 0 to 4 do
      for j := 0 to 9 do begin
        areas[i, j] := TArea.create;
      end;
   reset();
   Select(0,0);
end;

procedure Tmapa.Reset();
var     i, j       :integer;
begin
   for i := 0 to 4 do
      for j := 0 to 9 do begin
        areas[i, j].Reset();
      end;
   Refresh;
   //Select(sely, selx);
end;

procedure Tmapa.Select(i,j:integer);
begin
   selx := j;
   sely := i;
   FormMain.selected.left := 16+j*64;
   FormMain.selected.top := 12+i*40;
   areas[sely, selx].Selecciona();
   DrawRect();
   Refresh;
end;

procedure Tmapa.Build(i:integer);
begin
   areas[sely, selx].construccion := i;
   if (i > 0) then areas[sely, selx].integrity := 100
   else areas[sely, selx].integrity := 0;
   DrawRect();
   Refresh;
   Select(sely, selx);
end;

procedure Tmapa.AreaOwner(i:integer);
begin
   areas[sely, selx].raceowner := i;
   if (i = 0) then areas[sely, selx].racestriker := 0;
   if (i = 1) then areas[sely, selx].racestriker := 2;
   if (i = 2) then areas[sely, selx].racestriker := 1;
   DrawRect();
   Refresh;
   Select(sely, selx);
end;

function TMapa.SetValue(row,value:integer):integer;
begin
{   case row of
      1: begin
            if value < 0 then value := -1
            else if value > 4 then value := 4;
            areas[sely, selx].construccion := value;
         end;
      2: begin
            if value < 0 then value := 0
            else if value > 100 then value := 100;
            areas[sely, selx].unidentro := value;
         end;
      3: begin
            if value < 0 then value := 0
            else if value > 100 then value := 100;
            areas[sely, selx].unifuera := value;
         end;
      4: begin
            if value < 0 then value := 0
            else if value > 100 then value := 100;
            areas[sely, selx].unienemigo := value;
         end;
      5: begin
            if value < 0 then value := 0
            else if value > 100 then value := 100;
            areas[sely, selx].people := value;
         end;
      6: begin
            if value < 0 then value := 0
            else if value > 1 then value := 1;
            areas[sely, selx].raceowner := value;
         end;
      7: begin
            if value < 0 then value := 0
            else if value > 1 then value := 1;
            areas[sely, selx].racestriker := value;
         end;
      8: begin
            if value < 0 then value := 0
            else if value > 100 then value := 100;
            areas[sely, selx].integrity := value;
         end;

   end;
   Result := value;}
  // areas[sely, selx].Selecciona();
end;

procedure TMapa.Incrementa(e, val:integer);
var i, max:integer;
begin
   if e = 0 then begin
      i := areas[sely, selx].unidentro+val;
      if (i > 100) then i := 100;
      if (i < 0) then i := 0;
      areas[sely, selx].unidentro := i;
   end;
   if e = 1 then begin
      i := areas[sely, selx].unifuera+val;
      if (i > 100) then i := 100;
      if (i < 0) then i := 0;
      areas[sely, selx].unifuera := i;
   end;
   if e = 2 then begin
      i := areas[sely, selx].unienemigo+val;
      if (i > 100) then i := 100;
      if (i < 0) then i := 0;
      areas[sely, selx].unienemigo := i;
   end;
   if e = 3 then begin
      i := areas[sely, selx].people+val;
      if (i > 100) then i := 100;
      if (i < 0) then i := 0;
      areas[sely, selx].people := i;
   end;
    if e = 4 then begin
      i := areas[sely, selx].integrity+val;
      if (i > 100) then i := 100;
      if (i < 1) then i := 1;
      areas[sely, selx].integrity := i;
   end;

   //DrawRect();
//   Refresh;
   Select(sely, selx);
end;



end.
