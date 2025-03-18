# EventViewer

## A simple viewer for cues and timecode over OSC.

Currently binds to port 9000, accepts timecode as Hour, Min, Sec, Frame at address `/tc`.

Accepts cue information as Seconds (int32) and cue name (String) at `/cue`.
