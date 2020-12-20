#ifndef	_H_CAVF
#define _H_CAVF

/*
	------------------------------------------------------

	CAVF.h

version 2.0 - dh - 8/22/91
	Macros substituted for bitfields.
version 2.1 - dh - 8/26/91
	BITMAP enum changed to BMAP to avoid Windows collision.
version 2.2 - dh - 8/26/91
	Macros to access and set everything.
version 2.3 - rb - 8/27/91
	Added two OP_ macros to simplify length access.
version 2.4 - dh - 8/27/91
	Fixed bitfield setting macros.
version 2.5 - dh - 9/6/91
	Fixed bitfield setting macros.
version 2.6 - dh - 9/7/91
	Split version field of CAVF header into version_maj and
	version_min, and added associated macros.  Changed enum
	opcode types from simple names (SOUND, DELAY, etc.) to CAVF_Op_xxx.
	Added OPxxx_MEM_SIZE and OPxxx_FILE_SIZE constants to ease in
	determination of structure size on file or on specific platform.
version 2.7 - dh - 9/11/91
	Fixed OPSOUND_FILE_SIZE (thanx to mr belfer), added
	CAVF_VERSION_MAJ and CAVF_VERSION_MIN constants,
	switched order of version_maj and version_min.
version 2.8 - dh - 10/8/91
	Added two filler chars to OpPalette struct to reflect padding on mac.
version 2.9 - dps - 12/2/91
	Changed FILE_SIZEs, all opcodes mult of 4 in length,
	minor version -> 1.
	OpPalette filler1 -> num_colors
version 3.0 - dps - 12/10/91
	Changed major version to 2, minor to 0
version 4.0 - dh - 1/5/92
	added API, CODE versions
	added CAVF ¹ to check versions the right way
	changed opcode to opheader
	added macros for OpPalette
	fixed bug in bits2 of header macros
version 5.0 - dh - 1/31/92
	replaced bg_color field of CAVFheader with bits4, and replaced macros.
	added CAVF_H_INQ_PACKER_VERS and CAVF_H_INQ_PACKER_VERS macros
		(not automatically generated)
version 6.0 - rb- 3 Mar 92
	brought to sparc, altered indention, removed 'typedef' from
		CAVF_Op enumeration and compression type enumeration
	made all arrays use the VARIABLE_LEN macro from CoSAcnfg.h
		what was it there for anyhow?
	replaced Byte with u_char everywhere

	------------------------------------------------------
*/

#include <CoSAtype.h>
#include <U.h>

#define MAX_COLORS			256
#define BIT_DEPTH			8
#define	CAVF_VERSION_MAJ 	2
#define	CAVF_VERSION_MIN 	0

#define	CAVF_API_VERSION	6
#define	CAVFp_CODE_VERSION	0
#define	CAVF_PKG_ID			20


U_PkgVersion  	CAVF_PkgObjectVersion(void);

Err 		CAVF_CheckVersions(U_Location loc, U_PkgApiVersion api_vers);



/* fields for the application id (part of U_AppVersion) in packer_version */
enum {
	CAVF_AppID_PACo,
	CAVF_AppID_PACo_BLAST,
	CAVF_AppID_PACo_BLAST_DEMO,
	CAVF_AppID_QUICK_PICS,
	CAVF_AppID_VISUALIZER
};

typedef void (*ProcVPtr)() ;

typedef struct {
	u_char	red, green, blue;
} Rgb;

/* define RgbBufArray so it doesn't waste one byte per Rgb, 
 * as 'Rgb RgbBufArray[256]' would */

typedef u_char	RgbBufArray[MAX_COLORS*3];


/*	-----------------------	ChunkHeader structure	*/
typedef	std::uint32_t	ChunkHeader;

/* ------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	sound_only : 1;			can be loaded directly into sound buffer
	skippable : 1;			can skip this chunk if falling behind
	combinable : 1;			can combine this chunk w/next
	filler : 5;
	length : 24;
*/

/*	-----------------------	CONSTS FOR ChunkHeader	*/
#define CHUNK_H_SOUND_ONLY_BITS		0x1L
#define CHUNK_H_SOUND_ONLY_SHIFT	31
#define CHUNK_H_SKIPPABLE_BITS		0x1L
#define CHUNK_H_SKIPPABLE_SHIFT		30
#define CHUNK_H_COMBINABLE_BITS		0x1L
#define CHUNK_H_COMBINABLE_SHIFT	29
#define CHUNK_H_FILLER_BITS			0x1fL
#define CHUNK_H_FILLER_SHIFT		24
#define CHUNK_H_LENGTH_BITS			0x00ffffffL
#define CHUNK_H_LENGTH_SHIFT		0

/*	-----------------------	ChunkHeader size constants	*/
#define CHUNK_H_MEM_SIZE	sizeof(ChunkHeader)
#define CHUNK_H_FILE_SIZE	4

/*	-----------------------	ChunkHeader	MACROS	*/
/*	These macros are for INQUIRING fields of the ChunkHeader structure.
	They "return" a std::uint32_t.
	The header argument passed to them is the ChunkHeader structure itself.
*/

#define CHUNK_H_INQ_SOUND_ONLY(header) (((header) >> CHUNK_H_SOUND_ONLY_SHIFT) & CHUNK_H_SOUND_ONLY_BITS)
#define CHUNK_H_INQ_SKIPPABLE(header) (((header) >> CHUNK_H_SKIPPABLE_SHIFT) & CHUNK_H_SKIPPABLE_BITS)
#define CHUNK_H_INQ_COMBINABLE(header) (((header) >> CHUNK_H_COMBINABLE_SHIFT) & CHUNK_H_COMBINABLE_BITS)
#define CHUNK_H_INQ_FILLER(header) (((header) >> CHUNK_H_FILLER_SHIFT) & CHUNK_H_FILLER_BITS)
#define CHUNK_H_INQ_LENGTH(header) (((header) >> CHUNK_H_LENGTH_SHIFT) & CHUNK_H_LENGTH_BITS)

/*	These macros are for SETTING fields of the ChunkHeader structure.
	The header argument passed to them is the ChunkHeader structure itself.
	The value argument must be a std::uint32_t set to the desired value.
*/

#define CHUNK_H_SET_SOUND_ONLY(header, value) ((header) = (((header) & (~(CHUNK_H_SOUND_ONLY_BITS << CHUNK_H_SOUND_ONLY_SHIFT))) | (((value) & CHUNK_H_SOUND_ONLY_BITS) << CHUNK_H_SOUND_ONLY_SHIFT)))
#define CHUNK_H_SET_SKIPPABLE(header, value) ((header) = (((header) & (~(CHUNK_H_SKIPPABLE_BITS << CHUNK_H_SKIPPABLE_SHIFT))) | (((value) & CHUNK_H_SKIPPABLE_BITS) << CHUNK_H_SKIPPABLE_SHIFT)))
#define CHUNK_H_SET_COMBINABLE(header, value) ((header) = (((header) & (~(CHUNK_H_COMBINABLE_BITS << CHUNK_H_COMBINABLE_SHIFT))) | (((value) & CHUNK_H_COMBINABLE_BITS) << CHUNK_H_COMBINABLE_SHIFT)))
#define CHUNK_H_SET_FILLER(header, value) ((header) = (((header) & (~(CHUNK_H_FILLER_BITS << CHUNK_H_FILLER_SHIFT))) | (((value) & CHUNK_H_FILLER_BITS) << CHUNK_H_FILLER_SHIFT)))
#define CHUNK_H_SET_LENGTH(header, value) ((header) = (((header) & (~(CHUNK_H_LENGTH_BITS << CHUNK_H_LENGTH_SHIFT))) | (((value) & CHUNK_H_LENGTH_BITS) << CHUNK_H_LENGTH_SHIFT)))

/*	-----------------------	CAVFheader structure	*/
typedef struct {
	u_char 		version_min;
	u_char 		version_maj;
	int16  		header_size;
	int16  		width, height;
	int16  		default_delay;		/* pos: ticks per frame, neg: frames per second */
	
	u_int16		bits1;

	std::int32_t   		chunk_allocation;	/* size of largest non-sound-only chunk */
	std::int32_t   		coalesced_chunk_allocation;	/* size of largest coalesced chunk, or zero */
	std::int32_t   		sound_allocation;	/* zero means no sounds appear in movie */
	int16  		num_frames;		/* # of BITMAP opcodes */
	int16  		num_chunks;

	u_char 		bits4;			/* used to be background color for full_screen */

	unsigned char	bit_depth;		/* 1,2,4,8... (zero means 8 also) */
	int16  		packer_version;		/* version of the packer that packed this file */

	/* the following fields are only filled in for packer version > b3 */
	/* info only (global) */
	u_int16		bits2;
		
	/* action (global) */
	u_int16		bits3;
		
	int16  		finished_frames;	/* zero means all done, otherwise # before canceled */

	ChunkHeader	chunk_info[VARIABLE_LEN];	/* variable length */
	/* chunk 0 data ... */
	/* chunk 1 data ... */
} CAVFheader, *CAVFheaderPtr;

typedef HANDLE_TYPE(CAVFheader) CAVFheaderH;


