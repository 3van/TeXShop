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
 * $Id: TSDocument.h 262 2007-08-17 01:33:24Z richard_koch $
 *
 * Created by koch in July, 2000.
 *
 */

#import <AppKit/AppKit.h>
#import "TSFullscreenWindow.h"
#import <Quartz/Quartz.h>
#import "NoodleLineNumberView.h"
#import "NoodleLineNumberMarker.h"
#import "TSPreviewWindow.h"
#import "synctex_parser.h"

#define NUMBEROFERRORS	20

/*" Symbolic constants for the default Typeset program to use. "*/
enum DefaultCommand
{
	DefaultCommandTeX = 0,
	DefaultCommandLaTeX = 1,
	DefaultCommandConTEXt = 2,
	DefaultCommandUser = 3
};

typedef enum
{
	kTypesetViaPDFTeX			= 100,
	kTypesetViaGhostScript		= 101,
	kTypesetViaPersonalScript	= 102
} DefaultTypesetMode;

typedef enum {
	isTeX		= 0,
	isOther		= 1,
	isPDF		= 2,
	isEPS		= 3,
	isJPG		= 4,
	isTIFF		= 5
} TSDocumentType;

/*" Symbolic constants for Root File tests "*/
enum RootCommand
{
	RootForOpening = 1,
	RootForTexing = 2,
	RootForPrinting = 3,
	RootForSwitchWindow = 4,
	RootForPdfSync = 5,
	RootForTrashAUX = 6,
	RootForLogFile = 7,
	RootForConsole = 8
};

@class MyPDFKitView;
@class MyPDFView;
@class MySelection;

// FIX RULER SCROLL
@class NoodleLineNumberView;
// END FIX RULER SCROLL

@interface TSDocument : NSDocument <NSTextViewDelegate, NSToolbarDelegate>
{
	IBOutlet NSTextView			*textView1;
	IBOutlet NSTextView			*textView2;
	IBOutlet NSScrollView		*scrollView2;
	IBOutlet NSSplitView		*splitView;

	IBOutlet NSTextView			*textView;		/*" textView displaying the current TeX source "*/
	IBOutlet NSScrollView		*scrollView;		/*" scrollView for textView"*/
	IBOutlet NSWindow			*textWindow;		/*" window displaying the current document "*/
	NoodleLineNumberView		*lineNumberView1;
	NoodleLineNumberView		*lineNumberView2;
	NoodleLineNumberView		*logLineNumberView;

	IBOutlet MyPDFView			*pdfView;		/*" view displaying the current preview "*/
	IBOutlet NSWindow			*pdfWindow;		/*" window displaying the current pdf preview "*/

	IBOutlet MyPDFKitView		*myPDFKitView;
	IBOutlet TSPreviewWindow	*pdfKitWindow;
    IBOutlet TSPreviewWindow    *pdfKitWindow1;
	IBOutlet MyPDFKitView		*myPDFKitView2;

	IBOutlet NSWindow			*outputWindow;		/*" window displaying the output of the running TeX process "*/
	IBOutlet NSTextView			*outputText;		/*" text displaying the output of the running TeX process "*/

	IBOutlet NSTextField		*texCommand;		/*" connected to the command textField on the errors panel "*/
	IBOutlet NSPopUpButton		*popupButton;		/*" popupButton displaying all the TeX templates "*/
	IBOutlet NSPanel			*projectPanel;
	IBOutlet NSTextField		*projectName;
	IBOutlet NSPanel			*requestWindow;
	IBOutlet NSPanel			*printRequestPanel;
	IBOutlet NSPanel			*pagenumberPanel;
	IBOutlet NSPanel			*pagenumberKitPanel;
	IBOutlet NSPanel			*magnificationPanel;
	IBOutlet NSPanel			*magnificationKitPanel;
	IBOutlet NSPanel			*statisticsPanel;
	IBOutlet NSForm				*statisticsForm;
	IBOutlet NSPanel			*extensionPanel;
	IBOutlet NSTextField		*extensionResult;
	IBOutlet NSPopUpButton		*openSaveBox;		// TODO: Rename this to 'encodingPopUp' (don't forget to update the NIBs)
	IBOutlet NSView				*openSaveView;
	IBOutlet NSPanel			*linePanel;
	IBOutlet NSTextField		*lineBox;
	IBOutlet NSButton			*typesetButton;
	IBOutlet NSButton			*typesetButtonEE;
	IBOutlet NSPopUpButton		*programButton;
	IBOutlet NSPopUpButton		*programButtonEE;

