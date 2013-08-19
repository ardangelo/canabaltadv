/*
 * Krawall, XM/S3M Modplayer Library
 * Copyright (C) 2001-2005, 2013 Sebastian Kienzl
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License in COPYING for more details.
 */

// this file is generated, do not edit.
// see documentation for detailed information

#ifndef KRAWALL_H__INCLUDED
#define KRAWALL_H__INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS

typedef unsigned int chandle;
typedef unsigned int ihandle;

// internal data structures, revealed what might be of interest
typedef struct {
	// number of channels
	unsigned char	channels;
	// ...
} Module;

typedef struct {
	unsigned long	__private0;
	unsigned char*	__private1;
	// neutral frequency
	unsigned long	c2Freq;
	signed char		__private2;
	signed char		__private3;
	// default volume
	unsigned char	volDefault;
	// default pan
	signed char		panDefault;
	unsigned char  	loop;
	// ...
} Sample;

typedef struct {
	// ...
} Instrument;

#endif

extern const Sample* const samples[];
extern const Instrument* const instruments[];


#if __GNUC__ == 2
	#define kramWorker kramWorkerSTUB
	#define kramPlay kramPlaySTUB
	#define kramPlayExt kramPlayExtSTUB
	#define kramStop kramStopSTUB
	#define kramSetFreq kramSetFreqSTUB
	#define kramSetVol kramSetVolSTUB
	#define kramSetPan kramSetPanSTUB
	#define kramSetPos kramSetPosSTUB
	#define LONG_CALL
#elif __GNUC__ >= 3
	#define LONG_CALL __attribute__ ((long_call))
#else
	#error "This version of Krawall is for GCC2/3 only!!"
#endif


//! Init function.
/*!
Call this function once at startup.
\param stereo Whether Krawall should operate stereo (KRAG_INIT_STEREO) or not (KRAG_INIT_MONO)
*/
void kragInit( int stereo );
#define KRAG_INIT_MONO 0
#define KRAG_INIT_STEREO 1


//! Reset function.
/*!
This is only needed if you want to call kragInit() again, most likely because you want
to switch from mono to stereo or vice versa. Calling this while there is sound being output
will result in an audible (but harmless) hickup.
*/
void kragReset();


//! Start music
/*!
\param m Pointer to module
\param mode is one or more of:
			- KRAP_MODE_LOOP	Loop module
			- KRAP_MODE_SONG	Enable song-mode
			- KRAP_MODE_JINGLE	Play module as jingle
\param song Song of module to play
\sa krapStop
*/
void krapPlay( const Module *m, int mode, int song );
#define KRAP_MODE_LOOP 1
#define KRAP_MODE_SONG 2
#define KRAP_MODE_JINGLE 4

//! Stop music
/*!
Immediately stops playback of music.
\sa krapPlay
*/
void krapStop();

//! Stop a playing jingle
/*!
This will immediately stop a playing jingle
and resume playback of the old song.
Note that if no jingle is playing this function will do nothing.
The callback will immediately get called with KRAP_CB_JDONE if set.
\sa krapPlay
\sa krapCallback
*/
void krapStopJingle();

//! Install callback
/*!
Installs a callback. The callback should return as quickly as possible.
When the callback gets called the first numeric parameter
describes the event, the second numeric parameter (if any)
is the parameter to the event.
The events are as following:
	- KRAP_CB_FADE		Destination volume has been reached
	- KRAP_CB_DONE		Module is done (also when KRAP_MODE_LOOP)
	- KRAP_CB_MARK		Mark-Effect Zxx (xx in param 2)
	- KRAP_CB_SONG		Song-boundary hit (+++-Marker)
	- KRAP_CB_JDONE		Jingle is done
\sa krapSetMusicVol
*/
void krapCallback( void (*func)( int, int ) );
#define KRAP_CB_FADE 1	// fading done (see krapSetMusicVol)
#define KRAP_CB_DONE 2	// module stop
#define KRAP_CB_MARK 3	// mark-effect occured in pattern (op in param 2)
#define KRAP_CB_SONG 4	// played over a song-boundary (++)
#define KRAP_CB_JDONE 5 // jingle done
#define KRAP_CB_LOOP 6  // module/song restarts because looped

//! Pause music
/*!
Pauses all currently active channels. You still can play SFX's.
The paused channels will be frozen until krapUnpause() gets called.
\param sfx If true pause sfx as well; if false pause music only
\sa krapUnpause
*/
void krapPause( int sfx );

//! Unpause music
/*!
Reactivates all channels that have been paused with krapPause()
\sa krapPause
*/
void krapUnpause();

//! Get Pause status
/*!
Returns whether playback is currently paused or not
\return True if paused
\sa krapPause
\sa krapUnpause
*/
int krapIsPaused();

