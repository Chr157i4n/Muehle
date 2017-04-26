/***************************************************************
 * Name:      muehleMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2017-04-10
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef MUEHLEMAIN_H
#define MUEHLEMAIN_H


//(*Headers(muehleFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

class muehleFrame: public wxFrame
{
    public:

        muehleFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~muehleFrame();

    private:

        //(*Handlers(muehleFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        //*)

        //(*Identifiers(muehleFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(muehleFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // MUEHLEMAIN_H