/* ------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
u_int16		bits1;   
	user_interrupt : 1;  		stop animation w/click or key
	change_bit_depth : 1;		$$$ change to the proper bit depth if necessary
	blank_full_screen : 1;		$$$ fill unused part of screen with bg_color
	file_loading : 1;   		load whole anim file if possible
	chunk_coalescing : 1;		load multiple chunks if possible
	loop : 1;    			show animation indefinitely till user input
	no_transition_ops : 1;		TRUE if no transitions
	maintain_framerate : 1;		vary delay to maintain frame rate
	pixel_rep_x : 2;      		0 = none, 1 = 2x, 2 = 4x, 3 = 8x
	highlevel_blit : 1;   		use QuickDraw rendering routines
	exact_bitdepth_only : 1;	don't run animation unless in proper bitdepth
	eat_stopping_event : 1; 	should user-interrupt be eaten
	pixel_rep_y : 3;      		0-7, 0 = none, 1 = 2x, 2 = 3x, etc.

u_int16		bits2;   
	interlaced : 1;
	indirect : 1;
	smaller_packing : 1;
	sound_samplerate : 2;
	sound_mins : 5;
	sound_secs : 6;

u_int16		bits3;   
	sound_framerate : 1;	framerate based on sound (not real action)
	wait_at_end : 1;    	wait after last frame
	packer_version_hi : 14;

u_char		bits4;
	filler0 : 13;		unused
	vers_hi_dbg : 1;	dbg bit of packer version hi word
	vbl_sync : 1;		sync to vertical blank
	bg_color : 1;		black / white

*/

/*	-----------------------	CONSTS FOR BITS1 FIELD	*/
#define CAVF_H_USER_INTERRUPT_BITS			0x1
#define CAVF_H_USER_INTERRUPT_SHIFT			15
#define CAVF_H_CHANGE_BIT_DEPTH_BITS		0x1
#define CAVF_H_CHANGE_BIT_DEPTH_SHIFT		14		
#define CAVF_H_BLANK_FULL_SCREEN_BITS		0x1
#define CAVF_H_BLANK_FULL_SCREEN_SHIFT		13
#define CAVF_H_FILE_LOADING_BITS			0x1
#define CAVF_H_FILE_LOADING_SHIFT			12
#define CAVF_H_CHUNK_COALESCING_BITS		0x1
#define CAVF_H_CHUNK_COALESCING_SHIFT		11
#define CAVF_H_LOOP_BITS					0x1
#define CAVF_H_LOOP_SHIFT					10
#define CAVF_H_NO_TRANSITION_OPS_BITS		0x1
#define CAVF_H_NO_TRANSITION_OPS_SHIFT		9
#define CAVF_H_MAINTAIN_FRAMERATE_BITS		0x1
#define CAVF_H_MAINTAIN_FRAMERATE_SHIFT		8
#define CAVF_H_PIXEL_REP_X_BITS				0x3
#define CAVF_H_PIXEL_REP_X_SHIFT			6
#define CAVF_H_HIGHLEVEL_BLIT_BITS			0x1
#define CAVF_H_HIGHLEVEL_BLIT_SHIFT			5
#define CAVF_H_EXACT_BITDEPTH_ONLY_BITS		0x1
#define CAVF_H_EXACT_BITDEPTH_ONLY_SHIFT	4
#define CAVF_H_EAT_STOPPING_EVENT_BITS		0x1
#define CAVF_H_EAT_STOPPING_EVENT_SHIFT		3
#define CAVF_H_PIXEL_REP_Y_BITS				0x7
#define CAVF_H_PIXEL_REP_Y_SHIFT			0

/*	-----------------------	CONSTS FOR BITS2 FIELD	*/
#define CAVF_H_INTERLACED_BITS			0x1
#define CAVF_H_INTERLACED_SHIFT			15
#define CAVF_H_INDIRECT_BITS			0x1
#define CAVF_H_INDIRECT_SHIFT			14
#define CAVF_H_SMALLER_PACKING_BITS		0x1
#define CAVF_H_SMALLER_PACKING_SHIFT	13
#define CAVF_H_SOUND_SAMPLERATE_BITS	0x3
#define CAVF_H_SOUND_SAMPLERATE_SHIFT	11
#define CAVF_H_SOUND_MINS_BITS			0x1f
#define CAVF_H_SOUND_MINS_SHIFT			6
#define CAVF_H_SOUND_SECS_BITS			0x3F
#define CAVF_H_SOUND_SECS_SHIFT			0

/*	-----------------------	CONSTS FOR BITS3 FIELD	*/
#define CAVF_H_SOUND_FRAMERATE_BITS			0x1
#define CAVF_H_SOUND_FRAMERATE_SHIFT		15
#define CAVF_H_WAIT_AT_END_BITS				0x1
#define CAVF_H_WAIT_AT_END_SHIFT			14
#define CAVF_H_PACKER_VERSION_HI_BITS		0x3fff
#define CAVF_H_PACKER_VERSION_HI_SHIFT		0

/*	-----------------------	CONSTS FOR BITS4 FIELD	*/
#define CAVF_H_VERS_HI_DBG_BITS			0x1
#define CAVF_H_VERS_HI_DBG_SHIFT		2
#define CAVF_H_VBL_SYNC_BITS			0x1
#define CAVF_H_VBL_SYNC_SHIFT			1
#define CAVF_H_BG_COLOR_BITS			0x1
#define CAVF_H_BG_COLOR_SHIFT			0


/*	-----------------------	CAVFheader MACROS	*/
/*	These macros are for INQUIRING field of the CAVFheader structure.
	They "return" a u_int16.
	The header argument passed to them is the CAVFheader structure itself.
*/

#define CAVF_H_INQ_USER_INTERRUPT(header) ((((header).bits1) >> CAVF_H_USER_INTERRUPT_SHIFT) & CAVF_H_USER_INTERRUPT_BITS)
#define CAVF_H_INQ_CHANGE_BIT_DEPTH(header) ((((header).bits1) >> CAVF_H_CHANGE_BIT_DEPTH_SHIFT) & CAVF_H_CHANGE_BIT_DEPTH_BITS)
#define CAVF_H_INQ_BLANK_FULL_SCREEN(header) ((((header).bits1) >> CAVF_H_BLANK_FULL_SCREEN_SHIFT) & CAVF_H_BLANK_FULL_SCREEN_BITS)
#define CAVF_H_INQ_FILE_LOADING(header) ((((header).bits1) >> CAVF_H_FILE_LOADING_SHIFT) & CAVF_H_FILE_LOADING_BITS)
#define CAVF_H_INQ_CHUNK_COALESCING(header) ((((header).bits1) >> CAVF_H_CHUNK_COALESCING_SHIFT) & CAVF_H_CHUNK_COALESCING_BITS)
#define CAVF_H_INQ_LOOP(header) ((((header).bits1) >> CAVF_H_LOOP_SHIFT) & CAVF_H_LOOP_BITS)
#define CAVF_H_INQ_NO_TRANSITION_OPS(header) ((((header).bits1) >> CAVF_H_NO_TRANSITION_OPS_SHIFT) & CAVF_H_NO_TRANSITION_OPS_BITS)
#define CAVF_H_INQ_MAINTAIN_FRAMERATE(header) ((((header).bits1) >> CAVF_H_MAINTAIN_FRAMERATE_SHIFT) & CAVF_H_MAINTAIN_FRAMERATE_BITS)
#define CAVF_H_INQ_PIXEL_REP_X(header) ((((header).bits1) >> CAVF_H_PIXEL_REP_X_SHIFT) & CAVF_H_PIXEL_REP_X_BITS)
#define CAVF_H_INQ_HIGHLEVEL_BLIT(header) ((((header).bits1) >> CAVF_H_HIGHLEVEL_BLIT_SHIFT) & CAVF_H_HIGHLEVEL_BLIT_BITS)
#define CAVF_H_INQ_EXACT_BITDEPTH_ONLY(header) ((((header).bits1) >> CAVF_H_EXACT_BITDEPTH_ONLY_SHIFT) & CAVF_H_EXACT_BITDEPTH_ONLY_BITS)
#define CAVF_H_INQ_EAT_STOPPING_EVENT(header) ((((header).bits1) >> CAVF_H_EAT_STOPPING_EVENT_SHIFT) & CAVF_H_EAT_STOPPING_EVENT_BITS)
#define CAVF_H_INQ_PIXEL_REP_Y(header) ((((header).bits1) >> CAVF_H_PIXEL_REP_Y_SHIFT) & CAVF_H_PIXEL_REP_Y_BITS)
#define CAVF_H_INQ_INTERLACED(header) ((((header).bits2) >> CAVF_H_INTERLACED_SHIFT) & CAVF_H_INTERLACED_BITS)
#define CAVF_H_INQ_INDIRECT(header) ((((header).bits2) >> CAVF_H_INDIRECT_SHIFT) & CAVF_H_INDIRECT_BITS)
#define CAVF_H_INQ_SMALLER_PACKING(header) ((((header).bits2) >> CAVF_H_SMALLER_PACKING_SHIFT) & CAVF_H_SMALLER_PACKING_BITS)
#define CAVF_H_INQ_SOUND_SAMPLERATE(header) ((((header).bits2) >> CAVF_H_SOUND_SAMPLERATE_SHIFT) & CAVF_H_SOUND_SAMPLERATE_BITS)
#define CAVF_H_INQ_SOUND_MINS(header) ((((header).bits2) >> CAVF_H_SOUND_MINS_SHIFT) & CAVF_H_SOUND_MINS_BITS)
#define CAVF_H_INQ_SOUND_SECS(header) ((((header).bits2) >> CAVF_H_SOUND_SECS_SHIFT) & CAVF_H_SOUND_SECS_BITS)
#define CAVF_H_INQ_SOUND_FRAMERATE(header) ((((header).bits3) >> CAVF_H_SOUND_FRAMERATE_SHIFT) & CAVF_H_SOUND_FRAMERATE_BITS)
#define CAVF_H_INQ_WAIT_AT_END(header) ((((header).bits3) >> CAVF_H_WAIT_AT_END_SHIFT) & CAVF_H_WAIT_AT_END_BITS)
#define CAVF_H_INQ_PACKER_VERSION_HI(header) ((((header).bits3) >> CAVF_H_PACKER_VERSION_HI_SHIFT) & CAVF_H_PACKER_VERSION_HI_BITS)
#define CAVF_H_INQ_VERS_HI_DBG(header) ((((header).bits4) >> CAVF_H_VERS_HI_DBG_SHIFT) & CAVF_H_VERS_HI_DBG_BITS)
#define CAVF_H_INQ_VBL_SYNC(header) ((((header).bits4) >> CAVF_H_VBL_SYNC_SHIFT) & CAVF_H_VBL_SYNC_BITS)
#define CAVF_H_INQ_BG_COLOR(header) ((((header).bits4) >> CAVF_H_BG_COLOR_SHIFT) & CAVF_H_BG_COLOR_BITS)

