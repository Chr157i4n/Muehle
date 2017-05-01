/***************************************************************
 * Name:      muehleMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2017-04-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "muehleMain.h"
#include <wx/msgdlg.h>
#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include "spielfeld.h"
#include "spieler.h"


    spielfeld spielfeld[7][7];
    int spielerAnDerReihe=1,spielerNichtAnDerReihe=2;
    spieler spieler[2];
    wxBitmap bildSpielerWeiss;
    wxBitmap bildSpielerSchwarz;
    wxBitmap hintergrund;
    bool aktuellerSpielerHatMuehle = false;
    int phase=1;
    bool figurausgewaehlt=false;
    wxPoint ausgewaehlteFigur;
    int umrandungX=-1,umrandungY=-1;
    wxString meldung;

//(*InternalHeaders(muehleFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}




//(*IdInit(muehleFrame)
const long muehleFrame::idMenuQuit = wxNewId();
const long muehleFrame::idMenuAbout = wxNewId();
const long muehleFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(muehleFrame,wxFrame)
    //(*EventTable(muehleFrame)
    //*)
END_EVENT_TABLE()

muehleFrame::muehleFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(muehleFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(600,640));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&muehleFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&muehleFrame::OnAbout);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&muehleFrame::OnPaint);
    Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&muehleFrame::OnLeftDown);
    //*)

    spielfeld[0][1].wert=-1;
    spielfeld[0][2].wert=-1;
    spielfeld[0][4].wert=-1;
    spielfeld[0][5].wert=-1;

    spielfeld[1][0].wert=-1;
    spielfeld[1][2].wert=-1;
    spielfeld[1][4].wert=-1;
    spielfeld[1][6].wert=-1;

    spielfeld[2][0].wert=-1;
    spielfeld[2][1].wert=-1;
    spielfeld[2][5].wert=-1;
    spielfeld[2][6].wert=-1;

    spielfeld[3][3].wert=-2;

    spielfeld[4][0].wert=-1;
    spielfeld[4][1].wert=-1;
    spielfeld[4][5].wert=-1;
    spielfeld[4][6].wert=-1;

    spielfeld[5][0].wert=-1;
    spielfeld[5][2].wert=-1;
    spielfeld[5][4].wert=-1;
    spielfeld[5][6].wert=-1;

    spielfeld[6][1].wert=-1;
    spielfeld[6][2].wert=-1;
    spielfeld[6][4].wert=-1;
    spielfeld[6][5].wert=-1;



    bildSpielerWeiss.LoadFile("weiﬂ.png", wxBITMAP_TYPE_PNG);
    bildSpielerSchwarz.LoadFile("schwarz.png", wxBITMAP_TYPE_PNG);
    hintergrund.LoadFile("spielfeld.png", wxBITMAP_TYPE_PNG);


   // meldunganzeigen(meldung);
    meldung="Spieler ";
    meldung << spielerAnDerReihe;
    meldung = meldung + " darf einen Stein setzen";
}



muehleFrame::~muehleFrame()
{
    //(*Destroy(muehleFrame)
    //*)
}

void muehleFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void muehleFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void muehleFrame::OnPaint(wxPaintEvent& event)
{
    wxBufferedPaintDC dc(this);

    dc.DrawBitmap(hintergrund, 0, 0, false);

    //wxBitmap bitmap1("weiﬂ.jpg", wxBITMAP_TYPE_JPEG);
    //dc.DrawBitmap(bitmap1, stein.x, stein.y, false);

    for (int i=0;i<7;i++)
    {
        for (int j=0;j<7;j++)
        {
            if (spielfeld[i][j].wert==1)
                {

                    dc.DrawBitmap(bildSpielerWeiss, i*90, j*90, false);
                }

            if (spielfeld[i][j].wert==2)
                {

                    dc.DrawBitmap(bildSpielerSchwarz, i*90, j*90, false);
                }
        }
    }

    if (umrandungX!=-1)
    {
         dc.SetBrush(*wxTRANSPARENT_BRUSH);
      //Set Pen-> Color:255,50,50 , Width:Default Value
        dc.SetPen(wxPen(wxColour(0,50,50)));
        dc.DrawRectangle(umrandungX*90,umrandungY*90,75,75);
    }

    StatusBar1->SetStatusText(meldung);



}




void aufMuehlenPruefen(int x,int y)
{
    spieler[spielerAnDerReihe-1].anzahlmuehlen=0;



    ///waagerecht
    for (int i=0; i<7; i++)
    {


        if (spielfeld[i][y].wert==spielerAnDerReihe)
        {


            for (int j=i+1; j<7; j++)
            {
                if (spielfeld[j][y].wert==-2) {break;}
                if (spielfeld[j][y].wert==spielerAnDerReihe)
                {

                    if (spielfeld[j+(j-i)][y].wert==spielerAnDerReihe && j+(j-i)<7 && (j-i==0 || spielfeld[j+1][y].wert!=-2))
                    {
                        aktuellerSpielerHatMuehle=true;
                        meldung="Spieler ";
                        meldung << spielerAnDerReihe;
                        meldung = meldung + " hat eine M¸hle und darf einen Stein vom Gegner wegnehmen";



                    }
                }
            }
        }
    }



    ///senkrecht
    for (int i=0; i<7; i++)
    {


        if (spielfeld[x][i].wert==spielerAnDerReihe)
        {


            for (int j=i+1; j<7; j++)
            {
                if (spielfeld[x][j].wert==-2) {break;}
                if (spielfeld[x][j].wert==spielerAnDerReihe)
                {
                    if (spielfeld[x][j+(j-i)].wert==spielerAnDerReihe && j+(j-i)<7 && (j-i==0 || spielfeld[x][j+1].wert!=-2))
                    {
                        aktuellerSpielerHatMuehle=true;
                        meldung="Spieler ";
                        meldung << spielerAnDerReihe;
                        meldung = meldung + " hat eine M¸hle und darf einen Stein vom Gegner wegnehmen";


                    }
                }
            }
        }
    }


}


void steinentfernen(int x,int y)
{
    if (spielfeld[x][y].wert==spielerNichtAnDerReihe)
    {

        spielfeld[x][y].wert=0;
        aktuellerSpielerHatMuehle=false;
        spieler[spielerAnDerReihe-1].anzahlsteineweggenohmen++;
        spieler[spielerNichtAnDerReihe-1].anzahltatsaechlicheSteine--;

        if (spielerAnDerReihe==1)
        {
            spielerAnDerReihe =2;
            spielerNichtAnDerReihe =1;
        }
        else
        {
            spielerAnDerReihe =1;
            spielerNichtAnDerReihe =2;
        }

        meldung="Spieler ";
        meldung << spielerAnDerReihe;
        meldung = meldung + " darf einen Stein setzen";


        if (spieler[spielerAnDerReihe-1].anzahltatsaechlicheSteine==3 && phase!=1)
        {
            phase=3;
            spieler[spielerAnDerReihe-1].darfspringen=true;
             meldung= "Spieler ";
             meldung << spielerAnDerReihe;
             meldung = meldung + " darf nun springen";
        }

         if (spieler[spielerAnDerReihe-1].anzahltatsaechlicheSteine<3 && phase!=1)
        {
            meldung="Spieler ";
            meldung << spielerNichtAnDerReihe;
            meldung = meldung + " hat gewonnen";
            wxMessageBox(meldung);
        }



    }
}




void steinsetzen(int x,int y)
{

     if (spieler[1].anzahlgesetzteSteine<9)
     {
         spielfeld[x][y].wert=spielerAnDerReihe;
         spieler[spielerAnDerReihe-1].anzahlgesetzteSteine++;
         spieler[spielerAnDerReihe-1].anzahltatsaechlicheSteine++;
     }
     if (spieler[1].anzahlgesetzteSteine==9)
        {
            phase=2;
            wxMessageBox("Phase 2");}

}




void muehleFrame::OnLeftDown(wxMouseEvent& event)
{

if (spieler[spielerAnDerReihe-1].anzahltatsaechlicheSteine>=3 || spieler[spielerAnDerReihe-1].anzahlgesetzteSteine<4)
{
   const wxPoint pt = wxGetMousePosition();
    int mausX = pt.x - this->GetScreenPosition().x;
    int mausY = pt.y - this->GetScreenPosition().y;
    int spielfeldX=mausX/90;
    int spielfeldY=mausY/90;


if (aktuellerSpielerHatMuehle)
    {
        steinentfernen(spielfeldX,spielfeldY);
        Refresh();
    }




else
        {


    if (phase==1)
    {


            //if ((spielfeld[mausX/90][mausY/90].wert!=-1) && (spielfeld[mausX/90][mausY/90].wert!=1) && (spielfeld[mausX/90][mausY/90].wert!=2))
            if (spielfeld[spielfeldX][spielfeldY].wert==0)
            {

                steinsetzen(spielfeldX,spielfeldY);


                    meldung="Spieler ";
                    meldung << spielerNichtAnDerReihe;
                    meldung = meldung + " darf einen Stein setzen";

                aufMuehlenPruefen(spielfeldX,spielfeldY);

                if ((spielfeld[spielfeldX][spielfeldY].wert==spielerAnDerReihe && !aktuellerSpielerHatMuehle))
                {
                    if (spielerAnDerReihe==1)
                    {
                        spielerAnDerReihe =2;
                        spielerNichtAnDerReihe =1;

                    }
                    else
                    {
                        spielerAnDerReihe =1;
                        spielerNichtAnDerReihe =2;
                    }



                }
                Refresh();
            }

        }






    else if (phase==2 && spieler[spielerAnDerReihe].darfspringen!=true)
    {


                if (spielfeld[spielfeldX][spielfeldY].wert==spielerAnDerReihe)
                    {
                     ausgewaehlteFigur.x=spielfeldX;
                     ausgewaehlteFigur.y=spielfeldY;
                     figurausgewaehlt=true;
                    umrandungX=spielfeldX;
                    umrandungY=spielfeldY;
                    Refresh();
                    }


                    else if (spielfeld[spielfeldX][spielfeldY].wert==0 && figurausgewaehlt)
                    {

                        ///Darf nur auf benachbartes Feld
                        int darfsetzen=0;
                    if (ausgewaehlteFigur.x==spielfeldX)
                        {
                            for (int i=0;i<=7;i++)
                            {
                                if ((i==spielfeldY || i==ausgewaehlteFigur.y) && (darfsetzen==1 ||darfsetzen==2)) break;
                                if ((spielfeld[spielfeldX][i].wert==spielerNichtAnDerReihe || spielfeld[spielfeldX][i].wert==-2 || spielfeld[spielfeldX][i].wert==0) && darfsetzen==1) darfsetzen=2;
                                if ((i==spielfeldY || i==ausgewaehlteFigur.y) && darfsetzen==0) darfsetzen=1;

                            }

                        }
                    else if (ausgewaehlteFigur.y==spielfeldY)
                        {
                            for (int i=0;i<=7;i++)
                            {
                            if ((i==spielfeldX || i==ausgewaehlteFigur.x) && (darfsetzen==1 ||darfsetzen==2)) break;
                            if ((spielfeld[i][spielfeldY].wert==spielerNichtAnDerReihe || spielfeld[i][spielfeldY].wert==-2 || spielfeld[i][spielfeldY].wert==0) && darfsetzen==1) darfsetzen=2;
                            if ((i==spielfeldX || i==ausgewaehlteFigur.x) && darfsetzen==0) darfsetzen=1;
                            }
                        }
                        ///Darf nur auf benachbartes Feld



                    if (darfsetzen==1)
                    {
                     spielfeld[spielfeldX][spielfeldY].wert=spielerAnDerReihe;
                     spielfeld[ausgewaehlteFigur.x][ausgewaehlteFigur.y].wert=0;
                     umrandungX=-1;

                     Refresh();
                     figurausgewaehlt=false;

                        meldung="Spieler ";
                        meldung << spielerNichtAnDerReihe;
                        if (spieler[spielerNichtAnDerReihe-1].darfspringen)
                        {meldung = meldung + " darf nun mit einem Stein springen";}
                        else {meldung = meldung + " darf nun einen Stein versetzen";}

                        aufMuehlenPruefen(spielfeldX,spielfeldY);

                        if (spielerAnDerReihe==1 && !aktuellerSpielerHatMuehle)
                        {
                        spielerAnDerReihe =2;
                        spielerNichtAnDerReihe =1;
                        }
                        else if (!aktuellerSpielerHatMuehle)
                        {
                        spielerAnDerReihe =1;
                        spielerNichtAnDerReihe =2;
                        }
                    }
                    }


    }





    else if (spieler[spielerAnDerReihe].darfspringen==true)
    {



                if (!figurausgewaehlt && spielfeld[spielfeldX][spielfeldY].wert==spielerAnDerReihe)
                    {
                     ausgewaehlteFigur.x=spielfeldX;
                     ausgewaehlteFigur.y=spielfeldY;
                     figurausgewaehlt=true;
                    umrandungX=spielfeldX;
                    umrandungY=spielfeldY;
                    Refresh();


                    }
                    else if (spielfeld[spielfeldX][spielfeldY].wert==0 && figurausgewaehlt)
                    {
                     spielfeld[spielfeldX][spielfeldY].wert=spielerAnDerReihe;
                     spielfeld[ausgewaehlteFigur.x][ausgewaehlteFigur.y].wert=0;
                     umrandungX=-1;
                     Refresh();
                     figurausgewaehlt=false;

                        meldung="Spieler ";
                        meldung << spielerNichtAnDerReihe;
                        if (spieler[spielerNichtAnDerReihe-1].darfspringen)
                        {meldung = meldung + " darf nun mit einem Stein springen";}
                        else {meldung = meldung + " darf nun einen Stein versetzen";}

                        aufMuehlenPruefen(spielfeldX,spielfeldY);

                        if (spielerAnDerReihe==1 && !aktuellerSpielerHatMuehle)
                        {
                        spielerAnDerReihe =2;
                        spielerNichtAnDerReihe =1;
                        }
                        else if (!aktuellerSpielerHatMuehle)
                        {
                        spielerAnDerReihe =1;
                        spielerNichtAnDerReihe =2;
                        }
                    }


    }

 }

}


}