	IBOutlet NSBox				*gotopageOutletKK;
	IBOutlet NSBox				*magnificationOutletKK;
	IBOutlet NSMatrix			*mouseModeMatrixKK;
	IBOutlet NSSegmentedControl	*backforthKK;
	IBOutlet NSImageView		*drawerKK;


	IBOutlet NSPopUpButton		*tags;

	IBOutlet NSMatrix			*mouseModeMatrix; // mitsu 1.29 (O)
	IBOutlet NSMenu				*mouseModeMenu; // mitsu 1.29 (O)
	
	NSMenu				*mouseModeMenuKit; // mitsu 1.29 (O)

	IBOutlet NSPopUpButton		*macroButton;		/*" pull-down list for macros "*/
	IBOutlet NSPopUpButton		*macroButtonEE;          /*" same in pdf window "*/
	IBOutlet NSButton			*autoCompleteButton;
	IBOutlet NSButton           *showFullPathButton; // added by Terada
	NSWindow					*logWindow;
	NSTextView					*logTextView;
	NSScrollView				*logScrollView;
	NSString					*logExtension;

	id			gotopageOutlet;
	id			magnificationOutlet;
	id			previousButton;
	id			nextButton;

	NSConnection    *_completionConnection; //Adam Maxwell
    id               _completionServer; //Adam Maxwell

	NSTextStorage				*_textStorage;
	BOOL		windowIsSplit;
	BOOL		lineNumbersShowing;
	BOOL		invisibleCharactersShowing; // added by Terada
	
	BOOL				isFullScreen;
	TSFullscreenWindow	*fullscreenWindow;
	PDFView				*fullscreenPDFView;

	NSStringEncoding	_encoding;
	NSStringEncoding	_tempencoding;
	DefaultTypesetMode			whichScript;		/*" 100 = pdftex, 101 = gs, 102 = personal script "*/
	NSInteger			whichEngine;		/*" 1 = tex, 2 = latex, 3 = bibtex, 4 = makeindex, 5 = megapost, 6 = context,
													7 = metafont "*/
	TSDocument	*rootDocument;
	BOOL		tagLine;
    BOOL        skipTextWindow;


	BOOL                typesetStart;		/*" YES if tex output "*/
	NSFileHandle        *writeHandle;
	NSFileHandle        *readHandle;
	NSPipe              *inputPipe;
	NSPipe              *outputPipe;
	NSTask              *texTask;
	NSTask              *bibTask;
	NSTask              *indexTask;
	NSTask              *metaFontTask;
	NSTask              *detexTask;
	NSPipe              *detexPipe;
	NSFileHandle        *detexHandle;
	NSTask              *synctexTask;
	NSPipe              *synctexPipe;
	NSFileHandle        *synctexHandle;
    synctex_scanner_t	scanner;


	NSDate		*startDate;
	NSPDFImageRep	*texRep;
	NSData		*previousFontData;	/*" holds font data in case preferences change is cancelled "*/
	BOOL		fileIsTex;
	TSDocumentType			_documentType;
	NSInteger			errorLine[NUMBEROFERRORS];
	NSString	*errorLinePath[NUMBEROFERRORS];
	NSString	*errorText[NUMBEROFERRORS];
	NSInteger			errorNumber;
	NSInteger			whichError;
	DefaultTypesetMode			theScript;		/*" script currently executing; 100, 101, 102 "*/
	
