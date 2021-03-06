/*
 * TeXShop - TeX editor for Mac OS
 * Copyright (C) 2000-2005 Richard Koch
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * $Id: MyPDFKitView.h 260 2007-08-08 22:51:09Z richard_koch $
 *
 * Parts of this code are taken from Apple's example PDFKitViewer.
 *
 */

#import <AppKit/AppKit.h>
#import <Quartz/Quartz.h>
#import <AppKit/NSEvent.h>


@interface MyPDFKitView : PDFView <NSTableViewDelegate, NSWindowDelegate>
{
	id								currentPage;
	id								totalPage;
	id								myScale;
	id								myStepper;
	id								currentPage1;
	id								totalPage1;
	id								myScale1;
	id								myStepper1;
	id								myDocument;
	NSDrawer						*_drawer;
	PDFOutline						*_outline;
	NSTextField						*_noOutlineText;
	NSOutlineView					*_outlineView;

	NSMutableArray					*_searchResults;
	IBOutlet NSTableView			*_searchTable;
	IBOutlet NSProgressIndicator	*_searchProgress;
	IBOutlet NSMatrix				*mouseModeMatrix;
	IBOutlet NSMenu					*mouseModeMenu;


	NSWindow						*myPDFWindow;
	NSInteger								pageStyle;
    // NSInteger                               oldPageStyle;
    // NSInteger                               fullscreenPageStyle;
	NSInteger								firstPageStyle;
	NSInteger								resizeOption;
    // NSInteger                               oldResizeOption;
    // NSInteger                               fullscreenResizeOption;

	NSInteger								totalPages;

	NSInteger								mouseMode;
	NSInteger								currentMouseMode;

	NSInteger								totalRotation;
	NSInteger								scaleMag;  // view's magnification

	NSRect							selectedRect;
	NSRect							oldVisibleRect;
	NSTimer							*selRectTimer;

	// copy/paste stuff
	id								imageTypeView;
	id								imageTypePopup;

	NSInteger								pageIndexForMark;
	NSRect							pageBoundsForMark;
	BOOL							drawMark;
	BOOL							showSync;
	NSMutableArray					*sourceFiles;

	double							oldMagnification;

	BOOL							downOverLink;
	NSRect							rect;  // to simulate cacheImageInRect
	
	NSPoint							offsetPoint;
	NSPoint							menuSyncPoint;  // For calling sync using a contextual menu
	
	BOOL							secondNeedsInitialization;
	NSInteger								secondTheIndex;
	NSRect							secondFullRect, secondVisibleRect;
	BOOL							protectFind;
    
    BOOL							oldSync;
    NSRect							syncRect[200];
	int								numberSyncRect;

	
	
}

// - (void) scheduleAddintToolips;
- (id) init;
- (void) setup;
- (void) initializeDisplay;
- (void) showWithPath: (NSString *)imagePath;
- (void) reShowWithPath: (NSString *)imagePath;
- (void) showForSecond;
- (void) prepareSecond;
- (void) reShowForSecond;
- (void) setupPageStyle;
- (void) setupMagnificationStyle;
- (BOOL) doReleaseDocument;

- (void) rotateClockwise:sender;
- (void) rotateCounterclockwise:sender;
- (void) rotateClockwisePrimary;
- (void) rotateCounterclockwisePrimary;

- (void) goBack:sender;
- (void) goForward: sender;

- (void) goToKitPageNumber: (NSInteger)thePage;
- (void) goToKitPage: (id)sender;
- (void) previousPage: (id)sender;
- (void) nextPage: (id)sender;
- (void) firstPage: (id)sender;
- (void) lastPage: (id)sender;
- (void) changeScale: sender;
- (void) doStepper: sender;
- (double)magnification;
- (void) setMagnification: (double)magnification;
- (void) changePageStyle: (id)sender;
- (void) changePDFViewSize: (id)sender;
- (void) copy: (id)sender;
- (void) saveSelectionToFile: (id)sender;
- (IBAction) toggleDrawer: (id) sender;
- (void) takeDestinationFromOutline: (id) sender;
- (void) changeMouseMode: (id)sender;
- (void) mouseDown: (NSEvent *) theEvent;
- (void) mouseUp: (NSEvent *) theEvent;
- (void) mouseDragged: (NSEvent *) theEvent;
- (void) mouseMoved: (NSEvent *) theEvent;
- (void) scrollByDragging: (NSEvent *)theEvent;
- (void) zoomIn: (id)sender;
- (void) zoomOut: (id)sender;

- (BOOL) validateMenuItem:(NSMenuItem *)anItem;

// printing
- (void) printDocument: sender;

- (void)selectARect: (NSEvent *)theEvent;
- (void)selectAll: (id)sender;
- (void)updateMarquee: (NSTimer *)timer;
- (void)cleanupMarquee: (BOOL)terminate;
- (void)recacheMarquee;
- (BOOL)hasSelection;
- (NSData *)imageDataFromSelectionType: (NSInteger)type;
// - (void)saveSelectionToFile: (id)sender;
- (void) chooseExportImageType: sender;
// drag & drop
- (void)startDragging: (NSEvent *)theEvent; // mitsu 1.29 drag & drop
- (void)doMagnifyingGlass:(NSEvent *)theEvent level: (NSInteger)level;
- (void)flagsChanged:(NSEvent *)theEvent;
- (void)doSync: (NSPoint)thePoint;
- (BOOL)doNewSync: (NSPoint)thePoint;
- (BOOL)doSyncTeX: (NSPoint)thePoint;
- (void)drawDotsForPage:(NSInteger)page atPoint: (NSPoint)p;
- (void)drawPage:(PDFPage *)page;
- (void)resetCursorRects;
- (void)setIndexForMark: (NSInteger)idx;
- (void)setBoundsForMark: (NSRect)bounds;
- (void)setDrawMark: (BOOL)value;
- (void)setupSourceFiles;
- (void)keyDown:(NSEvent *)theEvent;
- (void)updateBackground: (NSRect)aRect;
- (void)goToKitPageNumber: (NSInteger) thePage; 
- (NSMenu *)menuForEvent:(NSEvent *)theEvent;
- (void)fixMagnificationControls;
- (NSMutableArray *)getSearchResults;
- (void)resetSearchDelegate;
- (void)cancelSearch;
- (void)setProtectFind: (BOOL)value;
- (void) setShowSync: (BOOL)value;
- (void)setNumberSyncRect: (int)value;
- (void)setSyncRect: (int)which originX: (float)x originY: (float)y width: (float)width height: (float)height;
- (void)setOldSync: (BOOL)value;
- (NSInteger)pageStyle;
- (NSInteger)resizeOption;
- (void)changePageStyleTo:(NSInteger)newStyle;
- (void)changePDFViewSizeTo: (NSInteger)newResizeOption;
@end

