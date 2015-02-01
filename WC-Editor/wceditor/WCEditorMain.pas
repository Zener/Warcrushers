unit WCEditorMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Menus, ToolWin, ActnMan, ActnCtrls, ExtCtrls, ComCtrls, StdCtrls,
  ImgList, Grids, ValEdit, Mapa, Area, Buttons, ActnList, GoldForm;

type
  TFormMain = class(TForm)
    MainMenu1: TMainMenu;
    File1: TMenuItem;
    Open1: TMenuItem;
    New1: TMenuItem;
    Save1: TMenuItem;
    SaveAs1: TMenuItem;
    Quit1: TMenuItem;
    PageControl1: TPageControl;
    GroupBox1: TGroupBox;
    Image1: TImage;
    Image2: TImage;
    Image3: TImage;
    Image4: TImage;
    Image5: TImage;
    Image6: TImage;
    Image7: TImage;
    Image8: TImage;
    Image9: TImage;
    Image10: TImage;
    Image11: TImage;
    Image12: TImage;
    Image13: TImage;
    Image14: TImage;
    Image15: TImage;
    Image16: TImage;
    Image17: TImage;
    Image18: TImage;
    Image19: TImage;
    Image20: TImage;
    Image21: TImage;
    Image22: TImage;
    Image23: TImage;
    Image24: TImage;
    Image25: TImage;
    Image26: TImage;
    Image27: TImage;
    Image28: TImage;
    Image29: TImage;
    Image30: TImage;
    Image31: TImage;
    Image32: TImage;
    Image33: TImage;
    Image34: TImage;
    Image35: TImage;
    Image36: TImage;
    Image37: TImage;
    Image38: TImage;
    Image39: TImage;
    Image40: TImage;
    Image41: TImage;
    Image42: TImage;
    Image43: TImage;
    Image44: TImage;
    Image45: TImage;
    Image46: TImage;
    Image47: TImage;
    Image48: TImage;
    Image49: TImage;
    Image50: TImage;
    ImageList1: TImageList;
    StatusBar1: TStatusBar;
    ImgFondo: TImage;
    Selected: TLabel;
    refresh: TBitBtn;
    TabSheet1: TTabSheet;
    imgcons: TImage;
    display: TImage;
    ImgGround: TImage;
    TabSheet2: TTabSheet;
    ButInv: TBitBtn;
    ButNone: TBitBtn;
    ButCamp: TBitBtn;
    ButVillage: TBitBtn;
    ButFortress: TBitBtn;
    ButCastle: TBitBtn;
    ButCitadel: TBitBtn;
    GroupBox2: TGroupBox;
    BitBtn1: TBitBtn;
    BitBtn2: TBitBtn;
    BitBtn3: TBitBtn;
    GroupBox3: TGroupBox;
    ValueListEditor1: TValueListEditor;
    UpDown1: TUpDown;
    UpDown2: TUpDown;
    UpDown3: TUpDown;
    UpDown4: TUpDown;
    GroupBox4: TGroupBox;
    ValueListEditor2: TValueListEditor;
    UpDown5: TUpDown;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    BitBtn4: TBitBtn;
    BitBtn5: TBitBtn;
    BitBtn6: TBitBtn;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    procedure FormCreate(Sender: TObject);
    procedure New1Click(Sender: TObject);
    procedure Image1Click(Sender: TObject);
    procedure Image2Click(Sender: TObject);
    procedure Image3Click(Sender: TObject);
    procedure ValueListEditor1SetEditText(Sender: TObject; ACol,
      ARow: Integer; const Value: String);
    procedure refreshClick(Sender: TObject);
    procedure Image4Click(Sender: TObject);
    procedure Image5Click(Sender: TObject);
    procedure Image6Click(Sender: TObject);
    procedure Image7Click(Sender: TObject);
    procedure Image8Click(Sender: TObject);
    procedure Image9Click(Sender: TObject);
    procedure Image10Click(Sender: TObject);
    procedure Image11Click(Sender: TObject);
    procedure Image12Click(Sender: TObject);
    procedure Image13Click(Sender: TObject);
    procedure Image14Click(Sender: TObject);
    procedure Image15Click(Sender: TObject);
    procedure Image16Click(Sender: TObject);
    procedure Image17Click(Sender: TObject);
    procedure Image18Click(Sender: TObject);
    procedure Image19Click(Sender: TObject);
    procedure Image20Click(Sender: TObject);
    procedure Image21Click(Sender: TObject);
    procedure Image22Click(Sender: TObject);
    procedure Image23Click(Sender: TObject);
    procedure Image24Click(Sender: TObject);
    procedure Image25Click(Sender: TObject);
    procedure Image26Click(Sender: TObject);
    procedure Image27Click(Sender: TObject);
    procedure Image28Click(Sender: TObject);
    procedure Image29Click(Sender: TObject);
    procedure Image30Click(Sender: TObject);
    procedure Image31Click(Sender: TObject);
    procedure Image32Click(Sender: TObject);
    procedure Image33Click(Sender: TObject);
    procedure Image34Click(Sender: TObject);
    procedure Image35Click(Sender: TObject);
    procedure Image36Click(Sender: TObject);
    procedure Image37Click(Sender: TObject);
    procedure Image38Click(Sender: TObject);
    procedure Image39Click(Sender: TObject);
    procedure Image40Click(Sender: TObject);
    procedure Image41Click(Sender: TObject);
    procedure Image42Click(Sender: TObject);
    procedure Image43Click(Sender: TObject);
    procedure Image44Click(Sender: TObject);
    procedure Image45Click(Sender: TObject);
    procedure Image46Click(Sender: TObject);
    procedure Image47Click(Sender: TObject);
    procedure Image48Click(Sender: TObject);
    procedure Image49Click(Sender: TObject);
    procedure Image50Click(Sender: TObject);
    procedure ButInvClick(Sender: TObject);
    procedure ButNoneClick(Sender: TObject);
    procedure ButCampClick(Sender: TObject);
    procedure ButFortressClick(Sender: TObject);
    procedure ButCastleClick(Sender: TObject);
    procedure ButVillageClick(Sender: TObject);
    procedure ButCitadelClick(Sender: TObject);
    procedure BitBtn1Click(Sender: TObject);
    procedure BitBtn2Click(Sender: TObject);
    procedure BitBtn3Click(Sender: TObject);
    procedure UpDown1Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown2Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown3Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown4Click(Sender: TObject; Button: TUDBtnType);
    procedure UpDown5Click(Sender: TObject; Button: TUDBtnType);
    procedure SaveAs1Click(Sender: TObject);
    procedure Save1Click(Sender: TObject);
    procedure SaveMap();
    procedure LoadMap();
    procedure Open1Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure BitBtn5Click(Sender: TObject);
    procedure BitBtn4Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FormMain: TFormMain;
  map: TMapa;


