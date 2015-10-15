#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "libXBMC_addon.h"

typedef void* GUIHANDLE;

/* current ADDONGUI API version */
#define KODI_GUILIB_API_VERSION "5.8.0"

/* min. ADDONGUI API version */
#define KODI_GUILIB_MIN_API_VERSION "5.8.0"

#define ADDON_ACTION_PREVIOUS_MENU          10
#define ADDON_ACTION_CLOSE_DIALOG           51
#define ADDON_ACTION_NAV_BACK               92

class CAddonGUIWindow;
class CAddonGUISpinControl;
class CAddonGUIRadioButton;
class CAddonGUIProgressControl;
class CAddonListItem;
class CAddonGUIRenderingControl;
class CAddonGUISliderControl;
class CAddonGUISettingsSliderControl;

class CHelper_libKODI_guilib
{
public:
  CHelper_libKODI_guilib()
  {
  }

  ~CHelper_libKODI_guilib()
  {
  }

  bool RegisterMe(void *Handle)
  {
    return Handle != NULL;
  }

  void Lock()
  {
  }

  void Unlock()
  {
  }

  int GetScreenHeight()
  {
    return 0;
  }

  int GetScreenWidth()
  {
    return 0;
  }

  int GetVideoResolution()
  {
    return 0;
  }

  CAddonGUIWindow* Window_create(const char *xmlFilename, const char *defaultSkin, bool forceFallback, bool asDialog)
  {
    return NULL;
  }

  void Window_destroy(CAddonGUIWindow* p)
  {
  }