	NSUInteger	colorStart, colorEnd;
	NSDictionary		*regularColorAttribute;
	NSDictionary		*commandColorAttribute;
	NSDictionary		*commentColorAttribute;
	NSDictionary		*markerColorAttribute;
	NSDictionary		*indexColorAttribute;
    
    // for full screen operation
    NSInteger           oldPageStyle;
    NSInteger           oldResizeOption;
    NSInteger           fullscreenPageStyle;
    NSInteger           fullscreenResizeOption;


	NSTimer		*tagTimer;		/*" Timer that repeatedly handles tag updates "*/
	NSUInteger	tagLocation;
	NSUInteger	tagLocationLine;

	BOOL				makeError;
	SEL					tempSEL;
	MySelection			*mSelection;
	BOOL                taskDone;
	NSInteger                 pdfSyncLine;
	id                  syncBox;
	id					indexColorBox;
	BOOL                aggressiveTrash;
	BOOL				willClose;

	BOOL		_externalEditor;
// added by mitsu --(H) Macro menu; macroButton
	BOOL		doAutoComplete;
	BOOL        showFullPath; // added by Terada
	BOOL		autoCompleting; // added by Terada
	BOOL	    contentHighlighting; // added by Terada
	BOOL	    braceHighlighting; // added by Terada
	BOOL		warningGiven;
	BOOL		omitShellEscape;
	BOOL		withLatex;

	NSDate              *_pdfLastModDate;
	NSTimer             *_pdfRefreshTimer;
	BOOL                _pdfRefreshTryAgain;

	BOOL                typesetContinuously;
	NSInteger                 tempEngine;
	BOOL                useTempEngine;
	BOOL                realEngine;
	NSWindow            *callingWindow;
	NSStringEncoding	_badEncoding;
	BOOL                showBadEncodingDialog;
	BOOL				PDFfromKit;
	NSUInteger		pdfCharacterIndex;
	BOOL				textSelectionYellow;
	BOOL				showIndexColor; // this is related to a bug where the source draws after the toolbar is disposed
	BOOL				showSync; // this fixes a bug in which the pdfkit draws a final time and accesses a toolbar button after it is disposed
	BOOL				isLoading;
	BOOL				firstTime;
	NSTimeInterval		colorTime;
	NSString			*spellLanguage;
	BOOL				consoleCleanStart;
	NSString			*statTempFile; // when get statistics for selection, name of temp file where selection is stored.

	NSInteger lastCursorLocation; // added by Terada
	NSInteger lastStringLength; // added by Terada
	BOOL lastInputIsDelete; // added by Terada
	
	//Michael Witten: mfwitten@mit.edu
	NSLineBreakMode		lineBreakMode;
	// end witten
    
// FIX RULER SCROLL
    NSRect lastDocumentVisibleRect;  // added by Terada (for Lion bug)
    NSRect lastDocumentVisibleRect2;  // added by Terada (for Lion bug)
    NSRect lastDocumentVisibleRectConsole; // added by Koch (for Lion bug)
// END FIX RULER SCROLL

// end addition

}
+ (BOOL)autosavesInPlace;
- (void)configureTypesetButton;
- (BOOL)prepareSavePanel:(NSSavePanel *)savePanel;

// FIX RULER SCROLL
- (void) redrawLineNumbers: sender;
// END FIX RULER SCROLL

