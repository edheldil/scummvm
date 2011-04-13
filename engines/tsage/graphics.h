/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL: https://scummvm-misc.svn.sourceforge.net/svnroot/scummvm-misc/trunk/engines/tsage/graphics.h $
 * $Id: graphics.h 184 2011-02-03 11:31:38Z dreammaster $
 *
 */

#ifndef RING_GRAPHICS_H
#define RING_GRAPHICS_H

#include "tsage/events.h"
#include "tsage/saveload.h"
#include "common/list.h"
#include "common/rect.h"
#include "common/system.h"
#include "graphics/surface.h"

namespace tSage {

class GfxSurface;
class Region;

/**
 * Extended Rect class with extra support methods
 */
class Rect: public Common::Rect, public Serialisable {
public:
	Rect(): Common::Rect() {};
	Rect(int16 x1, int16 y1, int16 x2, int16 y2): Common::Rect(x1, y1, x2, y2) {};

	void set(int16 x1, int16 y1, int16 x2, int16 y2);
	void collapse(int dx, int dy);
	void centre(int dx, int dy);
	void centre(const Rect &r);
	void centre(const Common::Point &pt) { centre(pt.x, pt.y); }
	void contain(const Rect &r);
	void resize(const GfxSurface &surface, int xp, int yp, int percent);
	void expandPanes();

	virtual void synchronise(Serialiser &s);
};

class GfxColours {
public:
	uint8 foreground;
	uint8 background;

	GfxColours(): foreground(0), background(0) {};
};

class LineSlice {
public:
	int xs, xe;
	
	LineSlice() { xs = 0; xe = 0; }
	LineSlice(int xStart, int xEnd) { xs = xStart; xe = xEnd; }
};

class GfxSurface {
private:
	Graphics::Surface *_customSurface;
	Graphics::Surface *_screenSurfaceP;
	int _lockSurfaceCtr;
	bool _screenSurface;

	bool _disableUpdates;
	Rect _bounds;
public:
	Common::Point _centroid;
	int _transColour;
public:
	GfxSurface();
	GfxSurface(const GfxSurface &s);
	~GfxSurface();

	void setScreenSurface();
	Graphics::Surface lockSurface();
	void unlockSurface();
	void create(int width, int height);
	void setBounds(const Rect &bounds) { _bounds = bounds; };
	const Rect &getBounds() const { return _bounds; };

	void copyFrom(GfxSurface &src, Rect srcBounds, Rect destBounds, Region *priorityRegion = NULL);
	void copyFrom(GfxSurface &src, Rect destBounds, Region *priorityRegion = NULL) {
		copyFrom(src, src.getBounds(), destBounds, priorityRegion);
	}
	void copyFrom(GfxSurface &src, int destX = 0, int destY = 0, Region *priorityRegion = NULL) {
		Rect tempRect = src.getBounds();
		tempRect.moveTo(destX, destY);
		copyFrom(src, tempRect, priorityRegion);
	}
	void draw(const Common::Point &pt, Rect *rect = NULL);
	void fillRect(const Rect &bounds, int colour);
	GfxSurface &operator=(const GfxSurface &s);

	static void loadScreenSection(Graphics::Surface &dest, int xHalf, int yHalf, int xSection, int ySection);
	static bool displayText(const Common::String &msg, const Common::Point &pt = Common::Point(160, 100));
};

enum TextAlign {ALIGN_LEFT = 0, ALIGN_CENTRE = 1, ALIGN_RIGHT = 2, ALIGN_JUSTIFIED = 3};

class GfxFont {
	friend class GfxFontBackup;
private:
	GfxManager *_gfxManager;
	// Raw font details
	const byte *_fontData;
	int _numChars;
	Common::Point _fontSize;
	int _bpp;
public:
	// Font fields
	Common::Point _edgeSize;
	Common::Point _position;
	bool _fillFlag;
	GfxColours _colours;
	GfxColours _colours2;
	uint32 _fontNumber;
	Common::Point _topLeft;
public:
	GfxFont();
	virtual ~GfxFont();

	void setFontNumber(uint32 fontNumber);
	int32 getHeight() const { return _fontSize.y; }
	int getCharWidth(char ch);
	int getStringWidth(const char *s, int numChars);
	int getStringWidth(const char *s);
	int getStringFit(const char *&s, int maxWidth);
	void getStringBounds(const char *s, Rect &bounds, int maxWidth);

	void setOwner(GfxManager *owner) { _gfxManager = owner; }
	void setPosition(int xp, int yp) { _position.x = xp; _position.y = yp; }
	int writeChar(const char ch);
	void writeString(const char *s);
	void writeString(const char *s, int numChars);
	void writeLines(const char *s, const Rect &bounds, TextAlign align);
};

class GfxFontBackup {
private:
	GfxSurface *_surface;
	Common::Point _edgeSize;
	Common::Point _position;
	GfxColours _colours;
	uint32 _fontNumber;
public:
	GfxFontBackup();
	~GfxFontBackup();
};

enum GFX_FLAGS {GFXFLAG_THICK_FRAME = 8};

class GfxManager;

class GfxElement {
public:
	GfxElement *_owner;
	Rect _bounds;
	uint16 _flags;
	uint16 _fontNumber;
	GfxColours _colours;
	GfxColours _fontColours;
	uint16 _keycode;
public:
	GfxElement();
	virtual ~GfxElement() {}

