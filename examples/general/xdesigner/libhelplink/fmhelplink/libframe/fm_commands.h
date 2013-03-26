#ifndef FM_COMMANDS_H
#define FM_COMMANDS_H

/*********************************************
 *
 * Keyboard commands and their default keyboard assignments follow.
 *
 * Modifiers for keyboard assignments are:
 * 	^ = Control
 *	~ = Meta
 *	! = Escape
 *	s = Shift
 */

#define NULLINPUT	-1
#define KBD_INPUT	 1

/* start of "gobbled" functions. All function codes between
 * KBD_GBL_START and KBD_GBL_END are gobbled. To gobble means
 * that, if one such function is found in the input stream,
 * then all immediately following such functions are thrown away.
 */
#define	  KBD_GBL_START 	0x100

		/* Cursor (insert point) moving commands */
		/* There are more cursor moving commands defined later */
#define CSR_HOME  		0x100	/* R11 - Top of column  */
#define CSR_UP    		0x101	/* R8,  ^p */
#define CSR_DOWN  		0x102	/* R14, ^n */
#define CSR_RIGHT 		0x103	/* R12, ^f */
#define CSR_LEFT  		0x104	/* R10, ^b */
#define CSR_BOL   		0x105	/* ^a - Beginning of line */
#define CSR_EOL   		0x106	/* ^e - End of line       */
#define CSR_BOW			0x107	/* ~b - Previous word start */
#define CSR_EOW			0x108	/* ~f - Next word end */
#define CSR_BOS     	0x109  	/* ~a - Previous sentence start */
#define CSR_EOS     	0x10A	/* ~e - Next sentence end */
#define CSR_BOP			0x10B	/* ~[ - Previous paragraph start */
#define CSR_EOP			0x10C	/* ~] - Next paragraph end */
#define CSR_TOTR		0x10D	/* UNUSED  RECYCLE THIS VALUE */
#define CSR_BOTR		0x10E	/* sR11 - Bottom of column */
#define CSR_TOP			0x10F	/* ~{ - Beginning of flow */
#define CSR_BOT			0x110	/* ~} - End of flow */

		/* Deletion commands */
		/* There are more deletion commands defined later */
#define	DEL_CHARBWD		0x112	/* Delete, BackSpace, ^h - Delete */
								/* backward one character */
#define DEL_CHARFWD		0x113	/* ^d - Delete forward one character */
#define DEL_BOW			0x114	/* ~Delete, ~BackSpace, ~^h - Delete */
								/* backward to previous word end */
#define DEL_EOW			0x115	/* ~d - Delete forward to next word start */
#define DEL_EOL     	0x116	/* ^k - Delete forward to end of line */
#define DEL_EOS			0x117	/* ~k - Delete forward to next sentence end */
#define DEL_SEL			0x118	/* see DEL_CHARBWD, Clear shortcut */
#define DEL_BOL			0x119	/*  ^u - Delete backward to start of line */

		/* For dialogs */
#define CSR_BOXTOP		0x11A	/* ~R8 - Top of scroll/roll box */
#define CSR_BOXBOT		0x11B	/* ~R14 - Bottom of scroll/roll box */		

		/* Kerning commands */
#define KBD_KERNUP 		0x11A	/* ~R8, ^R8   - Move 1 point up */
#define KBD_KERNDOWN 	0x11B	/* ~R14, ^R14 - Move 1 point down */
#define KBD_KERNLEFT 	0x11C	/* ~R10, ^R10 - Move 1 point left */
#define KBD_KERNRIGHT	0x11D	/* ~R12, ^R12 - Move 1 point right*/
#define KBD_KERNHOME 	0x11E	/* ~R11, ^R11 - Move back to baseline */

#define KBD_KERNUP6     0x121   /* sR8, SHIFT~R8   - Move 6 point up     */
#define KBD_KERNDOWN6   0x122   /* sR14, SHIFT~R14 - Move 6 point down   */
#define KBD_KERNLEFT6   0x123   /* sR10, SHIFT~R10 - Move 6 point left   */
#define KBD_KERNRIGHT6  0x124   /* sR12, SHIFT~R12 - Move 6 point right  */

		/* Cursor (insert point) moving commands */
		/* There are more cursor moving commands defined earlier */
