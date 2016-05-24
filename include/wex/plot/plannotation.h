#ifndef __pl_annotation_h
#define __pl_annotation_h

#include <wx/string.h>

#include "wex/plot/pltext.h"
#include "wex/plot/ploutdev.h"

class wxPLAnnotationMapping
{
public:
	enum PositionMode { FRACTIONAL, POINTS, AXIS };
	wxPLAnnotationMapping();
	virtual ~wxPLAnnotationMapping();
	virtual wxRealPoint ToDevice( const wxRealPoint &pos ) const = 0;
};

class wxPLAnnotation
{
public:
	wxPLAnnotation();
	virtual ~wxPLAnnotation();
	virtual void Draw( wxPLOutputDevice &dc, const wxPLAnnotationMapping &map ) = 0;
};

class wxPLTextAnnotation : public wxPLAnnotation
{
	wxString m_text;
	wxRealPoint m_pos;
	double m_size;
	double m_angle;
	wxColour m_colour;
	wxPLTextLayout::TextAlignment m_align;
	wxPLTextLayout *m_layout;
public:
	wxPLTextAnnotation( const wxString &text,
		const wxRealPoint &pos,
		double size = 0,
		double angle = 0,
		const wxColour &c = *wxBLACK,
		wxPLTextLayout::TextAlignment align = wxPLTextLayout::LEFT );

	virtual ~wxPLTextAnnotation();
	
	virtual void Draw( wxPLOutputDevice &dc, const wxPLAnnotationMapping &map );
};

class wxPLLineAnnotation : public wxPLAnnotation
{
public:
	enum ArrowType { NO_ARROW, FILLED_ARROW, OUTLINE_ARROW };
	wxPLLineAnnotation( const std::vector<wxRealPoint> &pts,
		double size = 0,
		const wxColour &c = *wxBLACK,
		wxPLOutputDevice::Style style = wxPLOutputDevice::SOLID,
		ArrowType arrow = NO_ARROW );

	virtual ~wxPLLineAnnotation();
	
	virtual void Draw( wxPLOutputDevice &dc, const wxPLAnnotationMapping &map );

private:
	std::vector<wxRealPoint> m_points;
	double m_size;
	wxColour m_colour;
	wxPLOutputDevice::Style m_style;
	ArrowType m_arrow;
};

#endif
