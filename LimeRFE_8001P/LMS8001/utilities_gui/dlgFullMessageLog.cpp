#include "dlgFullMessageLog.h"

lms8_dlgFullMessageLog::lms8_dlgFullMessageLog(wxWindow *parent)
    : lms8_dlgFullMessageLog_view(parent)
{
}

void lms8_dlgFullMessageLog::AddMessages(const std::deque<wxString> &messages)
{
    for (auto msg : messages)
        txtMessageField->AppendText(msg + _("\n"));
}