	void drawFrame();

	// Virtual table method
	virtual void setDefaults();
	virtual void remove() { _owner = NULL; }
	virtual void highlight();
	virtual void draw() {};
	virtual bool process(Event &event) { return false; };
	virtual bool focusedEvent(Event &event);
};

class GfxImage: public GfxElement {
public:
	GfxSurface _surface;
	int _resNum;
	int _rlbNum;
	int _cursorNum;
public:
	GfxImage();

	void setDetails(int resNum, int rlbNum, int cursorNum);

	virtual void setDefaults();
	virtual void draw();
	virtual bool process(Event &event) { return false; }
};

class GfxMessage: public GfxElement {
public:
	Common::String _message;
	TextAlign _textAlign;
	int _width;
public:
	GfxMessage();
	virtual ~GfxMessage() {}

	void set(const Common::String &s, int width, TextAlign textAlign);

	virtual void setDefaults();
	virtual void draw();
};

class GfxButton: public GfxElement {
private:
	void setFocus();
public:
	Common::String _message;
public:
	GfxButton(): GfxElement() {};
	virtual ~GfxButton() {}

	void setText(const Common::String &s) {
		_message = s;
		setDefaults();
	}

	// Virtual table method
	virtual void setDefaults();
	virtual void draw();
	virtual bool process(Event &event);
};

class GfxManager {
private:
	GfxSurface &_surface;
public:
	GfxManager *_oldManager;
	Common::Point _topLeft;
	Rect _bounds;
	Rect _pane0Rect4;
	GfxFont _font;
public:
	GfxManager();
	GfxManager(GfxSurface &s);
	virtual ~GfxManager() {}

	void setDefaults();
	void activate();
	void deactivate();

	// Accessor methods
	int getStringWidth(const char *s, int numChars);
	int getStringWidth(const char *s);
	void getStringBounds(const char *s, Rect &bounds, int maxWidth);

	void setDialogPalette();
	Graphics::Surface lockSurface() { 
		_surface.setBounds(_bounds);
		return _surface.lockSurface();
	}
	void unlockSurface() { _surface.unlockSurface(); };
	void fillArea(int xp, int yp, int colour);
	void fillRect(const Rect &bounds, int colour);
	void fillRect2(int xs, int ys, int width, int height, int colour);
	void setFillFlag(bool v) { _font._fillFlag = v; }

	static int getAngle(const Common::Point &p1, const Common::Point &p2);

	// Virtual method table
	virtual void xorArea(const Common::Rect &r, int colour, int fillMode) {
		//_surface->xorArea(r, colour, fillMode);
	}
	virtual void draw(const Common::Rect &r, void *gfxData, int v1, GfxColours *colours) {
		//_surface->draw(r, gfxData, v1, colours);
	}
	virtual void copy(const byte *src, byte *dest, int size) {
		Common::copy(src, src + size, dest);
	}
	virtual void set(byte *dest, int size, byte val) {
		Common::set_to(dest, dest + size, val);
	}
	void copyFrom(GfxSurface &src, Rect destBounds, Region *priorityRegion = NULL) {
		_surface.setBounds(_bounds);
		_surface.copyFrom(src, destBounds, priorityRegion);
	}
	void copyFrom(GfxSurface &src, int destX, int destY) {
		_surface.setBounds(_bounds);
		_surface.copyFrom(src, destX, destY);
		g_system->updateScreen();
	}
	GfxSurface &getSurface() {
		_surface.setBounds(_bounds);
		return _surface;
	}
};

typedef Common::List<GfxElement *> GfxElementList;

class GfxDialog: public GfxElement {
public:
	GfxManager _gfxManager;
	GfxElementList _elements;
	GfxButton *_defaultButton;
	GfxSurface *_savedArea;
public:
	GfxDialog();
	virtual ~GfxDialog();

	void add(GfxElement *element);
	void addElements(GfxElement *ge, ...);
	void setTopLeft(int xp, int yp);
	void setCentre(int xp, int yp);
	void frame() { 
		setDefaults();
		_bounds.collapse(6, 6); 
	}
	GfxButton *execute(GfxButton *defaultButton = NULL);

	virtual void setDefaults();
	virtual void remove();
	virtual void draw();

	static void setPalette();
};

GfxSurface *Surface_getArea(GfxSurface &src, const Rect &bounds);

GfxSurface surfaceFromRes(const byte *imgData);
GfxSurface surfaceFromRes(int resNum, int rlbNum, int subNum);

} // End of namespace tSage

#endif