implementation

{$R *.dfm}

procedure TFormMain.FormCreate(Sender: TObject);
begin
    map := TMapa.create;
    map.Init;
    left := 0;
    top := 0;
end;


procedure TFormMain.New1Click(Sender: TObject);
begin
   map.reset();
end;


procedure TFormMain.ValueListEditor1SetEditText(Sender: TObject; ACol,
  ARow: Integer; const Value: String);
var   val: integer;
      sval : string;
begin
   if (value = '') or (value = '-') then exit;
   try
     val := StrToInt(Value);
     sval := IntToStr(map.setValue(arow, val));
   except
      on EConvertError do exit;
   end;
end;


procedure TFormMain.refreshClick(Sender: TObject);
begin
   map.Refresh;
   map.Select(map.sely, map.selx);
end;


procedure TFormMain.Image1Click(Sender: TObject);
begin
   map.Select(0,0);
end;

procedure TFormMain.Image2Click(Sender: TObject);
begin
   map.Select(0,1);
end;

procedure TFormMain.Image3Click(Sender: TObject);
begin
    map.Select(0,2);
end;

procedure TFormMain.Image4Click(Sender: TObject);
begin
      map.Select(0,3);
end;

procedure TFormMain.Image5Click(Sender: TObject);
begin
      map.Select(0,4);