// forsplit
- (void) splitWindow: sender;
- (void) splitPreviewWindow: sender;
- (void) showHideLineNumbers: sender;
- (void) showHideInvisibleCharacters: sender;// added by Terada
- (void) setTextView: (id)aView;
// endforsplit
- (id) magnificationPanel;
- (id) pagenumberPanel;
- (void) quitMagnificationPanel: sender;
- (void) quitPagenumberPanel: sender;
- (void) okForPanel: sender;  //needed?
- (void) cancelForPanel: sender;  //needed?
- (void) showStatistics: sender;
- (void) updateStatistics: sender;
- (void) doTemplate: sender;
- (void) printSource: sender;
// - (void) okForRequest: sender;
// - (void) okForPrintRequest: sender;
- (void) chooseEncoding: sender;
- (NSStringEncoding) encoding;
- (void) close;
- (void) setProjectFile: sender;
- (void) doLine: sender;
- (void) doTag: sender;
- (void) chooseProgram: sender;
- (void) chooseProgramEE: sender;
- (id) pdfView;
- (id) pdfKitView;
- (void) doCompletion:(NSNotification *)notification;
- (void) doMatrix:(NSNotification *)notification; // Matrix by Jonas
- (void) changeAutoComplete: sender;
- (void) changeShowFullPath: sender; // added by Terada
- (void) fixAutoMenu;
- (void) fixShowFullPathButton; // added by Terada
- (NSString*) fileTitleName; // added by Terada
// - (void) openStyleFile: (id)sender; // added by Terada
- (void) setAutoCompleting:(BOOL)flag; // added by Terada
- (void) fixMacroMenu;
- (void) fixMacroMenuForWindowChange;
- (NSRange) lineRange: (NSInteger)line;
- (void) toLine: (NSInteger)line;
- (void) toLine: (NSInteger) line andSubstring: theString;
- (void) doChooseMethod: sender;
- (void) fixTypesetMenu;
- (void) doError: sender;
- (NSInteger) errorLineFor: (NSInteger)theError;
- (NSString *) errorLinePathFor: (NSInteger)theError;
- (NSString *) errorTextFor: (NSInteger)theError;
- (NSInteger) totalErrors;
- (NSInteger) textViewCountTabs: (NSTextView *) aTextView andSpaces: (NSInteger *) spaces;
- (BOOL)keepBackupFile;
- (void) setupTags;
- (TSDocumentType) documentType;
- (id) pdfWindow;
- (id) pdfKitWindow;
- (id) textWindow;
- (id) textView;
- (id) topView;
- (void)fixUpTabs;
- (BOOL) externalEditor;
- (void) refreshPDFAndBringFront: (BOOL)front;
- (void) refreshTEXT;
- (NSString *)displayName;
- (BOOL) isTexExtension: (NSString *)extension;  //needed?
- (BOOL) isTextExtension: (NSString *)extension; //needed?
- (NSPDFImageRep *) myTeXRep;
- (BOOL)isDocumentEdited;
- (BOOL)fileIsTex; // added by zenitani, Feb 13, 2003
- (void)bringPdfWindowFront;
- (NSWindow *)getCallingWindow;
- (void)setCallingWindow: (NSWindow *)thisWindow;
- (void)setPdfSyncLine:(NSInteger)line;
- (void)showSyncMarks:sender;
- (void) flipShowSync: sender;
- (void)showIndexColor:sender;
- (BOOL)indexColorState;
- (void) flipIndexColorState: sender;
- (void)doPreviewSyncWithFilename:(NSString *)fileName andLine:(NSInteger)line andCharacterIndex:(NSUInteger)idx andTextView:(id)aTextView;
- (BOOL)doNewPreviewSyncWithFilename:(NSString *)fileName andLine:(NSInteger)line andCharacterIndex:(NSUInteger)idx andTextView:(id)aTextView;
- (void)trashAUXFiles: sender;
- (void)trashAUX;
- (void)tryBadEncodingDialog: (NSWindow *)theWindow;
- (BOOL)fromKit;
- (BOOL)revertToContentsOfURL:(NSURL *)absoluteURL ofType:(NSString *)typeName error:(NSError **)outError;
- (void)doBackForward: (id)sender;
- (void)doBack: (id)sender;
- (void)doForward: (id)sender;
- (id) mousemodeMenu;
- (id) mousemodeMatrix;
- (void) setCharacterIndex:(NSUInteger)idx;
- (BOOL) textSelectionYellow;
- (void) setTextSelectionYellow:(BOOL)value;
- (void) saveSourcePosition;
- (void) savePreviewPosition;
- (void) fullscreen: (id)sender;
- (void) endFullScreen;
- (void)displayConsole: (id)sender;
- (void)displayLog: (id)sender;
- (void)resetSpelling;
- (void)closeCurrentEnvironment:(id)sender;
- (void)invalidateCompletionConnection;
// Forward Routines Not Found by Source
- (BOOL)fillLogWindow;
- (void)fillLogWindowIfVisible;
- (MyPDFKitView *)myPdfKitView;
- (MyPDFKitView *)myPdfKitView2;
- (void)enterFullScreen: (NSNotification *)notification;
- (void)exitFullScreen: (NSNotification *)notification;
- (BOOL)skipTextWindow;