/*	See the structure above to determine the return types of these macros.	*/

#define CAVF_H_INQ_version_maj(header) ((header).version_maj)
#define CAVF_H_INQ_version_min(header) ((header).version_min)
#define CAVF_H_INQ_header_size(header) ((header).header_size)
#define CAVF_H_INQ_width(header) ((header).width)
#define CAVF_H_INQ_height(header) ((header).height)
#define CAVF_H_INQ_default_delay(header) ((header).default_delay)
#define CAVF_H_INQ_chunk_allocation(header) ((header).chunk_allocation)
#define CAVF_H_INQ_coalesced_chunk_allocation(header) ((header).coalesced_chunk_allocation)
#define CAVF_H_INQ_sound_allocation(header) ((header).sound_allocation)
#define CAVF_H_INQ_num_frames(header) ((header).num_frames)
#define CAVF_H_INQ_num_chunks(header) ((header).num_chunks)
#define CAVF_H_INQ_bit_depth(header) ((header).bit_depth)
#define CAVF_H_INQ_packer_version(header) ((header).packer_version)
#define CAVF_H_INQ_finished_frames(header) ((header).finished_frames)
#define CAVF_H_INQ_chunk_info(header) ((header).chunk_info)

/*	These macros are for SETTING fields of the CAVFheader structure.
	The header argument passed to them is the CAVFheader structure itself.
	The value argument must be a u_int16 set to the desired value.		*/

#define CAVF_H_SET_USER_INTERRUPT(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_USER_INTERRUPT_BITS << CAVF_H_USER_INTERRUPT_SHIFT))) | (((u_int16) (value) & CAVF_H_USER_INTERRUPT_BITS) << CAVF_H_USER_INTERRUPT_SHIFT)))
#define CAVF_H_SET_CHANGE_BIT_DEPTH(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_CHANGE_BIT_DEPTH_BITS << CAVF_H_CHANGE_BIT_DEPTH_SHIFT))) | (((u_int16) (value) & CAVF_H_CHANGE_BIT_DEPTH_BITS) << CAVF_H_CHANGE_BIT_DEPTH_SHIFT)))
#define CAVF_H_SET_BLANK_FULL_SCREEN(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_BLANK_FULL_SCREEN_BITS << CAVF_H_BLANK_FULL_SCREEN_SHIFT))) | (((u_int16) (value) & CAVF_H_BLANK_FULL_SCREEN_BITS) << CAVF_H_BLANK_FULL_SCREEN_SHIFT)))
#define CAVF_H_SET_FILE_LOADING(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_FILE_LOADING_BITS << CAVF_H_FILE_LOADING_SHIFT))) | (((u_int16) (value) & CAVF_H_FILE_LOADING_BITS) << CAVF_H_FILE_LOADING_SHIFT)))
#define CAVF_H_SET_CHUNK_COALESCING(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_CHUNK_COALESCING_BITS << CAVF_H_CHUNK_COALESCING_SHIFT))) | (((u_int16) (value) & CAVF_H_CHUNK_COALESCING_BITS) << CAVF_H_CHUNK_COALESCING_SHIFT)))
#define CAVF_H_SET_LOOP(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_LOOP_BITS << CAVF_H_LOOP_SHIFT))) | (((u_int16) (value) & CAVF_H_LOOP_BITS) << CAVF_H_LOOP_SHIFT)))
#define CAVF_H_SET_NO_TRANSITION_OPS(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_NO_TRANSITION_OPS_BITS << CAVF_H_NO_TRANSITION_OPS_SHIFT))) | (((u_int16) (value) & CAVF_H_NO_TRANSITION_OPS_BITS) << CAVF_H_NO_TRANSITION_OPS_SHIFT)))
#define CAVF_H_SET_MAINTAIN_FRAMERATE(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_MAINTAIN_FRAMERATE_BITS << CAVF_H_MAINTAIN_FRAMERATE_SHIFT))) | (((u_int16) (value) & CAVF_H_MAINTAIN_FRAMERATE_BITS) << CAVF_H_MAINTAIN_FRAMERATE_SHIFT)))
#define CAVF_H_SET_PIXEL_REP_X(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_PIXEL_REP_X_BITS << CAVF_H_PIXEL_REP_X_SHIFT))) | (((u_int16) (value) & CAVF_H_PIXEL_REP_X_BITS) << CAVF_H_PIXEL_REP_X_SHIFT)))
#define CAVF_H_SET_HIGHLEVEL_BLIT(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_HIGHLEVEL_BLIT_BITS << CAVF_H_HIGHLEVEL_BLIT_SHIFT))) | (((u_int16) (value) & CAVF_H_HIGHLEVEL_BLIT_BITS) << CAVF_H_HIGHLEVEL_BLIT_SHIFT)))
#define CAVF_H_SET_EXACT_BITDEPTH_ONLY(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_EXACT_BITDEPTH_ONLY_BITS << CAVF_H_EXACT_BITDEPTH_ONLY_SHIFT))) | (((u_int16) (value) & CAVF_H_EXACT_BITDEPTH_ONLY_BITS) << CAVF_H_EXACT_BITDEPTH_ONLY_SHIFT)))
#define CAVF_H_SET_EAT_STOPPING_EVENT(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_EAT_STOPPING_EVENT_BITS << CAVF_H_EAT_STOPPING_EVENT_SHIFT))) | (((u_int16) (value) & CAVF_H_EAT_STOPPING_EVENT_BITS) << CAVF_H_EAT_STOPPING_EVENT_SHIFT)))
#define CAVF_H_SET_PIXEL_REP_Y(header, value) ((header).bits1 = (((header).bits1 & (~(CAVF_H_PIXEL_REP_Y_BITS << CAVF_H_PIXEL_REP_Y_SHIFT))) | (((u_int16) (value) & CAVF_H_PIXEL_REP_Y_BITS) << CAVF_H_PIXEL_REP_Y_SHIFT)))
#define CAVF_H_SET_INTERLACED(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_INTERLACED_BITS << CAVF_H_INTERLACED_SHIFT))) | (((u_int16) (value) & CAVF_H_INTERLACED_BITS) << CAVF_H_INTERLACED_SHIFT)))
#define CAVF_H_SET_INDIRECT(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_INDIRECT_BITS << CAVF_H_INDIRECT_SHIFT))) | (((u_int16) (value) & CAVF_H_INDIRECT_BITS) << CAVF_H_INDIRECT_SHIFT)))
#define CAVF_H_SET_SMALLER_PACKING(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_SMALLER_PACKING_BITS << CAVF_H_SMALLER_PACKING_SHIFT))) | (((u_int16) (value) & CAVF_H_SMALLER_PACKING_BITS) << CAVF_H_SMALLER_PACKING_SHIFT)))
#define CAVF_H_SET_SOUND_SAMPLERATE(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_SOUND_SAMPLERATE_BITS << CAVF_H_SOUND_SAMPLERATE_SHIFT))) | (((u_int16) (value) & CAVF_H_SOUND_SAMPLERATE_BITS) << CAVF_H_SOUND_SAMPLERATE_SHIFT)))
#define CAVF_H_SET_SOUND_MINS(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_SOUND_MINS_BITS << CAVF_H_SOUND_MINS_SHIFT))) | (((u_int16) (value) & CAVF_H_SOUND_MINS_BITS) << CAVF_H_SOUND_MINS_SHIFT)))
#define CAVF_H_SET_SOUND_SECS(header, value) ((header).bits2 = (((header).bits2 & (~(CAVF_H_SOUND_SECS_BITS << CAVF_H_SOUND_SECS_SHIFT))) | (((u_int16) (value) & CAVF_H_SOUND_SECS_BITS) << CAVF_H_SOUND_SECS_SHIFT)))
#define CAVF_H_SET_SOUND_FRAMERATE(header, value) ((header).bits3 = (((header).bits3 & (~(CAVF_H_SOUND_FRAMERATE_BITS << CAVF_H_SOUND_FRAMERATE_SHIFT))) | (((u_int16) (value) & CAVF_H_SOUND_FRAMERATE_BITS) << CAVF_H_SOUND_FRAMERATE_SHIFT)))
#define CAVF_H_SET_WAIT_AT_END(header, value) ((header).bits3 = (((header).bits3 & (~(CAVF_H_WAIT_AT_END_BITS << CAVF_H_WAIT_AT_END_SHIFT))) | (((u_int16) (value) & CAVF_H_WAIT_AT_END_BITS) << CAVF_H_WAIT_AT_END_SHIFT)))
#define CAVF_H_SET_PACKER_VERSION_HI(header, value) ((header).bits3 = (((header).bits3 & (~(CAVF_H_PACKER_VERSION_HI_BITS << CAVF_H_PACKER_VERSION_HI_SHIFT))) | (((u_int16) (value) & CAVF_H_PACKER_VERSION_HI_BITS) << CAVF_H_PACKER_VERSION_HI_SHIFT)))
#define CAVF_H_SET_VERS_HI_DBG(header, value) ((header).bits4 = (((header).bits4 & (~(CAVF_H_VERS_HI_DBG_BITS << CAVF_H_VERS_HI_DBG_SHIFT))) | (((u_char) (value) & CAVF_H_VERS_HI_DBG_BITS) << CAVF_H_VERS_HI_DBG_SHIFT)))
#define CAVF_H_SET_VBL_SYNC(header, value) ((header).bits4 = (((header).bits4 & (~(CAVF_H_VBL_SYNC_BITS << CAVF_H_VBL_SYNC_SHIFT))) | (((u_char) (value) & CAVF_H_VBL_SYNC_BITS) << CAVF_H_VBL_SYNC_SHIFT)))
#define CAVF_H_SET_BG_COLOR(header, value) ((header).bits4 = (((header).bits4 & (~(CAVF_H_BG_COLOR_BITS << CAVF_H_BG_COLOR_SHIFT))) | (((u_char) (value) & CAVF_H_BG_COLOR_BITS) << CAVF_H_BG_COLOR_SHIFT)))

