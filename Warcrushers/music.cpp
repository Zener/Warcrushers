///////////////////////AUDIO//////////////////////////////////////
#include "music.h"  
#include "gaudio.h"  //MP3
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "audiot\audio.h"

#if defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__DJGPP__)
#include <conio.h>
#else
#define kbhit() 0
#endif
LPAUDIOMODULE lpModule;
extern int modok;
//////////////////////////////////////////////////////////////////
#define FREQ(nPeriod) (((LONG) lpWave->nSampleRate * 428) / nPeriod)


LPAUDIOWAVE lpWave[20];
HAC hVoice[8];



void Sonido(int n, int side, int iii)
{
	BOOL stopped, stopped2;	   
	 
	AGetVoiceStatus(hVoice[iii*2], &stopped);
	AGetVoiceStatus(hVoice[(iii*2)+1], &stopped2);	 
	 
	if ((side == SR) && (stopped))
	{
		APlayVoice(hVoice[iii*2], lpWave[n]);
	}
	else if ((side == SL) && stopped2)
	{
		APlayVoice(hVoice[(iii*2)+1], lpWave[n]);
	}
	else if (stopped && stopped2)
	{		
		  APlayVoice(hVoice[(iii*2)+0], lpWave[n]);
		  APlayVoice(hVoice[(iii*2)+1], lpWave[n]);	
	}
	AUpdateAudio();
}


void InitSfx(unsigned long canales)
{
    ALoadWaveFile("music/burn.wav", &lpWave[1], 0);
	ALoadWaveFile("music/espada2.wav", &lpWave[2], 0);
	ALoadWaveFile("music/espada3.wav", &lpWave[3], 0);
    ALoadWaveFile("music/golpe1.wav", &lpWave[4], 0);
	ALoadWaveFile("music/grito1.wav", &lpWave[5], 0);
	ALoadWaveFile("music/grito2.wav", &lpWave[6], 0);
	ALoadWaveFile("music/grito3.wav", &lpWave[7], 0);
	ALoadWaveFile("music/pifia1.wav", &lpWave[8], 0);
	ALoadWaveFile("music/win.wav", &lpWave[9], 0);
	ALoadWaveFile("music/explo.wav", &lpWave[10], 0);
	//ALoadWaveFile("music/bosque1.wav", &lpWave[11], 0);
	ALoadWaveFile("music/victory.wav", &lpWave[12], 0);
	ALoadWaveFile("music/defeat.wav", &lpWave[13], 0);
	//ALoadWaveFile("music/Ambient.wav", &lpWave[14], 0);
	//ALoadWaveFile("music/Night.wav", &lpWave[15], 0);

	for (int n = 0; n < 8; n++) {
        ACreateAudioVoice(&hVoice[n]);
        ASetVoiceVolume(hVoice[n], 64);
        ASetVoicePanning(hVoice[n], n & 1 ? 0 : 255);
    }
    
}


void InitAudio(void)
{
    AUDIOINFO info;   

    /* initialize audio library */
    AInitialize();
    /* open audio device */
    info.nDeviceId = AUDIO_DEVICE_MAPPER;
    info.wFormat = AUDIO_FORMAT_16BITS | AUDIO_FORMAT_STEREO;
    info.nSampleRate = 44100;
	#ifdef USEFILTER
    /* enable antialias dynamic filtering */
    info.wFormat |= AUDIO_FORMAT_FILTER;
	#endif
    AOpenAudio(&info);
    /* load module file */
	srand( (unsigned)time( NULL ) );
	/*
	int r = rand()%250;
	if (r<50)	modok = !ALoadModuleFile("music\\SOTBForest.MOD", &lpModule, 0);
	if ((r>=50) && (r<100) )modok = !ALoadModuleFile("music\\SOTBCaves.MOD", &lpModule, 0);	
	if ((r>=100) && (r<150) )modok = !ALoadModuleFile("music\\SOTBFort.MOD", &lpModule, 0);	
	if ((r>=150) && (r<200) )modok = !ALoadModuleFile("music\\SOTBFuneral.MOD", &lpModule, 0);	
	if ((r>=200) )modok = !ALoadModuleFile("music\\SOTBTemple.MOD", &lpModule, 0);	
	*/
	modok = !ALoadModuleFile("music\\Xadou.xm", &lpModule, 0);
    if (modok)
//	if (modok = !ALoadModuleFile("music\\xadou.xm", &lpModule, 0))
	{
		/* open voices and play module */
		AOpenVoices(lpModule->nTracks + 8);
		APlayModule(lpModule);
    }
	InitSfx(lpModule->nTracks);

}

 
void setMusicVolume(int vol)
{
	ASetModuleVolume(vol*12);
}

