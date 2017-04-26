/***************************************************************
 * Name:      muehleApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2017-04-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "muehleApp.h"

//(*AppHeaders
#include "muehleMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(muehleApp);

bool muehleApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	muehleFrame* Frame = new muehleFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