end;

procedure TFormMain.Image6Click(Sender: TObject);
begin
      map.Select(0,5);
end;

procedure TFormMain.Image7Click(Sender: TObject);
begin
      map.Select(0,6);
end;

procedure TFormMain.Image8Click(Sender: TObject);
begin
   map.Select(0,7);
end;

procedure TFormMain.Image9Click(Sender: TObject);
begin
   map.Select(0,8);
end;

procedure TFormMain.Image10Click(Sender: TObject);
begin
   map.Select(0,9);
end;

procedure TFormMain.Image11Click(Sender: TObject);
begin
   map.Select(1,0);
end;

procedure TFormMain.Image12Click(Sender: TObject);
begin
   map.Select(1,1);
end;

procedure TFormMain.Image13Click(Sender: TObject);
begin
map.Select(1,2);
end;

procedure TFormMain.Image14Click(Sender: TObject);
begin
   map.Select(1,3);
end;

procedure TFormMain.Image15Click(Sender: TObject);
begin
   map.Select(1,4);
end;

procedure TFormMain.Image16Click(Sender: TObject);
begin
   map.Select(1,5);
end;

procedure TFormMain.Image17Click(Sender: TObject);
begin
   map.Select(1,6);
end;

procedure TFormMain.Image18Click(Sender: TObject);
begin
   map.Select(1,7);
end;

procedure TFormMain.Image19Click(Sender: TObject);
begin
   map.Select(1,8);
end;

procedure TFormMain.Image20Click(Sender: TObject);
begin
   map.Select(1,9);
end;

procedure TFormMain.Image21Click(Sender: TObject);
begin
   map.Select(2,0);
end;

procedure TFormMain.Image22Click(Sender: TObject);
begin
   map.Select(2,1);
end;

procedure TFormMain.Image23Click(Sender: TObject);
begin
   map.Select(2,2);
end;

procedure TFormMain.Image24Click(Sender: TObject);
begin
   map.Select(2,3);
end;

procedure TFormMain.Image25Click(Sender: TObject);
begin
   map.Select(2,4);
end;

procedure TFormMain.Image26Click(Sender: TObject);
begin
   map.Select(2,5);
end;

procedure TFormMain.Image27Click(Sender: TObject);
begin
   map.Select(2,6);
end;

procedure TFormMain.Image28Click(Sender: TObject);
begin
   map.Select(2,7);
end;

procedure TFormMain.Image29Click(Sender: TObject);
begin
   map.Select(2,8);
end;

procedure TFormMain.Image30Click(Sender: TObject);
begin
   map.Select(2,9);
end;

procedure TFormMain.Image31Click(Sender: TObject);
begin
   map.Select(3,0);
end;

procedure TFormMain.Image32Click(Sender: TObject);
begin
   map.Select(3,1);
end;

procedure TFormMain.Image33Click(Sender: TObject);
begin
   map.Select(3,2);
end;

procedure TFormMain.Image34Click(Sender: TObject);
begin
   map.Select(3,3);
end;

procedure TFormMain.Image35Click(Sender: TObject);
begin
   map.Select(3,4);
end;

procedure TFormMain.Image36Click(Sender: TObject);
begin
   map.Select(3,5);
end;

procedure TFormMain.Image37Click(Sender: TObject);
begin
   map.Select(3,6);
end;

procedure TFormMain.Image38Click(Sender: TObject);
begin
   map.Select(3,7);
end;

procedure TFormMain.Image39Click(Sender: TObject);
begin
   map.Select(3,8);
end;

procedure TFormMain.Image40Click(Sender: TObject);
begin
   map.Select(3,9);
end;