/*	See the structure above to determine the value types of these macros.	*/

#define CAVF_H_SET_version_maj(header, value) (((header).version_maj) = (value))
#define CAVF_H_SET_version_min(header, value) (((header).version_min) = (value))
#define CAVF_H_SET_header_size(header, value) (((header).header_size) = (value))
#define CAVF_H_SET_width(header, value) (((header).width) = (value))
#define CAVF_H_SET_height(header, value) (((header).height) = (value))
#define CAVF_H_SET_default_delay(header, value) (((header).default_delay) = (value))
#define CAVF_H_SET_chunk_allocation(header, value) (((header).chunk_allocation) = (value))
#define CAVF_H_SET_coalesced_chunk_allocation(header, value) (((header).coalesced_chunk_allocation) = (value))
#define CAVF_H_SET_sound_allocation(header, value) (((header).sound_allocation) = (value))
#define CAVF_H_SET_num_frames(header, value) (((header).num_frames) = (value))
#define CAVF_H_SET_num_chunks(header, value) (((header).num_chunks) = (value))
#define CAVF_H_SET_bit_depth(header, value) (((header).bit_depth) = (value))
#define CAVF_H_SET_packer_version(header, value) (((header).packer_version) = (value))
#define CAVF_H_SET_finished_frames(header, value) (((header).finished_frames) = (value))


/*	These macros combine the various and sundry fields that make up the
 *	packer version.  The value in the set macro is an std::uint32_t.
 */

#define CAVF_H_INQ_FULL_PACKER_VERS(header)	(((std::uint32_t) ((std::uint32_t) ((std::uint32_t) CAVF_H_INQ_VERS_HI_DBG(header) << 15) | CAVF_H_INQ_PACKER_VERSION_HI(header)) << 16) | CAVF_H_INQ_packer_version(header))
#define CAVF_H_SET_FULL_PACKER_VERS(header, value)	\
	CAVF_H_SET_packer_version((header), ((int16) (value))),										\
	CAVF_H_SET_PACKER_VERSION_HI((header), (((value) >> 16) & CAVF_H_PACKER_VERSION_HI_BITS)),	\
	CAVF_H_SET_VERS_HI_DBG((header), (((value) >> 31) & CAVF_H_VERS_HI_DBG_BITS))

/*	------------------------------------------------------	*/

enum {
	CAVF_Op_NONE, 
	CAVF_Op_TRANSITION, 
	CAVF_Op_PALETTE,
	CAVF_Op_DELAY,
	CAVF_Op_SOUND,
	CAVF_Op_CYCLE,
	CAVF_Op_FILL, 
	CAVF_Op_INPUT, 
	CAVF_Op_BMAP, 
	CAVF_Op_RECTCOPY, 
	CAVF_Op_BREAK,
	CAVF_Op_EO_CHUNK,
	CAVF_Op_NUM_OPCODES
};

/* --- Current Typical Opcode order, per chunk; as written by PACo ---
   PALETTE, TRANSITION, RECTCOPY, SOUND, BMAP, DELAY, INPUT, BREAK, EO_CHUNK
*/

/*	-------------------------------	OpHeader structure	*/
typedef	std::uint32_t	OpHeader;

/* --------------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	type : 8;
   	length : 24;
*/

/*	-------------------------------	OpHeader CONSTS	*/
#define OPHEADER_TYPE_BITS			0xffL
#define OPHEADER_TYPE_SHIFT			24
#define OPHEADER_LENGTH_BITS		0xffffffL
#define OPHEADER_LENGTH_SHIFT		0

/*	-------------------------------	OpHeader MACROS	*/
/*	INQUIRY macros. "Return" a std::uint32_t.								*/

#define OPHEADER_INQ_TYPE(opheader) (((opheader) >> OPHEADER_TYPE_SHIFT) & OPHEADER_TYPE_BITS)
#define OPHEADER_INQ_LENGTH(opheader) (((opheader) >> OPHEADER_LENGTH_SHIFT) & OPHEADER_LENGTH_BITS)

/*	SETTING macros.	*/

#define OPHEADER_SET_TYPE(opheader, value) ((opheader) = (((opheader) & (~(OPHEADER_TYPE_BITS << OPHEADER_TYPE_SHIFT))) | (((std::uint32_t) (value) & OPHEADER_TYPE_BITS) << OPHEADER_TYPE_SHIFT)))
#define OPHEADER_SET_LENGTH(opheader, value) ((opheader) = (((opheader) & (~(OPHEADER_LENGTH_BITS << OPHEADER_LENGTH_SHIFT))) | (((std::uint32_t) (value) & OPHEADER_LENGTH_BITS) << OPHEADER_LENGTH_SHIFT)))

/*	---------------------------------------------------------	*/
/*	USE THESE MACROS TO INQUIRE AND SET THE OPCODE TYPE STRUCTURE
 *	IN ANY OF THE OPCODES BELOW.
 */

#define OP_INQ_OPHEADER(opcode) ((opcode).op_header)
#define OP_SET_OPHEADER(opcode, value) (((opcode).op_header) = (value))

/* shortcuts to combine these and extract length and opcode from actual opcodes */

#define OP_INQ_TYPE(opcode)  		OPHEADER_INQ_TYPE(OP_INQ_OPHEADER(opcode))
#define OP_INQ_LENGTH(opcode)		OPHEADER_INQ_LENGTH(OP_INQ_OPHEADER(opcode))

#define OP_SET_TYPE(opcode, value)  	OPHEADER_SET_TYPE(OP_INQ_OPHEADER(opcode), value)
#define OP_SET_LENGTH(opcode, value)	OPHEADER_SET_LENGTH(OP_INQ_OPHEADER(opcode), value)

/*	------------------------------------------------------------	*/

typedef unsigned char	CustomAtom;	/* type for custom transition stream atoms */

/*** Old-style transition types: these now map directly to custom types when
	packed.  They are left in here for backwards compatibility (the
	player will do the mapping to a custom type if it finds one of these).
***/
enum {
	DIRECT, 	/* unpack directly to the screen (transition NO-OP) */
	INDIRECT,	/* unpack offscreen, but then blit AFAP onto the screen */
	INDIRECT_INTERLACED,/* unpack offscreen, blit AFAP interlaced (hides flumping) */
	WIPE_UP,	/* transfer bits top to bottom, left to right, etc. */
	WIPE_LEFT,
	WIPE_DOWN,
	WIPE_RIGHT,
	PUSH_UP,	/* scroll on the new while scrolling off the old */
	PUSH_LEFT,
	PUSH_DOWN,
	PUSH_RIGHT,
	REVEAL_UP,	/* scroll the original off, revealing the new */
	REVEAL_LEFT,
	REVEAL_DOWN,
	REVEAL_RIGHT,
	COVER_UP,	/* scroll the new on, covering the old */
	COVER_LEFT,
	COVER_DOWN,
	COVER_RIGHT,
	RANDOM_BARS,
	RANDOM_COLUMNS,
	RANDOM_SQUARES,
	DISSOLVE_FAST,	/* do a semi-random fade at the pixel level AFAP */
	DISSOLVE_SLOW,	/* do a dissolve that honors the duration (& can LUT fade too) */
	IRIS_OPEN,	/* reveal circularly from the inside out */
	IRIS_CLOSE,
	WIPE_RECT_OPEN,	/* like iris, but rectangular */
	WIPE_RECT_CLOSE,
	PROGRESSIVE_REFINE,	/* like dart */
	WIPE_HORIZ_OPEN,	/* barn door */
	WIPE_HORIZ_CLOSE,
	WIPE_VERT_OPEN,		/* clam shell */
	WIPE_VERT_CLOSE,
	RANDOM_TRANSITION,	/* any non-AFAP transition */
	TS_CHECKERBOARD,	/* (at some point, all transitions should be prefixed by TS_) */
	TS_VENETIANBLINDS,
	TS_STAIR4LEFT_LEADTOP,
	TS_STAIR5LEFT_LEADTOP,
	
