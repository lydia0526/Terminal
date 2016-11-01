/*++

Copyright (c) 1992  Microsoft Corporation

Module Name:

    console.h

Abstract:

    This module contains the definitions for the console applet

Author:

    Jerry Shea (jerrysh) Feb-3-1992

Revision History:
    Mike Griese, migrie, Oct 2016:
        Moved to cpp and the OpenConsole project

--*/
#pragma once

#include "font.h"
#include "OptionsPage.h"
#include "LayoutPage.h"
#include "ColorsPage.h"
//
// Icon ID.
//

#define IDI_CONSOLE                   1

//
// String table constants
//

#define IDS_NAME                      1
#define IDS_INFO                      2
#define IDS_TITLE                     3
#define IDS_RASTERFONT                4
#define IDS_FONTSIZE                  5
#define IDS_SELECTEDFONT              6
#define IDS_SAVE                      7
#define IDS_LINKERRCAP                8
#define IDS_LINKERROR                 9
#define IDS_FONTSTRING               10
#define IDS_TOOLTIP_LINE_SELECTION   11
#define IDS_TOOLTIP_FILTER_ON_PASTE  12
#define IDS_TOOLTIP_LINE_WRAP        13
#define IDS_TOOLTIP_CTRL_KEYS        14
#define IDS_TOOLTIP_EDIT_KEYS        15
// unused 16
#define IDS_TOOLTIP_OPACITY          17

NTSTATUS
MakeAltRasterFont(
    __in UINT CodePage,
    __out COORD *AltFontSize,
    __out BYTE  *AltFontFamily,
    __out ULONG *AltFontIndex,
    __out_ecount(LF_FACESIZE) LPTSTR AltFaceName);

NTSTATUS InitializeDbcsMisc();

BYTE
CodePageToCharSet(
    UINT CodePage
    );

BOOL
ShouldAllowAllMonoTTFonts();

LPTTFONTLIST
SearchTTFont(
    __in_opt LPCTSTR ptszFace,
    BOOL   fCodePage,
    UINT   CodePage
    );

BOOL
IsAvailableTTFont(
    LPCTSTR ptszFace
    );

BOOL
IsAvailableTTFontCP(
    LPCWSTR pwszFace,
    UINT CodePage
    );

BOOL
IsDisableBoldTTFont(
    LPCTSTR ptszFace
    );

LPTSTR
GetAltFaceName(
    LPCTSTR ptszFace
    );

NTSTATUS DestroyDbcsMisc();

int
LanguageListCreate(
    HWND hDlg,
    UINT CodePage
    );

int
LanguageDisplay(
    HWND hDlg,
    UINT CodePage
    ) ;

//
// registry.c
//
NTSTATUS
MyRegOpenKey(
    __in_opt HANDLE hKey,
    __in LPCWSTR lpSubKey,
    __out PHANDLE phResult
    );

NTSTATUS
MyRegEnumValue(
    __in HANDLE hKey,
    __in DWORD dwIndex,
    __in DWORD dwValueLength,
    __out_bcount(dwValueLength) LPWSTR lpValueName,
    __in_range(4, 1024) DWORD dwDataLength,
    __out_bcount(dwDataLength) LPBYTE lpData
    );

//
// Function prototypes
//

INT_PTR ConsolePropertySheet(
    __in HWND hWnd,
    __in PCONSOLE_STATE_INFO pStateInfo);

VOID RegisterClasses(
    HINSTANCE hModule);

VOID UnregisterClasses(
    HINSTANCE hModule);

INT_PTR FontDlgProc(
    HWND hDlg,
    UINT wMsg,
    WPARAM wParam,
    LPARAM lParam);

VOID InitRegistryValues(
    __out PCONSOLE_STATE_INFO pStateInfo);

DWORD GetRegistryValues(
    __out_opt PCONSOLE_STATE_INFO StateInfo);

VOID SetGlobalRegistryValues();

VOID SetRegistryValues(
    PCONSOLE_STATE_INFO StateInfo,
    DWORD dwPage);

PCONSOLE_STATE_INFO InitStateValues(
    HWND hwnd);

LRESULT FontPreviewWndProc(
    HWND hWnd,
    UINT wMsg,
    WPARAM wParam,
    LPARAM lParam);

LRESULT PreviewWndProc(
    HWND hWnd,
    UINT wMsg,
    WPARAM wParam,
    LPARAM lParam);

VOID EndDlgPage(
    _In_ const HWND hDlg,
    _In_ const BOOL fSaveNow);

BOOL UpdateStateInfo(
    HWND hDlg,
    UINT Item,
    int Value);

BOOL InitializeConsoleState();
void UninitializeConsoleState();
void UpdateApplyButton(_In_ const HWND hDlg);
HRESULT FindFontAndUpdateState();

BOOL PopulatePropSheetPageArray(_Out_writes_(cPsps) PROPSHEETPAGE *pPsp, _In_ const size_t cPsps, _In_ const BOOL fRegisterCallbacks);

void CreateAndAssociateToolTipToControl(_In_ const UINT dlgItem, _In_ const HWND hDlg, _In_ const UINT idsToolTip);

BOOL CheckNum(HWND hDlg, UINT Item);
void UpdateItem(HWND hDlg, UINT item, UINT nNum);
void Undo(HWND hControlWindow);

//
// Macros
//
#define AttrToRGB(Attr) (gpStateInfo->ColorTable[(Attr) & 0x0F])
#define ScreenTextColor(pStateInfo) \
            (AttrToRGB(LOBYTE(pStateInfo->ScreenAttributes) & 0x0F))
#define ScreenBkColor(pStateInfo) \
            (AttrToRGB(LOBYTE(pStateInfo->ScreenAttributes >> 4)))
#define PopupTextColor(pStateInfo) \
            (AttrToRGB(LOBYTE(pStateInfo->PopupAttributes) & 0x0F))
#define PopupBkColor(pStateInfo) \
            (AttrToRGB(LOBYTE(pStateInfo->PopupAttributes >> 4)))

#if DBG
  #define _DBGFONTS  0x00000001
  #define _DBGFONTS2 0x00000002
  #define _DBGCHARS  0x00000004
  #define _DBGOUTPUT 0x00000008
  #define _DBGALL    0xFFFFFFFF
  extern ULONG gDebugFlag;

  #define DBGFONTS(_params_)  
  #define DBGFONTS2(_params_) 
  #define DBGCHARS(_params_)  
  #define DBGOUTPUT(_params_) 
#else
  #define DBGFONTS(_params_)
  #define DBGFONTS2(_params_)
  #define DBGCHARS(_params_)
  #define DBGOUTPUT(_params_)
#endif

// Macro definitions that handle codepages
//
#define CP_US       (UINT)437
#define CP_JPN      (UINT)932
#define CP_WANSUNG  (UINT)949
#define CP_TC       (UINT)950
#define CP_SC       (UINT)936

#define IsBilingualCP(cp) ((cp)==CP_JPN || (cp)==CP_WANSUNG)
#define IsEastAsianCP(cp) ((cp)==CP_JPN || (cp)==CP_WANSUNG || (cp)==CP_TC || (cp)==CP_SC)

const unsigned int TRANSPARENCY_RANGE_MIN = 0x4D;

const unsigned int OPTIONS_PAGE_INDEX = 0;
const unsigned int FONT_PAGE_INDEX = 1;
const unsigned int LAYOUT_PAGE_INDEX = 2;
const unsigned int COLORS_PAGE_INDEX = 3;
// number of property sheet pages
static const int NUMBER_OF_PAGES = 4;

