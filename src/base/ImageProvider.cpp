/***********************************************************************
 This is the source code of Maitreya, open source platform for Vedic
 and western astrology.

 File       src/base/ImageProvider.cpp
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

#include "ImageProvider.h"

#include "Conf.h"
#include "FileConfig.h"
#include "maitreya.h"

#include <map>
#include <utility>
#include <wx/file.h>
#include <wx/filename.h>
#include <wx/image.h>
#include <wx/imaglist.h>
#include <wx/log.h>

#include "chart_images.h"
#include "xpm_images.h"

#define DEFAULT_BITMAP_SIZE 32
#define SMALL_IMAGE_SIZE 16

extern Config *config;

IMPLEMENT_SINGLETON(ImageProvider)

/*************************************************/ /**
                                                     *
                                                     *
                                                     *
                                                     ******************************************************/
class BitmapCache {
  DECLARE_SINGLETON(BitmapCache)

public:
  wxBitmap *findBitmapRef(const wxString &s, const int rotateHue = 0) {
    // printf( "BitmapCache::GET 1 size %d name %s rh %d\n", (int)mm.size(),
    // str2char( s ), rotateHue );
    const std::pair<wxString, int> k(s, rotateHue);

    std::map<std::pair<wxString, int>, wxBitmap *>::iterator iter = mm.find(k);
    if (iter != mm.end()) {
      // printf( "found\n" );
      return mm[k];
    } else {
      // printf( "not found\n" );
      return (wxBitmap *)NULL;
    }
  }

  void putBitmapRef(const wxString &s, const int rotateHue, wxBitmap *b) {
    // printf( "BitmapCache::PUT 1 size %d name %s rh %d\n", (int)mm.size(),
    // str2char( s ), rotateHue );
    const std::pair<wxString, int> k(s, rotateHue);
    mm[k] = b;
    // printf( "BitmapCache::PUT 2 size %d\n", (int)mm.size() );
  }

private:
  std::map<std::pair<wxString, int>, wxBitmap *> mm;
};

IMPLEMENT_SINGLETON(BitmapCache)

/*****************************************************
**
**   ImageProvider   ---   Constructor
**
******************************************************/
ImageProvider::ImageProvider() {
  errorBmp = getBitmap(BM_ERROR);
  dasaImageList = (wxImageList *)NULL;
}

/*****************************************************
**
**   ImageProvider   ---   Destructor
**
******************************************************/
ImageProvider::~ImageProvider() {
  if (dasaImageList)
    delete dasaImageList;
}

/*****************************************************
**
**   ImageProvider   ---   getDefaultBitmapSize
**
******************************************************/
int ImageProvider::getDefaultBitmapSize() const { return DEFAULT_BITMAP_SIZE; }

/*****************************************************
**
**   ImageProvider   ---   getFileBasedBitmap
**
******************************************************/
wxBitmap ImageProvider::getFileBasedBitmap(const wxString &s,
                                           const int rotateHue,
                                           const bool storeInCache) {
  wxBitmap *b = getFileBasedBitmapRef(s, rotateHue, storeInCache);
  if (b) {
    // workaround for wxgtk3
    wxImage img = b->ConvertToImage();
    return wxBitmap(img);
    // return wxBitmap( *b );
  } else
    return errorBmp;
}