//! Set music volume
/*!
You can either set the music volume immediately or fade slowly
to the specified volume. The fadespeed depends on the speed
of the currently active module.
If module is paused then volume is always set immediately.
If a callback is installed it will get triggered when fading is done.
The volume given will directly scale the global volume set in the S3M.
\param vol Music volume (0..128)
\param fade If true fade, if false set immediately
\sa kramSetSFXVol
\sa krapCallback
*/
void krapSetMusicVol( unsigned int vol, int fade );

//! Get music volume
/*!
Returns volume as set by krapSetMusicVol()
\sa krapSetMusicVol
\return volume
*/
unsigned int krapGetMusicVol();

//! Play an instrument as SFX
/*!
Plays an instrument as an SFX. If you use this, be sure to call
krapInstProcess() periodically, this is where the envelopes get
processed.
\param ins Pointer to instrument (instruments[])
\param note 0 (C-0) .. 95 (B-7)
\param old Old handle, will be recycled if given
\sa kramPlay
\sa krapInstRelease
\sa krapInstStop
\sa krapInstProcess
\return Instrument handle, zero if no channel/instrument could be allocated
*/
ihandle krapInstPlay( const Instrument *ins, int note, ihandle old );

//! Release a playing instrument
/*!
Releases a playing instrument if either still playing or in sustain-mode.
\param i Handle as returned by krapInstPlay()
\return true if successful
\sa krapInstPlay
*/
int krapInstRelease( ihandle i );

//! Stop a playing instrument
/*!
Will immediately stop a playing instrument
\param i Handle as returned by krapInstPlay()
\return true if successful
\sa krapInstPlay
*/
int krapInstStop( ihandle i );

//! Process instrument-sfx envelopes
/*!
If you use instruments for sfx you should call this periodically.
Once a frame is quite good idea.
*/
void krapInstProcess();

//! Check if an instrument-handle is still valid
/*!
This is similiar to kramHandleValid() but works
for an instrument-handle. It will return false
if an instrument has already stopped playing (one-shot sample).
\param i handle to check
\return true if valid, false if invalid
\sa kramHandleValid
*/
int krapInstHandleValid( ihandle i );

//! Set a channel's volume
/*!
This will set a channel's volume.
S3M-effects Mxx and Nxx will override this value.
krapPlay will reset all channel's volume to 64.
\param channel mod-channel (0..#channels of current mod)
\param vol volume (0..64)
\sa krapGetChannelVol
*/
void krapSetChannelVol( unsigned int channel, unsigned int vol );

//! Get a channel's volume
/*!
This will get a channel's volume as either set by
krapSetChannelVol() or S3M-effects Mxx and Nxx.
\param channel mod-channel (0..#channels of current mod)
\return volume
\sa krapSetChannelVol
*/
unsigned int krapGetChannelVol( unsigned int channel );



//! Worker procedure
/*!
This is where the actual work is done, you *MUST* call
this once per frame after kraInit() to get sound
\sa kragInit()
\return True if actual work has been done
*/
int kramWorker() LONG_CALL;

//! Get number of currently active channels
/*!
Returns number of currently active channels.
\return Number of currently active channels
*/
int kramGetActiveChannels();

//! Set quality mode
/*!
This sets the quality mode of the mixing routines.
KRAM_QM_NORMAL is the default, KRAM_QM_MARKED only plays the marked samples (see docs)
in HQ and KRAM_QM_HQ plays everything in HQ.
The flag KRAM_QM_RAMP_OFF (must be OR'd) DISABLES stop-ramping. Until version 20040707
you had to enable it explicitly, now it must be disabled explicitly. Hence the flag
KRAM_QM_RAMP has lost it's meaning.
Especially looped samples that get stopped abruptly might cause pops.
Stop-ramping removes these pops at the cost of a little more CPU.
*/
void kramQualityMode( int );
#define KRAM_QM_NORMAL 		0
#define KRAM_QM_MARKED 		1
#define KRAM_QM_HQ 			2
#define KRAM_QM_RAMP		16
#define KRAM_QM_RAMP_OFF	32

//! Play a sample
/*!
Plays a sample with it's C2 (neutral) frequency.
\param s Pointer to sample
\param sfx Whether sample to play is an SFX
\param c Old handle, will be recycled if given
\sa kramPlayExt()
\return Channel handle
*/
chandle kramPlay( const Sample *s, int sfx, chandle c ) LONG_CALL;

//! Play a sample Ext
/*!
Just like kramPlay, but all of the attribs can be specified.
\param s Pointer to sample
\param sfx Whether sample to play is an SFX
\param c Old handle, will be recycled if given
\param freq Frequency in hertz to play sample at
\param vol Volume to play sample with (0..64)
\param pan Panning to play sample with (-64..64)
\sa kramPlay()
\return Channel handle
*/
chandle kramPlayExt( const Sample *s, int sfx, chandle c, unsigned int freq, unsigned int vol, int pan ) LONG_CALL;