#define CSR_NEXT_BOW	0x140	/* !bw - Next word start */
#define CSR_NEXT_BOS   	0x141  	/* !bs - Next sentence start */
#define CSR_NEXT_BOP	0x142	/* !bp - Next paragraph start */

		/* Deletion commands */
		/* There are more deletion commands defined earlier */
#define DEL_WORD_START	0x160	/* !kb - Delete backward to previous word start */
#define DEL_WORD_END	0x161	/* !kf - Delete forward to next word end */
#define DEL_NEXT_SS		0x162	/* !ks - Delete forward to next sentence start */
#define DEL_BOS			0x163	/* !ka - Delete backward to previous sentence end */

#define	  KBD_GBL_END   	0x1FF

		/* Misc. editing commands */
#define KBD_BACKTAB		0x220	/* sTab - Back tab (as in dialogs) */
#define KBD_SHFTSPACE	0x221	/* sSpace - Shift Space */
#define KBD_FIRSTTAB	0x222	/* ~Tab - First tab (as in dialogs) */

#define KBD_XCHARS      0x224	/* ^t, ~t - transpose characters (eXchange) */

#define KBD_SOFTHYPHEN	0x225	/* !-d, ^- - discretionary hyphen */
#define KBD_DONTHYPHEN  0x226   /* !ns, s~- - suppress hyphenation */
#define KBD_HARDHYPHEN	0x227	/* !-h, ~- - nonbreaking hyphen */

#define KBD_HARDSPACE	0x228	/* ![Space]h, ~[Space] - hard space (not word delimeter) */
#define KBD_HARDRETURN	0x229	/* ~Return - Hard return */

#define KBD_NUMSPACE	0x22A	/* ![Space]1 - number space */
#define KBD_THINSPACE	0x22B	/* ![Space]t - thin space = 1/12 em */
#define KBD_EMSPACE		0x22C	/* ![Space]m - em space = 1 em */
#define KBD_ENSPACE		0x22D	/* ![Space]n - en space = 1/2 em */

#define KBD_OPENLINE	0x22E	/* ^o - Open line (same as Return L10) */

		/* Search and Replace commands */
#define KBD_FPREV		0x230	/* ~^r, !sp - Search backward */
#define KBD_FNEXT		0x231	/* ~^s, !sn, L9 - Search forward */
#define KBD_RONCE		0x232	/* ^% , !ro - Change*/
#define KBD_RGLOBAL		0x233	/*      !rg - Change all*/
#define KBD_RANDF  		0x234	/*      !ra - Replace and find again */
#define KBD_SETSEARCH	0x235   /* 		!ss - Display Set Search dialog */

		/* Highlighting commands */
		/* There are more highlighting commands defined later */
#define HIGH_CHAR       0x240	/* !hc - Highlight next character */
#define HIGH_WORD       0x241	/* !hw - Highlight next word */
#define HIGH_LINE       0x242	/* !hl - Highlight next line */
#define HIGH_SENT       0x243	/* !hs - Highlight next sentence */
#define HIGH_PGF        0x244	/* !hp - Highlight next paragraph */
#define HIGH_SHL        0x245	/* !hb - Shift highlighting left 1 char */
#define HIGH_SHR        0x246	/* !hf - Shift highlighting right 1 char */
#define HIGH_CLEAR		0x247	/* !h0 - Clear Selection */

		/* Misc. control commands, some are also on menus */
#define KBD_ABORT  		0x250	/* ^c  - Abort process like import or RGOLBAL */
#define KBD_CAPTURE		0x251	/*     - Capture portion of screen, not used  */
#define KBD_ECAPTURE	0x256	/* !dc - Capture portion of screen, compressed*/
#define KBD_RECORD 		0x252	/* ^]  - Record keystrokes                    */
#define KBD_GETTRIGGER	0x253	/* ^]  - Get trigger for recorded keystrokes  */

		/* Character attribute commands */