/*****************************************************
**
**   ImageProvider   ---   getFileBasedBitmapConservative
**
******************************************************/
wxBitmap ImageProvider::getFileBasedBitmapConservative(const wxString &s,
                                                       const int rotateHue) {
  // printf( "ImageProvider::getFileBasedBitmapConservative NEW BMP %s rotateHue
  // %d\n", str2char( s ), rotateHue );
  wxString filename = FileConfig::get()->getPicDir() + s;
  if (!wxFile::Exists(filename)) {
    wxLogError(wxString::Format(wxT("bitmap \"%s\" not found in directory %s"),
                                s.c_str(),
                                FileConfig::get()->getPicDir().c_str()));
    return errorBmp;
  } else if (!wxFileName::IsFileReadable(filename)) {
    wxLogError(
        wxString::Format(wxT("bitmap \"%s\" not readable in directory %s"),
                         s.c_str(), FileConfig::get()->getPicDir().c_str()));
    return errorBmp;
  } else // file exists and is readable
  {
    if (rotateHue) {
      wxBitmap bmp(filename, wxBITMAP_TYPE_ANY);
      // printf( "ImageProvider::getFileBasedBitmapConservative BMP %s rotateHue
      // %d NEW IS OK %d\n", str2char( s ), rotateHue, bmp.IsOk());
      wxImage image = bmp.ConvertToImage();
      image.RotateHue(rotateHue / 360.0);
      return wxBitmap(image);
    } else {
      return wxBitmap(filename, wxBITMAP_TYPE_ANY);
    }
  }
}

/*****************************************************
**
**   ImageProvider   ---   getFileBasedBitmapRef
**
******************************************************/
wxBitmap *ImageProvider::getFileBasedBitmapRef(const wxString &s,
                                               const int rotateHue,
                                               const bool storeInCache) {
  // printf( "ImageProvider::getFileBasedBitmapRef image %s rotate %d store
  // %d\n", str2char( s ), rotateHue, storeInCache );
  BitmapCache *cache = BitmapCache::get();
  wxBitmap *b = cache->findBitmapRef(s, rotateHue);

  if (!b) {
    // printf( "ImageProvider::getFileBasedBitmapRef NEW BMP %s rotateHue %d\n",
    // str2char( s ), rotateHue );
    wxString filename = FileConfig::get()->getPicDir() + s;
    if (!wxFile::Exists(filename)) {
      wxLogError(
          wxString::Format(wxT("bitmap \"%s\" not found in directory %s"),
                           s.c_str(), FileConfig::get()->getPicDir().c_str()));
      b = &errorBmp;
    } else if (!wxFileName::IsFileReadable(filename)) {
      wxLogError(
          wxString::Format(wxT("bitmap \"%s\" not readable in directory %s"),
                           s.c_str(), FileConfig::get()->getPicDir().c_str()));
      b = &errorBmp;
    } else // file exists and is readable
    {
      if (rotateHue) {
        wxBitmap bmp(filename, wxBITMAP_TYPE_ANY);
        // printf( "ImageProvider::getFileBasedBitmapRef BMP %s rotateHue %d NEW
        // IS OK %d\n", str2char( s ), rotateHue, bmp.IsOk());
        wxImage image = bmp.ConvertToImage();
        image.RotateHue(rotateHue / 360.0);
        b = new wxBitmap(image);
      } else {
        b = new wxBitmap(filename, wxBITMAP_TYPE_ANY);
        // b = new wxBitmap( filename, wxBITMAP_TYPE_PNG );
        // printf( "ImageProvider::getFileBasedBitmapRef ROTATED BMP rotateHue
        // %d NEW IS OK %d\n", rotateHue, b->IsOk());
      }
    }

    assert(b);
    if (storeInCache) {
      // printf( "PUT TO CACHE name %s rh %d\n", str2char( s ), rotateHue );
      cache->putBitmapRef(s, rotateHue, b);
    }
  } else {
    // printf( "ImageProvider::getFileBasedBitmapRef FOUND BMP %s rotateHue
    // %d\n", str2char( s ), rotateHue ); if ( b->IsOk()) printf( " OKi (1)\n"
    // );
  }
  return b;
}