//! Stop a channel
/*!
Stops playback of a channel.
Note that if the channel has already stopped this call will not do anything and return false.
\param c Channel handle
\return true if successful
*/
int kramStop( chandle c ) LONG_CALL;

//! Set frequency
/*!
Sets frequency of an active channel.
Note that if the channel has already stopped this call will not do anything and return false.
\param c Channel handle
\param freq Frequency in hertz
\return true if successful
*/
int kramSetFreq( chandle c, unsigned int freq ) LONG_CALL;

//! Set volume
/*!
Sets volume of an active channel.
Note that if the channel has already stopped this call will not do anything and return false.
\param c Channel handle
\param vol Volume (0..64)
\return true if successful
*/
int kramSetVol( chandle c, unsigned int vol ) LONG_CALL;

//! Set panning
/*!
Sets the panning-position of an active channel.
Note that if the channel has already stopped this call will not do anything and return false.
\param c Channel handle
\param pan Panning (-64..0..64), KRAM_SP_LEFT, KRAM_SP_RIGHT, KRAM_SP_CENTER
\return true if successful
*/
int kramSetPan( chandle c, int pan ) LONG_CALL;
#define KRAM_SP_LEFT -64
#define KRAM_SP_CENTER 0
#define KRAM_SP_RIGHT 64
//@}

//! Set Position
/*!
Sets the sample-position of an active channel.
Note that if the channel has already stopped this call will not do anything and return false.
\param c Channel handle
\param pos Sample offset to set
\return true if successful
*/
int kramSetPos( chandle c, unsigned int pos ) LONG_CALL;

//! Set SFX volume
/*!
Sets the volume of all active and future sfx.
\param vol Volume (0..128)
*/
void kramSetSFXVol( unsigned int vol );

//! Get SFX volume
/*!
Returns volume as set with kramSetSFXVol().
\sa kramSetSFXVol
\return volume
*/
unsigned int kramGetSFXVol();

//! Set Master Clip volume
/*!
Sets the clipping curve's steepness.
128 is the default value, setting a neutral clipping curve.
Values below 128 (down to 16) can be used to reduce distortion (volume) if the output is too high.
Values above 128 will give you additional gain but also reduce the quality because
information is lost, don't do this.
Additionally you can OR the volume with one of the parameters KRAM_MV_CHANNELS32, KRAM_MV_CHANNELS16
or KRAM_MV_CHANNELS8. KRAM_MV_CHANNELS32 is the default -- specifying one of the other values
will give you additional gain. However as the parameter says you should not use more than the amount
of channels then - otherwise you might get unpredictable clicks/distortion.
\param vol 128 is default, everything below/above changes the clipping curve. OR with KRAM_MV_CHANNELS16 or KRAM_MV_CHANNELS8 if appropriate
*/
void kramSetMasterVol( unsigned int vol );
#define KRAM_MV_CHANNELS32 ( 5 << 16 )
#define KRAM_MV_CHANNELS16 ( 4 << 16 )
#define KRAM_MV_CHANNELS8 ( 3 << 16 )

//! Stops all active SFX channels
/*!
Stops all currently active SFX channels. Paused SFX channels are not stopped.
*/
void kramStopSFXChannels();

//! Check whether a handle is still valid
/*!
Checks if chandle is still a valid handle. A handle will
get invalidated if for example a one-shot sample ends.
\param c handle to check
\return true if valid, false if invalid
*/
int kramHandleValid( chandle c );

//! Get frequency
/*!
Get frequency of a channel.
THIS FUNCTION DOES NOT CHECK FOR HANDLE-VALIDITY!
\param c handle
\return current frequency
*/
unsigned int kramGetFreq( chandle c );

//! Get volume
/*!
Get volume of a channel.
THIS FUNCTION DOES NOT CHECK FOR HANDLE-VALIDITY!
\param c handle
\return current volume
*/
unsigned int kramGetVol( chandle c );

//! Get panning
/*!
Get panning of a channel.
THIS FUNCTION DOES NOT CHECK FOR HANDLE-VALIDITY!
\param c handle
\return current panning
*/
int kramGetPan( chandle c );

//! Get position
/*!
Get position of a channel.
THIS FUNCTION DOES NOT CHECK FOR HANDLE-VALIDITY!
\param c handle
\return current position
*/
unsigned int kramGetPos( chandle c );


//! Directsound Interrupt
/*!
This function resets the DMA and must be tied to the
Timer1-IRQ.
*/
void kradInterrupt();

//! Activate Krawall
/*!
You only need to call this if you have called kradDeactivate().
*/
void kradActivate();

//! Deactivate Krawall
/*!
You might want to deactivate Krawall in order to write savegames
and stuff like that. Calling this will stop all DMA-operations
(and thus sound-output) until resumed by kradActivate().
*/
void kradDeactivate();



#ifdef __cplusplus
}
#endif

#endif

