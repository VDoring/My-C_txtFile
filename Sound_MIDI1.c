#include <stdio.h>

#include <conio.h>

#include <windows.h>

#include <mmsystem.h>



#pragma comment(lib, "winmm.lib")



#pragma pack(push,1)



typedef struct

{

	BYTE byteState;

	BYTE byteNote;

	BYTE byteVelocity;

	BYTE byteNULL;

}MJGRShortMidiMSG_ST;



typedef union

{

	DWORD                dwMidi_Data;

	MJGRShortMidiMSG_ST  stMidi_Data;

}MJGRShortMidiMSG;



#pragma pack(pop)



HMIDIOUT     m_DevHandle;

MMRESULT     m_MMErrCode;

MIDIOUTCAPS  m_NowMidiOutCaps;



void CALLBACK MidiOutProc(HMIDIOUT MidiOut, UINT Msg,

	DWORD Instance, DWORD Param1,

	DWORD Param2)

{

}



void Midi_OutputError(MMRESULT mmrErrCode)

{

	char m_szErrMsg[128];



	midiInGetErrorText(mmrErrCode, (char *)m_szErrMsg, sizeof(m_szErrMsg));



	MessageBox(0, m_szErrMsg, "Midi Error!!!", MB_OK);

}





long Midi_GetDevID(HMIDIOUT m_DevOutHandle)

{

	UINT     uDeviceID;

	MMRESULT Result = midiOutGetID(m_DevOutHandle, &uDeviceID);



	if (Result != MMSYSERR_NOERROR)

	{

		Midi_OutputError(Result);

		return -1;

	}



	return (long)uDeviceID;

}



void Midi_GetDevCaps(HMIDIOUT m_DevOutHandle, MIDIOUTCAPS *Caps)

{

	long     lDeviceID;

	MMRESULT Result;



	lDeviceID = Midi_GetDevID(m_DevOutHandle);



	if (lDeviceID < 0) return;



	Result = midiOutGetDevCaps((UINT)lDeviceID, Caps, sizeof(MIDIOUTCAPS));



	if (Result != MMSYSERR_NOERROR)

	{

		Midi_OutputError(Result);

	}

}



HMIDIOUT Midi_Open(WORD wDevsNum)

{

	WORD      wMaxDevNum = 0;

	MMRESULT  uiMidiOpen = 0;

	HMIDIOUT  m_DevHandle = NULL;



	wMaxDevNum = midiInGetNumDevs();



	if (wDevsNum >= wMaxDevNum)

	{

		wDevsNum = 0;

	}



	uiMidiOpen = midiOutOpen(&m_DevHandle, wDevsNum,

		(DWORD)(MidiOutProc),

		(DWORD)NULL, CALLBACK_FUNCTION);



	if (uiMidiOpen != MMSYSERR_NOERROR)

	{

		Midi_OutputError(uiMidiOpen);

		return NULL;

	}



	return m_DevHandle;

}



LRESULT Midi_Close(HMIDIOUT m_DevOutHandle)

{

	MMRESULT Result;



	Result = midiOutClose(m_DevOutHandle);



	if (Result != MMSYSERR_NOERROR)

	{

		Midi_OutputError(Result);

		return FALSE;

	}
	else {

		m_DevOutHandle = NULL;

	}



	return TRUE;

}



void Midi_SendShortMsg(HMIDIOUT m_DevOutHandle, BYTE byteState, BYTE byteNote, BYTE byteValo)

{

	MJGRShortMidiMSG  sMsg;



	sMsg.stMidi_Data.byteVelocity = byteValo;

	sMsg.stMidi_Data.byteNote = byteNote;

	sMsg.stMidi_Data.byteState = byteState;

	sMsg.stMidi_Data.byteNULL = 0;



	midiOutShortMsg(m_DevOutHandle, sMsg.dwMidi_Data);

}



void Midi_SendLongMsg(HMIDIOUT m_DevOutHandle, BYTE *lpMsg, DWORD dwMsgLength)

{

	MIDIHDR  m_MIDIHdr;

	MMRESULT Result;



	ZeroMemory(&m_MIDIHdr, sizeof(MIDIHDR));



	m_MIDIHdr.lpData = (char *)lpMsg;

	m_MIDIHdr.dwBufferLength = dwMsgLength;

	m_MIDIHdr.dwFlags = 0;



	Result = midiOutPrepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));



	if (Result != MMSYSERR_NOERROR)

	{

		Midi_OutputError(Result);

		return;

	}



	Result = midiOutLongMsg(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));



	if (Result != MMSYSERR_NOERROR)

	{

		Midi_OutputError(Result);

		return;

	}



	midiOutUnprepareHeader(m_DevOutHandle, &m_MIDIHdr, sizeof(MIDIHDR));

}



void Midi_AllChannelSoundOff(HMIDIOUT m_DevOutHandle)

{

	BYTE channel;



	for (channel = 0; channel < 16; channel++)

	{

		Midi_SendShortMsg(m_DevOutHandle, (BYTE)(0xB0 + channel), 0x78, 0);

	}

}



void main()

{

	int  i, loop;

	BYTE szMusKey[18] = { 0x41,0x57,0x53,0x45,0x44,

						0x46,0x54,0x47,0x59,0x48,

						0x55,0x4A,0x4B,0x4F,0x4C,

						0x50,0xBA,0xDE };

	BYTE szMusKeyOnOff[18] = { 0 };



	m_DevHandle = Midi_Open(0);



	if (m_DevHandle == NULL)

	{

		return;

	}



	printf("[ESC] : Á¾·á\n\n");

	printf("   [W]   [E]       [T]   [Y]   [U]       [O]   [P]\n\n");

	printf("[A]   [S]   [D] [F]   [G]   [H]   [J] [K]   [L]   [;] [\"]\n");



	Midi_AllChannelSoundOff(m_DevHandle);

	Midi_SendShortMsg(m_DevHandle, 0xB0, 7, 127);



	loop = 1;

	while (loop)

	{

		if (kbhit())

		{

			if (GetKeyState(VK_ESCAPE) & 0xFF00) loop = 0;

			else {

				for (i = 0; i < 18; i++)

				{

					if (GetKeyState(szMusKey[i]) & 0xFF00)

					{

						if (szMusKeyOnOff[i] == 0)

						{

							szMusKeyOnOff[i] = 1;

							Midi_SendShortMsg(m_DevHandle, 0x90, (BYTE)(0x30 + i), 120);

						}

					}

				}

			}

		}



		for (i = 0; i < 18; i++)

		{

			if (!(GetKeyState(szMusKey[i]) & 0xFF00))

			{

				if (szMusKeyOnOff[i] != 0)

				{

					szMusKeyOnOff[i] = 0;

					Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);

				}

			}

		}

	}



	for (i = 0; i < 18; i++)

	{

		if (szMusKeyOnOff[i] != 0)

		{

			Midi_SendShortMsg(m_DevHandle, 0x80, (BYTE)(0x30 + i), 120);

		}

	}



	Midi_AllChannelSoundOff(m_DevHandle);



	Midi_Close(m_DevHandle);

}

// https://www.crocus.co.kr/19?category=116609