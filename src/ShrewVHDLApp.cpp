/***************************************************************
 * Name:      ShrewVHDLApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Firas Hares (firas.hrs@gmail.com)
 * Created:   2022-12-11
 * Copyright: Firas Hares (https://github.com/firashrs/)
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "ShrewVHDLApp.h"
#include "ShrewVHDLMain.h"
#include <wx/image.h>

IMPLEMENT_APP(ShrewVHDLApp);

bool ShrewVHDLApp::OnInit()
{
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ShrewVHDLFrame* frame = new ShrewVHDLFrame(0L, _("Shrew VHDL"));
        frame->SetIcon(wxICON(aaaa)); // To Set App Icon
        frame->Show();
    	SetTopWindow(frame);
    }
//    ShrewVHDLFrame* frame = new ShrewVHDLFrame(0L, _("Shrew VHDL"));
//    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
//    frame->Show();

    return wxsOK;
}
