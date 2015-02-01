unit Area;

interface

uses  Graphics, ImgList, ExtCtrls, ComCtrls, StdCtrls, SysUtils, Types;

type
  TArea = class(TObject)
  private
    { Private declarations }
  public
    { Public declarations }
      construccion      :integer;
      unidentro         :integer;
      unifuera          :integer;
      unienemigo        :integer;
      people            :integer;
      raceowner         :integer;
      racestriker       :integer;
      integrity         :integer;
      explored          :integer;
      evervisible           :integer;

      procedure Reset();
      procedure Refresh(img: Timage);
      procedure Selecciona();
  end;

implementation

uses WCEditorMain, ValEdit;


procedure TArea.Reset();
begin
      construccion      := 0;
      unidentro         := 0;
      unifuera          := 0;
      unienemigo        := 0;
      people            := 0;
      raceowner         := 0;
      racestriker       := 0;
      integrity         := 0;
      explored          := 0;
      evervisible           := 0;

end;


procedure TArea.Refresh(img: Timage);
begin
   if (construccion < 0) then img.Canvas.Draw(0,0,FormMain.ImgFondo.Picture.Bitmap)
   else begin
      //DrawRect();
      if evervisible=1 then img.Canvas.Draw(-58*2,0,FormMain.Imgfondo.Picture.Bitmap)
      else img.Canvas.Draw(-58,0,FormMain.Imgfondo.Picture.Bitmap);
      if construccion >= 1 then img.Canvas.Draw(-(construccion-1)*58,0,FormMain.imgcons.Picture.Bitmap);
   end;
end;

procedure TArea.Selecciona();
begin;
   with FormMain.ValueListEditor1 do begin
      case construccion of
         -1: Values[Keys[1]] := 'INVALID';
         0: Values[Keys[1]] := 'NONE';
         1: Values[Keys[1]] := 'CAMP';
         2: Values[Keys[1]] := 'FORTRESS';
         3: Values[Keys[1]] := 'CASTLE';
         4: Values[Keys[1]] := 'VILLAGE';
         5: Values[Keys[1]] := 'CITADEL';
      end;
      Values[Keys[2]] := IntToStr(unidentro);
      Values[Keys[3]] := IntToStr(unifuera);
      Values[Keys[4]] := IntToStr(unienemigo);
      Values[Keys[5]] := IntToStr(people);
      case raceowner of
         0: Values[Keys[6]] := 'NONE';
         1: Values[Keys[6]] := 'HUMAN';
         2: Values[Keys[6]] := 'COMP';
      end;
      case racestriker of
         0: Values[Keys[7]] := 'NONE';
         1: Values[Keys[7]] := 'HUMAN';
         2: Values[Keys[7]] := 'COMP';
      end;
      Values[Keys[8]] := IntToStr(integrity);
      case explored of
         0: Values[Keys[9]] := 'NO';
         1: Values[Keys[9]] := 'YES';
      end;
      case evervisible of
         0: Values[Keys[10]] := 'NO';
         1: Values[Keys[10]] := 'YES';
      end;

   end;
end;

end.