	/* add new transitions here, and change the TransTable */
	
	NUM_TRANSITIONS,	/* must be last (but before TRANS_CUSTOM) */
	TRANS_CUSTOM = 255
};
typedef unsigned char TransType;


#define TICKS_PER_DURATION_UNIT		6
#define MAX_STANDARD_TRANS			51
/* maximum size (# of CustomAtoms) of a standard transition,
 *  i.e. one in the TransTable */

/*	-------------------------------	OpTransition structure	*/
typedef struct {
	OpHeader	op_header;		/* TRANSITION */
	TransType	trans;
	u_char		bits1;
	u_char		duration;		/* in 10ths of a second */
	u_char		chunk;			/* chunk size */
	u_char		part;			/* part size */
	CustomAtom	custom[MAX_STANDARD_TRANS];
/* custom is used only if trans == TRANS_CUSTOM,
 * NOTE: actually variable length in file
 */
} OpTransition;

/*	---------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	changing_area_only : 1;
	persist : 1;				not once-only
	filler0 : 6;
*/

/*	---------------------------------------	OpTransition CONSTS	*/
#define OPTRANS_CHANGING_AREA_ONLY_BITS			0x1
#define OPTRANS_CHANGING_AREA_ONLY_SHIFT		7
#define OPTRANS_PERSIST_BITS					0x1
#define OPTRANS_PERSIST_SHIFT					6
#define OPTRANS_FILLER_ZERO_BITS				0x3f
#define OPTRANS_FILLER_ZERO_SHIFT				0

/*	---------------------------------------	OpTransition size constants	*/
#define OPTRANS_MEM_SIZE	sizeof(OpTransition)
#define OPTRANS_FILE_SIZE	9

/*	---------------------------------------	OpTransition MACROS	*/
/*	INQUIRY macros. "Return" a u_char. */

#define OPTRANS_INQ_CHANGING_AREA_ONLY(optrans) ((((optrans).bits1) >> OPTRANS_CHANGING_AREA_ONLY_SHIFT) & OPTRANS_CHANGING_AREA_ONLY_BITS)
#define OPTRANS_INQ_PERSIST(optrans) ((((optrans).bits1) >> OPTRANS_PERSIST_SHIFT) & OPTRANS_PERSIST_BITS)
#define OPTRANS_INQ_FILLER_ZERO(optrans) ((((optrans).bits1) >> OPTRANS_FILLER_ZERO_SHIFT) & OPTRANS_FILLER_ZERO_BITS)

/*	See the structure above to determine the return types of these macros.	*/

#define OPTRANS_INQ_trans(optrans) ((optrans).trans)
#define OPTRANS_INQ_duration(optrans) ((optrans).duration)
#define OPTRANS_INQ_chunk(optrans) ((optrans).chunk)
#define OPTRANS_INQ_part(optrans) ((optrans).part)
#define OPTRANS_INQ_custom(optrans) ((optrans).custom)

/*	SETTING macros. The value argument must be a u_char.	*/

#define OPTRANS_SET_CHANGING_AREA_ONLY(optrans, value) ((optrans).bits1 = (((optrans).bits1 & (~(OPTRANS_CHANGING_AREA_ONLY_BITS << OPTRANS_CHANGING_AREA_ONLY_SHIFT))) | (((u_char) (value) & OPTRANS_CHANGING_AREA_ONLY_BITS) << OPTRANS_CHANGING_AREA_ONLY_SHIFT)))
#define OPTRANS_SET_PERSIST(optrans, value) ((optrans).bits1 = (((optrans).bits1 & (~(OPTRANS_PERSIST_BITS << OPTRANS_PERSIST_SHIFT))) | (((u_char) (value) & OPTRANS_PERSIST_BITS) << OPTRANS_PERSIST_SHIFT)))
#define OPTRANS_SET_FILLER_ZERO(optrans, value) ((optrans).bits1 = (((optrans).bits1 & (~(OPTRANS_FILLER_ZERO_BITS << OPTRANS_FILLER_ZERO_SHIFT))) | (((u_char) (value) & OPTRANS_FILLER_ZERO_BITS) << OPTRANS_FILLER_ZERO_SHIFT)))

/*	See the structure above to determine the value types of these macros.	*/

#define OPTRANS_SET_trans(optrans, value) (((optrans).trans) = (value))
#define OPTRANS_SET_duration(optrans, value) (((optrans).duration) = (value))
#define OPTRANS_SET_chunk(optrans, value) (((optrans).chunk) = (value))
#define OPTRANS_SET_part(optrans, value) (((optrans).part) = (value))
#define OPTRANS_SET_custom(optrans, value) (((optrans).custom) = (value))

/*	---------------------------------------------------------------	*/

/* ptype bits */
enum {
	P_GIVEN_LUT,		/* lut data follows */
	P_SYS_LUT,   		/* use system lut */
	P_SOLID_LUT 		/* use one-color lut */
};

/* when bits */
enum {
	P_NOW,         		/* fade lut immediately */
	P_WITH_TRANS, 		/* fade lut during the next transition */
	P_AFTER_TRANS,		/* fade lut after the next BITMAP appears */
	P_OVER_TIME,  		/* fade lut one step per frame, starting now */
	P_JUST_BEFORE_TRANS	/* the new preferred way instead of P_NOW */
};

/* note about LUT fades over time: the first change occurs immediately */

/*	---------------------------------------	OpPalette structure	*/
typedef struct {
	OpHeader	op_header;		/* PALETTE */
	u_char		bits1;
	u_char		time;			/* time for transition - 0 means immediate */
	u_char		solid_r;
	u_char		solid_g;
	u_char		solid_b;
	char		filler0;
	char		filler;
	char		num_colors;		/* 0 means old-style 256 colors, else BM_CompactLut follows */
	Rgb 		lut_data[VARIABLE_LEN];		/* LUT data, for non-system LUT */
} OpPalette;

/*	---------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	ptype : 3;			Palette transition
	when : 3;			when & how to do the fade
	filler0 : 2;
*/
/*	-------------------------------	OpPalette CONSTS	*/
#define OPPALETTE_PTYPE_BITS			0x7
#define OPPALETTE_PTYPE_SHIFT			5
#define OPPALETTE_WHEN_BITS				0x7
#define OPPALETTE_WHEN_SHIFT			2
#define OPPALETTE_BIT_FILLER_ZERO_BITS	0x3
#define OPPALETTE_BIT_FILLER_ZERO_SHIFT	0

/*	-------------------------------	OpPalette size constants	*/
#define OPPALETTE_MEM_SIZE	sizeof(OpPalette)
#define OPPALETTE_FILE_SIZE	12

/*	-------------------------------	OpPalette MACROS	*/
/*	INQUIRY macros. "Return" a u_char. */

#define OPPALETTE_INQ_PTYPE(oppalette) ((((oppalette).bits1) >> OPPALETTE_PTYPE_SHIFT) & OPPALETTE_PTYPE_BITS)
#define OPPALETTE_INQ_WHEN(oppalette) ((((oppalette).bits1) >> OPPALETTE_WHEN_SHIFT) & OPPALETTE_WHEN_BITS)
#define OPPALETTE_INQ_BIT_FILLER_ZERO(oppalette) ((((oppalette).bits1) >> OPPALETTE_BIT_FILLER_ZERO_SHIFT) & OPPALETTE_BIT_FILLER_ZERO_BITS)

/*	See the structure above to determine the return types of these macros.	*/

#define OPPALETTE_INQ_time(oppalette) ((oppalette).time)
#define OPPALETTE_INQ_solid_r(oppalette) ((oppalette).solid_r)
#define OPPALETTE_INQ_solid_g(oppalette) ((oppalette).solid_g)
#define OPPALETTE_INQ_solid_b(oppalette) ((oppalette).solid_b)
#define OPPALETTE_INQ_filler0(oppalette) ((oppalette).filler0)
#define OPPALETTE_INQ_filler(oppalette) ((oppalette).filler)
#define OPPALETTE_INQ_num_colors(oppalette) ((oppalette).num_colors)
#define OPPALETTE_INQ_lut_data(oppalette) ((oppalette).lut_data)

/*	SETTING macros. The value argument must be a u_char.	*/