/*****************************************************
**
**   ImageProvider   ---   getDasaImageList
**
******************************************************/
wxImageList *ImageProvider::getDasaImageList() {
  if (!dasaImageList) {
    const int max_image = 15;
    const BitmapId imageIdList[max_image] = {
        BM_DASA,       BM_FOLDER,     BM_MAHADASA,   BM_DASATREE1,
        BM_DASATREE2,  BM_DASATREE3,  BM_DASATREE4,  BM_DASATREE5,
        BM_FOLDERE,    BM_MAHADASAE,  BM_DASATREE1E, BM_DASATREE2E,
        BM_DASATREE3E, BM_DASATREE4E, BM_DASATREE5E};

    dasaImageList =
        new wxImageList(DEFAULT_BITMAP_SIZE, DEFAULT_BITMAP_SIZE, true);

    for (int i = 0; i < max_image; i++) {
      dasaImageList->Add(getBitmap(imageIdList[i]));
    }
  }
  return dasaImageList;
}

/*****************************************************
**
**   ImageProvider   ---   getViewImageListIndex4BitmapId
**
******************************************************/
int ImageProvider::getViewImageListIndex4BitmapId(const BitmapId &bid) const {
  return bid - (int)BM_ECLIPSE;
}

/*****************************************************
**
**   ImageProvider   ---   createViewImageList
**
******************************************************/
wxImageList *ImageProvider::createViewImageList(const bool small) {
  const int size = small ? SMALL_IMAGE_SIZE : getDefaultBitmapSize();
  wxImageList *imageList = new wxImageList(size, size);

  for (int id = (int)BM_ECLIPSE; id <= (int)BM_CHARTB; id++) {
    if (small)
      imageList->Add(getScaledBitmap((BitmapId)id, size));
    else
      imageList->Add(getBitmap((BitmapId)id));
  }
  return imageList;
}

/*****************************************************
**
**   ImageProvider   ---   bitmapId2CharArray
**
******************************************************/
char **ImageProvider::bitmapId2CharArray(const BitmapId &index) {
  if (!(IS_VALID_BITMAP_ID(index))) {
    wxLogError(
        wxT("invalid bitmap id %d, allowed values are between %d and %d"),
        (int)index, (int)BM_FIRST, (int)BM_LAST);
    return (char **)error_xpm;
  }

  static const char **xpms[] = {
      error_xpm, maitreya_xpm,

      // global commands
      close_xpm, new_xpm, open_xpm, quit_xpm, save_xpm, saveas_xpm,

      // view without document
      eclipse_xpm, ephem_xpm, hora_xpm, yogaeditor_xpm,

      // view with document
      ashtakavarga_xpm, dasa_xpm, graphicaldasa_xpm, mview_xpm, partner_xpm,
      sbc_xpm, shadbala_xpm, solar_xpm, sview_xpm, text_xpm, transit_xpm,
      uranian_xpm, varga_xpm, wchart_xpm, yoga_xpm,

      // vedic charts
      chart1_xpm, chart9_xpm, chart2_xpm, chart3_xpm, chart4_xpm, chart6_xpm,
      chart7_xpm, chart8_xpm, chart10_xpm, chart12_xpm, chart16_xpm,
      chart20_xpm, chart24_xpm, chart27_xpm, chart30_xpm, chart40_xpm,
      chart45_xpm, chart60_xpm, chart108_xpm, chart144_xpm, chartb_xpm,

      // misc modal dialogs
      about_xpm, atlas_xpm, config_xpm,

      // commands on document dependend views
      edit_xpm, print_xpm, quickprint_xpm,

      // dasa tree view
      folder_xpm, foldere_xpm, dasatree1_xpm, dasatree1e_xpm, dasatree2_xpm,
      dasatree2e_xpm, dasatree3_xpm, dasatree3e_xpm, dasatree4_xpm,
      dasatree4e_xpm, dasatree5_xpm, dasatree5e_xpm, mahadasa_xpm,
      mahadasae_xpm,

      // general toolbar command
      arrow_down_xpm, arrow_left_xpm, arrow_right_xpm, arrow_up_xpm, copy_xpm,
      export_csv_xpm, export_html_xpm, export_image_xpm, export_pdf_xpm,
      export_text_xpm, filter_xpm, goto_xpm, help_xpm, now_xpm, split_xpm,
      tip_xpm, zoom_in_xpm, zoom_original_xpm, zoom_out_xpm,

      separator_xpm};

  return (char **)xpms[index];
}