// BibDesk Completion
//---------------------------
 - (NSConnection *)completionConnection; //Adam Maxwell
 - (void)setCompletionConnection:(NSConnection *)completionConnection;
 - (id)completionServer; //Adam Maxwell
 - (void)setCompletionServer:(id)completionServer;
 - (void)registerForConnectionDidDieNotification;
//----------------------------

// - (void) printDocumentWithSettings: (NSDictionary :)printSettings showPrintPanel:(BOOL)showPrintPanel delegate:(id)delegate 
// 	didPrintSelector:(SEL)didPrintSelector contextInfo:(void *)contextInfo;
//-----------------------------------------------------------------------------
// Timer methods
//-----------------------------------------------------------------------------
- (void)fixTags:(NSTimer *)timer;
// - (void)fixColor1:(NSTimer *)timer;

//-----------------------------------------------------------------------------
// Extra methods
//-----------------------------------------------------------------------------

// added by mitsu --(J) Typeset command
- (NSInteger)whichEngine;
// end addition

// mitsu 1.29
- (void)showInfo: (id)sender; // mitsu 1.29 (Q)
- (BOOL)isDoAutoCompleteEnabled; // mitsu 1.29 (T4)
- (void)insertSpecial:(NSString *)theString undoKey:(NSString *)key;
- (void)insertSpecialNonStandard:(NSString *)theString undoKey:(NSString *)key;
- (void)registerUndoWithString:(NSString *)oldString location:(NSUInteger)oldLocation
	length: (NSUInteger)newLength key:(NSString *)key;
- (void)undoSpecial:(id)theDictionary;
- (void)doCommentOrIndent: (id)sender;
- (void)doCommentOrIndentForTag: (NSInteger)tag;
- (void)newTag: (id)sender;
- (void)saveDocument: (id)sender;
// end mitsu 1.29

// Michael Witten: mfwitten@mit.edu
- (void)insertNewlinesFromSelectionUsingIndexes: (NSArray*)indexes withActionName: (NSString*)actionName;	//mfwitten@mit.edu 22 June 2005
- (void)removeNewlinesUsingIndexes: (NSArray*)indexes withActionName: (NSString*)actionName;				//mfwitten@mit.edu 22 June 2005
- (void)setLineBreakMode: (id)sender;																		//mfwitten@mit.edu 31 May 2005
- (void)hardWrapSelection: (id)sender;																		//mfwitten@mit.edu 7 June 2005
- (void)removeNewLinesFromSelection: (id)sender;															//mfwitten@mit.edu 22 June 2005
// end witten

//BULLET (H. Neary) (modified by (HS))
- (void) placeComment: (id)sender;
- (void) placeBullet: (id)sender;
- (void)doNextBullet: (id)sender;
- (void)doPreviousBullet: (id)sender;
- (void)doNextBulletAndDelete: (id)sender;
- (void)doPreviousBulletAndDelete: (id)sender;
//end BULLET (H. Neary) (modified by (HS))