#define TXT_BOLD        0x260	/* !cb, F2 - Set chars to bold */
#define TXT_ITALIC      0x261	/* !ci, F3 - Set chars to italic */
#define TXT_UNDERLINE   0x262	/* !cu, F4 - Set chars to underline */
#define TXT_PLAIN       0x263	/* !cp, F1 - Set chars to plain */
#define TXT_SUPER       0x264	/* !c+ - Set chars to superscript */
#define TXT_SUB         0x265	/* !c- - Set chars to subscript */
#define TXT_NORMAL      0x266	/* !c= - Set chars to normal */
#define TXT_INCSIZE     0x267	/* !c], !+s - Increment text size */
#define TXT_DECSIZE     0x268	/* !c[, !-s - Decrement text size */
#define TXT_SQUEEZE		0x269	/* !cR10  - Squeeze spacing 20% of an em */
#define TXT_SPREAD 		0x26A	/* !cR12  - Spread spacing 20% of an em */
#define TXT_BAM         0x26B	/* !cc - Set to font dialog values, no dialog */
#define TXT_STRIKEOUT	0x26C	/* !cs, F5 - Set chars to strikethrough */
#define TXT_DEFAULT		0x26D	/* !cd - Set chars to default pgf font */
#define TXT_OVERLINE	0x26E	/* !co - Set chars to overline */
#define TXT_CHANGEBAR	0x26F	/* !ch - Set chars to change bar */
#define TXT_KERN		0x270	/* !ck - Set chars to kerned */
#define TXT_OUTLINE		0x271	/* !ct - Set chars to outline */
#define TXT_SHADOW		0x272	/* !ca - Set chars to shadow */
#define TXT_MINICAPS	0x273	/* !cm - Set chars to small caps */

		/* Paragraph attributes and justification commands */
#define PGF_INCLINE     0x280	/* !j+, !+l - Increment line spacing */
#define PGF_DECLINE     0x281	/* !j-, !-l - Decrement line spacing */
#define PGF_CENTER      0x282	/* !jc - Center paragraph */
#define PGF_LEFT        0x283	/* !jl - Left justify paragraph */
#define PGF_RIGHT       0x284	/* !jr - Right justify paragraph */
#define PGF_FULL        0x285	/* !jf - Full justify paragraph */
#define PGF_BAM         0x286	/* !jj - Set to pgf dialog values, no dialog */
#define PGF_LINEFIX		0x287	/* !jx - Fixed line spacing */
#define PGF_LINEFLOAT	0x288	/* !jo - Floating line spacing */
#define PGF_UNIFY		0x289	/* !jU - Make all pgfs with current */
								/* pgf's tag match current pgf's fmt */

		/* Alignment commands */
#define KBD_ALIGN_TOP		0x290	/* !jt - Top align */
#define KBD_ALIGN_MIDDLE	0x291	/* !jm - Top/bottom (middle) align */
#define KBD_ALIGN_BOTTOM	0x292	/* !jb - Bottom align */

		/*  Main window commands, some are also on menus   */
#define KBD_NEW         0x300	/*       !dn */
#define KBD_OPEN        0x301	/* ^x^f, !do */
#define KBD_HELP        0x302	/* ~?,   !dh */
#define KBD_INFO        0x303	/*       !dI */

		/* Book kit file menu commands */
#define KBD_BOOKADDFILE 		0x30A	/* !df */
#define KBD_BOOKEDITDEFINE		0x30B	/* !dd */
#define KBD_BOOKEDITFILELIST	0x30C	/* !de */

		/* File menu commands */
/*		KBD_NEW			defined in main window commands !dn */
/*		KBD_OPEN		defined in main window commands !do */
#define KBD_SAVE        0x310	/* ^x^s, !ds */
#define KBD_SAVEAS      0x311	/* ^x^w, !da */
#define KBD_REVERT		0x312	/*       !dr */
#define KBD_PRINT       0x313	/*       !dp */
#define KBD_IMPORT      0x314	/*       !di */
#define KBD_GENERATE    0x315	/*       !dg */
#define KBD_USEFMTFROM  0x316	/* 		 !du */
#define KBD_KBMACRO		0x317	/* 		 !dk */
/*		KBD_CAPTURE		defined in misc. control commands !dc */
#define KBD_SESSION		0x318	/* !dP */
/*		KBD_QUITWIN		defined in window menu commands !dq */

#define KBD_PAGESETUP 	0x319   /* page setup for Mac */

		/* File menu commands access by shift */
#define KBD_OPENALL		0x31A	/* !dO - Open all */
#define KBD_QUITALL		0x31B	/* !dQ - Quit all */
#define KBD_SAVEALL		0x31C	/* !dS - Save all */
#define KBD_REPEATNEW	0x31D	/* !dN - Repeat last new command */

		/* Edit menu commands */