#define OPPALETTE_SET_PTYPE(oppalette, value) ((oppalette).bits1 = (((oppalette).bits1 & (~(OPPALETTE_PTYPE_BITS << OPPALETTE_PTYPE_SHIFT))) | (((u_char) (value) & OPPALETTE_PTYPE_BITS) << OPPALETTE_PTYPE_SHIFT)))
#define OPPALETTE_SET_WHEN(oppalette, value) ((oppalette).bits1 = (((oppalette).bits1 & (~(OPPALETTE_WHEN_BITS << OPPALETTE_WHEN_SHIFT))) | (((u_char) (value) & OPPALETTE_WHEN_BITS) << OPPALETTE_WHEN_SHIFT)))
#define OPPALETTE_SET_BIT_FILLER_ZERO(oppalette, value) ((oppalette).bits1 = (((oppalette).bits1 & (~(OPPALETTE_BIT_FILLER_ZERO_BITS << OPPALETTE_BIT_FILLER_ZERO_SHIFT))) | (((u_char) (value) & OPPALETTE_BIT_FILLER_ZERO_BITS) << OPPALETTE_BIT_FILLER_ZERO_SHIFT)))

/*	See the structure above to determine the value types of these macros.	*/

#define OPPALETTE_SET_time(oppalette, value) (((oppalette).time) = (value))
#define OPPALETTE_SET_solid_r(oppalette, value) (((oppalette).solid_r) = (value))
#define OPPALETTE_SET_solid_g(oppalette, value) (((oppalette).solid_g) = (value))
#define OPPALETTE_SET_solid_b(oppalette, value) (((oppalette).solid_b) = (value))
#define OPPALETTE_SET_filler0(oppalette, value) (((oppalette).filler0) = (value))
#define OPPALETTE_SET_filler(oppalette, value) (((oppalette).filler) = (value))
#define OPPALETTE_SET_num_colors(oppalette, value) (((oppalette).num_colors) = (value))

/*	---------------------------------------	OpDelay structure	*/
typedef struct {
	OpHeader		op_header;			/* DELAY */
	u_int16			bits1;
	int16			filler1;
} OpDelay;

/*	-------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	persist : 1;    	use this delay until next DELAY opcode
	reset_timer : 1;	if true, g->prev_frame_time is set to last_timestamp
	maintain_framerate : 1; if FALSE, effectively a continuous reset_timer
	frames_per_sec : 1;     units: 0 = ticks per frame, 1 = frames per sec
	rate : 12;   		x ticks per frame, or x frames per sec
*/
/* note: reset_timer is ignored (effectively always on)
 * if header->maintain_framerate is false
 */

/*	---------------------------------------	OpDelay CONSTS	*/
#define OPDELAY_PERSIST_BITS				0x1
#define OPDELAY_PERSIST_SHIFT				15
#define OPDELAY_RESET_TIMER_BITS			0x1
#define OPDELAY_RESET_TIMER_SHIFT			14
#define OPDELAY_MAINTAIN_FRAMERATE_BITS		0x1
#define OPDELAY_MAINTAIN_FRAMERATE_SHIFT	13
#define OPDELAY_FRAMES_PER_SEC_BITS			0x1
#define OPDELAY_FRAMES_PER_SEC_SHIFT		12
#define OPDELAY_RATE_BITS					0xfff
#define OPDELAY_RATE_SHIFT					0

/*	---------------------------------------	OpDelay size constants	*/
#define OPDELAY_MEM_SIZE	sizeof(OpDelay)
#define OPDELAY_FILE_SIZE	8

/*	---------------------------------------	OpDelay MACROS	*/
/*	INQUIRY macros. "Return" a u_int16.	*/

#define OPDELAY_INQ_PERSIST(opdelay) ((((opdelay).bits1) >> OPDELAY_PERSIST_SHIFT) & OPDELAY_PERSIST_BITS)
#define OPDELAY_INQ_RESET_TIMER(opdelay) ((((opdelay).bits1) >> OPDELAY_RESET_TIMER_SHIFT) & OPDELAY_RESET_TIMER_BITS)
#define OPDELAY_INQ_MAINTAIN_FRAMERATE(opdelay) ((((opdelay).bits1) >> OPDELAY_MAINTAIN_FRAMERATE_SHIFT) & OPDELAY_MAINTAIN_FRAMERATE_BITS)
#define OPDELAY_INQ_FRAMES_PER_SEC(opdelay) ((((opdelay).bits1) >> OPDELAY_FRAMES_PER_SEC_SHIFT) & OPDELAY_FRAMES_PER_SEC_BITS)
#define OPDELAY_INQ_RATE(opdelay) ((((opdelay).bits1) >> OPDELAY_RATE_SHIFT) & OPDELAY_RATE_BITS)

/*	SETTING macros. The value argument must be a u_int16.			*/

#define OPDELAY_SET_PERSIST(opdelay, value) ((opdelay).bits1 = (((opdelay).bits1 & (~(OPDELAY_PERSIST_BITS << OPDELAY_PERSIST_SHIFT))) | (((u_int16) (value) & OPDELAY_PERSIST_BITS) << OPDELAY_PERSIST_SHIFT)))
#define OPDELAY_SET_RESET_TIMER(opdelay, value) ((opdelay).bits1 = (((opdelay).bits1 & (~(OPDELAY_RESET_TIMER_BITS << OPDELAY_RESET_TIMER_SHIFT))) | (((u_int16) (value) & OPDELAY_RESET_TIMER_BITS) << OPDELAY_RESET_TIMER_SHIFT)))
#define OPDELAY_SET_MAINTAIN_FRAMERATE(opdelay, value) ((opdelay).bits1 = (((opdelay).bits1 & (~(OPDELAY_MAINTAIN_FRAMERATE_BITS << OPDELAY_MAINTAIN_FRAMERATE_SHIFT))) | (((u_int16) (value) & OPDELAY_MAINTAIN_FRAMERATE_BITS) << OPDELAY_MAINTAIN_FRAMERATE_SHIFT)))
#define OPDELAY_SET_FRAMES_PER_SEC(opdelay, value) ((opdelay).bits1 = (((opdelay).bits1 & (~(OPDELAY_FRAMES_PER_SEC_BITS << OPDELAY_FRAMES_PER_SEC_SHIFT))) | (((u_int16) (value) & OPDELAY_FRAMES_PER_SEC_BITS) << OPDELAY_FRAMES_PER_SEC_SHIFT)))
#define OPDELAY_SET_RATE(opdelay, value) ((opdelay).bits1 = (((opdelay).bits1 & (~(OPDELAY_RATE_BITS << OPDELAY_RATE_SHIFT))) | (((u_int16) (value) & OPDELAY_RATE_BITS) << OPDELAY_RATE_SHIFT)))

/*	-----------------------------------------------------------	*/

enum {
	RATE_5,
	RATE_7,
	RATE_11,
	RATE_22
	/* others reserved (8 total) */
};

/*	--------------------------------------	OpSound structure	*/

typedef struct {
	OpHeader		op_header;		/* SOUND */
	u_int16			bits1;
	int16			defer_till_frame;	/* don't queue until frame xx, or zero for none */
	char			data[VARIABLE_LEN];
} OpSound;

/*	note: it is legal to have zero-length data, so as to allow a 
	stop-sound effect (using flush)		*/

/*	---------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	flush : 1;      	flush all pending sounds--this one is important
	wait_start : 1; 	don't display next frame until this sound starts
	wait_finish : 1;	don't display next frame until this sound finishes
	rate : 3;       	sample rate
	no_wave_data : 1;	no sound information, used for flush or wait_finish
	filler0 : 9;
*/
/*	---------------------------------------	OpSound CONSTS	*/
#define OPSOUND_FLUSH_BITS				0x1
#define OPSOUND_FLUSH_SHIFT				15
#define OPSOUND_WAIT_START_BITS			0x1
#define OPSOUND_WAIT_START_SHIFT		14
#define OPSOUND_WAIT_FINISH_BITS		0x1
#define OPSOUND_WAIT_FINISH_SHIFT		13
#define OPSOUND_RATE_BITS				0x7
#define OPSOUND_RATE_SHIFT				10
#define OPSOUND_NO_WAVE_DATA_BITS		0x1
#define OPSOUND_NO_WAVE_DATA_SHIFT		9
#define OPSOUND_FILLER_ZERO_BITS		0x1ff
#define OPSOUND_FILLER_ZERO_SHIFT		0

/*	---------------------------------------	OpSound size constants	*/
#define OPSOUND_MEM_SIZE	sizeof(OpSound)
#define OPSOUND_FILE_SIZE	8

/*	---------------------------------------	OpSound MACROS	*/
/*	INQUIRY macros. "Return" a u_int16.	*/

#define OPSOUND_INQ_FLUSH(opsound) ((((opsound).bits1) >> OPSOUND_FLUSH_SHIFT) & OPSOUND_FLUSH_BITS)
#define OPSOUND_INQ_WAIT_START(opsound) ((((opsound).bits1) >> OPSOUND_WAIT_START_SHIFT) & OPSOUND_WAIT_START_BITS)
#define OPSOUND_INQ_WAIT_FINISH(opsound) ((((opsound).bits1) >> OPSOUND_WAIT_FINISH_SHIFT) & OPSOUND_WAIT_FINISH_BITS)
#define OPSOUND_INQ_RATE(opsound) ((((opsound).bits1) >> OPSOUND_RATE_SHIFT) & OPSOUND_RATE_BITS)
#define OPSOUND_INQ_NO_WAVE_DATA(opsound) ((((opsound).bits1) >> OPSOUND_NO_WAVE_DATA_SHIFT) & OPSOUND_NO_WAVE_DATA_BITS)
#define OPSOUND_INQ_FILLER_ZERO(opsound) ((((opsound).bits1) >> OPSOUND_FILLER_ZERO_SHIFT) & OPSOUND_FILLER_ZERO_BITS)