procedure TFormMain.Image41Click(Sender: TObject);
begin
   map.Select(4,0);
end;

procedure TFormMain.Image42Click(Sender: TObject);
begin
   map.Select(4,1);
end;

procedure TFormMain.Image43Click(Sender: TObject);
begin
   map.Select(4,2);
end;

procedure TFormMain.Image44Click(Sender: TObject);
begin
   map.Select(4,3);
end;

procedure TFormMain.Image45Click(Sender: TObject);
begin
   map.Select(4,4);
end;

procedure TFormMain.Image46Click(Sender: TObject);
begin
   map.Select(4,5);
end;

procedure TFormMain.Image47Click(Sender: TObject);
begin
   map.Select(4,6);
end;

procedure TFormMain.Image48Click(Sender: TObject);
begin
   map.Select(4,7);
end;

procedure TFormMain.Image49Click(Sender: TObject);
begin
   map.Select(4,8);
end;

procedure TFormMain.Image50Click(Sender: TObject);
begin
   map.Select(4,9);
end;



procedure TFormMain.ButInvClick(Sender: TObject);
begin
   map.Build(-1);
end;

procedure TFormMain.ButNoneClick(Sender: TObject);
begin
   map.Build(0);
end;

procedure TFormMain.ButCampClick(Sender: TObject);
begin
 map.Build(1);
end;

procedure TFormMain.ButFortressClick(Sender: TObject);
begin
 map.Build(2);
end;

procedure TFormMain.ButCastleClick(Sender: TObject);
begin
 map.Build(3);
end;

procedure TFormMain.ButVillageClick(Sender: TObject);
begin
 map.Build(4);
end;

procedure TFormMain.ButCitadelClick(Sender: TObject);
begin
 map.Build(5);
end;


procedure TFormMain.BitBtn1Click(Sender: TObject);
begin
   map.AreaOwner(0);
end;

procedure TFormMain.BitBtn2Click(Sender: TObject);
begin
    map.AreaOwner(1);
end;

procedure TFormMain.BitBtn3Click(Sender: TObject);
begin
   map.AreaOwner(2);
end;

procedure TFormMain.UpDown1Click(Sender: TObject; Button: TUDBtnType);
begin
   if Button = btNext then map.Incrementa(0, 1)
   else map.Incrementa(0,-1);
end;

procedure TFormMain.UpDown2Click(Sender: TObject; Button: TUDBtnType);
begin
   if Button = btNext then map.Incrementa(1, 1)
   else map.Incrementa(1,-1);
end;

procedure TFormMain.UpDown3Click(Sender: TObject; Button: TUDBtnType);
begin
   if Button = btNext then map.Incrementa(2, 1)
   else map.Incrementa(2,-1);
end;

procedure TFormMain.UpDown4Click(Sender: TObject; Button: TUDBtnType);
begin
   if Button = btNext then map.Incrementa(3, 1)
   else map.Incrementa(3,-1);
end;

procedure TFormMain.UpDown5Click(Sender: TObject; Button: TUDBtnType);
begin
   if Button = btNext then map.Incrementa(4, 1)
   else map.Incrementa(4,-1);
end;

procedure TFormMain.SaveMap();
var fichero: TextFile;
    i,j:integer;

begin
      AssignFile(fichero, SaveDialog1.Filename);
      Rewrite(fichero);
      WriteLn(fichero, map.inix);
      WriteLn(fichero, map.iniy);
      WriteLn(fichero, map.inigold);
      WriteLn(fichero, map.daytime);
      WriteLn(fichero, map.dificulty);
      for i:= 0 to 4 do
         for j:=0 to 9 do begin
            WriteLn(fichero, map.areas[i,j].construccion);
            WriteLn(fichero, map.areas[i,j].unidentro);
            WriteLn(fichero, map.areas[i,j].unifuera);
            WriteLn(fichero, map.areas[i,j].unienemigo);
            WriteLn(fichero, map.areas[i,j].people);
            WriteLn(fichero, map.areas[i,j].raceowner);

            if map.areas[i,j].unienemigo > 0 then WriteLn(fichero, map.areas[i,j].racestriker)
            else WriteLn(fichero, 0);
            WriteLn(fichero, map.areas[i,j].integrity);
            WriteLn(fichero, map.areas[i,j].explored);
            WriteLn(fichero, map.areas[i,j].evervisible);
         end;
      CloseFile(fichero);
