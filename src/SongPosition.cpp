/*
 *  SongPosition.cpp
 *  stepmania
 *
 *  Created by [Full Username] on 5/10/11.
 *  Copyright 2011 [Organization Name]. All rights reserved.
 *
 */

#include "SongPosition.h"

void SongPosition::UpdateSongPosition( float fPositionSeconds, const TimingData &timing, const RageTimer &timestamp )
{

	if( !timestamp.IsZero() )
		m_LastBeatUpdate = timestamp;
	else
		m_LastBeatUpdate.Touch();

	// xxx testing: only do this on monotune survivor
	/*
	if( m_pCurSong && m_pCurSong->GetDisplayFullTitle() == "monotune survivor" )
		LOG->Trace( ssprintf("[GameState::UpdateSongPosition] cur BPS = %f, fPositionSeconds = %f",m_fCurBPS,fPositionSeconds) );
	*/

	timing.GetBeatAndBPSFromElapsedTime( fPositionSeconds, m_fSongBeat, m_fCurBPS, m_bFreeze, m_bDelay, m_iWarpBeginRow, m_fWarpDestination );
	
	// "Crash reason : -243478.890625 -48695.773438"
	ASSERT_M( m_fSongBeat > -2000, ssprintf("Song beat %f at %f seconds", m_fSongBeat, fPositionSeconds) );

	m_fMusicSeconds = fPositionSeconds;

	m_fLightSongBeat = timing.GetBeatFromElapsedTime( fPositionSeconds + g_fLightsAheadSeconds );

	m_fSongBeatNoOffset = timing.GetBeatFromElapsedTimeNoOffset( fPositionSeconds );

	m_fMusicSecondsVisible = fPositionSeconds - g_fVisualDelaySeconds.Get();
	float fThrowAway, fThrowAway2;
	bool bThrowAway;
	int iThrowAway;
	timing.GetBeatAndBPSFromElapsedTime( m_fMusicSecondsVisible, m_fSongBeatVisible, fThrowAway, bThrowAway, bThrowAway, iThrowAway, fThrowAway2 );

	/*
	// xxx testing: only do this on monotune survivor
	if( m_pCurSong && m_pCurSong->GetDisplayFullTitle() == "monotune survivor" )
	{
		// and only do it in the known negative bpm region. HACKITY HACK
		if(m_fSongBeat >= 445.490f && m_fSongBeat <= 453.72f)
		{
			LOG->Trace( ssprintf("fPositionSeconds = %f",fPositionSeconds) );
			LOG->Trace( ssprintf("Song beat: %f (%f seconds), BPS = %f (%f BPM)",m_fSongBeat,m_fMusicSecondsVisible,m_fCurBPS,m_fCurBPS*60.0f) );
			//LOG->Trace( ssprintf("Music seconds visible %f = fPositionSeconds %f - g_fVisualDelaySeconds %f", m_fMusicSecondsVisible,fPositionSeconds,g_fVisualDelaySeconds.Get()) );
		}
		else if(m_fSongBeat == 445.500f)
		{
			LOG->Trace( ssprintf("[beat 445.500] fPositionSeconds = %f",fPositionSeconds) );
			LOG->Trace( ssprintf("Song beat: %f (%f seconds), BPS = %f (%f BPM)",m_fSongBeat,m_fMusicSecondsVisible,m_fCurBPS,m_fCurBPS*60.0f) );
		}
	}
	*/


}
