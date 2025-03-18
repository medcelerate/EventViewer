# EventViewer
<img width="987" alt="Screenshot 2025-03-17 at 9 15 38 PM" src="https://github.com/user-attachments/assets/562e975d-3bc9-4555-9ac5-9a4ca262c10f" />

## A simple viewer for cues and timecode over OSC.

Currently binds to port 9000, accepts timecode as Hour, Min, Sec, Frame at address `/tc`.

Accepts cue information as Seconds (int32) and cue name (String) at `/cue`.