end;

procedure TFormMain.SaveAs1Click(Sender: TObject);
begin
   if (SaveDialog1.Execute) then begin
      SaveMap();
   end;
end;

procedure TFormMain.Save1Click(Sender: TObject);
begin
   if SaveDialog1.Filename <> 'name' then
      SaveMap()
   else SaveAs1Click(Sender);
end;

procedure TFormMain.Open1Click(Sender: TObject);
begin
   if (OpenDialog1.Execute) then begin
      LoadMap();
      refreshClick(self);
   end;
end;


procedure TFormMain.LoadMap();
var fichero: TextFile;
    i,j:integer;

begin
      AssignFile(fichero, OpenDialog1.Filename);
      Reset(fichero);
      ReadLn(fichero, map.inix);
      ReadLn(fichero, map.iniy);
      ReadLn(fichero, map.inigold);
      ReadLn(fichero, map.daytime);
      ReadLn(fichero, map.dificulty);
      for i:= 0 to 4 do
         for j:=0 to 9 do begin
            ReadLn(fichero, map.areas[i,j].construccion);
            ReadLn(fichero, map.areas[i,j].unidentro);
            ReadLn(fichero, map.areas[i,j].unifuera);
            ReadLn(fichero, map.areas[i,j].unienemigo);
            ReadLn(fichero, map.areas[i,j].people);
            ReadLn(fichero, map.areas[i,j].raceowner);
            ReadLn(fichero, map.areas[i,j].racestriker);
            ReadLn(fichero, map.areas[i,j].integrity);
            ReadLn(fichero, map.areas[i,j].explored);
            ReadLn(fichero, map.areas[i,j].evervisible);
         end;
      CloseFile(fichero);

      // Init forms
      ValueListEditor2.Values[ValueListEditor2.Keys[1]] := IntToStr(map.inigold);
      ValueListEditor2.Values[ValueListEditor2.Keys[2]] := IntToStr(map.iniy);
      ValueListEditor2.Values[ValueListEditor2.Keys[3]] := IntToStr(map.inix);
      map.selx := map.inix;
      map.sely := map.iniy;
end;


procedure TFormMain.SpeedButton1Click(Sender: TObject);
begin
        if (FormGold.ShowModal = mrOK) then begin

              map.inigold := StrToInt(FormGold.MaskEdit1.EditText);
              ValueListEditor2.Values[ValueListEditor2.Keys[1]] := FormGold.MaskEdit1.EditText;

        end;
end;

procedure TFormMain.SpeedButton4Click(Sender: TObject);
begin
        ValueListEditor2.Values[ValueListEditor2.Keys[2]] := IntToStr(map.sely);
        ValueListEditor2.Values[ValueListEditor2.Keys[3]] := IntToStr(map.selx);
        map.inix := map.selx;
        map.iniy := map.sely;
end;

procedure TFormMain.SpeedButton3Click(Sender: TObject);
begin
        map.dificulty := map.dificulty + 1;
        if map.dificulty >= 5 then map.dificulty := 0;

end;

procedure TFormMain.BitBtn5Click(Sender: TObject);
begin
        map.areas[map.sely,map.selx].evervisible := 1-map.areas[map.sely,map.selx].evervisible;
        map.Select(map.sely, map.selx);

end;

procedure TFormMain.BitBtn4Click(Sender: TObject);
begin
        map.areas[map.sely,map.selx].explored := 1-map.areas[map.sely,map.selx].explored;
        map.Select(map.sely, map.selx);

end;

end.
