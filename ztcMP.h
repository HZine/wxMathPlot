#pragma once
#include "mathplot.h"

class MyFrame : public wxFrame
{
public:
    MyFrame();

    void OnAbout(wxCommandEvent& event);
    void OnQuit(wxCommandEvent& event);
    void OnPrintPreview(wxCommandEvent& event);
    void OnPrint(wxCommandEvent& event);
    void OnFit(wxCommandEvent& event);
    void OnAlignXAxis(wxCommandEvent& event);
    void OnAlignYAxis(wxCommandEvent& event);
    void OnToggleGrid(wxCommandEvent& event);
    void OnToggleScrollbars(wxCommandEvent& event);
    void OnToggleInfoLayer(wxCommandEvent& event);
    void OnSaveScreenshot(wxCommandEvent& event);
    void OnToggleLissajoux(wxCommandEvent& event);
    void OnToggleSine(wxCommandEvent& event);
    void OnToggleCosine(wxCommandEvent& event);
    void OnBlackTheme(wxCommandEvent& event);

    mpWindow* m_plot;
    wxTextCtrl* m_log;

private:
    int axesPos[2];
    bool ticks;
    mpInfoCoords* nfo; // mpInfoLayer* nfo;
    DECLARE_DYNAMIC_CLASS(MyFrame)
    DECLARE_EVENT_TABLE()
};

enum
{
    ID_QUIT = 108,
    ID_ABOUT,
    ID_PRINT,
    ID_PRINT_PREVIEW,
    ID_ALIGN_X_AXIS,
    ID_ALIGN_Y_AXIS,
    ID_TOGGLE_GRID,
    ID_TOGGLE_SCROLLBARS,
    ID_TOGGLE_INFO,
    ID_SAVE_SCREENSHOT,
    ID_TOGGLE_LISSAJOUX,
    ID_TOGGLE_SINE,
    ID_TOGGLE_COSINE,
    ID_BLACK_THEME
};



class MySIN : public mpFX
{
    double m_freq, m_amp;
public:
    MySIN(double freq, double amp) : mpFX(wxT("f(x) = SIN(x)"), mpALIGN_LEFT) { m_freq = freq; m_amp = amp; m_drawOutsideMargins = false; }
    virtual double GetY(double x) { return m_amp * sin(x / 6.283185 / m_freq); }
    virtual double GetMinY() { return -m_amp; }
    virtual double GetMaxY() { return  m_amp; }
};

// MyCOSinverse

class MyCOSinverse : public mpFY
{
    double m_freq, m_amp;
public:
    MyCOSinverse(double freq, double amp) : mpFY(wxT("g(y) = COS(y)"), mpALIGN_BOTTOM) { m_freq = freq; m_amp = amp; m_drawOutsideMargins = false; }
    virtual double GetX(double y) { return m_amp * cos(y / 6.283185 / m_freq); }
    virtual double GetMinX() { return -m_amp; }
    virtual double GetMaxX() { return  m_amp; }
};

// MyLissajoux

class MyLissajoux : public mpFXY
{
    double m_rad;
    int    m_idx;
public:
    MyLissajoux(double rad) : mpFXY(wxT("Lissajoux")) { m_rad = rad; m_idx = 0; m_drawOutsideMargins = false; }
    virtual bool GetNextXY(double& x, double& y)
    {
        if (m_idx < 360)
        {
            x = m_rad * cos(m_idx / 6.283185 * 360);
            y = m_rad * sin(m_idx / 6.283185 * 360 * 3);
            m_idx++;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    virtual void Rewind() { m_idx = 0; }
    virtual double GetMinX() { return -m_rad; }
    virtual double GetMaxX() { return  m_rad; }
    virtual double GetMinY() { return -m_rad; }
    virtual double GetMaxY() { return  m_rad; }
};