#define KBD_UNDO        0x320	/*     !eu, L4 */
#define KBD_CUT         0x321	/* ^w, !ex     */
#define KBD_COPY        0x322	/* ~w, !ec     */
#define KBD_PASTE       0x323	/* ^y, !ep	   */
#define KBD_CLEAR       0x324   /*     !eb     */
#define KBD_COPYFONT	0x325	/* 	   !ef - Copy font attr */
#define KBD_COPYPGF		0x326	/* 	   !er - Copy pgf  attr */
#define KBD_SELECTALL   0x327	/*     !ea     */
#define KBD_STUFF       0x328	/* ~y, !i	   */
#define KBD_SEARCH      0x329	/* ^s, !es     */
#define KBD_SPELLING	0x32A	/*	   !el     */
#define KBD_CAPITAL		0x32B	/*     !eC     */

#define KBD_PUT			0x32C	/* L6 -	put on suntools shelf */
#define KBD_GET			0x32D	/* L8 - get from shelf	      */
#define KBD_PUTCUT		0x32E	/* L10 - put on suntools shelf and cut */

#define KBD_ALLCAP		0x33A	/* ~u - convert selected text to cap */
#define KBD_ALLLOWER	0x33B	/* ~l - convert selected text to lower case */
#define KBD_INITCAP		0x33C	/* ~c - convert selected text to initial cap */

		/* Format menu commands */
#define KBD_FONTDESIGN 		0x330	/* !fc     */
#define KBD_PGFDESIGN  		0x331	/* !fp, L3 */
#define KBD_COLPRO      	0x332	/* !fl     */
#define KBD_DOCUMENTPRO	   	0x333	/* !fd     */
#define KBD_CBARPRO	    	0x334	/* !fb     */
#define KBD_FOOTNOTEPRO    	0x335	/* !fn     */
#define KBD_EQUATION        0x336   /* !fe     */

#define KBD_FONTCATALOG 	0x337
#define KBD_PGFCATALOG  	0x338

		/* Page menu commands */
#define KBD_FIRSTPAGE   0x340	/* !pf, ~<, ~F6 */
#define KBD_LASTPAGE    0x341	/* !pl, ~>, ~F7 */
#define KBD_BODYPAGE	0x342	/* !pb */
#define KBD_MASTERPAGE	0x343	/* !pm */
#define KBD_REFPAGE		0x344	/* !pr */
#define KBD_GOTOPAGE    0x345	/* !pg, ^g*/
#define KBD_ADDPAGE     0x346	/* !pa */
#define KBD_DELETEPAGE  0x347	/* !pd */
#define KBD_COLLAYOUT   0x348	/* !pt */ 
#define KBD_CONNECT     0x349	/* !pc */
#define KBD_PAGEBACK 	0x34A	/* !pk */
#define KBD_FREEZE		0x34B   /* !pz */

#define KBD_PREVPAGE    0x34C	/* !pp, ~v, F6 */
#define KBD_NEXTPAGE    0x34D	/* !pn, ^v, F7 */

#define KBD_ROTPAGE_PLUS	0x34E	/* !po */
#define KBD_ROTPAGE_MINUS	0x34F	/* !pO */

#define KBD_SPLIT		0x35A	/* !CS - Split column below IP */
#define KBD_CONNECTCOL	0x35B	/* !CC - Connect columns */
#define KBD_CUTHEAD		0x35C	/* !CH - Cut head */
#define KBD_CURTAIL		0x35D	/* !CT - Cut tail */

		/* Special menu commands */
#define KBD_ANCHOR      0x350	/* !sa */
#define KBD_FOOTNOTE	0x351	/* !sf */
#define KBD_REFERENCE	0x352	/* !sc */
#define KBD_VARIABLE	0x353	/* !sv */
#define KBD_INSET		0x354	/* !si */
#define KBD_MARKERS     0x355	/* !sm */

#define KBD_NEWMARKER	0x356	/* !mk - Insert new marker */

		/* View menu commands */
#define KBD_OPTIONS		0x360	/* !vo */
#define KBD_BORDERS     0x361	/* !vb */
#define KBD_SYMBOLS     0x362	/* !vt */
#define KBD_RULERS     	0x363	/* !vr */
#define KBD_GRID     	0x364	/* !vg */
#define KBD_SEPARATIONS 0x365	/* !vs */

#define KBD_TOGGLEDRAW	0x366	/* !vv - Toggle draw/don't draw preference */

#define KBD_VIEWSEP1    0x36D	/* !v1 */ 
#define KBD_VIEWSEP2    0x36E	/* !v2 */
#define KBD_VIEWSEP3    0x36F	/* !v3 */

		/* Graphics menu commands */
