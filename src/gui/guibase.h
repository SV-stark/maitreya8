/***********************************************************************
 This is the source code of Maitreya, open source platform for Vedic
 and western astrology.

 File       src/gui/guibase.h
 Release    8.0
 Author     Martin Pettau
 Copyright  2003-2017 by the author

 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License,
 * or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
************************************************************************/

#ifndef _GUIBASE_H_
#define _GUIBASE_H_

#include <wx/dialog.h>
#include <wx/event.h>
#include <wx/string.h>

#include "maitreya.h"

class wxButton;
class wxCheckBox;
class wxWindow;

#define DEFAULT_DIALOG_STYLE                                                   \
  wxRESIZE_BORDER | wxSYSTEM_MENU | wxMAXIMIZE_BOX | wxCLOSE_BOX | wxCAPTION

// BEGIN_DECLARE_EVENT_TYPES()
extern const wxEventType TOOLPANEL_CHANGED;
extern const wxEventType TOOLPANEL_CREATEDOC;
extern const wxEventType SHOW_EPHEM_FILE_WARNING;
extern const wxEventType CREATE_ENTRY_CHART;
// END_DECLARE_EVENT_TYPES()

wxString createImageHash(wxImage *);

int doMessageBox(wxWindow *parent, const wxString message,
                 const long style = wxOK | wxICON_INFORMATION);

void showHelpPopup(wxWindow *parent, wxString header, wxString contents);

/*************************************************/ /**
                                                     *
                                                     *
                                                     *
                                                     ******************************************************/
class DoNotShowAgainDialog : public wxDialog {
public:
  DoNotShowAgainDialog(wxWindow *parent, wxString message, bool *item,
                       const int style = wxOK);

private:
  void OnButton(wxCommandEvent &);

  wxCheckBox *check_not_ask_again;
  bool *cfgitem;
};

#endif
