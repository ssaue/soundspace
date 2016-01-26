// SSpGUIMessage.cpp : implementation file
//

#include "stdafx.h"
#include "SoundSpace.h"
#include "SSpGUIMessage.h"
#include "SSpGUIMessageEditor.h"
#include "SSpMessage.h"
#include "sspPools.h"
#include "sspSetting.h"


CMessageDialog::CMessageDialog(unsigned int nIDTemplate, CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd)
{
}


CString SSpGUIMessage::GetMessageText(SSpStreamMsg* pMessage)
{
	CString text;
	CString add;
	if (pMessage->GetStream() == USE_SEND_PARAMETER)
		text = "Current stream";
	else
		text = sspPool::Instance().streams.GetName(pMessage->GetStream());
	switch (pMessage->GetMessage().GetMsgType()) {
	case SSP_LOAD_EVENT:
		text += "  LoadTask  " + CString(sspPool::Instance().values.GetName(pMessage->GetMsgPara(0).iVal));
		if (pMessage->GetMsgPara(1).iVal == USE_SEND_PARAMETER)
			text += "  This task";
		else
			text += "  " + CString(sspPool::Instance().tasks.GetName(pMessage->GetMsgPara(1).iVal));
		return text;
	case SSP_SOLO:
		add.Format("  SoloTask  %d sec", pMessage->GetMsgPara(0).iVal);
		text += add;
		return text;
	case SSP_MUTE:
		add.Format("  MuteStream  %d sec", pMessage->GetMsgPara(0).iVal);
		text += add;
		return text;
	case SSP_UNSOLO:
		add.Format("  EndSolo  %d sec", pMessage->GetMsgPara(0).iVal);
		text += add;
		return text;
	case SSP_UNMUTE:
		add.Format("  EndMute  %d sec", pMessage->GetMsgPara(0).iVal);
		text += add;
		return text;
	case SSP_START:
		text += "  StartStream";
		return text;
	case SSP_STOP:
		text += "  StopStream";
		return text;
	case SSP_SET_VOLUME:
		add.Format(" SetVolume  %s  %d sec", 
			sspPool::Instance().values.GetName(pMessage->GetMsgPara(0).iVal), pMessage->GetMsgPara(1).iVal);
		text += add;
		return text;
	case SSP_ADJUST_VOLUME:
		add.Format(" AdjustVolume  %s  %d sec", 
			sspPool::Instance().values.GetName(pMessage->GetMsgPara(0).iVal), pMessage->GetMsgPara(1).iVal);
		text += add;
		return text;
	default:
		return "";
	}
}

bool SSpGUIMessage::LoadMessageEditor(SSpStreamMsg* pMessage, BOOL bSpecify)
{
	bool bOK = false;
	CMessageDialog* pDlg = NULL;

	switch (pMessage->GetMessage().GetMsgType()) {
	case SSP_LOAD_EVENT:
		pDlg = new CLoadMessageDialog;
		pDlg->m_strTitle = "Load message editor";
		break;
	case SSP_SOLO:
		pDlg = new CSoloMessageDialog;
		pDlg->m_strTitle = "Solo message editor";
		break;
	case SSP_MUTE:
		pDlg = new CSoloMessageDialog;
		pDlg->m_strTitle = "Mute message editor";
		break;
	case SSP_UNSOLO:
		pDlg = new CSoloMessageDialog;
		pDlg->m_strTitle = "Unsolo message editor";
		break;
	case SSP_UNMUTE:
		pDlg = new CSoloMessageDialog;
		pDlg->m_strTitle = "Unmute message editor";
		break;
	case SSP_START:
		pDlg = new CStartMessageDialog;
		pDlg->m_strTitle = "Start message editor";
		break;
	case SSP_STOP:
		pDlg = new CStartMessageDialog;
		pDlg->m_strTitle = "Stop message editor";
		break;
	case SSP_SET_VOLUME:
		pDlg = new CVolumeMessageDialog;
		pDlg->m_strTitle = "Set volume editor";
		break;
	case SSP_ADJUST_VOLUME:
		pDlg = new CVolumeMessageDialog;
		pDlg->m_strTitle = "Adjust volume editor";
		break;
	default:
		break;
	}

	if (pDlg) {
		pDlg->m_msg = *pMessage;
		pDlg->m_bSpecify = bSpecify;
		if (pDlg->DoModal() == IDOK) {
			*pMessage = pDlg->m_msg;
			bOK = true;
		}
		delete pDlg;
	}

	return bOK;
}

void SSpGUIMessage::FillMessageData(SSpStreamMsg* pMessage, int nType)
{
	pMessage->SetStream(USE_SEND_PARAMETER);
	pMessage->GetMessage().SetMsgType(nType);

	switch (nType) {
	case SSP_LOAD_EVENT:
		pMessage->GetMsgPara(0).Clean();
		pMessage->GetMsgPara(1).iVal = USE_SEND_PARAMETER;
		break;
	case SSP_SOLO:
	case SSP_MUTE:
	case SSP_UNSOLO:
	case SSP_UNMUTE:
	case SSP_START:
	case SSP_STOP:
		pMessage->GetMsgPara(0).iVal = sspSetting::fade.fadeOut;
		pMessage->GetMsgPara(1).iVal = USE_SEND_PARAMETER;
		break;
	case SSP_SET_VOLUME:
	case SSP_ADJUST_VOLUME:
		pMessage->GetMsgPara(0).Clean();
		pMessage->GetMsgPara(1).iVal = sspSetting::fade.volume;
		break;
	default:
		break;
	}
}