/*	See the structure above to determine the return types of these macros.	*/

#define OPSOUND_INQ_defer_till_frame(opsound) ((opsound).defer_till_frame)
#define OPSOUND_INQ_data(opsound) ((opsound).data)

/*	SETTING macros. The value argument must be a u_int16.	*/

#define OPSOUND_SET_FLUSH(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_FLUSH_BITS << OPSOUND_FLUSH_SHIFT))) | (((u_int16) (value) & OPSOUND_FLUSH_BITS) << OPSOUND_FLUSH_SHIFT)))
#define OPSOUND_SET_WAIT_START(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_WAIT_START_BITS << OPSOUND_WAIT_START_SHIFT))) | (((u_int16) (value) & OPSOUND_WAIT_START_BITS) << OPSOUND_WAIT_START_SHIFT)))
#define OPSOUND_SET_WAIT_FINISH(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_WAIT_FINISH_BITS << OPSOUND_WAIT_FINISH_SHIFT))) | (((u_int16) (value) & OPSOUND_WAIT_FINISH_BITS) << OPSOUND_WAIT_FINISH_SHIFT)))
#define OPSOUND_SET_RATE(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_RATE_BITS << OPSOUND_RATE_SHIFT))) | (((u_int16) (value) & OPSOUND_RATE_BITS) << OPSOUND_RATE_SHIFT)))
#define OPSOUND_SET_NO_WAVE_DATA(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_NO_WAVE_DATA_BITS << OPSOUND_NO_WAVE_DATA_SHIFT))) | (((u_int16) (value) & OPSOUND_NO_WAVE_DATA_BITS) << OPSOUND_NO_WAVE_DATA_SHIFT)))
#define OPSOUND_SET_FILLER_ZERO(opsound, value) ((opsound).bits1 = (((opsound).bits1 & (~(OPSOUND_FILLER_ZERO_BITS << OPSOUND_FILLER_ZERO_SHIFT))) | (((u_int16) (value) & OPSOUND_FILLER_ZERO_BITS) << OPSOUND_FILLER_ZERO_SHIFT)))

/*	See the structure above to determine the value types of these macros.	*/

#define OPSOUND_SET_defer_till_frame(opsound, value) (((opsound).defer_till_frame) = (value))

/*	--------------------------------------------------------------	*/

typedef struct {
	u_char	start;			/* entry to cycle (zero-based) */
	u_char	count;			/* number total (sequential) */
	u_char	ticks_per_change;	/* do one change every n ticks */
} CycGroup;


/*	---------------------------------------	OpCycle structure	*/
typedef struct {
	OpHeader	op_header;		/* CYCLE */
	int16		duration;
	/* positive: duration in ticks, 0 means forever,
	   negative is a change-count */
	Boolean		user_interruptable;	/* click/keydown interrupt? */
	Boolean		eat_event;		/* eat the user's event? */
	int16		num_groups;
	int16		filler1;
	CycGroup	groups[VARIABLE_LEN];
} OpCycle;

/*	---------------------------------------	OpCycle size constants	*/
#define OPCYCLE_MEM_SIZE	sizeof(OpCycle)
#define OPCYCLE_FILE_SIZE	12

/*	---------------------------------------	OpCycle MACROS	*/
/*	See the structure above to determine the return types of these macros.	*/

#define OPCYCLE_INQ_duration(opcycle) ((opcycle).duration)
#define OPCYCLE_INQ_user_interruptable(opcycle) ((opcycle).user_interruptable)
#define OPCYCLE_INQ_eat_event(opcycle) ((opcycle).eat_event)
#define OPCYCLE_INQ_num_groups(opcycle) ((opcycle).num_groups)
#define OPCYCLE_INQ_groups(opcycle) ((opcycle).groups)

/*	See the structure above to determine the value types of these macros.	*/

#define OPCYCLE_SET_duration(opcycle, value) (((opcycle).duration) = (value))
#define OPCYCLE_SET_user_interruptable(opcycle, value) (((opcycle).user_interruptable) = (value))
#define OPCYCLE_SET_eat_event(opcycle, value) (((opcycle).eat_event) = (value))
#define OPCYCLE_SET_num_groups(opcycle, value) (((opcycle).num_groups) = (value))

/*	---------------------------------------	OpFill structure	*/
typedef struct {
	OpHeader		op_header;			/* FILL */
	union {
		u_char		index;
		Rgb 		col;
	} u;
} OpFill;

/*	---------------------------------------	OpInput structure	*/
typedef struct {
	OpHeader		op_header;			/* INPUT */
	u_int16			bits1;
	int16			filler1;
} OpInput;

/*	-----------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	keypress : 1;
	mouseclick : 1;
	eat_event : 1;
	show_cursor : 1;
	filler0 : 12;
*/
/*	---------------------------------------------	OpInput CONSTS	*/
#define OPINPUT_KEYPRESS_BITS			0x1
#define OPINPUT_KEYPRESS_SHIFT			15
#define OPINPUT_MOUSECLICK_BITS			0x1
#define OPINPUT_MOUSECLICK_SHIFT		14
#define OPINPUT_EAT_EVENT_BITS			0x1
#define OPINPUT_EAT_EVENT_SHIFT			13
#define OPINPUT_SHOW_CURSOR_BITS		0x1
#define OPINPUT_SHOW_CURSOR_SHIFT		12
#define OPINPUT_FILLER_ZERO_BITS		0xfff
#define OPINPUT_FILLER_ZERO_SHIFT		0

/*	--------------------------------------	OpInput size constants	*/
#define OPINPUT_MEM_SIZE	sizeof(OpInput)
#define OPINPUT_FILE_SIZE	8

/*	---------------------------------------------	OpInput MACROS	*/
/*	INQUIRY macros. "Return" a u_int16.	*/

#define OPINPUT_INQ_KEYPRESS(opinput) ((((opinput).bits1) >> OPINPUT_KEYPRESS_SHIFT) & OPINPUT_KEYPRESS_BITS)
#define OPINPUT_INQ_MOUSECLICK(opinput) ((((opinput).bits1) >> OPINPUT_MOUSECLICK_SHIFT) & OPINPUT_MOUSECLICK_BITS)
#define OPINPUT_INQ_EAT_EVENT(opinput) ((((opinput).bits1) >> OPINPUT_EAT_EVENT_SHIFT) & OPINPUT_EAT_EVENT_BITS)
#define OPINPUT_INQ_SHOW_CURSOR(opinput) ((((opinput).bits1) >> OPINPUT_SHOW_CURSOR_SHIFT) & OPINPUT_SHOW_CURSOR_BITS)
#define OPINPUT_INQ_FILLER_ZERO(opinput) ((((opinput).bits1) >> OPINPUT_FILLER_ZERO_SHIFT) & OPINPUT_FILLER_ZERO_BITS)

/*	SETTING macros. The value argument must be a u_int16.	*/

#define OPINPUT_SET_KEYPRESS(opinput, value) ((opinput).bits1 = (((opinput).bits1 & (~(OPINPUT_KEYPRESS_BITS << OPINPUT_KEYPRESS_SHIFT))) | (((u_int16) (value) & OPINPUT_KEYPRESS_BITS) << OPINPUT_KEYPRESS_SHIFT)))
#define OPINPUT_SET_MOUSECLICK(opinput, value) ((opinput).bits1 = (((opinput).bits1 & (~(OPINPUT_MOUSECLICK_BITS << OPINPUT_MOUSECLICK_SHIFT))) | (((u_int16) (value) & OPINPUT_MOUSECLICK_BITS) << OPINPUT_MOUSECLICK_SHIFT)))
#define OPINPUT_SET_EAT_EVENT(opinput, value) ((opinput).bits1 = (((opinput).bits1 & (~(OPINPUT_EAT_EVENT_BITS << OPINPUT_EAT_EVENT_SHIFT))) | (((u_int16) (value) & OPINPUT_EAT_EVENT_BITS) << OPINPUT_EAT_EVENT_SHIFT)))
#define OPINPUT_SET_SHOW_CURSOR(opinput, value) ((opinput).bits1 = (((opinput).bits1 & (~(OPINPUT_SHOW_CURSOR_BITS << OPINPUT_SHOW_CURSOR_SHIFT))) | (((u_int16) (value) & OPINPUT_SHOW_CURSOR_BITS) << OPINPUT_SHOW_CURSOR_SHIFT)))
#define OPINPUT_SET_FILLER_ZERO(opinput, value) ((opinput).bits1 = (((opinput).bits1 & (~(OPINPUT_FILLER_ZERO_BITS << OPINPUT_FILLER_ZERO_SHIFT))) | (((u_int16) (value) & OPINPUT_FILLER_ZERO_BITS) << OPINPUT_FILLER_ZERO_SHIFT)))

/*	---------------------------------------------------------------	*/

/* compression types (up to 8 different kinds) */
enum {
	COMP_NONE,		/* uncompressed bitmap */
	COMP_RLE,		/* CAVF comprehensive RLE format */
	COMP_RLE_INTERLACED	/* CAVF comprehensive RLE format interlaced */
};