/*****************************************************
**
**   ImageProvider   ---   getIcon
**
******************************************************/
wxIcon ImageProvider::getIcon(const BitmapId &index) {
  char **bmp = bitmapId2CharArray(index);
  return wxIcon(bmp);
}

/*****************************************************
**
**   ImageProvider   ---   getScaledBitmap
**
******************************************************/
wxBitmap ImageProvider::getScaledBitmap(const BitmapId &index,
                                        const int &size) {
  return wxBitmap(getBitmap(index).ConvertToImage().Scale(size, size));
}

/*****************************************************
**
**   ImageProvider   ---   getScaledBitmap
**
******************************************************/
wxBitmap ImageProvider::getScaledBitmap(const wxString s, const int &size) {
  return wxBitmap(getFileBasedBitmapRef(s)->ConvertToImage().Scale(size, size));
}

/*****************************************************
**
**   ImageProvider   ---   getMenuBitmap
**
******************************************************/
wxBitmap ImageProvider::getMenuBitmap(const BitmapId &index) {
  return getScaledBitmap(index, SMALL_IMAGE_SIZE);
}

/*****************************************************
**
**   ImageProvider   ---   getImage
**
******************************************************/
wxImage ImageProvider::getImage(const wxString &s) {
  return getFileBasedBitmap(s).ConvertToImage();
}

/*****************************************************
**
**   ImageProvider   ---   getBitmap
**
******************************************************/

/*****************************************************
**
**   ImageProvider   ---   bitmapId2Name
**   helper to get filename for ID (modernization)
**
******************************************************/
wxString ImageProvider::bitmapId2Name(const BitmapId &index) {
  switch (index) {
  case BM_MAITREYA:
    return "maitreya.png";
  case BM_CLOSE:
    return "close.png";
  case BM_NEW:
    return "new.png";
  case BM_OPEN:
    return "open.png";
  case BM_QUIT:
    return "quit.png";
  case BM_SAVE:
    return "save.png";
  case BM_SAVEAS:
    return "saveas.png";
  // Add more mappings as needed for the 5-10 key icons
  case BM_TEXT:
    return "text.png";
  case BM_CHART:
    return "chart.png";
  case BM_EDIT:
    return "edit.png";
  case BM_PRINT:
    return "print.png";
  default:
    return wxEmptyString;
  }
}

wxBitmap ImageProvider::getBitmap(const BitmapId &index,
                                  const int rotateHue) // Updated method
{
  // 1. Try to load external file first (Modernization hook)
  wxString fname = bitmapId2Name(index);
  if (!fname.IsEmpty()) {
    wxBitmap fileBmp = getFileBasedBitmapConservative(fname, rotateHue);
    if (fileBmp.IsOk() && fileBmp.GetWidth() > 0) { // Check if valid
      // Error bmp is returned if not found, we need to check if it IS the error
      // bmp. getFileBasedBitmapConservative returns errorBmp if failed. We can
      // check if it is the same object or size/content. Simpler: check if file
      // exists before calling, or rely on a "strict" load. usage of
      // getFileBasedBitmapRef checks Cache. We'll trust
      // getFileBasedBitmapConservative for now but it returns errorBmp on fail.
      // Let's check against errorBmp size or identity if possible, or just
      // re-implement simple check.
      wxString path = FileConfig::get()->getPicDir() + fname;
      if (wxFile::Exists(path)) {
        return fileBmp;
      }
    }
  }

  // 2. Fallback to XPM
  // char **bmp = getBitmapArray( index );
  char **bmp = bitmapId2CharArray(index);

  if (rotateHue) {
    // printf( "ROTATE NOW %d\n", rotateHue );
    wxImage image(bmp);
    image.RotateHue(rotateHue / 360);
    return wxBitmap(image);

  } else
    return wxBitmap(bmp);
}