//-----------------------------------------------------------------------------
// private API
//-----------------------------------------------------------------------------
- (void)registerForNotifications;
- (void)setDocumentFontFromPreferences:(NSNotification *)notification;
- (void)setConsoleFontFromPreferences:(NSNotification *)notification;
- (void)setupFromPreferencesUsingWindowController:(NSWindowController *)windowController;
- (void) makeMenuFromDirectory: (NSMenu *)menu basePath: (NSString *)basePath action:(SEL)action level:(NSUInteger)level; // added by S. Zenitani
- (void)resetMacroButton:(NSNotification *)notification;

- (NSString *)filterBackslashes:(NSString *)aString;
- (NSStringEncoding)dataEncoding:(NSData *)theData;

@end




@interface TSDocument (JobProcessing)

- (NSDictionary *)environmentForSubTask;

- (void) doUser: (NSInteger)theEngine;

- (void) doTex: sender;
- (void) doTex1: sender;
- (void) doLatex: sender;
- (void) doLatex1: sender;
- (void) doBibtex: sender;
- (void) doMetapost: sender;
- (void) doMetapost1: sender;
- (void) doContext: sender;
- (void) doContext1: sender;
- (void) doIndex: sender;
- (void) doMetaFont: sender;
- (void) doMetaFont1: sender;
- (void) doTexTemp: sender;
- (void) doLatexTemp: sender;
- (void) doBibtexTemp: sender;
- (void) doMetapostTemp: sender;
- (void) doContextTemp: sender;
- (void) doIndexTemp: sender;
- (void) doMetaFontTemp: sender;
- (void) doTypeset: sender;
- (void) doTypesetForScriptContinuously:(BOOL)method;
- (void) doJob:(NSInteger)type withError:(BOOL)error runContinuously:(BOOL)continuous;
- (void) doJobForScript:(NSInteger)type withError:(BOOL)error runContinuously:(BOOL)continuous;
- (void) doTypesetEE: sender;

- (void) saveFinished: (NSDocument *)doc didSave:(BOOL)didSave contextInfo:(void *)contextInfo;
- (BOOL) startTask: (NSTask*) task running: (NSString*) leafname withArgs: (NSMutableArray*) args inDirectoryContaining: (NSString*) sourcePath withEngine: (NSInteger)theEngine;
- (void) completeSaveFinished;

- (void) doTexCommand: sender;
- (void) convertDocument;
- (void) abort:sender;
- (void) sheetDidEnd:(NSWindow *)sheet returnCode:(NSInteger)returnCode contextInfo:(void *)contextInfo;
- (BOOL) getWillClose;
- (void) setWillClose: (BOOL)value;

@end



@interface TSDocument (RootFile)

- (id) rootDocument;

- (BOOL) checkMasterFile:(NSString *)theSource forTask:(NSInteger)task;
- (BOOL) checkRootFile_forTask:(NSInteger)task;
- (void) checkFileLinks:(NSString *)theSource;
- (void) checkFileLinksA;
- (NSString *) readInputArg:(NSString *)fileLine atIndex:(NSUInteger)i
		homePath:(NSString *)home job:(NSString *)jobname;
- (NSString *) decodeFile:(NSString *)relFile homePath:(NSString *)home job:(NSString *)jobname;

@end



@interface TSDocument (SyntaxHighlighting)

- (void)setupColors;

- (void)fixColor:(NSUInteger)from :(NSUInteger)to;
- (void)colorizeAll;
- (void)colorizeVisibleAreaInTextView:(NSTextView *)aTextView;

@end


@interface TSDocument (SyncTeX)

 - (BOOL)doSyncTeXForPage: (NSInteger)pageNumber x: (CGFloat)xPosition y: (CGFloat)yPosition yOriginal: (CGFloat)yOriginalPosition;
 - (BOOL)doPreviewSyncTeXWithFilename:(NSString *)fileName andLine:(NSInteger)line andCharacterIndex:(NSUInteger)idx andTextView:(id)aTextView;
- (void)allocateSyncScanner;


@end

@interface TSDocument (Console)

/*
 - (NSRect)windowWillUseStandardFrame:(NSWindow *)window defaultFrame:(NSRect)defaultFrame;
 - (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize;
*/

@end

