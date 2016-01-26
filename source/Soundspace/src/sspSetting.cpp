// sspSetting.cpp: implementation of the sspSetting class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sspSetting.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////
// Static declarations
/////////////////////////////////

const char sspSetting::strProfileAudio[] = "Audio";
const char sspSetting::strAudioFrequency[] = "frequency";
const char sspSetting::strAudioBuffer[] = "buffer";
const char sspSetting::strAudioUpdate[] = "update";

const char sspSetting::strProfileResolution[] = "Resolution";
const char sspSetting::strResolutionTimer[] = "timer";
const char sspSetting::strResolutionEnvelope[] = "envelope";
const char sspSetting::strResolutionEvent[] = "event";

const char sspSetting::strProfileUpdates[] = "Updates";
const char sspSetting::strTimingEvent[] = "event";
const char sspSetting::strTimingClock[] = "clock";
const char sspSetting::strTimingGUI[] = "GUI";

const char sspSetting::strProfileFades[] = "Fade times";
const char sspSetting::strTimingFadeIn[] = "fade in";
const char sspSetting::strTimingFadeOut[] = "fade out";
const char sspSetting::strTimingVolume[] = "volume change";

const char sspSetting::strProfileSlider[] = "Slider";
const char sspSetting::strSlider[] = "value";

sspSetting::Audio		    sspSetting::audio = {44100, 2000, 500};
sspSetting::Resolution  sspSetting::res = {1, 10, 100};
sspSetting::Updates		  sspSetting::update = {1.0f, 5.0f, 10.0f};
sspSetting::FadeTimes		sspSetting::fade = {2, 5, 3};

float	sspSetting::sliderValue[] = {0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

void sspSetting::Audio::ReadRegistry()
{
	freq = AfxGetApp()->GetProfileInt(strProfileAudio, strAudioFrequency, 44100);
	bufSize = AfxGetApp()->GetProfileInt(strProfileAudio, strAudioBuffer, 2000);
	update = AfxGetApp()->GetProfileInt(strProfileAudio, strAudioUpdate, 500);
}

void sspSetting::Resolution::ReadRegistry()
{
	timer = AfxGetApp()->GetProfileInt(strProfileResolution, strResolutionTimer, 1);
	envelope = AfxGetApp()->GetProfileInt(strProfileResolution, strResolutionEnvelope, 10);
	event = AfxGetApp()->GetProfileInt(strProfileResolution, strResolutionEvent, 100);
}

void sspSetting::Updates::ReadRegistry()
{
	CString dataStr;
	dataStr = AfxGetApp()->GetProfileString(strProfileUpdates, strTimingEvent);
	sscanf_s(dataStr, "%f", &event);
	dataStr = AfxGetApp()->GetProfileString(strProfileUpdates, strTimingClock);
	sscanf_s(dataStr, "%f", &clock);
	dataStr = AfxGetApp()->GetProfileString(strProfileUpdates, strTimingGUI);
	sscanf_s(dataStr, "%f", &gui);
}

void sspSetting::FadeTimes::ReadRegistry()
{
	fadeIn = AfxGetApp()->GetProfileInt(strProfileFades, strTimingFadeIn, 2);
	fadeOut = AfxGetApp()->GetProfileInt(strProfileFades, strTimingFadeOut, 5);
	volume = AfxGetApp()->GetProfileInt(strProfileFades, strTimingVolume, 3);
}

void sspSetting::ReadSliderRegistry()
{
	CString dataStr;
	dataStr = AfxGetApp()->GetProfileString(strProfileSlider, strSlider);
	sscanf_s(dataStr, "%f %f %f %f %f %f %f %f %f", &sliderValue[0], &sliderValue[1], &sliderValue[2], &sliderValue[3],
		&sliderValue[4], &sliderValue[5], &sliderValue[6], &sliderValue[7], &sliderValue[8]);
}

void sspSetting::ReadAllRegistry()
{
	audio.ReadRegistry();
	res.ReadRegistry();
	update.ReadRegistry();
	fade.ReadRegistry();
	ReadSliderRegistry();
}

void sspSetting::Audio::WriteRegistry()
{
	AfxGetApp()->WriteProfileInt(strProfileAudio, strAudioFrequency, freq);
	AfxGetApp()->WriteProfileInt(strProfileAudio, strAudioBuffer, bufSize);
	AfxGetApp()->WriteProfileInt(strProfileAudio, strAudioUpdate, update);
}

void sspSetting::Resolution::WriteRegistry()
{
	AfxGetApp()->WriteProfileInt(strProfileResolution, strResolutionTimer, timer);
	AfxGetApp()->WriteProfileInt(strProfileResolution, strResolutionEnvelope, envelope);
	AfxGetApp()->WriteProfileInt(strProfileResolution, strResolutionEvent, event);
}

void sspSetting::Updates::WriteRegistry()
{
	CString dataStr;
	dataStr.Format("%.2f", event);
	AfxGetApp()->WriteProfileString(strProfileUpdates, strTimingEvent, dataStr);
	dataStr.Format("%.2f", clock);
	AfxGetApp()->WriteProfileString(strProfileUpdates, strTimingClock, dataStr);
	dataStr.Format("%.2f", gui);
	AfxGetApp()->WriteProfileString(strProfileUpdates, strTimingGUI, dataStr);
}

void sspSetting::FadeTimes::WriteRegistry()
{
	AfxGetApp()->WriteProfileInt(strProfileFades, strTimingFadeIn, fadeIn);
	AfxGetApp()->WriteProfileInt(strProfileFades, strTimingFadeOut, fadeOut);
	AfxGetApp()->WriteProfileInt(strProfileFades, strTimingVolume, volume);
}

void sspSetting::WriteSliderRegistry()
{
	CString dataStr;
	dataStr.Format("%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f", sliderValue[0], sliderValue[1], sliderValue[2],
		sliderValue[3], sliderValue[4], sliderValue[5], sliderValue[6], sliderValue[7], sliderValue[8]);
	AfxGetApp()->WriteProfileString(strProfileSlider, strSlider, dataStr);
}

void sspSetting::WriteAllRegistry()
{
	audio.WriteRegistry();
	res.WriteRegistry();
	update.WriteRegistry();
	fade.WriteRegistry();
	WriteSliderRegistry();
}