  CAddonGUISpinControl* Control_getSpin(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseSpin(CAddonGUISpinControl* p)
  {
  }

  CAddonGUIRadioButton* Control_getRadioButton(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseRadioButton(CAddonGUIRadioButton* p)
  {
  }

  CAddonGUIProgressControl* Control_getProgress(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseProgress(CAddonGUIProgressControl* p)
  {
  }

  CAddonListItem* ListItem_create(const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path)
  {
    return NULL;
  }

  void ListItem_destroy(CAddonListItem* p)
  {
  }

  CAddonGUIRenderingControl* Control_getRendering(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseRendering(CAddonGUIRenderingControl* p)
  {
  }

  CAddonGUISliderControl* Control_getSlider(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseSlider(CAddonGUISliderControl* p)
  {
  }

  CAddonGUISettingsSliderControl* Control_getSettingsSlider(CAddonGUIWindow *window, int controlId)
  {
    return NULL;
  }

  void Control_releaseSettingsSlider(CAddonGUISettingsSliderControl* p)
  {
  }

  /*! @name GUI Keyboard functions */
  //@{
  bool Dialog_Keyboard_ShowAndGetInput(char &strText, unsigned int iMaxStringSize, const char *strHeading, bool allowEmptyResult, bool hiddenInput, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndGetInput(char &strText, unsigned int iMaxStringSize, bool allowEmptyResult, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndGetNewPassword(char &strNewPassword, unsigned int iMaxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndGetNewPassword(char &strNewPassword, unsigned int iMaxStringSize, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndVerifyNewPassword(char &strNewPassword, unsigned int iMaxStringSize, const char *strHeading, bool allowEmptyResult, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndVerifyNewPassword(char &strNewPassword, unsigned int iMaxStringSize, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  int Dialog_Keyboard_ShowAndVerifyPassword(char &strPassword, unsigned int iMaxStringSize, const char *strHeading, int iRetries, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_ShowAndGetFilter(char &strText, unsigned int iMaxStringSize, bool searching, unsigned int autoCloseMs = 0)
  {
    return false;
  }

  bool Dialog_Keyboard_SendTextToActiveKeyboard(const char *aTextString, bool closeKeyboard = false)
  {
    return false;
  }

  bool Dialog_Keyboard_isKeyboardActivated()
  {
    return false;
  }
  //@}

  /*! @name GUI Numeric functions */
  //@{
  bool Dialog_Numeric_ShowAndVerifyNewPassword(char &strNewPassword, unsigned int iMaxStringSize)
  {
    return false;
  }

  int Dialog_Numeric_ShowAndVerifyPassword(char &strPassword, unsigned int iMaxStringSize, const char *strHeading, int iRetries)
  {
    return 0;
  }

  bool Dialog_Numeric_ShowAndVerifyInput(char &strPassword, unsigned int iMaxStringSize, const char *strHeading, bool bGetUserInput)
  {
    return false;
  }

  bool Dialog_Numeric_ShowAndGetTime(tm &time, const char *strHeading)
  {
    return false;
  }

  bool Dialog_Numeric_ShowAndGetDate(tm &date, const char *strHeading)
  {
    return false;
  }

  bool Dialog_Numeric_ShowAndGetIPAddress(char &strIPAddress, unsigned int iMaxStringSize, const char *strHeading)
  {
    return false;
  }

  bool Dialog_Numeric_ShowAndGetNumber(char &strInput, unsigned int iMaxStringSize, const char *strHeading, unsigned int iAutoCloseTimeoutMs = 0)
  {
    return false;
  }

  bool Dialog_Numeric_ShowAndGetSeconds(char &strTime, unsigned int iMaxStringSize, const char *strHeading)
  {
    return false;
  }
  //@}

  /*! @name GUI File browser functions */
  //@{
  bool Dialog_FileBrowser_ShowAndGetFile(const char *directory, const char *mask, const char *heading, char &strPath, unsigned int iMaxStringSize, bool useThumbs = false, bool useFileDirectories = false, bool singleList = false)
  {
    return false;
  }
  //@}

  /*! @name GUI OK Dialog functions */
  //@{
  void Dialog_OK_ShowAndGetInput(const char *heading, const char *text)
  {
  }

  void Dialog_OK_ShowAndGetInput(const char *heading, const char *line0, const char *line1, const char *line2)
  {
  }
  //@}

  /*! @name GUI Yes No Dialog functions */
  //@{
  bool Dialog_YesNo_ShowAndGetInput(const char *heading, const char *text, bool& bCanceled, const char *noLabel = "", const char *yesLabel = "")
  {
    return false;
  }

  bool Dialog_YesNo_ShowAndGetInput(const char *heading, const char *line0, const char *line1, const char *line2, const char *noLabel = "", const char *yesLabel = "")
  {
    return false;
  }

  bool Dialog_YesNo_ShowAndGetInput(const char *heading, const char *line0, const char *line1, const char *line2, bool &bCanceled, const char *noLabel = "", const char *yesLabel = "")
  {
    return false;
  }
  //@}

  /*! @name GUI Text viewer Dialog */
  //@{
  void Dialog_TextViewer(const char *heading, const char *text)
  {
  }
  //@}

  /*! @name GUI select Dialog */
  //@{
  int Dialog_Select(const char *heading, const char *entries[], unsigned int size, int selected = -1)
  {
    return 0;
  }
  //@}

};

class CAddonGUISpinControl
{
public:
  CAddonGUISpinControl(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUISpinControl(void) {}

  virtual void SetVisible(bool yesNo);
  virtual void SetText(const char *label);
  virtual void Clear();
  virtual void AddLabel(const char *label, int iValue);
  virtual int GetValue();
  virtual void SetValue(int iValue);

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_SpinHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUIRadioButton
{
public:
  CAddonGUIRadioButton(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUIRadioButton() {}

  virtual void SetVisible(bool yesNo);
  virtual void SetText(const char *label);
  virtual void SetSelected(bool yesNo);
  virtual bool IsSelected();

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_ButtonHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUIProgressControl
{
public:
  CAddonGUIProgressControl(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUIProgressControl(void) {}

  virtual void SetPercentage(float fPercent);
  virtual float GetPercentage() const;
  virtual void SetInfo(int iInfo);
  virtual int GetInfo() const;
  virtual std::string GetDescription() const;

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_ProgressHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUISliderControl
{
public:
  CAddonGUISliderControl(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUISliderControl(void) {}

  virtual void        SetVisible(bool yesNo);
  virtual std::string GetDescription() const;

  virtual void        SetIntRange(int iStart, int iEnd);
  virtual void        SetIntValue(int iValue);
  virtual int         GetIntValue() const;
  virtual void        SetIntInterval(int iInterval);

  virtual void        SetPercentage(float fPercent);
  virtual float       GetPercentage() const;

  virtual void        SetFloatRange(float fStart, float fEnd);
  virtual void        SetFloatValue(float fValue);
  virtual float       GetFloatValue() const;
  virtual void        SetFloatInterval(float fInterval);

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_SliderHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUISettingsSliderControl
{
public:
  CAddonGUISettingsSliderControl(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUISettingsSliderControl(void) {}

  virtual void        SetVisible(bool yesNo);
  virtual void        SetText(const char *label);
  virtual std::string GetDescription() const;

  virtual void        SetIntRange(int iStart, int iEnd);
  virtual void        SetIntValue(int iValue);
  virtual int         GetIntValue() const;
  virtual void        SetIntInterval(int iInterval);

  virtual void        SetPercentage(float fPercent);
  virtual float       GetPercentage() const;

  virtual void        SetFloatRange(float fStart, float fEnd);
  virtual void        SetFloatValue(float fValue);
  virtual float       GetFloatValue() const;
  virtual void        SetFloatInterval(float fInterval);

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_SettingsSliderHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonListItem
{
friend class CAddonGUIWindow;

public:
  CAddonListItem(void *hdl, void *cb, const char *label, const char *label2, const char *iconImage, const char *thumbnailImage, const char *path);
  virtual ~CAddonListItem(void) {}

  virtual const char  *GetLabel();
  virtual void         SetLabel(const char *label);
  virtual const char  *GetLabel2();
  virtual void         SetLabel2(const char *label);
  virtual void         SetIconImage(const char *image);
  virtual void         SetThumbnailImage(const char *image);
  virtual void         SetInfo(const char *Info);
  virtual void         SetProperty(const char *key, const char *value);
  virtual const char  *GetProperty(const char *key) const;
  virtual void         SetPath(const char *Path);

//    {(char*)"select();
//    {(char*)"isSelected();
protected:
  GUIHANDLE   m_ListItemHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUIWindow
{
friend class CAddonGUISpinControl;
friend class CAddonGUIRadioButton;
friend class CAddonGUIProgressControl;
friend class CAddonGUIRenderingControl;
friend class CAddonGUISliderControl;
friend class CAddonGUISettingsSliderControl;

public:
  CAddonGUIWindow(void *hdl, void *cb, const char *xmlFilename, const char *defaultSkin, bool forceFallback, bool asDialog);
  virtual ~CAddonGUIWindow();

  virtual bool         Show();
  virtual void         Close();
  virtual void         DoModal();
  virtual bool         SetFocusId(int iControlId);
  virtual int          GetFocusId();
  virtual bool         SetCoordinateResolution(int res);
  virtual void         SetProperty(const char *key, const char *value);
  virtual void         SetPropertyInt(const char *key, int value);
  virtual void         SetPropertyBool(const char *key, bool value);
  virtual void         SetPropertyDouble(const char *key, double value);
  virtual const char  *GetProperty(const char *key) const;
  virtual int          GetPropertyInt(const char *key) const;
  virtual bool         GetPropertyBool(const char *key) const;
  virtual double       GetPropertyDouble(const char *key) const;
  virtual void         ClearProperties();
  virtual int          GetListSize();
  virtual void         ClearList();
  virtual GUIHANDLE    AddStringItem(const char *name, int itemPosition = -1);
  virtual void         AddItem(GUIHANDLE item, int itemPosition = -1);
  virtual void         AddItem(CAddonListItem *item, int itemPosition = -1);
  virtual void         RemoveItem(int itemPosition);
  virtual GUIHANDLE    GetListItem(int listPos);
  virtual void         SetCurrentListPosition(int listPos);
  virtual int          GetCurrentListPosition();
  virtual void         SetControlLabel(int controlId, const char *label);
  virtual void         MarkDirtyRegion();

  virtual bool         OnClick(int controlId);
  virtual bool         OnFocus(int controlId);
  virtual bool         OnInit();
  virtual bool         OnAction(int actionId);

  GUIHANDLE m_cbhdl;
  bool (*CBOnInit)(GUIHANDLE cbhdl);
  bool (*CBOnFocus)(GUIHANDLE cbhdl, int controlId);
  bool (*CBOnClick)(GUIHANDLE cbhdl, int controlId);
  bool (*CBOnAction)(GUIHANDLE cbhdl, int actionId);

protected:
  GUIHANDLE m_WindowHandle;
  void *m_Handle;
  void *m_cb;
};

class CAddonGUIRenderingControl
{
public:
  CAddonGUIRenderingControl(void *hdl, void *cb, CAddonGUIWindow *window, int controlId);
  virtual ~CAddonGUIRenderingControl();
  virtual void Init();

  virtual bool Create(int x, int y, int w, int h, void *device);
  virtual void Render();
  virtual void Stop();
  virtual bool Dirty();

  GUIHANDLE m_cbhdl;
  bool (*CBCreate)(GUIHANDLE cbhdl, int x, int y, int w, int h, void *device);
  void (*CBRender)(GUIHANDLE cbhdl);
  void (*CBStop)(GUIHANDLE cbhdl);
  bool (*CBDirty)(GUIHANDLE cbhdl);

private:
  CAddonGUIWindow *m_Window;
  int         m_ControlId;
  GUIHANDLE   m_RenderingHandle;
  void *m_Handle;
  void *m_cb;
};