void setSoundVolume(int vol)
{
	ASetVoiceVolume(hVoice[0], vol*5);
	ASetVoiceVolume(hVoice[1], vol*5);
	ASetVoiceVolume(hVoice[2], vol*5);
	ASetVoiceVolume(hVoice[3], vol*5);
	ASetVoiceVolume(hVoice[4], vol*5);
	ASetVoiceVolume(hVoice[5], vol*5);
	ASetVoiceVolume(hVoice[6], vol*5);
	ASetVoiceVolume(hVoice[7], vol*5);
}




#define FREQ(nPeriod) (((LONG) lpWave->nSampleRate * 428) / nPeriod)

void Audio()
{
	
	
//    HAC hVoice[5];
//    BOOL stopped;
//    UINT n, m;
	//BOOL stopped;
        /* check if the module is stopped */
        //AGetModuleStatus(&stopped);
        //if (stopped) break;
        /* update audio system */

    /*
	for (n = 0; n < 5; n++) {
        ACreateAudioVoice(&hVoice[n]);
        ASetVoiceVolume(hVoice[n], 64);
        ASetVoicePanning(hVoice[n], n & 1 ? 0 : 255);
    }
*/

    //for (n = m = 0; !kbhit() && n < 48 - 7; n++) {
        /* play chord C-E-G */
        //APlayVoice(hVoice[m+1], lpWave);
        //APlayVoice(hVoice[m+2], lpWave);
 //       ASetVoiceFrequency(hVoice[m+0], FREQ(aPeriodTable[n+0]));
 //       ASetVoiceFrequency(hVoice[m+1], FREQ(aPeriodTable[n+4]));
  //      ASetVoiceFrequency(hVoice[m+2], FREQ(aPeriodTable[n+7]));
    //    m = (m + 3) % 5;

        /* wait until note finishes 
        do {
            /* update audio system 
            AUpdateAudio();
            AGetVoiceStatus(hVoice[0], &stopped);
        } while (!stopped);
    //}*/


    /* stop and release voices 
    for (n = 0; n < 5; n++) {
        AStopVoice(hVoice[n]);
        ADestroyAudioVoice(hVoice[n]);
    }
    ACloseVoices();
	
	  */
	AUpdateAudio();
	//Sleep(300);
	
}

void FiniAudio()
{
    /* stop module and close voices */
    AStopModule();
    ACloseVoices();
    /* release module file */
    AFreeModuleFile(lpModule);
    /* close audio device */
    ACloseAudio();
}








////////////////////////////////////////////////////////////////////////
/////////////////////////////// MP3 ////////////////////////////////////
////////////////////////////////////////////////////////////////////////


WORD		DllVersion;
CGAudio		*pgAudio;
CMPEGstream	*pMPEG;
	

void music()
{
	GA_ERRCODE err;

	DllVersion = GA_getLibVersion();
	
	char rev = DllVersion&0xff;
	char sec = (DllVersion>>16)&0xff;
	char prim = (DllVersion>>8)&0x7f;
	
	pgAudio = new CGAudio();
	err = pgAudio->init(GA_DEVICETYPE_DSOUND, GA_DEVICEFREQ_44K, FALSE);
	if (err != GA_OK)
	{
		//printf(pgAudio->getLastErrorString());
//		getch();
		delete pgAudio;
		return;
	}

	st_GA_StreamParameters MPEGParams;
	ZeroMemory(&MPEGParams, sizeof MPEGParams);
	MPEGParams.classID = CLASS_MPEGSTREAM_ID;
	MPEGParams.fileName = "redbull.mp3";
	MPEGParams.flag = GA_FLAG_LOOP + GA_FLAG_MEMPROGRESS;
	MPEGParams.input = GA_INPUT_DISK;
	MPEGParams.audioStage = NULL;
	MPEGParams.output = GA_OUTPUT_DSOUND;

	err = pgAudio->getSoundClass(GA_SOUNDCLASS_MPEG, &MPEGParams, (void**)&pMPEG);
	if (err != GA_OK)
	{
		//printf(pgAudio->getLastErrorString());
		delete pgAudio;
		return;
	}

	pMPEG->play();

//	pMPEG->release();
//	delete pgAudio;
}