#define KBD_FLIPUD			0x370	/* !gv */
#define KBD_FLIPLR			0x371	/* !gh */
#define KBD_ROT_PLUS		0x372	/* !gt */
#define KBD_SCALE       	0x373	/* !gz */
#define KBD_SMOOTH      	0x374	/* !gs */
#define KBD_UNSMOOTH    	0x375	/* !gm */
#define KBD_RESHAPE     	0x376	/* !gr */
#define KBD_SETSIDES    	0x378	/* !gn */
#define KBD_CONSTRAIN   	0x379
#define KBD_SNAP        	0x37A	/* !gp */
#define KBD_GRAVITY     	0x37B	/* !gy */
#define KBD_KEEPTOOL    	0x37C
#define KBD_FRONT       	0x380	/* !gf */
#define KBD_BACK        	0x381	/* !gb */
#define KBD_GROUP       	0x382	/* !gg */
#define KBD_UNGROUP     	0x383	/* !gu */
#define KBD_ALIGN       	0x384	/* !ga */
#define KBD_DISTRIBUTE  	0x385	/* !gd */
#define KBD_ROT_MINUS		0x386	/* !gT */
#define KBD_OBJPROPS		0x387	/* !go */
#define KBD_PICKOBJPROPS	0x388	/* !gO */

#define KBD_ROTATE				0x389   /* !xx1 */
#define KBD_ROTATE_INTERACTIVE  0x38A   /* !xx2 */

		/* Window menu commands  */
#define KBD_CLOSEWIN    0x390   /* !wc       */
#define KBD_OPENWIN     0x391	/* !wo       */
#define KBD_CLOPWIN     0x392   /* L7 - Close/open toggle */  
#define KBD_MOVEWIN     0x393   /* !wm       */
	/* 0x394 UNUSED */
#define KBD_EXPOSEWIN   0x395   /* !we       */
#define KBD_HIDEWIN     0x396   /* !wh, sL5  */
#define KBD_HISHWIN     0x397	/* L5 - Hide/show toggel */
#define KBD_REFRESHWIN  0x398   /* !wr, ^l   */
#define KBD_QUITWIN     0x399   /* !wq, !dq, ^x^c */

		/* Only used internally to resize document toggling */
		/* between lock and unlock. */
#define KBD_RESIZELOCK		0x39A
#define KBD_RESIZEUNLOCK	0x39B

		/* Only used internally */  
#define KBD_QUIETCLOSEWIN   0x39C

    /* Bring up the Popup Menu (ala right button), in X-Motif port */
#define KBD_POPUP_MENU      0x39D

		/* Tools window tools */
#define KBD_LINETOOL    0x3A0   /* !1l  */
#define KBD_RECTTOOL    0x3A1   /* !1r  */
#define KBD_POLYGTOOL   0x3A2   /* !1pg */
#define KBD_POLYLTOOL   0x3A3   /* !1pl */
#define KBD_ARCTOOL     0x3A4   /* !1a  */
#define KBD_ROUNDRECT   0x3A5   /* !1R  */
#define KBD_OVALTOOL    0x3A6   /* !1e   ("ellipse") */
#define KBD_TEXTLTOOL   0x3A7   /* !1tl */
#define KBD_TEXTRTOOL   0x3A8   /* !1tc */
#define KBD_FREETOOL    0x3A9   /* !1f  */
#define KBD_FRAMETOOL   0x3AA   /* !1m  */
#define KBD_LASTTOOL    0x3AB   /* !11  select last-used tool  */
 
        /* Line width commands */
#define KBD_WIDTH0      0x3AC   /* !0w - Set to thinnest width  */
#define KBD_WIDTH1      0x3AD   /* !9w - Set to thickest width   */
#define KBD_INCWIDTH    0x3AE   /* !+w - Increment line width   */
#define KBD_DECWIDTH    0x3AF   /* !-w - Decrement line width   */
 
        /* Pen pattern commands */
#define KBD_PEN0        0x3B0   /* !0p - Set to "first" pen pat */
#define KBD_PEN1        0x3B1   /* !9p - Set to last pen  pattern*/
#define KBD_INCPEN      0x3B2   /* !+p - Increment pen pattern  */
#define KBD_DECPEN      0x3B3   /* !-p - Decrement pen pattern  */
 
        /* Fill pattern commands */