/*	---------------------------------------	OpBitmap structure	*/
typedef struct {
	OpHeader	op_header;		/* BITMAP */
	WHRect  	range;			/* area of change */
	u_int16 	bits1;
	u_char    	data[VARIABLE_LEN];	/* packed bitmap data */
} OpBitmap;

/*	--------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	bw : 1;  			black and white (one-bit)
	diffs_only : 1;			depends on previous frame data
	lut_encoded : 1;		are any lines lut-encoded?
	filler : 1;
	comp_type : 4;			Compression type
	filler0 : 8;
*/
/*	---------------------------------------	OpBitmap CONSTS	*/
#define OPBITMAP_BW_BITS			0x1
#define OPBITMAP_BW_SHIFT			15
#define OPBITMAP_DIFFS_ONLY_BITS		0x1
#define OPBITMAP_DIFFS_ONLY_SHIFT		14
#define OPBITMAP_LUT_ENCODED_BITS		0x1
#define OPBITMAP_LUT_ENCODED_SHIFT		13
#define OPBITMAP_FILLER_BITS			0x1
#define OPBITMAP_FILLER_SHIFT			12
#define OPBITMAP_COMP_TYPE_BITS			0xf
#define OPBITMAP_COMP_TYPE_SHIFT		8
#define OPBITMAP_FILLER_ZERO_BITS		0xff
#define OPBITMAP_FILLER_ZERO_SHIFT		0

/*	---------------------------------------	OpBitmap size constants	*/
#define OPBITMAP_MEM_SIZE	sizeof(OpBitmap)
#define OPBITMAP_FILE_SIZE	14

/*	---------------------------------------	OpBitmap MACROS	*/
/*	INQUIRY macros. "Return" a u_int16.	*/

#define OPBITMAP_INQ_BW(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_BW_SHIFT) & OPBITMAP_BW_BITS)
#define OPBITMAP_INQ_DIFFS_ONLY(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_DIFFS_ONLY_SHIFT) & OPBITMAP_DIFFS_ONLY_BITS)
#define OPBITMAP_INQ_LUT_ENCODED(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_LUT_ENCODED_SHIFT) & OPBITMAP_LUT_ENCODED_BITS)
#define OPBITMAP_INQ_FILLER(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_FILLER_SHIFT) & OPBITMAP_FILLER_BITS)
#define OPBITMAP_INQ_COMP_TYPE(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_COMP_TYPE_SHIFT) & OPBITMAP_COMP_TYPE_BITS)
#define OPBITMAP_INQ_FILLER_ZERO(opbitmap) ((((opbitmap).bits1) >> OPBITMAP_FILLER_ZERO_SHIFT) & OPBITMAP_FILLER_ZERO_BITS)

/*	See the structure above to determine the return types of these macros.	*/

#define OPBITMAP_INQ_range(opbitmap) ((opbitmap).range)
#define OPBITMAP_INQ_data(opbitmap) ((opbitmap).data)

/*	SETTING macros. The value argument must be a u_int16.	*/

#define OPBITMAP_SET_BW(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_BW_BITS << OPBITMAP_BW_SHIFT))) | (((u_int16) (value) & OPBITMAP_BW_BITS) << OPBITMAP_BW_SHIFT)))
#define OPBITMAP_SET_DIFFS_ONLY(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_DIFFS_ONLY_BITS << OPBITMAP_DIFFS_ONLY_SHIFT))) | (((u_int16) (value) & OPBITMAP_DIFFS_ONLY_BITS) << OPBITMAP_DIFFS_ONLY_SHIFT)))
#define OPBITMAP_SET_LUT_ENCODED(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_LUT_ENCODED_BITS << OPBITMAP_LUT_ENCODED_SHIFT))) | (((u_int16) (value) & OPBITMAP_LUT_ENCODED_BITS) << OPBITMAP_LUT_ENCODED_SHIFT)))
#define OPBITMAP_SET_FILLER(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_FILLER_BITS << OPBITMAP_FILLER_SHIFT))) | (((u_int16) (value) & OPBITMAP_FILLER_BITS) << OPBITMAP_FILLER_SHIFT)))
#define OPBITMAP_SET_COMP_TYPE(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_COMP_TYPE_BITS << OPBITMAP_COMP_TYPE_SHIFT))) | (((u_int16) (value) & OPBITMAP_COMP_TYPE_BITS) << OPBITMAP_COMP_TYPE_SHIFT)))
#define OPBITMAP_SET_FILLER_ZERO(opbitmap, value) ((opbitmap).bits1 = (((opbitmap).bits1 & (~(OPBITMAP_FILLER_ZERO_BITS << OPBITMAP_FILLER_ZERO_SHIFT))) | (((u_int16) (value) & OPBITMAP_FILLER_ZERO_BITS) << OPBITMAP_FILLER_ZERO_SHIFT)))

/*	See the structure above to determine the value types of these macros.	*/

#define OPBITMAP_SET_range(opbitmap, value) (((opbitmap).range) = (value))
#define OPBITMAP_SET_data(opbitmap, value) (((opbitmap).data) = (value))

/*	--------------------------------------------------------------	*/

/* RECTCOPY -- copies regions from one part of the image to another */
/* applied after all subsequent BITMAP operations */

typedef struct {
	int16		left, top, width, height;
	int16		destx, desty;
} RectcopyInfo;

#define		MAX_COPY_RECTS		32
/*	--------------------------------------	OpRectcopy structure	*/
typedef struct {
	OpHeader    	op_header;	/* RECTCOPY */
	char        	num_rects;	/* number of rects to be copied */
	u_char      	bits1;
	RectcopyInfo	copy_rects[MAX_COPY_RECTS];	/* rects to copy */
	/* note that on disk, this structure is variably-sized */
} OpRectcopy;

/*	---------------	DESCRIPTION OF BITFIELDS (IN CASE YOU'RE INTERESTED)
	once_only : 1;		do this repeat to the following BITMAP only
	filler0 : 7;
*/
/*	--------------------------------------	OpRectcopy CONSTS	*/
#define OPRECTCOPY_ONCE_ONLY_BITS			0x1
#define OPRECTCOPY_ONCE_ONLY_SHIFT			7
#define OPRECTCOPY_FILLER_ZERO_BITS			0x7f
#define OPRECTCOPY_FILLER_ZERO_SHIFT		0

/*	--------------------------------------	OpRectcopy size constants	*/
#define OPRECTCOPY_MEM_SIZE		sizeof(OpRectcopy)
#define OPRECTCOPY_FILE_SIZE	6					/* $$$ note -> variably sized on disk	*/

/*	--------------------------------------	OpRectcopy MACROS	*/
/*	INQUIRY macros. "Return" a u_char.	*/

#define OPRECTCOPY_INQ_ONCE_ONLY(oprectcopy) ((((oprectcopy).bits1) >> OPRECTCOPY_ONCE_ONLY_SHIFT) & OPRECTCOPY_ONCE_ONLY_BITS)
#define OPRECTCOPY_INQ_FILLER_ZERO(oprectcopy) ((((oprectcopy).bits1) >> OPRECTCOPY_FILLER_ZERO_SHIFT) & OPRECTCOPY_FILLER_ZERO_BITS)

/*	See the structure above to determine the return type of this macro.	*/

#define OPRECTCOPY_INQ_num_rects(oprectcopy) ((oprectcopy).num_rects)

/*	SETTING macros. The value argument must be a u_char.	*/

#define OPRECTCOPY_SET_ONCE_ONLY(oprectcopy, value) ((oprectcopy).bits1 = (((oprectcopy).bits1 & (~(OPRECTCOPY_ONCE_ONLY_BITS << OPRECTCOPY_ONCE_ONLY_SHIFT))) | (((u_char) (value) & OPRECTCOPY_ONCE_ONLY_BITS) << OPRECTCOPY_ONCE_ONLY_SHIFT)))
#define OPRECTCOPY_SET_FILLER_ZERO(oprectcopy, value) ((oprectcopy).bits1 = (((oprectcopy).bits1 & (~(OPRECTCOPY_FILLER_ZERO_BITS << OPRECTCOPY_FILLER_ZERO_SHIFT))) | (((u_char) (value) & OPRECTCOPY_FILLER_ZERO_BITS) << OPRECTCOPY_FILLER_ZERO_SHIFT)))

/*	See the structure above to determine the value type of this macro.	*/

#define OPRECTCOPY_SET_num_rects(oprectcopy, value) (((oprectcopy).num_rects) = (value))

/*	---------------------------------------	OpBreak structure	*/
typedef struct {
	OpHeader	op_header;		/* BREAK */
	std::int32_t    	data;			/* user-associated data */
} OpBreak;

/*	--------------------------------------	OpBreak size constants	*/
#define OPBREAK_MEM_SIZE	sizeof(OpBreak)
#define OPBREAK_FILE_SIZE	8

/*	---------------------------------------	OpBreak MACROS	*/
/*	See the structure above to determine the return type of this macro.	*/

#define OPBREAK_INQ_data(opbreak) ((opbreak).data)

/*	See the structure above to determine the value type of this macro.	*/

#define OPBREAK_SET_data(opbreak, value) (((opbreak).data) = (value))

#endif