#define KBD_FILL0       0x3B4   /* !0f - Set to "first" fill pat*/
#define KBD_FILL1       0x3B5   /* !9f - Set to last fill pattern*/
#define KBD_INCFILL     0x3B6   /* !+f - Increment fill pattern */
#define KBD_DECFILL     0x3B7   /* !-f - Decrement fill pattern */
 
        /* This cmds are never issued by keyboard only by graphics palette */
#define KBD_SETFILL      0x3B8
#define KBD_SETPEN       0x3B9
#define KBD_SETWIDTH     0x3BA
#define KBD_SETCAP       0x3BB
#define KBD_SETSEP       0x3BC

		/* Spelling checker commands */
#define KBD_CHECKSEL	0x3C0	/* !ls  check selection		*/
#define KBD_CHECKDOC	0x3C1	/* !le  check entire doc	*/
#define KBD_CORRECT		0x3C2	/* !lcw correct word		*/
#define KBD_ADDUSRDICT	0x3C3	/* !lap add to personal dict	*/
#define KBD_ADDDOCDICT	0x3C4	/* !lad add to document dict	*/
#define KBD_ADDAUTOCORR 0x3C5	/* !lac add to auto corrections */
#define KBD_DELUSRDICT	0x3C6	/* !lxp del from personal dict	*/
#define KBD_DELDOCDICT	0x3C7	/* !lxd del from document dict	*/
#define KBD_CLEARAUTO	0x3C8   /* !lca clear auto corrections  */
#define KBD_CHANGEDICT	0x3C9	/* !lcd change dictionaries	*/
#define KBD_SPELLRESET  0x3CA	/* !lr  reset checked pgfs	*/
#define KBD_CHECKPAGE	0x3CB	/* !lp  check page		*/
#define KBD_SPOPTIONS	0x3CC   /* !lo  spell check options */
#define KBD_HYPHENATE	0x3CD   /* !l-  hyphenate word */
#define KBD_CHECKBATCH  0x3CE   /* !lb  batch spell check */
#define KBD_REFORMATDOC 0x3CF   /* !lR  reformat entire document */

        /* Smart quotes */
#define KBD_SINGLE_QUOTE    0x400   /* '    */
#define KBD_DOUBLE_QUOTE    0x401   /* "    */

		/* Highlighting commands */
		/* There are more highlighting commands defined earlier */
#define HIGH_CHAR_PREV  	0x410	/* !HC - Extend one character to the left */
#define HIGH_WORD_PREV  	0x411	/* !hHW - Select current word, then extend to previous one */
#define HIGH_LINE_PREV  	0x412	/* !hHL - Select current line, then extend to previous one */
#define HIGH_SENT_PREV  	0x413	/* !hHS - Select current sentence, then extend to previous one */
#define HIGH_PGF_PREV   	0x414	/* !hHP - Select current paragraph, then extend to previous one */

#define HIGH_LINE_UP   		0x415	/* !hu - Extend one line up */
#define HIGH_LINE_DOWN   	0x416	/* !hd - Extend one line down*/
#define HIGH_COL_TOP   		0x417	/* !ht - Extend to top of column */
#define HIGH_COL_BOT   		0x418	/* !hm - Extend to bottom of column */
#define HIGH_FLOW_BEG   	0x419	/* !hg - Extend to beginning of flow */
#define HIGH_FLOW_END		0x41A	/* !he - Extend to end of flow */

#define HIGH_CHAR_NEXT  	0x510	/* !hHc - Extend one character to the right */
#define HIGH_WORD_NEXT  	0x511	/* !hHw - Select current word, then extend to next one */
#define HIGH_LINE_NEXT  	0x512	/* !hHl - Select current line, then extend to next one */
#define HIGH_SENT_NEXT  	0x513	/* !hHs - Select current sentence, then extend to next one */
#define HIGH_PGF_NEXT   	0x514	/* !hHp - Select current paragraph, then extend to next one */

#define KBD_VIEWER		0xF00	/* !ZZv	toggle viewer brand 	*/
#define KBD_DSEXIT		0xF01	/* !ZZz	exercise dsexit		*/
#define KBD_MEMFAIL		0xF02	/* !ZZy	exercise mem_fail	*/
#define KBD_SAVEMETA	0xF03	/* !ZZs	toggle mode so Save Text saves meta Chars */ 
#define KBD_MEM_STATS	0xF04	/* !ZZm print busy/free memory totals */
#define KBD_CACHE_STATS	0xF05	/* !ZZc print cache statistics */

#define KBD_NEWVAR		0xF06	/* new variable @ ip */
#define KBD_UPDATEREF	0xF07	/* update ref @ ip */
#define KBD_DEREFREF	0xF08	/* dereference ref @ ip */
#define KBD_HEATREF		0xF09	/* heat reference @ ip */

		/* Document right border commands */
#define KBD_ALLSELECT 	0xF20   /* !1s - smart selection */
#define KBD_OBJSELECT 	0xF21   /* !1o - object selection */
#define KBD_TOOLWIN     0xF22   /* !1w - tools window */
#define KBD_PGFWIN      0xF23   /* !jw - paragraph catalog window */
#define KBD_FONTWIN     0xF24   /* !cw - font catalog window */
#define KBD_RESIZEBOX   0xF25	/* window resize box */
#define KBD_MATHWIN     0xF26   /* !mw math window */
#define KBD_RESIZEBOXM  0xF27	/* window resize box using ctrl-middle mouse*/

		/* Document bottom border commands */
#define KBD_ZOOMIN			0xF30	/* !zi - zoom in */
#define KBD_ZOOMOUT 		0xF31	/* !zo - zoom out */
#define KBD_ZOOM_FIT_PAGE  	0xF32   /* !zp - zoom fit page in window */
#define KBD_ZOOM_FIT_WINDOW 0xF33   /* !zw - zoom fit window to page */
#define KBD_ZOOM			0xF34   /* zoom */
#define KBD_ZOOM100			0xF35	/* !zz - zoom to 100% */

#define KBD_RENAMEPAGE		0xF3A	/* !pN - rename master/reference page */

		/* Font and paragraph catalog selection quick key. */
#define KBD_FONTQUICK	0xF40	/* !qc, F8, ^8 - Char fmt quick key */
#define KBD_PGFQUICK	0xF41	/* !qp, F9, ^9 - Pgf fmt quick key */
#define KBD_VARQUICK	0xF42	/* !qv,     ^0 - Variable quick key */

		/* Dialog commands: set all to As Is and reset. */
#define KBD_NOCHANGEDB	0xF4A	/* ~F8 - Set all items fo As Is in dialog */
#define KBD_RESETDB		0xF4B	/* ~F9 - Reset dialog */

		/* New Equation commands. */
#define KBD_SMEQN       	0xF50	/* !ms - Small equation */
#define KBD_MEDEQN      	0xF51	/* !mm - Medium equation */
#define KBD_LGEQN       	0xF52	/* !ml - Large equation */
#define KBD_PUTINLINE       0xF53	/* !mp - Shrinkwrap */
#define KBD_ANTIPUTINLINE   0xF54	/* !me - Expand (unwrap) */

#define KBD_EVACUATE	0xF60	/* (unbound) Force assertion botch */

#define FM_TERMINATE	0xFFF	/* Quit FrameMaker */

#define KBD_MATH_BASE	0x1000

#define TEXTSEL_QUICK_COPY	0x001
#define TEXTSEL_EXTEND		0x002
#define TEXTSEL_EXTEND_WORD	0x004
#define TEXTSEL_EXTEND_LINE	0x008
#define TEXTSEL_EXTEND_PGF	0x010
#define TEXTSEL_WORD		0x020
#define TEXTSEL_LINE		0x040
#define TEXTSEL_PGF			0x080
#define TEXTSEL_SELECT_ONLY 0x100

/*
These are not function codes but rather
are the flags in the MIF Save Options Mask.
These are used by DocServer.
*/

#define MIF_SAVE_TEXT	0x001
#define MIF_SAVE_TAGS	0x002
#define MIF_SAVE_FMTS	0x004
#define MIF_SAVE_FONTS	0x008
#define MIF_SAVE_MKRS	0x010
#define MIF_SAVE_AFMS	0x020
#define MIF_SAVE_LAYT	0x040
#define MIF_SAVE_MPAGE	0x080
#define MIF_SAVE_FCAT	0x100
#define MIF_SAVE_PCAT	0x200
#define MIF_SAVE_TMPLT	0x400
#define MIF_SAVE_DICT	0x800
#define MIF_SAVE_VARS	0x1000

#endif /* FM_COMMANDS_H */
